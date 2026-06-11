#pragma once
#include "tmanager.hpp"
#include "bindable.hpp"
#include <string>

class Image : public Bindable {
public:
    struct RGBA_Data {
        size_t width;
        size_t height;
        const uint8_t* data;
    };

    Image(const std::string& name, std::shared_ptr<TextureManager> manager, const RGBA_Data& data);
    ~Image();

    Image(const Image&) = delete;
    Image(Image&&) = delete;

    Image& operator=(const Image&) = delete;
    Image& operator=(Image&&) = delete;

    inline void SetId(int bind_id) { id = bind_id; }
    inline void SetStage(nvn::ShaderStage new_stage) { stage = new_stage; }

    const std::string& Name() const { return name; }

    constexpr size_t Width() const { return width; }
    constexpr size_t Height() const { return height; }

    virtual void Bind(nvn::CommandBuffer* cmdbuf) override;

private:
    std::shared_ptr<TextureManager> manager;
    GfxAllocator* texture_memory;
    std::string name;
    size_t width;
    size_t height;
    nvn::ShaderStage stage;
    int id;
};