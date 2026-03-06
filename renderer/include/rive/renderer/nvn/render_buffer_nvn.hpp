/*
 * Copyright 2026 Rive
 */

#pragma once

#include "rive/renderer/rive_render_buffer.hpp"
#include <vector>

namespace rive::gpu
{
// CPU-backed buffer used while NVN backend rebuild is in progress.
class RenderBufferNVN final
    : public LITE_RTTI_OVERRIDE(RiveRenderBuffer, RenderBufferNVN)
{
public:
    RenderBufferNVN(RenderBufferType type,
                    RenderBufferFlags flags,
                    size_t sizeInBytes);

    const std::vector<uint8_t>& bytes() const { return m_bytes; }
    const void* data() const
    {
        return m_bytes.empty() ? nullptr : m_bytes.data();
    }
    uint64_t gpuAddress() const { return m_gpuAddress; }
    size_t gpuSizeInBytes() const { return m_gpuSizeInBytes; }
    void setGpuRange(uint64_t gpuAddress, size_t sizeInBytes)
    {
        m_gpuAddress = gpuAddress;
        m_gpuSizeInBytes = sizeInBytes;
    }

private:
    void* onMap() override;
    void onUnmap() override;

    std::vector<uint8_t> m_bytes;
    uint64_t m_gpuAddress = 0;
    size_t m_gpuSizeInBytes = 0;
};
} // namespace rive::gpu
