#include "gfx/image.hpp"
#include "utils.hpp"
#include "environment.hpp"

Image::Image(const std::string& name, std::shared_ptr<TextureManager> manager, const RGBA_Data& data)
    : name(name),
        manager(manager),
        texture_memory(nullptr),
        width(data.width),
        height(data.height),
        stage(nvn::ShaderStage::FRAGMENT),
        id(0)
{
    nvn::TextureBuilder builder;
    
    builder.SetDefaults()
        .SetDevice(g_Device)
        .SetLevels(1)
        .SetFormat(nvn::Format::RGBA8)
        .SetSize2D(static_cast<int>(width), static_cast<int>(height))
        .SetTarget(nvn::TextureTarget::TARGET_2D)
        .SetDepth(1)
        .SetSamples(0);
    
    auto alignment = builder.GetStorageAlignment();
    auto size = builder.GetStorageSize();

    texture_memory = new GfxAllocator(g_Device, ALIGN_UP(size, alignment));

    auto offset = texture_memory->Allocate(size, alignment);
    builder.SetStorage(&texture_memory->GetPool(), offset);

    int t_id = manager->MakeTexture(name, builder);

    auto texture = manager->GetTexture(t_id);
    SL_ASSERT(texture.has_value());

    nvn::CopyRegion region {
        .xoffset = 0,
        .yoffset = 0,
        .zoffset = 0,
        .width = static_cast<int>(width),
        .height = static_cast<int>(height),
        .depth = 1
    };

    texture.value()->WriteTexels(nullptr, &region, data.data);

    nvn::SamplerBuilder s_builder;

    s_builder.SetDefaults()
        .SetDevice(g_Device)
        .SetMinMagFilter(nvn::MinFilter::LINEAR, nvn::MagFilter::LINEAR)
        .SetWrapMode(nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP);

    int s_id = manager->MakeSampler(name, s_builder);

    manager->RegisterTSPair(name, t_id, s_id);
}

Image::~Image() {
    delete texture_memory;
}

void Image::Bind(nvn::CommandBuffer* cmdbuf) {
    auto handle = manager->GetTextureHandle(name);
    SL_ASSERTM(handle.has_value(), "texture manager is missing image handle");
    manager->Bind(cmdbuf);
    cmdbuf->BindTexture(stage, id, handle.value());
}