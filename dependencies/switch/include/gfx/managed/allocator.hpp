#pragma once
#include "nvn/nvn.hpp"

#include <atomic>

class GfxAllocator {
private:
    void* mem;
    size_t mem_size;
    nvn::MemoryPool pool;
    std::atomic<ptrdiff_t> block_offset;
    std::atomic<size_t> num_blocks;

public:
    GfxAllocator(nvn::Device* device, uint64_t size, nvn::MemoryPoolFlags flags = nvn::MemoryPoolFlags::CPU_UNCACHED | nvn::MemoryPoolFlags::GPU_CACHED);
    ~GfxAllocator();

    ptrdiff_t Allocate(uint64_t size, uint64_t align = 0);
    void Free(ptrdiff_t block_offset);

    constexpr nvn::MemoryPool& GetPool() { return pool; }
};