#include "gfx/rgba_renderer.hpp"
#include "gfx/res/simple_texture.h"

#define COORDS
#include "environment.hpp"

void RGBA_Renderer::LoadTexture(const std::string& name, const void* data, size_t width, size_t height) {
    auto& instance = Instance();

    Image::RGBA_Data img_data;
    img_data.data = reinterpret_cast<const uint8_t*>(data);
    img_data.width = width;
    img_data.height = height;

    instance.images.push_back(std::make_unique<Image>(name, instance.manager, img_data));
}

void RGBA_Renderer::LoadTexture(const std::string& name, const char* path, size_t width, size_t height) {
    void* data;
    int64_t size;
    read_file(path, &data, &size);
    SL_ASSERTM(data != nullptr, "failed to read file data");
    
    LoadTexture(name, data, width, height);
}

void RGBA_Renderer::DrawTexture(const std::string& name, phx::Vector2f pos, phx::Vector2f dim) {
    auto& instance = Instance();

    auto handle = instance.manager->GetTextureHandle(name);
    SL_ASSERTM(handle.has_value(), "no texture found with that name");

    auto texture = instance.manager->GetTexture(name);
    SL_ASSERT(texture.has_value());

    auto width = (float)texture.value()->GetWidth();
    auto height = (float)texture.value()->GetHeight();

    dim.x = (dim.x == -1.0f) ? width : dim.x;
    dim.y = (dim.y == -1.0f) ? height : dim.y;

    auto screen_pos = normalize_screen_coords(pos);
    auto screen_dim = normalize_texture(dim, { (float)g_DisplayWidth / 2.0f, (float)-g_DisplayHeight / 2.0f });

    size_t start = instance.vertex_buffer[instance.buffer_in_use].Length();

    instance.vertex_buffer[instance.buffer_in_use].SafePush(screen_pos);
    instance.vertex_buffer[instance.buffer_in_use].SafePush({ screen_pos.x + screen_dim.x, screen_pos.y });
    instance.vertex_buffer[instance.buffer_in_use].SafePush({ screen_pos.x + screen_dim.x, screen_pos.y + screen_dim.y });
    instance.vertex_buffer[instance.buffer_in_use].SafePush({ screen_pos.x, screen_pos.y + screen_dim.y });

    instance.tcoord_buffer[instance.buffer_in_use].SafePush({ 0.0f, 0.0f });
    instance.tcoord_buffer[instance.buffer_in_use].SafePush({ 1.0f, 0.0f });
    instance.tcoord_buffer[instance.buffer_in_use].SafePush({ 1.0f, 1.0f });
    instance.tcoord_buffer[instance.buffer_in_use].SafePush({ 0.0f, 1.0f });

    instance.mcoord_buffer[instance.buffer_in_use].SafeResize(start + 4, phx::Vector2f { 0.0f, 0.0f });

    instance.index_buffer[instance.buffer_in_use].SafePush(start);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 1);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 2);
    instance.index_buffer[instance.buffer_in_use].SafePush(start);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 2);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 3);

    instance.draw_infos[instance.buffer_in_use].push_back(TextureDrawInfo { handle.value(), false });
}

void RGBA_Renderer::DrawTexture(const std::string& name, phx::Vector2f pos, phx::Vector2f dim, phx::Vector2f part_pos, phx::Vector2f part_dim) {
    auto& instance = Instance();

    auto handle = instance.manager->GetTextureHandle(name);
    SL_ASSERTM(handle.has_value(), "no texture found with that name");

    auto texture = instance.manager->GetTexture(name);
    SL_ASSERT(texture.has_value());

    auto width = (float)texture.value()->GetWidth();
    auto height = (float)texture.value()->GetHeight();

    auto tex_pos = normalize_texture(part_pos, { width, height });
    auto tex_dim = normalize_texture(part_dim, { width, height });

    dim.x = (dim.x == -1.0f) ? tex_dim.x : dim.x;
    dim.y = (dim.y == -1.0f) ? tex_dim.y : dim.y;

    auto screen_pos = normalize_screen_coords(pos);
    auto screen_dim = normalize_texture(dim, { (float)g_DisplayWidth, (float)-g_DisplayHeight });

    size_t start = instance.vertex_buffer[instance.buffer_in_use].Length();

    instance.vertex_buffer[instance.buffer_in_use].SafePush(screen_pos);
    instance.vertex_buffer[instance.buffer_in_use].SafePush({ screen_pos.x + screen_dim.x, screen_pos.y });
    instance.vertex_buffer[instance.buffer_in_use].SafePush({ screen_pos.x + screen_dim.x, screen_pos.y + screen_dim.y });
    instance.vertex_buffer[instance.buffer_in_use].SafePush({ screen_pos.x, screen_pos.y + screen_dim.y });

    instance.tcoord_buffer[instance.buffer_in_use].SafePush(tex_pos);
    instance.tcoord_buffer[instance.buffer_in_use].SafePush({ tex_pos.x + tex_dim.x, tex_pos.y });
    instance.tcoord_buffer[instance.buffer_in_use].SafePush({ tex_pos.x + tex_dim.x, tex_pos.y + tex_dim.y });
    instance.tcoord_buffer[instance.buffer_in_use].SafePush({ tex_pos.x, tex_pos.y + tex_dim.y });

    instance.mcoord_buffer[instance.buffer_in_use].SafeResize(start + 4, phx::Vector2f { 0.0f, 0.0f });

    instance.index_buffer[instance.buffer_in_use].SafePush(start);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 1);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 2);
    instance.index_buffer[instance.buffer_in_use].SafePush(start);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 2);
    instance.index_buffer[instance.buffer_in_use].SafePush(start + 3);

    instance.draw_infos[instance.buffer_in_use].push_back(TextureDrawInfo { handle.value(), false });
}

void RGBA_Renderer::SetLastMask(const std::string& name, phx::Vector2f apply_pos, phx::Vector2f apply_dim) {
    SL_ASSERTM(false, "unimplemented");
}

void RGBA_Renderer::SetLastMask(const std::string& name, phx::Vector2f apply_pos, phx::Vector2f apply_dim, phx::Vector2f part_pos, phx::Vector2f part_dim) {
    SL_ASSERTM(false, "unimplemented");
}

void RGBA_Renderer::Render(nvn::CommandBuffer* cmdbuf) {
    auto& instance = Instance();
    size_t i = instance.buffer_in_use;

    instance.shaders.Bind(cmdbuf);
    instance.draw_modes.Bind(cmdbuf);
    instance.blend_state.Bind(cmdbuf);
    instance.channel_mask_state.Bind(cmdbuf);
    instance.color_state.Bind(cmdbuf);
    instance.multisample_state.Bind(cmdbuf);
    instance.polygon_state.Bind(cmdbuf);
    instance.vertex_attrib_state.Bind(cmdbuf);
    instance.vertex_stream_state.Bind(cmdbuf);

    instance.vertex_buffer[i].Bind(cmdbuf);
    instance.tcoord_buffer[i].Bind(cmdbuf);
    instance.mcoord_buffer[i].Bind(cmdbuf);

    instance.manager->Bind(cmdbuf);
    
    size_t vertex_start = 0;
    for (const auto& draw_info : instance.draw_infos[i]) {
        cmdbuf->BindTexture(nvn::ShaderStage::FRAGMENT, simple_texture::FRAGMENT_TEXTURE_BINDING, draw_info.handle);
        instance.index_buffer[i].SetSubArray(vertex_start, 6);
        instance.index_buffer[i].Draw(cmdbuf);
        vertex_start += 6;
    }

    instance.buffer_in_use = (instance.buffer_in_use + 1) % 3;
    instance.vertex_buffer[instance.buffer_in_use].Clear();
    instance.tcoord_buffer[instance.buffer_in_use].Clear();
    instance.mcoord_buffer[instance.buffer_in_use].Clear();
    instance.index_buffer[instance.buffer_in_use].Clear();
    instance.draw_infos[instance.buffer_in_use].clear();
    instance.draw_modes.SetIndex(instance.buffer_in_use);
}

RGBA_Renderer::RGBA_Renderer()
    : vertex_buffer( { VertexBuffer<phx::Vector2f>(g_Device, 0x200), VertexBuffer<phx::Vector2f>(g_Device, 0x200), VertexBuffer<phx::Vector2f>(g_Device, 0x200) }),
        tcoord_buffer( { VertexBuffer<phx::Vector2f>(g_Device, 0x200), VertexBuffer<phx::Vector2f>(g_Device, 0x200), VertexBuffer<phx::Vector2f>(g_Device, 0x200) }),
        mcoord_buffer( { VertexBuffer<phx::Vector2f>(g_Device, 0x200), VertexBuffer<phx::Vector2f>(g_Device, 0x200), VertexBuffer<phx::Vector2f>(g_Device, 0x200) }),
        index_buffer( { IndexBuffer<unsigned short>(g_Device, 0x400), IndexBuffer<unsigned short>(g_Device, 0x400), IndexBuffer<unsigned short>(g_Device, 0x400) }),
        draw_modes(g_Device, 3),
        manager(new TextureManager()),
        shaders(),
        blend_state(),
        channel_mask_state(),
        color_state(),
        multisample_state(),
        polygon_state(),
        vertex_attrib_state(3),
        vertex_stream_state(3),
        images(),
        draw_infos({ { }, { }, { } }),
        buffer_in_use(0)
{
    for (size_t i = 0; i < 3; i++) {
        vertex_buffer[i].SetId(simple_texture::VERTEX_POSITION_BINDING);
        tcoord_buffer[i].SetId(simple_texture::VERTEX_TEXTURE_BINDING);
        mcoord_buffer[i].SetId(simple_texture::VERTEX_MASK_BINDING);
        draw_modes.Set(DRAW_MODE_REGULAR, i);
    }

    draw_modes.SetStage(nvn::ShaderStage::FRAGMENT);
    draw_modes.SetId(simple_texture::FRAGMENT_MODE_BINDING);
    draw_modes.SetIndex(0);

    shaders[ShaderStage::Vertex] = ShaderProgram::DataSet(simple_texture::get_vertex_code_bin(), simple_texture::get_vertex_control_bin());
    shaders[ShaderStage::Fragment] = ShaderProgram::DataSet(simple_texture::get_fragment_code_bin(), simple_texture::get_fragment_control_bin());
    SL_ASSERTM(shaders.Initialize(g_Device), "failed to initialize shader program");

    blend_state->SetBlendTarget(0)
        .SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD)
        .SetBlendFunc(nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA, nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA);

    color_state->SetBlendEnable(0, true)
        .SetLogicOp(nvn::LogicOp::COPY);

    polygon_state->SetCullFace(nvn::Face::NONE)
        .SetFrontFace(nvn::FrontFace::CCW)
        .SetPolygonMode(nvn::PolygonMode::FILL);

    for (size_t i = 0; i < 3; i++) {
        vertex_attrib_state[i].SetFormat(nvn::Format::RG32F, 0)
            .SetStreamIndex(static_cast<int>(i));

        vertex_stream_state[i].SetDefaults().SetStride(sizeof(phx::Vector2f));
    }
}

RGBA_Renderer& RGBA_Renderer::Instance() {
    static RGBA_Renderer instance;
    return instance;
}