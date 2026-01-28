#pragma once

#include "font.h"
#include "bindable.hpp"
#include "managed/allocator.hpp"
#include "vbuffer.hpp"
#include "ibuffer.hpp"
#include "ubuffer.hpp"
#include "tmanager.hpp"
#include "basic_bindables.hpp"
#include "smash.hpp"
#include "shader.hpp"
#include <string>

class FontManager {
private:
    struct GlyphAccessor {
        float x0;
        float y0;
        float x1;
        float y1;

        float ascent;
        float left;
        float top;
        float width;
        float height;

        float dx;
    };

    nn::fontll::ScalableFontEngine m_Engine;
    GlyphAccessor m_Glyphs[0x100];
    std::string m_LoadedFont;
    GfxAllocator* m_pAllocator;
    std::shared_ptr<TextureManager> m_pTextureManager;
    uint32_t m_Scale;
    bool m_IsFontLoaded;

    VertexBuffer<phx::Vector2f> m_VertexBuffer[3];
    VertexBuffer<phx::Vector2f> m_TexCoordBuffer[3];
    VertexBuffer<phx::Vector2f> m_MCoordBuffer[3];
    IndexBuffer<unsigned short> m_IndexBuffer[3];
    UniformBuffer<int> m_DrawMode;
    ShaderProgram m_Shaders;
    BlendState m_BlendState;
    ChannelMaskState m_ChannelMaskState;
    ColorState m_ColorState;
    PolygonState m_PolygonState;
    MultisampleState m_MultisampleState;
    VertexAttribState m_VertexAttribState;
    VertexStreamState m_VertexStreamState;
    size_t m_BufferInUse;

    FontManager();
    void WriteGlyphImage(uint8_t* output, uint32_t width, char code, ptrdiff_t stride, GlyphAccessor* glyph);

public:
    ~FontManager();

    static FontManager& Instance();

    void LoadFont(const char* path); 
    void LoadFontFromMemory(void* data, size_t data_size);

    void SetScale(uint32_t scale);
    void SetOutlineWidth(uint16_t width);
    void SetFlags(nn::fontll::ScalableFontEngine::Flags flag);
    f32 GetLineSpacing();
    f32 GetAscentRatio();

    void InitializeTextureImage(uint32_t glyph_width);

    static f32 DrawText(int x, int y, float height, const char* text);
    static void Render(nvn::CommandBuffer* cmdbuf);
};

// class Font : public Bindable {
// private:
//     struct GlyphAccessor {
//         float x0;
//         float y0;
//         float x1;
//         float y1;

//         float ascent;
//         float left;
//         float top;
//         float width;
//         float height;

//         float dx;
//     };

//     static constexpr uint32_t RENDER_SCALE = 192;

// private:
//     char name[nn::fontll::FontNameLengthMax];
//     GfxAllocator* allocator;
//     nvn::Texture* texture;

// };