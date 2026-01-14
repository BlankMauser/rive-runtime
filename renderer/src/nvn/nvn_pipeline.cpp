#include "rive/renderer/nvn/nvn_pipeline.hpp"

namespace rive::gpu::nvn
{
ProgramSources BuildAtomicProgramSources(const ShaderBuildParams& params,
                                         const char* versionLine)
{
    ProgramSources sources;
    sources.vertex = BuildAtomicShaderSource(ShaderStage::vertex,
                                             params,
                                             versionLine);
    sources.fragment = BuildAtomicShaderSource(ShaderStage::fragment,
                                               params,
                                               versionLine);
    return sources;
}
} // namespace rive::gpu::nvn
