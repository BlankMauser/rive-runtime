#include "gfx/hitbox.hpp"
#include "gfx/res/hb_shaders.h"
#include "utils.hpp"
// using namespace app::lua_bind;

struct AttackDataEx {
public:
    AttackData base;
    void* unknown;
    int is_active;
    u8 unknown2[0x24];
};

static_assert(sizeof(AttackDataEx) == 0x130);
static_assert(offsetof(AttackDataEx, base) == 0x0);
static_assert(offsetof(AttackDataEx, unknown) == 0x100);
static_assert(offsetof(AttackDataEx, is_active) == 0x108);

class AttackModule {
public:
    void** vtable;
    app::BattleObjectModuleAccessor* owner;
    u64 _x10;
    u64 _x18;
    u64 _x20;
    u64 _x28;
    u64 _x30;
    u64 _x38;
    u64 _x40;
    u64 _x48;
    u64 _x50;
    u64 _x58;
    u64 _x60;
    AttackDataEx* attack_datas;
    u64 _x70[0x39];
    bool is_not_attacking;

    bool IsAttack(int id, bool is_abs) {
        if (is_abs) {
            debug_log("AttackModule::IsAttack is not implemented for absolute hitboxes");
            return false;
        }

        return attack_datas[id].is_active && !is_not_attacking;
    }

    AttackData* AttackData(int id, bool is_abs) {
        if (is_abs) {
            debug_log("AttackModule::AttackData is not implemented for absolute hitboxes");
            return nullptr;
        }

        return &attack_datas[id].base;
    }

    static inline AttackModule* Get(app::BattleObjectModuleAccessor* boma) {
        return *reinterpret_cast<AttackModule**>(reinterpret_cast<u64>(boma) + 0xA0);
    }
};

static_assert(offsetof(AttackModule, attack_datas) == 0x68);
static_assert(offsetof(AttackModule, is_not_attacking) == 0x238);

ShaderProgram* CreateHitboxShaders(nvn::Device* device) {
    ShaderProgram* program = new ShaderProgram;

    (*program)[ShaderStage::Fragment] = ShaderProgram::DataSet(get_fragment_code(), get_fragment_control());
    (*program)[ShaderStage::Vertex] = ShaderProgram::DataSet(get_vertex_code(), get_vertex_control());

    SL_ASSERTM(program->Initialize(device), "Hitbox shaders failed to initialize");

    return program;
}

std::shared_ptr<ShaderProgram> GetHitboxShaders(nvn::Device* device) {
    static std::shared_ptr<ShaderProgram> SHADERS = std::shared_ptr<ShaderProgram>(CreateHitboxShaders(device));
    return std::shared_ptr<ShaderProgram>(SHADERS);
}

Hitbox::Hitbox(nvn::Device* device, app::BattleObjectModuleAccessor* owner, int hitbox_id) : id(hitbox_id), owner(owner), vertices(device, Hitbox::MAX_HITBOX_VERTICES), shader(nullptr) {
    shader = GetHitboxShaders(device);
}

void Hitbox::Draw(nvn::CommandBuffer* buffer) {
    AttackModule* mod = AttackModule::Get(owner);

    if (!mod->IsAttack(id, false))
        return;

    debug_log("Hitbox::Draw is unimplemented");
}

void Hitbox::Update(nvn::CommandBuffer* buffer) {
    AttackModule* mod = AttackModule::Get(owner);

    if (!mod->IsAttack(id, false)) {
        current_data = {};
        is_interpolated = false;
        return;
    }

    Sha256Hash current_hash;
    auto* data = mod->AttackData(id, false);
    hash_bytes(data, sizeof(AttackData), &current_hash);
    if (current_hash == current_data_hash) {
        debug_log("[Hitbox::Update] Hitbox data has not changed since last update");
        return;
    }

    debug_log("[Hitbox::Update] Hitbox data has changed since last update");

    vertices.Clear();
    if (data->IsCapsule()) {

    } else {

    }
}

static uint8_t ATTACKMODULE_CLEAR_SEARCH_CODE[] = {
    0x08, 0x34, 0x40, 0xf9, // ldr x8, [x0, #0x68]
    0x09, 0x26, 0x80, 0x52, // mov w9, #0x130
    0x2a, 0x20, 0x29, 0x9b, // smaddl x10, w1, w9, x8
    0x49, 0x09, 0x41, 0xb9  // ldr w9, [x10, #0x108]
};

static uint8_t ATTACKMODULE_SET_ATTACK_SEARCH_CODE[] = {
    0xfb, 0x0f, 0x1a, 0xf8, // str x27, [sp, #-0x60]!
    0xfa, 0x67, 0x01, 0xa9, // stp x26, x25, [sp, #0x10]
    0xf8, 0x5f, 0x02, 0xa9, // stp x24, x23, [sp, #0x20]
    0xf6, 0x57, 0x03, 0xa9, // stp x22, x21, [sp, #0x30]
    0xf4, 0x4f, 0x04, 0xa9, // stp x20, x19, [sp, #0x40]
    0xfd, 0x7b, 0x05, 0xa9, // stp x29, x30, [sp, #0x50]
    0xfd, 0x43, 0x01, 0x91, // add x29, sp, #0x50
    0x19, 0x34, 0x40, 0xf9, // ldr x25, [x0, #0x68]
    0x08, 0x26, 0x80, 0x52  // mov w8, #0x130
};

void install_hitbox_hooks() {
    void* clear = byte_search(ATTACKMODULE_CLEAR_SEARCH_CODE, sizeof(ATTACKMODULE_CLEAR_SEARCH_CODE));
    void* set_attack = byte_search(ATTACKMODULE_SET_ATTACK_SEARCH_CODE, sizeof(ATTACKMODULE_SET_ATTACK_SEARCH_CODE));

    debug_log("%p %p", clear, set_attack);
}