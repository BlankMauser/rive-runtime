/*
 * Copyright 2026 Rive
 */

#pragma once

#include "rive/renderer/capi_renderer.hpp"

namespace nvn
{
class Texture;
}

// C API-facing NVN render target wrapper.
class RenderTargetNVN : public RiveRenderTarget
{
public:
    RenderTargetNVN(uint32_t width,
                    uint32_t height,
                    nvn::Texture* colorTexture,
                    nvn::Texture* depthTexture,
                    uint32_t sampleCount) :
        RiveRenderTarget(width, height),
        m_colorTexture(colorTexture),
        m_depthTexture(depthTexture),
        m_sampleCount(sampleCount)
    {}

    nvn::Texture* colorTexture() const { return m_colorTexture; }
    nvn::Texture* depthTexture() const { return m_depthTexture; }
    uint32_t sampleCount() const { return m_sampleCount; }

    void setColorTexture(nvn::Texture* texture) { m_colorTexture = texture; }
    void setDepthTexture(nvn::Texture* texture) { m_depthTexture = texture; }
    void setSampleCount(uint32_t sampleCount) { m_sampleCount = sampleCount; }

private:
    nvn::Texture* m_colorTexture = nullptr;
    nvn::Texture* m_depthTexture = nullptr;
    uint32_t m_sampleCount = 1;
};
