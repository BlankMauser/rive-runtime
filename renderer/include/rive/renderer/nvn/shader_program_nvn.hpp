/*
 * Copyright 2026 Rive
 */

#pragma once

#include "rive/renderer/gpu.hpp"
#include <cstdint>
#include <string>

namespace rive::gpu::nvn
{
// NVN per-stage resource limits from local GLSLC docs.
constexpr uint32_t kMaxActiveSSBOBindings = 16;
constexpr uint32_t kMaxActiveUBOBindings = 14;
constexpr uint32_t kMaxActiveCombinedSamplerBindings = 32;
constexpr uint32_t kMaxActiveSeparateSamplerBindings = 32;
constexpr uint32_t kMaxActiveSeparateTextureBindings = 128;
constexpr uint32_t kMaxActiveImageBindings = 8;

// Backend policy while stabilizing NVN path rendering.
constexpr bool kPreferGlslOverSpirv = false;
constexpr bool kEnableSpirvInputPath = true;
constexpr bool kEnableGlslFallbackPath = true;

enum class ShaderStage
{
    vertex,
    fragment,
};

struct ShaderBuildParams
{
    DrawType drawType = DrawType::renderPassInitialize;
    InterlockMode interlockMode = InterlockMode::rasterOrdering;
    ShaderFeatures shaderFeatures = ShaderFeatures::NONE;
    ShaderMiscFlags shaderMiscFlags = ShaderMiscFlags::none;
    bool fixedFunctionColorOutput = false;
};

std::string BuildAtomicShaderSource(ShaderStage stage,
                                    const ShaderBuildParams& params,
                                    const char* shaderMainSource);
} // namespace rive::gpu::nvn
