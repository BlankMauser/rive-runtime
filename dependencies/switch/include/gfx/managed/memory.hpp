#pragma once

#include "nn/mem.h"

#define SL_MEM_DEFAULT_SIZE 0x4000000

#ifndef SL_MEM_SIZE
#define SL_MEM_SIZE SL_MEM_DEFAULT_SIZE
#endif

class GlobalAllocator {
private:
    static const uint64_t MemoryPageAlign = 0x1000;
    static const uint64_t MemoryManagementSize = 0x4000;
    static const uint64_t MemorySize = SL_MEM_SIZE;

    nn::mem::StandardAllocator allocator;

    GlobalAllocator();

    void* AllocImpl(uint64_t size);
    void* AllocAlignedImpl(uint64_t size, uint64_t align);
    void* ReallocImpl(void* address, uint64_t new_size);
    void FreeImpl(void* address);

    static GlobalAllocator& Instance();

public:
    static inline void* Alloc(uint64_t size) { return Instance().AllocImpl(size); }
    static inline void* AllocAligned(uint64_t size, uint64_t align) { return Instance().AllocAlignedImpl(size, align); }
    static inline void* Realloc(void* address, uint64_t new_size) { return Instance().ReallocImpl(address, new_size); }
    static inline void Free(void* address) { return Instance().FreeImpl(address); }
};