/*
 * Copyright 2026 Rive
 */

#include "rive/renderer/nvn/render_context_nvn.hpp"

#include "rive/renderer/nvn/render_buffer_nvn.hpp"
#include "rive/renderer/nvn/render_target_nvn.hpp"
#include "rive/shapes/paint/color.hpp"
#include "gfx/managed/allocator.hpp"
#include <nvntool/capi/nvnTool_GlslcInterface.h>
#include "utils/lite_rtti.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <new>
#include <utility>
#include <nvn/nvn.hpp>

namespace
{
static bool g_preferSpirvInput = rive::gpu::nvn::kEnableSpirvInputPath;
constexpr int kFlushUniformBufferIdx = 0;
constexpr int kImageDrawUniformBufferIdx = 2;
constexpr int kPathBufferIdx = 3;
constexpr int kPaintBufferIdx = 4;
constexpr int kPaintAuxBufferIdx = 5;
constexpr int kContourBufferIdx = 6;
constexpr int kImageTextureIdx = 12;
constexpr int kImageSamplerIdx = 13;

static void init_texture_view(::nvn::TextureView* view, ::nvn::Texture* texture)
{
    if (view == nullptr || texture == nullptr)
    {
        return;
    }

    view->SetDefaults();
    view->SetTarget(texture->GetTarget());
    view->SetFormat(texture->GetFormat());
    view->SetLevels(0, std::max(1, texture->GetLevels()));
    view->SetLayers(0, std::max(1, texture->GetDepth()));
}

static int query_device_info(::nvn::Device* device,
                             ::nvn::DeviceInfo info,
                             int fallback)
{
    if (device == nullptr)
    {
        return fallback;
    }
    int value = fallback;
    device->GetInteger(info, &value);
    return value;
}

static bool validate_glslc_output(const void* outputBlob,
                                  size_t outputSize,
                                  bool requireReflection)
{
    if (outputBlob == nullptr || outputSize < sizeof(GLSLCoutput))
    {
        std::fprintf(stderr,
                     "rive_nvn: invalid GLSLC output blob (null or too small)\n");
        return false;
    }

    const auto* output = static_cast<const GLSLCoutput*>(outputBlob);
    if (output->magic != GLSLC_MAGIC_NUMBER)
    {
        std::fprintf(stderr,
                     "rive_nvn: invalid GLSLC output magic 0x%x (expected 0x%x)\n",
                     static_cast<unsigned int>(output->magic),
                     static_cast<unsigned int>(GLSLC_MAGIC_NUMBER));
        return false;
    }

    const size_t declaredSize = static_cast<size_t>(output->size);
    const size_t boundedSize =
        declaredSize == 0 ? outputSize : std::min(outputSize, declaredSize);
    const size_t headersOffset = offsetof(GLSLCoutput, headers);
    const size_t headersBytes =
        static_cast<size_t>(output->numSections) * sizeof(GLSLCsectionHeaderUnion);
    if (headersOffset + headersBytes > boundedSize)
    {
        std::fprintf(stderr,
                     "rive_nvn: GLSLC output header table out of range (%u sections)\n",
                     output->numSections);
        return false;
    }

    bool foundReflection = false;
    for (uint32_t i = 0; i < output->numSections; ++i)
    {
        const GLSLCsectionHeaderCommon& common =
            output->headers[i].genericHeader.common;
        const size_t dataOffset = static_cast<size_t>(common.dataOffset);
        const size_t sectionSize = static_cast<size_t>(common.size);
        if (dataOffset > boundedSize || sectionSize > boundedSize - dataOffset)
        {
            std::fprintf(stderr,
                         "rive_nvn: GLSLC section %u out of range (type=%d)\n",
                         i,
                         static_cast<int>(common.type));
            return false;
        }
        if (common.type == GLSLC_SECTION_TYPE_REFLECTION)
        {
            foundReflection = true;
        }
    }

    if (requireReflection && !foundReflection)
    {
        std::fprintf(stderr,
                     "rive_nvn: GLSLC compile succeeded but emitted no reflection section; should fall back to GLSL input path\n");
        if (rive::gpu::nvn::kEnableGlslFallbackPath)
        {
            g_preferSpirvInput = false;
            std::fprintf(stderr,
                         "rive_nvn: SPIR-V input disabled for subsequent NVN contexts\n");
        }
        return false;
    }
    if (foundReflection)
    {
        std::fprintf(stderr, "rive_nvn: GLSLC reflection section found\n");
    }
    return true;
}

static bool extract_gpu_code_sections(const void* outputBlob,
                                      size_t outputSize,
                                      RiveNVNGpuCodeSections* outSections)
{
    if (outSections == nullptr)
    {
        return false;
    }
    std::memset(outSections, 0, sizeof(*outSections));
    if (outputBlob == nullptr || outputSize < sizeof(GLSLCoutput))
    {
        return false;
    }

    const auto* output = static_cast<const GLSLCoutput*>(outputBlob);
    if (output->magic != GLSLC_MAGIC_NUMBER)
    {
        return false;
    }

    const size_t declaredSize = static_cast<size_t>(output->size);
    const size_t boundedSize =
        declaredSize == 0 ? outputSize : std::min(outputSize, declaredSize);
    const size_t headersOffset = offsetof(GLSLCoutput, headers);
    const size_t headersBytes =
        static_cast<size_t>(output->numSections) * sizeof(GLSLCsectionHeaderUnion);
    if (headersOffset + headersBytes > boundedSize)
    {
        return false;
    }

    for (uint32_t i = 0; i < output->numSections; ++i)
    {
        const GLSLCsectionHeaderUnion& headerUnion = output->headers[i];
        const GLSLCsectionHeaderCommon& common = headerUnion.genericHeader.common;
        if (common.type != GLSLC_SECTION_TYPE_GPU_CODE)
        {
            continue;
        }

        const GLSLCgpuCodeHeader& gpuHeader = headerUnion.gpuCodeHeader;
        const size_t dataOffset = static_cast<size_t>(gpuHeader.dataOffset);
        const size_t dataSize = static_cast<size_t>(gpuHeader.dataSize);
        const size_t controlOffset = static_cast<size_t>(gpuHeader.controlOffset);
        const size_t controlSize = static_cast<size_t>(gpuHeader.controlSize);
        if (dataOffset > boundedSize || dataSize > boundedSize - dataOffset ||
            controlOffset > boundedSize ||
            controlSize > boundedSize - controlOffset)
        {
            return false;
        }

        RiveNVNGpuCodeSection* section = nullptr;
        if (gpuHeader.stage == NVN_SHADER_STAGE_VERTEX)
        {
            section = &outSections->vertex;
        }
        else if (gpuHeader.stage == NVN_SHADER_STAGE_FRAGMENT)
        {
            section = &outSections->fragment;
        }
        if (section == nullptr)
        {
            continue;
        }
        section->control =
            static_cast<const uint8_t*>(outputBlob) + controlOffset;
        section->control_size = static_cast<uint32_t>(controlSize);
        section->code = static_cast<const uint8_t*>(outputBlob) + dataOffset;
        section->code_size = static_cast<uint32_t>(dataSize);
    }

    return outSections->vertex.code != nullptr &&
           outSections->fragment.code != nullptr;
}

static void* glslc_alloc(size_t size, size_t alignment, void* userPtr)
{
    (void)alignment;
    (void)userPtr;
    return std::malloc(size);
}

static void* glslc_realloc(void* ptr, size_t newSize, void* userPtr)
{
    (void)userPtr;
    return std::realloc(ptr, newSize);
}

static void glslc_free(void* ptr, void* userPtr)
{
    (void)userPtr;
    std::free(ptr);
}

static bool glslc_compile_validate_pair(const void* vertexData,
                                        size_t vertexSize,
                                        const void* fragmentData,
                                        size_t fragmentSize,
                                        bool spirvInput,
                                        bool requireReflection,
                                        std::vector<uint8_t>* outOutputBlob)
{
    if (vertexData == nullptr || fragmentData == nullptr)
    {
        std::fprintf(stderr, "rive_nvn: glslc compile input is null\n");
        return false;
    }

    glslcSetAllocator(glslc_alloc, glslc_free, glslc_realloc, nullptr);
    GLSLCcompileObject compileObject = {};
    if (!glslcInitialize(&compileObject))
    {
        std::fprintf(stderr, "rive_nvn: glslcInitialize failed\n");
        return false;
    }

    compileObject.options = glslcGetDefaultOptions();
    compileObject.options.optionFlags.outputGpuBinaries = 1;
    compileObject.options.optionFlags.outputShaderReflection = 1;
    compileObject.options.optionFlags.language =
        spirvInput ? GLSLC_LANGUAGE_SPIRV : GLSLC_LANGUAGE_GLSL;

    const char* stageSources[2] = {
        static_cast<const char*>(vertexData),
        static_cast<const char*>(fragmentData),
    };
    compileObject.input.sources = stageSources;
    compileObject.input.count = 2;

    uint32_t spirvModuleSizes[2] = {static_cast<uint32_t>(vertexSize),
                                    static_cast<uint32_t>(fragmentSize)};
    const char* entryNames[2] = {"main", "main"};
    if (spirvInput)
    {
        compileObject.input.spirvModuleSizes = spirvModuleSizes;
        compileObject.input.spirvEntryPointNames = entryNames;
    }

    bool success = glslcCompile(&compileObject) != 0;
    GLSLCresults* results = compileObject.lastCompiledResults;
    if (!success || results == nullptr || results->glslcOutput == nullptr)
    {
        const GLSLCcompilationStatus* status =
            results != nullptr ? results->compilationStatus : nullptr;
        if (status != nullptr && status->infoLogLength != 0 &&
            status->infoLog != nullptr)
        {
            std::fprintf(stderr, "rive_nvn: glslc compile failed: %s\n", status->infoLog);
        }
        else
        {
            std::fprintf(stderr, "rive_nvn: glslc compile failed without info log\n");
        }
        glslcFinalize(&compileObject);
        return false;
    }

    const GLSLCoutput* output = results->glslcOutput;
    const bool valid =
        validate_glslc_output(output, static_cast<size_t>(output->size), requireReflection);
    if (valid && outOutputBlob != nullptr)
    {
        outOutputBlob->resize(output->size);
        std::memcpy(outOutputBlob->data(), output, output->size);
    }
    glslcFinalize(&compileObject);
    return valid;
}

static size_t align_up(size_t value, size_t alignment)
{
    return (value + alignment - 1) & ~(alignment - 1);
}

static void apply_barriers(::nvn::CommandBuffer* cmd,
                           rive::gpu::BarrierFlags barriers)
{
    if (cmd == nullptr || barriers == rive::gpu::BarrierFlags::none)
    {
        return;
    }

    ::nvn::BarrierBits nvnBarrierBits = static_cast<::nvn::BarrierBits>(0);
    if ((barriers & rive::gpu::BarrierFlags::plsAtomic) !=
            rive::gpu::BarrierFlags::none ||
        (barriers & rive::gpu::BarrierFlags::plsAtomicPreResolve) !=
            rive::gpu::BarrierFlags::none ||
        (barriers & rive::gpu::BarrierFlags::dstBlend) !=
            rive::gpu::BarrierFlags::none ||
        (barriers & rive::gpu::BarrierFlags::preManualResolve) !=
            rive::gpu::BarrierFlags::none)
    {
        nvnBarrierBits |= ::nvn::BarrierBits::ORDER_FRAGMENTS;
    }
    if ((barriers & rive::gpu::BarrierFlags::msaaPostInit) !=
            rive::gpu::BarrierFlags::none ||
        (barriers & rive::gpu::BarrierFlags::clockwiseBorrowedCoverage) !=
            rive::gpu::BarrierFlags::none)
    {
        nvnBarrierBits |= ::nvn::BarrierBits::ORDER_PRIMITIVES;
    }

    if (nvnBarrierBits != static_cast<::nvn::BarrierBits>(0))
    {
        cmd->Barrier(nvnBarrierBits);
    }
}

static void draw_batch(::nvn::CommandBuffer* cmd,
                       const rive::gpu::DrawBatch& batch)
{
    if (cmd == nullptr || batch.elementCount == 0)
    {
        return;
    }

    switch (batch.drawType)
    {
        case rive::gpu::DrawType::renderPassInitialize:
        case rive::gpu::DrawType::renderPassResolve:
            cmd->DrawArrays(::nvn::DrawPrimitive::TRIANGLES, 0, 3);
            break;
        case rive::gpu::DrawType::midpointFanPatches:
        case rive::gpu::DrawType::midpointFanCenterAAPatches:
        case rive::gpu::DrawType::outerCurvePatches:
        case rive::gpu::DrawType::interiorTriangulation:
        case rive::gpu::DrawType::atlasBlit:
        case rive::gpu::DrawType::imageRect:
        case rive::gpu::DrawType::msaaStrokes:
        case rive::gpu::DrawType::msaaMidpointFanBorrowedCoverage:
        case rive::gpu::DrawType::msaaMidpointFans:
        case rive::gpu::DrawType::msaaMidpointFanStencilReset:
        case rive::gpu::DrawType::msaaMidpointFanPathsStencil:
        case rive::gpu::DrawType::msaaMidpointFanPathsCover:
        case rive::gpu::DrawType::msaaOuterCubics:
        case rive::gpu::DrawType::msaaStencilClipReset:
            cmd->DrawArrays(::nvn::DrawPrimitive::TRIANGLES,
                            static_cast<int>(batch.baseElement),
                            static_cast<int>(batch.elementCount));
            break;
        case rive::gpu::DrawType::imageMesh:
        {
            auto* vertexBuffer =
                rive::lite_rtti_cast<rive::gpu::RenderBufferNVN*>(batch.vertexBuffer);
            if (vertexBuffer != nullptr && vertexBuffer->gpuAddress() != 0 &&
                vertexBuffer->gpuSizeInBytes() != 0)
            {
                cmd->BindVertexBuffer(
                    0,
                    static_cast<::nvn::BufferAddress>(vertexBuffer->gpuAddress()),
                    vertexBuffer->gpuSizeInBytes());
            }
            auto* uvBuffer =
                rive::lite_rtti_cast<rive::gpu::RenderBufferNVN*>(batch.uvBuffer);
            if (uvBuffer != nullptr && uvBuffer->gpuAddress() != 0 &&
                uvBuffer->gpuSizeInBytes() != 0)
            {
                cmd->BindVertexBuffer(
                    1,
                    static_cast<::nvn::BufferAddress>(uvBuffer->gpuAddress()),
                    uvBuffer->gpuSizeInBytes());
            }
            auto* indexBuffer = rive::lite_rtti_cast<rive::gpu::RenderBufferNVN*>(
                batch.indexBuffer);
            if (indexBuffer != nullptr && indexBuffer->gpuAddress() != 0)
            {
                const uint64_t elementOffset =
                    static_cast<uint64_t>(batch.baseElement) *
                    sizeof(uint16_t);
                cmd->DrawElements(::nvn::DrawPrimitive::TRIANGLES,
                                  ::nvn::IndexType::UNSIGNED_SHORT,
                                  static_cast<int>(batch.elementCount),
                                  indexBuffer->gpuAddress() + elementOffset);
                break;
            }
            cmd->DrawArrays(::nvn::DrawPrimitive::TRIANGLES,
                            static_cast<int>(batch.baseElement),
                            static_cast<int>(batch.elementCount));
            break;
        }
    }
}

static void bind_uniform_buffer(::nvn::CommandBuffer* cmd,
                                ::nvn::ShaderStage stage,
                                int index,
                                uint64_t gpuAddress,
                                size_t sizeInBytes)
{
    if (cmd == nullptr || gpuAddress == 0 || sizeInBytes == 0)
    {
        return;
    }
    cmd->BindUniformBuffer(stage,
                           index,
                           static_cast<::nvn::BufferAddress>(gpuAddress),
                           sizeInBytes);
}

static void bind_storage_buffer(::nvn::CommandBuffer* cmd,
                                ::nvn::ShaderStage stage,
                                int index,
                                uint64_t gpuAddress,
                                size_t sizeInBytes)
{
    if (cmd == nullptr || gpuAddress == 0 || sizeInBytes == 0)
    {
        return;
    }
    cmd->BindStorageBuffer(stage,
                           index,
                           static_cast<::nvn::BufferAddress>(gpuAddress),
                           sizeInBytes);
}
} // namespace

namespace rive::gpu
{
RenderBufferNVN::RenderBufferNVN(RenderBufferType type,
                                 RenderBufferFlags flags,
                                 size_t sizeInBytes) :
    lite_rtti_override(type, flags, sizeInBytes), m_bytes(sizeInBytes)
{}

void* RenderBufferNVN::onMap()
{
    return m_bytes.empty() ? nullptr : m_bytes.data();
}

void RenderBufferNVN::onUnmap() {}

TextureNVN::TextureNVN(uint32_t width, uint32_t height) : Texture(width, height)
{}

RenderContextNVNImpl::RenderContextNVNImpl(const RiveNVNContextDesc& desc) :
    m_device(static_cast<::nvn::Device*>(desc.device)),
    m_queue(static_cast<::nvn::Queue*>(desc.queue)),
    m_getProcAddress(desc.get_proc_address)
{
    // NVN platform policy: target the fixed Switch feature set directly.
    const bool supportsInterlock = true;
    const bool supportsAdvancedBlend = true;
    m_platformFeatures.supportsRasterOrderingMode = supportsInterlock;
    m_platformFeatures.supportsBlendAdvancedKHR = supportsAdvancedBlend;
    // NVN does not expose a separate coherent advanced blend capability bit.
    m_platformFeatures.supportsBlendAdvancedCoherentKHR = false;
    // Force rasterOrdering-only on NVN until atomics/clockwise modes are
    // fully validated end-to-end in this backend.
    m_platformFeatures.supportsAtomicMode = false;
    m_platformFeatures.supportsClockwiseMode = false;
    m_platformFeatures.supportsClockwiseFixedFunctionMode = false;
    m_platformFeatures.supportsClockwiseAtomicMode = false;
    m_platformFeatures.supportsClipPlanes = true;
    m_platformFeatures.clipSpaceBottomUp = desc.clip_space_bottom_up != 0;
    m_platformFeatures.framebufferBottomUp = desc.framebuffer_bottom_up != 0;
    m_platformFeatures.pathIDGranularity = 1;
    const uint32_t deviceMaxTextureSize = static_cast<uint32_t>(
        std::max(1,
                 query_device_info(
                     m_device, ::nvn::DeviceInfo::MAX_TEXTURE_SIZE, 4096)));
    m_platformFeatures.maxTextureSize = desc.max_texture_size == 0
                                            ? deviceMaxTextureSize
                                            : desc.max_texture_size;
    m_useSpirvInput = g_preferSpirvInput;
    std::fprintf(stderr,
                 "rive_nvn: shader input mode = %s (fallback GLSL: %s)\n",
                 m_useSpirvInput ? "SPIR-V" : "GLSL",
                 nvn::kEnableGlslFallbackPath ? "enabled" : "disabled");
}

RenderContextNVNImpl::~RenderContextNVNImpl()
{
    for (auto& entry : m_ownedPrograms)
    {
        auto& resources = entry.second;
        if (resources.program)
        {
            resources.program->Finalize();
        }
        if (resources.vertexBuffer)
        {
            resources.vertexBuffer->Finalize();
        }
        if (resources.fragmentBuffer)
        {
            resources.fragmentBuffer->Finalize();
        }
    }
}

rcp<RenderBuffer> RenderContextNVNImpl::makeRenderBuffer(RenderBufferType type,
                                                         RenderBufferFlags flags,
                                                         size_t sizeInBytes)
{
    return make_rcp<RenderBufferNVN>(type, flags, sizeInBytes);
}

rcp<Texture> RenderContextNVNImpl::makeImageTexture(
    uint32_t width,
    uint32_t height,
    uint32_t mipLevelCount,
    const uint8_t imageDataRGBAPremul[])
{
    (void)mipLevelCount;
    (void)imageDataRGBAPremul;
    return make_rcp<TextureNVN>(width, height);
}

void RenderContextNVNImpl::resizeBytes(std::vector<uint8_t>* bytes,
                                       size_t sizeInBytes)
{
    bytes->resize(sizeInBytes);
}

void* RenderContextNVNImpl::mapBytes(std::vector<uint8_t>* bytes,
                                     size_t mapSizeInBytes)
{
    assert(mapSizeInBytes <= bytes->size());
    (void)mapSizeInBytes;
    return bytes->empty() ? nullptr : bytes->data();
}

#define RIVE_IMPL_RESIZE_BYTES(NAME, FIELD)                                    \
    void RenderContextNVNImpl::resize##NAME(size_t sizeInBytes)                \
    {                                                                          \
        resizeBytes(&FIELD, sizeInBytes);                                      \
    }

#define RIVE_IMPL_RESIZE_STRUCTURED_BYTES(NAME, FIELD)                         \
    void RenderContextNVNImpl::resize##NAME(size_t sizeInBytes,                \
                                            gpu::StorageBufferStructure)        \
    {                                                                          \
        resizeBytes(&FIELD, sizeInBytes);                                      \
    }

#define RIVE_IMPL_MAP_BYTES(NAME, FIELD)                                       \
    void* RenderContextNVNImpl::map##NAME(size_t mapSizeInBytes)               \
    {                                                                          \
        return mapBytes(&FIELD, mapSizeInBytes);                               \
    }                                                                          \
    void RenderContextNVNImpl::unmap##NAME(size_t) {}

RIVE_IMPL_RESIZE_BYTES(FlushUniformBuffer, m_flushUniformBytes)
RIVE_IMPL_RESIZE_BYTES(ImageDrawUniformBuffer, m_imageDrawUniformBytes)
RIVE_IMPL_RESIZE_STRUCTURED_BYTES(PathBuffer, m_pathBytes)
RIVE_IMPL_RESIZE_STRUCTURED_BYTES(PaintBuffer, m_paintBytes)
RIVE_IMPL_RESIZE_STRUCTURED_BYTES(PaintAuxBuffer, m_paintAuxBytes)
RIVE_IMPL_RESIZE_STRUCTURED_BYTES(ContourBuffer, m_contourBytes)
RIVE_IMPL_RESIZE_BYTES(GradSpanBuffer, m_gradSpanBytes)
RIVE_IMPL_RESIZE_BYTES(TessVertexSpanBuffer, m_tessSpanBytes)
RIVE_IMPL_RESIZE_BYTES(TriangleVertexBuffer, m_triangleBytes)

RIVE_IMPL_MAP_BYTES(FlushUniformBuffer, m_flushUniformBytes)
RIVE_IMPL_MAP_BYTES(ImageDrawUniformBuffer, m_imageDrawUniformBytes)
RIVE_IMPL_MAP_BYTES(PathBuffer, m_pathBytes)
RIVE_IMPL_MAP_BYTES(PaintBuffer, m_paintBytes)
RIVE_IMPL_MAP_BYTES(PaintAuxBuffer, m_paintAuxBytes)
RIVE_IMPL_MAP_BYTES(ContourBuffer, m_contourBytes)
RIVE_IMPL_MAP_BYTES(GradSpanBuffer, m_gradSpanBytes)
RIVE_IMPL_MAP_BYTES(TessVertexSpanBuffer, m_tessSpanBytes)
RIVE_IMPL_MAP_BYTES(TriangleVertexBuffer, m_triangleBytes)

#undef RIVE_IMPL_RESIZE_BYTES
#undef RIVE_IMPL_RESIZE_STRUCTURED_BYTES
#undef RIVE_IMPL_MAP_BYTES

void RenderContextNVNImpl::resizeGradientTexture(uint32_t width, uint32_t height)
{
    m_gradientTextureWidth = width;
    m_gradientTextureHeight = height;
}

void RenderContextNVNImpl::resizeTessellationTexture(uint32_t width,
                                                     uint32_t height)
{
    m_tessTextureWidth = width;
    m_tessTextureHeight = height;
}

void RenderContextNVNImpl::resizeAtlasTexture(uint32_t width, uint32_t height)
{
    m_atlasTextureWidth = width;
    m_atlasTextureHeight = height;
}

void RenderContextNVNImpl::resizeTransientPLSBacking(uint32_t width,
                                                     uint32_t height,
                                                     uint32_t planeCount)
{
    m_transientPLSWidth = width;
    m_transientPLSHeight = height;
    m_transientPLSPlaneCount = planeCount;
}

void RenderContextNVNImpl::resizeAtomicCoverageBacking(uint32_t width,
                                                       uint32_t height)
{
    m_atomicCoverageWidth = width;
    m_atomicCoverageHeight = height;
}

void RenderContextNVNImpl::resizeCoverageBuffer(size_t sizeInBytes)
{
    resizeBytes(&m_coverageBytes, sizeInBytes);
}

void RenderContextNVNImpl::cacheShaderProgram(uint32_t key,
                                              const gpu::DrawBatch& batch,
                                              const gpu::FlushDescriptor& desc)
{
    if (m_shaderProgramCache.find(key) != m_shaderProgramCache.end())
    {
        return;
    }

    nvn::ShaderBuildParams params;
    params.drawType = batch.drawType;
    params.interlockMode = desc.interlockMode;
    params.shaderFeatures = batch.shaderFeatures;
    params.shaderMiscFlags = batch.shaderMiscFlags;
    params.fixedFunctionColorOutput = desc.fixedFunctionColorOutput;

    ShaderProgramStub stub;
    stub.params = params;
    // Main stage snippets are not wired yet; cache the common prologue so we
    // can verify stable keying before glslc/NVN program integration.
    stub.vertexSource =
        nvn::BuildAtomicShaderSource(nvn::ShaderStage::vertex, params, nullptr);
    stub.fragmentSource =
        nvn::BuildAtomicShaderSource(nvn::ShaderStage::fragment, params, nullptr);
    m_shaderProgramCache.emplace(key, std::move(stub));
}

void RenderContextNVNImpl::registerProgramVariant(uint32_t key,
                                                  ::nvn::Program* program,
                                                  bool spirvInput,
                                                  bool reflectionValid)
{
    auto& variants = m_programVariants[key];
    if (spirvInput)
    {
        variants.spirvProgram = program;
        variants.spirvReflectionValid = reflectionValid;
    }
    else
    {
        variants.glslProgram = program;
        variants.glslReflectionValid = reflectionValid;
    }
}

void RenderContextNVNImpl::setInternalBufferGpuRange(uint32_t slot,
                                                     uint64_t gpuAddress,
                                                     size_t sizeInBytes)
{
    switch (slot)
    {
        case RIVE_NVN_INTERNAL_BUFFER_FLUSH_UNIFORM:
            m_flushUniformGpuAddress = gpuAddress;
            m_flushUniformGpuSize = sizeInBytes;
            break;
        case RIVE_NVN_INTERNAL_BUFFER_IMAGE_DRAW_UNIFORM:
            m_imageDrawUniformGpuAddress = gpuAddress;
            m_imageDrawUniformGpuSize = sizeInBytes;
            break;
        case RIVE_NVN_INTERNAL_BUFFER_PATH:
            m_pathBufferGpuAddress = gpuAddress;
            m_pathBufferGpuSize = sizeInBytes;
            break;
        case RIVE_NVN_INTERNAL_BUFFER_PAINT:
            m_paintBufferGpuAddress = gpuAddress;
            m_paintBufferGpuSize = sizeInBytes;
            break;
        case RIVE_NVN_INTERNAL_BUFFER_PAINT_AUX:
            m_paintAuxBufferGpuAddress = gpuAddress;
            m_paintAuxBufferGpuSize = sizeInBytes;
            break;
        case RIVE_NVN_INTERNAL_BUFFER_CONTOUR:
            m_contourBufferGpuAddress = gpuAddress;
            m_contourBufferGpuSize = sizeInBytes;
            break;
        default:
            std::fprintf(stderr, "rive_nvn: unknown internal buffer slot=%u\n", slot);
            break;
    }
}

void RenderContextNVNImpl::setTextureHandle(uint32_t slot, uint64_t handle)
{
    if (handle == 0)
    {
        m_textureHandles.erase(slot);
    }
    else
    {
        m_textureHandles[slot] = handle;
    }
}

void RenderContextNVNImpl::setImageHandle(uint32_t slot, uint64_t handle)
{
    if (handle == 0)
    {
        m_imageHandles.erase(slot);
    }
    else
    {
        m_imageHandles[slot] = handle;
    }
}

bool RenderContextNVNImpl::compileAndRegisterProgram(uint32_t key,
                                                     const void* vertexData,
                                                     size_t vertexSize,
                                                     const void* fragmentData,
                                                     size_t fragmentSize,
                                                     bool spirvInput,
                                                     bool requireReflection)
{
    const uint64_t ownedKey =
        (static_cast<uint64_t>(key) << 1) | (spirvInput ? 1ull : 0ull);
    auto existing = m_ownedPrograms.find(ownedKey);
    if (existing != m_ownedPrograms.end())
    {
        registerProgramVariant(
            key, existing->second.program.get(), spirvInput, true);
        return true;
    }

    std::vector<uint8_t> glslcOutputBlob;
    if (!glslc_compile_validate_pair(vertexData,
                                     vertexSize,
                                     fragmentData,
                                     fragmentSize,
                                     spirvInput,
                                     requireReflection,
                                     &glslcOutputBlob))
    {
        return false;
    }

    RiveNVNGpuCodeSections codeSections = {};
    if (!extract_gpu_code_sections(
            glslcOutputBlob.data(), glslcOutputBlob.size(), &codeSections))
    {
        std::fprintf(stderr,
                     "rive_nvn: failed to extract vertex/fragment GPU code sections\n");
        return false;
    }

    OwnedProgramResources resources;
    const size_t shaderCodeAlign = 0x100;
    const size_t codeBudget = align_up(codeSections.vertex.code_size, shaderCodeAlign) +
                              align_up(codeSections.fragment.code_size,
                                       shaderCodeAlign) +
                              1024;
    resources.codeAllocator = std::make_unique<GfxAllocator>(
        m_device,
        codeBudget,
        ::nvn::MemoryPoolFlags::CPU_UNCACHED |
            ::nvn::MemoryPoolFlags::GPU_CACHED |
            ::nvn::MemoryPoolFlags::SHADER_CODE);

    ptrdiff_t vertexCodeOffset = resources.codeAllocator->Allocate(
        codeSections.vertex.code_size, shaderCodeAlign);
    ptrdiff_t fragmentCodeOffset = resources.codeAllocator->Allocate(
        codeSections.fragment.code_size, shaderCodeAlign);
    void* codeMemory = resources.codeAllocator->GetPool().Map();
    if (codeMemory == nullptr)
    {
        std::fprintf(stderr, "rive_nvn: shader code pool map failed\n");
        return false;
    }
    std::memcpy(static_cast<uint8_t*>(codeMemory) + vertexCodeOffset,
                codeSections.vertex.code,
                codeSections.vertex.code_size);
    std::memcpy(static_cast<uint8_t*>(codeMemory) + fragmentCodeOffset,
                codeSections.fragment.code,
                codeSections.fragment.code_size);

    const size_t vertexControlOffset = 0;
    const size_t fragmentControlOffset =
        align_up(codeSections.vertex.control_size, shaderCodeAlign);
    resources.controlBytes.resize(fragmentControlOffset +
                                  codeSections.fragment.control_size);
    std::memcpy(resources.controlBytes.data() + vertexControlOffset,
                codeSections.vertex.control,
                codeSections.vertex.control_size);
    std::memcpy(resources.controlBytes.data() + fragmentControlOffset,
                codeSections.fragment.control,
                codeSections.fragment.control_size);

    resources.vertexBuffer = std::make_unique<::nvn::Buffer>();
    resources.fragmentBuffer = std::make_unique<::nvn::Buffer>();
    ::nvn::BufferBuilder bufferBuilder;
    bufferBuilder.SetDefaults().SetDevice(m_device);

    bufferBuilder.SetStorage(&resources.codeAllocator->GetPool(),
                             vertexCodeOffset,
                             codeSections.vertex.code_size);
    if (!resources.vertexBuffer->Initialize(&bufferBuilder))
    {
        std::fprintf(stderr, "rive_nvn: vertex shader buffer init failed\n");
        return false;
    }
    bufferBuilder.SetStorage(&resources.codeAllocator->GetPool(),
                             fragmentCodeOffset,
                             codeSections.fragment.code_size);
    if (!resources.fragmentBuffer->Initialize(&bufferBuilder))
    {
        std::fprintf(stderr, "rive_nvn: fragment shader buffer init failed\n");
        return false;
    }

    ::nvn::ShaderData shaderData[2] = {};
    shaderData[0].control = resources.controlBytes.data() + vertexControlOffset;
    shaderData[0].data = resources.vertexBuffer->GetAddress();
    shaderData[1].control = resources.controlBytes.data() + fragmentControlOffset;
    shaderData[1].data = resources.fragmentBuffer->GetAddress();

    resources.program = std::make_unique<::nvn::Program>();
    if (!resources.program->Initialize(m_device))
    {
        std::fprintf(stderr, "rive_nvn: nvn::Program initialize failed\n");
        return false;
    }
    if (!resources.program->SetShaders(2, shaderData))
    {
        std::fprintf(stderr, "rive_nvn: nvn::Program::SetShaders failed\n");
        resources.program->Finalize();
        return false;
    }

    m_ownedPrograms[ownedKey] = std::move(resources);
    registerProgramVariant(
        key, m_ownedPrograms[ownedKey].program.get(), spirvInput, true);
    return true;
}

::nvn::Program* RenderContextNVNImpl::chooseProgram(uint32_t key,
                                                    const gpu::DrawBatch& batch,
                                                    bool* outUsingSpirv)
{
    auto it = m_programVariants.find(key);
    if (it == m_programVariants.end())
    {
        if (m_loggedMissingProgramKeys.insert(key).second)
        {
            std::fprintf(stderr,
                         "rive_nvn: no NVN program registered for key=%u drawType=%u\n",
                         key,
                         static_cast<unsigned int>(batch.drawType));
        }
        return nullptr;
    }

    ProgramVariants& variants = it->second;
    if (m_useSpirvInput && variants.spirvProgram != nullptr &&
        variants.spirvReflectionValid)
    {
        if (outUsingSpirv != nullptr)
        {
            *outUsingSpirv = true;
        }
        return variants.spirvProgram;
    }
    if (m_useSpirvInput && nvn::kEnableGlslFallbackPath &&
        variants.glslProgram != nullptr)
    {
        m_useSpirvInput = false;
        std::fprintf(
            stderr,
            "rive_nvn: falling back to GLSL program for key=%u (SPIR-V missing/invalid reflection)\n",
            key);
    }

    if (variants.glslProgram != nullptr)
    {
        if (outUsingSpirv != nullptr)
        {
            *outUsingSpirv = false;
        }
        return variants.glslProgram;
    }

    if (m_loggedMissingProgramKeys.insert(key).second)
    {
        std::fprintf(stderr,
                     "rive_nvn: program key=%u has no usable variant (spirv=%p glsl=%p)\n",
                     key,
                     static_cast<void*>(variants.spirvProgram),
                     static_cast<void*>(variants.glslProgram));
    }
    return nullptr;
}

void RenderContextNVNImpl::flush(const gpu::FlushDescriptor& desc)
{
    auto* cmd = static_cast<::nvn::CommandBuffer*>(desc.externalCommandBuffer);
    auto* target = static_cast<RenderTargetNVN*>(desc.renderTarget);
    if (cmd == nullptr || target == nullptr || target->colorTexture() == nullptr)
    {
        return;
    }

    const ::nvn::Texture* const colorTarget = target->colorTexture();
    ::nvn::TextureView colorView;
    init_texture_view(&colorView, target->colorTexture());
    const ::nvn::TextureView* colorViewPtr = &colorView;

    const ::nvn::Texture* const depthTarget = target->depthTexture();
    ::nvn::TextureView depthView;
    const ::nvn::TextureView* depthViewPtr = nullptr;
    if (depthTarget != nullptr)
    {
        init_texture_view(&depthView, target->depthTexture());
        depthViewPtr = &depthView;
    }

    const ::nvn::Texture* colorTargets[1] = {colorTarget};
    const ::nvn::Texture* const* colorTargetsPtr = colorTargets;
    const ::nvn::TextureView* colorViews[1] = {colorViewPtr};
    const ::nvn::TextureView* const* colorViewsPtr = colorViews;

    cmd->SetRenderTargets(
        1, colorTargetsPtr, colorViewsPtr, depthTarget, depthViewPtr);

    const IAABB updateBounds = desc.renderTargetUpdateBounds.empty()
                                   ? IAABB{
                                              0,
                                              0,
                                              static_cast<int>(
                                                  desc.renderTarget->width()),
                                              static_cast<int>(
                                                  desc.renderTarget->height())}
                                   : desc.renderTargetUpdateBounds;

    cmd->SetViewport(0,
                     0,
                     static_cast<int>(desc.renderTarget->width()),
                     static_cast<int>(desc.renderTarget->height()));
    cmd->SetScissor(updateBounds.left,
                    updateBounds.top,
                    updateBounds.width(),
                    updateBounds.height());
    cmd->SetRenderEnable(true);
    cmd->SetRasterizerDiscard(false);

    if (desc.colorLoadAction == gpu::LoadAction::clear)
    {
        float clearColor[4];
        UnpackColorToRGBA32F(desc.colorClearValue, clearColor);
        cmd->ClearColor(0, clearColor, ::nvn::ClearColorMask::RGBA);

        if (depthTarget != nullptr)
        {
            cmd->ClearDepthStencil(
                desc.depthClearValue, true, desc.stencilClearValue, 0xff);
        }
    }

    if (desc.drawList == nullptr)
    {
        apply_barriers(cmd, desc.unresolvedBarriers);
        return;
    }

    if (m_flushUniformGpuAddress != 0 &&
        m_flushUniformGpuSize >= desc.flushUniformDataOffsetInBytes +
                                     sizeof(gpu::FlushUniforms))
    {
        const uint64_t flushAddress =
            m_flushUniformGpuAddress + desc.flushUniformDataOffsetInBytes;
        bind_uniform_buffer(cmd,
                            ::nvn::ShaderStage::VERTEX,
                            kFlushUniformBufferIdx,
                            flushAddress,
                            sizeof(gpu::FlushUniforms));
        bind_uniform_buffer(cmd,
                            ::nvn::ShaderStage::FRAGMENT,
                            kFlushUniformBufferIdx,
                            flushAddress,
                            sizeof(gpu::FlushUniforms));
    }

    const size_t pathOffset = desc.firstPath * sizeof(gpu::PathData);
    if (m_pathBufferGpuAddress != 0 && m_pathBufferGpuSize > pathOffset)
    {
        const uint64_t address = m_pathBufferGpuAddress + pathOffset;
        const size_t size = m_pathBufferGpuSize - pathOffset;
        bind_storage_buffer(
            cmd, ::nvn::ShaderStage::VERTEX, kPathBufferIdx, address, size);
        bind_storage_buffer(
            cmd, ::nvn::ShaderStage::FRAGMENT, kPathBufferIdx, address, size);
    }

    const size_t paintOffset = desc.firstPaint * sizeof(gpu::PaintData);
    if (m_paintBufferGpuAddress != 0 && m_paintBufferGpuSize > paintOffset)
    {
        const uint64_t address = m_paintBufferGpuAddress + paintOffset;
        const size_t size = m_paintBufferGpuSize - paintOffset;
        bind_storage_buffer(
            cmd, ::nvn::ShaderStage::VERTEX, kPaintBufferIdx, address, size);
        bind_storage_buffer(
            cmd, ::nvn::ShaderStage::FRAGMENT, kPaintBufferIdx, address, size);
    }

    const size_t paintAuxOffset = desc.firstPaintAux * sizeof(gpu::PaintAuxData);
    if (m_paintAuxBufferGpuAddress != 0 && m_paintAuxBufferGpuSize > paintAuxOffset)
    {
        const uint64_t address = m_paintAuxBufferGpuAddress + paintAuxOffset;
        const size_t size = m_paintAuxBufferGpuSize - paintAuxOffset;
        bind_storage_buffer(
            cmd, ::nvn::ShaderStage::VERTEX, kPaintAuxBufferIdx, address, size);
        bind_storage_buffer(cmd,
                            ::nvn::ShaderStage::FRAGMENT,
                            kPaintAuxBufferIdx,
                            address,
                            size);
    }

    const size_t contourOffset = desc.firstContour * sizeof(gpu::ContourData);
    if (m_contourBufferGpuAddress != 0 && m_contourBufferGpuSize > contourOffset)
    {
        const uint64_t address = m_contourBufferGpuAddress + contourOffset;
        const size_t size = m_contourBufferGpuSize - contourOffset;
        bind_storage_buffer(
            cmd, ::nvn::ShaderStage::VERTEX, kContourBufferIdx, address, size);
        bind_storage_buffer(
            cmd, ::nvn::ShaderStage::FRAGMENT, kContourBufferIdx, address, size);
    }

    for (const auto& entry : m_imageHandles)
    {
        cmd->BindImage(::nvn::ShaderStage::FRAGMENT,
                       static_cast<int>(entry.first),
                       static_cast<::nvn::ImageHandle>(entry.second));
    }

    for (const gpu::DrawBatch& batch : *desc.drawList)
    {
        const uint32_t key = ShaderUniqueKey(batch.drawType,
                                             batch.shaderFeatures,
                                             desc.interlockMode,
                                             batch.shaderMiscFlags);
        cacheShaderProgram(key, batch, desc);
        bool usingSpirvProgram = false;
        ::nvn::Program* program = chooseProgram(key, batch, &usingSpirvProgram);
        if (program == nullptr)
        {
            continue;
        }
        auto textureIt = m_textureHandles.find(kImageTextureIdx);
        if (textureIt != m_textureHandles.end())
        {
            cmd->BindTexture(::nvn::ShaderStage::FRAGMENT,
                             kImageTextureIdx,
                             static_cast<::nvn::TextureHandle>(textureIt->second));
        }
        auto samplerIt = m_textureHandles.find(kImageSamplerIdx);
        if (samplerIt != m_textureHandles.end())
        {
            cmd->BindTexture(::nvn::ShaderStage::FRAGMENT,
                             kImageSamplerIdx,
                             static_cast<::nvn::TextureHandle>(samplerIt->second));
        }
        if (m_imageDrawUniformGpuAddress != 0 &&
            batch.imageDrawDataOffset + sizeof(gpu::ImageDrawUniforms) <=
                m_imageDrawUniformGpuSize)
        {
            bind_uniform_buffer(
                cmd,
                ::nvn::ShaderStage::FRAGMENT,
                kImageDrawUniformBufferIdx,
                m_imageDrawUniformGpuAddress + batch.imageDrawDataOffset,
                sizeof(gpu::ImageDrawUniforms));
        }
        cmd->BindProgram(program,
                         ::nvn::ShaderStageBits::VERTEX |
                             ::nvn::ShaderStageBits::FRAGMENT);
        apply_barriers(cmd, batch.barriers);
        draw_batch(cmd, batch);
    }

    apply_barriers(cmd, desc.unresolvedBarriers);
}
} // namespace rive::gpu

extern "C"
{
RiveRenderTarget* rive_nvn_render_target_new(uint32_t width,
                                             uint32_t height,
                                             void* color_texture,
                                             void* depth_texture,
                                             uint32_t sample_count)
{
    auto* target = new (std::nothrow)
        RenderTargetNVN(width,
                        height,
                        static_cast<::nvn::Texture*>(color_texture),
                        static_cast<::nvn::Texture*>(depth_texture),
                        sample_count == 0 ? 1 : sample_count);
    return target;
}

void rive_nvn_render_buffer_set_gpu_range(void* buffer,
                                          uint64_t gpu_address,
                                          size_t size_in_bytes)
{
    auto* nvnBuffer = reinterpret_cast<rive::gpu::RenderBufferNVN*>(buffer);
    if (nvnBuffer == nullptr)
    {
        return;
    }
    nvnBuffer->setGpuRange(gpu_address, size_in_bytes);
}

RiveRenderContextImpl* rive_nvn_render_context_impl_new(
    const RiveNVNContextDesc* desc)
{
    if (desc == nullptr || desc->device == nullptr || desc->queue == nullptr)
    {
        return nullptr;
    }
    auto* impl = new (std::nothrow) rive::gpu::RenderContextNVNImpl(*desc);
    return reinterpret_cast<RiveRenderContextImpl*>(impl);
}

int rive_nvn_validate_glslc_output(const void* output_blob,
                                   size_t output_size,
                                   int require_reflection)
{
    return validate_glslc_output(
               output_blob, output_size, require_reflection != 0)
               ? 1
               : 0;
}

int rive_nvn_uses_spirv_input(void)
{
    return g_preferSpirvInput ? 1 : 0;
}

void rive_nvn_set_prefer_spirv_input(int enabled)
{
    g_preferSpirvInput = enabled != 0;
}

uint32_t rive_nvn_shader_unique_key(uint32_t draw_type,
                                    uint32_t shader_features,
                                    uint32_t interlock_mode,
                                    uint32_t shader_misc_flags)
{
    return rive::gpu::ShaderUniqueKey(
        static_cast<rive::gpu::DrawType>(draw_type),
        static_cast<rive::gpu::ShaderFeatures>(shader_features),
        static_cast<rive::gpu::InterlockMode>(interlock_mode),
        static_cast<rive::gpu::ShaderMiscFlags>(shader_misc_flags));
}

int rive_nvn_register_program(RiveRenderContextImpl* impl,
                              uint32_t shader_key,
                              void* program,
                              int spirv_input,
                              const void* glslc_output_blob,
                              size_t glslc_output_size,
                              int require_reflection)
{
    auto* nvnImpl = reinterpret_cast<rive::gpu::RenderContextNVNImpl*>(impl);
    if (nvnImpl == nullptr || program == nullptr)
    {
        return 0;
    }

    bool reflectionValid = true;
    if (glslc_output_blob != nullptr && glslc_output_size != 0)
    {
        reflectionValid = validate_glslc_output(glslc_output_blob,
                                                glslc_output_size,
                                                require_reflection != 0);
        if (!reflectionValid && (spirv_input != 0 || require_reflection != 0))
        {
            return 0;
        }
    }
    else if (require_reflection != 0)
    {
        std::fprintf(stderr,
                     "rive_nvn: reflection required but no GLSLC output blob was provided\n");
        return 0;
    }

    nvnImpl->registerProgramVariant(shader_key,
                                    static_cast<::nvn::Program*>(program),
                                    spirv_input != 0,
                                    reflectionValid);
    return 1;
}

void rive_nvn_set_internal_buffer_gpu_range(RiveRenderContextImpl* impl,
                                            uint32_t slot,
                                            uint64_t gpu_address,
                                            size_t size_in_bytes)
{
    auto* nvnImpl = reinterpret_cast<rive::gpu::RenderContextNVNImpl*>(impl);
    if (nvnImpl == nullptr)
    {
        return;
    }
    nvnImpl->setInternalBufferGpuRange(slot, gpu_address, size_in_bytes);
}

int rive_nvn_set_texture_handle(RiveRenderContextImpl* impl,
                                uint32_t slot,
                                uint64_t texture_handle)
{
    auto* nvnImpl = reinterpret_cast<rive::gpu::RenderContextNVNImpl*>(impl);
    if (nvnImpl == nullptr)
    {
        return 0;
    }
    nvnImpl->setTextureHandle(slot, texture_handle);
    return 1;
}

int rive_nvn_set_image_handle(RiveRenderContextImpl* impl,
                              uint32_t slot,
                              uint64_t image_handle)
{
    auto* nvnImpl = reinterpret_cast<rive::gpu::RenderContextNVNImpl*>(impl);
    if (nvnImpl == nullptr)
    {
        return 0;
    }
    nvnImpl->setImageHandle(slot, image_handle);
    return 1;
}

int rive_nvn_glslc_compile_validate(const void* vertex_data,
                                    size_t vertex_size,
                                    const void* fragment_data,
                                    size_t fragment_size,
                                    int spirv_input,
                                    int require_reflection)
{
    return glslc_compile_validate_pair(vertex_data,
                                       vertex_size,
                                       fragment_data,
                                       fragment_size,
                                       spirv_input != 0,
                                       require_reflection != 0,
                                       nullptr)
               ? 1
               : 0;
}

int rive_nvn_compile_and_register_program(RiveRenderContextImpl* impl,
                                          uint32_t shader_key,
                                          const void* vertex_data,
                                          size_t vertex_size,
                                          const void* fragment_data,
                                          size_t fragment_size,
                                          int spirv_input,
                                          int require_reflection)
{
    auto* nvnImpl = reinterpret_cast<rive::gpu::RenderContextNVNImpl*>(impl);
    if (nvnImpl == nullptr)
    {
        return 0;
    }
    return nvnImpl->compileAndRegisterProgram(shader_key,
                                              vertex_data,
                                              vertex_size,
                                              fragment_data,
                                              fragment_size,
                                              spirv_input != 0,
                                              require_reflection != 0)
               ? 1
               : 0;
}

int rive_nvn_extract_gpu_code_sections(const void* output_blob,
                                       size_t output_size,
                                       RiveNVNGpuCodeSections* out_sections)
{
    return extract_gpu_code_sections(output_blob, output_size, out_sections) ? 1
                                                                             : 0;
}

RiveRenderContext* rive_nvn_render_context_new(const RiveNVNContextDesc* desc)
{
    RiveRenderContextImpl* impl = rive_nvn_render_context_impl_new(desc);
    if (impl == nullptr)
    {
        return nullptr;
    }
    return rive_render_context_new(impl);
}
}
