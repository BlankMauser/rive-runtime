#include "gfx/collision.hpp"
#include "gfx/res/simple_2d.h"
#include "vector_math.hpp"
#include "environment.hpp"
#include "skyline/inlinehook/And64InlineHook.hpp"
#include "gfx/shape_renderer.hpp"

void (*CollisionLogManager_collide_orig)(CollisionManager *) = nullptr;

void CollisionLogManager_collide(CollisionManager *manager)
{
    CollisionLogManager_collide_orig(manager);
    for (auto *object : manager->objects[0])
    {
        for (int i = 0; i < object->active_transactors; i++)
        {
            auto *trans = object->transactors + i;
            for (int j = trans->start; j < (trans->start + trans->count); j++)
            {
                auto *data = trans->datas[j];
                if (data == nullptr || !data->is_active)
                    continue;
                phx::Vector2f bottom_left = as_pixels(data->bottom_left);
                phx::Vector2f top_right = as_pixels(data->top_right);

                ShapeRenderer::DrawRectangle({bottom_left.x, top_right.y}, top_right.x - bottom_left.x, bottom_left.y - top_right.y, {1.0f, 0.0f, 0.0f, 0.6f});
            }
        }
    }
}

static phx::Vector4f HITBOX_COLORS[8] = {
    phx::Vector4f{239.0 / 255.0, 100.0 / 255.0, 0.0 / 255.0, 0.70},
    phx::Vector4f{255.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0, 0.70},
    phx::Vector4f{255.0 / 255.0, 0.0 / 255.0, 255.0 / 255.0, 0.70},
    phx::Vector4f{24.0 / 255.0, 214.0 / 255.0, 201.0 / 255.0, 0.70},
    phx::Vector4f{36.0 / 255.0, 214.0 / 255.0, 24.0 / 255.0, 0.70},
    phx::Vector4f{102.0 / 255.0, 102.0 / 255.0, 255.0 / 255.0, 0.70},
    phx::Vector4f{0.0 / 255.0, 128.0 / 255.0, 128.0 / 255.0, 0.70},
    phx::Vector4f{205.0 / 255.0, 196.0 / 255.0, 78.0 / 255.0, 0.70}};

static phx::Vector4f BASIC_COLOR = {0.5f, 1.0f, 0.7f, 0.55f};

void collision_render()
{
    CollisionManager *manager = *reinterpret_cast<CollisionManager **>(skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x52b65f8);
    if (manager == nullptr)
        return;

    for (int box = 6; box >= 0; box--)
    {
        auto& object_set = manager->objects[box];
        if ((box == 1) && !g_DrawSettings.hurtboxes)
            continue;
        for (auto *object : object_set)
        {
            for (int i = object->active_transactors - 1; i >= 0; i--)
            {
                auto *trans = object->transactors + i;
                for (int j = trans->start + trans->count - 1; j >= (int)trans->start; j--)
                {
                    auto *data = trans->datas[j];
                    if (data == nullptr || !data->is_active)
                        continue;

                    if (data->collision_shape == 0)
                    {
                        if (data->position2_relative == phx::Vector3f{0.0f, 0.0f, 0.0f})
                        {
                            ShapeRenderer::DrawSphere(data->position, {1.0f, 1.0f, 1.0f}, data->radius, (box == 0) ? HITBOX_COLORS[j % 8] : BASIC_COLOR);
                        }
                        else
                        {
                            ShapeRenderer::DrawCapsule2(data->position, data->position + data->position2_relative, {1.0f, 1.0f, 1.0f}, data->radius, (box == 0) ? HITBOX_COLORS[j % 8] : BASIC_COLOR, {});
                        }
                    }
                    else if (data->collision_shape == 2)
                    {
                        ShapeRenderer::DrawCapsule2(data->position, data->position + data->position2_relative, data->scale, data->radius, (box == 0) ? HITBOX_COLORS[j % 8] : BASIC_COLOR, {ShapeRenderer::ScaleMatrix{data->x_axis, data->y_axis, data->z_axis}});
                    }
                }
            }
        }
    }
}

void install_collision_hooks()
{
    // A64HookFunction(
    //     skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x3e8150,
    //     reinterpret_cast<void*>(CollisionLogManager_collide),
    //     reinterpret_cast<void**>(&CollisionLogManager_collide_orig)
    // );
}

// CollidableObjectManager::CollidableObjectManager()
//     : vertex_buffer { VertexBuffer<phx::Vector2f>(g_Device, 0x300), VertexBuffer<phx::Vector2f>(g_Device, 0x300), VertexBuffer<phx::Vector2f>(g_Device, 0x300) },
//         index_buffer { IndexBuffer<unsigned short>(g_Device, 0xC00), IndexBuffer<unsigned short>(g_Device, 0xC00), IndexBuffer<unsigned short>(g_Device, 0xC00) },
//         color_buffer { UniformBuffer<phx::Vector4f>(g_Device, 3) },
//         shaders(),
//         blend_state(),
//         channel_mask_state(),
//         color_state(),
//         multisample_state(),
//         polygon_state(),
//         vertex_attrib_state(1),
//         vertex_stream_state(1),
//         draw_infos()
// {
//     for (size_t i = 0; i < 3; i++) {
//         vertex_buffer[i].SetId(0);
//     }

//     color_buffer.SetId(0);
//     color_buffer.SetStage(nvn::ShaderStage::FRAGMENT);
//     color_buffer.SetIndex(0);

//     shaders[ShaderStage::Vertex] = ShaderProgram::DataSet(simple_2d::get_vertex_code_bin(), simple_2d::get_vertex_control_bin());
//     shaders[ShaderStage::Fragment] = ShaderProgram::DataSet(simple_2d::get_fragment_code_bin(), simple_2d::get_fragment_control_bin());

//     SL_ASSERTM(shaders.Initialize(g_Device), "failed to initialize shaders");

//     blend_state->SetBlendTarget(0)
//         .SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD)
//         .SetBlendFunc(nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA, nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA);

//     color_state->SetBlendEnable(0, true)
//         .SetLogicOp(nvn::LogicOp::COPY);

//     polygon_state->SetCullFace(nvn::Face::NONE)
//         .SetFrontFace(nvn::FrontFace::CCW)
//         .SetPolygonMode(nvn::PolygonMode::FILL);

//     vertex_attrib_state[0].SetFormat(nvn::Format::RG32F, 0)
//         .SetStreamIndex(0);

//     vertex_stream_state[0].SetStride(sizeof(phx::Vector2f));
// }

// CollidableObjectManager& CollidableObjectManager::Instance() {
//     static CollidableObjectManager instance;
//     return instance;
// }

// void CollidableObjectManager::Render(nvn::CommandBuffer* cmdbuf) {
//     auto& instance = Instance();
//     instance.shaders.Bind(cmdbuf);
//     instance.color_buffer.Bind(cmdbuf);
//     instance.blend_state.Bind(cmdbuf);
//     instance.channel_mask_state.Bind(cmdbuf);
//     instance.color_state.Bind(cmdbuf);
//     instance.multisample_state.Bind(cmdbuf);
//     instance.polygon_state.Bind(cmdbuf);
//     instance.vertex_attrib_state.Bind(cmdbuf);
//     instance.vertex_stream_state.Bind(cmdbuf);

//     instance.vertex_buffer[instance.buffer_in_use].Bind(cmdbuf);

//     cmdbuf->SetLineWidth(3.0f);

//     for (const auto& info : instance.draw_infos[instance.buffer_in_use]) {
//         instance.color_buffer.Update(cmdbuf, &info.color);
//         instance.index_buffer[instance.buffer_in_use].SetSubArray(info.index_start, info.len);
//         instance.index_buffer[instance.buffer_in_use].SetPrimitive(info.primitive);
//         instance.index_buffer[instance.buffer_in_use].Draw(cmdbuf);
//     }

//     instance.buffer_in_use = (instance.buffer_in_use + 1) % 3;
//     instance.index_buffer[instance.buffer_in_use].Clear();
//     instance.vertex_buffer[instance.buffer_in_use].Clear();
//     instance.color_buffer.SetIndex(instance.buffer_in_use);
//     instance.draw_infos[instance.buffer_in_use].clear();
// }