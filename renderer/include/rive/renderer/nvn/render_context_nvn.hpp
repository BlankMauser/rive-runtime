/*
 * Copyright 2026 Rive
 */

#pragma once

#include "rive/capi.h"
#include "rive/renderer/render_context_impl.hpp"
#include "rive/renderer/nvn/render_state_nvn.hpp"
#include "rive/renderer/nvn/shader_program_nvn.hpp"
#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nvn
{
class Device;
class Queue;
class CommandBuffer;
class Texture;
class Program;
class Buffer;
}

class GfxAllocator;

namespace rive::gpu
{
class TextureNVN final : public Texture
{
public:
    TextureNVN(uint32_t width, uint32_t height);

    ::nvn::Texture* texture() const { return m_texture; }
    void setTexture(::nvn::Texture* texture) { m_texture = texture; }

private:
    ::nvn::Texture* m_texture = nullptr;
};

class RenderContextNVNImpl final : public RenderContextImpl
{
public:
    explicit RenderContextNVNImpl(const RiveNVNContextDesc& desc);
    ~RenderContextNVNImpl() override;

    ::nvn::Device* device() const { return m_device; }
    ::nvn::Queue* queue() const { return m_queue; }

    rcp<RenderBuffer> makeRenderBuffer(RenderBufferType,
                                       RenderBufferFlags,
                                       size_t) override;

    rcp<Texture> makeImageTexture(uint32_t width,
                                  uint32_t height,
                                  uint32_t mipLevelCount,
                                  const uint8_t imageDataRGBAPremul[]) override;

    void resizeFlushUniformBuffer(size_t sizeInBytes) override;
    void resizeImageDrawUniformBuffer(size_t sizeInBytes) override;
    void resizePathBuffer(size_t sizeInBytes,
                          gpu::StorageBufferStructure) override;
    void resizePaintBuffer(size_t sizeInBytes,
                           gpu::StorageBufferStructure) override;
    void resizePaintAuxBuffer(size_t sizeInBytes,
                              gpu::StorageBufferStructure) override;
    void resizeContourBuffer(size_t sizeInBytes,
                             gpu::StorageBufferStructure) override;
    void resizeGradSpanBuffer(size_t sizeInBytes) override;
    void resizeTessVertexSpanBuffer(size_t sizeInBytes) override;
    void resizeTriangleVertexBuffer(size_t sizeInBytes) override;
    void resizeGradientTexture(uint32_t width, uint32_t height) override;
    void resizeTessellationTexture(uint32_t width, uint32_t height) override;
    void resizeAtlasTexture(uint32_t width, uint32_t height) override;
    void resizeTransientPLSBacking(uint32_t width,
                                   uint32_t height,
                                   uint32_t planeCount) override;
    void resizeAtomicCoverageBacking(uint32_t width, uint32_t height) override;
    void resizeCoverageBuffer(size_t sizeInBytes) override;

    void* mapFlushUniformBuffer(size_t mapSizeInBytes) override;
    void* mapImageDrawUniformBuffer(size_t mapSizeInBytes) override;
    void* mapPathBuffer(size_t mapSizeInBytes) override;
    void* mapPaintBuffer(size_t mapSizeInBytes) override;
    void* mapPaintAuxBuffer(size_t mapSizeInBytes) override;
    void* mapContourBuffer(size_t mapSizeInBytes) override;
    void* mapGradSpanBuffer(size_t mapSizeInBytes) override;
    void* mapTessVertexSpanBuffer(size_t mapSizeInBytes) override;
    void* mapTriangleVertexBuffer(size_t mapSizeInBytes) override;

    void unmapFlushUniformBuffer(size_t mapSizeInBytes) override;
    void unmapImageDrawUniformBuffer(size_t mapSizeInBytes) override;
    void unmapPathBuffer(size_t mapSizeInBytes) override;
    void unmapPaintBuffer(size_t mapSizeInBytes) override;
    void unmapPaintAuxBuffer(size_t mapSizeInBytes) override;
    void unmapContourBuffer(size_t mapSizeInBytes) override;
    void unmapGradSpanBuffer(size_t mapSizeInBytes) override;
    void unmapTessVertexSpanBuffer(size_t mapSizeInBytes) override;
    void unmapTriangleVertexBuffer(size_t mapSizeInBytes) override;

    void flush(const gpu::FlushDescriptor&) override;
    void registerProgramVariant(uint32_t key,
                                ::nvn::Program* program,
                                bool spirvInput,
                                bool reflectionValid);
    void setInternalBufferGpuRange(uint32_t slot,
                                   uint64_t gpuAddress,
                                   size_t sizeInBytes);
    void setTextureHandle(uint32_t slot, uint64_t handle);
    void setImageHandle(uint32_t slot, uint64_t handle);
    bool compileAndRegisterProgram(uint32_t key,
                                   const void* vertexData,
                                   size_t vertexSize,
                                   const void* fragmentData,
                                   size_t fragmentSize,
                                   bool spirvInput,
                                   bool requireReflection);

    double secondsNow() const override
    {
        auto elapsed = std::chrono::steady_clock::now() - m_localEpoch;
        return std::chrono::duration<double>(elapsed).count();
    }

private:
    struct ProgramVariants
    {
        ::nvn::Program* spirvProgram = nullptr;
        ::nvn::Program* glslProgram = nullptr;
        bool spirvReflectionValid = false;
        bool glslReflectionValid = false;
    };

    struct ShaderProgramStub
    {
        nvn::ShaderBuildParams params;
        std::string vertexSource;
        std::string fragmentSource;
    };
    struct OwnedProgramResources
    {
        std::unique_ptr<GfxAllocator> codeAllocator;
        std::unique_ptr<::nvn::Buffer> vertexBuffer;
        std::unique_ptr<::nvn::Buffer> fragmentBuffer;
        std::unique_ptr<::nvn::Program> program;
        std::vector<uint8_t> controlBytes;
    };

    static void resizeBytes(std::vector<uint8_t>* bytes, size_t sizeInBytes);
    static void* mapBytes(std::vector<uint8_t>* bytes, size_t mapSizeInBytes);
    void cacheShaderProgram(uint32_t key,
                            const gpu::DrawBatch&,
                            const gpu::FlushDescriptor&);
    ::nvn::Program* chooseProgram(uint32_t key,
                                  const gpu::DrawBatch& batch,
                                  bool* outUsingSpirv);

    ::nvn::Device* m_device = nullptr;
    ::nvn::Queue* m_queue = nullptr;
    void* m_getProcAddress = nullptr;

    std::vector<uint8_t> m_flushUniformBytes;
    std::vector<uint8_t> m_imageDrawUniformBytes;
    std::vector<uint8_t> m_pathBytes;
    std::vector<uint8_t> m_paintBytes;
    std::vector<uint8_t> m_paintAuxBytes;
    std::vector<uint8_t> m_contourBytes;
    std::vector<uint8_t> m_gradSpanBytes;
    std::vector<uint8_t> m_tessSpanBytes;
    std::vector<uint8_t> m_triangleBytes;
    std::vector<uint8_t> m_coverageBytes;

    uint32_t m_gradientTextureWidth = 0;
    uint32_t m_gradientTextureHeight = 0;
    uint32_t m_tessTextureWidth = 0;
    uint32_t m_tessTextureHeight = 0;
    uint32_t m_atlasTextureWidth = 0;
    uint32_t m_atlasTextureHeight = 0;
    uint32_t m_transientPLSWidth = 0;
    uint32_t m_transientPLSHeight = 0;
    uint32_t m_transientPLSPlaneCount = 0;
    uint32_t m_atomicCoverageWidth = 0;
    uint32_t m_atomicCoverageHeight = 0;
    uint64_t m_flushUniformGpuAddress = 0;
    size_t m_flushUniformGpuSize = 0;
    uint64_t m_imageDrawUniformGpuAddress = 0;
    size_t m_imageDrawUniformGpuSize = 0;
    uint64_t m_pathBufferGpuAddress = 0;
    size_t m_pathBufferGpuSize = 0;
    uint64_t m_paintBufferGpuAddress = 0;
    size_t m_paintBufferGpuSize = 0;
    uint64_t m_paintAuxBufferGpuAddress = 0;
    size_t m_paintAuxBufferGpuSize = 0;
    uint64_t m_contourBufferGpuAddress = 0;
    size_t m_contourBufferGpuSize = 0;
    std::unordered_map<uint32_t, uint64_t> m_textureHandles;
    std::unordered_map<uint32_t, uint64_t> m_imageHandles;
    bool m_useSpirvInput = nvn::kEnableSpirvInputPath;
    std::unordered_map<uint32_t, ProgramVariants> m_programVariants;
    std::unordered_map<uint64_t, OwnedProgramResources> m_ownedPrograms;
    std::unordered_map<uint32_t, ShaderProgramStub> m_shaderProgramCache;
    std::unordered_set<uint32_t> m_loggedMissingProgramKeys;

    std::chrono::steady_clock::time_point m_localEpoch =
        std::chrono::steady_clock::now();
};
} // namespace rive::gpu
