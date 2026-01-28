#pragma once
#include "nvn/nvn.hpp"

extern nvn::Device* g_Device;
extern int g_DisplayWidth;
extern int g_DisplayHeight;
extern int g_DisplayTextureIndex;
extern bool g_IsCameraUpdateOnly;
extern bool g_IsReplay;
extern bool g_ShouldDoubleSpeed;

struct DrawSettings {
    bool input;
    bool ecb;
    bool ledge_grab;
    bool hurtboxes;
    int camera_angle;
};

extern DrawSettings g_DrawSettings;

extern "C" void sl_device_add_init_callback(void (*callback)());
nvn::Texture* sl_window_get_texture(int index);
void sl_window_render_to_active_texture(nvn::CommandBuffer* cmdbuf);
bool sl_is_match_active();

#ifdef COORDS
#include "smash.hpp"
inline phx::Vector2f normalize_texture(const phx::Vector2f& coords, const phx::Vector2f& dimensions) {
    return phx::Vector2f {
        coords.x / dimensions.x,
        coords.y / dimensions.y
    };
}

inline phx::Vector2f normalize_coords(const phx::Vector2f& coords, const phx::Vector2f& dimensions) {
    float divisor_x = (float)dimensions.x / 2.0;
    float divisor_y = (float)dimensions.y / -2.0f;
    return phx::Vector2f {
        coords.x / divisor_x - 1,
        coords.y / divisor_y + 1
    };
}

inline phx::Vector2f normalize_screen_coords(const phx::Vector2f& coords) {
    return normalize_coords(coords, { (float)1920.0f, (float)1080.0f });
}
#endif