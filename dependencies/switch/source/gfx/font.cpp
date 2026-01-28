#include "gfx/font.hpp"
#include "utils.hpp"
#include <cmath>

#include "environment.hpp"
#include "gfx/res/simple_texture.h"
#include "vector_math.hpp"

FontManager::FontManager()
    : m_Engine(), m_LoadedFont(), m_Scale(192), m_IsFontLoaded(false),
    m_VertexBuffer( { VertexBuffer<phx::Vector2f>(g_Device, 0x10000), VertexBuffer<phx::Vector2f>(g_Device, 0x10000), VertexBuffer<phx::Vector2f>(g_Device, 0x10000) }),
    m_TexCoordBuffer( { VertexBuffer<phx::Vector2f>(g_Device, 0x10000), VertexBuffer<phx::Vector2f>(g_Device, 0x10000), VertexBuffer<phx::Vector2f>(g_Device, 0x10000) }),
    m_MCoordBuffer( { VertexBuffer<phx::Vector2f>(g_Device, 0x10000), VertexBuffer<phx::Vector2f>(g_Device, 0x10000), VertexBuffer<phx::Vector2f>(g_Device, 0x10000) }),
    m_IndexBuffer( { IndexBuffer<unsigned short>(g_Device, 0x4000), IndexBuffer<unsigned short>(g_Device, 0x4000), IndexBuffer<unsigned short>(g_Device, 0x4000) }),
    m_pTextureManager(new TextureManager()),
    m_Shaders(),
    m_DrawMode(g_Device, 3),
    m_BlendState(),
    m_ChannelMaskState(),
    m_ColorState(),
    m_MultisampleState(),
    m_PolygonState(),
    m_VertexAttribState(3),
    m_VertexStreamState(3),
    m_BufferInUse(0),
    m_pAllocator(nullptr)
{
    for (size_t i = 0; i < 3; i++) {
        m_VertexBuffer[i].SetId(simple_texture::VERTEX_POSITION_BINDING);
        m_TexCoordBuffer[i].SetId(simple_texture::VERTEX_TEXTURE_BINDING);
        m_MCoordBuffer[i].SetId(simple_texture::VERTEX_MASK_BINDING);
        m_DrawMode.Set(0, i);
    }

    m_DrawMode.SetStage(nvn::ShaderStage::FRAGMENT);
    m_DrawMode.SetId(simple_texture::FRAGMENT_MODE_BINDING);
    m_DrawMode.SetIndex(0);

    m_Shaders[ShaderStage::Vertex] = ShaderProgram::DataSet(simple_texture::get_vertex_code_bin(), simple_texture::get_vertex_control_bin());
    m_Shaders[ShaderStage::Fragment] = ShaderProgram::DataSet(simple_texture::get_fragment_code_bin(), simple_texture::get_fragment_control_bin());

    SL_ASSERTM(m_Shaders.Initialize(g_Device), "failed to initialize shader program");

    m_BlendState->SetBlendTarget(0)
        .SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD)
        .SetBlendFunc(nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA, nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA);

    m_ColorState->SetBlendEnable(0, true)
        .SetLogicOp(nvn::LogicOp::COPY);

    m_PolygonState->SetCullFace(nvn::Face::NONE)
        .SetFrontFace(nvn::FrontFace::CCW)
        .SetPolygonMode(nvn::PolygonMode::FILL);

    for (size_t i = 0; i < 3; i++) {
        m_VertexAttribState[i].SetFormat(nvn::Format::RG32F, 0)
            .SetStreamIndex(static_cast<int>(i));

        m_VertexStreamState[i].SetDefaults().SetStride(sizeof(phx::Vector2f));
    }
}

FontManager::~FontManager() {
    // TODO?
}

FontManager& FontManager::Instance() {
    static FontManager s_Instance;
    return s_Instance;
}

void FontManager::LoadFont(const char* path) {
    SL_ASSERTM(!m_IsFontLoaded, "Only one font at a time please :)");
    void* output_data = nullptr;
    int64_t output_size = -1;
    read_file(path, &output_data, &output_size);

    LoadFontFromMemory(output_data, static_cast<size_t>(output_size));
}

void FontManager::LoadFontFromMemory(void* data, size_t data_size) {
    SL_ASSERTM(!m_IsFontLoaded, "Only one font at a time please :)");
    // 10 MB
    constexpr size_t WORK_BUF_SIZE = 10 * 1024 * 1024;
    char* work_buffer = new char[WORK_BUF_SIZE];
    SL_ASSERTM(0 == m_Engine.Initialize((void*)work_buffer, static_cast<uint32_t>(WORK_BUF_SIZE)), "failed to initialize");
    char buf[nn::fontll::FontNameLengthMax];
    auto res = m_Engine.LoadFont(buf, data, 0, nn::fontll::FontNameLengthMax);
    debug_log("%x", res);
    SL_ASSERTM(0 == res, "failed to load font");
    SL_ASSERTM(0 == m_Engine.SetFont(buf), "failed to set font");

    m_IsFontLoaded = true;
}

void FontManager::SetScale(uint32_t scale) {
    m_Scale = scale;
    m_Engine.SetScale(scale << 16, 0, 0, scale << 16);
}

void FontManager::SetOutlineWidth(uint16_t width) {
    m_Engine.SetOutlineWidth(width);
}

void FontManager::SetFlags(nn::fontll::ScalableFontEngine::Flags flag) {
    m_Engine.SetFlags(flag);
}

f32 FontManager::GetLineSpacing() {
    nn::fontll::Metrics metrics;
    m_Engine.GetFontMetrics(&metrics);

    return static_cast<float>(metrics.os2Leading);
}

f32 FontManager::GetAscentRatio() {
    nn::fontll::Metrics metrics;
    m_Engine.GetFontMetrics(&metrics);

    return static_cast<float>(metrics.os2WinAscent) / metrics.metricsResolution;
}

float fixed_to_float(nn::fontll::Fixed32 fixed) {
    float output = (float)(fixed >> 16);
    for (int i = 0; i < 16; i++) {
        if ((fixed & (1 << (15 - i))) != 0)
            output += 1.0f / powf(2.0f, i + 1.0f);
    }
    return output;
}

void FontManager::WriteGlyphImage(
    uint8_t* output,
    uint32_t width,
    char code,
    ptrdiff_t stride,
    GlyphAccessor* glyph
)
{
    nn::fontll::GlyphMap* map = m_Engine.AcquireGlyphmap(code, nn::fontll::FormatGrayMap8);
    for (uint32_t i  = 0; i < width; i++) {
        memset(output + i * stride, 0, width);
    }

    const int font_ascent = static_cast<int>(GetAscentRatio() * m_Scale + 0.5f);
    const int offset_from_top = std::max(font_ascent - map->hiY, 0);
    const int render_oy = offset_from_top;
    const int render_ox = static_cast<int>((width - map->width) * 0.5 + map->loX);

    glyph->x0 = (float)render_ox;
    glyph->y0 = (float)render_oy;
    glyph->x1 = glyph->x0 + (float)map->width;
    glyph->y1 = glyph->y0 + (float)map->height;
    glyph->ascent = (float)font_ascent;
    glyph->height = map->height;
    glyph->width = map->width;
    glyph->top = map->hiY;
    glyph->left = map->loX;
    glyph->dx = fixed_to_float(map->dX);

    for (int32_t l = 0; l < map->height; l++) {
        uint8_t* l_start = &output[(l + render_oy) * stride + render_ox];
        memcpy(l_start, &map->bits[l * map->width], map->width);
    }

}

void FontManager::InitializeTextureImage(uint32_t glyph_width) {
    int alignment = 0;
    g_Device->GetInteger(nvn::DeviceInfo::LINEAR_RENDER_TARGET_STRIDE_ALIGNMENT, &alignment);
    
    nvn::TextureBuilder builder;
    builder.SetDefaults()
        .SetDevice(g_Device)
        .SetLevels(1)
        .SetFormat(nvn::Format::RGBA8)
        .SetSize2D(0x100 * glyph_width, glyph_width)
        .SetTarget(nvn::TextureTarget::TARGET_2D)
        .SetDepth(1)
        .SetSamples(0);

    auto size = builder.GetStorageSize();

    m_pAllocator = new GfxAllocator(g_Device, ALIGN_UP(builder.GetStorageSize(), alignment));
    ptrdiff_t mem_offset = m_pAllocator->Allocate(builder.GetStorageSize(), alignment);
    builder.SetStorage(&m_pAllocator->GetPool(), mem_offset);

    const int tex_id = m_pTextureManager->MakeTexture("glyph_map", builder);
    auto texture_opt = m_pTextureManager->GetTexture("glyph_map");
    SL_ASSERTM(texture_opt.has_value(), "glyph map has no texture");
    auto texture = texture_opt.value();

    uint8_t* buf1 = new uint8_t[glyph_width * glyph_width];
    uint8_t* buf2 = new uint8_t[glyph_width * glyph_width * 4];

    for (int i = 0; i < 0x100; i++) {
        auto* glyph = &m_Glyphs[i];
        WriteGlyphImage(buf1, glyph_width, (char)i, glyph_width, glyph);
        glyph->x0 += (float)(i * glyph_width);
        glyph->x1 += (float)(i * glyph_width);
        for (size_t j = 0; j < glyph_width; j++) {
            for (size_t k = 0; k < glyph_width; k++) {
                buf2[j * glyph_width * 4 + k * 4 + 0] = 0xFF;
                buf2[j * glyph_width * 4 + k * 4 + 1] = 0xFF;
                buf2[j * glyph_width * 4 + k * 4 + 2] = 0xFF;
                buf2[j * glyph_width * 4 + k * 4 + 3] = buf1[j * glyph_width + k];
            }
        }

        nvn::CopyRegion region {
            .xoffset = i * glyph_width,
            .yoffset = 0,
            .zoffset = 0,
            .width = glyph_width,
            .height = glyph_width,
            .depth = 1
        };

        texture->WriteTexels(nullptr, &region, buf2);
    }

    nvn::SamplerBuilder s_builder;
    s_builder.SetDefaults()
        .SetDevice(g_Device)
        .SetMinMagFilter(nvn::MinFilter::LINEAR, nvn::MagFilter::LINEAR)
        .SetWrapMode(nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP);

    const int s_id = m_pTextureManager->MakeSampler("glyph_map", s_builder);
    m_pTextureManager->RegisterTSPair("glyph_map", tex_id, s_id);

    delete[] buf1;
    delete[] buf2;
}

f32 FontManager::DrawText(int x, int y, float height_max, const char* text) {
    auto& instance = Instance();

    size_t len = strlen(text);
    if (len == 0)
        return;

    auto texture_opt = instance.m_pTextureManager->GetTexture("glyph_map");
    SL_ASSERTM(texture_opt.has_value(), "texture manager has not glyph map :(");
    auto texture = texture_opt.value();

    float width = texture->GetWidth();
    float height = texture->GetHeight();

    float ratio = height_max / instance.m_Scale;

    float _x = (float)x;
    float _y = (float)y;

    for (size_t i = 0; i < len; i++) {
        auto& glyph = instance.m_Glyphs[text[i]];
        if (text[i] == '\n') {
            _x = (float)x;
            _y += instance.GetAscentRatio() * instance.m_Scale * ratio;
            continue;
        }

        uint16_t start = static_cast<uint16_t>(instance.m_VertexBuffer[instance.m_BufferInUse].Length());

        instance.m_TexCoordBuffer[instance.m_BufferInUse].SafePush(phx::Vector2f {
            glyph.x0 / width, glyph.y0 / height
        });
        instance.m_TexCoordBuffer[instance.m_BufferInUse].SafePush(phx::Vector2f {
            glyph.x1 / width, glyph.y0 / height
        });
        instance.m_TexCoordBuffer[instance.m_BufferInUse].SafePush(phx::Vector2f {
            glyph.x1 / width, glyph.y1 / height
        });
        instance.m_TexCoordBuffer[instance.m_BufferInUse].SafePush(phx::Vector2f {
            glyph.x0 / width, glyph.y1 / height
        });

        float x0 = _x;
        float x1 = _x + glyph.width * ratio;

        float offset_from_top = std::max(glyph.ascent - glyph.top, 0.0f);
        float y1 = _y + (offset_from_top + glyph.height) * ratio;
        float y0 = y1 - glyph.height * ratio;

        instance.m_VertexBuffer[instance.m_BufferInUse].SafePush(as_screen_coords(phx::Vector2f { x0, y0 }));
        instance.m_VertexBuffer[instance.m_BufferInUse].SafePush(as_screen_coords(phx::Vector2f { x1, y0 }));
        instance.m_VertexBuffer[instance.m_BufferInUse].SafePush(as_screen_coords(phx::Vector2f { x1, y1 }));
        instance.m_VertexBuffer[instance.m_BufferInUse].SafePush(as_screen_coords(phx::Vector2f { x0, y1 }));

        instance.m_IndexBuffer[instance.m_BufferInUse].SafePush(start);
        instance.m_IndexBuffer[instance.m_BufferInUse].SafePush(start + 1);
        instance.m_IndexBuffer[instance.m_BufferInUse].SafePush(start + 2);
        instance.m_IndexBuffer[instance.m_BufferInUse].SafePush(start);
        instance.m_IndexBuffer[instance.m_BufferInUse].SafePush(start + 2);
        instance.m_IndexBuffer[instance.m_BufferInUse].SafePush(start + 3);

        _x += glyph.dx * ratio;
        if (text[i + 1] != '\0') {
            nn::fontll::Fixed32 dx, dy;
            instance.m_Engine.GetKerning(&dx, &dy, text[i], text[i + 1]);
            x += fixed_to_float(dx);
            y += fixed_to_float(dy);
        }
    }

    return _x;
}

void FontManager::Render(nvn::CommandBuffer* cmdbuf) {
    auto& instance = Instance();
    size_t i = instance.m_BufferInUse;
    instance.m_Shaders.Bind(cmdbuf);
    instance.m_BlendState.Bind(cmdbuf);
    instance.m_ChannelMaskState.Bind(cmdbuf);
    instance.m_ColorState.Bind(cmdbuf);
    instance.m_MultisampleState.Bind(cmdbuf);
    instance.m_PolygonState.Bind(cmdbuf);
    instance.m_VertexAttribState.Bind(cmdbuf);
    instance.m_VertexStreamState.Bind(cmdbuf);
    instance.m_VertexBuffer[i].Bind(cmdbuf);
    instance.m_TexCoordBuffer[i].Bind(cmdbuf);
    instance.m_pTextureManager->Bind(cmdbuf);

    instance.m_IndexBuffer[i].Draw(cmdbuf);

    instance.m_BufferInUse = (i + 1) % 3;
    instance.m_VertexBuffer[instance.m_BufferInUse].Clear();
    instance.m_TexCoordBuffer[instance.m_BufferInUse].Clear();
    instance.m_IndexBuffer[instance.m_BufferInUse].Clear();
}