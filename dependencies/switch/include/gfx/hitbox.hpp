#pragma once
#include "drawable.hpp"
#include "vbuffer.hpp"
#include "shader.hpp"
#include "smash.hpp"
#include <memory>

struct AttackData {
public:

    phx::Vector3f offset;
    float padding;
    phx::Vector3f offset2;
    float padding2;

    float power;
    float size;
    float angle;
    int32_t r_eff;
    int32_t r_fix;
    int32_t r_add;
    float slip;
    float stop_frame;
    float stop_delay;
    phx::Hash40 node;
    uint16_t target_category;
    uint8_t target_situation;
    bool target_lr;
    uint8_t target_part;
    phx::Hash40 attribute;
    uint8_t sound_level;
    uint8_t sound_attr;
    uint8_t set_off;
    bool no_scale;
    bool shield;
    bool reflector;
    bool absorber;
    bool direct;
    bool no_invincible;
    bool no_xlu;
    uint8_t lr_check;
    bool catch_;
    bool no_team;
    bool no_stop;
    bool no_effect;
    uint8_t unused;
    bool speed;
    uint8_t region;
    bool ignore_down;
    uint8_t check_type; // 0x0 for sphere, 0x2 for capsule
    uint16_t sub_shield;
    uint8_t camera_quake;
    int32_t serial_hit_frame;
    bool force_reaction;
    bool no_attacker_log;
    uint8_t no_weight_reaction;
    uint8_t no_reaction_search;
    bool keep_rumble;
    bool composition_speed;
    phx::Hash40 target_pos_node;
    phx::Vector2f target_pos_offset;
    uint64_t padding3;
    int32_t target_pos_frame;
    bool r_fix_damage_speed_up;
    uint8_t unused2;
    bool captured_same_time_attack;
    uint8_t unknown[0x59];

    bool IsCapsule() const {
        return check_type == 0x2;
    }
};

static_assert(sizeof(AttackData) == 0x100);
static_assert(offsetof(AttackData, offset)                    == 0x0);
static_assert(offsetof(AttackData, offset2)                   == 0x10);
static_assert(offsetof(AttackData, power)                     == 0x20);
static_assert(offsetof(AttackData, size)                      == 0x24);
static_assert(offsetof(AttackData, angle)                     == 0x28);
static_assert(offsetof(AttackData, r_eff)                     == 0x2C);
static_assert(offsetof(AttackData, r_fix)                     == 0x30);
static_assert(offsetof(AttackData, r_add)                     == 0x34);
static_assert(offsetof(AttackData, slip)                      == 0x38);
static_assert(offsetof(AttackData, stop_frame)                == 0x3C);
static_assert(offsetof(AttackData, stop_delay)                == 0x40);
static_assert(offsetof(AttackData, node)                      == 0x48);
static_assert(offsetof(AttackData, target_category)           == 0x50);
static_assert(offsetof(AttackData, target_situation)          == 0x52);
static_assert(offsetof(AttackData, target_lr)                 == 0x53);
static_assert(offsetof(AttackData, target_part)               == 0x54);
static_assert(offsetof(AttackData, attribute)                 == 0x58);
static_assert(offsetof(AttackData, sound_level)               == 0x60);
static_assert(offsetof(AttackData, sound_attr)                == 0x61);
static_assert(offsetof(AttackData, set_off)                   == 0x62);
static_assert(offsetof(AttackData, no_scale)                  == 0x63);
static_assert(offsetof(AttackData, shield)                    == 0x64);
static_assert(offsetof(AttackData, reflector)                 == 0x65);
static_assert(offsetof(AttackData, absorber)                  == 0x66);
static_assert(offsetof(AttackData, direct)                    == 0x67);
static_assert(offsetof(AttackData, no_invincible)             == 0x68);
static_assert(offsetof(AttackData, no_xlu)                    == 0x69);
static_assert(offsetof(AttackData, lr_check)                  == 0x6A);
static_assert(offsetof(AttackData, catch_)                    == 0x6B);
static_assert(offsetof(AttackData, no_team)                   == 0x6C);
static_assert(offsetof(AttackData, no_stop)                   == 0x6D);
static_assert(offsetof(AttackData, no_effect)                 == 0x6E);
static_assert(offsetof(AttackData, speed)                     == 0x70);
static_assert(offsetof(AttackData, region)                    == 0x71);
static_assert(offsetof(AttackData, ignore_down)               == 0x72);
static_assert(offsetof(AttackData, check_type)                == 0x73);
static_assert(offsetof(AttackData, sub_shield)                == 0x74);
static_assert(offsetof(AttackData, camera_quake)              == 0x76);
static_assert(offsetof(AttackData, serial_hit_frame)          == 0x78);
static_assert(offsetof(AttackData, force_reaction)            == 0x7C);
static_assert(offsetof(AttackData, no_attacker_log)           == 0x7D);
static_assert(offsetof(AttackData, no_weight_reaction)        == 0x7E);
static_assert(offsetof(AttackData, no_reaction_search)        == 0x7F);
static_assert(offsetof(AttackData, keep_rumble)               == 0x80);
static_assert(offsetof(AttackData, composition_speed)         == 0x81);
static_assert(offsetof(AttackData, target_pos_node)           == 0x88);
static_assert(offsetof(AttackData, target_pos_offset)         == 0x90);
static_assert(offsetof(AttackData, target_pos_frame)          == 0xA0);
static_assert(offsetof(AttackData, r_fix_damage_speed_up)     == 0xA4);
static_assert(offsetof(AttackData, captured_same_time_attack) == 0xA6);

class Hitbox : public Drawable {
public:
    static const size_t MAX_HITBOX_VERTICES = 0x100;

    Hitbox(nvn::Device* device, app::BattleObjectModuleAccessor* owner, int hitbox_id);
    ~Hitbox() = default;

    Hitbox(const Hitbox&) = delete;
    Hitbox(Hitbox&&) = delete;

    Hitbox& operator=(const Hitbox&) = delete;
    Hitbox& operator=(Hitbox&&) = delete;

    virtual void Draw(nvn::CommandBuffer* buffer) override;
    virtual void Update(nvn::CommandBuffer* buffer) override;

private:
    int id;
    Sha256Hash current_data_hash;
    std::optional<AttackData> current_data;
    bool is_interpolated;

    app::BattleObjectModuleAccessor* owner;
    std::shared_ptr<ShaderProgram> shader;
    VertexBuffer<phx::Vector2f> vertices;
};

void install_hitbox_hooks();