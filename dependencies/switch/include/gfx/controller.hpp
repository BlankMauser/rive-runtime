#pragma once
#include "drawable.hpp"
#include "vbuffer.hpp"
#include "ibuffer.hpp"
#include "ubuffer.hpp"
#include "image.hpp"
#include "tmanager.hpp"
#include "shader.hpp"
#include "basic_bindables.hpp"

#include "smash.hpp"
#include "nn/hid.hpp"

struct SmashControllerButtons {
    uint32_t attack      : 1;
    uint32_t special     : 1;
    uint32_t jump        : 1;
    uint32_t guard       : 1;
    uint32_t catch_      : 1;
    uint32_t smash       : 1;
    uint32_t jump_mini   : 1;
    uint32_t c_stick_on  : 1;
    uint32_t stock_share : 1;
    uint32_t attack_raw  : 1;
    uint32_t appeal_hi   : 1;
    uint32_t special_raw : 1;
    uint32_t appeal_lw   : 1;
    uint32_t appeal_s_l  : 1;
    uint32_t appeal_s_r  : 1;
    uint32_t flick_jump  : 1;
    uint32_t guard_hold  : 1;
    uint32_t special_raw2  : 1;
    uint32_t unused : 14;
    signed char lstick_x;
    signed char lstick_y;
    signed char rstick_x;
    signed char rstick_y;
};

static_assert(sizeof(SmashControllerButtons) == 0x8);
static_assert(offsetof(SmashControllerButtons, lstick_x) == 0x4);

class Controller : public Drawable {
public:
    Controller(uint32_t npad_id);

    inline void SetFromWidth(float width) {
        this->width = width;
        this->height = -1.0f;
    }

    inline void SetFromHeight(float height) {
        this->height = height;
        this->width = -1.0f;
    }

    inline void SetPos(float x, float y) {
        if (!std::isnan(x)) this->x = x;
        if (!std::isnan(y)) this->y = y;
    }

    inline void Dimensions(float* w, float* h) const {
        if (w) *w = width;
        if (h) *h = height;
    }

    inline void Pos(float* x, float* y) const {
        if (x) *x = this->x;
        if (y) *y = this->y;
    }

    inline void SetNpadId(uint32_t id) {
        npad_id = id;
    }

    virtual void Draw(nvn::CommandBuffer* cmdbuf) override;

protected:
    VertexBuffer<phx::Vector2f> vertex_buffer[3];
    VertexBuffer<phx::Vector2f> tcoord_buffer[3];
    VertexBuffer<phx::Vector2f> mcoord_buffer[3];
    IndexBuffer<unsigned short> index_buffer[3];
    UniformBuffer<int> draw_mode;
    std::shared_ptr<Image> image;
    ShaderProgram shaders;
    BlendState blend_state;
    ChannelMaskState channel_mask_state;
    ColorState color_state;
    MultisampleState multisample_state;
    PolygonState polygon_state;
    VertexAttribState vertex_attrib_state;
    VertexStreamState vertex_stream_state;

    uint32_t npad_id;
    float width;
    float height;
    float x;
    float y;
    
    size_t buffer_in_use;
};

class GamecubeController : public Controller {
public:
    GamecubeController(uint32_t npad_id);

    virtual void Update(nvn::CommandBuffer* cmdbuf) override;
};

class ProController : public Controller {
public:
    ProController(uint32_t npad_id);

    virtual void Update(nvn::CommandBuffer* cmdbuf) override;
};

class SmashController : public Controller {
public:
    SmashControllerButtons buttons;

    SmashController(uint32_t player_id);

    virtual void Update(nvn::CommandBuffer* cmdbuf) override;

};

class InputManager {
private:
    InputManager();

    static InputManager& Instance();
public:
    static void Update(nvn::CommandBuffer* cmdbuf);
    static void Render(nvn::CommandBuffer* cmdbuf);

    static void InstallHooks();

    static SmashController* GetSmashController(size_t player_id);

private:
    Controller* active;
    GamecubeController gc_controller;
    ProController pro_controller;
    SmashController smash_controllers[2];
};