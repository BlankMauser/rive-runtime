#pragma once

#include "vbuffer.hpp"
#include "ibuffer.hpp"
#include "ubuffer.hpp"
#include "smash.hpp"
#include "shader.hpp"
#include "basic_bindables.hpp"

struct CollisionData;

struct CollisionTransactor {
    char _x0[0x8];
    uint start;
    uint count;
    void** vec_vtable;
    size_t capacity;
    size_t length;
    CollisionData** array;
    CollisionData* datas[64];
    char _x230[0xa0];
};

static_assert(sizeof(CollisionTransactor) == 0x2d0);

struct CollisionObject {
    char _x0[0x10];
    size_t num_transactors;
    CollisionTransactor* transactors;
    int active_transactors;
    int collision_kind;
    uint32_t battle_object_id;
    uint32_t battle_object_category;
    void* hit_team_info;
    bool is_active;
    bool no_team;
    bool ignore_glancing_blow;
    bool _x3b;
    uint _x3c;
};

struct CollisionData {
    void** vtable;
    uint32_t flags;
    uint32_t flags2;
    phx::Vector3f position_;
    float _x1C;
    uint64_t _x20;
    void* _x28;
    void* _x30;
    uint64_t _x38;
    phx::Vector3f bottom_left;
    float _x4C;
    phx::Vector3f top_right;
    float _x5C;
    phx::Vector3f collision_location;
    float _x6C;
    float collision_overlap;
    float _x74;
    float _x78;
    float _x7C;
    int collision_shape;
    bool is_active;
    char _x86[10];
    phx::Vector3f position;
    float _x9C;
    float radius;
    float _xA4;
    float _xA8;
    float _xAC;
    phx::Vector3f position2_relative;
    float _xBC;
    phx::Vector3f x_axis;
    float _xCC;
    phx::Vector3f y_axis;
    float _xDC;
    phx::Vector3f z_axis;
    float _xEC;
    phx::Vector3f bone_pos;
    float _xFC;
    phx::Vector3f scale;
};

struct CollisionManager {
    std::vector<CollisionObject*> objects[7];
    std::vector<CollisionData*> datas[3];
};
static_assert(offsetof(CollisionManager, datas) == 0xa8);

void install_collision_hooks();
void collision_render();

// struct CollisionManager;

// class CollidableObjectManager {
// private:
//     struct DrawInfo {
//         int index_start;
//         int len;
//         nvn::DrawPrimitive primitive;
//         phx::Vector4f color;
//     };


//     CollidableObjectManager();

//     static CollidableObjectManager& Instance();

//     friend void CollisionManager__collide(CollisionManager*);
// public:
//     static void InstallHooks();

//     static void Render(nvn::CommandBuffer* cmdbuf);

// private:
//     VertexBuffer<phx::Vector2f> vertex_buffer[3];
//     IndexBuffer<unsigned short> index_buffer[3];
//     UniformBuffer<phx::Vector4f> color_buffer;
//     ShaderProgram shaders;
//     BlendState blend_state;
//     ChannelMaskState channel_mask_state;
//     ColorState color_state;
//     MultisampleState multisample_state;
//     PolygonState polygon_state;
//     VertexAttribState vertex_attrib_state;
//     VertexStreamState vertex_stream_state;
//     int buffer_in_use;

//     std::vector<DrawInfo> draw_infos[3];
// };