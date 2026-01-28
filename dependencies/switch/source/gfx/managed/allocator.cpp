#include "gfx/managed/allocator.hpp"
#include "gfx/managed/memory.hpp"
#include "utils.hpp"

static constexpr size_t StorageAlignment   = 0x1000;
static constexpr size_t StorageGranularity = 0x1000;

GfxAllocator::GfxAllocator(nvn::Device* device, uint64_t size, nvn::MemoryPoolFlags flags) {
    this->mem_size = SL_ALIGN(size, StorageGranularity);
    this->mem = GlobalAllocator::AllocAligned(this->mem_size, StorageAlignment);
    SL_ASSERTM(this->mem, "GfxAllocator::GfxAllocator failed: global allocator has run out of memory");
    nvn::MemoryPoolBuilder builder;
    builder
        .SetDefaults()
        .SetDevice(device)
        .SetFlags(flags)
        .SetStorage(this->mem, this->mem_size);
    SL_ASSERT(this->pool.Initialize(&builder));
    this->block_offset.store(0);
    this->num_blocks.store(0);
}

GfxAllocator::~GfxAllocator() {
    this->pool.Finalize();
    GlobalAllocator::Free(this->mem);
}

ptrdiff_t GfxAllocator::Allocate(uint64_t size, uint64_t align) {
    ptrdiff_t cur = block_offset.load();
    size_t aligned = (align ? SL_ALIGN(cur, align) : cur) + size;
    SL_ASSERTM(aligned <= this->mem_size, "GfxAllocator::Allocate failed: run out of memory");
    block_offset.store(aligned);
    return aligned - size;
}

void GfxAllocator::Free(ptrdiff_t block_offset) {
    SL_ASSERTM(false, "GfxAllocator::Free failed: unimplemented");
}