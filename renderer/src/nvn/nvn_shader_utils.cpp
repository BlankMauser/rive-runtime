#include "rive/renderer/nvn/nvn_shader_utils.hpp"

#include "generated/shaders/advanced_blend.glsl.hpp"
#include "generated/shaders/atomic_draw.glsl.hpp"
#include "generated/shaders/common.glsl.hpp"
#include "generated/shaders/constants.glsl.hpp"
#include "generated/shaders/draw_path_common.glsl.hpp"
#include "generated/shaders/glsl.glsl.exports.h"
#include "generated/shaders/glsl.glsl.hpp"

#include <sstream>
#include <vector>

#ifndef RIVE_NVN_PLS_CLIP_RGBA8
#define RIVE_NVN_PLS_CLIP_RGBA8 1
#endif

#ifndef RIVE_NVN_PLS_BINDING_BASE
#define RIVE_NVN_PLS_BINDING_BASE 0
#endif

#ifndef RIVE_NVN_PLS_FIXED_LAYOUT
#define RIVE_NVN_PLS_FIXED_LAYOUT 1
#endif

namespace rive::gpu::nvn
{
static void append_shader_feature_defines(std::vector<const char*>& defines,
                                          ShaderFeatures features,
                                          DrawType drawType)
{
    ShaderFeatures allowed = ShaderFeaturesMaskFor(drawType,
                                                   InterlockMode::atomics);
    ShaderFeatures enabled = features & allowed;
    for (size_t i = 0; i < kShaderFeatureCount; ++i)
    {
        ShaderFeatures feature = static_cast<ShaderFeatures>(1 << i);
        if (enabled & feature)
        {
            defines.push_back(GetShaderFeatureGLSLName(feature));
        }
    }
}

static void append_draw_type_defines(std::vector<const char*>& defines,
                                     ShaderStage stage,
                                     DrawType drawType,
                                     AtlasTextureType atlasTextureType,
                                     ShaderMiscFlags miscFlags)
{
    switch (drawType)
    {
        case DrawType::midpointFanPatches:
        case DrawType::midpointFanCenterAAPatches:
        case DrawType::outerCurvePatches:
        case DrawType::msaaStrokes:
        case DrawType::msaaMidpointFanBorrowedCoverage:
        case DrawType::msaaMidpointFans:
        case DrawType::msaaMidpointFanStencilReset:
        case DrawType::msaaMidpointFanPathsStencil:
        case DrawType::msaaMidpointFanPathsCover:
        case DrawType::msaaOuterCubics:
            if (stage == ShaderStage::vertex)
            {
                defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);
            }
            defines.push_back(GLSL_DRAW_PATH);
            break;
        case DrawType::interiorTriangulation:
            defines.push_back(GLSL_DRAW_INTERIOR_TRIANGLES);
            break;
        case DrawType::atlasBlit:
            defines.push_back(GLSL_ATLAS_BLIT);
            switch (atlasTextureType)
            {
                case AtlasTextureType::r32uiFloatBits:
                    defines.push_back(GLSL_ATLAS_TEXTURE_R32UI_FLOAT_BITS);
                    break;
                case AtlasTextureType::r32iFixedPoint:
                    defines.push_back(GLSL_ATLAS_TEXTURE_R32I_FIXED_POINT);
                    break;
                case AtlasTextureType::rgba8:
                    defines.push_back(GLSL_ATLAS_TEXTURE_RGBA8_UNORM);
                    break;
                case AtlasTextureType::r32f:
                case AtlasTextureType::r16f:
                    break;
            }
            break;
        case DrawType::imageRect:
            defines.push_back(GLSL_DRAW_IMAGE);
            defines.push_back(GLSL_DRAW_IMAGE_RECT);
            break;
        case DrawType::imageMesh:
            defines.push_back(GLSL_DRAW_IMAGE);
            defines.push_back(GLSL_DRAW_IMAGE_MESH);
            break;
        case DrawType::renderPassInitialize:
            defines.push_back(GLSL_INITIALIZE_PLS);
            defines.push_back(GLSL_DRAW_RENDER_TARGET_UPDATE_BOUNDS);
            if (miscFlags & ShaderMiscFlags::storeColorClear)
            {
                defines.push_back(GLSL_STORE_COLOR_CLEAR);
            }
            if (miscFlags & ShaderMiscFlags::swizzleColorBGRAToRGBA)
            {
                defines.push_back(GLSL_SWIZZLE_COLOR_BGRA_TO_RGBA);
            }
            break;
        case DrawType::renderPassResolve:
            defines.push_back(GLSL_DRAW_RENDER_TARGET_UPDATE_BOUNDS);
            defines.push_back(GLSL_RESOLVE_PLS);
            if (miscFlags & ShaderMiscFlags::coalescedResolveAndTransfer)
            {
                defines.push_back(GLSL_COALESCED_PLS_RESOLVE_AND_TRANSFER);
            }
            break;
        case DrawType::msaaStencilClipReset:
            break;
    }
}

static void append_shader_misc_defines(std::vector<const char*>& defines,
                                       ShaderMiscFlags miscFlags)
{
    if (miscFlags & ShaderMiscFlags::fixedFunctionColorOutput)
    {
        defines.push_back(GLSL_FIXED_FUNCTION_COLOR_OUTPUT);
    }
    if (miscFlags & ShaderMiscFlags::clockwiseFill)
    {
        defines.push_back(GLSL_CLOCKWISE_FILL);
    }
    if (miscFlags & ShaderMiscFlags::borrowedCoveragePass)
    {
        defines.push_back(GLSL_BORROWED_COVERAGE_PASS);
    }
}

std::string BuildAtomicShaderSource(ShaderStage stage,
                                    const ShaderBuildParams& params,
                                    const char* versionLine)
{
    std::vector<const char*> defines;
    defines.reserve(32);

    defines.push_back(GLSL_USING_PLS_STORAGE_TEXTURES);
    defines.push_back(GLSL_PLS_IMPL_STORAGE_TEXTURE);
#if RIVE_NVN_PLS_CLIP_RGBA8
    // Keep clip buffer RGBA8 without changing color blending behavior.
    defines.push_back("RIVE_NVN_PLS_CLIP_RGBA8");
#endif
    // NVN backend hardcodes PLS storage images to 2D for emulator compatibility.
    defines.push_back("RIVE_NVN_PLS_FORCE_2D");
#if RIVE_NVN_PLS_FIXED_LAYOUT
    // Force a stable PLS binding layout to avoid relying on reflection.
    defines.push_back("RIVE_NVN_PLS_FIXED_LAYOUT");
#endif
    if (params.caps.supportsFragmentShaderInterlock)
    {
        // Enable NV_fragment_shader_interlock so PLS atomics serialize.
        defines.push_back("GL_NV_fragment_shader_interlock");
    }

    append_shader_misc_defines(defines, params.miscFlags);
    append_shader_feature_defines(defines,
                                  params.shaderFeatures,
                                  params.drawType);

    if (params.caps.framebufferBottomUp)
    {
        defines.push_back(GLSL_FRAMEBUFFER_BOTTOM_UP);
    }
    if (!params.caps.supportsShaderStorageBuffers)
    {
        defines.push_back(GLSL_DISABLE_SHADER_STORAGE_BUFFERS);
    }

    append_draw_type_defines(defines,
                             stage,
                             params.drawType,
                             params.atlasTextureType,
                             params.miscFlags);

    std::ostringstream shaderSource;
    if (versionLine != nullptr && versionLine[0] != '\0')
    {
        shaderSource << "#version " << versionLine << "\n";
        shaderSource << "#define " << GLSL_GLSL_VERSION << ' ' << versionLine
                     << "\n";
    }

    if (stage == ShaderStage::vertex)
    {
        shaderSource << "#define " << GLSL_VERTEX << "\n";
    }
    else
    {
        shaderSource << "#define " << GLSL_FRAGMENT << "\n";
    }

    if (params.caps.avoidFlatVaryings)
    {
        shaderSource << "#define " << GLSL_OPTIONALLY_FLAT << "\n";
    }
    else
    {
        shaderSource << "#define " << GLSL_OPTIONALLY_FLAT << " flat\n";
    }

    if (params.caps.needsBaseInstanceUniform)
    {
#ifdef GLSL_BASE_INSTANCE_UNIFORM_NAME
        shaderSource << "#define " << GLSL_BASE_INSTANCE_UNIFORM_NAME
                     << " _baseInstance\n";
#endif
    }

    if (params.caps.needsFloatingPointTessellationTexture)
    {
#ifdef GLSL_TESS_TEXTURE_FLOATING_POINT
        shaderSource << "#define " << GLSL_TESS_TEXTURE_FLOATING_POINT << "\n";
#endif
    }

    if (params.caps.isMali)
    {
#ifdef GLSL_GL_RENDERER_MALI
        shaderSource << "#define " << GLSL_GL_RENDERER_MALI << "\n";
#endif
    }

    for (const char* define : defines)
    {
        shaderSource << "#define " << define << " true\n";
    }

#if !RIVE_NVN_PLS_FIXED_LAYOUT
    shaderSource << "#define RIVE_PLS_BINDING_BASE "
                 << RIVE_NVN_PLS_BINDING_BASE << "\n";
    const int plsBindingBase = RIVE_NVN_PLS_BINDING_BASE;
    shaderSource << "#define COLOR_PLANE_IDX " << (plsBindingBase + 0) << "\n";
    shaderSource << "#define CLIP_PLANE_IDX " << (plsBindingBase + 1) << "\n";
    shaderSource << "#define SCRATCH_COLOR_PLANE_IDX " << (plsBindingBase + 2)
                 << "\n";
    shaderSource << "#define COVERAGE_PLANE_IDX " << (plsBindingBase + 3)
                 << "\n";
    shaderSource << "#define PLS_PLANE_COUNT 4\n";
#endif

    shaderSource << rive::gpu::glsl::glsl << "\n";
    shaderSource << rive::gpu::glsl::constants << "\n";
    shaderSource << rive::gpu::glsl::common << "\n";

    if (params.shaderFeatures & ShaderFeatures::ENABLE_ADVANCED_BLEND)
    {
        shaderSource << rive::gpu::glsl::advanced_blend << "\n";
    }

    shaderSource << rive::gpu::glsl::draw_path_common << "\n";
    shaderSource << rive::gpu::glsl::atomic_draw << "\n";

    return shaderSource.str();
}
} // namespace rive::gpu::nvn
