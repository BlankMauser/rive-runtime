#pragma once
#include "nvn/nvn.hpp"
#include "allocator.hpp"

class GfxCommandBuffer {
private:
    GfxAllocator* command_memory;
    ptrdiff_t command_block_addr;
    size_t command_size;

    void* control_memory;
    size_t control_size;

    nvn::CommandBuffer* cmd_buffer;

public:
    GfxCommandBuffer(nvn::Device* device, size_t command_size, size_t control_size);
    ~GfxCommandBuffer();

    nvn::CommandBuffer* Get();
    const nvn::CommandBuffer* Get() const;

    void Reset();

    void Begin();
    
    nvn::CommandHandle End();
};