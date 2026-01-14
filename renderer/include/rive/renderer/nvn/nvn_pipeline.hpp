#pragma once

#include "rive/renderer/gpu.hpp"
#include "rive/renderer/nvn/nvn_shader_utils.hpp"

#include <string>

namespace rive::gpu::nvn
{
struct ProgramSources
{
    std::string vertex;
    std::string fragment;
};

ProgramSources BuildAtomicProgramSources(const ShaderBuildParams& params,
                                         const char* versionLine);
} // namespace rive::gpu::nvn
