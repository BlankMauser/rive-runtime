#pragma once

#include "rive/renderer/gpu.hpp"

#include <string>

namespace rive::gpu::nvn
{
enum class ShaderStage
{
    vertex,
    fragment,
};

enum class AtlasTextureType
{
    r32f,
    r16f,
    r32uiFloatBits,
    r32iFixedPoint,
    rgba8,
};

struct ShaderBuildCaps
{
    bool avoidFlatVaryings = false;
    bool supportsShaderStorageBuffers = true;
    bool framebufferBottomUp = true;
    bool needsBaseInstanceUniform = false;
    bool needsFloatingPointTessellationTexture = false;
    bool isMali = false;
    bool supportsFragmentShaderInterlock = false;
};

struct ShaderBuildParams
{
    DrawType drawType = DrawType::midpointFanPatches;
    ShaderFeatures shaderFeatures = ShaderFeatures::NONE;
    ShaderMiscFlags miscFlags = ShaderMiscFlags::none;
    AtlasTextureType atlasTextureType = AtlasTextureType::r32f;
    InterlockMode interlockMode = InterlockMode::atomics;
    ShaderBuildCaps caps = {};
};

// Returns a complete GLSL shader string for atomic-mode rendering.
// Pass versionLine as a full version token (e.g. "450", "310 es").
std::string BuildAtomicShaderSource(ShaderStage stage,
                                    const ShaderBuildParams& params,
                                    const char* versionLine);
} // namespace rive::gpu::nvn
