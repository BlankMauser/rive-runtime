#include "../environment.hpp"
#include "mem.h"
#include "utils.hpp"

#include "skyline/inlinehook/And64InlineHook.hpp"

#include <vector>

constexpr const char* SET_TEXTURES = "nvnWindowBuilderSetTextures";
constexpr const char* ACQUIRE_TEXTURE = "nvnWindowAcquireTexture";

static nvn::NVN_TYPE(WindowBuilderSetTextures) nvnWindowBuilderSetTextures_orig = nullptr;
static nvn::NVN_TYPE(WindowAcquireTexture) nvnWindowAcquireTexture_orig = nullptr;

static std::vector<nvn::Texture*> s_WindowTextures = {};
int g_DisplayTextureIndex = -1;

void nvnWindowBuilderSetTextures_hook(nvn::WindowBuilder* builder, int count, nvn::Texture** textures) {
    if (textures != nullptr && count > 0) {
        s_WindowTextures.resize(count);
        memcpy(s_WindowTextures.data(), textures, sizeof(nvn::Texture*) * count);
    }
    nvnWindowBuilderSetTextures_orig(builder, count, textures);
}

nvn::WindowAcquireTextureResult::Enum nvnWindowAcquireTexture_hook(nvn::Window* window, nvn::Sync* texture_available, int* index) {
    auto ret = nvnWindowAcquireTexture_orig(window, texture_available, index);
    g_DisplayTextureIndex = *index;
    return ret;
}

nvn::Texture* sl_window_get_texture(int index) {
    SL_ASSERTM(index < s_WindowTextures.size(), "sl_window_get_texture failed: index is outside the texture range");
    return s_WindowTextures[index];
}

void sl_window_render_to_active_texture(nvn::CommandBuffer* cmdbuf) {
    SL_ASSERTM(g_DisplayTextureIndex >= 0, "sl_window_render_to_active_texture failed: window is not initialized");
    cmdbuf->SetRenderTargets(1, &s_WindowTextures[g_DisplayTextureIndex], nullptr, nullptr, nullptr);
}

void install_window_hooks() {
    A64HookFunction(
        reinterpret_cast<void*>(g_Device->GetProcAddress(SET_TEXTURES)),
        reinterpret_cast<void*>(nvnWindowBuilderSetTextures_hook),
        (void**)&nvnWindowBuilderSetTextures_orig
    );
    A64HookFunction(
        reinterpret_cast<void*>(g_Device->GetProcAddress(ACQUIRE_TEXTURE)),
        reinterpret_cast<void*>(nvnWindowAcquireTexture_hook),
        (void**)&nvnWindowAcquireTexture_orig
    );
}