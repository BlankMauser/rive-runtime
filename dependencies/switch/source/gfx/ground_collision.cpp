#include "gfx/ground_collision.hpp"
#include "gfx/res/simple_2d.h"
#define COORDS
#include "environment.hpp"

#include "nn/os.hpp"
#include "skyline/inlinehook/And64InlineHook.hpp"

#include "vector_math.hpp"

#define B2S(b) ((b) == true ? "true" : "false")

const phx::Vector4f RHOMBUS_COLOR = {232.0f / 255.0f, 113.0f / 255.0f, 23.0f / 255.0f, 0.75f};
const phx::Vector4f OUTLINE_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};
const phx::Vector4f CLIFF_COLOR = {221.0f / 255.0f, 34.0f / 255.0f, 144.0f / 255.0f, 1.0f};
const phx::Vector4f CLIFF_BACK_COLOR = {0.0f, 0.0f, 1.0f, 1.0f};
const phx::Vector4f CLIFF_FRONT_COLOR = {1.0f, 0.0f, 0.0f, 1.0f};

struct GroundTouch
{
    void *line;
    uint64_t _x8;
    phx::Vector2f touch_pos;
    uint64_t _x18[3];
};

// 0x6E0
struct GroundCollisionObject
{
    char _x0[0x10];
    GroundTouch touch[8];
    GroundTouch prev_touch[8];
    char _x310[0x8C];
    int mode;
    char _x3A0[0x20];
    phx::Vector4f top_shift;
    phx::Vector4f bottom_shift;
    phx::Vector4f left_shift;
    phx::Vector4f right_shift;
    char _x400[0xC0];
    phx::Vector4f pos;
    char _x4D0[0x38];
    float lr;
    char _x50C[0x14];
    phx::Vector4f cliff_grab_center;
    phx::Vector4f cliff_grab_front;
    phx::Vector4f cliff_grab_back;
    char _x540[0x175];
    bool is_active;
    bool _x6C6;
    bool _x6C7;
    bool _x6C8;
    bool _x6C9;
    bool _x6CA;

    void GetRhombus(phx::Vector2f *tblr) const
    {
        tblr[0] = {pos.x + top_shift.x, pos.y + top_shift.y};
        tblr[1] = {pos.x + bottom_shift.x, pos.y + bottom_shift.y};
        tblr[2] = {pos.x + left_shift.x, pos.y + left_shift.y};
        tblr[3] = {pos.x + right_shift.x, pos.y + right_shift.y};
    }

    void GetFrontLedgeGrab(phx::Vector2f *bl_tr) const
    {
        if (lr >= 0.0f)
        {
            phx::Vector2f center = {cliff_grab_center.x + pos.x, cliff_grab_center.y + pos.y};
            bl_tr[0] = {center.x, center.y};
            bl_tr[1] = {cliff_grab_front.x + center.x, cliff_grab_front.y + center.y};
        }
        else
        {
            phx::Vector2f center = {-cliff_grab_center.x + pos.x, cliff_grab_center.y + pos.y};
            bl_tr[0] = {-cliff_grab_front.x + center.x, center.y};
            bl_tr[1] = {center.x, cliff_grab_front.y + center.y};
        }
    }

    void GetBackLedgeGrab(phx::Vector2f *bl_tr) const
    {
        if (lr >= 0.0f)
        {
            phx::Vector2f center = {cliff_grab_center.x + pos.x, cliff_grab_center.y + pos.y};
            bl_tr[0] = {-cliff_grab_back.x + center.x, center.y};
            bl_tr[1] = {center.x, cliff_grab_back.y + center.y};
        }
        else
        {
            phx::Vector2f center = {-cliff_grab_center.x + pos.x, cliff_grab_center.y + pos.y};
            bl_tr[0] = {center.x, center.y};
            bl_tr[1] = {cliff_grab_back.x + center.x, cliff_grab_back.y + center.y};
        }
    }
};
struct GroundCollisionVertex;
struct GroundCollisionLine;

struct GroundCollisionCliffData
{
    GroundCollisionCliffData *next;
    GroundCollisionCliffData *prev;
    GroundCollisionVertex *vertex;
    GroundCollisionLine *line;
    // ...
};

struct GroundCollisionCliff
{
    GroundCollisionCliff *next;
    GroundCollisionCliff *prev;
    GroundCollisionCliffData data;
};

struct GroundCollisionVertex
{
    GroundCollisionVertex *next;
    GroundCollisionVertex *prev;
    phx::Vector4f pos;
    phx::Vector4f pos_;
    phx::Vector4f pos__;
    phx::Vector4f pos___;
};

struct GroundCollisionLineGroup
{
    GroundCollisionLineGroup *next;
    GroundCollisionLineGroup *prev;
    uint64_t _x10;
    void *_x18;
    phx::Vector4f bottom_left;
    phx::Vector4f top_right;
    phx::Vector4f bottom_left_;
    phx::Vector4f top_right_;
    size_t vertex_count;
    GroundCollisionVertex *vertex_start;
    GroundCollisionVertex *vertex_end;
    size_t line_count;
    GroundCollisionLine *line_start;
    GroundCollisionLine *line_end;
    size_t cliff_count;
    void **cliff_start;
    void **cliff_end;
    uint64_t _xA8[7];
    bool is_enabled;
};

struct GroundCollisionLine
{
    GroundCollisionLine *next;
    GroundCollisionLine *prev;
    uint64_t _x10[2];
    phx::Vector2f bottom_left;
    uint64_t _x28;
    phx::Vector2f top_right;
    uint64_t _x38[10];
    GroundCollisionVertex *vertex_1;
    GroundCollisionVertex *vertex_2;
};

struct GroundCollision
{
    char _x0[0x30];
    void *_x30[0x20];
    char _x130[0x28];
    std::vector<GroundCollisionLine *> lines;
    std::vector<GroundCollisionCliff *> cliffs;
    std::vector<GroundCollisionLineGroup *> groups;
    char _x1A0[0xA0];
    std::vector<GroundCollisionObject *> collision_objects;

    static GroundCollision *Instance()
    {
        return *(GroundCollision **)(skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x52b7298);
    }
};

static_assert(offsetof(GroundCollision, groups) == 0x188);
static_assert(offsetof(GroundCollision, collision_objects) == 0x240);
static_assert(offsetof(GroundCollisionObject, _x6CA) == 0x6CA);

static void (*GroundCollision__collide__orig)(GroundCollision *);

void GroundCollision__update_graphics(GroundCollision *collision)
{
    for (int i = 0; i < 2; i++)
    {
        for (const auto *ptr : collision->groups)
        {
            auto &instance = GroundCollisionManager::Instance();
            if (!ptr->is_enabled)
                continue;

            auto *current = ptr->line_start;
            while (current != reinterpret_cast<const GroundCollisionLine *>(&ptr->line_start))
            {
                size_t v_len = instance.vertex_buffer[instance.buffer_in_use].Length();
                instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({current->vertex_1->pos.x, current->vertex_1->pos.y, 0.0f}));
                instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({current->vertex_2->pos.x, current->vertex_2->pos.y, 0.0f}));

                size_t i_base = instance.index_buffer[instance.buffer_in_use].Length();

                instance.index_buffer[instance.buffer_in_use].SafePush(v_len);
                instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 1);

                for (const auto *cliff : collision->cliffs)
                {
                    if (cliff->data.vertex == current->vertex_1 || cliff->data.vertex == current->vertex_2)
                    {
                        if (i == 1)
                        {
                            instance.draw_infos[instance.buffer_in_use].push_back(GroundCollisionManager::DrawInfo{static_cast<int>(i_base), 2, nvn::DrawPrimitive::LINES, CLIFF_COLOR});
                            goto repeat;
                        }
                    }
                }

                if (i == 1)
                {
                    instance.draw_infos[instance.buffer_in_use].push_back(GroundCollisionManager::DrawInfo{static_cast<int>(i_base), 2, nvn::DrawPrimitive::LINES, OUTLINE_COLOR});
                }
                else
                {
                    instance.draw_infos[instance.buffer_in_use].push_back(GroundCollisionManager::DrawInfo{static_cast<int>(i_base), 2, nvn::DrawPrimitive::LINES, phx::Vector4f{0.0f, 0.0f, 0.0f, 1.0f}, {7.0f}});
                }

            repeat:
                current = current->next;
            }
        }
    }

    for (const auto *ptr : collision->collision_objects)
    {
        if (!ptr->is_active || !ptr->_x6C9)
            continue;

        auto &instance = GroundCollisionManager::Instance();
        size_t v_len = instance.vertex_buffer[instance.buffer_in_use].Length();
        size_t i_base = instance.index_buffer[instance.buffer_in_use].Length();
        if (!g_DrawSettings.ecb)
            goto ledge_grab_graphics;

        phx::Vector2f tblr[4];
        ptr->GetRhombus(tblr);

        // calculate top/bottom/left/right vertices
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({tblr[0].x, tblr[0].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({tblr[1].x, tblr[1].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({tblr[2].x, tblr[2].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({tblr[3].x, tblr[3].y, 0.0f}));

        instance.index_buffer[instance.buffer_in_use].SafePush(v_len);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 3);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 1);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 1);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 2);

        instance.index_buffer[instance.buffer_in_use].SafePush(v_len);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 2);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 1);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 3);

        instance.draw_infos[instance.buffer_in_use].push_back(GroundCollisionManager::DrawInfo{static_cast<int>(i_base), 6, nvn::DrawPrimitive::TRIANGLES, RHOMBUS_COLOR});
        instance.draw_infos[instance.buffer_in_use].push_back(GroundCollisionManager::DrawInfo{static_cast<int>(i_base + 6), 4, nvn::DrawPrimitive::LINE_LOOP, OUTLINE_COLOR});

    ledge_grab_graphics:
        if (!g_DrawSettings.ledge_grab)
            continue;

        phx::Vector2f cliff_hang_back[2];
        phx::Vector2f cliff_hang_front[2];

        ptr->GetBackLedgeGrab(cliff_hang_back);
        ptr->GetFrontLedgeGrab(cliff_hang_front);

        v_len = instance.vertex_buffer[instance.buffer_in_use].Length();
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_back[0].x, cliff_hang_back[0].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_back[0].x, cliff_hang_back[1].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_back[1].x, cliff_hang_back[1].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_back[1].x, cliff_hang_back[0].y, 0.0f}));

        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_front[0].x, cliff_hang_front[0].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_front[0].x, cliff_hang_front[1].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_front[1].x, cliff_hang_front[1].y, 0.0f}));
        instance.vertex_buffer[instance.buffer_in_use].SafePush(as_screen_coords({cliff_hang_front[1].x, cliff_hang_front[0].y, 0.0f}));

        i_base = instance.index_buffer[instance.buffer_in_use].Length();

        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 0);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 1);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 2);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 3);

        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 4);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 5);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 6);
        instance.index_buffer[instance.buffer_in_use].SafePush(v_len + 7);

        instance.draw_infos[instance.buffer_in_use].push_back(GroundCollisionManager::DrawInfo{static_cast<int>(i_base), 4, nvn::DrawPrimitive::LINE_LOOP, CLIFF_BACK_COLOR});
        instance.draw_infos[instance.buffer_in_use].push_back(GroundCollisionManager::DrawInfo{static_cast<int>(i_base + 4), 4, nvn::DrawPrimitive::LINE_LOOP, CLIFF_FRONT_COLOR});
    }
}

void GroundCollision__collide(GroundCollision *collision)
{
    GroundCollision__collide__orig(collision);
    GroundCollision__update_graphics(collision);
}

GroundCollisionManager::GroundCollisionManager()
    : vertex_buffer{VertexBuffer<phx::Vector2f>(g_Device, 0x300), VertexBuffer<phx::Vector2f>(g_Device, 0x300), VertexBuffer<phx::Vector2f>(g_Device, 0x300)},
      index_buffer{IndexBuffer<unsigned short>(g_Device, 0xC00), IndexBuffer<unsigned short>(g_Device, 0xC00), IndexBuffer<unsigned short>(g_Device, 0xC00)},
      color_buffer{UniformBuffer<phx::Vector4f>(g_Device, 3)},
      shaders(),
      blend_state(),
      channel_mask_state(),
      color_state(),
      multisample_state(),
      polygon_state(),
      vertex_attrib_state(1),
      vertex_stream_state(1),
      draw_infos()
{
    for (size_t i = 0; i < 3; i++)
    {
        vertex_buffer[i].SetId(0);
    }

    color_buffer.SetId(0);
    color_buffer.SetStage(nvn::ShaderStage::FRAGMENT);
    color_buffer.SetIndex(0);

    shaders[ShaderStage::Vertex] = ShaderProgram::DataSet(simple_2d::get_vertex_code_bin(), simple_2d::get_vertex_control_bin());
    shaders[ShaderStage::Fragment] = ShaderProgram::DataSet(simple_2d::get_fragment_code_bin(), simple_2d::get_fragment_control_bin());

    SL_ASSERTM(shaders.Initialize(g_Device), "failed to initialize shaders");

    blend_state->SetBlendTarget(0)
        .SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD)
        .SetBlendFunc(nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ZERO, nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ZERO);

    color_state->SetBlendEnable(0, true)
        .SetLogicOp(nvn::LogicOp::COPY);

    polygon_state->SetCullFace(nvn::Face::NONE)
        .SetFrontFace(nvn::FrontFace::CCW)
        .SetPolygonMode(nvn::PolygonMode::FILL);

    vertex_attrib_state[0].SetFormat(nvn::Format::RG32F, 0).SetStreamIndex(0);

    vertex_stream_state[0].SetStride(sizeof(phx::Vector2f));
}

GroundCollisionManager &GroundCollisionManager::Instance()
{
    static GroundCollisionManager instance;
    return instance;
}

void GroundCollisionManager::InstallHooks()
{
    const uint64_t text = reinterpret_cast<uint64_t>(skyline::utils::getRegionAddress(skyline::utils::region::Text));
    A64HookFunction(
        reinterpret_cast<void *>(text + 0x523a60),
        reinterpret_cast<void *>(GroundCollision__collide),
        reinterpret_cast<void **>(&GroundCollision__collide__orig));
}

void GroundCollisionManager::Render(nvn::CommandBuffer *cmdbuf)
{
    if (!sl_is_match_active())
        return;
    if (g_IsCameraUpdateOnly)
    {
        GroundCollision__update_graphics(GroundCollision::Instance());
    }

    auto &instance = Instance();
    instance.shaders.Bind(cmdbuf);
    instance.color_buffer.Bind(cmdbuf);
    instance.blend_state.Bind(cmdbuf);
    instance.channel_mask_state.Bind(cmdbuf);
    instance.color_state.Bind(cmdbuf);
    instance.multisample_state.Bind(cmdbuf);
    instance.polygon_state.Bind(cmdbuf);
    instance.vertex_attrib_state.Bind(cmdbuf);
    instance.vertex_stream_state.Bind(cmdbuf);

    auto current_buffer = (instance.buffer_in_use) % 3;
    auto draw_buffer = (current_buffer + 2) % 3;

    instance.vertex_buffer[draw_buffer].Bind(cmdbuf);

    cmdbuf->SetLineWidth(3.0f);

    for (const auto &info : instance.draw_infos[draw_buffer])
    {
        if (info.line_width.has_value())
        {
            cmdbuf->SetLineWidth(info.line_width.value());
        }
        else
        {
            cmdbuf->SetLineWidth(3.0f);
        }
        instance.color_buffer.Update(cmdbuf, &info.color);
        instance.index_buffer[draw_buffer].SetSubArray(info.index_start, info.len);
        instance.index_buffer[draw_buffer].SetPrimitive(info.primitive);
        instance.index_buffer[draw_buffer].Draw(cmdbuf);
    }

    instance.buffer_in_use = (instance.buffer_in_use + 1) % 3;
    instance.index_buffer[draw_buffer].Clear();
    instance.vertex_buffer[draw_buffer].Clear();
    instance.color_buffer.SetIndex(draw_buffer);
    instance.draw_infos[draw_buffer].clear();
}

bool sl_is_match_active()
{
    return GroundCollision::Instance() != nullptr;
}