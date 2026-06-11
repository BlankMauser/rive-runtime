#pragma once
#include "assert.hpp"
#include "types.hpp"
#include "pfncpp.hpp"
#include "classes.hpp"

#define NVN_TYPE(ident) PFNCPP_##ident
#define NVN_VAR(ident) pfncpp_##ident

#define NVN_GLOBAL(ident) \
    NVN_TYPE(ident) NVN_VAR(ident)

#define NVN_LOAD_FUNC(ident, device, getter) \
    NVN_VAR(ident) = reinterpret_cast<NVN_TYPE(ident)>(getter(device, "nvn" #ident))

#define NVN_CONFIRM(ident, location) \
    OCEAN_ASSERT((NVN_VAR(ident) != NULL), location, #ident, 0x69)

// Requires ident ## _orig to be an already existing variable
// Required ident ## _nvnhook to already exist
#define NVN_HOOK(ident, pDevice) \
    A64HookFunction( \
        reinterpret_cast<void*>((pDevice)->GetProcAddress("nvn" #ident)), \
        reinterpret_cast<void*>(ident ## _nvnhook), \
        (void**)&ident ## _orig \
        )

namespace nvn {
   void initialize(Device* pDevice, GetProcAddressPtr getProc);
}
