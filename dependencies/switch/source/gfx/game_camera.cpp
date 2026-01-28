#include "gfx/game_camera.hpp"
#include "skyline/inlinehook/And64InlineHook.hpp"
#include "smash.hpp"
#include "environment.hpp"

namespace app {
    struct FighterManager;
}

extern "C" {
    extern app::FighterManager* _ZN3lib9SingletonIN3app14FighterManagerEE9instance_E;
    extern void* _ZN3app8lua_bind38FighterManager__get_fighter_entry_implEPNS_14FighterManagerENS_14FighterEntryIDE(app::FighterManager*, u32);
}

app::BattleObject* get_battle_object_from_id(u32 id) {
    return  reinterpret_cast<app::BattleObject* (*)(u32)>(skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x3ac540)(id);
}

app::BattleObject* get_battle_object_from_entry_id(u32 entry_id) {
    void* entry = _ZN3app8lua_bind38FighterManager__get_fighter_entry_implEPNS_14FighterManagerENS_14FighterEntryIDE(
        _ZN3lib9SingletonIN3app14FighterManagerEE9instance_E,
        entry_id
    );

    if (entry) {
        return *reinterpret_cast<app::BattleObject**>((reinterpret_cast<u8*>(entry) + 0x4160));
    }
}

u32 get_active_battle_object_id_from_entry_id(u32 entry_id) {
    auto* object = get_battle_object_from_entry_id(entry_id);
    if (!object) return 0xFFFFFFFF;

    auto kind = object->kind;
    auto status = app::lua_bind::StatusModule::status_kind_impl(object->accessor);
    if (status != -1 && status != 0x1d6)
        return object->id;

    if (kind == 0x5b || kind == 0x5c) {
        return object->id + 0x10000;
    }

    if (kind == 0x24 || kind == 0x25 || kind == 0x26) {
        auto next_id = object->id + 0x10000;
        auto next_object = get_battle_object_from_id(next_id);
        auto next_status = app::lua_bind::StatusModule::status_kind_impl(next_object->accessor);
        if (next_status != -1 && next_status != 0x1d6) {
            return next_id;
        } else {
            return next_id + 0x10000;
        }
    } else {
        return object->id;
    }
}

static void (*s_CameraUpdate)(f32*) = nullptr;
static bool s_AsmFlag = true;

void asm_flag_set(InlineCtx* ctx) {
    if (s_AsmFlag) {
        asm(
            "str q1, [%0, #0xf0]" : : "r"(ctx->registers[19].x)
        );
    }
}

void camera_update_hook(f32* args) {
    if (g_DrawSettings.camera_angle == 0) {
        s_CameraUpdate(args);
        return;
    }
    
    auto object_id = get_active_battle_object_id_from_entry_id(0);
    if (object_id == 0xFFFFFFFF)
        return;

    auto* object = get_battle_object_from_id(0);
    if (!object) return;

    auto offset = phx::Vector3f { 0.0f, 0.0f, 0.0f };
    auto pos = phx::Vector3f { 0.0f, 0.0f, 0.0f };

    app::lua_bind::ModelModule::joint_global_position_with_offset_impl(
        object->accessor,
        phx::Hash40 { 0x4a7f3f69c },
        offset,
        pos,
        false
    );

    auto base_pos = pos;
    auto angle_x = 0.0f;
    auto angle_y = 0.0f;
    switch (g_DrawSettings.camera_angle) {
        case 1:
            pos.x -= 25.0f;
            angle_x = 3.1415f / 2.0f;
            break;
        case 2:
            pos.y += 25.0f;
            angle_x = 3.1415f / -2.0f;
            break;
        case 3:
            pos.x += 25.0f;
            angle_y = 3.1415f / 2.0f;
            break;
        default: break;
    }

    auto* instance = CameraManager::Instance();
    instance->position = pos;
    instance->angle_x = angle_x;
    instance->angle_y = angle_y;

    s_AsmFlag = false;
    s_CameraUpdate(args);
    s_AsmFlag = true;
}

void install_camera() {
    // A64HookFunction(
    //     reinterpret_cast<void*>(skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x4ec7e0),
    //     reinterpret_cast<void*>(camera_update_hook),
    //     reinterpret_cast<void**>(&s_CameraUpdate)
    // );
    // A64InlineHook(
    //     reinterpret_cast<void*>(skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x4ed1e4),
    //     reinterpret_cast<void*>(asm_flag_set)
    // );
}