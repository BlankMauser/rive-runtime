#include "../environment.hpp"
#include "utils.hpp"
#include "hook.hpp"

#include "skyline/inlinehook/And64InlineHook.hpp"

#include <vector>

extern "C" {
    nvn::GenericFuncPtr nvnBootstrapLoader(const char* symbol);
}

constexpr const char* DEVICE_INIT = "nvnDeviceInitialize";
constexpr const char* GET_ADDRESS = "nvnDeviceGetProcAddress";

static bool (*nvnDeviceInitialize_orig)(nvn::Device* device, const nvn::DeviceBuilder*);
static nvn::GenericFuncPtr (*nvnBootstrapLoader_orig)(const char* symbol);
static nvn::GetProcAddressPtr nvnDeviceGetProcAddress = nullptr;

static std::vector<void (*)()> s_DeviceInitCallbacks = {};
static nvn::Device* g_Device = nullptr;

/**
 * @brief Hooks nvn's device initialization function, in order to also initialize
 * all of starlight's function pointers
 * 
 * @param device The device being initialized
 * @param builder The device configuration to be used
 * @return true
 */
bool nvnDeviceInitialize_hook(nvn::Device* device, const nvn::DeviceBuilder* builder) {
    // We can just assert here, since if this fails then the game should have never made it into production
    SL_ASSERTM(
        nvnDeviceInitialize_orig(device, builder),
        "nvnDeviceInitialize_hook failed: vanilla device failed to initialize"        
    );

    // store the device so that starlight can use it whenever it wants
    g_Device = device;

    // check to see if we have nvnDeviceGetProcAddress yet (gotten from
    // hooking nvnBootstrapLoader).
    //
    // Technically it isn't a hard requirement to get it that way, so we can
    // manually get it that way
    if (nvnDeviceGetProcAddress == nullptr)
        nvnDeviceGetProcAddress = reinterpret_cast<nvn::GetProcAddressPtr>(nvnBootstrapLoader_orig(GET_ADDRESS));

    // by this point it's ride-or-die, and if we don't have the pointer there is no
    // point in continuing
    SL_ASSERTM(
        nvnDeviceGetProcAddress != nullptr,
        "nvnDeviceInitialize_hook failed: could not retreive nvnDeviceGetProcAddress"
    );

    // get the actual device get proc address
    nvnDeviceGetProcAddress = reinterpret_cast<nvn::GetProcAddressPtr>(nvnDeviceGetProcAddress(device, GET_ADDRESS));
    
    // initialize all available func pointers
    nvn::initialize(device, nvnDeviceGetProcAddress);

    install_window_hooks();
    install_queue_hooks();

    // run our device initialization callbacks
    //
    // this can include starlight's mods or any other plugin that needs
    // access to this information
    for (auto cb : s_DeviceInitCallbacks)
        cb();
    
    return true;
}

/**
 * @brief This hooks watches for nvnDeviceInitialize and hooks it, it also looks
 *        for nvnDeviceGetProcAddress in case that gets received
 * 
 * @param symbol The symbol name to search for
 * @return nvn::GenericFuncPtr 
 */
nvn::GenericFuncPtr nvnBootstrapLoader_hook(const char* symbol) {
    nvn::GenericFuncPtr ret = nvnBootstrapLoader_orig(symbol);
    if (strcmp(symbol, DEVICE_INIT) == 0) {
        A64HookFunction(
            reinterpret_cast<void*>(ret),
            reinterpret_cast<void*>(nvnDeviceInitialize_hook),
            (void**)&nvnDeviceInitialize_orig
        );
    } else if (strcmp(symbol, GET_ADDRESS) == 0)
        nvnDeviceGetProcAddress = reinterpret_cast<nvn::GetProcAddressPtr>(ret);
    
    return ret;
}

void install_device_hooks() {
    A64HookFunction(
        reinterpret_cast<void*>(nvnBootstrapLoader),
        reinterpret_cast<void*>(nvnBootstrapLoader_hook),
        (void**)&nvnBootstrapLoader_orig
    );
}

/**
 * @brief Allows other mods/plugins to add device init, also used by starlight's mods internally
 * 
 * @param callback The callback to run on device initialization
 */
extern "C" void sl_device_add_init_callback(void (*callback)()) {
    s_DeviceInitCallbacks.push_back(callback);
}