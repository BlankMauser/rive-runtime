#include "environment.hpp"
#include "utils.hpp"
#include "gfx/tmanager.hpp"

#include <algorithm>

constexpr size_t TEXTURE_DESCRIPTOR_MIN = 0x100;
constexpr size_t TEXTURE_DESCRIPTOR_MAX = 0x100000;

constexpr size_t SAMPLER_DESCRIPTOR_MIN = 0x100;
constexpr size_t SAMPLER_DESCRIPTOR_MAX = 0x1000;

constexpr size_t DESCRIPTOR_SIZE = 0x20;

TextureManager::TextureManager(size_t texture_count, size_t sampler_count)
    : spool(nullptr),
      tpool(nullptr),
      device(g_Device),
      allocator(nullptr),
      textures(),
      samplers(),
      tlookup({}),
      slookup({}),
      hlookup({})
{
    texture_count = std::clamp(texture_count, TEXTURE_DESCRIPTOR_MIN, TEXTURE_DESCRIPTOR_MAX);
    sampler_count = std::clamp(sampler_count, SAMPLER_DESCRIPTOR_MIN, SAMPLER_DESCRIPTOR_MAX);

    size_t pool_size = ALIGN_UP((texture_count + sampler_count) * DESCRIPTOR_SIZE, 0x1000);
    allocator = new GfxAllocator(device, pool_size);

    spool = new nvn::SamplerPool;
    tpool = new nvn::TexturePool;

    auto spool_offset = allocator->Allocate(sampler_count * DESCRIPTOR_SIZE);
    auto tpool_offset = allocator->Allocate(texture_count * DESCRIPTOR_SIZE);

    SL_ASSERTM(spool->Initialize(&allocator->GetPool(), spool_offset, sampler_count), "Failed to initialize sampler pool");
    SL_ASSERTM(tpool->Initialize(&allocator->GetPool(), tpool_offset, texture_count), "Failed to initialize texture pool");
}

TextureManager::~TextureManager()
{
    tpool->Finalize();
    spool->Finalize();

    delete tpool;
    delete spool;

    delete allocator;
}

nvn::TextureHandle TextureManager::GetTextureHandle(int t_id, int s_id)
{
    SL_ASSERTM(t_id >= 0 && s_id >= 0, "Texture/Sampler IDs must be valid");

    return device->GetTextureHandle(t_id, s_id);
}

std::optional<nvn::TextureHandle> TextureManager::GetTextureHandle(const std::string &name)
{
    auto entry = hlookup.find(name);
    if (entry == hlookup.end())
        return {};
    else
        return entry->second;
}

int TextureManager::GetTextureId(const std::string &name)
{
    auto entry = tlookup.find(name);
    return (entry == tlookup.end()) ? -1 : entry->second;
}

int TextureManager::GetSamplerId(const std::string &name)
{
    auto entry = slookup.find(name);
    return (entry == slookup.end()) ? -1 : entry->second;
}

std::optional<std::shared_ptr<nvn::Texture>> TextureManager::GetTexture(int id)
{
    if (id >= static_cast<int>(textures.size()))
        return {};

    if (id < 0)
        return {};

    return textures[id];
}

std::optional<std::shared_ptr<nvn::Texture>> TextureManager::GetTexture(const std::string &name)
{
    return GetTexture(GetTextureId(name));
}

std::optional<std::shared_ptr<nvn::Sampler>> TextureManager::GetSampler(int id)
{
    if (id >= static_cast<int>(samplers.size()))
        return {};

    if (id < 0)
        return {};

    return samplers[id];
}

std::optional<std::shared_ptr<nvn::Sampler>> TextureManager::GetSampler(const std::string &name)
{
    return GetSampler(GetSamplerId(name));
}

nvn::TextureHandle TextureManager::RegisterTSPair(const std::string &name, int t_id, int s_id)
{
    SL_ASSERTM(t_id >= 0 && s_id >= 0, "Texture/sampler IDs must be valid");

    auto handle = device->GetTextureHandle(t_id, s_id);
    hlookup.insert_or_assign(name, handle);
    return handle;
}

int TextureManager::MakeTexture(const std::string &name, nvn::Texture *texture, const nvn::TextureView *view)
{
    auto entry = tlookup.find(name);
    if (entry == tlookup.end())
    {
        int id = static_cast<int>(textures.size());
        tlookup.insert({name, id});
        tpool->RegisterTexture(id, texture, view);
        textures.push_back(std::shared_ptr<nvn::Texture>(texture));
        return id;
    }
    else
    {
        int id = entry->second;
        SL_ASSERT(id < static_cast<int>(textures.size()));
        tpool->RegisterTexture(id, texture, view);
        textures[id] = std::shared_ptr<nvn::Texture>(texture);
        return id;
    }
}

int TextureManager::MakeTexture(const std::string &name, const nvn::TextureBuilder &builder, const nvn::TextureView *view)
{
    auto texture = new nvn::Texture;
    SL_ASSERTM(texture->Initialize(&builder), "Failed to initialize texture");

    return MakeTexture(name, texture, view);
}

int TextureManager::MakeSampler(const std::string &name, const nvn::SamplerBuilder &builder)
{
    auto sampler = new nvn::Sampler;
    SL_ASSERTM(sampler->Initialize(&builder), "Failed to initialize sampler");

    auto entry = slookup.find(name);
    if (entry == slookup.end())
    {
        int id = static_cast<int>(samplers.size());
        slookup.insert({name, id});
        spool->RegisterSampler(id, sampler);
        samplers.push_back(std::shared_ptr<nvn::Sampler>(sampler));
        return id;
    }
    else
    {
        int id = entry->second;
        SL_ASSERT(id < static_cast<int>(samplers.size()));
        spool->RegisterSampler(id, sampler);
        samplers[id] = std::shared_ptr<nvn::Sampler>(sampler);
        return id;
    }
}

void TextureManager::Bind(nvn::CommandBuffer *cmdbuf)
{
    cmdbuf->SetTexturePool(tpool);
    cmdbuf->SetSamplerPool(spool);
}