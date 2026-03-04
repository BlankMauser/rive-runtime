#include "rive/capi.h"
#include "rive/renderer/capi_renderer.hpp"
#include "rive/renderer/draw.hpp"
#include "rive/renderer/gpu.hpp"
#include "rive/renderer/nvn/nvn_pipeline.hpp"
#include "rive/renderer/render_context_impl.hpp"
#include "rive/renderer/texture.hpp"
#include "rive/refcnt.hpp"
#include "rive/shapes/paint/color.hpp"

#include "instance_chunker.hpp"

#include "nvn/nvn.hpp"
#include "glslc/glslc.h"
#include "nn/ro.h"
#include "nvn_test_config.hpp"
#include "utils.hpp"

#ifndef RIVE_NVN_ENABLE_LOGS
#define RIVE_NVN_ENABLE_LOGS 0
#endif

#ifndef RIVE_NVN_ENABLE_RENDERER_LOGS
#define RIVE_NVN_ENABLE_RENDERER_LOGS 0
#endif

#ifndef RIVE_NVN_ENABLE_BIND_LOGS
#define RIVE_NVN_ENABLE_BIND_LOGS 0
#endif

#ifndef RIVE_NVN_ENABLE_RASTER_ORDERING
#define RIVE_NVN_ENABLE_RASTER_ORDERING 1
#endif

#ifndef RIVE_NVN_DISABLE_PLS
#define RIVE_NVN_DISABLE_PLS 1
#endif

#ifndef RIVE_NVN_ENABLE_SHADER_PREWARM
#define RIVE_NVN_ENABLE_SHADER_PREWARM 1
#endif

#ifndef RIVE_NVN_GLSLC_USE_DEFAULT_ALLOC
#define RIVE_NVN_GLSLC_USE_DEFAULT_ALLOC 1
#endif

#ifndef RIVE_NVN_GLSLC_DEBUG_LEVEL
#define RIVE_NVN_GLSLC_DEBUG_LEVEL GLSLC_DEBUG_LEVEL_NONE
#endif

#ifndef RIVE_NVN_DISABLE_RESOURCE_TRIM
#define RIVE_NVN_DISABLE_RESOURCE_TRIM 1
#endif

// Apply gamma correction in MSAA shaders when rendering to sRGB targets.
#ifndef RIVE_NVN_NEEDS_GAMMA_CORRECTION
#define RIVE_NVN_NEEDS_GAMMA_CORRECTION 1
#endif

// Debug: disable stencil tests in MSAA path to isolate black output.
#ifndef RIVE_NVN_MSAA_DISABLE_STENCIL
#define RIVE_NVN_MSAA_DISABLE_STENCIL 0
#endif

// Use RGBA8 clip plane to avoid integer storage-image issues on some backends.
#ifndef RIVE_NVN_PLS_CLIP_RGBA8
#define RIVE_NVN_PLS_CLIP_RGBA8 1
#endif

#ifndef RIVE_NVN_PLS_FIXED_LAYOUT
#define RIVE_NVN_PLS_FIXED_LAYOUT 1
#endif

#ifndef RIVE_NVN_BUFFER_RING_SIZE
#define RIVE_NVN_BUFFER_RING_SIZE 16
#endif

#if !RIVE_NVN_ENABLE_LOGS || !RIVE_NVN_ENABLE_RENDERER_LOGS
#define debug_log(...) ((void)0)
#endif

#ifndef RIVE_NVN_ENABLE_PER_FRAME_LOGS
#define RIVE_NVN_ENABLE_PER_FRAME_LOGS 0
#endif

#if RIVE_NVN_ENABLE_PER_FRAME_LOGS
#define frame_log(...) debug_log(__VA_ARGS__)
#else
#define frame_log(...) ((void)0)
#endif

static bool env_flag_enabled(const char* name)
{
    if (!name)
    {
        return false;
    }
    const char* value = std::getenv(name);
    if (!value || !*value)
    {
        return false;
    }
    return value[0] == '1' || value[0] == 'y' || value[0] == 'Y' ||
           value[0] == 't' || value[0] == 'T';
}

#if defined(__SWITCH__)
#include "gfx/managed/memory.hpp"
#endif

#ifndef RIVE_NVN_PLS_BINDING_BASE
#define RIVE_NVN_PLS_BINDING_BASE 0
#endif
#if !RIVE_NVN_PLS_FIXED_LAYOUT
#define RIVE_PLS_BINDING_BASE RIVE_NVN_PLS_BINDING_BASE
#endif
#include "shaders/constants.glsl"

namespace nvn_api = ::nvn;

#ifndef RIVE_NVN_PLS_COLOR_FORMAT
#define RIVE_NVN_PLS_COLOR_FORMAT nvn_api::Format::RGBA8
#endif
#ifndef RIVE_NVN_PLS_SCRATCH_FORMAT
#define RIVE_NVN_PLS_SCRATCH_FORMAT nvn_api::Format::RGBA8
#endif
#ifndef RIVE_NVN_PLS_CLIP_FORMAT
#if RIVE_NVN_PLS_CLIP_RGBA8
#define RIVE_NVN_PLS_CLIP_FORMAT nvn_api::Format::RGBA8
#else
#define RIVE_NVN_PLS_CLIP_FORMAT nvn_api::Format::R32UI
#endif
#endif
#ifndef RIVE_NVN_PLS_COVERAGE_FORMAT
#define RIVE_NVN_PLS_COVERAGE_FORMAT nvn_api::Format::R32UI
#endif


#include "generated/shaders/advanced_blend.glsl.hpp"
#include "generated/shaders/bezier_utils.glsl.hpp"
#include "generated/shaders/color_ramp.glsl.hpp"
#include "generated/shaders/common.glsl.hpp"
#include "generated/shaders/constants.glsl.hpp"
#include "generated/shaders/draw_path_common.glsl.hpp"
#include "generated/shaders/draw_path.vert.hpp"
#include "generated/shaders/draw_msaa_object.frag.hpp"
#include "generated/shaders/draw_mesh.frag.hpp"
#include "generated/shaders/draw_image_mesh.vert.hpp"
#include "generated/shaders/stencil_draw.glsl.hpp"
#include "generated/shaders/glsl.glsl.hpp"
#include "generated/shaders/render_atlas.glsl.hpp"
#include "generated/shaders/tessellate.glsl.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <cstdio>

namespace
{
constexpr bool kDumpShaders = false;
enum class ViewKind
{
    SampleOrRenderTarget,
    StorageImage,
};

nvn_api::TextureTarget coerce_array_target(nvn_api::TextureTarget target)
{
    switch (target)
    {
        case nvn_api::TextureTarget::TARGET_2D_ARRAY:
            return nvn_api::TextureTarget::TARGET_2D;
        case nvn_api::TextureTarget::TARGET_2D_MULTISAMPLE_ARRAY:
            return nvn_api::TextureTarget::TARGET_2D_MULTISAMPLE;
        case nvn_api::TextureTarget::TARGET_CUBEMAP_ARRAY:
            return nvn_api::TextureTarget::TARGET_CUBEMAP;
        default:
            return target;
    }
}

nvn_api::TextureTarget view_target_for(nvn_api::TextureTarget target,
                                       ViewKind kind)
{
    switch (target)
    {
        case nvn_api::TextureTarget::TARGET_2D_MULTISAMPLE_ARRAY:
            return nvn_api::TextureTarget::TARGET_2D_MULTISAMPLE;
        default:
            break;
    }

    if (kind == ViewKind::SampleOrRenderTarget)
    {
        return coerce_array_target(target);
    }

    return target;
}

inline nvn_api::BarrierBits texture_visibility_barrier_bits()
{
    return nvn_api::BarrierBits::ORDER_FRAGMENTS |
           nvn_api::BarrierBits::INVALIDATE_TEXTURE |
           nvn_api::BarrierBits::INVALIDATE_SHADER;
}

#ifndef RIVE_NVN_FORCE_PLS_L2_INVALIDATE
#define RIVE_NVN_FORCE_PLS_L2_INVALIDATE 1
#endif

#ifndef RIVE_NVN_FORCE_PLS_BARRIER_EVERY_DRAW
#define RIVE_NVN_FORCE_PLS_BARRIER_EVERY_DRAW 1
#endif

#ifndef RIVE_NVN_ENABLE_REFLECTION_LOGS
#define RIVE_NVN_ENABLE_REFLECTION_LOGS 0
#endif

inline nvn_api::BarrierBits pls_storage_barrier_bits()
{
    auto bits = nvn_api::BarrierBits::ORDER_FRAGMENTS |
                nvn_api::BarrierBits::INVALIDATE_TEXTURE |
                nvn_api::BarrierBits::INVALIDATE_SHADER |
                nvn_api::BarrierBits::ORDER_PRIMITIVES;
#if RIVE_NVN_FORCE_PLS_L2_INVALIDATE
#ifdef NVN_BARRIER_INVALIDATE_L2_CACHE_BIT
    bits = bits |
           static_cast<nvn_api::BarrierBits>(NVN_BARRIER_INVALIDATE_L2_CACHE_BIT);
#endif
#endif
    return bits;
}

static void dump_shader_source(const char* label,
                               const char* stage,
                               const char* source)
{
    (void)label;
    (void)stage;
    (void)source;
    // Disabled: SD card access can crash on emulator and hardware.
}


void init_texture_view(nvn_api::TextureView* view,
                       nvn_api::TextureTarget target,
                       nvn_api::Format format,
                       ViewKind kind = ViewKind::SampleOrRenderTarget)
{
    if (!view)
    {
        return;
    }
    nvn_api::TextureTarget out_target = view_target_for(target, kind);
    debug_log("[rive dbg] init_texture_view: in_target=%d, out_target=%d, format=%d",
              static_cast<int>(target),
              static_cast<int>(out_target),
              static_cast<int>(format));
    view->SetDefaults()
        .SetFormat(format)
        .SetTarget(out_target)
        .SetLevels(0, 1)
        .SetLayers(0, 1);
}

void init_texture_view(nvn_api::TextureView* view,
                       nvn_api::Texture* texture,
                       ViewKind kind = ViewKind::SampleOrRenderTarget)
{
    if (!view || !texture)
    {
        return;
    }
    init_texture_view(view, texture->GetTarget(), texture->GetFormat(), kind);
}

size_t align_up(size_t value, size_t alignment)
{
    if (alignment == 0)
    {
        return value;
    }
    return (value + alignment - 1) & ~(alignment - 1);
}

void dump_texture_descriptor(const void* descriptor_memory,
                             size_t descriptor_memory_size,
                             size_t sampler_bytes,
                             int descriptor_size,
                             int id,
                             const char* label)
{
    if (!descriptor_memory || descriptor_size <= 0 || id < 0)
    {
        return;
    }
    const size_t entry_size = static_cast<size_t>(descriptor_size);
    const size_t offset = sampler_bytes + entry_size * static_cast<size_t>(id);
    if (offset + sizeof(uint32_t) * 8 > descriptor_memory_size)
    {
        return;
    }
    const auto* base = static_cast<const uint8_t*>(descriptor_memory) + offset;
    const auto* words = reinterpret_cast<const uint32_t*>(base);
    const uint32_t word0 = words[0];
    const uint32_t word4 = words[4];
    const uint32_t word5 = words[5];
    const uint32_t fmt = word0 & 0x8007ffffu;
    const int swizzle_r = static_cast<int>((word0 >> 19) & 7u);
    const int swizzle_g = static_cast<int>((word0 >> 22) & 7u);
    const int swizzle_b = static_cast<int>((word0 >> 25) & 7u);
    const int swizzle_a = static_cast<int>((word0 >> 28) & 7u);
    const int target = static_cast<int>((word4 >> 23) & 0xfu);
    const int srgb = static_cast<int>((word4 >> 22) & 1u);
    const int width = static_cast<int>(word4 & 0xffffu) + 1;
    const int height = static_cast<int>(word5 & 0xffffu) + 1;
    const int depth = static_cast<int>((word5 >> 16) & 0x3fffu) + 1;
    debug_log(
        "[rive nvn] texdesc %s id=%d fmt=0x%x target=%d srgb=%d whd=%dx%dx%d swz=%d%d%d%d word0=0x%08x",
        label ? label : "(unknown)",
        id,
        fmt,
        target,
        srgb,
        width,
        height,
        depth,
        swizzle_r,
        swizzle_g,
        swizzle_b,
        swizzle_a,
        word0);
}

struct GameAllocFns
{
    void* (*malloc_fn)(size_t) = nullptr;
    void* (*aligned_alloc_fn)(size_t, size_t) = nullptr;
    void* (*realloc_fn)(void*, size_t) = nullptr;
    void (*free_fn)(void*) = nullptr;
    bool resolved = false;
};

GameAllocFns g_game_alloc;

void resolve_game_allocators()
{
    if (g_game_alloc.resolved)
    {
        return;
    }
    uintptr_t addr = 0;
    if (R_SUCCEEDED(nn::ro::LookupSymbol(&addr, "malloc")))
    {
        g_game_alloc.malloc_fn =
            reinterpret_cast<void* (*)(size_t)>(addr);
    }
    if (R_SUCCEEDED(nn::ro::LookupSymbol(&addr, "aligned_alloc")))
    {
        g_game_alloc.aligned_alloc_fn =
            reinterpret_cast<void* (*)(size_t, size_t)>(addr);
    }
    if (R_SUCCEEDED(nn::ro::LookupSymbol(&addr, "realloc")))
    {
        g_game_alloc.realloc_fn =
            reinterpret_cast<void* (*)(void*, size_t)>(addr);
    }
    if (R_SUCCEEDED(nn::ro::LookupSymbol(&addr, "free")))
    {
        g_game_alloc.free_fn =
            reinterpret_cast<void (*)(void*)>(addr);
    }
    g_game_alloc.resolved = true;
}

void* game_alloc_aligned(size_t size, size_t alignment)
{
    resolve_game_allocators();
    size_t align = alignment ? alignment : alignof(std::max_align_t);
    size_t aligned_size = align_up(size, align);
    if (g_game_alloc.aligned_alloc_fn)
    {
        return g_game_alloc.aligned_alloc_fn(align, aligned_size);
    }
    if (g_game_alloc.malloc_fn && align <= alignof(std::max_align_t))
    {
        return g_game_alloc.malloc_fn(aligned_size);
    }
    return std::malloc(aligned_size);
}

void* default_alloc(size_t size, size_t alignment, void*)
{
    return game_alloc_aligned(size, alignment);
}

void* default_realloc(void* ptr, size_t size, void*)
{
    resolve_game_allocators();
    if (g_game_alloc.realloc_fn)
    {
        return g_game_alloc.realloc_fn(ptr, size);
    }
    return std::realloc(ptr, size);
}

void default_free(void* ptr, void*)
{
    if (!ptr)
    {
        return;
    }
    resolve_game_allocators();
    if (g_game_alloc.free_fn)
    {
        g_game_alloc.free_fn(ptr);
        return;
    }
    std::free(ptr);
}

RiveNVNAllocator make_allocator(const RiveNVNAllocator* allocator)
{
    if (allocator && allocator->alloc && allocator->free)
    {
        return *allocator;
    }
    return RiveNVNAllocator{default_alloc, default_realloc, default_free, nullptr};
}

struct GlslAllocatorState
{
    RiveNVNAllocator allocator = {};
    bool use_default = true;
};

void* glslc_alloc_cb(size_t size, size_t alignment, void* user)
{
    auto* state = static_cast<GlslAllocatorState*>(user);
    if (!state || state->use_default)
    {
        return std::malloc(size);
    }
    return state->allocator.alloc(size, alignment, state->allocator.user);
}

void* glslc_realloc_cb(void* ptr, size_t size, void* user)
{
    auto* state = static_cast<GlslAllocatorState*>(user);
    if (!state || state->use_default)
    {
        return std::realloc(ptr, size);
    }
    return state->allocator.realloc(ptr, size, state->allocator.user);
}

void glslc_free_cb(void* ptr, void* user)
{
    auto* state = static_cast<GlslAllocatorState*>(user);
    if (!state || state->use_default)
    {
        std::free(ptr);
        return;
    }
    state->allocator.free(ptr, state->allocator.user);
}

GlslAllocatorState make_glslc_allocator(const RiveNVNAllocator* allocator)
{
    GlslAllocatorState state;
#if RIVE_NVN_GLSLC_USE_DEFAULT_ALLOC
    state.use_default = true;
    return state;
#endif
    if (allocator && allocator->alloc && allocator->realloc && allocator->free)
    {
        state.allocator = *allocator;
    }
    else
    {
        state.allocator = make_allocator(nullptr);
    }
    state.use_default = false;
    return state;
}

struct GlslCompilerApi
{
    using SetAllocatorFn = void (*)(GLSLCallocateFunction,
                                    GLSLCfreeFunction,
                                    GLSLCreallocateFunction,
                                    void*);
    using InitializeFn = int (*)(GLSLCcompileObject*);
    using CompileFn = int (*)(GLSLCcompileObject*);
    using FinalizeFn = void (*)(GLSLCcompileObject*);
    using GetDefaultOptionsFn = GLSLCoptions (*)();

    SetAllocatorFn setAllocator = nullptr;
    InitializeFn initialize = nullptr;
    CompileFn compile = nullptr;
    FinalizeFn finalize = nullptr;
    GetDefaultOptionsFn getDefaultOptions = nullptr;

    bool ready() const
    {
        return setAllocator && initialize && compile && finalize;
    }
};

[[maybe_unused]] bool resolve_symbol(uintptr_t* out, const char* name)
{
    if (!out || !name)
    {
        return false;
    }
    *out = 0;
    nn::ro::LookupSymbol(out, name);
    return *out != 0;
}

bool resolve_glslc_api(GlslCompilerApi* api)
{
    if (!api)
    {
        return false;
    }

    *api = {};

    static bool s_logged_lookup_failure = false;
    uintptr_t ignored = 0;
    const bool glslc_dll_available =
        R_SUCCEEDED(nn::ro::LookupSymbol(
            &ignored,
            "nn::gfx::detail::GlslcDll::GlslcGetVersion")) &&
        ignored >= 0x1000;
    if (!glslc_dll_available)
    {
        if (!s_logged_lookup_failure)
        {
            debug_log("[rive] glslc LookupSymbol failed (GlslcGetVersion)");
            s_logged_lookup_failure = true;
        }
    }

    nn::gfx::detail::GlslcDll* glslc =
        glslc_dll_available ? nn::gfx::detail::GlslcDll::GetInstance()
                            : nullptr;
    static bool s_logged_glslc_version = false;
    static bool s_logged_glslc_header = false;

    if (glslc)
    {
        if (!glslc->IsInitialized())
        {
            glslc->Initialize();
        }
        if (!glslc->IsInitialized())
        {
            static bool s_logged_init_failure = false;
            if (!s_logged_init_failure)
            {
                debug_log("[rive] glslc Initialize failed");
                s_logged_init_failure = true;
            }
        }
        else
        {
            if (!s_logged_glslc_version && glslc->GlslcGetVersion)
            {
                GLSLCversion version = glslc->GlslcGetVersion();
                debug_log(
                    "[rive] glslc version api=%u.%u gpu=%u.%u pkg=%u",
                    version.apiMajor,
                    version.apiMinor,
                    version.gpuCodeVersionMajor,
                    version.gpuCodeVersionMinor,
                    version.package);
                s_logged_glslc_version = true;
                if (!s_logged_glslc_header)
                {
                    debug_log(
                        "[rive] glslc header api=%u.%u gpu=%u.%u",
                        GLSLC_API_VERSION_MAJOR,
                        GLSLC_API_VERSION_MINOR,
                        GLSLC_GPU_CODE_VERSION_MAJOR,
                        GLSLC_GPU_CODE_VERSION_MINOR);
                    s_logged_glslc_header = true;
                }
            }

            api->setAllocator =
                reinterpret_cast<GlslCompilerApi::SetAllocatorFn>(
                    glslc->GlslcSetAllocator);
            api->initialize =
                reinterpret_cast<GlslCompilerApi::InitializeFn>(
                    glslc->GlslcInitialize);
            api->compile =
                reinterpret_cast<GlslCompilerApi::CompileFn>(
                    glslc->GlslcCompile);
            api->finalize =
                reinterpret_cast<GlslCompilerApi::FinalizeFn>(
                    glslc->GlslcFinalize);
            api->getDefaultOptions =
                reinterpret_cast<GlslCompilerApi::GetDefaultOptionsFn>(
                    glslc->GlslcGetDefaultOptions);
        }
    }
    else if (glslc_dll_available)
    {
        static bool s_logged_get_instance_failure = false;
        if (!s_logged_get_instance_failure)
        {
            debug_log("[rive] glslc GetInstance failed");
            s_logged_get_instance_failure = true;
        }
    }

    if (!api->ready())
    {
        uintptr_t set_allocator = 0;
        uintptr_t initialize = 0;
        uintptr_t compile = 0;
        uintptr_t finalize = 0;
        uintptr_t get_version = 0;
        uintptr_t get_default_options = 0;
        resolve_symbol(&set_allocator, "glslcSetAllocator");
        resolve_symbol(&initialize, "glslcInitialize");
        resolve_symbol(&compile, "glslcCompile");
        resolve_symbol(&finalize, "glslcFinalize");
        resolve_symbol(&get_version, "glslcGetVersion");
        resolve_symbol(&get_default_options, "glslcGetDefaultOptions");

        api->setAllocator =
            reinterpret_cast<GlslCompilerApi::SetAllocatorFn>(set_allocator);
        api->initialize =
            reinterpret_cast<GlslCompilerApi::InitializeFn>(initialize);
        api->compile =
            reinterpret_cast<GlslCompilerApi::CompileFn>(compile);
        api->finalize =
            reinterpret_cast<GlslCompilerApi::FinalizeFn>(finalize);
        api->getDefaultOptions =
            reinterpret_cast<GlslCompilerApi::GetDefaultOptionsFn>(
                get_default_options);

        if (!s_logged_glslc_version && get_version)
        {
            using GetVersionFn = GLSLCversion (*)();
            GetVersionFn fn = reinterpret_cast<GetVersionFn>(get_version);
            GLSLCversion version = fn();
            debug_log(
                "[rive] glslc version api=%u.%u gpu=%u.%u pkg=%u",
                version.apiMajor,
                version.apiMinor,
                version.gpuCodeVersionMajor,
                version.gpuCodeVersionMinor,
                version.package);
            s_logged_glslc_version = true;
            if (!s_logged_glslc_header)
            {
                debug_log(
                    "[rive] glslc header api=%u.%u gpu=%u.%u",
                    GLSLC_API_VERSION_MAJOR,
                    GLSLC_API_VERSION_MINOR,
                    GLSLC_GPU_CODE_VERSION_MAJOR,
                    GLSLC_GPU_CODE_VERSION_MINOR);
                s_logged_glslc_header = true;
            }
        }

        if (api->ready())
        {
            static bool s_logged_c_api = false;
            if (!s_logged_c_api)
            {
                debug_log("[rive] glslc api resolved via C symbols");
                s_logged_c_api = true;
            }
        }
    }

    if (!api->ready())
    {
        static bool s_logged_missing_entrypoints = false;
        if (!s_logged_missing_entrypoints)
        {
            debug_log(
                "[rive] glslc entrypoints missing set=%d init=%d compile=%d finalize=%d",
                api->setAllocator != nullptr,
                api->initialize != nullptr,
                api->compile != nullptr,
                api->finalize != nullptr);
            s_logged_missing_entrypoints = true;
        }
    }

    return api->ready();
}

const char* glslc_init_status_label(GLSLCinitializationStatus status)
{
    switch (status)
    {
        case GLSLC_INIT_ERROR_UNINITIALIZED:
            return "uninitialized";
        case GLSLC_INIT_SUCCESS:
            return "success";
        case GLSLC_INIT_ERROR_ALLOC_FAILURE:
            return "alloc_failure";
        case GLSLC_INIT_ERROR_NO_ALLOC_CALLBACKS_SET:
            return "no_alloc_callbacks";
        default:
            return "unknown";
    }
}

void log_glslc_compile_failure(const GLSLCcompileObject& compile_object)
{
    const GLSLCresults* results = compile_object.lastCompiledResults;
    if (!results)
    {
        debug_log("[rive] glslc compile: results missing");
        return;
    }
    const GLSLCcompilationStatus* status = results->compilationStatus;
    if (!status)
    {
        debug_log("[rive] glslc compile: status missing");
        return;
    }
    debug_log("[rive] glslc status success=%u alloc=%u info_len=%u",
              static_cast<unsigned int>(status->success),
              static_cast<unsigned int>(status->allocError),
              static_cast<unsigned int>(status->infoLogLength));
    if (status->infoLog && status->infoLogLength > 0)
    {
        constexpr size_t kMaxLog = 512;
        size_t length = static_cast<size_t>(status->infoLogLength);
        size_t copy_len = std::min(length, kMaxLog - 1);
        char buffer[kMaxLog];
        std::memcpy(buffer, status->infoLog, copy_len);
        buffer[copy_len] = '\0';
        debug_log("[rive] glslc info: %s", buffer);
    }
    else if (status->infoLogLength > 0)
    {
        debug_log("[rive] glslc info log missing");
    }
}

struct PipelineKey
{
    rive::gpu::DrawType drawType = rive::gpu::DrawType::midpointFanPatches;
    rive::gpu::ShaderFeatures shaderFeatures = rive::gpu::ShaderFeatures::NONE;
    rive::gpu::ShaderMiscFlags miscFlags = rive::gpu::ShaderMiscFlags::none;
    rive::gpu::InterlockMode interlockMode = rive::gpu::InterlockMode::atomics;
    rive::gpu::nvn::AtlasTextureType atlasTextureType =
        rive::gpu::nvn::AtlasTextureType::rgba8;

    bool operator==(const PipelineKey& other) const
    {
        return drawType == other.drawType &&
               shaderFeatures == other.shaderFeatures &&
               miscFlags == other.miscFlags &&
               interlockMode == other.interlockMode &&
               atlasTextureType == other.atlasTextureType;
    }
};

struct PipelineKeyHasher
{
    size_t operator()(const PipelineKey& key) const noexcept
    {
        size_t value = static_cast<size_t>(key.drawType);
        value = value * 1315423911u +
                static_cast<size_t>(static_cast<uint32_t>(key.shaderFeatures));
        value = value * 1315423911u +
                static_cast<size_t>(static_cast<uint32_t>(key.miscFlags));
        value = value * 1315423911u +
                static_cast<size_t>(key.interlockMode);
        value = value * 1315423911u +
                static_cast<size_t>(key.atlasTextureType);
        return value;
    }
};

class NVNBuffer
{
public:
    NVNBuffer() = default;
    explicit NVNBuffer(const RiveNVNAllocator& allocator) : m_allocator(allocator) {}
    ~NVNBuffer() { reset(); }

    NVNBuffer(const NVNBuffer&) = delete;
    NVNBuffer& operator=(const NVNBuffer&) = delete;

    void setAllocator(const RiveNVNAllocator& allocator) { m_allocator = allocator; }

    void resize(size_t size)
    {
        if (size <= m_capacity)
        {
            m_size = size;
            return;
        }

        void* new_data =
            m_allocator.alloc ? m_allocator.alloc(size, alignof(std::max_align_t), m_allocator.user)
                              : nullptr;
        if (!new_data)
        {
            return;
        }

        if (m_data && m_allocator.free)
        {
            std::memcpy(new_data, m_data, m_size);
            m_allocator.free(m_data, m_allocator.user);
        }

        m_data = new_data;
        m_capacity = size;
        m_size = size;
    }

    void* data() { return m_data; }
    const void* data() const { return m_data; }
    size_t size() const { return m_size; }

private:
    void reset()
    {
        if (m_data && m_allocator.free)
        {
            m_allocator.free(m_data, m_allocator.user);
        }
        m_data = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

    RiveNVNAllocator m_allocator = {};
    void* m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
};

void* alloc_memory(size_t size,
                   size_t alignment,
                   const RiveNVNAllocator& allocator)
{
    const size_t kPoolAlignment = 0x1000;
    if (alignment < kPoolAlignment)
    {
        alignment = kPoolAlignment;
    }
    size = align_up(size, alignment);
    if (allocator.alloc)
    {
        return allocator.alloc(size, alignment, allocator.user);
    }

#if defined(__SWITCH__)
    static bool s_logged_global_alloc = false;
    if (!s_logged_global_alloc)
    {
        debug_log("[rive] alloc_memory: GlobalAllocator aligned");
        s_logged_global_alloc = true;
    }
    return GlobalAllocator::AllocAligned(size, alignment);
#else
    return aligned_alloc(alignment, size);
#endif
}

void free_memory(void* ptr, const RiveNVNAllocator& allocator)
{
    if (!ptr)
    {
        return;
    }

    if (allocator.free)
    {
        allocator.free(ptr, allocator.user);
    }
    else
    {
#if defined(__SWITCH__)
        GlobalAllocator::Free(ptr);
#else
        std::free(ptr);
#endif
    }
}

class NVNGpuBuffer
{
public:
    NVNGpuBuffer() = default;
    explicit NVNGpuBuffer(const RiveNVNAllocator& allocator) : m_allocator(allocator) {}
    ~NVNGpuBuffer() { reset(); }

    NVNGpuBuffer(const NVNGpuBuffer&) = delete;
    NVNGpuBuffer& operator=(const NVNGpuBuffer&) = delete;

    void setAllocator(const RiveNVNAllocator& allocator) { m_allocator = allocator; }

    bool upload(nvn_api::Device* device,
                const void* data,
                size_t size,
                nvn_api::MemoryPoolFlags flags)
    {
        if (!ensure(device, size, flags))
        {
            return false;
        }
        static bool s_skip_gpu_upload = false;
        if (s_skip_gpu_upload)
        {
            static bool s_logged_skip = false;
            if (!s_logged_skip)
            {
                debug_log("[rive] buffer upload skipped");
                s_logged_skip = true;
            }
            return true;
        }
        if (data && size > 0 && m_mapped)
        {
            static bool s_logged_upload = false;
            if (!s_logged_upload)
            {
                debug_log("[rive] buffer upload memcpy ptr=%p size=%zu flags=0x%x",
                          m_mapped,
                          size,
                          static_cast<unsigned int>(flags));
                s_logged_upload = true;
            }
            std::memcpy(m_mapped, data, size);
            if (s_logged_upload)
            {
                debug_log("[rive] buffer upload memcpy ok");
                debug_log("[rive] buffer upload flush size=%zu", size);
            }
            m_pool.FlushMappedRange(0, size);
            if (s_logged_upload)
            {
                debug_log("[rive] buffer upload flush ok");
            }
        }
        return true;
    }

    bool ensure(nvn_api::Device* device, size_t size, nvn_api::MemoryPoolFlags flags)
    {
        if (!device)
        {
            return false;
        }
        if (size == 0)
        {
            m_size = 0;
            return true;
        }
        if (m_initialized && size <= m_capacity && flags == m_flags)
        {
            m_size = size;
            return true;
        }

        {
            static bool s_logged_sizes = false;
            if (!s_logged_sizes)
            {
                debug_log("[rive] nvn sizes buffer_builder=%zu buffer=%zu",
                          sizeof(nvn_api::BufferBuilder),
                          sizeof(nvn_api::Buffer));
                s_logged_sizes = true;
            }
        }
        if (m_initialized || m_buffer)
        {
            debug_log("[rive] buffer ensure reset this=%p initialized=%d buffer=%p memory=%p size=%zu cap=%zu",
                      this,
                      m_initialized ? 1 : 0,
                      m_buffer.get(),
                      m_memory,
                      m_size,
                      m_capacity);
        }
        reset();
        debug_log("[rive] buffer ensure enter size=%zu flags=0x%x",
                  size,
                  static_cast<unsigned int>(flags));

        int page_alignment = 0;
        device->GetInteger(
            nvn_api::DeviceInfo::MEMPOOL_TEXTURE_OBJECT_PAGE_ALIGNMENT,
            &page_alignment);
        if (page_alignment <= 0)
        {
            page_alignment = 0x1000;
        }
        const size_t alignment = static_cast<size_t>(page_alignment);
        size_t aligned_size = align_up(size, alignment);
        m_memory = alloc_memory(aligned_size, alignment, m_allocator);
        if (!m_memory)
        {
            debug_log("[rive] buffer alloc failed size=%zu aligned=%zu flags=0x%x",
                      size,
                      aligned_size,
                      static_cast<unsigned int>(flags));
            return false;
        }

        nvn_api::MemoryPoolBuilder pool_builder;
        pool_builder.SetDefaults();
        pool_builder.SetDevice(device);
        pool_builder.SetFlags(flags);
        pool_builder.SetStorage(m_memory, aligned_size);
        if (!m_pool.Initialize(&pool_builder))
        {
            debug_log("[rive] buffer pool init failed size=%zu aligned=%zu flags=0x%x",
                      size,
                      aligned_size,
                      static_cast<unsigned int>(flags));
            free_memory(m_memory, m_allocator);
            m_memory = nullptr;
            return false;
        }
        debug_log("[rive] buffer pool init ok size=%zu aligned=%zu flags=0x%x",
                  size,
                  aligned_size,
                  static_cast<unsigned int>(flags));

        nvn_api::BufferBuilder buffer_builder;
        buffer_builder.SetDefaults().SetDevice(device).SetStorage(&m_pool, 0, aligned_size);
        m_buffer = std::make_unique<nvn_api::Buffer>();
        if (!m_buffer->Initialize(&buffer_builder))
        {
            debug_log("[rive] buffer init failed size=%zu aligned=%zu flags=0x%x",
                      size,
                      aligned_size,
                      static_cast<unsigned int>(flags));
            reset();
            return false;
        }
        debug_log("[rive] buffer init ok size=%zu aligned=%zu flags=0x%x",
                  size,
                  aligned_size,
                  static_cast<unsigned int>(flags));

        m_mapped = m_pool.Map();
        debug_log("[rive] buffer map %s",
                  m_mapped ? "ok" : "null");
        m_capacity = aligned_size;
        m_size = size;
        m_flags = flags;
        m_initialized = true;
        return true;
    }

    nvn_api::BufferAddress address(size_t offset = 0) const
    {
        if (!m_buffer)
        {
            return 0;
        }
        return m_buffer->GetAddress() + static_cast<nvn_api::BufferAddress>(offset);
    }

    size_t size() const { return m_size; }

private:
    void reset()
    {
        if (m_buffer)
        {
            m_buffer->Finalize();
            m_buffer.reset();
        }
        if (m_initialized)
        {
            m_pool.Finalize();
            m_initialized = false;
        }
        if (m_memory)
        {
            free_memory(m_memory, m_allocator);
            m_memory = nullptr;
        }
        m_mapped = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

    RiveNVNAllocator m_allocator = {};
    nvn_api::MemoryPool m_pool;
    std::unique_ptr<nvn_api::Buffer> m_buffer;
    void* m_memory = nullptr;
    void* m_mapped = nullptr;
    size_t m_capacity = 0;
    size_t m_size = 0;
    bool m_initialized = false;
    nvn_api::MemoryPoolFlags m_flags = nvn_api::MemoryPoolFlags::CPU_UNCACHED;
};

struct NVNTextureResource
{
    nvn_api::Texture texture;
    nvn_api::TextureView view;
    nvn_api::TextureView image_view;
    nvn_api::MemoryPool pool;
    void* memory = nullptr;
    size_t memory_size = 0;
    int width = 0;
    int height = 0;
    nvn_api::Format format = nvn_api::Format::RGBA8;
    nvn_api::TextureFlags flags = nvn_api::TextureFlags(0);
    nvn_api::TextureTarget target = nvn_api::TextureTarget::TARGET_2D;
    int texture_id = -1;
    int sampler_id = -1;
    int image_id = -1;
    nvn_api::TextureHandle handle = 0;
    nvn_api::ImageHandle image_handle = 0;
    bool initialized = false;

    void reset(const RiveNVNAllocator& allocator)
    {
        if (initialized)
        {
            texture.Finalize();
            pool.Finalize();
        }
        if (memory)
        {
            free_memory(memory, allocator);
            memory = nullptr;
        }
        memory_size = 0;
        initialized = false;
    }

    bool ensure(nvn_api::Device* device,
                const RiveNVNAllocator& allocator,
                nvn_api::TexturePool* texture_pool,
                int tex_id,
                int samp_id,
                int img_id,
                int new_width,
                int new_height,
                nvn_api::Format new_format,
                nvn_api::TextureFlags new_flags,
                nvn_api::TextureTarget new_target,
                nvn_api::MemoryPoolFlags pool_flags,
                bool register_texture,
                bool register_image)
    {
        if (!device)
        {
            return false;
        }

        // Some NVN producers (and some emulator backends) treat ordinary 2D textures as 2D_ARRAY with 1 layer.
        nvn_api::TextureTarget canonical_target = new_target;
        switch (canonical_target)
        {
            case nvn_api::TextureTarget::TARGET_2D_ARRAY:
                canonical_target = nvn_api::TextureTarget::TARGET_2D;
                break;
            case nvn_api::TextureTarget::TARGET_2D_MULTISAMPLE_ARRAY:
                canonical_target = nvn_api::TextureTarget::TARGET_2D_MULTISAMPLE;
                break;
            case nvn_api::TextureTarget::TARGET_CUBEMAP_ARRAY:
                canonical_target = nvn_api::TextureTarget::TARGET_CUBEMAP;
                break;
            default:
                break;
        }

        if (initialized && width == new_width && height == new_height &&
            format == new_format && flags == new_flags && target == canonical_target)
        {
            return true;
        }

        reset(allocator);

        width = new_width;
        height = new_height;
        format = new_format;
        flags = new_flags;
        target = canonical_target;
        texture_id = tex_id;
        sampler_id = samp_id;
        image_id = img_id;

        nvn_api::TextureBuilder builder{};
        builder.SetDefaults();
        builder.SetDevice(device);
        builder.SetFlags(flags);
        builder.SetTarget(target);
        builder.SetSize2D(width, height);
        builder.SetDepth(1);
        builder.SetLevels(1);
        builder.SetFormat(format);

        const size_t storage_size = builder.GetStorageSize();
        const size_t storage_alignment = builder.GetStorageAlignment();
        memory = alloc_memory(storage_size, storage_alignment, allocator);
        if (!memory)
        {
            debug_log(
                "[rive] texture alloc failed fmt=%d flags=0x%x target=%d size=%dx%d storage=%zu align=%zu",
                static_cast<int>(format),
                static_cast<unsigned int>(flags),
                static_cast<int>(target),
                width,
                height,
                storage_size,
                storage_alignment);
            return false;
        }
        memory_size = storage_size;

        nvn_api::MemoryPoolBuilder pool_builder;
        pool_builder.SetDefaults();
        pool_builder.SetDevice(device);
        pool_builder.SetFlags(pool_flags);
        pool_builder.SetStorage(memory, memory_size);
        if (!pool.Initialize(&pool_builder))
        {
            debug_log(
                "[rive] texture pool init failed fmt=%d flags=0x%x target=%d size=%dx%d pool_flags=0x%x storage=%zu",
                static_cast<int>(format),
                static_cast<unsigned int>(flags),
                static_cast<int>(target),
                width,
                height,
                static_cast<unsigned int>(pool_flags),
                memory_size);
            reset(allocator);
            return false;
        }

        builder.SetStorage(&pool, 0);
        if (!texture.Initialize(&builder))
        {
            debug_log(
                "[rive] texture init failed fmt=%d flags=0x%x target=%d size=%dx%d",
                static_cast<int>(format),
                static_cast<unsigned int>(flags),
                static_cast<int>(target),
                width,
                height);
            reset(allocator);
            return false;
        }

        // Keep views explicit about levels/layers to avoid array-view mismatches in emulators.
        init_texture_view(&view, target, format, ViewKind::SampleOrRenderTarget);
        // Keep image views identity-swizzled to avoid storage-image validation issues.
        image_view.SetDefaults()
            .SetFormat(format)
            .SetTarget(view_target_for(target, ViewKind::StorageImage))
            .SetLevels(0, 1)
            .SetLayers(0, 1)
            .SetSwizzle(nvn_api::TextureSwizzle::R,
                        nvn_api::TextureSwizzle::G,
                        nvn_api::TextureSwizzle::B,
                        nvn_api::TextureSwizzle::A);
        if (register_texture && texture_pool)
        {
            texture_pool->RegisterTexture(texture_id, &texture, &view);
            handle = device->GetTextureHandle(texture_id, sampler_id);
            if (handle == 0)
            {
                debug_log(
                    "[rive] texture handle 0 fmt=%d flags=0x%x target=%d size=%dx%d id=%d sampler=%d",
                    static_cast<int>(format),
                    static_cast<unsigned int>(flags),
                    static_cast<int>(target),
                    width,
                    height,
                    texture_id,
                    sampler_id);
            }
        }
        if (register_image && texture_pool)
        {
            texture_pool->RegisterImage(image_id, &texture, &image_view);
            image_handle = device->GetImageHandle(image_id);
            if (image_handle == 0)
            {
                debug_log(
                    "[rive] image handle 0 fmt=%d flags=0x%x target=%d size=%dx%d id=%d",
                    static_cast<int>(format),
                    static_cast<unsigned int>(flags),
                    static_cast<int>(target),
                    width,
                    height,
                    image_id);
            }
        }

        initialized = true;
        return true;
    }

    void upload_linear(const void* data, size_t size)
    {
        if (!data || !initialized)
        {
            return;
        }
        void* mapped = pool.Map();
        std::memcpy(mapped, data, size);
        pool.FlushMappedRange(0, size);
    }
};

struct ShaderBinary
{
    NVNshaderStage stage = NVN_SHADER_STAGE_VERTEX;
    std::vector<uint8_t> control;
    std::vector<uint8_t> code;
};

bool extract_shader_binary(const GLSLCoutput* output,
                           NVNshaderStage stage,
                           ShaderBinary* out)
{
    if (!output || output->magic != GLSLC_MAGIC_NUMBER || !out)
    {
        return false;
    }

    for (uint32_t i = 0; i < output->numSections; ++i)
    {
        const GLSLCsectionHeaderUnion& header = output->headers[i];
        if (header.genericHeader.common.type != GLSLC_SECTION_TYPE_GPU_CODE)
        {
            continue;
        }

        const GLSLCgpuCodeHeader& gpu = header.gpuCodeHeader;
        if (gpu.stage != stage)
        {
            continue;
        }

        const uint8_t* base =
            reinterpret_cast<const uint8_t*>(output) + gpu.common.dataOffset;
        const uint8_t* control_ptr = base + gpu.controlOffset;
        const uint8_t* data_ptr = base + gpu.dataOffset;

        out->stage = stage;
        out->control.assign(control_ptr, control_ptr + gpu.controlSize);
        out->code.assign(data_ptr, data_ptr + gpu.dataSize);
        return true;
    }

    return false;
}

struct ProgramBindings
{
    int pls_color = -1;
    int pls_clip = -1;
    int pls_scratch = -1;
    int pls_coverage = -1;

    bool has_any() const
    {
        return pls_color >= 0 || pls_clip >= 0 || pls_scratch >= 0 ||
               pls_coverage >= 0;
    }
};

struct PreprocIfState
{
    bool parent_active = true;
    bool branch_taken = false;
    bool active = true;
};

static inline std::string_view trim_view(std::string_view text)
{
    size_t start = 0;
    while (start < text.size() && std::isspace(static_cast<unsigned char>(text[start])))
    {
        ++start;
    }
    size_t end = text.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(text[end - 1])))
    {
        --end;
    }
    return text.substr(start, end - start);
}

static bool parse_int_token(std::string_view token, int* out)
{
    if (!out)
    {
        return false;
    }
    token = trim_view(token);
    if (token.empty())
    {
        return false;
    }
    while (!token.empty() &&
           (token.back() == 'u' || token.back() == 'U'))
    {
        token = token.substr(0, token.size() - 1);
    }
    if (token.empty())
    {
        return false;
    }
    std::string temp(token);
    char* end = nullptr;
    long value = std::strtol(temp.c_str(), &end, 0);
    if (!end || end == temp.c_str() || *end != '\0')
    {
        return false;
    }
    *out = static_cast<int>(value);
    return true;
}

static bool eval_int_expr(const std::string& expr,
                          const std::unordered_map<std::string, std::string>& macros,
                          int* out,
                          int depth = 0)
{
    if (!out || depth > 16)
    {
        return false;
    }
    std::string_view view = trim_view(expr);
    if (view.empty())
    {
        return false;
    }
    while (view.size() >= 2 && view.front() == '(' && view.back() == ')')
    {
        view = trim_view(view.substr(1, view.size() - 2));
    }
    if (view.empty())
    {
        return false;
    }
    size_t pos = 0;
    long sum = 0;
    bool any = false;
    while (pos < view.size())
    {
        size_t next = view.find('+', pos);
        std::string_view token =
            trim_view(view.substr(pos, next == std::string_view::npos
                                           ? view.size() - pos
                                           : next - pos));
        if (!token.empty())
        {
            int value = 0;
            if (parse_int_token(token, &value))
            {
                sum += value;
                any = true;
            }
            else
            {
                std::string key(token);
                auto it = macros.find(key);
                if (it == macros.end())
                {
                    return false;
                }
                if (!eval_int_expr(it->second, macros, &value, depth + 1))
                {
                    return false;
                }
                sum += value;
                any = true;
            }
        }
        if (next == std::string_view::npos)
        {
            break;
        }
        pos = next + 1;
    }
    if (!any)
    {
        return false;
    }
    *out = static_cast<int>(sum);
    return true;
}

static bool eval_defined_expr(std::string_view expr,
                              const std::unordered_map<std::string, std::string>& macros)
{
    expr = trim_view(expr);
    if (expr.empty())
    {
        return false;
    }
    // Split by ||
    size_t pos = 0;
    while (pos < expr.size())
    {
        size_t next_or = expr.find("||", pos);
        std::string_view term =
            trim_view(expr.substr(pos, next_or == std::string_view::npos
                                           ? expr.size() - pos
                                           : next_or - pos));
        bool term_value = true;
        size_t term_pos = 0;
        while (term_pos < term.size())
        {
            size_t next_and = term.find("&&", term_pos);
            std::string_view factor =
                trim_view(term.substr(term_pos,
                                      next_and == std::string_view::npos
                                          ? term.size() - term_pos
                                          : next_and - term_pos));
            bool value = false;
            if (!factor.empty())
            {
                bool negated = false;
                if (factor.front() == '!')
                {
                    negated = true;
                    factor = trim_view(factor.substr(1));
                }
                if (factor.rfind("defined", 0) == 0)
                {
                    size_t l = factor.find('(');
                    size_t r = factor.find(')', l == std::string_view::npos ? 0 : l + 1);
                    if (l != std::string_view::npos && r != std::string_view::npos && r > l)
                    {
                        std::string_view name =
                            trim_view(factor.substr(l + 1, r - l - 1));
                        value = macros.find(std::string(name)) != macros.end();
                    }
                }
                else if (!factor.empty())
                {
                    int numeric = 0;
                    if (parse_int_token(factor, &numeric))
                    {
                        value = (numeric != 0);
                    }
                    else
                    {
                        value = macros.find(std::string(factor)) != macros.end();
                    }
                }
                if (negated)
                {
                    value = !value;
                }
            }
            term_value = term_value && value;
            if (!term_value)
            {
                break;
            }
            if (next_and == std::string_view::npos)
            {
                break;
            }
            term_pos = next_and + 2;
        }
        if (term_value)
        {
            return true;
        }
        if (next_or == std::string_view::npos)
        {
            break;
        }
        pos = next_or + 2;
    }
    return false;
}

static bool parse_pls_bindings_from_glsl(const char* source,
                                         ProgramBindings* out)
{
    if (!source || !out)
    {
        return false;
    }
    *out = {};
    std::unordered_map<std::string, std::string> macros;
    std::vector<PreprocIfState> if_stack;

    auto parse_define_line = [&](std::string_view trimmed_line,
                                 std::unordered_map<std::string, std::string>&
                                     macro_map) {
        std::string_view rest = trim_view(trimmed_line.substr(7));
        if (rest.empty())
        {
            return;
        }
        size_t name_end = 0;
        while (name_end < rest.size() &&
               !std::isspace(static_cast<unsigned char>(rest[name_end])) &&
               rest[name_end] != '(')
        {
            ++name_end;
        }
        if (name_end == 0)
        {
            return;
        }
        std::string name(rest.substr(0, name_end));
        if (name_end < rest.size() && rest[name_end] == '(')
        {
            return; // function-like macro
        }
        std::string value;
        if (name_end < rest.size())
        {
            value = std::string(trim_view(rest.substr(name_end)));
        }
        macro_map[name] = value;
    };

    auto parse_pls_decl_line = [&](std::string_view trimmed_line,
                                   const std::unordered_map<std::string, std::string>&
                                       macro_map,
                                   ProgramBindings* bindings) {
        size_t decl_pos = trimmed_line.find("PLS_DECL");
        if (decl_pos == std::string_view::npos)
        {
            return;
        }

        size_t open = trimmed_line.find('(', decl_pos);
        size_t comma =
            trimmed_line.find(',', open == std::string_view::npos ? 0 : open + 1);
        size_t close =
            trimmed_line.find(')', comma == std::string_view::npos ? 0 : comma + 1);
        if (open == std::string_view::npos || comma == std::string_view::npos ||
            close == std::string_view::npos || comma <= open)
        {
            return;
        }

        std::string idx_expr(
            trim_view(trimmed_line.substr(open + 1, comma - open - 1)));
        std::string name(
            trim_view(trimmed_line.substr(comma + 1, close - comma - 1)));

        int binding = -1;
        if (!idx_expr.empty() && eval_int_expr(idx_expr, macro_map, &binding))
        {
            if (name.find("colorBuffer") != std::string::npos)
            {
                bindings->pls_color = binding;
            }
            else if (name.find("clipBuffer") != std::string::npos)
            {
                bindings->pls_clip = binding;
            }
            else if (name.find("scratch") != std::string::npos)
            {
                bindings->pls_scratch = binding;
            }
            else if (name.find("coverage") != std::string::npos)
            {
                bindings->pls_coverage = binding;
            }
        }
    };

    auto is_active = [&]() {
        return if_stack.empty() ? true : if_stack.back().active;
    };

    std::string_view text(source);
    size_t pos = 0;
    while (pos <= text.size())
    {
        size_t end = text.find('\n', pos);
        std::string_view line =
            text.substr(pos, end == std::string_view::npos ? text.size() - pos
                                                           : end - pos);
        pos = (end == std::string_view::npos) ? text.size() + 1 : end + 1;

        std::string_view trimmed = trim_view(line);
        if (trimmed.empty())
        {
            continue;
        }

        if (trimmed.front() == '#')
        {
            if (trimmed.rfind("#ifdef", 0) == 0)
            {
                std::string_view name = trim_view(trimmed.substr(6));
                bool cond = macros.find(std::string(name)) != macros.end();
                PreprocIfState state;
                state.parent_active = is_active();
                state.branch_taken = cond;
                state.active = state.parent_active && cond;
                if_stack.push_back(state);
                continue;
            }
            if (trimmed.rfind("#ifndef", 0) == 0)
            {
                std::string_view name = trim_view(trimmed.substr(7));
                bool cond = macros.find(std::string(name)) == macros.end();
                PreprocIfState state;
                state.parent_active = is_active();
                state.branch_taken = cond;
                state.active = state.parent_active && cond;
                if_stack.push_back(state);
                continue;
            }
            if (trimmed.rfind("#if", 0) == 0 && trimmed.rfind("#ifdef", 0) != 0 &&
                trimmed.rfind("#ifndef", 0) != 0)
            {
                std::string_view expr = trim_view(trimmed.substr(3));
                bool cond = eval_defined_expr(expr, macros);
                PreprocIfState state;
                state.parent_active = is_active();
                state.branch_taken = cond;
                state.active = state.parent_active && cond;
                if_stack.push_back(state);
                continue;
            }
            if (trimmed.rfind("#elif", 0) == 0)
            {
                if (!if_stack.empty())
                {
                    auto& state = if_stack.back();
                    if (state.branch_taken)
                    {
                        state.active = false;
                    }
                    else
                    {
                        std::string_view expr = trim_view(trimmed.substr(5));
                        bool cond = eval_defined_expr(expr, macros);
                        state.active = state.parent_active && cond;
                        if (cond)
                        {
                            state.branch_taken = true;
                        }
                    }
                }
                continue;
            }
            if (trimmed.rfind("#else", 0) == 0)
            {
                if (!if_stack.empty())
                {
                    auto& state = if_stack.back();
                    state.active = state.parent_active && !state.branch_taken;
                    state.branch_taken = true;
                }
                continue;
            }
            if (trimmed.rfind("#endif", 0) == 0)
            {
                if (!if_stack.empty())
                {
                    if_stack.pop_back();
                }
                continue;
            }
            if (trimmed.rfind("#define", 0) == 0)
            {
                if (!is_active())
                {
                    continue;
                }
                parse_define_line(trimmed, macros);
                continue;
            }
            if (trimmed.rfind("#undef", 0) == 0)
            {
                if (!is_active())
                {
                    continue;
                }
                std::string_view name = trim_view(trimmed.substr(6));
                if (!name.empty())
                {
                    macros.erase(std::string(name));
                }
                continue;
            }
        }

        if (!is_active())
        {
            continue;
        }
        if (trimmed.rfind("#define", 0) == 0)
        {
            continue;
        }

        parse_pls_decl_line(trimmed, macros, out);
    }

    if (out->has_any())
    {
        return true;
    }

    // Fallback: ignore preprocessor state and scan for PLS_DECL lines using
    // any macro definitions we can find in the source.
    std::unordered_map<std::string, std::string> fallback_macros;
    text = std::string_view(source);
    pos = 0;
    while (pos <= text.size())
    {
        size_t end = text.find('\n', pos);
        std::string_view line =
            text.substr(pos, end == std::string_view::npos ? text.size() - pos
                                                           : end - pos);
        pos = (end == std::string_view::npos) ? text.size() + 1 : end + 1;

        std::string_view trimmed = trim_view(line);
        if (trimmed.empty())
        {
            continue;
        }
        if (trimmed.rfind("#define", 0) == 0)
        {
            parse_define_line(trimmed, fallback_macros);
            continue;
        }
    }

    text = std::string_view(source);
    pos = 0;
    while (pos <= text.size())
    {
        size_t end = text.find('\n', pos);
        std::string_view line =
            text.substr(pos, end == std::string_view::npos ? text.size() - pos
                                                           : end - pos);
        pos = (end == std::string_view::npos) ? text.size() + 1 : end + 1;

        std::string_view trimmed = trim_view(line);
        if (trimmed.empty())
        {
            continue;
        }
        parse_pls_decl_line(trimmed, fallback_macros, out);
    }

    return out->has_any();
}

static bool parse_reflection_bindings_from_header(
    const GLSLCprogramReflectionHeader* reflection,
    const uint8_t* header_base,
    ProgramBindings* out)
{
    if (!out)
    {
        return false;
    }
    *out = {};
    if (!reflection || !header_base)
    {
        return false;
    }

    const uint8_t* data_base = header_base + reflection->common.dataOffset;
    const char* string_pool =
        reinterpret_cast<const char*>(data_base +
                                      reflection->stringPoolOffset);
    const auto* uniforms = reinterpret_cast<const GLSLCuniformInfo*>(
        data_base + reflection->uniformOffset);
    const int stage_index = static_cast<int>(NVN_SHADER_STAGE_FRAGMENT);
    bool matched_any = false;

    for (uint32_t i = 0; i < reflection->numUniforms; ++i)
    {
        const GLSLCuniformInfo& uniform = uniforms[i];
        const char* name = string_pool + uniform.nameInfo.nameOffset;
        if (!name)
        {
            continue;
        }
        if (!std::strstr(name, "colorBuffer") &&
            !std::strstr(name, "clipBuffer") &&
            !std::strstr(name, "scratch") &&
            !std::strstr(name, "coverage"))
        {
            continue;
        }
        const int binding = uniform.bindings[stage_index];
        if (binding < 0)
        {
            continue;
        }
        if (std::strstr(name, "colorBuffer"))
        {
            out->pls_color = binding;
            matched_any = true;
        }
        else if (std::strstr(name, "clipBuffer"))
        {
            out->pls_clip = binding;
            matched_any = true;
        }
        else if (std::strstr(name, "scratch"))
        {
            out->pls_scratch = binding;
            matched_any = true;
        }
        else if (std::strstr(name, "coverage"))
        {
            out->pls_coverage = binding;
            matched_any = true;
        }

#if RIVE_NVN_ENABLE_BIND_LOGS
        if (RIVE_NVN_ENABLE_REFLECTION_LOGS)
        {
            debug_log("[rive nvn] reflection image name=%s binding=%d type=%d",
                      name ? name : "(null)",
                      binding,
                      static_cast<int>(uniform.type));
        }
#endif
    }

    return matched_any;
}

class NvnShaderProgram
{
public:
    NvnShaderProgram() = default;
    ~NvnShaderProgram() { finalize(); }

    NvnShaderProgram(const NvnShaderProgram&) = delete;
    NvnShaderProgram& operator=(const NvnShaderProgram&) = delete;

    bool initialize(nvn_api::Device* device,
                    const RiveNVNAllocator& allocator,
                    GlslCompilerApi& glslc_api,
                    GlslAllocatorState& glslc_allocator,
                    const char* vertex_source,
                    const char* fragment_source)
    {
        if (!device || !vertex_source || !fragment_source)
        {
            return false;
        }

        finalize();
        m_bindings = {};

        std::vector<ShaderBinary> binaries;
        if (!compile_glsl(glslc_api,
                          glslc_allocator,
                          vertex_source,
                          fragment_source,
                          binaries,
                          &m_bindings))
        {
            static bool s_logged_compile_failure = false;
            if (!s_logged_compile_failure)
            {
                debug_log("[rive] program init failed: glslc compile");
                s_logged_compile_failure = true;
            }
            return false;
        }

        if (!build_program(device, allocator, binaries))
        {
            static bool s_logged_build_failure = false;
            if (!s_logged_build_failure)
            {
                debug_log("[rive] program init failed: build_program");
                s_logged_build_failure = true;
            }
            return false;
        }
        return true;
    }

    void bind(nvn_api::CommandBuffer* command_buffer) const
    {
        if (!m_program || !command_buffer)
        {
            return;
        }
        command_buffer->BindProgram(m_program.get(), m_stage_bits);
    }

    bool initialized() const { return m_program != nullptr; }
    const ProgramBindings& bindings() const { return m_bindings; }

    void finalize()
    {
        if (m_program)
        {
            m_program->Finalize();
            m_program.reset();
        }

        for (auto& buffer : m_code_buffers)
        {
            if (buffer)
            {
                buffer->Finalize();
            }
        }
        m_code_buffers.clear();
        m_shader_data.clear();

        if (m_code_pool_initialized)
        {
            m_code_pool.Finalize();
            m_code_pool_initialized = false;
        }
        if (m_code_memory)
        {
            free_memory(m_code_memory, m_allocator);
            m_code_memory = nullptr;
            m_code_memory_size = 0;
        }

        if (m_control_memory)
        {
            free_memory(m_control_memory, m_allocator);
            m_control_memory = nullptr;
            m_control_memory_size = 0;
        }
    }

private:
    static bool compile_glsl(GlslCompilerApi& glslc_api,
                             GlslAllocatorState& glslc_allocator,
                             const char* vertex_source,
                             const char* fragment_source,
                             std::vector<ShaderBinary>& out_binaries,
                             ProgramBindings* out_bindings)
    {
        if (!glslc_api.ready())
        {
            resolve_glslc_api(&glslc_api);
        }
        if (!glslc_api.ready())
        {
            static bool s_logged_glslc_unavailable = false;
            if (!s_logged_glslc_unavailable)
            {
                debug_log("[rive] glslc unavailable");
                s_logged_glslc_unavailable = true;
            }
            return false;
        }

        glslc_api.setAllocator(glslc_alloc_cb,
                               glslc_free_cb,
                               glslc_realloc_cb,
                               &glslc_allocator);

        GLSLCcompileObject compile_object = {};
        if (!glslc_api.initialize(&compile_object))
        {
            static bool s_logged_init_failure = false;
            if (!s_logged_init_failure)
            {
                debug_log("[rive] glslc initialize failed status=%u (%s)",
                          static_cast<unsigned int>(compile_object.initStatus),
                          glslc_init_status_label(compile_object.initStatus));
                s_logged_init_failure = true;
            }
            return false;
        }
        if (compile_object.initStatus != GLSLC_INIT_SUCCESS)
        {
            static bool s_logged_init_status = false;
            if (!s_logged_init_status)
            {
                debug_log("[rive] glslc init status=%u (%s)",
                          static_cast<unsigned int>(compile_object.initStatus),
                          glslc_init_status_label(compile_object.initStatus));
                s_logged_init_status = true;
            }
        }
        if (glslc_api.getDefaultOptions)
        {
            compile_object.options = glslc_api.getDefaultOptions();
        }

        ProgramBindings glsl_bindings = {};
        bool have_glsl_bindings = false;
        if (out_bindings)
        {
            have_glsl_bindings =
                parse_pls_bindings_from_glsl(fragment_source, &glsl_bindings);
#if RIVE_NVN_ENABLE_BIND_LOGS
            if (glsl_bindings.has_any())
            {
                static ProgramBindings s_last_logged_bindings = {};
                static bool s_has_last_logged = false;
                if (!s_has_last_logged ||
                    glsl_bindings.pls_color != s_last_logged_bindings.pls_color ||
                    glsl_bindings.pls_clip != s_last_logged_bindings.pls_clip ||
                    glsl_bindings.pls_scratch != s_last_logged_bindings.pls_scratch ||
                    glsl_bindings.pls_coverage != s_last_logged_bindings.pls_coverage)
                {
                    debug_log(
                        "[rive nvn] glsl bindings color=%d clip=%d scratch=%d coverage=%d",
                        glsl_bindings.pls_color,
                        glsl_bindings.pls_clip,
                        glsl_bindings.pls_scratch,
                        glsl_bindings.pls_coverage);
                    s_last_logged_bindings = glsl_bindings;
                    s_has_last_logged = true;
                }
            }
#endif
        }

        const char* sources[] = {vertex_source, fragment_source};
        NVNshaderStage stages[] = {NVN_SHADER_STAGE_VERTEX,
                                   NVN_SHADER_STAGE_FRAGMENT};

        compile_object.input.sources = sources;
        compile_object.input.stages = stages;
        compile_object.input.count = 2;

        compile_object.options.optionFlags.outputGpuBinaries = 1;
        compile_object.options.optionFlags.outputShaderReflection = 1;
        compile_object.options.optionFlags.outputAssembly = 0;
        compile_object.options.optionFlags.outputPerfStats = 0;
        compile_object.options.optionFlags.outputDebugInfo = RIVE_NVN_GLSLC_DEBUG_LEVEL;
        compile_object.options.optionFlags.language = GLSLC_LANGUAGE_GLSL;
        // Respect explicit layout(binding=...) indices so our NVN binding calls match.
        compile_object.options.optionFlags.ignoreBindings = 0;

        bool ok = glslc_api.compile(&compile_object) != 0;
        if (!ok || !compile_object.lastCompiledResults ||
            !compile_object.lastCompiledResults->glslcOutput)
        {
            static bool s_logged_compile_failure = false;
            if (!s_logged_compile_failure)
            {
                debug_log("[rive] glslc compile failed");
                log_glslc_compile_failure(compile_object);
                dump_shader_source("compile_fail", "vert", vertex_source);
                dump_shader_source("compile_fail", "frag", fragment_source);
                s_logged_compile_failure = true;
            }
            glslc_api.finalize(&compile_object);
            return false;
        }

        const GLSLCoutput* output =
            compile_object.lastCompiledResults->glslcOutput;
#if RIVE_NVN_ENABLE_REFLECTION_LOGS
        {
            static bool s_logged_reflection_enabled = false;
            if (!s_logged_reflection_enabled)
            {
                debug_log("[rive nvn] reflection logs enabled");
                s_logged_reflection_enabled = true;
            }
        }
#endif

        ProgramBindings reflection_bindings = {};
        bool have_reflection = false;
        if (out_bindings && compile_object.reflectionSection)
        {
            have_reflection = parse_reflection_bindings_from_header(
                compile_object.reflectionSection,
                reinterpret_cast<const uint8_t*>(
                    compile_object.reflectionSection),
                &reflection_bindings);
        }
        if (out_bindings && !have_reflection && output &&
            output->magic == GLSLC_MAGIC_NUMBER)
        {
            const uint8_t* base = reinterpret_cast<const uint8_t*>(output);
            for (uint32_t section = 0; section < output->numSections; ++section)
            {
                const GLSLCsectionHeaderUnion& header =
                    output->headers[section];
                if (header.genericHeader.common.type !=
                    GLSLC_SECTION_TYPE_REFLECTION)
                {
                    continue;
                }
                const auto* reflection =
                    reinterpret_cast<const GLSLCprogramReflectionHeader*>(
                        base + header.genericHeader.common.dataOffset);
                have_reflection = parse_reflection_bindings_from_header(
                    reflection,
                    base,
                    &reflection_bindings);
                break;
            }
        }
        if (out_bindings)
        {
            ProgramBindings final_bindings = {};
            if (have_glsl_bindings)
            {
                final_bindings = glsl_bindings;
            }
            if (have_reflection)
            {
                auto apply_binding = [](int& dst, int src) {
                    if (src >= 0)
                    {
                        dst = src;
                    }
                };
                apply_binding(final_bindings.pls_color,
                              reflection_bindings.pls_color);
                apply_binding(final_bindings.pls_clip,
                              reflection_bindings.pls_clip);
                apply_binding(final_bindings.pls_scratch,
                              reflection_bindings.pls_scratch);
                apply_binding(final_bindings.pls_coverage,
                              reflection_bindings.pls_coverage);
                if (!have_glsl_bindings)
                {
                    final_bindings = reflection_bindings;
                }
            }
            *out_bindings = final_bindings;
#if RIVE_NVN_ENABLE_REFLECTION_LOGS
            {
                static bool s_logged_final_bindings = false;
                if (!s_logged_final_bindings)
                {
                    const char* source =
                        have_reflection ? "reflection" :
                        (have_glsl_bindings ? "glsl" : "fallback");
                    debug_log(
                        "[rive nvn] final PLS bindings color=%d clip=%d scratch=%d coverage=%d (source=%s)",
                        final_bindings.pls_color,
                        final_bindings.pls_clip,
                        final_bindings.pls_scratch,
                        final_bindings.pls_coverage,
                        source);
                    s_logged_final_bindings = true;
                }
            }
#endif
        }
        if (!have_glsl_bindings && !have_reflection)
        {
            static bool s_logged_reflection_missing = false;
            if (!s_logged_reflection_missing)
            {
                debug_log(
                    "[rive nvn] shader reflection missing (bind logs may be incomplete)");
                s_logged_reflection_missing = true;
            }
        }
#if RIVE_NVN_ENABLE_REFLECTION_LOGS
        {
            static bool s_logged_reflection_status = false;
            if (!s_logged_reflection_status)
            {
                debug_log(
                    "[rive nvn] reflection present=%d section=%d",
                    have_reflection ? 1 : 0,
                    compile_object.reflectionSection ? 1 : 0);
                s_logged_reflection_status = true;
            }
        }
#endif
        ShaderBinary vertex_binary;
        ShaderBinary fragment_binary;
        bool have_vertex =
            extract_shader_binary(output, NVN_SHADER_STAGE_VERTEX, &vertex_binary);
        bool have_fragment =
            extract_shader_binary(output, NVN_SHADER_STAGE_FRAGMENT, &fragment_binary);

        if (have_vertex)
        {
            out_binaries.push_back(std::move(vertex_binary));
        }
        if (have_fragment)
        {
            out_binaries.push_back(std::move(fragment_binary));
        }
        if (have_vertex && have_fragment)
        {
            static bool s_logged_compile_ok = false;
            if (!s_logged_compile_ok)
            {
                debug_log("[rive] glslc compile ok ignoreBindings=%u debugInfo=%d",
                          static_cast<unsigned int>(
                              output->optionFlags.ignoreBindings),
                          static_cast<int>(output->optionFlags.outputDebugInfo));
                s_logged_compile_ok = true;
            }
        }

        glslc_api.finalize(&compile_object);
        return have_vertex && have_fragment;
    }

    bool build_program(nvn_api::Device* device,
                       const RiveNVNAllocator& allocator,
                       const std::vector<ShaderBinary>& binaries)
    {
        static constexpr size_t kShaderAlignment = 0x100;
        static constexpr size_t kPoolAlignment = 0x1000;
        static const nvn_api::MemoryPoolFlags kShaderPoolFlags =
            nvn_api::MemoryPoolFlags::CPU_UNCACHED |
            nvn_api::MemoryPoolFlags::GPU_CACHED |
            nvn_api::MemoryPoolFlags::SHADER_CODE;

        if (binaries.empty())
        {
            return false;
        }

        m_allocator = allocator;

        size_t code_pool_size = 1024;
        size_t control_size = 0;
        for (const auto& stage : binaries)
        {
            code_pool_size += align_up(stage.code.size(), kShaderAlignment);
            control_size += align_up(stage.control.size(), kShaderAlignment);
        }

        m_control_memory_size = align_up(control_size, kShaderAlignment);
        m_control_memory =
            alloc_memory(m_control_memory_size, kShaderAlignment, allocator);
        if (!m_control_memory)
        {
            return false;
        }

        m_code_memory_size = align_up(code_pool_size, kPoolAlignment);
        m_code_memory =
            alloc_memory(m_code_memory_size, kPoolAlignment, allocator);
        if (!m_code_memory)
        {
            return false;
        }

        nvn_api::MemoryPoolBuilder pool_builder;
        pool_builder.SetDefaults();
        pool_builder.SetDevice(device);
        pool_builder.SetFlags(kShaderPoolFlags);
        pool_builder.SetStorage(m_code_memory, m_code_memory_size);
        if (!m_code_pool.Initialize(&pool_builder))
        {
            return false;
        }
        m_code_pool_initialized = true;

        m_program = std::make_unique<nvn_api::Program>();
        if (!m_program->Initialize(device))
        {
            return false;
        }

        void* code_ptr = m_code_pool.Map();
        size_t code_offset = 0;
        size_t control_offset = 0;
        uint32_t stage_bits = 0;

        nvn_api::BufferBuilder buffer_builder;
        buffer_builder.SetDefaults().SetDevice(device);

        for (const auto& stage : binaries)
        {
            if (stage.code.empty() || stage.control.empty())
            {
                continue;
            }

            const size_t code_size = stage.code.size();
            const size_t control_size = stage.control.size();

            std::memcpy(static_cast<uint8_t*>(code_ptr) + code_offset,
                        stage.code.data(),
                        code_size);
            std::memcpy(static_cast<uint8_t*>(m_control_memory) + control_offset,
                        stage.control.data(),
                        control_size);

            buffer_builder.SetStorage(&m_code_pool,
                                      static_cast<ptrdiff_t>(code_offset),
                                      code_size);
            auto buffer = std::make_unique<nvn_api::Buffer>();
            if (!buffer->Initialize(&buffer_builder))
            {
                return false;
            }

            nvn_api::ShaderData data = {};
            data.control =
                static_cast<uint8_t*>(m_control_memory) + control_offset;
            data.data = buffer->GetAddress();

            stage_bits |= 1u << static_cast<uint32_t>(stage.stage);
            m_shader_data.push_back(data);
            m_code_buffers.push_back(std::move(buffer));

            m_code_pool.FlushMappedRange(static_cast<ptrdiff_t>(code_offset),
                                         code_size);

            code_offset += align_up(code_size, kShaderAlignment);
            control_offset += align_up(control_size, kShaderAlignment);
        }

        m_stage_bits = static_cast<nvn_api::ShaderStageBits>(stage_bits);
        return m_program->SetShaders(static_cast<int>(m_shader_data.size()),
                                     m_shader_data.data());
    }

    RiveNVNAllocator m_allocator = {};
    std::unique_ptr<nvn_api::Program> m_program;
    nvn_api::ShaderStageBits m_stage_bits = static_cast<nvn_api::ShaderStageBits>(0);
    nvn_api::MemoryPool m_code_pool;
    bool m_code_pool_initialized = false;
    void* m_code_memory = nullptr;
    size_t m_code_memory_size = 0;
    void* m_control_memory = nullptr;
    size_t m_control_memory_size = 0;
    std::vector<std::unique_ptr<nvn_api::Buffer>> m_code_buffers;
    std::vector<nvn_api::ShaderData> m_shader_data;
    ProgramBindings m_bindings;
};

enum class ProgramStage
{
    vertex,
    fragment,
};

static void append_shader_feature_defines(std::vector<const char*>& defines,
                                          rive::gpu::ShaderFeatures features)
{
    for (size_t i = 0; i < rive::gpu::kShaderFeatureCount; ++i)
    {
        rive::gpu::ShaderFeatures feature =
            static_cast<rive::gpu::ShaderFeatures>(1 << i);
        if (features & feature)
        {
            defines.push_back(rive::gpu::GetShaderFeatureGLSLName(feature));
        }
    }
}

static void append_shader_misc_defines(std::vector<const char*>& defines,
                                       rive::gpu::ShaderMiscFlags miscFlags)
{
    if (miscFlags & rive::gpu::ShaderMiscFlags::fixedFunctionColorOutput)
    {
        defines.push_back(GLSL_FIXED_FUNCTION_COLOR_OUTPUT);
    }
    if (miscFlags & rive::gpu::ShaderMiscFlags::clockwiseFill)
    {
        defines.push_back(GLSL_CLOCKWISE_FILL);
    }
    if (miscFlags & rive::gpu::ShaderMiscFlags::borrowedCoveragePass)
    {
        defines.push_back(GLSL_BORROWED_COVERAGE_PASS);
    }
}

static void append_draw_type_defines(std::vector<const char*>& defines,
                                     rive::gpu::nvn::ShaderStage stage,
                                     rive::gpu::DrawType drawType,
                                     rive::gpu::nvn::AtlasTextureType atlasTextureType,
                                     rive::gpu::ShaderMiscFlags miscFlags)
{
    switch (drawType)
    {
        case rive::gpu::DrawType::midpointFanPatches:
        case rive::gpu::DrawType::midpointFanCenterAAPatches:
        case rive::gpu::DrawType::outerCurvePatches:
        case rive::gpu::DrawType::msaaStrokes:
        case rive::gpu::DrawType::msaaMidpointFanBorrowedCoverage:
        case rive::gpu::DrawType::msaaMidpointFans:
        case rive::gpu::DrawType::msaaMidpointFanStencilReset:
        case rive::gpu::DrawType::msaaMidpointFanPathsStencil:
        case rive::gpu::DrawType::msaaMidpointFanPathsCover:
        case rive::gpu::DrawType::msaaOuterCubics:
            if (stage == rive::gpu::nvn::ShaderStage::vertex)
            {
                defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);
            }
            defines.push_back(GLSL_DRAW_PATH);
            break;
        case rive::gpu::DrawType::interiorTriangulation:
            defines.push_back(GLSL_DRAW_INTERIOR_TRIANGLES);
            break;
        case rive::gpu::DrawType::atlasBlit:
            defines.push_back(GLSL_ATLAS_BLIT);
            switch (atlasTextureType)
            {
                case rive::gpu::nvn::AtlasTextureType::r32uiFloatBits:
                    defines.push_back(GLSL_ATLAS_TEXTURE_R32UI_FLOAT_BITS);
                    break;
                case rive::gpu::nvn::AtlasTextureType::r32iFixedPoint:
                    defines.push_back(GLSL_ATLAS_TEXTURE_R32I_FIXED_POINT);
                    break;
                case rive::gpu::nvn::AtlasTextureType::rgba8:
                    defines.push_back(GLSL_ATLAS_TEXTURE_RGBA8_UNORM);
                    break;
                case rive::gpu::nvn::AtlasTextureType::r32f:
                case rive::gpu::nvn::AtlasTextureType::r16f:
                    break;
            }
            break;
        case rive::gpu::DrawType::imageRect:
            defines.push_back(GLSL_DRAW_IMAGE);
            defines.push_back(GLSL_DRAW_IMAGE_RECT);
            break;
        case rive::gpu::DrawType::imageMesh:
            defines.push_back(GLSL_DRAW_IMAGE);
            defines.push_back(GLSL_DRAW_IMAGE_MESH);
            break;
        case rive::gpu::DrawType::renderPassInitialize:
            defines.push_back(GLSL_INITIALIZE_PLS);
            defines.push_back(GLSL_DRAW_RENDER_TARGET_UPDATE_BOUNDS);
            if (miscFlags & rive::gpu::ShaderMiscFlags::storeColorClear)
            {
                defines.push_back(GLSL_STORE_COLOR_CLEAR);
            }
            if (miscFlags & rive::gpu::ShaderMiscFlags::swizzleColorBGRAToRGBA)
            {
                defines.push_back(GLSL_SWIZZLE_COLOR_BGRA_TO_RGBA);
            }
            break;
        case rive::gpu::DrawType::renderPassResolve:
            defines.push_back(GLSL_DRAW_RENDER_TARGET_UPDATE_BOUNDS);
            defines.push_back(GLSL_RESOLVE_PLS);
            if (miscFlags & rive::gpu::ShaderMiscFlags::coalescedResolveAndTransfer)
            {
                defines.push_back(GLSL_COALESCED_PLS_RESOLVE_AND_TRANSFER);
            }
            break;
        case rive::gpu::DrawType::msaaStencilClipReset:
            break;
    }
}

static std::string build_program_source(
    ProgramStage stage,
    const std::vector<const char*>& defines,
    const std::vector<const char*>& sources,
    const rive::gpu::PlatformFeatures& platform_features)
{
    std::ostringstream shader;
    shader << "#version 460\n";
    shader << "#define " << GLSL_GLSL_VERSION << " 460\n";
    shader << "#define " << (stage == ProgramStage::vertex ? GLSL_VERTEX
                                                           : GLSL_FRAGMENT)
           << "\n";

    if (platform_features.avoidFlatVaryings)
    {
        shader << "#define " << GLSL_OPTIONALLY_FLAT << "\n";
    }
    else
    {
        shader << "#define " << GLSL_OPTIONALLY_FLAT << " flat\n";
    }

    if (platform_features.framebufferBottomUp)
    {
        shader << "#define " << GLSL_FRAMEBUFFER_BOTTOM_UP << " true\n";
    }

    for (const char* define_name : defines)
    {
        shader << "#define " << define_name << " true\n";
    }

    shader << rive::gpu::glsl::glsl << "\n";
    shader << rive::gpu::glsl::constants << "\n";
    shader << rive::gpu::glsl::common << "\n";

    for (const char* source : sources)
    {
        shader << source << "\n";
    }

    return shader.str();
}

static bool build_msaa_program_sources(
    const rive::gpu::nvn::ShaderBuildParams& params,
    const rive::gpu::PlatformFeatures& platform_features,
    rive::gpu::nvn::ProgramSources* out_sources)
{
    if (!out_sources)
    {
        return false;
    }

    std::vector<const char*> base_defines;
    base_defines.reserve(32);
    append_shader_misc_defines(base_defines, params.miscFlags);
    append_shader_feature_defines(base_defines, params.shaderFeatures);
    base_defines.push_back(GLSL_RENDER_MODE_MSAA);
#if RIVE_NVN_NEEDS_GAMMA_CORRECTION
    base_defines.push_back(GLSL_NEEDS_GAMMA_CORRECTION);
    static bool s_logged_gamma = false;
    if (!s_logged_gamma)
    {
        debug_log("[rive] NVN MSAA gamma correction enabled");
        s_logged_gamma = true;
    }
#endif
    if (!params.caps.supportsShaderStorageBuffers)
    {
        base_defines.push_back(GLSL_DISABLE_SHADER_STORAGE_BUFFERS);
    }
    if (params.caps.needsFloatingPointTessellationTexture)
    {
        base_defines.push_back(GLSL_TESS_TEXTURE_FLOATING_POINT);
    }
    if (params.caps.isMali)
    {
        base_defines.push_back(GLSL_GL_RENDERER_MALI);
    }

    std::vector<const char*> vertex_defines = base_defines;
    std::vector<const char*> fragment_defines = base_defines;
    append_draw_type_defines(vertex_defines,
                             rive::gpu::nvn::ShaderStage::vertex,
                             params.drawType,
                             params.atlasTextureType,
                             params.miscFlags);
    append_draw_type_defines(fragment_defines,
                             rive::gpu::nvn::ShaderStage::fragment,
                             params.drawType,
                             params.atlasTextureType,
                             params.miscFlags);

    std::vector<const char*> vertex_sources;
    std::vector<const char*> fragment_sources;

    switch (params.drawType)
    {
        case rive::gpu::DrawType::msaaStrokes:
        case rive::gpu::DrawType::msaaMidpointFanBorrowedCoverage:
        case rive::gpu::DrawType::msaaMidpointFans:
        case rive::gpu::DrawType::msaaMidpointFanStencilReset:
        case rive::gpu::DrawType::msaaMidpointFanPathsStencil:
        case rive::gpu::DrawType::msaaMidpointFanPathsCover:
        case rive::gpu::DrawType::msaaOuterCubics:
        case rive::gpu::DrawType::interiorTriangulation:
        case rive::gpu::DrawType::atlasBlit:
            vertex_sources.push_back(rive::gpu::glsl::draw_path_common);
            vertex_sources.push_back(rive::gpu::glsl::draw_path_vert);
            fragment_sources.push_back(rive::gpu::glsl::draw_path_common);
            fragment_sources.push_back(rive::gpu::glsl::draw_path_vert);
            if (params.shaderFeatures & rive::gpu::ShaderFeatures::ENABLE_ADVANCED_BLEND)
            {
                fragment_sources.push_back(rive::gpu::glsl::advanced_blend);
            }
            fragment_sources.push_back(rive::gpu::glsl::draw_msaa_object_frag);
            break;

        case rive::gpu::DrawType::msaaStencilClipReset:
            vertex_sources.push_back(rive::gpu::glsl::stencil_draw);
            fragment_sources.push_back(rive::gpu::glsl::stencil_draw);
            break;

        case rive::gpu::DrawType::imageMesh:
            vertex_sources.push_back(rive::gpu::glsl::draw_image_mesh_vert);
            fragment_sources.push_back(rive::gpu::glsl::draw_image_mesh_vert);
            if (params.shaderFeatures & rive::gpu::ShaderFeatures::ENABLE_ADVANCED_BLEND)
            {
                fragment_sources.push_back(rive::gpu::glsl::advanced_blend);
            }
            fragment_sources.push_back(rive::gpu::glsl::draw_msaa_object_frag);
            break;

        case rive::gpu::DrawType::midpointFanPatches:
        case rive::gpu::DrawType::midpointFanCenterAAPatches:
        case rive::gpu::DrawType::outerCurvePatches:
        case rive::gpu::DrawType::imageRect:
        case rive::gpu::DrawType::renderPassInitialize:
        case rive::gpu::DrawType::renderPassResolve:
            return false;
    }

    out_sources->vertex = build_program_source(ProgramStage::vertex,
                                               vertex_defines,
                                               vertex_sources,
                                               platform_features);
    out_sources->fragment = build_program_source(ProgramStage::fragment,
                                                 fragment_defines,
                                                 fragment_sources,
                                                 platform_features);
    return true;
}

static nvn_api::BlendEquation to_nvn_blend_equation(rive::gpu::BlendEquation eq)
{
    switch (eq)
    {
        case rive::gpu::BlendEquation::max:
            return nvn_api::BlendEquation::MAX;
        case rive::gpu::BlendEquation::plus:
        case rive::gpu::BlendEquation::srcOver:
            return nvn_api::BlendEquation::ADD;
        case rive::gpu::BlendEquation::none:
        default:
            return nvn_api::BlendEquation::ADD;
    }
}

static void blend_factors_for_equation(rive::gpu::BlendEquation eq,
                                       nvn_api::BlendFunc* src,
                                       nvn_api::BlendFunc* dst)
{
    if (!src || !dst)
    {
        return;
    }
    switch (eq)
    {
        case rive::gpu::BlendEquation::plus:
            *src = nvn_api::BlendFunc::ONE;
            *dst = nvn_api::BlendFunc::ONE;
            break;
        case rive::gpu::BlendEquation::max:
            *src = nvn_api::BlendFunc::ONE;
            *dst = nvn_api::BlendFunc::ONE;
            break;
        case rive::gpu::BlendEquation::srcOver:
            *src = nvn_api::BlendFunc::ONE;
            *dst = nvn_api::BlendFunc::ONE_MINUS_SRC_ALPHA;
            break;
        case rive::gpu::BlendEquation::none:
        default:
            *src = nvn_api::BlendFunc::ONE;
            *dst = nvn_api::BlendFunc::ZERO;
            break;
    }
}

static nvn_api::StencilOp to_nvn_stencil_op(rive::gpu::StencilOp op)
{
    switch (op)
    {
        case rive::gpu::StencilOp::keep:
            return nvn_api::StencilOp::KEEP;
        case rive::gpu::StencilOp::replace:
            return nvn_api::StencilOp::REPLACE;
        case rive::gpu::StencilOp::zero:
            return nvn_api::StencilOp::ZERO;
        case rive::gpu::StencilOp::decrClamp:
            return nvn_api::StencilOp::DECR;
        case rive::gpu::StencilOp::incrWrap:
            return nvn_api::StencilOp::INCR_WRAP;
        case rive::gpu::StencilOp::decrWrap:
            return nvn_api::StencilOp::DECR_WRAP;
    }
    return nvn_api::StencilOp::KEEP;
}

static nvn_api::StencilFunc to_nvn_stencil_func(rive::gpu::StencilCompareOp op)
{
    switch (op)
    {
        case rive::gpu::StencilCompareOp::less:
            return nvn_api::StencilFunc::LESS;
        case rive::gpu::StencilCompareOp::equal:
            return nvn_api::StencilFunc::EQUAL;
        case rive::gpu::StencilCompareOp::lessOrEqual:
            return nvn_api::StencilFunc::LEQUAL;
        case rive::gpu::StencilCompareOp::notEqual:
            return nvn_api::StencilFunc::NOTEQUAL;
        case rive::gpu::StencilCompareOp::always:
            return nvn_api::StencilFunc::ALWAYS;
    }
    return nvn_api::StencilFunc::ALWAYS;
}

static nvn_api::Face to_nvn_cull_face(rive::gpu::CullFace cull)
{
    switch (cull)
    {
        case rive::gpu::CullFace::none:
            return nvn_api::Face::NONE;
        case rive::gpu::CullFace::clockwise:
            return nvn_api::Face::FRONT;
        case rive::gpu::CullFace::counterclockwise:
            return nvn_api::Face::BACK;
    }
    return nvn_api::Face::NONE;
}

static void apply_pipeline_state(nvn_api::CommandBuffer* command_buffer,
                                 const rive::gpu::PipelineState& state,
                                 int sample_count)
{
    if (!command_buffer)
    {
        return;
    }

    nvn_api::BlendState blend_state;
    blend_state.SetDefaults().SetBlendTarget(0);

    nvn_api::ColorState color_state;
    color_state.SetDefaults();

    nvn_api::ChannelMaskState mask_state;
    mask_state.SetDefaults();

    nvn_api::DepthStencilState depth_state;
    depth_state.SetDefaults();

    nvn_api::PolygonState polygon_state;
    polygon_state.SetDefaults();

    nvn_api::MultisampleState multisample_state;
    multisample_state.SetDefaults();

    depth_state.SetDepthTestEnable(state.depthTestEnabled);
    depth_state.SetDepthWriteEnable(state.depthWriteEnabled);
    depth_state.SetDepthFunc(state.depthTestEnabled ? nvn_api::DepthFunc::LESS
                                                    : nvn_api::DepthFunc::ALWAYS);

    depth_state.SetStencilTestEnable(state.stencilTestEnabled);
    if (state.stencilTestEnabled)
    {
        const rive::gpu::StencilFaceOps& front_ops = state.stencilFrontOps;
        const rive::gpu::StencilFaceOps& back_ops =
            state.stencilDoubleSided ? state.stencilFrontOps
                                     : state.stencilBackOps;
        depth_state.SetStencilFunc(nvn_api::Face::FRONT,
                                   to_nvn_stencil_func(front_ops.compareOp));
        depth_state.SetStencilFunc(nvn_api::Face::BACK,
                                   to_nvn_stencil_func(back_ops.compareOp));
        depth_state.SetStencilOp(nvn_api::Face::FRONT,
                                 to_nvn_stencil_op(front_ops.failOp),
                                 to_nvn_stencil_op(front_ops.depthFailOp),
                                 to_nvn_stencil_op(front_ops.passOp));
        depth_state.SetStencilOp(nvn_api::Face::BACK,
                                 to_nvn_stencil_op(back_ops.failOp),
                                 to_nvn_stencil_op(back_ops.depthFailOp),
                                 to_nvn_stencil_op(back_ops.passOp));

        command_buffer->SetStencilValueMask(nvn_api::Face::FRONT_AND_BACK,
                                            state.stencilCompareMask);
        command_buffer->SetStencilMask(nvn_api::Face::FRONT_AND_BACK,
                                       state.stencilWriteMask);
        command_buffer->SetStencilRef(nvn_api::Face::FRONT_AND_BACK,
                                      state.stencilReference);
    }

    polygon_state.SetCullFace(to_nvn_cull_face(state.cullFace));
    polygon_state.SetFrontFace(nvn_api::FrontFace::CW);

    if (state.blendEquation == rive::gpu::BlendEquation::none)
    {
        color_state.SetBlendEnable(0, false);
    }
    else
    {
        nvn_api::BlendFunc src = nvn_api::BlendFunc::ONE;
        nvn_api::BlendFunc dst = nvn_api::BlendFunc::ZERO;
        blend_factors_for_equation(state.blendEquation, &src, &dst);
        blend_state.SetBlendEquation(to_nvn_blend_equation(state.blendEquation),
                                     to_nvn_blend_equation(state.blendEquation));
        blend_state.SetBlendFunc(src, dst, src, dst);
        color_state.SetBlendEnable(0, true);
    }

    mask_state.SetChannelMask(0,
                              state.colorWriteEnabled,
                              state.colorWriteEnabled,
                              state.colorWriteEnabled,
                              state.colorWriteEnabled);

    if (sample_count > 1)
    {
        multisample_state.SetMultisampleEnable(true);
        multisample_state.SetSamples(sample_count);
    }
    else
    {
        multisample_state.SetMultisampleEnable(false);
    }

    command_buffer->BindBlendState(&blend_state);
    command_buffer->BindColorState(&color_state);
    command_buffer->BindChannelMaskState(&mask_state);
    command_buffer->BindDepthStencilState(&depth_state);
    command_buffer->BindPolygonState(&polygon_state);
    command_buffer->BindMultisampleState(&multisample_state);
}
} // namespace

class RenderTargetNVN : public RiveRenderTarget
{
public:
    RenderTargetNVN(uint32_t width,
                    uint32_t height,
                    void* colorTexture,
                    void* depthTexture,
                    uint32_t sampleCount) :
        RiveRenderTarget(width, height),
        m_colorTexture(colorTexture),
        m_depthTexture(depthTexture),
        m_sampleCount(sampleCount)
    {}

    void* colorTexture() const { return m_colorTexture; }
    void* depthTexture() const { return m_depthTexture; }
    uint32_t sampleCount() const { return m_sampleCount; }

private:
    void* m_colorTexture = nullptr;
    void* m_depthTexture = nullptr;
    uint32_t m_sampleCount = 0;
};

namespace rive::gpu
{
using nvn::AtlasTextureType;
using nvn::ShaderBuildParams;

class RenderContextNVNImpl;

class RenderBufferNVN : public LITE_RTTI_OVERRIDE(RenderBuffer, RenderBufferNVN)
{
public:
    RenderBufferNVN(RenderBufferType type,
                    RenderBufferFlags flags,
                    size_t sizeInBytes,
                    const RiveNVNAllocator& allocator) :
        lite_rtti_override(type, flags, sizeInBytes),
        m_data(sizeInBytes),
        m_gpuBuffer(allocator)
    {}

    const uint8_t* data() const { return m_data.data(); }
    size_t size() const { return m_data.size(); }
    size_t gpuSize() const { return m_gpuBuffer.size(); }
    nvn_api::BufferAddress address(size_t offset = 0) const
    {
        return m_gpuBuffer.address(offset);
    }

    bool upload(nvn_api::Device* device)
    {
        if (!device)
        {
            return false;
        }
        if (!m_dirty && m_gpuBuffer.size() >= m_data.size())
        {
            return true;
        }

        static const nvn_api::MemoryPoolFlags kBufferFlags =
            nvn_api::MemoryPoolFlags::CPU_UNCACHED |
            nvn_api::MemoryPoolFlags::GPU_CACHED;
        if (!m_gpuBuffer.upload(device,
                                m_data.data(),
                                m_data.size(),
                                kBufferFlags))
        {
            return false;
        }
        m_dirty = false;
        return true;
    }

protected:
    void* onMap() override { return m_data.data(); }
    void onUnmap() override { m_dirty = true; }

private:
    std::vector<uint8_t> m_data;
    NVNGpuBuffer m_gpuBuffer;
    bool m_dirty = true;
};

class TextureNVN : public Texture
{
public:
    TextureNVN(uint32_t width, uint32_t height, const uint8_t* data) :
        Texture(width, height)
    {
        if (data)
        {
            m_pixels.assign(data, data + width * height * 4);
        }
    }

    bool ensureUploaded(RenderContextNVNImpl& context);
    nvn_api::TextureHandle handle() const { return m_resource.handle; }
    const nvn_api::TextureView* view() const { return &m_resource.view; }
    int textureId() const { return m_resource.texture_id; }
    bool uploaded() const { return m_uploaded; }

private:
    friend class RenderContextNVNImpl;

    std::vector<uint8_t> m_pixels;
    NVNTextureResource m_resource;
    bool m_uploaded = false;
};

class RenderContextNVNImpl : public RenderContextImpl
{
    friend class TextureNVN;

public:
    static constexpr size_t kBufferRingSize = RIVE_NVN_BUFFER_RING_SIZE;

    RenderContextNVNImpl(void* device,
                         void* queue,
                         uint32_t maxTextureSize,
                         bool clipSpaceBottomUp,
                         bool framebufferBottomUp,
                         const RiveNVNAllocator* allocator) :
        m_device(device), m_queue(queue)
    {
        m_allocator = make_allocator(allocator);
        m_glslcAllocator = make_glslc_allocator(allocator);
        {
            static bool s_logged_glslc_alloc = false;
            if (!s_logged_glslc_alloc)
            {
                debug_log("[rive] glslc allocator=%s debug_level=%d",
#if RIVE_NVN_GLSLC_USE_DEFAULT_ALLOC
                          "system",
#else
                          "rive",
#endif
                          static_cast<int>(RIVE_NVN_GLSLC_DEBUG_LEVEL));
                s_logged_glslc_alloc = true;
            }
        }
        resolve_glslc_api(&m_glslcApi);
        m_flushUniformBuffer.setAllocator(m_allocator);
        m_imageDrawUniformBuffer.setAllocator(m_allocator);
        m_pathBuffer.setAllocator(m_allocator);
        m_paintBuffer.setAllocator(m_allocator);
        m_paintAuxBuffer.setAllocator(m_allocator);
        m_contourBuffer.setAllocator(m_allocator);
        m_gradSpanBuffer.setAllocator(m_allocator);
        m_tessVertexSpanBuffer.setAllocator(m_allocator);
        m_triangleVertexBuffer.setAllocator(m_allocator);
        m_coverageBuffer.setAllocator(m_allocator);
        for (auto& buffer : m_flushUniformGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_imageDrawUniformGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_pathGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_paintGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_paintAuxGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_contourGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_gradSpanGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_tessSpanGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_triangleGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        for (auto& buffer : m_coverageGpu)
        {
            buffer.setAllocator(m_allocator);
        }
        m_patchVertexGpu.setAllocator(m_allocator);
        m_patchIndexGpu.setAllocator(m_allocator);
        m_tessSpanIndexGpu.setAllocator(m_allocator);
        m_imageRectVertexGpu.setAllocator(m_allocator);
        m_imageRectIndexGpu.setAllocator(m_allocator);

        // Disable PLS on NVN; force MSAA path instead.
#if RIVE_NVN_DISABLE_PLS
        m_platformFeatures.supportsAtomicMode = false;
        m_platformFeatures.supportsRasterOrderingMode = false;
#else
        m_platformFeatures.supportsAtomicMode = true;
        m_platformFeatures.supportsRasterOrderingMode = false;
#endif
        m_platformFeatures.supportsClockwiseMode = false;
        m_platformFeatures.supportsClockwiseFixedFunctionMode = false;
        m_platformFeatures.supportsClockwiseAtomicMode = false;
        m_platformFeatures.clipSpaceBottomUp = clipSpaceBottomUp;
        m_platformFeatures.framebufferBottomUp = framebufferBottomUp;
        if (maxTextureSize > 0)
        {
            m_platformFeatures.maxTextureSize = maxTextureSize;
        }
#if defined(__SWITCH__)
        int supports_interlock = 0;
        if (auto* nvn_device = reinterpret_cast<nvn_api::Device*>(m_device))
        {
            nvn_device->GetInteger(
                nvn_api::DeviceInfo::SUPPORTS_FRAGMENT_SHADER_INTERLOCK,
                &supports_interlock);
        }
        m_supportsFragmentShaderInterlock = supports_interlock != 0;
        debug_log("[rive] fragment shader interlock support=%d",
                  m_supportsFragmentShaderInterlock ? 1 : 0);
#endif
#if RIVE_NVN_DISABLE_PLS
        debug_log("[rive] NVN PLS disabled; forcing MSAA rendering path");
#endif
#if RIVE_NVN_ENABLE_RASTER_ORDERING
        debug_log("[rive] raster ordering support enabled");
#endif
    }

    rcp<RenderBuffer> makeRenderBuffer(RenderBufferType type,
                                       RenderBufferFlags flags,
                                       size_t sizeInBytes) override
    {
        return make_rcp<RenderBufferNVN>(type, flags, sizeInBytes, m_allocator);
    }

    rcp<Texture> makeImageTexture(uint32_t width,
                                  uint32_t height,
                                  uint32_t mipLevelCount,
                                  const uint8_t imageDataRGBAPremul[]) override
    {
        (void)mipLevelCount;
        return make_rcp<TextureNVN>(width, height, imageDataRGBAPremul);
    }

    void resizeFlushUniformBuffer(size_t sizeInBytes) override
    {
        m_flushUniformBuffer.resize(sizeInBytes);
    }
    void resizeImageDrawUniformBuffer(size_t sizeInBytes) override
    {
        m_imageDrawUniformBuffer.resize(sizeInBytes);
    }
    void resizePathBuffer(size_t sizeInBytes,
                          gpu::StorageBufferStructure) override
    {
        m_pathBuffer.resize(sizeInBytes);
    }
    void resizePaintBuffer(size_t sizeInBytes,
                           gpu::StorageBufferStructure) override
    {
        m_paintBuffer.resize(sizeInBytes);
    }
    void resizePaintAuxBuffer(size_t sizeInBytes,
                              gpu::StorageBufferStructure) override
    {
        m_paintAuxBuffer.resize(sizeInBytes);
    }
    void resizeContourBuffer(size_t sizeInBytes,
                             gpu::StorageBufferStructure) override
    {
        m_contourBuffer.resize(sizeInBytes);
    }
    void resizeGradSpanBuffer(size_t sizeInBytes) override
    {
        m_gradSpanBuffer.resize(sizeInBytes);
    }
    void resizeTessVertexSpanBuffer(size_t sizeInBytes) override
    {
        m_tessVertexSpanBuffer.resize(sizeInBytes);
    }
    void resizeTriangleVertexBuffer(size_t sizeInBytes) override
    {
        m_triangleVertexBuffer.resize(sizeInBytes);
    }

    void* mapFlushUniformBuffer(size_t mapSizeInBytes) override
    {
        m_flushUniformBuffer.resize(mapSizeInBytes);
        return m_flushUniformBuffer.data();
    }
    void* mapImageDrawUniformBuffer(size_t mapSizeInBytes) override
    {
        m_imageDrawUniformBuffer.resize(mapSizeInBytes);
        return m_imageDrawUniformBuffer.data();
    }
    void* mapPathBuffer(size_t mapSizeInBytes) override
    {
        m_pathBuffer.resize(mapSizeInBytes);
        return m_pathBuffer.data();
    }
    void* mapPaintBuffer(size_t mapSizeInBytes) override
    {
        m_paintBuffer.resize(mapSizeInBytes);
        return m_paintBuffer.data();
    }
    void* mapPaintAuxBuffer(size_t mapSizeInBytes) override
    {
        m_paintAuxBuffer.resize(mapSizeInBytes);
        return m_paintAuxBuffer.data();
    }
    void* mapContourBuffer(size_t mapSizeInBytes) override
    {
        m_contourBuffer.resize(mapSizeInBytes);
        return m_contourBuffer.data();
    }
    void* mapGradSpanBuffer(size_t mapSizeInBytes) override
    {
        m_gradSpanBuffer.resize(mapSizeInBytes);
        return m_gradSpanBuffer.data();
    }
    void* mapTessVertexSpanBuffer(size_t mapSizeInBytes) override
    {
        m_tessVertexSpanBuffer.resize(mapSizeInBytes);
        return m_tessVertexSpanBuffer.data();
    }
    void* mapTriangleVertexBuffer(size_t mapSizeInBytes) override
    {
        m_triangleVertexBuffer.resize(mapSizeInBytes);
        return m_triangleVertexBuffer.data();
    }

    void unmapFlushUniformBuffer(size_t) override {}
    void unmapImageDrawUniformBuffer(size_t) override {}
    void unmapPathBuffer(size_t) override {}
    void unmapPaintBuffer(size_t) override {}
    void unmapPaintAuxBuffer(size_t) override {}
    void unmapContourBuffer(size_t) override {}
    void unmapGradSpanBuffer(size_t) override {}
    void unmapTessVertexSpanBuffer(size_t) override {}
    void unmapTriangleVertexBuffer(size_t) override {}

    void resizeGradientTexture(uint32_t width, uint32_t height) override
    {
        m_gradientTextureWidth = width;
        m_gradientTextureHeight = height;
    }
    void resizeTessellationTexture(uint32_t width, uint32_t height) override
    {
        m_tessellationTextureWidth = width;
        m_tessellationTextureHeight = height;
    }
    void resizeAtlasTexture(uint32_t width, uint32_t height) override
    {
        m_atlasTextureWidth = width;
        m_atlasTextureHeight = height;
    }
    void resizeTransientPLSBacking(uint32_t width,
                                   uint32_t height,
                                   uint32_t planeCount) override
    {
        m_plsTransientBackingWidth = width;
        m_plsTransientBackingHeight = height;
        m_plsTransientBackingPlaneCount = planeCount;
    }
    void resizeAtomicCoverageBacking(uint32_t width, uint32_t height) override
    {
        m_atomicCoverageWidth = width;
        m_atomicCoverageHeight = height;
    }
    void resizeCoverageBuffer(size_t sizeInBytes) override
    {
        m_coverageBuffer.resize(sizeInBytes);
    }

    void prepareToFlush(uint64_t nextFrameNumber,
                        uint64_t safeFrameNumber) override
    {
        m_currentFrameNumber = nextFrameNumber;
        m_safeFrameNumber = safeFrameNumber;
        if constexpr (kBufferRingSize > 1)
        {
            m_bufferRingIndex =
                static_cast<int>(nextFrameNumber % kBufferRingSize);
        }
        else
        {
            m_bufferRingIndex = 0;
        }
    }

    void flush(const gpu::FlushDescriptor& desc) override
    {
        if (!m_device || !m_queue)
        {
            return;
        }

        auto* render_target =
            static_cast<RenderTargetNVN*>(desc.renderTarget);
        if (!render_target)
        {
            return;
        }

        auto* command_buffer =
            reinterpret_cast<nvn_api::CommandBuffer*>(desc.externalCommandBuffer);
        if (!command_buffer)
        {
            return;
        }

        static bool s_logged_build = false;
        if (!s_logged_build)
        {
            debug_log("[rive] renderer build %s %s", __DATE__, __TIME__);
            s_logged_build = true;
        }
        prewarm_shaders();

        static size_t s_last_draw_count = static_cast<size_t>(-1);
        static size_t s_last_atlas_fill_count = static_cast<size_t>(-1);
        static size_t s_last_atlas_stroke_count = static_cast<size_t>(-1);
        const size_t draw_count = desc.drawList ? desc.drawList->count() : 0;
        if (draw_count != s_last_draw_count ||
            desc.atlasFillBatchCount != s_last_atlas_fill_count ||
            desc.atlasStrokeBatchCount != s_last_atlas_stroke_count)
        {
            size_t init_count = 0;
            size_t resolve_count = 0;
            size_t patch_count = 0;
            size_t msaa_count = 0;
            size_t tri_count = 0;
            size_t atlas_count = 0;
            size_t image_count = 0;
            size_t other_count = 0;
            if (desc.drawList)
            {
                for (const DrawBatch& batch : *desc.drawList)
                {
                    switch (batch.drawType)
                    {
                        case DrawType::renderPassInitialize:
                            ++init_count;
                            break;
                        case DrawType::renderPassResolve:
                            ++resolve_count;
                            break;
                        case DrawType::imageRect:
                        case DrawType::imageMesh:
                            ++image_count;
                            break;
                        case DrawType::atlasBlit:
                            ++atlas_count;
                            break;
                        case DrawType::interiorTriangulation:
                            ++tri_count;
                            break;
                        case DrawType::msaaStrokes:
                        case DrawType::msaaMidpointFanBorrowedCoverage:
                        case DrawType::msaaMidpointFans:
                        case DrawType::msaaMidpointFanStencilReset:
                        case DrawType::msaaMidpointFanPathsStencil:
                        case DrawType::msaaMidpointFanPathsCover:
                        case DrawType::msaaOuterCubics:
                        case DrawType::msaaStencilClipReset:
                            ++msaa_count;
                            break;
                        case DrawType::midpointFanPatches:
                        case DrawType::midpointFanCenterAAPatches:
                        case DrawType::outerCurvePatches:
                            ++patch_count;
                            break;
                        default:
                            ++other_count;
                            break;
                    }
                }
            }
            debug_log(
                "[rive] flush drawList=%zu atlas_fill=%zu atlas_stroke=%zu interlock=%d msaa=%d fixed_color=%d load=%d",
                draw_count,
                desc.atlasFillBatchCount,
                desc.atlasStrokeBatchCount,
                static_cast<int>(desc.interlockMode),
                static_cast<int>(desc.msaaSampleCount),
                desc.fixedFunctionColorOutput ? 1 : 0,
                static_cast<int>(desc.colorLoadAction));
            debug_log(
                "[rive] draw_types init=%zu resolve=%zu patch=%zu msaa=%zu tri=%zu atlas=%zu image=%zu other=%zu",
                init_count,
                resolve_count,
                patch_count,
                msaa_count,
                tri_count,
                atlas_count,
                image_count,
                other_count);
            s_last_draw_count = draw_count;
            s_last_atlas_fill_count = desc.atlasFillBatchCount;
            s_last_atlas_stroke_count = desc.atlasStrokeBatchCount;
        }

        auto* device = reinterpret_cast<nvn_api::Device*>(m_device);
        if (!ensure_descriptor_pools(device))
        {
            static bool s_logged_flush_descriptor_fail = false;
            if (!s_logged_flush_descriptor_fail)
            {
                debug_log("[rive] flush abort: descriptor pools");
                s_logged_flush_descriptor_fail = true;
            }
            return;
        }
        const int sampler_id = ensure_default_sampler(device);
        frame_log("[rive] flush step: sampler id=%d", sampler_id);
        if (sampler_id < 0)
        {
            static bool s_logged_flush_sampler_fail = false;
            if (!s_logged_flush_sampler_fail)
            {
                debug_log("[rive] flush abort: default sampler");
                s_logged_flush_sampler_fail = true;
            }
            return;
        }
        else
        {
            static bool s_logged_default_sampler = false;
            if (!s_logged_default_sampler)
            {
                frame_log("[rive] default sampler ok");
                s_logged_default_sampler = true;
            }
        }
        {
            static int s_flush_step_seq = 0;
            if (s_flush_step_seq < 5)
            {
                frame_log("[rive] flush step seq=%d pre-geometry",
                          s_flush_step_seq);
            }
            ++s_flush_step_seq;
        }
        if (!ensure_geometry(device))
        {
            static bool s_logged_flush_geometry_fail = false;
            if (!s_logged_flush_geometry_fail)
            {
                debug_log("[rive] flush abort: geometry");
                s_logged_flush_geometry_fail = true;
            }
            return;
        }
        {
            static int s_flush_step_geometry_ok = 0;
            if (s_flush_step_geometry_ok < 5)
            {
                frame_log("[rive] flush step seq=%d geometry ok",
                          s_flush_step_geometry_ok);
            }
            ++s_flush_step_geometry_ok;
        }
        {
            static bool s_logged_vertex_enter = false;
            if (!s_logged_vertex_enter)
            {
                frame_log("[rive] flush step: vertex states enter");
                s_logged_vertex_enter = true;
            }
        }
        static bool s_skip_vertex_states = false;
        if (s_skip_vertex_states)
        {
            if (!m_vertexStatesInitialized)
            {
                m_vertexStatesInitialized = true;
            }
            static bool s_logged_vertex_skip = false;
            if (!s_logged_vertex_skip)
            {
                frame_log("[rive] flush step: vertex states skipped");
                s_logged_vertex_skip = true;
            }
        }
        else
        {
            init_vertex_states();
            static bool s_logged_vertex_ok = false;
            if (!s_logged_vertex_ok)
            {
                frame_log("[rive] flush step: vertex states ok");
                s_logged_vertex_ok = true;
            }
        }

        frame_log("[rive] flush step: buffers enter");
        if (!upload_resource_buffers(desc, device))
        {
            static bool s_logged_flush_buffers_fail = false;
            if (!s_logged_flush_buffers_fail)
            {
                debug_log("[rive] flush abort: resource buffers");
                s_logged_flush_buffers_fail = true;
            }
            return;
        }
        {
            static bool s_logged_buffers_ok = false;
            if (!s_logged_buffers_ok)
            {
                frame_log("[rive] flush step: buffers ok");
                s_logged_buffers_ok = true;
            }
        }
        if (!ensure_resource_textures(desc, device))
        {
            static bool s_logged_flush_textures_fail = false;
            if (!s_logged_flush_textures_fail)
            {
                debug_log("[rive] flush abort: resource textures");
                s_logged_flush_textures_fail = true;
            }
            return;
        }
        {
            static bool s_logged_textures_ok = false;
            if (!s_logged_textures_ok)
            {
                frame_log("[rive] flush step: textures ok");
                s_logged_textures_ok = true;
            }
        }

#if !RIVE_NVN_DISABLE_PLS
        static int s_pls_width = -1;
        static int s_pls_height = -1;
        static unsigned long long s_pls_color_img = 0;
        static unsigned long long s_pls_clip_img = 0;
        static unsigned long long s_pls_scratch_img = 0;
        static unsigned long long s_pls_coverage_img = 0;
        const int pls_width = m_plsColorTexture.width;
        const int pls_height = m_plsColorTexture.height;
        const unsigned long long color_img =
            static_cast<unsigned long long>(m_plsColorTexture.image_handle);
        const unsigned long long clip_img =
            static_cast<unsigned long long>(m_plsClipTexture.image_handle);
        const unsigned long long scratch_img =
            static_cast<unsigned long long>(m_plsScratchTexture.image_handle);
        const unsigned long long coverage_img =
            static_cast<unsigned long long>(m_plsCoverageTexture.image_handle);
        if (s_pls_width != pls_width ||
            s_pls_height != pls_height ||
            s_pls_color_img != color_img ||
            s_pls_clip_img != clip_img ||
            s_pls_scratch_img != scratch_img ||
            s_pls_coverage_img != coverage_img)
        {
            debug_log(
                "[rive] pls images color=0x%llx fmt=%d clip=0x%llx fmt=%d scratch=0x%llx fmt=%d coverage=0x%llx fmt=%d size=%dx%d",
                color_img,
                static_cast<int>(m_plsColorTexture.format),
                clip_img,
                static_cast<int>(m_plsClipTexture.format),
                scratch_img,
                static_cast<int>(m_plsScratchTexture.format),
                coverage_img,
                static_cast<int>(m_plsCoverageTexture.format),
                pls_width,
                pls_height);
            s_pls_width = pls_width;
            s_pls_height = pls_height;
            s_pls_color_img = color_img;
            s_pls_clip_img = clip_img;
            s_pls_scratch_img = scratch_img;
            s_pls_coverage_img = coverage_img;
        }
#endif

        command_buffer->SetRenderEnable(true);
        command_buffer->SetRasterizerDiscard(false);
        command_buffer->SetTexturePool(&m_texturePool);
        command_buffer->SetSamplerPool(&m_samplerPool);
        command_buffer->Barrier(nvn_api::BarrierBits::INVALIDATE_TEXTURE_DESCRIPTOR);

        render_color_ramp(desc, command_buffer);
        render_tessellation(desc, command_buffer);
        render_atlas(desc, command_buffer);
        // Ensure render-to-texture outputs are visible for subsequent sampling.
        command_buffer->Barrier(texture_visibility_barrier_bits());

        auto* color_texture =
            reinterpret_cast<nvn_api::Texture*>(render_target->colorTexture());
        auto* depth_texture =
            reinterpret_cast<nvn_api::Texture*>(render_target->depthTexture());
        if (!color_texture)
        {
            return;
        }

        nvn_api::TextureView color_view;
        init_texture_view(&color_view, color_texture);
        nvn_api::TextureView* color_views[] = {&color_view};
        nvn_api::Texture* colors[] = {color_texture};

        nvn_api::TextureView depth_view;
        nvn_api::TextureView* depth_view_ptr = nullptr;
        if (depth_texture)
        {
            init_texture_view(&depth_view, depth_texture);
            depth_view_ptr = &depth_view;
        }

        command_buffer->SetRenderTargets(1,
                                         colors,
                                         color_views,
                                         depth_texture,
                                         depth_view_ptr);

        const int width = static_cast<int>(render_target->width());
        const int height = static_cast<int>(render_target->height());
        command_buffer->SetViewport(0, 0, width, height);
        command_buffer->SetScissor(0, 0, width, height);

        if (desc.colorLoadAction == LoadAction::clear)
        {
            float clear_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
            rive::UnpackColorToRGBA32F(desc.colorClearValue, clear_color);
            command_buffer->ClearColor(
                0,
                clear_color,
                nvn_api::ClearColorMask(nvn_api::ClearColorMask::RGBA));
            if (depth_texture)
            {
                command_buffer->ClearDepthStencil(
                    desc.depthClearValue,
                    true,
                    desc.stencilClearValue,
                    0xFF);
            }
        }

#if !RIVE_NVN_DISABLE_PLS
        const bool has_pls_images =
            m_plsColorTexture.initialized ||
            m_plsClipTexture.initialized ||
            m_plsScratchTexture.initialized ||
            m_plsCoverageTexture.initialized;
        if (has_pls_images)
        {
            nvn_api::CopyRegion region = {};
            region.xoffset = 0;
            region.yoffset = 0;
            region.zoffset = 0;
            region.width = width;
            region.height = height;
            region.depth = 1;

            if (!desc.fixedFunctionColorOutput &&
                m_plsColorTexture.initialized)
            {
                if (desc.colorLoadAction == LoadAction::clear)
                {
                    float clear_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
                    rive::UnpackColorToRGBA32FPremul(desc.colorClearValue,
                                                     clear_color);
                    command_buffer->ClearTexture(
                        &m_plsColorTexture.texture,
                        &m_plsColorTexture.view,
                        &region,
                        clear_color,
                        nvn_api::ClearColorMask(nvn_api::ClearColorMask::RGBA));
                }
                else if (desc.colorLoadAction ==
                         LoadAction::preserveRenderTarget)
                {
                    nvn_api::TextureView rt_view;
                    init_texture_view(&rt_view, color_texture);
                    command_buffer->CopyTextureToTexture(
                        color_texture,
                        &rt_view,
                        &region,
                        &m_plsColorTexture.texture,
                        &m_plsColorTexture.view,
                        &region,
                        nvn_api::CopyFlags::NONE);
                }
            }

            if (m_plsCoverageTexture.initialized)
            {
                uint32_t coverage_clear = desc.coverageClearValue;
#ifdef RIVE_NVN_PLS_COVERAGE_CLEAR_VALUE
                coverage_clear =
                    static_cast<uint32_t>(RIVE_NVN_PLS_COVERAGE_CLEAR_VALUE);
                static bool s_logged_pls_coverage_clear_override = false;
                if (!s_logged_pls_coverage_clear_override)
                {
                    debug_log(
                        "[rive] pls coverage clear override=0x%08x (was 0x%08x)",
                        static_cast<unsigned int>(coverage_clear),
                        static_cast<unsigned int>(desc.coverageClearValue));
                    s_logged_pls_coverage_clear_override = true;
                }
#endif
                uint32_t clear_values[4] = {coverage_clear, 0, 0, 0};
                command_buffer->ClearTextureui(
                    &m_plsCoverageTexture.texture,
                    &m_plsCoverageTexture.view,
                    &region,
                    clear_values,
                    nvn_api::ClearColorMask(nvn_api::ClearColorMask::RGBA));
            }

            if (m_plsClipTexture.initialized)
            {
#if RIVE_NVN_PLS_CLIP_RGBA8
                const float clear_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
                command_buffer->ClearTexture(
                    &m_plsClipTexture.texture,
                    &m_plsClipTexture.view,
                    &region,
                    clear_color,
                    nvn_api::ClearColorMask(nvn_api::ClearColorMask::RGBA));
#else
                constexpr uint32_t clear_values[4] = {0, 0, 0, 0};
                command_buffer->ClearTextureui(&m_plsClipTexture.texture,
                                               &m_plsClipTexture.view,
                                               &region,
                                               clear_values,
                                               nvn_api::ClearColorMask(
                                                   nvn_api::ClearColorMask::RGBA));
#endif
            }

            if (m_plsScratchTexture.initialized)
            {
                const float clear_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
                command_buffer->ClearTexture(
                    &m_plsScratchTexture.texture,
                    &m_plsScratchTexture.view,
                    &region,
                    clear_color,
                    nvn_api::ClearColorMask(nvn_api::ClearColorMask::RGBA));
            }

            // ClearTexture/CopyTextureToTexture use the 3D engine; ensure writes
            // are visible before the PLS images are accessed by shaders.
            command_buffer->Barrier(pls_storage_barrier_bits());
        }
#endif

        compile_draw_list_shaders(desc);
        execute_draw_list(desc, command_buffer);

#if !RIVE_NVN_DISABLE_PLS
        if (!desc.fixedFunctionColorOutput &&
            m_plsColorTexture.initialized)
        {
            static bool s_logged_pls_copy = false;
            if (!s_logged_pls_copy)
            {
                debug_log("[rive] pls resolve copy -> render target");
                s_logged_pls_copy = true;
            }
            nvn_api::CopyRegion region = {};
            region.xoffset = 0;
            region.yoffset = 0;
            region.zoffset = 0;
            region.width = width;
            region.height = height;
            region.depth = 1;

            nvn_api::TextureView dst_view;
            init_texture_view(&dst_view, color_texture);

            command_buffer->Barrier(pls_storage_barrier_bits());
            command_buffer->CopyTextureToTexture(
                &m_plsColorTexture.texture,
                &m_plsColorTexture.view,
                &region,
                color_texture,
                &dst_view,
                &region,
                nvn_api::CopyFlags::NONE);
            // Reset storage usage after a copy (emulators often track this as read-only).
            command_buffer->Barrier(pls_storage_barrier_bits());
        }
#endif
    }

    double secondsNow() const override
    {
#if RIVE_NVN_DISABLE_RESOURCE_TRIM
        return 0.0;
#else
        using clock = std::chrono::steady_clock;
        return std::chrono::duration<double>(
                   clock::now().time_since_epoch())
            .count();
#endif
    }

private:
    template <size_t N>
    NVNGpuBuffer& frame_buffer(std::array<NVNGpuBuffer, N>& ring)
    {
        static_assert(N >= 1, "Buffer ring size must be >= 1");
        return ring[m_bufferRingIndex];
    }

    template <size_t N>
    const NVNGpuBuffer& frame_buffer(
        const std::array<NVNGpuBuffer, N>& ring) const
    {
        static_assert(N >= 1, "Buffer ring size must be >= 1");
        return ring[m_bufferRingIndex];
    }

    bool ensure_descriptor_pools(nvn_api::Device* device);
    int ensure_default_sampler(nvn_api::Device* device);
    int ensure_sampler(const ImageSampler& sampler, nvn_api::Device* device);
    bool ensure_geometry(nvn_api::Device* device);
    void init_vertex_states();
    bool upload_resource_buffers(const gpu::FlushDescriptor& desc,
                                 nvn_api::Device* device);
    void bind_common_buffers(const gpu::FlushDescriptor& desc,
                             nvn_api::CommandBuffer* command_buffer);
    void bind_common_textures(nvn_api::CommandBuffer* command_buffer,
                              const ProgramBindings* bindings);
    void reset_bind_cache();
    bool ensure_resource_textures(const gpu::FlushDescriptor& desc,
                                  nvn_api::Device* device);
    void render_color_ramp(const gpu::FlushDescriptor& desc,
                           nvn_api::CommandBuffer* command_buffer);
    void render_tessellation(const gpu::FlushDescriptor& desc,
                             nvn_api::CommandBuffer* command_buffer);
    void render_atlas(const gpu::FlushDescriptor& desc,
                      nvn_api::CommandBuffer* command_buffer);
    void execute_draw_list(const gpu::FlushDescriptor& desc,
                           nvn_api::CommandBuffer* command_buffer);

    bool wants_coalesced_resolve(const gpu::FlushDescriptor& desc,
                                 const DrawBatch& batch) const
    {
        // NVN uses PLS storage textures; use a manual copy after resolve.
        (void)desc;
        (void)batch;
        return false;
    }

    ShaderBuildParams make_shader_params(const gpu::FlushDescriptor& desc,
                                         const DrawBatch& batch) const
    {
        ShaderBuildParams params = {};
        params.drawType = batch.drawType;
        params.interlockMode = desc.interlockMode;

        ShaderFeatures allowed =
            ShaderFeaturesMaskFor(batch.drawType, desc.interlockMode);
        ShaderFeatures combined = batch.shaderFeatures |
                                  desc.combinedShaderFeatures;
        params.shaderFeatures = combined & allowed;

#if RIVE_NVN_DISABLE_PLS
        if (desc.interlockMode == gpu::InterlockMode::msaa)
        {
            // NVN MSAA path: force fixed-function color output and avoid
            // advanced blend shaders (dstColor reads) to prevent black output.
            params.shaderFeatures &=
                ~(ShaderFeatures::ENABLE_ADVANCED_BLEND |
                  ShaderFeatures::ENABLE_HSL_BLEND_MODES);
            static bool s_logged_force_fixed_color = false;
            if (!s_logged_force_fixed_color)
            {
                debug_log(
                    "[rive] forcing fixed-function color output for NVN MSAA");
                s_logged_force_fixed_color = true;
            }
        }
#endif

        ShaderMiscFlags misc = batch.shaderMiscFlags;
        if (desc.fixedFunctionColorOutput)
        {
            misc |= ShaderMiscFlags::fixedFunctionColorOutput;
        }
#if RIVE_NVN_DISABLE_PLS
        if (desc.interlockMode == gpu::InterlockMode::msaa)
        {
            misc |= ShaderMiscFlags::fixedFunctionColorOutput;
        }
#endif
        if (wants_coalesced_resolve(desc, batch))
        {
            misc |= ShaderMiscFlags::coalescedResolveAndTransfer;
        }
        if (desc.clockwiseFillOverride)
        {
            misc |= ShaderMiscFlags::clockwiseFill;
        }
        params.miscFlags = misc;

        params.atlasTextureType = m_atlasTextureType;

        params.caps.avoidFlatVaryings = m_platformFeatures.avoidFlatVaryings;
        params.caps.supportsShaderStorageBuffers = true;
        params.caps.framebufferBottomUp = m_platformFeatures.framebufferBottomUp;
        params.caps.needsBaseInstanceUniform = false;
        params.caps.needsFloatingPointTessellationTexture = true;
        params.caps.isMali = false;
        params.caps.supportsFragmentShaderInterlock =
            m_supportsFragmentShaderInterlock;
        params.caps.supportsFragmentShaderInterlock =
            m_supportsFragmentShaderInterlock;
        return params;
    }

    const NvnShaderProgram* get_or_create_program(
        const ShaderBuildParams& params)
    {
        PipelineKey key;
        key.drawType = params.drawType;
        key.shaderFeatures = params.shaderFeatures;
        key.miscFlags = params.miscFlags;
        key.interlockMode = params.interlockMode;
        key.atlasTextureType = params.atlasTextureType;

        auto it = m_programCache.find(key);
        if (it != m_programCache.end())
        {
            return it->second.get();
        }

        rive::gpu::nvn::ProgramSources sources;
        bool built_sources = false;
        switch (params.interlockMode)
        {
            case gpu::InterlockMode::msaa:
                built_sources = build_msaa_program_sources(params,
                                                          m_platformFeatures,
                                                          &sources);
                break;
            case gpu::InterlockMode::atomics:
#if RIVE_NVN_DISABLE_PLS
                built_sources = false;
#else
                sources =
                    rive::gpu::nvn::BuildAtomicProgramSources(params, "460");
                built_sources = true;
#endif
                break;
            case gpu::InterlockMode::rasterOrdering:
            case gpu::InterlockMode::clockwise:
            case gpu::InterlockMode::clockwiseAtomic:
                built_sources = false;
                break;
        }
        if (!built_sources)
        {
            static bool s_logged_build_failure = false;
            if (!s_logged_build_failure)
            {
                debug_log("[rive] shader build skipped drawType=%d interlock=%d",
                          static_cast<int>(params.drawType),
                          static_cast<int>(params.interlockMode));
                s_logged_build_failure = true;
            }
            m_programCache.emplace(key, std::unique_ptr<NvnShaderProgram>());
            return nullptr;
        }
        if (kDumpShaders)
        {
            static int s_dumped = 0;
            if (s_dumped < 2)
            {
                char label[128];
                std::snprintf(label,
                              sizeof(label),
                              "drawType_%d_feat_%u_misc_%u_atlas_%d",
                              static_cast<int>(params.drawType),
                              static_cast<unsigned int>(params.shaderFeatures),
                              static_cast<unsigned int>(params.miscFlags),
                              static_cast<int>(params.atlasTextureType));
                dump_shader_source("program", "vert", sources.vertex.c_str());
                dump_shader_source("program", "frag", sources.fragment.c_str());
                s_dumped++;
            }
        }
        auto program = std::make_unique<NvnShaderProgram>();
        if (!program->initialize(reinterpret_cast<nvn_api::Device*>(m_device),
                                 m_allocator,
                                 m_glslcApi,
                                 m_glslcAllocator,
                                 sources.vertex.c_str(),
                                 sources.fragment.c_str()))
        {
            static bool s_logged_program_failure = false;
            if (!s_logged_program_failure)
            {
                debug_log(
                    "[rive] program init failed drawType=%d features=0x%x misc=0x%x atlas=%d",
                    static_cast<int>(params.drawType),
                    static_cast<unsigned int>(params.shaderFeatures),
                    static_cast<unsigned int>(params.miscFlags),
                    static_cast<int>(params.atlasTextureType));
                s_logged_program_failure = true;
            }
            m_programCache.emplace(key, std::unique_ptr<NvnShaderProgram>());
            return nullptr;
        }

        const NvnShaderProgram* ptr = program.get();
        m_programCache.emplace(key, std::move(program));
        return ptr;
    }

    void compile_draw_list_shaders(const gpu::FlushDescriptor& desc)
    {
        if (!desc.drawList)
        {
            return;
        }

        for (const DrawBatch& batch : *desc.drawList)
        {
            ShaderBuildParams params = make_shader_params(desc, batch);
            get_or_create_program(params);
        }

        // TODO: compile atlas fill/stroke programs when atlas batches exist.
    }

    void prewarm_shaders()
    {
        if (m_shader_prewarmed)
        {
            return;
        }
#if !RIVE_NVN_ENABLE_SHADER_PREWARM
        if (!m_logged_prewarm_unavailable)
        {
            debug_log("[rive] prewarm skipped: disabled");
            m_logged_prewarm_unavailable = true;
        }
        m_shader_prewarmed = true;
        return;
#endif
        if (!m_glslcApi.ready())
        {
            resolve_glslc_api(&m_glslcApi);
        }
        if (!m_glslcApi.ready())
        {
            if (!m_logged_prewarm_unavailable)
            {
                debug_log("[rive] prewarm skipped: glslc unavailable");
                m_logged_prewarm_unavailable = true;
            }
            return;
        }
        debug_log("[rive] prewarm shaders begin");

        if (!m_colorRampProgram.initialized())
        {
            std::vector<const char*> defines;
            defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);

            std::vector<const char*> sources;
            sources.push_back(rive::gpu::glsl::color_ramp);

            std::string vertex_source = build_program_source(
                ProgramStage::vertex,
                defines,
                sources,
                m_platformFeatures);
            std::string fragment_source = build_program_source(
                ProgramStage::fragment,
                defines,
                sources,
                m_platformFeatures);

            m_colorRampProgram.initialize(reinterpret_cast<nvn_api::Device*>(m_device),
                                          m_allocator,
                                          m_glslcApi,
                                          m_glslcAllocator,
                                          vertex_source.c_str(),
                                          fragment_source.c_str());
        }

        if (!m_tessellateProgram.initialized())
        {
            std::vector<const char*> defines;
            defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);

            std::vector<const char*> sources;
            sources.push_back(rive::gpu::glsl::bezier_utils);
            sources.push_back(rive::gpu::glsl::tessellate);

            std::string vertex_source = build_program_source(
                ProgramStage::vertex,
                defines,
                sources,
                m_platformFeatures);
            std::string fragment_source = build_program_source(
                ProgramStage::fragment,
                defines,
                sources,
                m_platformFeatures);

            m_tessellateProgram.initialize(reinterpret_cast<nvn_api::Device*>(m_device),
                                           m_allocator,
                                           m_glslcApi,
                                           m_glslcAllocator,
                                           vertex_source.c_str(),
                                           fragment_source.c_str());
        }

        if (!m_atlasFillProgram.initialized() ||
            !m_atlasStrokeProgram.initialized())
        {
            std::vector<const char*> base_defines;
            base_defines.push_back(GLSL_DRAW_PATH);
            base_defines.push_back(GLSL_ENABLE_FEATHER);
            base_defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);
            base_defines.push_back(GLSL_ATLAS_RENDER_TARGET_RGBA8_UNORM);

            std::vector<const char*> sources;
            sources.push_back(rive::gpu::glsl::draw_path_common);
            sources.push_back(rive::gpu::glsl::render_atlas);

            std::vector<const char*> defines = base_defines;
            defines.push_back(GLSL_ATLAS_FEATHERED_FILL);
            std::string fill_vertex = build_program_source(
                ProgramStage::vertex,
                defines,
                sources,
                m_platformFeatures);
            std::string fill_fragment = build_program_source(
                ProgramStage::fragment,
                defines,
                sources,
                m_platformFeatures);
            m_atlasFillProgram.initialize(reinterpret_cast<nvn_api::Device*>(m_device),
                                          m_allocator,
                                          m_glslcApi,
                                          m_glslcAllocator,
                                          fill_vertex.c_str(),
                                          fill_fragment.c_str());

            defines = base_defines;
            defines.push_back(GLSL_ATLAS_FEATHERED_STROKE);
            std::string stroke_vertex = build_program_source(
                ProgramStage::vertex,
                defines,
                sources,
                m_platformFeatures);
            std::string stroke_fragment = build_program_source(
                ProgramStage::fragment,
                defines,
                sources,
                m_platformFeatures);
            m_atlasStrokeProgram.initialize(
                reinterpret_cast<nvn_api::Device*>(m_device),
                m_allocator,
                m_glslcApi,
                m_glslcAllocator,
                stroke_vertex.c_str(),
                stroke_fragment.c_str());
        }

        ShaderBuildParams params = {};
        params.shaderFeatures = ShaderFeatures::NONE;
        params.miscFlags = ShaderMiscFlags::none;
        params.atlasTextureType = m_atlasTextureType;
        params.interlockMode = m_platformFeatures.supportsAtomicMode
                                   ? gpu::InterlockMode::atomics
                                   : gpu::InterlockMode::msaa;
        params.caps.avoidFlatVaryings = m_platformFeatures.avoidFlatVaryings;
        params.caps.supportsShaderStorageBuffers = true;
        params.caps.framebufferBottomUp = m_platformFeatures.framebufferBottomUp;
        params.caps.needsBaseInstanceUniform = false;
        params.caps.needsFloatingPointTessellationTexture = true;
        params.caps.isMali = false;

        if (params.interlockMode == gpu::InterlockMode::msaa)
        {
            static const DrawType kPrewarmDrawTypesMsaa[] = {
                DrawType::msaaStrokes,
                DrawType::msaaMidpointFanBorrowedCoverage,
                DrawType::msaaMidpointFans,
                DrawType::msaaMidpointFanStencilReset,
                DrawType::msaaMidpointFanPathsStencil,
                DrawType::msaaMidpointFanPathsCover,
                DrawType::msaaOuterCubics,
                DrawType::interiorTriangulation,
                DrawType::imageMesh,
                DrawType::atlasBlit,
                DrawType::msaaStencilClipReset,
            };
            for (DrawType draw_type : kPrewarmDrawTypesMsaa)
            {
                params.drawType = draw_type;
                get_or_create_program(params);
            }
        }
        else
        {
            static const DrawType kPrewarmDrawTypesAtomic[] = {
                DrawType::renderPassInitialize,
                DrawType::renderPassResolve,
                DrawType::midpointFanPatches,
                DrawType::midpointFanCenterAAPatches,
                DrawType::outerCurvePatches,
                DrawType::interiorTriangulation,
                DrawType::imageRect,
                DrawType::imageMesh,
                DrawType::atlasBlit,
            };
            for (DrawType draw_type : kPrewarmDrawTypesAtomic)
            {
                params.drawType = draw_type;
                get_or_create_program(params);
            }
        }

        debug_log("[rive] prewarm shaders done");
        m_shader_prewarmed = true;
    }

    void* m_device = nullptr;
    void* m_queue = nullptr;

    RiveNVNAllocator m_allocator = {};
    GlslCompilerApi m_glslcApi = {};
    GlslAllocatorState m_glslcAllocator = {};
    NVNBuffer m_flushUniformBuffer;
    NVNBuffer m_imageDrawUniformBuffer;
    NVNBuffer m_pathBuffer;
    NVNBuffer m_paintBuffer;
    NVNBuffer m_paintAuxBuffer;
    NVNBuffer m_contourBuffer;
    NVNBuffer m_gradSpanBuffer;
    NVNBuffer m_tessVertexSpanBuffer;
    NVNBuffer m_triangleVertexBuffer;
    NVNBuffer m_coverageBuffer;
    std::array<NVNGpuBuffer, kBufferRingSize> m_flushUniformGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_imageDrawUniformGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_pathGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_paintGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_paintAuxGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_contourGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_gradSpanGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_tessSpanGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_triangleGpu;
    std::array<NVNGpuBuffer, kBufferRingSize> m_coverageGpu;

    NVNGpuBuffer m_patchVertexGpu;
    NVNGpuBuffer m_patchIndexGpu;
    NVNGpuBuffer m_tessSpanIndexGpu;
    NVNGpuBuffer m_imageRectVertexGpu;
    NVNGpuBuffer m_imageRectIndexGpu;

    NVNTextureResource m_gradientTexture;
    NVNTextureResource m_tessTexture;
    NVNTextureResource m_atlasTexture;
    NVNTextureResource m_featherTexture;
    NVNTextureResource m_plsColorTexture;
    NVNTextureResource m_plsClipTexture;
    NVNTextureResource m_plsScratchTexture;
    NVNTextureResource m_plsCoverageTexture;

    nvn_api::MemoryPool m_descriptorPool;
    void* m_descriptorMemory = nullptr;
    size_t m_descriptorMemorySize = 0;
    size_t m_samplerBytes = 0;
    int m_textureDescriptorSize = 0;
    nvn_api::MemoryPool m_samplerDescriptorPool;
    nvn_api::MemoryPool m_textureDescriptorPool;
    void* m_samplerDescriptorMemory = nullptr;
    void* m_textureDescriptorMemory = nullptr;
    size_t m_samplerDescriptorMemorySize = 0;
    size_t m_textureDescriptorMemorySize = 0;
    uint64_t m_texturePoolGuardPre = 0;
    nvn_api::TexturePool m_texturePool;
    uint64_t m_texturePoolGuardPost = 0;
    uint64_t m_samplerPoolGuardPre = 0;
    nvn_api::SamplerPool m_samplerPool;
    uint64_t m_samplerPoolGuardPost = 0;
    bool m_descriptorPoolsInitialized = false;
    uint32_t m_descriptorPoolTestVersion = 0;
    int m_textureIdBase = 0;
    int m_samplerIdBase = 0;
    int m_texturePoolSize = 0;
    int m_samplerPoolSize = 0;
    int m_nextTextureId = 0;
    int m_nextSamplerId = 0;
    int m_defaultSamplerId = -1;
    std::vector<std::unique_ptr<nvn_api::Sampler>> m_samplers;

    std::array<nvn_api::TextureHandle, 32> m_boundTexturesVert = {};
    std::array<nvn_api::TextureHandle, 32> m_boundTexturesFrag = {};
    std::array<nvn_api::ImageHandle, 16> m_boundImagesFrag = {};

    bool m_vertexStatesInitialized = false;
    nvn_api::VertexAttribState m_patchAttribs[2];
    nvn_api::VertexStreamState m_patchStreams[1];
    nvn_api::VertexAttribState m_triangleAttribs[1];
    nvn_api::VertexStreamState m_triangleStreams[1];
    nvn_api::VertexAttribState m_gradAttribs[1];
    nvn_api::VertexStreamState m_gradStreams[1];
    nvn_api::VertexAttribState m_tessAttribs[4];
    nvn_api::VertexStreamState m_tessStreams[1];
    nvn_api::VertexAttribState m_imageRectAttribs[1];
    nvn_api::VertexStreamState m_imageRectStreams[1];
    nvn_api::VertexAttribState m_imageMeshAttribs[2];
    nvn_api::VertexStreamState m_imageMeshStreams[2];

    NvnShaderProgram m_colorRampProgram;
    NvnShaderProgram m_tessellateProgram;
    NvnShaderProgram m_atlasFillProgram;
    NvnShaderProgram m_atlasStrokeProgram;
    bool m_shader_prewarmed = false;
    bool m_logged_prewarm_unavailable = false;
    bool m_supportsFragmentShaderInterlock = false;

    uint32_t m_gradientTextureWidth = 0;
    uint32_t m_gradientTextureHeight = 0;
    uint32_t m_tessellationTextureWidth = 0;
    uint32_t m_tessellationTextureHeight = 0;
    uint32_t m_atlasTextureWidth = 0;
    uint32_t m_atlasTextureHeight = 0;
    uint32_t m_plsTransientBackingWidth = 0;
    uint32_t m_plsTransientBackingHeight = 0;
    uint32_t m_plsTransientBackingPlaneCount = 0;
    uint32_t m_atomicCoverageWidth = 0;
    uint32_t m_atomicCoverageHeight = 0;
    uint64_t m_currentFrameNumber = 0;
    uint64_t m_safeFrameNumber = 0;
    int m_bufferRingIndex = 0;

    AtlasTextureType m_atlasTextureType = AtlasTextureType::rgba8;
    std::unordered_map<PipelineKey, std::unique_ptr<NvnShaderProgram>, PipelineKeyHasher>
        m_programCache;
};

bool TextureNVN::ensureUploaded(RenderContextNVNImpl& context)
{
    if (m_uploaded)
    {
        return true;
    }

    auto* device = reinterpret_cast<nvn_api::Device*>(context.m_device);
    if (!device)
    {
        return false;
    }

    if (!context.ensure_descriptor_pools(device))
    {
        return false;
    }

    const int sampler_id = context.ensure_default_sampler(device);
    if (sampler_id < 0)
    {
        return false;
    }

    int texture_id = m_resource.texture_id;
    if (texture_id < 0)
    {
        texture_id = context.m_nextTextureId++;
    }

      static const nvn_api::MemoryPoolFlags kPoolFlags =
          nvn_api::MemoryPoolFlags::CPU_UNCACHED |
          nvn_api::MemoryPoolFlags::GPU_CACHED;
      static const nvn_api::MemoryPoolFlags kPlsPoolFlags =
          nvn_api::MemoryPoolFlags::CPU_NO_ACCESS |
          nvn_api::MemoryPoolFlags::GPU_CACHED;

    bool had_texture = m_resource.initialized;
    if (!m_resource.ensure(device,
                           context.m_allocator,
                           &context.m_texturePool,
                           texture_id,
                           sampler_id,
                           -1,
                           static_cast<int>(width()),
                           static_cast<int>(height()),
                           nvn_api::Format::RGBA8,
                           nvn_api::TextureFlags(0),
                           nvn_api::TextureTarget::TARGET_2D,
                           kPoolFlags,
                           true,
                           false))
    {
        return false;
    }

    if (!m_pixels.empty() && (!had_texture || !m_uploaded))
    {
        nvn_api::CopyRegion region = {};
        region.xoffset = 0;
        region.yoffset = 0;
        region.zoffset = 0;
        region.width = static_cast<int>(width());
        region.height = static_cast<int>(height());
        region.depth = 1;
        m_resource.texture.WriteTexels(&m_resource.view,
                                       &region,
                                       m_pixels.data());
    }

    m_uploaded = true;
    return true;
}

bool RenderContextNVNImpl::ensure_descriptor_pools(nvn_api::Device* device)
{
    const uint32_t test_version = rive_nvn_get_descriptor_pool_test_version();
    if (!device)
    {
        return false;
    }

    auto reset_descriptor_pools = [&]() {
        if (m_descriptorPoolsInitialized)
        {
            m_texturePool.Finalize();
            m_samplerPool.Finalize();
            m_descriptorPool.Finalize();
        }
        m_textureDescriptorPool.Finalize();
        m_samplerDescriptorPool.Finalize();
        free_memory(m_descriptorMemory, m_allocator);
        m_descriptorMemory = nullptr;
        m_descriptorMemorySize = 0;
        m_samplerBytes = 0;
        m_textureDescriptorSize = 0;
        m_descriptorPoolsInitialized = false;
        m_texturePoolSize = 0;
        m_samplerPoolSize = 0;
        m_textureIdBase = 0;
        m_samplerIdBase = 0;
        m_nextTextureId = 0;
        m_nextSamplerId = 0;
        m_defaultSamplerId = -1;
        m_samplers.clear();
    };

    if (m_descriptorPoolsInitialized &&
        m_descriptorPoolTestVersion != test_version)
    {
        reset_descriptor_pools();
    }
    if (m_descriptorPoolsInitialized)
    {
        return true;
    }
    if (m_descriptorMemory)
    {
        reset_descriptor_pools();
    }

    int texture_descriptor_size = 0;
    int sampler_descriptor_size = 0;
    int reserved_texture = 0;
    int reserved_sampler = 0;
    device->GetInteger(nvn_api::DeviceInfo::TEXTURE_DESCRIPTOR_SIZE,
                       &texture_descriptor_size);
    device->GetInteger(nvn_api::DeviceInfo::SAMPLER_DESCRIPTOR_SIZE,
                       &sampler_descriptor_size);
    device->GetInteger(nvn_api::DeviceInfo::RESERVED_TEXTURE_DESCRIPTORS,
                       &reserved_texture);
    device->GetInteger(nvn_api::DeviceInfo::RESERVED_SAMPLER_DESCRIPTORS,
                       &reserved_sampler);

    if (texture_descriptor_size <= 0)
    {
        texture_descriptor_size = 0x20;
    }
    if (sampler_descriptor_size <= 0)
    {
        sampler_descriptor_size = 0x20;
    }
    if (reserved_texture < 256)
    {
        reserved_texture = 256;
    }
    if (reserved_sampler < 256)
    {
        reserved_sampler = 256;
    }

    constexpr int kExtraDescriptors = 100;
    int texture_pool_count = reserved_texture + kExtraDescriptors;
    int sampler_pool_count = reserved_sampler + kExtraDescriptors;

    const size_t kPoolAlignment = 0x1000;
    size_t sampler_bytes =
        align_up(static_cast<size_t>(sampler_descriptor_size) *
                     static_cast<size_t>(sampler_pool_count),
                 kPoolAlignment);
    size_t texture_bytes =
        align_up(static_cast<size_t>(texture_descriptor_size) *
                     static_cast<size_t>(texture_pool_count),
                 kPoolAlignment);
    size_t total_bytes = sampler_bytes + texture_bytes;
    m_samplerBytes = sampler_bytes;
    m_textureDescriptorSize = texture_descriptor_size;

    m_descriptorMemory =
        alloc_memory(total_bytes, kPoolAlignment, m_allocator);
    if (!m_descriptorMemory)
    {
        return false;
    }
    m_descriptorMemorySize = total_bytes;
    std::memset(m_descriptorMemory, 0, total_bytes);

    nvn_api::MemoryPoolBuilder builder;
    builder.SetDefaults();
    builder.SetDevice(device);
    builder.SetFlags(nvn_api::MemoryPoolFlags::CPU_UNCACHED |
                nvn_api::MemoryPoolFlags::GPU_CACHED);
    builder.SetStorage(m_descriptorMemory, total_bytes);

    if (!m_descriptorPool.Initialize(&builder))
    {
        free_memory(m_descriptorMemory, m_allocator);
        m_descriptorMemory = nullptr;
        m_descriptorMemorySize = 0;
        return false;
    }

    if (!m_samplerPool.Initialize(&m_descriptorPool, 0, sampler_pool_count))
    {
        m_descriptorPool.Finalize();
        free_memory(m_descriptorMemory, m_allocator);
        m_descriptorMemory = nullptr;
        m_descriptorMemorySize = 0;
        return false;
    }

    if (!m_texturePool.Initialize(&m_descriptorPool,
                                  static_cast<ptrdiff_t>(sampler_bytes),
                                  texture_pool_count))
    {
        m_samplerPool.Finalize();
        m_descriptorPool.Finalize();
        free_memory(m_descriptorMemory, m_allocator);
        m_descriptorMemory = nullptr;
        m_descriptorMemorySize = 0;
        return false;
    }

    m_descriptorPoolsInitialized = true;
    m_descriptorPoolTestVersion = test_version;
    m_textureIdBase = reserved_texture;
    m_samplerIdBase = reserved_sampler;
    m_texturePoolSize = texture_pool_count;
    m_samplerPoolSize = sampler_pool_count;
    m_nextTextureId = m_textureIdBase;
    m_nextSamplerId = m_samplerIdBase;
    m_defaultSamplerId = -1;
    m_samplers.clear();
    m_samplers.resize(ImageSampler::MAX_SAMPLER_PERMUTATIONS);
    return true;
}

int RenderContextNVNImpl::ensure_default_sampler(nvn_api::Device* device)
{
    {
        static bool s_logged_default_sampler_enter = false;
        if (!s_logged_default_sampler_enter)
        {
            debug_log("[rive] ensure_default_sampler enter default_id=%d",
                      m_defaultSamplerId);
            s_logged_default_sampler_enter = true;
        }
    }
    if (m_defaultSamplerId >= 0)
    {
        return m_defaultSamplerId;
    }
    ImageSampler sampler = ImageSampler::LinearClamp();
    m_defaultSamplerId = ensure_sampler(sampler, device);
    {
        static bool s_logged_default_sampler_exit = false;
        if (!s_logged_default_sampler_exit)
        {
            debug_log("[rive] ensure_default_sampler exit default_id=%d",
                      m_defaultSamplerId);
            s_logged_default_sampler_exit = true;
        }
    }
    return m_defaultSamplerId;
}

int RenderContextNVNImpl::ensure_sampler(const ImageSampler& sampler,
                                         nvn_api::Device* device)
{
    if (!device)
    {
        return -1;
    }
    if (!ensure_descriptor_pools(device))
    {
        return -1;
    }

    const uint8_t key = sampler.asKey();
    if (key >= m_samplers.size())
    {
        return -1;
    }
    const int sampler_id = m_samplerIdBase + static_cast<int>(key);
    if (sampler_id >= m_samplerPoolSize)
    {
        return -1;
    }

    if (!m_samplers[key])
    {
        static bool s_logged_sampler_create = false;
        if (!s_logged_sampler_create)
        {
            debug_log("[rive] create sampler key=%u filter=%d wrap=%d/%d",
                      static_cast<unsigned int>(key),
                      static_cast<int>(sampler.filter),
                      static_cast<int>(sampler.wrapX),
                      static_cast<int>(sampler.wrapY));
            s_logged_sampler_create = true;
        }
        auto map_wrap = [](ImageWrap wrap) {
            switch (wrap)
            {
                case ImageWrap::repeat:
                    return nvn_api::WrapMode::REPEAT;
                case ImageWrap::mirror:
                    return nvn_api::WrapMode::MIRRORED_REPEAT;
                case ImageWrap::clamp:
                default:
                    return nvn_api::WrapMode::CLAMP_TO_EDGE;
            }
        };

        nvn_api::MinFilter min_filter = nvn_api::MinFilter::LINEAR;
        nvn_api::MagFilter mag_filter = nvn_api::MagFilter::LINEAR;
        if (sampler.filter == ImageFilter::nearest)
        {
            min_filter = nvn_api::MinFilter::NEAREST;
            mag_filter = nvn_api::MagFilter::NEAREST;
        }

        nvn_api::SamplerBuilder builder{};
        builder.SetDefaults();
        builder.SetDevice(device);
        builder.SetMinMagFilter(min_filter, mag_filter);
        builder.SetWrapMode(map_wrap(sampler.wrapX),
                         map_wrap(sampler.wrapY),
                         nvn_api::WrapMode::CLAMP_TO_EDGE);
        builder.SetLodBias(rive::gpu::MIP_MAP_LOD_BIAS);

        auto sampler_obj = std::make_unique<nvn_api::Sampler>();
        if (!sampler_obj->Initialize(&builder))
        {
            debug_log("[rive] sampler init failed key=%u",
                      static_cast<unsigned int>(key));
            return -1;
        }

        m_samplerPool.RegisterSampler(sampler_id, sampler_obj.get());
        debug_log("[rive] sampler registered key=%u id=%d",
                  static_cast<unsigned int>(key),
                  sampler_id);
        m_samplers[key] = std::move(sampler_obj);
    }

    return sampler_id;
}

bool RenderContextNVNImpl::ensure_geometry(nvn_api::Device* device)
{
    if (!device)
    {
        return false;
    }

    {
        static bool s_logged_geometry_enter = false;
        if (!s_logged_geometry_enter)
        {
            debug_log("[rive] ensure_geometry enter");
            s_logged_geometry_enter = true;
        }
    }
    static bool s_skip_geometry = false;
    if (s_skip_geometry)
    {
        static bool s_logged_skip_geometry = false;
        if (!s_logged_skip_geometry)
        {
            debug_log("[rive] ensure_geometry skipped");
            s_logged_skip_geometry = true;
        }
        return true;
    }
    if (m_patchVertexGpu.size() != 0 && m_patchIndexGpu.size() != 0 &&
        m_tessSpanIndexGpu.size() != 0 && m_imageRectVertexGpu.size() != 0 &&
        m_imageRectIndexGpu.size() != 0)
    {
        return true;
    }

    static PatchVertex s_patch_vertices[kPatchVertexBufferCount];
    static uint16_t s_patch_indices[kPatchIndexBufferCount];
    static bool s_patch_data_ready = false;
    if (!s_patch_data_ready)
    {
        debug_log("[rive] ensure_geometry generate patch data");
        GeneratePatchBufferData(s_patch_vertices, s_patch_indices);
        s_patch_data_ready = true;
        debug_log("[rive] ensure_geometry patch data ok");
    }

    static const nvn_api::MemoryPoolFlags kBufferFlags =
        nvn_api::MemoryPoolFlags::CPU_UNCACHED |
        nvn_api::MemoryPoolFlags::GPU_CACHED;

    {
        static bool s_logged_geometry_patch_vertices = false;
        if (!s_logged_geometry_patch_vertices)
        {
            debug_log("[rive] ensure_geometry upload patch vertices");
            s_logged_geometry_patch_vertices = true;
        }
    }
    if (!m_patchVertexGpu.upload(device,
                                 s_patch_vertices,
                                 sizeof(s_patch_vertices),
                                 kBufferFlags))
    {
        debug_log("[rive] ensure_geometry failed: patch vertices");
        return false;
    }
    debug_log("[rive] ensure_geometry patch vertices ok");
    {
        static bool s_logged_geometry_patch_indices = false;
        if (!s_logged_geometry_patch_indices)
        {
            debug_log("[rive] ensure_geometry upload patch indices");
            s_logged_geometry_patch_indices = true;
        }
    }
    if (!m_patchIndexGpu.upload(device,
                                s_patch_indices,
                                sizeof(s_patch_indices),
                                kBufferFlags))
    {
        debug_log("[rive] ensure_geometry failed: patch indices");
        return false;
    }
    debug_log("[rive] ensure_geometry patch indices ok");
    {
        static bool s_logged_geometry_tess_span = false;
        if (!s_logged_geometry_tess_span)
        {
            debug_log("[rive] ensure_geometry upload tess span indices");
            s_logged_geometry_tess_span = true;
        }
    }
    if (!m_tessSpanIndexGpu.upload(device,
                                   gpu::kTessSpanIndices,
                                   sizeof(gpu::kTessSpanIndices),
                                   kBufferFlags))
    {
        debug_log("[rive] ensure_geometry failed: tess span indices");
        return false;
    }
    debug_log("[rive] ensure_geometry tess span indices ok");
    {
        static bool s_logged_geometry_image_rect_vertices = false;
        if (!s_logged_geometry_image_rect_vertices)
        {
            debug_log("[rive] ensure_geometry upload image rect vertices");
            s_logged_geometry_image_rect_vertices = true;
        }
    }
    if (!m_imageRectVertexGpu.upload(device,
                                     gpu::kImageRectVertices,
                                     sizeof(gpu::kImageRectVertices),
                                     kBufferFlags))
    {
        debug_log("[rive] ensure_geometry failed: image rect vertices");
        return false;
    }
    debug_log("[rive] ensure_geometry image rect vertices ok");
    {
        static bool s_logged_geometry_image_rect_indices = false;
        if (!s_logged_geometry_image_rect_indices)
        {
            debug_log("[rive] ensure_geometry upload image rect indices");
            s_logged_geometry_image_rect_indices = true;
        }
    }
    if (!m_imageRectIndexGpu.upload(device,
                                    gpu::kImageRectIndices,
                                    sizeof(gpu::kImageRectIndices),
                                    kBufferFlags))
    {
        debug_log("[rive] ensure_geometry failed: image rect indices");
        return false;
    }
    debug_log("[rive] ensure_geometry image rect indices ok");

    {
        static bool s_logged_geometry_ok = false;
        if (!s_logged_geometry_ok)
        {
            debug_log("[rive] ensure_geometry ok");
            s_logged_geometry_ok = true;
        }
    }
    return true;
}

void RenderContextNVNImpl::init_vertex_states()
{
    {
        static bool s_logged_vertex_enter = false;
        if (!s_logged_vertex_enter)
        {
            debug_log("[rive] init_vertex_states enter");
            s_logged_vertex_enter = true;
        }
    }
    if (m_vertexStatesInitialized)
    {
        static bool s_logged_vertex_already = false;
        if (!s_logged_vertex_already)
        {
            debug_log("[rive] init_vertex_states already initialized");
            s_logged_vertex_already = true;
        }
        return;
    }

    debug_log("[rive] init_vertex_states patch");
    debug_log("[rive] init_vertex_states patch a0 defaults");
    m_patchAttribs[0].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32F, 0)
        .SetStreamIndex(0);
    debug_log("[rive] init_vertex_states patch a0 ok");
    debug_log("[rive] init_vertex_states patch a1 defaults");
    m_patchAttribs[1].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32F, sizeof(float) * 4)
        .SetStreamIndex(0);
    debug_log("[rive] init_vertex_states patch a1 ok");
    debug_log("[rive] init_vertex_states patch s0 defaults");
    m_patchStreams[0].SetDefaults()
        .SetStride(sizeof(PatchVertex))
        .SetDivisor(0);
    debug_log("[rive] init_vertex_states patch s0 ok");

    debug_log("[rive] init_vertex_states triangle");
    m_triangleAttribs[0].SetDefaults()
        .SetFormat(nvn_api::Format::RGB32F, 0)
        .SetStreamIndex(0);
    m_triangleStreams[0].SetDefaults()
        .SetStride(sizeof(gpu::TriangleVertex))
        .SetDivisor(0);

    debug_log("[rive] init_vertex_states gradient");
    m_gradAttribs[0].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32UI, 0)
        .SetStreamIndex(0);
    m_gradStreams[0].SetDefaults()
        .SetStride(sizeof(gpu::GradientSpan))
        .SetDivisor(1);

    debug_log("[rive] init_vertex_states tess");
    m_tessAttribs[0].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32F, 0)
        .SetStreamIndex(0);
    m_tessAttribs[1].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32F, sizeof(float) * 4)
        .SetStreamIndex(0);
    m_tessAttribs[2].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32F, sizeof(float) * 8)
        .SetStreamIndex(0);
    m_tessAttribs[3].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32UI, sizeof(float) * 12)
        .SetStreamIndex(0);
    m_tessStreams[0].SetDefaults()
        .SetStride(sizeof(gpu::TessVertexSpan))
        .SetDivisor(1);

    debug_log("[rive] init_vertex_states image rect");
    m_imageRectAttribs[0].SetDefaults()
        .SetFormat(nvn_api::Format::RGBA32F, 0)
        .SetStreamIndex(0);
    m_imageRectStreams[0].SetDefaults()
        .SetStride(sizeof(gpu::ImageRectVertex))
        .SetDivisor(0);

    debug_log("[rive] init_vertex_states image mesh");
    m_imageMeshAttribs[0].SetDefaults()
        .SetFormat(nvn_api::Format::RG32F, 0)
        .SetStreamIndex(0);
    m_imageMeshAttribs[1].SetDefaults()
        .SetFormat(nvn_api::Format::RG32F, 0)
        .SetStreamIndex(1);
    m_imageMeshStreams[0].SetDefaults()
        .SetStride(sizeof(float) * 2)
        .SetDivisor(0);
    m_imageMeshStreams[1].SetDefaults()
        .SetStride(sizeof(float) * 2)
        .SetDivisor(0);

    m_vertexStatesInitialized = true;
    debug_log("[rive] init_vertex_states ok");
}

bool RenderContextNVNImpl::upload_resource_buffers(
    const gpu::FlushDescriptor& desc,
    nvn_api::Device* device)
{
    if (!device)
    {
        return false;
    }

    static bool s_skip_resource_buffers = false;
    if (s_skip_resource_buffers)
    {
        static bool s_logged_skip = false;
        if (!s_logged_skip)
        {
            debug_log("[rive] upload_resource_buffers skipped");
            s_logged_skip = true;
        }
        return true;
    }

    static const nvn_api::MemoryPoolFlags kBufferFlags =
        nvn_api::MemoryPoolFlags::CPU_UNCACHED |
        nvn_api::MemoryPoolFlags::GPU_CACHED;

    auto& flush_gpu = frame_buffer(m_flushUniformGpu);
    auto& image_draw_gpu = frame_buffer(m_imageDrawUniformGpu);
    auto& path_gpu = frame_buffer(m_pathGpu);
    auto& paint_gpu = frame_buffer(m_paintGpu);
    auto& paint_aux_gpu = frame_buffer(m_paintAuxGpu);
    auto& contour_gpu = frame_buffer(m_contourGpu);
    auto& grad_span_gpu = frame_buffer(m_gradSpanGpu);
    auto& tess_span_gpu = frame_buffer(m_tessSpanGpu);
    auto& triangle_gpu = frame_buffer(m_triangleGpu);
    auto& coverage_gpu = frame_buffer(m_coverageGpu);

    if (m_flushUniformBuffer.size() > 0)
    {
        static bool s_logged_flush = false;
        if (!s_logged_flush)
        {
            debug_log("[rive] upload_resource_buffers flush size=%zu gpu=%p",
                      m_flushUniformBuffer.size(),
                      &flush_gpu);
            s_logged_flush = true;
        }
        if (!flush_gpu.upload(device,
                              m_flushUniformBuffer.data(),
                              m_flushUniformBuffer.size(),
                              kBufferFlags))
        {
            return false;
        }
    }
    if (m_imageDrawUniformBuffer.size() > 0)
    {
        static bool s_logged_image_draw = false;
        if (!s_logged_image_draw)
        {
            debug_log("[rive] upload_resource_buffers image_draw size=%zu gpu=%p",
                      m_imageDrawUniformBuffer.size(),
                      &image_draw_gpu);
            s_logged_image_draw = true;
        }
        if (!image_draw_gpu.upload(device,
                                   m_imageDrawUniformBuffer.data(),
                                   m_imageDrawUniformBuffer.size(),
                                   kBufferFlags))
        {
            return false;
        }
    }
    if (m_pathBuffer.size() > 0)
    {
        static bool s_logged_path = false;
        if (!s_logged_path)
        {
            debug_log("[rive] upload_resource_buffers path size=%zu gpu=%p",
                      m_pathBuffer.size(),
                      &path_gpu);
            s_logged_path = true;
        }
        if (!path_gpu.upload(device,
                             m_pathBuffer.data(),
                             m_pathBuffer.size(),
                             kBufferFlags))
        {
            return false;
        }
    }
    if (m_paintBuffer.size() > 0)
    {
        static bool s_logged_paint = false;
        if (!s_logged_paint)
        {
            debug_log("[rive] upload_resource_buffers paint size=%zu gpu=%p",
                      m_paintBuffer.size(),
                      &paint_gpu);
            s_logged_paint = true;
        }
        if (!paint_gpu.upload(device,
                              m_paintBuffer.data(),
                              m_paintBuffer.size(),
                              kBufferFlags))
        {
            return false;
        }
    }
    if (m_paintAuxBuffer.size() > 0)
    {
        static bool s_logged_paint_aux = false;
        if (!s_logged_paint_aux)
        {
            debug_log("[rive] upload_resource_buffers paint_aux size=%zu gpu=%p",
                      m_paintAuxBuffer.size(),
                      &paint_aux_gpu);
            s_logged_paint_aux = true;
        }
        if (!paint_aux_gpu.upload(device,
                                  m_paintAuxBuffer.data(),
                                  m_paintAuxBuffer.size(),
                                  kBufferFlags))
        {
            return false;
        }
    }
    if (m_contourBuffer.size() > 0)
    {
        static bool s_logged_contour = false;
        if (!s_logged_contour)
        {
            debug_log("[rive] upload_resource_buffers contour size=%zu gpu=%p",
                      m_contourBuffer.size(),
                      &contour_gpu);
            s_logged_contour = true;
        }
        if (!contour_gpu.upload(device,
                                m_contourBuffer.data(),
                                m_contourBuffer.size(),
                                kBufferFlags))
        {
            return false;
        }
    }
    if (m_gradSpanBuffer.size() > 0)
    {
        static bool s_logged_grad = false;
        if (!s_logged_grad)
        {
            debug_log("[rive] upload_resource_buffers grad_span size=%zu gpu=%p",
                      m_gradSpanBuffer.size(),
                      &grad_span_gpu);
            s_logged_grad = true;
        }
        if (!grad_span_gpu.upload(device,
                                  m_gradSpanBuffer.data(),
                                  m_gradSpanBuffer.size(),
                                  kBufferFlags))
        {
            return false;
        }
    }
    if (m_tessVertexSpanBuffer.size() > 0)
    {
        static bool s_logged_tess_span = false;
        if (!s_logged_tess_span)
        {
            debug_log("[rive] upload_resource_buffers tess_span size=%zu gpu=%p",
                      m_tessVertexSpanBuffer.size(),
                      &tess_span_gpu);
            s_logged_tess_span = true;
        }
        if (!tess_span_gpu.upload(device,
                                  m_tessVertexSpanBuffer.data(),
                                  m_tessVertexSpanBuffer.size(),
                                  kBufferFlags))
        {
            return false;
        }
    }
    if (desc.hasTriangleVertices && m_triangleVertexBuffer.size() > 0)
    {
        static bool s_logged_triangle = false;
        if (!s_logged_triangle)
        {
            debug_log("[rive] upload_resource_buffers triangle size=%zu gpu=%p",
                      m_triangleVertexBuffer.size(),
                      &triangle_gpu);
            s_logged_triangle = true;
        }
        if (!triangle_gpu.upload(device,
                                 m_triangleVertexBuffer.data(),
                                 m_triangleVertexBuffer.size(),
                                 kBufferFlags))
        {
            return false;
        }
    }
    if (m_coverageBuffer.size() > 0)
    {
        static bool s_logged_coverage = false;
        if (!s_logged_coverage)
        {
            debug_log("[rive] upload_resource_buffers coverage size=%zu gpu=%p",
                      m_coverageBuffer.size(),
                      &coverage_gpu);
            s_logged_coverage = true;
        }
        if (!coverage_gpu.upload(device,
                                 m_coverageBuffer.data(),
                                 m_coverageBuffer.size(),
                                 kBufferFlags))
        {
            return false;
        }
    }

    return true;
}

void RenderContextNVNImpl::bind_common_buffers(
    const gpu::FlushDescriptor& desc,
    nvn_api::CommandBuffer* command_buffer)
{
    if (!command_buffer)
    {
        return;
    }

    auto& flush_gpu = frame_buffer(m_flushUniformGpu);
    auto& path_gpu = frame_buffer(m_pathGpu);
    auto& paint_gpu = frame_buffer(m_paintGpu);
    auto& paint_aux_gpu = frame_buffer(m_paintAuxGpu);
    auto& contour_gpu = frame_buffer(m_contourGpu);
    auto& coverage_gpu = frame_buffer(m_coverageGpu);

    if (flush_gpu.size() >= sizeof(gpu::FlushUniforms))
    {
        nvn_api::BufferAddress address =
            flush_gpu.address(desc.flushUniformDataOffsetInBytes);
        command_buffer->BindUniformBuffer(nvn_api::ShaderStage::VERTEX,
                                          FLUSH_UNIFORM_BUFFER_IDX,
                                          address,
                                          sizeof(gpu::FlushUniforms));
        command_buffer->BindUniformBuffer(nvn_api::ShaderStage::FRAGMENT,
                                          FLUSH_UNIFORM_BUFFER_IDX,
                                          address,
                                          sizeof(gpu::FlushUniforms));
    }

    auto bind_storage = [&](int idx,
                            nvn_api::BufferAddress address,
                            size_t size) {
        command_buffer->BindStorageBuffer(nvn_api::ShaderStage::VERTEX,
                                          idx,
                                          address,
                                          size);
        command_buffer->BindStorageBuffer(nvn_api::ShaderStage::FRAGMENT,
                                          idx,
                                          address,
                                          size);
    };

    if (desc.pathCount > 0)
    {
        size_t size = desc.pathCount * sizeof(gpu::PathData);
        bind_storage(PATH_BUFFER_IDX,
                     path_gpu.address(desc.firstPath *
                                      sizeof(gpu::PathData)),
                     size);

        size = desc.pathCount * sizeof(gpu::PaintData);
        bind_storage(PAINT_BUFFER_IDX,
                     paint_gpu.address(desc.firstPaint *
                                       sizeof(gpu::PaintData)),
                     size);

        size = desc.pathCount * sizeof(gpu::PaintAuxData);
        bind_storage(PAINT_AUX_BUFFER_IDX,
                     paint_aux_gpu.address(desc.firstPaintAux *
                                           sizeof(gpu::PaintAuxData)),
                     size);
    }

    if (desc.contourCount > 0)
    {
        size_t size = desc.contourCount * sizeof(gpu::ContourData);
        bind_storage(CONTOUR_BUFFER_IDX,
                     contour_gpu.address(desc.firstContour *
                                         sizeof(gpu::ContourData)),
                     size);
    }

    if (coverage_gpu.size() > 0)
    {
        bind_storage(COVERAGE_BUFFER_IDX,
                     coverage_gpu.address(),
                     coverage_gpu.size());
    }
}

void RenderContextNVNImpl::bind_common_textures(
    nvn_api::CommandBuffer* command_buffer,
    const ProgramBindings* bindings)
{
    if (!command_buffer)
    {
        return;
    }

    auto bind_texture = [&](int idx,
                            nvn_api::TextureHandle handle,
                            const char* label) {
        if (handle == 0)
        {
            return;
        }
        if (idx < 0 || idx >= static_cast<int>(m_boundTexturesFrag.size()))
        {
            return;
        }
        if (m_boundTexturesFrag[static_cast<size_t>(idx)] == handle &&
            m_boundTexturesVert[static_cast<size_t>(idx)] == handle)
        {
            return;
        }
#if RIVE_NVN_ENABLE_BIND_LOGS
        if (label)
        {
            debug_log("[rive nvn] bind texture %s idx=%d handle=0x%llx",
                      label,
                      idx,
                      static_cast<unsigned long long>(handle));
        }
#endif
        command_buffer->BindTexture(nvn_api::ShaderStage::VERTEX, idx, handle);
        command_buffer->BindTexture(nvn_api::ShaderStage::FRAGMENT, idx, handle);
        m_boundTexturesVert[static_cast<size_t>(idx)] = handle;
        m_boundTexturesFrag[static_cast<size_t>(idx)] = handle;
    };

    auto bind_image = [&](int idx,
                          nvn_api::ImageHandle handle,
                          const char* label) {
        if (handle == 0)
        {
            return;
        }
        if (idx < 0 || idx >= static_cast<int>(m_boundImagesFrag.size()))
        {
            return;
        }
        if (m_boundImagesFrag[static_cast<size_t>(idx)] == handle)
        {
            return;
        }
#if RIVE_NVN_ENABLE_BIND_LOGS
        if (label)
        {
            debug_log("[rive nvn] bind image %s idx=%d handle=0x%llx",
                      label,
                      idx,
                      static_cast<unsigned long long>(handle));
        }
#endif
        command_buffer->BindImage(nvn_api::ShaderStage::FRAGMENT, idx, handle);
        m_boundImagesFrag[static_cast<size_t>(idx)] = handle;
    };

    bind_texture(TESS_VERTEX_TEXTURE_IDX,
                 m_tessTexture.handle,
                 "tess");
    bind_texture(GRAD_TEXTURE_IDX,
                 m_gradientTexture.handle,
                 "grad");
    bind_texture(FEATHER_TEXTURE_IDX,
                 m_featherTexture.handle,
                 "feather");
    bind_texture(ATLAS_TEXTURE_IDX,
                 m_atlasTexture.handle,
                 "atlas");

#if RIVE_NVN_DISABLE_PLS
    return;
#endif

    const bool bindings_valid =
#if RIVE_NVN_PLS_FIXED_LAYOUT
        false;
#else
        bindings &&
        (bindings->pls_color >= 0 || bindings->pls_clip >= 0 ||
         bindings->pls_scratch >= 0 || bindings->pls_coverage >= 0);
#endif

    auto resolve_image_index = [&](int idx, int fallback,
                                   const char* label) {
        int resolved = idx;
        if (!bindings_valid)
        {
            resolved = fallback;
        }
        if (resolved < 0)
        {
            return -1;
        }
        if (resolved >= static_cast<int>(m_boundImagesFrag.size()))
        {
#if RIVE_NVN_ENABLE_BIND_LOGS
            debug_log("[rive nvn] binding %s idx=%d out of range, skipping",
                      label ? label : "(unknown)",
                      resolved);
#endif
            return -1;
        }
        return resolved;
    };

    const int color_idx = resolve_image_index(
        bindings ? bindings->pls_color : -1,
        COLOR_PLANE_IDX,
        "pls_color");
    const int clip_idx = resolve_image_index(
        bindings ? bindings->pls_clip : -1,
        CLIP_PLANE_IDX,
        "pls_clip");
    const int scratch_idx = resolve_image_index(
        bindings ? bindings->pls_scratch : -1,
        SCRATCH_COLOR_PLANE_IDX,
        "pls_scratch");
    const int coverage_idx = resolve_image_index(
        bindings ? bindings->pls_coverage : -1,
        COVERAGE_PLANE_IDX,
        "pls_coverage");

    bind_image(color_idx,
               m_plsColorTexture.image_handle,
               "pls_color");
    bind_image(clip_idx,
               m_plsClipTexture.image_handle,
               "pls_clip");
    bind_image(scratch_idx,
               m_plsScratchTexture.image_handle,
               "pls_scratch");
    bind_image(coverage_idx,
               m_plsCoverageTexture.image_handle,
               "pls_coverage");
}

void RenderContextNVNImpl::reset_bind_cache()
{
    m_boundTexturesVert.fill(0);
    m_boundTexturesFrag.fill(0);
    m_boundImagesFrag.fill(0);
}

bool RenderContextNVNImpl::ensure_resource_textures(
    const gpu::FlushDescriptor& desc,
    nvn_api::Device* device)
{
    static bool s_logged_enter = false;
    if (!s_logged_enter)
    {
        frame_log("[rive] ensure_resource_textures enter");
        s_logged_enter = true;
    }
    {
        static int s_last_interlock = -1;
        const int interlock = static_cast<int>(desc.interlockMode);
        if (s_last_interlock != interlock)
        {
            debug_log("[rive] pls interlock mode=%d", interlock);
            s_last_interlock = interlock;
        }
    }
    static bool s_logged_descriptor_fail = false;
    static bool s_logged_sampler_fail = false;
    static bool s_logged_gradient_fail = false;
    static bool s_logged_tess_fail = false;
    static bool s_logged_atlas_fail = false;
    static bool s_logged_feather_fail = false;
    static bool s_logged_pls_color_fail = false;
    static bool s_logged_pls_clip_fail = false;
    static bool s_logged_pls_scratch_fail = false;
    static bool s_logged_pls_coverage_fail = false;
    static bool s_logged_pls_color_desc = false;
    static bool s_logged_pls_clip_desc = false;
    static bool s_logged_pls_scratch_desc = false;
    static bool s_logged_pls_coverage_desc = false;
    if (!device)
    {
        return false;
    }

    auto* render_target = static_cast<RenderTargetNVN*>(desc.renderTarget);
    if (!render_target)
    {
        return false;
    }

    if (!ensure_descriptor_pools(device))
    {
        if (!s_logged_descriptor_fail)
        {
            debug_log("[rive] ensure_resource_textures failed: descriptor pool");
            s_logged_descriptor_fail = true;
        }
        return false;
    }
    {
        static bool s_logged_pools_ok = false;
        if (!s_logged_pools_ok)
        {
            frame_log("[rive] ensure_resource_textures step: pools ok");
            s_logged_pools_ok = true;
        }
    }

    {
        static bool s_logged_sampler_enter = false;
        if (!s_logged_sampler_enter)
        {
            frame_log("[rive] ensure_resource_textures step: sampler enter");
            s_logged_sampler_enter = true;
        }
    }
    const int sampler_id = ensure_default_sampler(device);
    {
        static bool s_logged_sampler_id = false;
        if (!s_logged_sampler_id)
        {
            frame_log("[rive] ensure_resource_textures step: sampler id=%d",
                      sampler_id);
            s_logged_sampler_id = true;
        }
    }
    if (sampler_id < 0)
    {
        if (!s_logged_sampler_fail)
        {
            debug_log("[rive] ensure_resource_textures failed: sampler");
            s_logged_sampler_fail = true;
        }
        return false;
    }
    {
        static bool s_logged_sampler_ok = false;
        if (!s_logged_sampler_ok)
        {
            frame_log("[rive] ensure_resource_textures step: sampler ok");
            s_logged_sampler_ok = true;
        }
    }

    static const nvn_api::MemoryPoolFlags kPoolFlags =
        nvn_api::MemoryPoolFlags::CPU_UNCACHED |
        nvn_api::MemoryPoolFlags::GPU_CACHED;
    static const nvn_api::MemoryPoolFlags kPlsPoolFlags =
        nvn_api::MemoryPoolFlags::CPU_NO_ACCESS |
        nvn_api::MemoryPoolFlags::GPU_CACHED;

    if (m_gradientTextureWidth > 0 && m_gradientTextureHeight > 0)
    {
        static bool s_logged_gradient_try = false;
        if (!s_logged_gradient_try)
        {
            frame_log("[rive] ensure_resource_textures step: gradient %ux%u",
                      static_cast<unsigned int>(m_gradientTextureWidth),
                      static_cast<unsigned int>(m_gradientTextureHeight));
            s_logged_gradient_try = true;
        }
        int tex_id = m_gradientTexture.texture_id >= 0
                         ? m_gradientTexture.texture_id
                         : m_nextTextureId++;
        if (!m_gradientTexture.ensure(device,
                                      m_allocator,
                                      &m_texturePool,
                                      tex_id,
                                      sampler_id,
                                      -1,
                                      static_cast<int>(m_gradientTextureWidth),
                                      static_cast<int>(m_gradientTextureHeight),
                                      nvn_api::Format::RGBA8,
                                      nvn_api::TextureFlags(0),
                                      nvn_api::TextureTarget::TARGET_2D,
                                      kPoolFlags,
                                      true,
                                      false))
        {
            if (!s_logged_gradient_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: gradient");
                s_logged_gradient_fail = true;
            }
            return false;
        }
        static bool s_logged_gradient_ok = false;
        if (!s_logged_gradient_ok)
        {
            frame_log("[rive] ensure_resource_textures step: gradient ok");
            s_logged_gradient_ok = true;
        }
    }

    if (m_tessellationTextureWidth > 0 && m_tessellationTextureHeight > 0)
    {
        static bool s_logged_tess_try = false;
        if (!s_logged_tess_try)
        {
            frame_log("[rive] ensure_resource_textures step: tess %ux%u",
                      static_cast<unsigned int>(m_tessellationTextureWidth),
                      static_cast<unsigned int>(m_tessellationTextureHeight));
            s_logged_tess_try = true;
        }
        ImageSampler tess_sampler = ImageSampler::LinearClamp();
        tess_sampler.filter = ImageFilter::nearest;
        int tess_sampler_id = ensure_sampler(tess_sampler, device);
        if (tess_sampler_id < 0)
        {
            tess_sampler_id = sampler_id;
        }
        int tex_id = m_tessTexture.texture_id >= 0 ? m_tessTexture.texture_id
                                                   : m_nextTextureId++;
        if (!m_tessTexture.ensure(device,
                                  m_allocator,
                                  &m_texturePool,
                                  tex_id,
                                  tess_sampler_id,
                                  -1,
                                  static_cast<int>(m_tessellationTextureWidth),
                                  static_cast<int>(m_tessellationTextureHeight),
                                  nvn_api::Format::RGBA32F,
                                  nvn_api::TextureFlags(0),
                                  nvn_api::TextureTarget::TARGET_2D,
                                  kPoolFlags,
                                  true,
                                  false))
        {
            if (!s_logged_tess_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: tess");
                s_logged_tess_fail = true;
            }
            return false;
        }
        static bool s_logged_tess_ok = false;
        if (!s_logged_tess_ok)
        {
            frame_log("[rive] ensure_resource_textures step: tess ok");
            s_logged_tess_ok = true;
        }
    }

    if (m_atlasTextureWidth > 0 && m_atlasTextureHeight > 0)
    {
        static bool s_logged_atlas_try = false;
        if (!s_logged_atlas_try)
        {
            frame_log("[rive] ensure_resource_textures step: atlas %ux%u",
                      static_cast<unsigned int>(m_atlasTextureWidth),
                      static_cast<unsigned int>(m_atlasTextureHeight));
            s_logged_atlas_try = true;
        }
        int tex_id = m_atlasTexture.texture_id >= 0 ? m_atlasTexture.texture_id
                                                    : m_nextTextureId++;
        if (!m_atlasTexture.ensure(device,
                                   m_allocator,
                                   &m_texturePool,
                                   tex_id,
                                   sampler_id,
                                   -1,
                                   static_cast<int>(m_atlasTextureWidth),
                                   static_cast<int>(m_atlasTextureHeight),
                                   nvn_api::Format::RGBA8,
                                   nvn_api::TextureFlags(0),
                                   nvn_api::TextureTarget::TARGET_2D,
                                   kPoolFlags,
                                   true,
                                   false))
        {
            if (!s_logged_atlas_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: atlas");
                s_logged_atlas_fail = true;
            }
            return false;
        }
        static bool s_logged_atlas_ok = false;
        if (!s_logged_atlas_ok)
        {
            frame_log("[rive] ensure_resource_textures step: atlas ok");
            s_logged_atlas_ok = true;
        }
    }

    {
        static bool s_logged_feather_try = false;
        if (!s_logged_feather_try)
        {
            frame_log("[rive] ensure_resource_textures step: feather");
            s_logged_feather_try = true;
        }
        const int feather_width = gpu::GAUSSIAN_TABLE_SIZE;
        const int feather_height = FEATHER_TEXTURE_1D_ARRAY_LENGTH;
        bool had_feather = m_featherTexture.initialized;
        int tex_id = m_featherTexture.texture_id >= 0
                         ? m_featherTexture.texture_id
                         : m_nextTextureId++;
        if (!m_featherTexture.ensure(device,
                                     m_allocator,
                                     &m_texturePool,
                                     tex_id,
                                     sampler_id,
                                     -1,
                                     feather_width,
                                     feather_height,
                                     nvn_api::Format::R16F,
                                     nvn_api::TextureFlags(0),
                                     nvn_api::TextureTarget::TARGET_2D,
                                     kPoolFlags,
                                     true,
                                     false))
        {
            if (!s_logged_feather_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: feather");
                s_logged_feather_fail = true;
            }
            return false;
        }

        if (!had_feather)
        {
            static bool s_logged_feather_upload = false;
            if (!s_logged_feather_upload)
            {
                frame_log("[rive] ensure_resource_textures step: feather upload");
                s_logged_feather_upload = true;
            }
            nvn_api::CopyRegion region = {};
            region.xoffset = 0;
            region.zoffset = 0;
            region.width = feather_width;
            region.height = 1;
            region.depth = 1;

            region.yoffset = FEATHER_FUNCTION_ARRAY_INDEX;
            m_featherTexture.texture.WriteTexels(
                &m_featherTexture.view,
                &region,
                gpu::g_gaussianIntegralTableF16);

            region.yoffset = FEATHER_INVERSE_FUNCTION_ARRAY_INDEX;
            m_featherTexture.texture.WriteTexels(
                &m_featherTexture.view,
                &region,
                gpu::g_inverseGaussianIntegralTableF16);
        }
        static bool s_logged_feather_ok = false;
        if (!s_logged_feather_ok)
        {
            frame_log("[rive] ensure_resource_textures step: feather ok");
            s_logged_feather_ok = true;
        }
    }

#if RIVE_NVN_DISABLE_PLS
    return true;
#endif

    {
        static bool s_logged_target_ptr = false;
        if (!s_logged_target_ptr)
        {
            debug_log("[rive] ensure_resource_textures step: render target %p",
                      render_target);
            s_logged_target_ptr = true;
        }
    }
    const int render_width = static_cast<int>(render_target->width());
    const int render_height = static_cast<int>(render_target->height());
    const int pls_width = m_plsTransientBackingWidth > 0
                              ? static_cast<int>(m_plsTransientBackingWidth)
                              : render_width;
    const int pls_height = m_plsTransientBackingHeight > 0
                               ? static_cast<int>(m_plsTransientBackingHeight)
                               : render_height;
    const int coverage_width = m_atomicCoverageWidth > 0
                                   ? static_cast<int>(m_atomicCoverageWidth)
                                   : pls_width;
    const int coverage_height = m_atomicCoverageHeight > 0
                                    ? static_cast<int>(m_atomicCoverageHeight)
                                    : pls_height;
    {
        static const RenderTargetNVN* s_last_rt = nullptr;
        static int s_last_render_w = -1;
        static int s_last_render_h = -1;
        static int s_last_pls_w = -1;
        static int s_last_pls_h = -1;
        static int s_last_cov_w = -1;
        static int s_last_cov_h = -1;
        if (s_last_rt != render_target ||
            s_last_render_w != render_width ||
            s_last_render_h != render_height ||
            s_last_pls_w != pls_width ||
            s_last_pls_h != pls_height ||
            s_last_cov_w != coverage_width ||
            s_last_cov_h != coverage_height)
        {
            debug_log(
                "[rive] pls dims render=%dx%d pls=%dx%d coverage=%dx%d transient=%u/%u atomic=%u/%u",
                render_width,
                render_height,
                pls_width,
                pls_height,
                coverage_width,
                coverage_height,
                static_cast<unsigned int>(m_plsTransientBackingWidth),
                static_cast<unsigned int>(m_plsTransientBackingHeight),
                static_cast<unsigned int>(m_atomicCoverageWidth),
                static_cast<unsigned int>(m_atomicCoverageHeight));
            s_last_rt = render_target;
            s_last_render_w = render_width;
            s_last_render_h = render_height;
            s_last_pls_w = pls_width;
            s_last_pls_h = pls_height;
            s_last_cov_w = coverage_width;
            s_last_cov_h = coverage_height;
        }
    }

    const nvn_api::TextureTarget pls_target =
        nvn_api::TextureTarget::TARGET_2D;
    static bool s_logged_pls_target = false;
    if (!s_logged_pls_target)
    {
        debug_log("[rive] PLS storage textures hardcoded to TARGET_2D");
        s_logged_pls_target = true;
    }

    if (pls_width > 0 && pls_height > 0)
    {
        const nvn_api::TextureFlags pls_flags =
            nvn_api::TextureFlags::IMAGE;
        const nvn_api::Format color_format =
            static_cast<nvn_api::Format>(RIVE_NVN_PLS_COLOR_FORMAT);
        const nvn_api::Format clip_format =
            static_cast<nvn_api::Format>(RIVE_NVN_PLS_CLIP_FORMAT);
        const nvn_api::Format scratch_format =
            static_cast<nvn_api::Format>(RIVE_NVN_PLS_SCRATCH_FORMAT);
        static bool s_logged_pls_formats = false;
        if (!s_logged_pls_formats)
        {
            debug_log(
                "[rive] pls formats color=%d clip=%d scratch=%d",
                static_cast<int>(color_format),
                static_cast<int>(clip_format),
                static_cast<int>(scratch_format));
            s_logged_pls_formats = true;
        }
        int color_id = m_plsColorTexture.texture_id >= 0
                           ? m_plsColorTexture.texture_id
                           : m_nextTextureId++;
        int color_image = m_plsColorTexture.image_id >= 0
                               ? m_plsColorTexture.image_id
                              : color_id;
        if (!m_plsColorTexture.ensure(device,
                                      m_allocator,
                                      &m_texturePool,
                                      color_id,
                                      sampler_id,
                                      color_image,
                                      pls_width,
                                      pls_height,
                                      color_format,
                                      pls_flags,
                                      pls_target,
                                      kPlsPoolFlags,
                                      false,
                                      true))
        {
            if (!s_logged_pls_color_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: pls color");
                s_logged_pls_color_fail = true;
            }
            return false;
        }
        if (!s_logged_pls_color_desc)
        {
            dump_texture_descriptor(m_descriptorMemory,
                                    m_descriptorMemorySize,
                                    m_samplerBytes,
                                    m_textureDescriptorSize,
                                    color_image,
                                    "pls_color");
            s_logged_pls_color_desc = true;
        }

        int clip_id = m_plsClipTexture.texture_id >= 0
                          ? m_plsClipTexture.texture_id
                          : m_nextTextureId++;
        int clip_image = m_plsClipTexture.image_id >= 0
                             ? m_plsClipTexture.image_id
                             : clip_id;
        if (!m_plsClipTexture.ensure(device,
                                     m_allocator,
                                     &m_texturePool,
                                     clip_id,
                                     sampler_id,
                                     clip_image,
                                     pls_width,
                                     pls_height,
                                     clip_format,
                                     pls_flags,
                                     pls_target,
                                     kPlsPoolFlags,
                                     false,
                                     true))
        {
            if (!s_logged_pls_clip_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: pls clip");
                s_logged_pls_clip_fail = true;
            }
            return false;
        }
        if (!s_logged_pls_clip_desc)
        {
            dump_texture_descriptor(m_descriptorMemory,
                                    m_descriptorMemorySize,
                                    m_samplerBytes,
                                    m_textureDescriptorSize,
                                    clip_image,
                                    "pls_clip");
            s_logged_pls_clip_desc = true;
        }

        int scratch_id = m_plsScratchTexture.texture_id >= 0
                             ? m_plsScratchTexture.texture_id
                             : m_nextTextureId++;
        int scratch_image = m_plsScratchTexture.image_id >= 0
                                ? m_plsScratchTexture.image_id
                                : scratch_id;
        if (!m_plsScratchTexture.ensure(device,
                                        m_allocator,
                                        &m_texturePool,
                                        scratch_id,
                                        sampler_id,
                                        scratch_image,
                                        pls_width,
                                        pls_height,
                                        scratch_format,
                                        pls_flags,
                                        pls_target,
                                        kPlsPoolFlags,
                                        false,
                                        true))
        {
            if (!s_logged_pls_scratch_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: pls scratch");
                s_logged_pls_scratch_fail = true;
            }
            return false;
        }
        if (!s_logged_pls_scratch_desc)
        {
            dump_texture_descriptor(m_descriptorMemory,
                                    m_descriptorMemorySize,
                                    m_samplerBytes,
                                    m_textureDescriptorSize,
                                    scratch_image,
                                    "pls_scratch");
            s_logged_pls_scratch_desc = true;
        }
    }

    if (desc.interlockMode != gpu::InterlockMode::msaa &&
        coverage_width > 0 && coverage_height > 0)
    {
        const nvn_api::TextureFlags pls_flags =
            nvn_api::TextureFlags::IMAGE;
        const nvn_api::Format coverage_format =
            static_cast<nvn_api::Format>(RIVE_NVN_PLS_COVERAGE_FORMAT);
        static bool s_logged_pls_coverage_format = false;
        if (!s_logged_pls_coverage_format)
        {
            debug_log("[rive] pls coverage format=%d",
                      static_cast<int>(coverage_format));
            s_logged_pls_coverage_format = true;
        }
        int coverage_id = m_plsCoverageTexture.texture_id >= 0
                              ? m_plsCoverageTexture.texture_id
                              : m_nextTextureId++;
        int coverage_image = m_plsCoverageTexture.image_id >= 0
                                 ? m_plsCoverageTexture.image_id
                                 : coverage_id;
        if (!m_plsCoverageTexture.ensure(device,
                                         m_allocator,
                                         &m_texturePool,
                                         coverage_id,
                                         sampler_id,
                                         coverage_image,
                                         coverage_width,
                                         coverage_height,
                                         coverage_format,
                                         pls_flags,
                                         pls_target,
                                         kPlsPoolFlags,
                                         false,
                                         true))
        {
            if (!s_logged_pls_coverage_fail)
            {
                debug_log("[rive] ensure_resource_textures failed: pls coverage");
                s_logged_pls_coverage_fail = true;
            }
            return false;
        }
        if (!s_logged_pls_coverage_desc)
        {
            dump_texture_descriptor(m_descriptorMemory,
                                    m_descriptorMemorySize,
                                    m_samplerBytes,
                                    m_textureDescriptorSize,
                                    coverage_image,
                                    "pls_coverage");
            s_logged_pls_coverage_desc = true;
        }
    }

    return true;
}

void RenderContextNVNImpl::render_color_ramp(
    const gpu::FlushDescriptor& desc,
    nvn_api::CommandBuffer* command_buffer)
{
    if (!command_buffer || desc.gradSpanCount == 0 ||
        m_gradientTextureWidth == 0 || m_gradientTextureHeight == 0)
    {
        return;
    }

    if (!m_colorRampProgram.initialized())
    {
        std::vector<const char*> defines;
        defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);

        std::vector<const char*> sources;
        sources.push_back(rive::gpu::glsl::color_ramp);

        std::string vertex_source = build_program_source(
            ProgramStage::vertex,
            defines,
            sources,
            m_platformFeatures);
        std::string fragment_source = build_program_source(
            ProgramStage::fragment,
            defines,
            sources,
            m_platformFeatures);

        m_colorRampProgram.initialize(reinterpret_cast<nvn_api::Device*>(m_device),
                                      m_allocator,
                                      m_glslcApi,
                                      m_glslcAllocator,
                                      vertex_source.c_str(),
                                      fragment_source.c_str());
    }

    if (!m_colorRampProgram.initialized())
    {
        return;
    }

    nvn_api::Texture* colors[] = {&m_gradientTexture.texture};
    nvn_api::TextureView* color_views[] = {&m_gradientTexture.view};
    command_buffer->SetRenderTargets(1, colors, color_views, nullptr, nullptr);
    command_buffer->SetViewport(0,
                                0,
                                static_cast<int>(m_gradientTextureWidth),
                                static_cast<int>(desc.gradDataHeight));
    command_buffer->SetScissor(0,
                               0,
                               static_cast<int>(m_gradientTextureWidth),
                               static_cast<int>(desc.gradDataHeight));

    apply_pipeline_state(command_buffer, gpu::COLOR_ONLY_PIPELINE_STATE, 1);
    bind_common_buffers(desc, command_buffer);

    auto& grad_span_gpu = frame_buffer(m_gradSpanGpu);
    command_buffer->BindVertexAttribState(1, m_gradAttribs);
    command_buffer->BindVertexStreamState(1, m_gradStreams);
    command_buffer->BindVertexBuffer(0,
                                     grad_span_gpu.address(),
                                     grad_span_gpu.size());

    m_colorRampProgram.bind(command_buffer);

    constexpr uint32_t kMaxInstances =
        std::numeric_limits<uint32_t>::max();
    for (auto [instanceCount, baseInstance] :
         InstanceChunker(desc.gradSpanCount,
                         static_cast<uint32_t>(desc.firstGradSpan),
                         kMaxInstances))
    {
        command_buffer->DrawArraysInstanced(
            nvn_api::DrawPrimitive::TRIANGLE_STRIP,
            0,
            gpu::GRAD_SPAN_TRI_STRIP_VERTEX_COUNT,
            static_cast<int>(baseInstance),
            static_cast<int>(instanceCount));
    }
}

void RenderContextNVNImpl::render_tessellation(
    const gpu::FlushDescriptor& desc,
    nvn_api::CommandBuffer* command_buffer)
{
    if (!command_buffer || desc.tessVertexSpanCount == 0 ||
        m_tessellationTextureWidth == 0 || m_tessellationTextureHeight == 0)
    {
        return;
    }

    if (!m_tessellateProgram.initialized())
    {
        std::vector<const char*> defines;
        defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);
        defines.push_back(GLSL_TESS_TEXTURE_FLOATING_POINT);

        std::vector<const char*> sources;
        sources.push_back(rive::gpu::glsl::bezier_utils);
        sources.push_back(rive::gpu::glsl::tessellate);

        std::string vertex_source = build_program_source(
            ProgramStage::vertex,
            defines,
            sources,
            m_platformFeatures);
        std::string fragment_source = build_program_source(
            ProgramStage::fragment,
            defines,
            sources,
            m_platformFeatures);

        m_tessellateProgram.initialize(reinterpret_cast<nvn_api::Device*>(m_device),
                                       m_allocator,
                                       m_glslcApi,
                                       m_glslcAllocator,
                                       vertex_source.c_str(),
                                       fragment_source.c_str());
    }

    if (!m_tessellateProgram.initialized())
    {
        return;
    }

    nvn_api::Texture* colors[] = {&m_tessTexture.texture};
    nvn_api::TextureView* color_views[] = {&m_tessTexture.view};
    command_buffer->SetRenderTargets(1, colors, color_views, nullptr, nullptr);
    command_buffer->SetViewport(0,
                                0,
                                static_cast<int>(m_tessellationTextureWidth),
                                static_cast<int>(desc.tessDataHeight));
    command_buffer->SetScissor(0,
                               0,
                               static_cast<int>(m_tessellationTextureWidth),
                               static_cast<int>(desc.tessDataHeight));

    apply_pipeline_state(command_buffer, gpu::COLOR_ONLY_PIPELINE_STATE, 1);
    bind_common_buffers(desc, command_buffer);
    if (m_featherTexture.handle != 0)
    {
        command_buffer->BindTexture(nvn_api::ShaderStage::VERTEX,
                                    FEATHER_TEXTURE_IDX,
                                    m_featherTexture.handle);
        command_buffer->BindTexture(nvn_api::ShaderStage::FRAGMENT,
                                    FEATHER_TEXTURE_IDX,
                                    m_featherTexture.handle);
    }

    auto& tess_span_gpu = frame_buffer(m_tessSpanGpu);
    command_buffer->BindVertexAttribState(4, m_tessAttribs);
    command_buffer->BindVertexStreamState(1, m_tessStreams);
    command_buffer->BindVertexBuffer(0,
                                     tess_span_gpu.address(),
                                     tess_span_gpu.size());

    m_tessellateProgram.bind(command_buffer);

    constexpr uint32_t kMaxInstances =
        std::numeric_limits<uint32_t>::max();
    for (auto [instanceCount, baseInstance] :
         InstanceChunker(desc.tessVertexSpanCount,
                         static_cast<uint32_t>(desc.firstTessVertexSpan),
                         kMaxInstances))
    {
        command_buffer->DrawElementsInstanced(
            nvn_api::DrawPrimitive::TRIANGLES,
            nvn_api::IndexType::UNSIGNED_SHORT,
            static_cast<int>(sizeof(gpu::kTessSpanIndices) /
                             sizeof(gpu::kTessSpanIndices[0])),
            m_tessSpanIndexGpu.address(),
            0,
            static_cast<int>(baseInstance),
            static_cast<int>(instanceCount));
    }
}

void RenderContextNVNImpl::render_atlas(
    const gpu::FlushDescriptor& desc,
    nvn_api::CommandBuffer* command_buffer)
{
    if (!command_buffer)
    {
        return;
    }
    if ((desc.atlasFillBatchCount | desc.atlasStrokeBatchCount) == 0 ||
        m_atlasTextureWidth == 0 || m_atlasTextureHeight == 0)
    {
        return;
    }

    if (!m_atlasFillProgram.initialized() ||
        !m_atlasStrokeProgram.initialized())
    {
        std::vector<const char*> base_defines;
        base_defines.push_back(GLSL_DRAW_PATH);
        base_defines.push_back(GLSL_ENABLE_FEATHER);
        base_defines.push_back(GLSL_ENABLE_INSTANCE_INDEX);
        base_defines.push_back(GLSL_ATLAS_RENDER_TARGET_RGBA8_UNORM);

        std::vector<const char*> sources;
        sources.push_back(rive::gpu::glsl::draw_path_common);
        sources.push_back(rive::gpu::glsl::render_atlas);

        std::vector<const char*> defines = base_defines;
        defines.push_back(GLSL_ATLAS_FEATHERED_FILL);
        std::string fill_vertex = build_program_source(
            ProgramStage::vertex,
            defines,
            sources,
            m_platformFeatures);
        std::string fill_fragment = build_program_source(
            ProgramStage::fragment,
            defines,
            sources,
            m_platformFeatures);
        m_atlasFillProgram.initialize(reinterpret_cast<nvn_api::Device*>(m_device),
                                      m_allocator,
                                      m_glslcApi,
                                      m_glslcAllocator,
                                      fill_vertex.c_str(),
                                      fill_fragment.c_str());

        defines = base_defines;
        defines.push_back(GLSL_ATLAS_FEATHERED_STROKE);
        std::string stroke_vertex = build_program_source(
            ProgramStage::vertex,
            defines,
            sources,
            m_platformFeatures);
        std::string stroke_fragment = build_program_source(
            ProgramStage::fragment,
            defines,
            sources,
            m_platformFeatures);
        m_atlasStrokeProgram.initialize(
            reinterpret_cast<nvn_api::Device*>(m_device),
            m_allocator,
            m_glslcApi,
            m_glslcAllocator,
            stroke_vertex.c_str(),
            stroke_fragment.c_str());
    }

    if ((desc.atlasFillBatchCount != 0 && !m_atlasFillProgram.initialized()) ||
        (desc.atlasStrokeBatchCount != 0 &&
         !m_atlasStrokeProgram.initialized()))
    {
        return;
    }

    nvn_api::Texture* colors[] = {&m_atlasTexture.texture};
    nvn_api::TextureView* color_views[] = {&m_atlasTexture.view};
    command_buffer->SetRenderTargets(1, colors, color_views, nullptr, nullptr);
    command_buffer->SetViewport(0,
                                0,
                                static_cast<int>(desc.atlasContentWidth),
                                static_cast<int>(desc.atlasContentHeight));
    command_buffer->SetScissor(0,
                               0,
                               static_cast<int>(desc.atlasContentWidth),
                               static_cast<int>(desc.atlasContentHeight));

    float clear_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    command_buffer->ClearColor(0,
                               clear_color,
                               nvn_api::ClearColorMask(nvn_api::ClearColorMask::RGBA));

    bind_common_buffers(desc, command_buffer);
    if (m_tessTexture.handle != 0)
    {
        command_buffer->BindTexture(nvn_api::ShaderStage::VERTEX,
                                    TESS_VERTEX_TEXTURE_IDX,
                                    m_tessTexture.handle);
        command_buffer->BindTexture(nvn_api::ShaderStage::FRAGMENT,
                                    TESS_VERTEX_TEXTURE_IDX,
                                    m_tessTexture.handle);
    }
    if (m_featherTexture.handle != 0)
    {
        command_buffer->BindTexture(nvn_api::ShaderStage::VERTEX,
                                    FEATHER_TEXTURE_IDX,
                                    m_featherTexture.handle);
        command_buffer->BindTexture(nvn_api::ShaderStage::FRAGMENT,
                                    FEATHER_TEXTURE_IDX,
                                    m_featherTexture.handle);
    }
    command_buffer->BindVertexAttribState(2, m_patchAttribs);
    command_buffer->BindVertexStreamState(1, m_patchStreams);
    command_buffer->BindVertexBuffer(0,
                                     m_patchVertexGpu.address(),
                                     m_patchVertexGpu.size());

    constexpr uint32_t kMaxInstances =
        std::numeric_limits<uint32_t>::max();

    if (desc.atlasFillBatchCount != 0)
    {
        apply_pipeline_state(command_buffer,
                             gpu::ATLAS_FILL_PIPELINE_STATE,
                             1);
        m_atlasFillProgram.bind(command_buffer);
        for (size_t i = 0; i < desc.atlasFillBatchCount; ++i)
        {
            const gpu::AtlasDrawBatch& batch = desc.atlasFillBatches[i];
            command_buffer->SetScissor(batch.scissor.left,
                                       batch.scissor.top,
                                       batch.scissor.width(),
                                       batch.scissor.height());
            for (auto [instanceCount, baseInstance] :
                 InstanceChunker(batch.patchCount,
                                 batch.basePatch,
                                 kMaxInstances))
            {
                command_buffer->DrawElementsInstanced(
                    nvn_api::DrawPrimitive::TRIANGLES,
                    nvn_api::IndexType::UNSIGNED_SHORT,
                    static_cast<int>(
                        gpu::kMidpointFanCenterAAPatchIndexCount),
                    m_patchIndexGpu.address(
                        gpu::kMidpointFanCenterAAPatchBaseIndex *
                        sizeof(uint16_t)),
                    0,
                    static_cast<int>(baseInstance),
                    static_cast<int>(instanceCount));
            }
        }
    }

    if (desc.atlasStrokeBatchCount != 0)
    {
        apply_pipeline_state(command_buffer,
                             gpu::ATLAS_STROKE_PIPELINE_STATE,
                             1);
        m_atlasStrokeProgram.bind(command_buffer);
        for (size_t i = 0; i < desc.atlasStrokeBatchCount; ++i)
        {
            const gpu::AtlasDrawBatch& batch = desc.atlasStrokeBatches[i];
            command_buffer->SetScissor(batch.scissor.left,
                                       batch.scissor.top,
                                       batch.scissor.width(),
                                       batch.scissor.height());
            for (auto [instanceCount, baseInstance] :
                 InstanceChunker(batch.patchCount,
                                 batch.basePatch,
                                 kMaxInstances))
            {
                command_buffer->DrawElementsInstanced(
                    nvn_api::DrawPrimitive::TRIANGLES,
                    nvn_api::IndexType::UNSIGNED_SHORT,
                    static_cast<int>(gpu::kMidpointFanPatchBorderIndexCount),
                    m_patchIndexGpu.address(
                        gpu::kMidpointFanPatchBaseIndex *
                        sizeof(uint16_t)),
                    0,
                    static_cast<int>(baseInstance),
                    static_cast<int>(instanceCount));
            }
        }
    }
}

void RenderContextNVNImpl::execute_draw_list(
    const gpu::FlushDescriptor& desc,
    nvn_api::CommandBuffer* command_buffer)
{
    if (!desc.drawList || !command_buffer)
    {
        return;
    }
    const bool has_pls_images =
        m_plsColorTexture.initialized ||
        m_plsClipTexture.initialized ||
        m_plsScratchTexture.initialized ||
        m_plsCoverageTexture.initialized;
    if (has_pls_images)
    {
        // Ensure PLS storage images are in a valid state before the first draw.
        command_buffer->Barrier(pls_storage_barrier_bits());
    }

    reset_bind_cache();

    auto* render_target = static_cast<RenderTargetNVN*>(desc.renderTarget);
    const int sample_count =
        render_target ? static_cast<int>(render_target->sampleCount()) : 1;

    bind_common_buffers(desc, command_buffer);

    auto& triangle_gpu = frame_buffer(m_triangleGpu);
    auto& image_draw_gpu = frame_buffer(m_imageDrawUniformGpu);

    const NvnShaderProgram* last_program = nullptr;
    bool saw_msaa_draw = false;
    bool saw_msaa_color = false;

    for (const DrawBatch& batch : *desc.drawList)
    {
        ShaderBuildParams params = make_shader_params(desc, batch);
        const NvnShaderProgram* program = get_or_create_program(params);
        if (!program)
        {
            continue;
        }

        if (program != last_program)
        {
            bind_common_textures(command_buffer, &program->bindings());
            last_program = program;
        }

        program->bind(command_buffer);

        gpu::PipelineState pipeline_state;
        gpu::get_pipeline_state(batch, desc, m_platformFeatures, &pipeline_state);
        if (desc.interlockMode == gpu::InterlockMode::msaa)
        {
            saw_msaa_draw = true;
            if (pipeline_state.colorWriteEnabled)
            {
                saw_msaa_color = true;
            }
        }
#if RIVE_NVN_MSAA_DISABLE_STENCIL
        if (desc.interlockMode == gpu::InterlockMode::msaa)
        {
            pipeline_state.stencilTestEnabled = false;
            pipeline_state.stencilWriteMask = 0;
            static bool s_logged_stencil_disabled = false;
            if (!s_logged_stencil_disabled)
            {
                debug_log("[rive] NVN MSAA stencil disabled");
                s_logged_stencil_disabled = true;
            }
        }
#endif
        if (desc.interlockMode == gpu::InterlockMode::atomics &&
            !desc.fixedFunctionColorOutput && !pipeline_state.colorWriteEnabled)
        {
            // NVN appears to skip fragment work when color writes are disabled,
            // which would drop PLS image stores. Force color writes on in atomics.
            pipeline_state.colorWriteEnabled = true;
            static bool s_logged_force_color = false;
            if (!s_logged_force_color)
            {
                debug_log("[rive] forcing color writes for PLS atomics");
                s_logged_force_color = true;
            }
        }
        if (wants_coalesced_resolve(desc, batch))
        {
            pipeline_state.colorWriteEnabled = true;
        }
        apply_pipeline_state(command_buffer, pipeline_state, sample_count);

        if (batch.barriers & (BarrierFlags::plsAtomic |
                              BarrierFlags::plsAtomicPreResolve |
                              BarrierFlags::dstBlend))
        {
            command_buffer->Barrier(pls_storage_barrier_bits());
        }
#if RIVE_NVN_FORCE_PLS_BARRIER_EVERY_DRAW
        if (desc.interlockMode == gpu::InterlockMode::atomics)
        {
            // Force a storage barrier every draw in atomics to debug ordering issues.
            command_buffer->Barrier(pls_storage_barrier_bits());
        }
#endif

        if (auto image_texture =
                static_cast<const TextureNVN*>(batch.imageTexture))
        {
            if (image_texture->uploaded() ||
                const_cast<TextureNVN*>(image_texture)->ensureUploaded(*this))
            {
                debug_log("[rive dbg] execute_draw_list bind image: drawType=%d target=%d handle=0x%llx",
                          static_cast<int>(batch.drawType),
                          static_cast<int>(image_texture->m_resource.target),
                          static_cast<unsigned long long>(
                              image_texture->m_resource.handle));
                int sampler_id = ensure_sampler(batch.imageSampler,
                                                reinterpret_cast<nvn_api::Device*>(
                                                    m_device));
                if (sampler_id >= 0 && image_texture->textureId() >= 0)
                {
                    nvn_api::TextureHandle handle =
                        reinterpret_cast<nvn_api::Device*>(m_device)
                            ->GetTextureHandle(image_texture->textureId(),
                                               sampler_id);
                    command_buffer->BindTexture(
                        nvn_api::ShaderStage::FRAGMENT,
                        IMAGE_TEXTURE_IDX,
                        handle);
                    command_buffer->BindTexture(nvn_api::ShaderStage::VERTEX,
                                                IMAGE_TEXTURE_IDX,
                                                handle);
                }
            }
        }

        switch (batch.drawType)
        {
            case DrawType::midpointFanPatches:
            case DrawType::midpointFanCenterAAPatches:
            case DrawType::outerCurvePatches:
            case DrawType::msaaStrokes:
            case DrawType::msaaMidpointFanBorrowedCoverage:
            case DrawType::msaaMidpointFans:
            case DrawType::msaaMidpointFanStencilReset:
            case DrawType::msaaMidpointFanPathsStencil:
            case DrawType::msaaMidpointFanPathsCover:
            case DrawType::msaaOuterCubics:
            {
                command_buffer->BindVertexAttribState(2, m_patchAttribs);
                command_buffer->BindVertexStreamState(1, m_patchStreams);
                command_buffer->BindVertexBuffer(0,
                                                 m_patchVertexGpu.address(),
                                                 m_patchVertexGpu.size());

                constexpr uint32_t kMaxInstances =
                    std::numeric_limits<uint32_t>::max();
                for (auto [instanceCount, baseInstance] :
                     InstanceChunker(batch.elementCount,
                                     batch.baseElement,
                                     kMaxInstances))
                {
                    command_buffer->DrawElementsInstanced(
                        nvn_api::DrawPrimitive::TRIANGLES,
                        nvn_api::IndexType::UNSIGNED_SHORT,
                        static_cast<int>(gpu::PatchIndexCount(batch.drawType)),
                        m_patchIndexGpu.address(
                            gpu::PatchBaseIndex(batch.drawType) *
                            sizeof(uint16_t)),
                        0,
                        static_cast<int>(baseInstance),
                        static_cast<int>(instanceCount));
                }
                break;
            }

            case gpu::DrawType::msaaStencilClipReset:
            case gpu::DrawType::interiorTriangulation:
            case gpu::DrawType::atlasBlit:
            {
                command_buffer->BindVertexAttribState(1, m_triangleAttribs);
                command_buffer->BindVertexStreamState(1, m_triangleStreams);
                command_buffer->BindVertexBuffer(0,
                                                 triangle_gpu.address(),
                                                 triangle_gpu.size());
                command_buffer->DrawArrays(
                    nvn_api::DrawPrimitive::TRIANGLES,
                    static_cast<int>(batch.baseElement),
                    static_cast<int>(batch.elementCount));
                break;
            }

            case gpu::DrawType::imageRect:
            {
                if (image_draw_gpu.size() >=
                    sizeof(gpu::ImageDrawUniforms))
                {
                    nvn_api::BufferAddress address =
                        image_draw_gpu.address(
                            batch.imageDrawDataOffset);
                    command_buffer->BindUniformBuffer(
                        nvn_api::ShaderStage::VERTEX,
                        IMAGE_DRAW_UNIFORM_BUFFER_IDX,
                        address,
                        sizeof(gpu::ImageDrawUniforms));
                    command_buffer->BindUniformBuffer(
                        nvn_api::ShaderStage::FRAGMENT,
                        IMAGE_DRAW_UNIFORM_BUFFER_IDX,
                        address,
                        sizeof(gpu::ImageDrawUniforms));
                }

                command_buffer->BindVertexAttribState(1, m_imageRectAttribs);
                command_buffer->BindVertexStreamState(1, m_imageRectStreams);
                command_buffer->BindVertexBuffer(0,
                                                 m_imageRectVertexGpu.address(),
                                                 m_imageRectVertexGpu.size());
                command_buffer->DrawElements(
                    nvn_api::DrawPrimitive::TRIANGLES,
                    nvn_api::IndexType::UNSIGNED_SHORT,
                    static_cast<int>(sizeof(gpu::kImageRectIndices) /
                                     sizeof(gpu::kImageRectIndices[0])),
                    m_imageRectIndexGpu.address());
                break;
            }

            case gpu::DrawType::imageMesh:
            {
                LITE_RTTI_CAST_OR_BREAK(vertexBuffer,
                                        RenderBufferNVN*,
                                        batch.vertexBuffer);
                LITE_RTTI_CAST_OR_BREAK(uvBuffer,
                                        RenderBufferNVN*,
                                        batch.uvBuffer);
                LITE_RTTI_CAST_OR_BREAK(indexBuffer,
                                        RenderBufferNVN*,
                                        batch.indexBuffer);

                if (!vertexBuffer->upload(
                        reinterpret_cast<nvn_api::Device*>(m_device)) ||
                    !uvBuffer->upload(reinterpret_cast<nvn_api::Device*>(m_device)) ||
                    !indexBuffer->upload(
                        reinterpret_cast<nvn_api::Device*>(m_device)))
                {
                    break;
                }

                if (image_draw_gpu.size() >=
                    sizeof(gpu::ImageDrawUniforms))
                {
                    nvn_api::BufferAddress address =
                        image_draw_gpu.address(
                            batch.imageDrawDataOffset);
                    command_buffer->BindUniformBuffer(
                        nvn_api::ShaderStage::VERTEX,
                        IMAGE_DRAW_UNIFORM_BUFFER_IDX,
                        address,
                        sizeof(gpu::ImageDrawUniforms));
                    command_buffer->BindUniformBuffer(
                        nvn_api::ShaderStage::FRAGMENT,
                        IMAGE_DRAW_UNIFORM_BUFFER_IDX,
                        address,
                        sizeof(gpu::ImageDrawUniforms));
                }

                command_buffer->BindVertexAttribState(2, m_imageMeshAttribs);
                command_buffer->BindVertexStreamState(2, m_imageMeshStreams);
                command_buffer->BindVertexBuffer(0,
                                                 vertexBuffer->address(),
                                                 vertexBuffer->gpuSize());
                command_buffer->BindVertexBuffer(1,
                                                 uvBuffer->address(),
                                                 uvBuffer->gpuSize());
                command_buffer->DrawElements(
                    nvn_api::DrawPrimitive::TRIANGLES,
                    nvn_api::IndexType::UNSIGNED_SHORT,
                    static_cast<int>(batch.elementCount),
                    indexBuffer->address(batch.baseElement *
                                         sizeof(uint16_t)));
                break;
            }

            case gpu::DrawType::renderPassResolve:
            case gpu::DrawType::renderPassInitialize:
            {
                command_buffer->BindVertexAttribState(0, nullptr);
                command_buffer->BindVertexStreamState(0, nullptr);
                command_buffer->DrawArrays(nvn_api::DrawPrimitive::TRIANGLE_STRIP,
                                           0,
                                           4);
                break;
            }
        }
    }

    if (desc.interlockMode == gpu::InterlockMode::msaa &&
        saw_msaa_draw && !saw_msaa_color)
    {
        static bool s_logged_no_msaa_color = false;
        if (!s_logged_no_msaa_color)
        {
            debug_log(
                "[rive] msaa draw list has no color-writing passes (stencil-only)");
            s_logged_no_msaa_color = true;
        }
    }
}
} // namespace rive::gpu

RiveRenderTarget* rive_nvn_render_target_new(uint32_t width,
                                             uint32_t height,
                                             void* color_texture,
                                             void* depth_texture,
                                             uint32_t sample_count)
{
    return new (std::nothrow) RenderTargetNVN(width,
                                              height,
                                              color_texture,
                                              depth_texture,
                                              sample_count);
}

RiveRenderContextImpl* rive_nvn_render_context_impl_new(
    const RiveNVNContextDesc* desc)
{
    if (!desc)
    {
        return nullptr;
    }

    auto* impl = new (std::nothrow) rive::gpu::RenderContextNVNImpl(
        desc->device,
        desc->queue,
        desc->max_texture_size,
        desc->clip_space_bottom_up != 0,
        desc->framebuffer_bottom_up != 0,
        desc->allocator);
    return reinterpret_cast<RiveRenderContextImpl*>(impl);
}

RiveRenderContext* rive_nvn_render_context_new(const RiveNVNContextDesc* desc)
{
    auto* impl = rive_nvn_render_context_impl_new(desc);
    if (!impl)
    {
        return nullptr;
    }
    return rive_render_context_new(impl);
}
