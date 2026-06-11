#pragma once

#include "bindable.hpp"
#include "managed/allocator.hpp"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <optional>
class TextureManager : public Bindable
{
public:
    TextureManager(size_t texture_count = 0, size_t sampler_count = 0);
    ~TextureManager();

    TextureManager(const TextureManager &) = delete;
    TextureManager(TextureManager &&) = delete;

    TextureManager &operator=(const TextureManager &) = delete;
    TextureManager &operator=(TextureManager &&) = delete;

    nvn::TextureHandle GetTextureHandle(int t_id, int s_id);
    std::optional<nvn::TextureHandle> GetTextureHandle(const std::string &name);

    int GetTextureId(const std::string &name);
    int GetSamplerId(const std::string &name);

    std::optional<std::shared_ptr<nvn::Texture>> GetTexture(int id);
    std::optional<std::shared_ptr<nvn::Texture>> GetTexture(const std::string &name);

    std::optional<std::shared_ptr<nvn::Sampler>> GetSampler(int id);
    std::optional<std::shared_ptr<nvn::Sampler>> GetSampler(const std::string &name);

    nvn::TextureHandle RegisterTSPair(const std::string &name, int t_id, int s_id);
    int MakeTexture(const std::string &name, nvn::Texture *texture, const nvn::TextureView *view = nullptr);
    int MakeTexture(const std::string &name, const nvn::TextureBuilder &builder, const nvn::TextureView *view = nullptr);
    int MakeSampler(const std::string &name, const nvn::SamplerBuilder &builder);

    virtual void Bind(nvn::CommandBuffer *cmdbuf) override;

private:
    nvn::SamplerPool *spool;
    nvn::TexturePool *tpool;
    nvn::Device *device;
    GfxAllocator *allocator;

    std::vector<std::shared_ptr<nvn::Texture>> textures;
    std::vector<std::shared_ptr<nvn::Sampler>> samplers;

    std::unordered_map<std::string, int> tlookup;
    std::unordered_map<std::string, int> slookup;
    std::unordered_map<std::string, nvn::TextureHandle> hlookup;
};