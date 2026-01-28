#pragma once
#include "image.hpp"
#include "vbuffer.hpp"
#include "ubuffer.hpp"
#include "ibuffer.hpp"
#include "shader.hpp"
#include "basic_bindables.hpp"
#include "smash.hpp"

class RGBA_Renderer {
private:
    static constexpr int DRAW_MODE_REGULAR = 0x0;
    static constexpr int DRAW_MODE_MASKED  = 0x1;

    struct TextureUniform {
        int mode;

        std::string name;
    };

    struct TextureDrawInfo {
        nvn::TextureHandle handle;

        bool is_masked;
    };

    RGBA_Renderer();

    static RGBA_Renderer& Instance();

public:
    static void LoadTexture(const std::string& name, const void* data, size_t width, size_t height);
    static void LoadTexture(const std::string& name, const char* path, size_t width, size_t height);

    static void DrawTexture(const std::string& name, phx::Vector2f pos, phx::Vector2f dim = { -1.0f, -1.0f });
    static void DrawTexture(const std::string& name, phx::Vector2f pos, phx::Vector2f dim, phx::Vector2f part_pos, phx::Vector2f part_dim);

    static void SetLastMask(
        const std::string& name,
        phx::Vector2f apply_pos,
        phx::Vector2f apply_dim
    );

    static void SetLastMask(
        const std::string& name,
        phx::Vector2f apply_pos,
        phx::Vector2f apply_dim,
        phx::Vector2f part_pos,
        phx::Vector2f part_dim
    );

    static void Render(nvn::CommandBuffer* cmdbuf);

private:
    VertexBuffer<phx::Vector2f> vertex_buffer[3];
    VertexBuffer<phx::Vector2f> tcoord_buffer[3];
    VertexBuffer<phx::Vector2f> mcoord_buffer[3];
    IndexBuffer<unsigned short> index_buffer[3];
    UniformBuffer<int> draw_modes;
    std::shared_ptr<TextureManager> manager;
    ShaderProgram shaders;
    BlendState blend_state;
    ChannelMaskState channel_mask_state;
    ColorState color_state;
    MultisampleState multisample_state;
    PolygonState polygon_state;
    VertexAttribState vertex_attrib_state;
    VertexStreamState vertex_stream_state;

    std::vector<std::unique_ptr<Image>> images;
    std::vector<TextureDrawInfo> draw_infos[3];
    size_t buffer_in_use;
};