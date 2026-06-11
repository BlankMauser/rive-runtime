/*
 * Copyright 2026 Rive
 */

#include "rive/renderer/nvn/shader_program_nvn.hpp"

#include "generated/shaders/advanced_blend.glsl.hpp"
#include "generated/shaders/atomic_draw.glsl.hpp"
#include "generated/shaders/common.glsl.hpp"
#include "generated/shaders/constants.glsl.hpp"
#include "generated/shaders/draw_path_common.glsl.hpp"
#include "generated/shaders/glsl.glsl.hpp"
#include <sstream>

namespace rive::gpu::nvn
{
static void append_stage_define(std::stringstream* ss, ShaderStage stage)
{
    if (stage == ShaderStage::vertex)
    {
        *ss << "#define _EXPORTED_VERTEX 1\n";
    }
    else
    {
        *ss << "#define _EXPORTED_FRAGMENT 1\n";
    }
}

static void append_interlock_defines(std::stringstream* ss,
                                     const ShaderBuildParams& params)
{
    switch (params.interlockMode)
    {
        case InterlockMode::rasterOrdering:
            *ss << "#define _EXPORTED_RENDER_MODE_RASTER_ORDERED 1\n";
            break;
        case InterlockMode::atomics:
            *ss << "#define _EXPORTED_RENDER_MODE_ATOMIC 1\n";
            break;
        case InterlockMode::clockwise:
            *ss << "#define _EXPORTED_RENDER_MODE_CLOCKWISE 1\n";
            break;
        case InterlockMode::clockwiseAtomic:
            *ss << "#define _EXPORTED_RENDER_MODE_CLOCKWISE_ATOMIC 1\n";
            break;
        case InterlockMode::msaa:
            *ss << "#define _EXPORTED_RENDER_MODE_MSAA 1\n";
            break;
    }
}

std::string BuildAtomicShaderSource(ShaderStage stage,
                                    const ShaderBuildParams& params,
                                    const char* shaderMainSource)
{
    std::stringstream source;

    source << "#version 460\n";
    source << "#define _EXPORTED_GLSL_VERSION 460\n";
    source << "#define RIVE_NVN 1\n";
    source << "#define TARGET_NVN_SPIRV 1\n";
    source << "#define RIVE_NVN_PLS_FIXED_LAYOUT 1\n";
    source << "#define RIVE_NVN_PLS_FORCE_2D 1\n";
    source << "#define _EXPORTED_PLS_IMPL_STORAGE_TEXTURE 1\n";
    source << "#define _EXPORTED_USING_PLS_STORAGE_TEXTURES 1\n";
    append_stage_define(&source, stage);
    append_interlock_defines(&source, params);

    if (params.fixedFunctionColorOutput)
    {
        source << "#define _EXPORTED_FIXED_FUNCTION_COLOR_OUTPUT 1\n";
    }
    if ((params.shaderFeatures & ShaderFeatures::ENABLE_ADVANCED_BLEND) ==
        ShaderFeatures::ENABLE_ADVANCED_BLEND)
    {
        source << "#define _EXPORTED_ENABLE_ADVANCED_BLEND 1\n";
    }

    source << glsl::glsl << '\n';
    source << glsl::common << '\n';
    source << glsl::constants << '\n';
    source << glsl::advanced_blend << '\n';
    source << glsl::draw_path_common << '\n';
    source << glsl::atomic_draw << '\n';
    if (shaderMainSource != nullptr)
    {
        source << shaderMainSource << '\n';
    }
    return source.str();
}
} // namespace rive::gpu::nvn
