#pragma once

#include "vbuffer.hpp"
#include "ibuffer.hpp"
#include "ubuffer.hpp"
#include "smash.hpp"
#include "shader.hpp"
#include "basic_bindables.hpp"

struct GroundCollision;

class GroundCollisionManager
{
private:
    struct DrawInfo
    {
        int index_start;
        int len;
        nvn::DrawPrimitive primitive;
        phx::Vector4f color;
        std::optional<float> line_width = {};
    };

    GroundCollisionManager();

    static GroundCollisionManager &Instance();

    friend void GroundCollision__update_graphics(GroundCollision *);

public:
    static void InstallHooks();

    static void Render(nvn::CommandBuffer *cmdbuf);

private:
    VertexBuffer<phx::Vector2f> vertex_buffer[3];
    IndexBuffer<unsigned short> index_buffer[3];
    UniformBuffer<phx::Vector4f> color_buffer;
    ShaderProgram shaders;
    BlendState blend_state;
    ChannelMaskState channel_mask_state;
    ColorState color_state;
    MultisampleState multisample_state;
    PolygonState polygon_state;
    VertexAttribState vertex_attrib_state;
    VertexStreamState vertex_stream_state;
    int buffer_in_use;

    std::vector<DrawInfo> draw_infos[3];
};