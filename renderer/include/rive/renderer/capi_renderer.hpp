#pragma once

#include "rive/renderer/render_target.hpp"

class RiveRenderTarget : public rive::gpu::RenderTarget
{
public:
    RiveRenderTarget(uint32_t width, uint32_t height) :
        rive::gpu::RenderTarget(width, height)
    {}
    virtual ~RiveRenderTarget() = default;
};
