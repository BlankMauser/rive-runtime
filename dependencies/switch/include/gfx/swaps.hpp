#pragma once
#include <memory>

#include "bindable.hpp"
#include "drawable.hpp"
#include "tmanager.hpp"

template <size_t COUNT = 3>
class Swaps : public Bindable
{

public:
    Swaps(nvn::Device *device)
        : Bindable(),
          manager(COUNT, 1),
          current_index(0),
          render_targets{},
          sampler_id(0)
    {
        nvn::TextureBuilder builder;
        builder.SetDefaults()
            .SetDevice(device)
            .SetLevels(1)
            .SetFormat(nvn::Format::RGBA8)
            .SetTarget(nvn::TextureTarget::TARGET_2D)
            .SetStride(1920 * 4)
            .SetSize2D(1920, 1080)
            .SetDepth(1)
            .SetSamples(0);

        nvn::SamplerBuilder sbuilder;
        sbuilder.SetDefaults()
            .SetDevice(device)
            .SetMinMagFilter(nvn::MinFilter::LINEAR, nvn::MagFilter::LINEAR)
            .SetWrapMode(nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP, nvn::WrapMode::CLAMP);

        sampler_id = manager.MakeSampler("sampler", sbuilder);

        size_t size = builder.GetStorageSize();

        allocator = new GfxAllocator(device, size * COUNT);

        int alignment;
        device->GetInteger(nvn::DeviceInfo::LINEAR_RENDER_TARGET_STRIDE_ALIGNMENT, &alignment);

        for (size_t i = 0; i < COUNT; i++)
        {
            auto offset = allocator->Allocate(size, static_cast<size_t>(alignment));
            builder.SetStorage(&allocator->GetPool(), offset);

            int id = manager.MakeTexture(std::to_string(i), builder);
            render_targets[i] = manager.GetTexture(id).value();
            handles[i] = manager.RegisterTSPair(std::to_string(i), id, sampler_id);
        }
    }

    virtual void Bind(nvn::CommandBuffer *cmdbuf) override
    {
        nvn::Texture *target = render_targets[current_index].get();
        cmdbuf->SetRenderTargets(1, &target, nullptr, nullptr, nullptr);
    }

    void Advance()
    {
        has_rendered[current_index] = true;
        current_index = (current_index + 1) % COUNT;
    }

    void BindForDraw(nvn::CommandBuffer *cmdbuf)
    {
        manager.Bind(cmdbuf);
    }

    void RegisterSystemTextures()
    {
        auto id0 = manager.MakeTexture("wintex0", sl_window_get_texture(0));
        auto id1 = manager.MakeTexture("wintex1", sl_window_get_texture(0));
        auto id2 = manager.MakeTexture("wintex2", sl_window_get_texture(0));

        manager.RegisterTSPair("window0", id0, sampler_id);
        manager.RegisterTSPair("window1", id1, sampler_id);
        manager.RegisterTSPair("window2", id2, sampler_id);
    }

    std::optional<nvn::TextureHandle> GetHandleForDraw()
    {
        if (has_rendered[(current_index + 2) % 3])
            return {handles[(current_index + 2) % 3]};
        else
            return {};
    }

private:
    TextureManager manager;
    size_t current_index;
    std::shared_ptr<nvn::Texture> render_targets[COUNT];
    nvn::TextureHandle handles[COUNT];
    bool has_rendered[COUNT];
    GfxAllocator *allocator;
    int sampler_id;
};