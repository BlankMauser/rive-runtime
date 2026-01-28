#include "gfx/managed/memory.hpp"
#include "utils.hpp"
#include "mem.h"

GlobalAllocator::GlobalAllocator() : allocator() {
    SL_ASSERTM(
        MemorySize > MemoryManagementSize,
        "GlobalAllocator::GlobalAllocator failed: memory size does not account for memory manager"
    );

    void* memory = memalign(MemoryPageAlign, MemorySize);
    SL_ASSERTM(
        memory != nullptr,
        "GlobalAllocator::GlobalAllocator failed: failed to allocate enough memory"
    );

    this->allocator.Initialize(memory, MemorySize);
    SL_ASSERTM(
        this->allocator.mIsInitialized,
        "GlobalAllocator::GlobalAllocator failed: failed to initialize nn::mem::StandardAllocator"
    );
}

void* GlobalAllocator::AllocImpl(uint64_t size) {
    return this->allocator.Allocate(size);
}

void* GlobalAllocator::AllocAlignedImpl(uint64_t size, uint64_t alignment) {
    return this->allocator.Allocate(size, alignment);
}

void* GlobalAllocator::ReallocImpl(void* address, uint64_t new_size) {
    return this->allocator.Reallocate(address, new_size);
}

void GlobalAllocator::FreeImpl(void* address) {
    this->allocator.Free(address);
}

GlobalAllocator& GlobalAllocator::Instance() {
    static GlobalAllocator instance;
    return instance;
}