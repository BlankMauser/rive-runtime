/*
 * Copyright 2026 Rive
 */

#pragma once

#include "rive/renderer/gpu.hpp"

namespace rive::gpu::nvn
{
// Small state cache for command buffer binding churn.
struct BindStateCache
{
    const RenderBuffer* vertexBuffer = nullptr;
    const RenderBuffer* indexBuffer = nullptr;
    const Texture* imageTexture = nullptr;
};
} // namespace rive::gpu::nvn
