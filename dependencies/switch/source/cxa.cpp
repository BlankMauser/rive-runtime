#include "cxa.h"
#include "nn/ro.h"

void __cxa_atexit() {}

extern "C" s32 __cxa_guard_acquire(u32 *guard) {
    static uintptr_t ptr = 0;
    if (ptr == 0) {
        nn::ro::Initialize();
        nn::ro::LookupSymbol(&ptr, "__cxa_guard_acquire");
    }
    if (ptr) {
        return reinterpret_cast<s32 (*)(u32*)>(ptr)(guard);
    }
    if (!guard) {
        return 0;
    }
    if (*guard) {
        return 0;
    }
    *guard = 1;
    return 1;
}
extern "C" void __cxa_guard_release(u32 *guard) {
    static uintptr_t ptr = 0;
    if (ptr == 0) {
        nn::ro::Initialize();
        nn::ro::LookupSymbol(&ptr, "__cxa_guard_release");
    }
    if (ptr) {
        reinterpret_cast<void (*)(u32*)>(ptr)(guard);
        return;
    }
    if (guard) {
        *guard = 1;
    }
}
