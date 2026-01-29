#include "rive/capi.h"
#include "nvn/nvn.hpp"
#include "nn/hid.hpp"
#include "nn/ro.h"
#include "skyline/inlinehook/And64InlineHook.hpp"
#include "gfx/managed/allocator.hpp"
#include "gfx/managed/memory.hpp"
#include "nvn_test_config.hpp"
#include "utils.hpp"

#if defined(__GNUC__) || defined(__clang__)
#define RIVE_EXPORT __attribute__((visibility("default"))) __attribute__((used))
#else
#define RIVE_EXPORT
#endif

#ifndef RIVE_NVN_ENABLE_LOGS
#define RIVE_NVN_ENABLE_LOGS 0
#endif

#ifndef RIVE_NVN_ENABLE_TOGGLE_DEBUG_CLEAR
#define RIVE_NVN_ENABLE_TOGGLE_DEBUG_CLEAR 0
#endif

#ifndef RIVE_NVN_ENABLE_POOL_TEST_TOGGLE
#define RIVE_NVN_ENABLE_POOL_TEST_TOGGLE 0
#endif

#ifndef RIVE_NVN_RENDER_IN_PRESENT
#define RIVE_NVN_RENDER_IN_PRESENT 1
#endif

#ifndef RIVE_NVN_ENABLE_RASTER_ORDERING
#define RIVE_NVN_ENABLE_RASTER_ORDERING 0
#endif

#ifndef RIVE_NVN_DEBUG_CLEAR_OFFSCREEN
#define RIVE_NVN_DEBUG_CLEAR_OFFSCREEN 0
#endif

#ifndef RIVE_NVN_FORCE_RASTER_ORDERING
#define RIVE_NVN_FORCE_RASTER_ORDERING 0
#endif

#ifndef RIVE_NVN_FORCE_COPY_TEXTURE
#define RIVE_NVN_FORCE_COPY_TEXTURE 1
#endif

// Hooking nvnWindowAcquireTexture can crash some emulators; keep it off by default.
#ifndef RIVE_NVN_HOOK_WINDOW_ACQUIRE
#define RIVE_NVN_HOOK_WINDOW_ACQUIRE 0
#endif

#ifndef RIVE_NVN_FORCE_MSAA_SAMPLES
#define RIVE_NVN_FORCE_MSAA_SAMPLES 0
#endif

#ifndef RIVE_NVN_ADDR_FALLBACK
#define RIVE_NVN_ADDR_FALLBACK 0
#endif
#if RIVE_NVN_ADDR_FALLBACK
#ifndef RIVE_NVN_BOOTSTRAP_ADDR
#define RIVE_NVN_BOOTSTRAP_ADDR 0x71037f7bd0ULL
#endif
#ifndef RIVE_NVN_DEVICE_INIT_ADDR
#define RIVE_NVN_DEVICE_INIT_ADDR 0x710593f900ULL
#endif
#ifndef RIVE_NVN_DEVICE_GET_PROC_ADDR
#define RIVE_NVN_DEVICE_GET_PROC_ADDR 0x710593f918ULL
#endif
#ifndef RIVE_NVN_QUEUE_SUBMIT_ADDR
#define RIVE_NVN_QUEUE_SUBMIT_ADDR 0x710593fab0ULL
#endif
#ifndef RIVE_NVN_QUEUE_PRESENT_ADDR
#define RIVE_NVN_QUEUE_PRESENT_ADDR 0x710593fac8ULL
#endif
#endif

#if !RIVE_NVN_ENABLE_LOGS
#define debug_log(...) ((void)0)
#endif

#include <atomic>
#include <cctype>
#include <cstdarg>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <new>
#include <vector>

extern "C" {
nvn::GenericFuncPtr nvnBootstrapLoader(const char* symbol);
__attribute__((weak)) void skyline_tcp_send_raw(char* data, size_t size) {
    (void)data;
    (void)size;
}
}

namespace skyline::TcpLogger {
void SendRaw(const void* data, size_t size)
{
    if (!data || size == 0) {
        return;
    }
    skyline_tcp_send_raw(reinterpret_cast<char*>(const_cast<void*>(data)), size);
}

void SendRaw(const char* data)
{
    if (!data) {
        return;
    }
    SendRaw(data, std::strlen(data));
}

void SendRawFormat(const char* format, ...)
{
    if (!format) {
        return;
    }
    va_list args;
    char buff[0x1000] = {0};
    va_start(args, format);
    int len = vsnprintf(buff, sizeof(buff), format, args);
    va_end(args);
    if (len > 0) {
        SendRaw(buff, static_cast<size_t>(len));
    }
}
} // namespace skyline::TcpLogger

namespace {
nvn::TextureTarget view_target_for(nvn::TextureTarget target)
{
    switch (target) {
        case nvn::TextureTarget::TARGET_2D_ARRAY:
        case nvn::TextureTarget::TARGET_CUBEMAP_ARRAY:
            return nvn::TextureTarget::TARGET_2D;
        case nvn::TextureTarget::TARGET_2D_MULTISAMPLE_ARRAY:
            return nvn::TextureTarget::TARGET_2D_MULTISAMPLE;
        default:
            return target;
    }
}

void init_texture_view(nvn::TextureView* view,
                       nvn::TextureTarget target,
                       nvn::Format format)
{
    if (!view) {
        return;
    }
    view->SetDefaults()
        .SetFormat(format)
        .SetTarget(view_target_for(target))
        .SetLevels(0, 1)
        .SetLayers(0, 1);
}

void init_texture_view(nvn::TextureView* view, nvn::Texture* texture)
{
    if (!view || !texture) {
        return;
    }
    init_texture_view(view, texture->GetTarget(), texture->GetFormat());
}

constexpr const char* kDeviceInit = "nvnDeviceInitialize";
constexpr const char* kGetAddress = "nvnDeviceGetProcAddress";
constexpr const char* kWindowSetTextures = "nvnWindowBuilderSetTextures";
constexpr const char* kWindowInitialize = "nvnWindowInitialize";
constexpr const char* kWindowAcquireTexture = "nvnWindowAcquireTexture";
constexpr const char* kQueueSubmit = "nvnQueueSubmitCommands";
constexpr const char* kQueueInitialize = "nvnQueueInitialize";
constexpr const char* kQueuePresent = "nvnQueuePresentTexture";
constexpr const char* kCommandBufferInitialize = "nvnCommandBufferInitialize";
constexpr const char* kCommandBufferBeginRecording = "nvnCommandBufferBeginRecording";
constexpr const char* kCommandBufferEndRecording = "nvnCommandBufferEndRecording";
constexpr const char* kCommandBufferSetTexturePool = "nvnCommandBufferSetTexturePool";
constexpr const char* kCommandBufferSetSamplerPool = "nvnCommandBufferSetSamplerPool";
constexpr const char* kWindowSetCrop = "nvnWindowSetCrop";
#if RIVE_NVN_ADDR_FALLBACK
constexpr uintptr_t kNvnBootstrapLoaderAddr = RIVE_NVN_BOOTSTRAP_ADDR;
constexpr uintptr_t kNvnDeviceInitializeAddr = RIVE_NVN_DEVICE_INIT_ADDR;
constexpr uintptr_t kNvnDeviceGetProcAddressAddr = RIVE_NVN_DEVICE_GET_PROC_ADDR;
constexpr uintptr_t kNvnQueueSubmitAddr = RIVE_NVN_QUEUE_SUBMIT_ADDR;
constexpr uintptr_t kNvnQueuePresentAddr = RIVE_NVN_QUEUE_PRESENT_ADDR;
#endif
constexpr uint64_t kNvnLoaderOffset = 0x37f7bd0;

using NvnLoaderGetProc = nvn::GenericFuncPtr (*)(uintptr_t, const char*);
using NvnLoaderFunc = void (*)(uintptr_t, NvnLoaderGetProc);

static nvn::Device* g_device = nullptr;
static nvn::GetProcAddressPtr g_get_proc_orig = nullptr;

static nvn::NVN_TYPE(QueueSubmitCommands) g_queue_submit_orig = nullptr;
static nvn::NVN_TYPE(QueuePresentTexture) g_queue_present_orig = nullptr;
static nvn::NVN_TYPE(WindowBuilderSetTextures) g_window_set_textures_orig = nullptr;
static nvn::NVN_TYPE(WindowInitialize) g_window_init_orig = nullptr;
static nvn::NVN_TYPE(WindowAcquireTexture) g_window_acquire_orig = nullptr;
static nvn::NVN_TYPE(DeviceInitialize) g_device_init_orig = nullptr;
static nvn::NVN_TYPE(DeviceGetProcAddress) g_device_get_proc_orig = nullptr;
static nvn::NVN_TYPE(QueueInitialize) g_queue_init_orig = nullptr;
static nvn::NVN_TYPE(CommandBufferInitialize) g_command_buffer_init_orig = nullptr;
static nvn::NVN_TYPE(CommandBufferBeginRecording) g_command_buffer_begin_orig = nullptr;
static nvn::NVN_TYPE(CommandBufferEndRecording) g_command_buffer_end_orig = nullptr;
static nvn::NVN_TYPE(CommandBufferSetTexturePool) g_command_set_texture_pool_orig = nullptr;
static nvn::NVN_TYPE(CommandBufferSetSamplerPool) g_command_set_sampler_pool_orig = nullptr;
static nvn::NVN_TYPE(WindowSetCrop) g_window_set_crop_orig = nullptr;
static nvn::GenericFuncPtr (*g_bootstrap_orig)(const char*) = nullptr;
static void (*g_main_loop_orig)(uint32_t*, bool) = nullptr;
static NvnLoaderFunc g_nvn_loader_orig = nullptr;
static NvnLoaderGetProc g_nvn_loader_get_proc_orig = nullptr;

static nvn::Window* g_window = nullptr;
static nvn::WindowBuilder* g_window_builder = nullptr;
static nvn::Texture** g_window_textures = nullptr;
static int g_window_texture_count = 0;
static int g_display_texture_index = -1;
static nvn::WindowBuilder* g_pending_window_builder = nullptr;
static nvn::Texture** g_pending_window_textures = nullptr;
static int g_pending_window_texture_count = 0;
static bool g_logged_window_mismatch = false;
static nvn::Queue* g_queue = nullptr;
static nvn::CommandBuffer* g_cmd_buffer = nullptr;
static const nvn::TexturePool* g_cmd_texture_pool = nullptr;
static const nvn::SamplerPool* g_cmd_sampler_pool = nullptr;
static int g_cmd_buffer_count = 0;
static std::atomic<bool> g_game_cmd_recording{false};
static std::atomic<bool> g_overlay_cmd_recording{false};
static std::atomic<bool> g_bootstrap_active{false};

static bool is_address_in_text(uintptr_t addr)
{
    if (addr < 0x1000) {
        return false;
    }
    void* text = skyline::utils::getRegionAddress(skyline::utils::region::Text);
    void* rodata = skyline::utils::getRegionAddress(skyline::utils::region::Rodata);
    if (!text || !rodata) {
        return false;
    }
    const uintptr_t start = reinterpret_cast<uintptr_t>(text);
    const uintptr_t end = reinterpret_cast<uintptr_t>(rodata);
    if (end <= start) {
        return false;
    }
    return addr >= start && addr < end;
}

static bool should_hook_proc(void* addr, void* hook)
{
    if (!addr || addr == hook) {
        return false;
    }
    return is_address_in_text(reinterpret_cast<uintptr_t>(addr));
}

static nvn::GenericFuncPtr lookup_nvn_symbol(const char* symbol)
{
    if (!symbol) {
        return nullptr;
    }
    if (g_bootstrap_orig && g_bootstrap_active.load(std::memory_order_relaxed)) {
        return g_bootstrap_orig(symbol);
    }
    return nullptr;
}

static nvn::Device* resolve_device_from_queue_builder(const nvn::QueueBuilder* builder)
{
    if (!builder) {
        return nullptr;
    }
    using GetDeviceFn = const nvn::Device* (*)(const nvn::QueueBuilder*);
    static GetDeviceFn s_get_device = nullptr;
    static bool s_logged_missing = false;
    if (!s_get_device) {
        s_get_device = reinterpret_cast<GetDeviceFn>(
            lookup_nvn_symbol("nvnQueueBuilderGetDevice"));
        if (!s_get_device && !s_logged_missing) {
            debug_log("[rive] nvnQueueBuilderGetDevice missing");
            s_logged_missing = true;
        }
    }
    if (!s_get_device) {
        return nullptr;
    }
    return const_cast<nvn::Device*>(s_get_device(builder));
}

void set_error(const char* message);
static void clear_texture_color(nvn::CommandBuffer* cmd,
                                nvn::Texture* tex,
                                const float* color);
static void clear_window_texture(nvn::CommandBuffer* cmd, nvn::Texture* tex);
void update_toggle_input();
void install_queue_hooks();
void install_window_hooks();
void ensure_device_initialized(nvn::Device* device);
bool nvnDeviceInitialize_hook(nvn::Device* device, const nvn::DeviceBuilder* builder);
nvn::GenericFuncPtr nvnDeviceGetProcAddress_hook(const nvn::Device* device,
                                                 const char* procName);
bool nvnQueueInitialize_hook(nvn::Queue* queue, const nvn::QueueBuilder* builder);
bool nvnCommandBufferInitialize_hook(nvn::CommandBuffer* buffer, nvn::Device* device);
void nvnCommandBufferBeginRecording_hook(nvn::CommandBuffer* buffer);
nvn::CommandHandle nvnCommandBufferEndRecording_hook(nvn::CommandBuffer* buffer);
void nvnCommandBufferSetTexturePool_hook(nvn::CommandBuffer* cmd_buf,
                                         const nvn::TexturePool* pool);
void nvnCommandBufferSetSamplerPool_hook(nvn::CommandBuffer* cmd_buf,
                                         const nvn::SamplerPool* pool);
void nvnQueuePresentTexture_hook(nvn::Queue* queue, nvn::Window* window, int texture_index);
void nvnQueueSubmitCommands_hook(nvn::Queue* queue,
                                 int count,
                                 const nvn::CommandHandle* handles);
void nvnWindowSetCrop_hook(nvn::Window* window, int x, int y, int w, int h);
void nvnWindowBuilderSetTextures_hook(nvn::WindowBuilder* builder,
                                      int count,
                                      nvn::Texture* const* textures);
bool nvnWindowInitialize_hook(nvn::Window* window, const nvn::WindowBuilder* builder);
nvn::WindowAcquireTextureResult::Enum nvnWindowAcquireTexture_hook(
    nvn::Window* window,
    nvn::Sync* texture_available,
    int* index);


#ifndef RIVE_NVN_COMMAND_BUFFER_ID
#define RIVE_NVN_COMMAND_BUFFER_ID 1
#endif

struct HostState {
    RiveRenderContext* context = nullptr;
    RiveRenderer* renderer = nullptr;
    RiveRenderTarget* target = nullptr;
    nvn::Texture* target_texture = nullptr;
    nvn::Texture* target_depth = nullptr;
    uint32_t target_width = 0;
    uint32_t target_height = 0;
    uint32_t sample_count = 1;
    nvn::CommandBuffer* command_buffer = nullptr;
    uint64_t frame = 0;
};

struct OffscreenTarget {
    nvn::Texture texture;
    nvn::TextureView view;
    nvn::MemoryPool pool;
    void* memory = nullptr;
    size_t memory_size = 0;
    nvn::Texture depth_texture;
    nvn::TextureView depth_view;
    nvn::MemoryPool depth_pool;
    void* depth_memory = nullptr;
    size_t depth_memory_size = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    int depth = 1;
    int levels = 1;
    int samples = 0;
    ptrdiff_t stride = 0;
    nvn::Format format = nvn::Format::RGBA8;
    nvn::TextureFlags flags = nvn::TextureFlags(0);
    nvn::TextureTarget target = nvn::TextureTarget::TARGET_2D;
    bool initialized = false;
    nvn::Format depth_format = nvn::Format::DEPTH24_STENCIL8;
    nvn::TextureFlags depth_flags = nvn::TextureFlags(0);
    nvn::TextureTarget depth_target = nvn::TextureTarget::TARGET_2D;
    bool depth_initialized = false;
};

struct OverlayCommandBuffer {
    nvn::CommandBuffer buffer;
    nvn::MemoryPool pool;
    void* pool_memory = nullptr;
    size_t pool_size = 0;
    void* control_memory = nullptr;
    size_t control_size = 0;
    bool initialized = false;
};

struct OverlayCommandMemoryBlock {
    nvn::MemoryPool pool;
    void* memory = nullptr;
    size_t size = 0;
};

struct BlitState {
    GfxAllocator* allocator = nullptr;
    nvn::TexturePool texture_pool;
    nvn::SamplerPool sampler_pool;
    nvn::Sampler sampler;
    nvn::BlendState blend_state;
    nvn::ColorState color_state;
    nvn::ChannelMaskState mask_state;
    nvn::DepthStencilState depth_state;
    nvn::MultisampleState multisample_state;
    nvn::PolygonState polygon_state;
    nvn::TextureView view;
    nvn::Texture* texture = nullptr;
    nvn::TextureHandle handle = 0;
    bool initialized = false;
    bool state_initialized = false;
};

static HostState g_host;
static OffscreenTarget g_offscreen_resolve;
static OffscreenTarget g_offscreen_msaa;
static OverlayCommandBuffer g_overlay_cmd;
static std::vector<OverlayCommandMemoryBlock*> g_overlay_cmd_blocks;
static std::vector<void*> g_overlay_ctrl_blocks;
static std::atomic<bool> g_overlay_cmd_initializing{false};
static BlitState g_blit;
static std::atomic<RiveArtboard*> g_artboard{nullptr};
static std::atomic<const uint8_t*> g_pending_riv_data{nullptr};
static std::atomic<size_t> g_pending_riv_len{0};
static RiveFile* g_pending_file = nullptr;
static RiveArtboard* g_pending_artboard = nullptr;
static std::atomic<bool> g_enabled{false};
static std::atomic<bool> g_hooks_installed{false};
static std::atomic<bool> g_allocator_set{false};
static RiveNVNAllocator g_allocator = {};
static std::atomic<bool> g_allocator_default{false};

static uint64_t g_prev_buttons = 0;
static std::atomic<bool> g_logged_toggle_probe{false};
static std::atomic<bool> g_input_hooks_installed{false};
static std::atomic<bool> g_device_initialized{false};
static const char* g_last_error = "idle";
static nvn::Queue* g_last_queue = nullptr;
static bool g_logged_render_attempt = false;
static bool g_logged_window_info = false;
static std::atomic<int> g_render_mode{RIVE_RUNTIME_RENDER_DIRECT};
static int g_supports_draw_texture = -1;
static std::atomic<bool> g_log_window_info{false};
static std::atomic<bool> g_force_debug_clear{false};
static std::atomic<bool> g_force_debug_clear_all{false};
static std::atomic<bool> g_force_debug_clear_offscreen{false};
static std::atomic<int> g_force_msaa_samples{RIVE_NVN_FORCE_MSAA_SAMPLES};
static std::atomic<bool> g_render_in_present{RIVE_NVN_RENDER_IN_PRESENT != 0};
static std::atomic<bool> g_rendered_this_frame{false};
static std::atomic<bool> g_rendering{false};
static std::atomic<bool> g_toggle_clear_pending{false};
static bool g_logged_riv_info = false;

using RiveToggleCallback = void (*)(const RiveRuntimeStatus*, uint64_t);
static RiveToggleCallback g_toggle_callback = nullptr;

void ensure_device_initialized(nvn::Device* device)
{
    if (!device) {
        return;
    }
    if (!g_device) {
        g_device = device;
    }
    if (g_device_initialized.load(std::memory_order_relaxed)) {
        return;
    }
    if (!g_device_get_proc_orig) {
        nvn::GenericFuncPtr get_proc = lookup_nvn_symbol(kGetAddress);
        if (get_proc) {
            g_device_get_proc_orig =
                reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(get_proc);
        }
    }
    if (!g_device_get_proc_orig) {
        return;
    }
    g_get_proc_orig =
        reinterpret_cast<nvn::GetProcAddressPtr>(g_device_get_proc_orig);
    nvn::initialize(g_device, g_get_proc_orig);
    if (g_supports_draw_texture < 0) {
        int supports_draw = 0;
        g_device->GetInteger(nvn::DeviceInfo::SUPPORTS_DRAW_TEXTURE,
                             &supports_draw);
        g_supports_draw_texture = supports_draw;
    }
    install_queue_hooks();
    install_window_hooks();
    g_device_initialized.store(true, std::memory_order_relaxed);
    set_error("device-ready");
}

constexpr const char* kPoolTestConfigPath = "sdmc:/rive/pool_test.cfg";
constexpr const char* kPoolTestIndexPath = "sdmc:/rive/pool_test.idx";
#ifndef RIVE_POOL_TEST_FS
#define RIVE_POOL_TEST_FS 0
#endif
constexpr const char* kPoolTestConfigDefault =
    "# Rive NVN descriptor pool tests\n"
    "# flags: CPU_UNCACHED|GPU_CACHED or CPU_CACHED|GPU_CACHED\n"
    "# *_count overrides descriptor counts; *_pool_pages uses MEMORY_POOL_PAGE_SIZE\n"
    "# *_extra_pages adds pages to the computed size\n"
    "case name=base_uncached flags=CPU_UNCACHED|GPU_CACHED\n"
    "case name=base_cached flags=CPU_CACHED|GPU_CACHED\n"
    "case name=small_counts flags=CPU_UNCACHED|GPU_CACHED sampler_count=274 texture_count=512\n"
    "case name=sampler_pages_2 flags=CPU_UNCACHED|GPU_CACHED sampler_pool_pages=2\n"
    "case name=sampler_pages_4 flags=CPU_UNCACHED|GPU_CACHED sampler_pool_pages=4\n"
    "case name=texture_pages_2 flags=CPU_UNCACHED|GPU_CACHED texture_pool_pages=2\n"
    "case name=texture_pages_4 flags=CPU_UNCACHED|GPU_CACHED texture_pool_pages=4\n"
    "case name=both_pages_2 flags=CPU_UNCACHED|GPU_CACHED sampler_pool_pages=2 texture_pool_pages=2\n"
    "case name=both_pages_4 flags=CPU_UNCACHED|GPU_CACHED sampler_pool_pages=4 texture_pool_pages=4\n"
    "case name=extra_pages flags=CPU_UNCACHED|GPU_CACHED sampler_extra_pages=1 texture_extra_pages=1\n";

static std::atomic<uint32_t> g_pool_test_version{1};
static std::atomic<bool> g_pool_test_valid{false};
static RiveDescriptorPoolTestCase g_pool_test_case = {};
static std::atomic<int> g_pool_test_index{0};
static std::atomic<int> g_pool_test_total{0};
#if RIVE_POOL_TEST_FS
static std::atomic<int> g_pool_test_fs_state{0};

static bool ensure_pool_test_fs_ready()
{
    int state = g_pool_test_fs_state.load(std::memory_order_relaxed);
    if (state != 0) {
        return state > 0;
    }
    if (!nn::fs::IsSdCardInserted()) {
        debug_log("[rive] pool test fs: sdcard not inserted");
        g_pool_test_fs_state.store(-1, std::memory_order_relaxed);
        return false;
    }
    Result rc = nn::fs::MountSdCard("sdmc");
    if (!R_SUCCEEDED(rc)) {
        Result rc_debug = nn::fs::MountSdCardForDebug("sdmc");
        if (!R_SUCCEEDED(rc_debug)) {
            debug_log("[rive] pool test fs: mount failed rc=0x%x dbg=0x%x",
                      static_cast<unsigned int>(rc),
                      static_cast<unsigned int>(rc_debug));
            g_pool_test_fs_state.store(-1, std::memory_order_relaxed);
            return false;
        }
        debug_log("[rive] pool test fs: mounted sdmc (debug)");
    } else {
        debug_log("[rive] pool test fs: mounted sdmc");
    }
    g_pool_test_fs_state.store(1, std::memory_order_relaxed);
    return true;
}
#else
static bool ensure_pool_test_fs_ready()
{
    return false;
}
#endif

constexpr uint64_t kSmashControllerUpdateOffset = 0x3f7260;
constexpr uint64_t kSmashControllerUpdateNonPlayerOffset = 0x6b7ff8;

void smash_controller_update_hook(InlineCtx* ctx)
{
    (void)ctx;
    update_toggle_input();
}

void smash_controller_update_non_player_hook(InlineCtx* ctx)
{
    (void)ctx;
    update_toggle_input();
}

void install_input_hooks()
{
    if (g_input_hooks_installed.load(std::memory_order_relaxed)) {
        return;
    }
    void* base = skyline::utils::getRegionAddress(skyline::utils::region::Text);
    if (!base) {
        set_error("input hook text base missing");
        return;
    }
    A64InlineHook(reinterpret_cast<char*>(base) + kSmashControllerUpdateOffset,
                  reinterpret_cast<void*>(smash_controller_update_hook));
    A64InlineHook(reinterpret_cast<char*>(base) +
                      kSmashControllerUpdateNonPlayerOffset,
                  reinterpret_cast<void*>(smash_controller_update_non_player_hook));
    g_input_hooks_installed.store(true, std::memory_order_relaxed);
}

nvn::GenericFuncPtr nvn_loader_get_proc_hook(uintptr_t handle, const char* symbol)
{
    if (!g_nvn_loader_get_proc_orig) {
        return nullptr;
    }
    nvn::GenericFuncPtr ret = g_nvn_loader_get_proc_orig(handle, symbol);
    if (!ret || !symbol) {
        return ret;
    }
    if (std::strcmp(symbol, kDeviceInit) == 0) {
        if (!g_device_init_orig) {
            void* orig = nullptr;
            A64HookFunction(reinterpret_cast<void*>(ret),
                            reinterpret_cast<void*>(nvnDeviceInitialize_hook),
                            &orig);
            if (orig) {
                g_device_init_orig =
                    reinterpret_cast<nvn::NVN_TYPE(DeviceInitialize)>(orig);
            }
        }
        return ret;
    }
    if (std::strcmp(symbol, kGetAddress) == 0) {
        if (!g_device_get_proc_orig) {
            void* orig = nullptr;
            A64HookFunction(reinterpret_cast<void*>(ret),
                            reinterpret_cast<void*>(nvnDeviceGetProcAddress_hook),
                            &orig);
            if (orig) {
                g_device_get_proc_orig =
                    reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(orig);
            } else {
                g_device_get_proc_orig =
                    reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(ret);
            }
        }
        return ret;
    }
    return ret;
}

void nvn_loader_hook(uintptr_t handle, NvnLoaderGetProc loader)
{
    if (!g_nvn_loader_orig) {
        return;
    }
    g_bootstrap_active.store(true, std::memory_order_relaxed);
    if (!g_nvn_loader_get_proc_orig && loader) {
        g_nvn_loader_get_proc_orig = loader;
    }
    if (g_nvn_loader_get_proc_orig) {
        g_nvn_loader_orig(handle, nvn_loader_get_proc_hook);
    } else {
        g_nvn_loader_orig(handle, loader);
    }
}

#if RIVE_POOL_TEST_FS
static void ensure_pool_test_dir()
{
    if (!ensure_pool_test_fs_ready()) {
        return;
    }
    nn::fs::CreateDirectory("sdmc:/rive");
}

static bool read_text_file(const char* path, std::vector<char>& out)
{
    if (!path) {
        return false;
    }
    if (!ensure_pool_test_fs_ready()) {
        return false;
    }
    nn::fs::FileHandle handle;
    Result result =
        nn::fs::OpenFile(&handle, path, nn::fs::OpenMode::OpenMode_Read);
    if (!R_SUCCEEDED(result)) {
        return false;
    }
    int64_t size = 0;
    result = nn::fs::GetFileSize(&size, handle);
    if (!R_SUCCEEDED(result) || size <= 0) {
        nn::fs::CloseFile(handle);
        return false;
    }
    out.resize(static_cast<size_t>(size) + 1);
    result = nn::fs::ReadFile(handle, 0, out.data(), static_cast<size_t>(size));
    nn::fs::CloseFile(handle);
    if (!R_SUCCEEDED(result)) {
        return false;
    }
    out[static_cast<size_t>(size)] = '\0';
    return true;
}

static int load_pool_test_index()
{
    if (!ensure_pool_test_fs_ready()) {
        return 0;
    }
    nn::fs::FileHandle handle;
    Result result =
        nn::fs::OpenFile(&handle, kPoolTestIndexPath, nn::fs::OpenMode::OpenMode_Read);
    if (!R_SUCCEEDED(result)) {
        return 0;
    }
    int index = 0;
    result = nn::fs::ReadFile(handle, 0, &index, sizeof(index));
    nn::fs::CloseFile(handle);
    if (!R_SUCCEEDED(result)) {
        return 0;
    }
    return index;
}

static void save_pool_test_index(int index)
{
    if (!ensure_pool_test_fs_ready()) {
        return;
    }
    ensure_pool_test_dir();
    nn::fs::FileHandle handle;
    Result result =
        nn::fs::OpenFile(&handle,
                         kPoolTestIndexPath,
                         nn::fs::OpenMode::OpenMode_Write);
    if (!R_SUCCEEDED(result)) {
        nn::fs::CreateFile(kPoolTestIndexPath, sizeof(index));
        result = nn::fs::OpenFile(&handle,
                                  kPoolTestIndexPath,
                                  nn::fs::OpenMode::OpenMode_Write);
    }
    if (!R_SUCCEEDED(result)) {
        return;
    }
    nn::fs::WriteFile(handle,
                      0,
                      &index,
                      sizeof(index),
                      nn::fs::WriteOption::CreateOption(
                          nn::fs::WriteOptionFlag_Flush));
    nn::fs::CloseFile(handle);
}
#else
static void ensure_pool_test_dir()
{
}

static bool read_text_file(const char*, std::vector<char>&)
{
    return false;
}

static int load_pool_test_index()
{
    return 0;
}

static void save_pool_test_index(int)
{
}
#endif

static void set_default_pool_tests(std::vector<RiveDescriptorPoolTestCase>& cases)
{
    cases.clear();
    RiveDescriptorPoolTestCase tc = {};
    tc.flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_UNCACHED |
                                     nvn::MemoryPoolFlags::GPU_CACHED);
    std::snprintf(tc.name, sizeof(tc.name), "cpu_uncached");
    cases.push_back(tc);

    tc = {};
    tc.flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_NO_ACCESS |
                                     nvn::MemoryPoolFlags::GPU_CACHED);
    std::snprintf(tc.name, sizeof(tc.name), "no_access");
    cases.push_back(tc);

    tc = {};
    tc.flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_CACHED |
                                     nvn::MemoryPoolFlags::GPU_CACHED);
    std::snprintf(tc.name, sizeof(tc.name), "cpu_cached");
    cases.push_back(tc);
}

static void trim_line(char* line)
{
    if (!line) {
        return;
    }
    char* start = line;
    while (*start && std::isspace(static_cast<unsigned char>(*start))) {
        ++start;
    }
    if (start != line) {
        std::memmove(line, start, std::strlen(start) + 1);
    }
    size_t len = std::strlen(line);
    while (len > 0 &&
           std::isspace(static_cast<unsigned char>(line[len - 1]))) {
        line[len - 1] = '\0';
        --len;
    }
}

static uint32_t parse_pool_flags(const char* value)
{
    uint32_t cpu_flags = 0;
    uint32_t gpu_flags = 0;
    uint32_t other_flags = 0;
    if (!value) {
        return static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_UNCACHED |
                                     nvn::MemoryPoolFlags::GPU_CACHED);
    }
    const char* cursor = value;
    while (*cursor) {
        while (*cursor == '|' || *cursor == ',' || std::isspace(static_cast<unsigned char>(*cursor))) {
            ++cursor;
        }
        if (!*cursor) {
            break;
        }
        char token[64] = {};
        size_t token_len = 0;
        while (*cursor && *cursor != '|' && *cursor != ',' &&
               !std::isspace(static_cast<unsigned char>(*cursor))) {
            if (token_len + 1 < sizeof(token)) {
                token[token_len++] =
                    static_cast<char>(std::toupper(static_cast<unsigned char>(*cursor)));
            }
            ++cursor;
        }
        token[token_len] = '\0';
        if (std::strcmp(token, "CPU_NO_ACCESS") == 0) {
            cpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_NO_ACCESS);
        } else if (std::strcmp(token, "CPU_UNCACHED") == 0) {
            cpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_UNCACHED);
        } else if (std::strcmp(token, "CPU_CACHED") == 0) {
            cpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_CACHED);
        } else if (std::strcmp(token, "GPU_NO_ACCESS") == 0) {
            gpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::GPU_NO_ACCESS);
        } else if (std::strcmp(token, "GPU_UNCACHED") == 0) {
            gpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::GPU_UNCACHED);
        } else if (std::strcmp(token, "GPU_CACHED") == 0) {
            gpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::GPU_CACHED);
        } else if (std::strcmp(token, "SHADER_CODE") == 0) {
            other_flags |= static_cast<uint32_t>(nvn::MemoryPoolFlags::SHADER_CODE);
        }
    }
    if (cpu_flags == 0) {
        cpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::CPU_UNCACHED);
    }
    if (gpu_flags == 0) {
        gpu_flags = static_cast<uint32_t>(nvn::MemoryPoolFlags::GPU_CACHED);
    }
    return cpu_flags | gpu_flags | other_flags;
}

static bool parse_int_value(const char* value, int* out)
{
    if (!value || !out) {
        return false;
    }
    char* end = nullptr;
    long parsed = std::strtol(value, &end, 10);
    if (end == value) {
        return false;
    }
    *out = static_cast<int>(parsed);
    return true;
}

static void finalize_pool_test_case(std::vector<RiveDescriptorPoolTestCase>& cases,
                                    RiveDescriptorPoolTestCase& tc,
                                    int index)
{
    if (tc.name[0] == '\0') {
        std::snprintf(tc.name, sizeof(tc.name), "case_%d", index);
    }
    cases.push_back(tc);
    tc = {};
}

static bool load_pool_test_config(std::vector<RiveDescriptorPoolTestCase>& cases)
{
    std::vector<char> contents;
    if (!read_text_file(kPoolTestConfigPath, contents)) {
        return false;
    }
    cases.clear();
    RiveDescriptorPoolTestCase current = {};
    bool has_current = false;
    int case_index = 0;
    char* cursor = contents.data();
    while (cursor && *cursor) {
        char* line = cursor;
        char* line_end = std::strchr(cursor, '\n');
        if (line_end) {
            *line_end = '\0';
            cursor = line_end + 1;
        } else {
            cursor = nullptr;
        }
        char* comment = std::strchr(line, '#');
        if (comment) {
            *comment = '\0';
        }
        trim_line(line);
        if (line[0] == '\0') {
            if (has_current) {
                finalize_pool_test_case(cases, current, case_index++);
                has_current = false;
            }
            continue;
        }
        const bool starts_with_case =
            std::strncmp(line, "case", 4) == 0 &&
            (line[4] == '\0' || std::isspace(static_cast<unsigned char>(line[4])));
        if (starts_with_case) {
            if (has_current) {
                finalize_pool_test_case(cases, current, case_index++);
            }
            has_current = true;
            current = {};
            line += 4;
        } else if (!has_current) {
            has_current = true;
            current = {};
        }
        while (*line) {
            while (*line && std::isspace(static_cast<unsigned char>(*line))) {
                ++line;
            }
            if (!*line) {
                break;
            }
            char* token = line;
            while (*line && !std::isspace(static_cast<unsigned char>(*line))) {
                ++line;
            }
            char saved = *line;
            *line = '\0';
            char* eq = std::strchr(token, '=');
            if (eq) {
                *eq = '\0';
                const char* key = token;
                const char* value = eq + 1;
                if (std::strcmp(key, "name") == 0) {
                    std::snprintf(current.name, sizeof(current.name), "%s", value);
                } else if (std::strcmp(key, "flags") == 0) {
                    current.flags = parse_pool_flags(value);
                } else if (std::strcmp(key, "sampler_count") == 0) {
                    parse_int_value(value, &current.sampler_count);
                } else if (std::strcmp(key, "texture_count") == 0) {
                    parse_int_value(value, &current.texture_count);
                } else if (std::strcmp(key, "sampler_extra_pages") == 0) {
                    parse_int_value(value, &current.sampler_extra_pages);
                } else if (std::strcmp(key, "texture_extra_pages") == 0) {
                    parse_int_value(value, &current.texture_extra_pages);
                } else if (std::strcmp(key, "sampler_pool_pages") == 0) {
                    parse_int_value(value, &current.sampler_pool_pages);
                } else if (std::strcmp(key, "texture_pool_pages") == 0) {
                    parse_int_value(value, &current.texture_pool_pages);
                }
            }
            *line = saved;
        }
    }
    if (has_current) {
        finalize_pool_test_case(cases, current, case_index++);
    }
    return !cases.empty();
}

#if RIVE_POOL_TEST_FS
static void write_default_pool_test_config_file()
{
    if (!ensure_pool_test_fs_ready()) {
        return;
    }
    ensure_pool_test_dir();
    nn::fs::FileHandle handle;
    Result result =
        nn::fs::OpenFile(&handle, kPoolTestConfigPath, nn::fs::OpenMode::OpenMode_Read);
    if (R_SUCCEEDED(result)) {
        nn::fs::CloseFile(handle);
        return;
    }
    const size_t size = std::strlen(kPoolTestConfigDefault);
    nn::fs::CreateFile(kPoolTestConfigPath, static_cast<s64>(size));
    result =
        nn::fs::OpenFile(&handle, kPoolTestConfigPath, nn::fs::OpenMode::OpenMode_Write);
    if (!R_SUCCEEDED(result)) {
        return;
    }
    nn::fs::WriteFile(handle,
                      0,
                      kPoolTestConfigDefault,
                      size,
                      nn::fs::WriteOption::CreateOption(
                          nn::fs::WriteOptionFlag_Flush));
    nn::fs::CloseFile(handle);
    debug_log("[rive] pool test config created: %s", kPoolTestConfigPath);
}
#else
static void write_default_pool_test_config_file()
{
}
#endif

static void advance_pool_test_case()
{
    debug_log("[rive] pool test advance begin");
    static int s_pool_test_session_index = 0;
    std::vector<RiveDescriptorPoolTestCase> cases;
    const bool fs_ready = ensure_pool_test_fs_ready();
    bool loaded = fs_ready && load_pool_test_config(cases);
    if (!loaded) {
        set_default_pool_tests(cases);
        if (fs_ready) {
            write_default_pool_test_config_file();
            debug_log("[rive] pool test config missing: %s", kPoolTestConfigPath);
        } else {
            debug_log("[rive] pool test fs unavailable; using built-in cases");
            static bool s_logged_builtin_config = false;
            if (!s_logged_builtin_config) {
                s_logged_builtin_config = true;
                debug_log("[rive] pool test config (built-in):");
                const char* cursor = kPoolTestConfigDefault;
                while (*cursor) {
                    const char* line_end = std::strchr(cursor, '\n');
                    size_t len = line_end ? static_cast<size_t>(line_end - cursor)
                                          : std::strlen(cursor);
                    if (len > 0) {
                        char line[256] = {};
                        if (len >= sizeof(line)) {
                            len = sizeof(line) - 1;
                        }
                        std::memcpy(line, cursor, len);
                        line[len] = '\0';
                        debug_log("[rive] %s", line);
                    }
                    if (!line_end) {
                        break;
                    }
                    cursor = line_end + 1;
                }
            }
        }
    }
    if (cases.empty()) {
        return;
    }
    const int total = static_cast<int>(cases.size());
    int index = fs_ready ? load_pool_test_index() : s_pool_test_session_index;
    if (index < 0 || index >= total) {
        index = 0;
    }
    const RiveDescriptorPoolTestCase& tc = cases[index];
    rive_nvn_set_descriptor_pool_test_case(&tc, index, total);
    const int remaining = (total - 1) - index;
    debug_log("[rive] pool test case %d/%d name=%s flags=0x%x sampler_count=%d texture_count=%d sampler_pages=%d texture_pages=%d sampler_extra=%d texture_extra=%d remaining=%d",
              index + 1,
              total,
              tc.name[0] ? tc.name : "<unnamed>",
              tc.flags,
              tc.sampler_count,
              tc.texture_count,
              tc.sampler_pool_pages,
              tc.texture_pool_pages,
              tc.sampler_extra_pages,
              tc.texture_extra_pages,
              remaining < 0 ? 0 : remaining);
    int next = index + 1;
    if (next >= total) {
        next = 0;
    }
    if (fs_ready) {
        save_pool_test_index(next);
    } else {
        s_pool_test_session_index = next;
    }
}

struct GameAllocFns
{
    void* (*aligned_alloc_fn)(size_t, size_t) = nullptr;
    void* (*realloc_fn)(void*, size_t) = nullptr;
    void (*free_fn)(void*) = nullptr;
    bool resolved = false;
    bool valid = false;
};

static GameAllocFns g_game_alloc;

static size_t align_up_size(size_t value, size_t align)
{
    if (align == 0) {
        return value;
    }
    return (value + align - 1) & ~(align - 1);
}

static void resolve_game_allocators()
{
    if (g_game_alloc.resolved) {
        return;
    }
    uintptr_t addr = 0;
    if (R_SUCCEEDED(nn::ro::LookupSymbol(&addr, "aligned_alloc"))) {
        g_game_alloc.aligned_alloc_fn =
            reinterpret_cast<void* (*)(size_t, size_t)>(addr);
    }
    if (R_SUCCEEDED(nn::ro::LookupSymbol(&addr, "realloc"))) {
        g_game_alloc.realloc_fn =
            reinterpret_cast<void* (*)(void*, size_t)>(addr);
    }
    if (R_SUCCEEDED(nn::ro::LookupSymbol(&addr, "free"))) {
        g_game_alloc.free_fn =
            reinterpret_cast<void (*)(void*)>(addr);
    }
    g_game_alloc.valid = g_game_alloc.aligned_alloc_fn &&
                         g_game_alloc.realloc_fn &&
                         g_game_alloc.free_fn;
    g_game_alloc.resolved = true;
}

static void* default_alloc(size_t size, size_t alignment, void*)
{
    resolve_game_allocators();
    if (alignment == 0) {
        alignment = 0x1000;
    }
    const size_t aligned_size = align_up_size(size, alignment);
    if (g_game_alloc.valid) {
        return g_game_alloc.aligned_alloc_fn(alignment, aligned_size);
    }
    return GlobalAllocator::AllocAligned(aligned_size, alignment);
}

static void* default_realloc(void* ptr, size_t new_size, void*)
{
    resolve_game_allocators();
    if (g_game_alloc.valid && g_game_alloc.realloc_fn) {
        return g_game_alloc.realloc_fn(ptr, new_size);
    }
    return GlobalAllocator::Realloc(ptr, new_size);
}

static void default_free(void* ptr, void*)
{
    resolve_game_allocators();
    if (g_game_alloc.valid && g_game_alloc.free_fn) {
        g_game_alloc.free_fn(ptr);
        return;
    }
    GlobalAllocator::Free(ptr);
}

static void ensure_default_allocator()
{
    if (g_allocator_set.load(std::memory_order_relaxed)) {
        return;
    }
    g_allocator.alloc = default_alloc;
    g_allocator.realloc = default_realloc;
    g_allocator.free = default_free;
    g_allocator.user = nullptr;
    g_allocator_set.store(true, std::memory_order_relaxed);
    g_allocator_default.store(true, std::memory_order_relaxed);
    debug_log("[rive] allocator default enabled");
}

void set_error(const char* message)
{
    g_last_error = message ? message : "unknown";
}

void log_status(const char* reason)
{
    const bool enabled = g_enabled.load(std::memory_order_relaxed);
    RiveArtboard* artboard = g_artboard.load(std::memory_order_relaxed);
    float art_w = artboard ? rive_artboard_width(artboard) : 0.0f;
    float art_h = artboard ? rive_artboard_height(artboard) : 0.0f;
    debug_log(
        "[rive] %s enabled=%d artboard=%p artboard_w=%.2f artboard_h=%.2f device=%p queue=%p ctx=%p renderer=%p target=%p target_w=%u target_h=%u textures=%d index=%d hooks=%d queue_hook=%d window_hook=%d last_error=%s",
        reason ? reason : "status",
        enabled ? 1 : 0,
        artboard,
        art_w,
        art_h,
        g_device,
        g_last_queue,
        g_host.context,
        g_host.renderer,
        g_host.target,
        g_host.target_width,
        g_host.target_height,
        g_window_texture_count,
        g_display_texture_index,
        g_hooks_installed.load(std::memory_order_relaxed) ? 1 : 0,
        g_queue_submit_orig ? 1 : 0,
        (g_window_set_textures_orig && g_window_acquire_orig) ? 1 : 0,
        g_last_error ? g_last_error : "none");
}

void ensure_hid_initialized()
{
    static bool s_initialized = false;
    if (!s_initialized) {
        nn::hid::InitializeNpad();
        s_initialized = true;
    }
}

void update_toggle_input()
{
    ensure_hid_initialized();
    nn::hid::NpadFullKeyState state{};
    constexpr uint32_t kNpadId = nn::hid::CONTROLLER_PLAYER_1;
    nn::hid::GetNpadState(&state, kNpadId);
    if ((state.Flags & nn::hid::NPAD_CONNECTED) == 0) {
        nn::hid::GetNpadState(
            reinterpret_cast<nn::hid::NpadJoyDualState*>(&state),
            kNpadId);
        if ((kNpadId == nn::hid::CONTROLLER_PLAYER_1) &&
            ((state.Flags & nn::hid::NPAD_CONNECTED) == 0)) {
            nn::hid::GetNpadState(
                reinterpret_cast<nn::hid::NpadHandheldState*>(&state),
                nn::hid::CONTROLLER_HANDHELD);
        }
    }
    uint64_t buttons = state.Buttons;
    if ((nn::hid::GetNpadStyleSet(kNpadId) & (1 << 5)) != 0) {
        nn::hid::NpadGcState gc{};
        nn::hid::GetNpadState(&gc, kNpadId);
        if ((gc.Flags & nn::hid::NPAD_CONNECTED) != 0 || gc.Buttons != 0) {
            buttons = gc.Buttons;
        }
    }
    if (g_toggle_callback &&
        !g_logged_toggle_probe.exchange(true, std::memory_order_relaxed)) {
        RiveRuntimeStatus status = {};
        rive_runtime_get_status(&status);
        constexpr uint64_t kProbeMask = (1ull << 63);
        g_toggle_callback(&status, buttons | kProbeMask);
    }
    constexpr uint64_t kToggleMaskLR = nn::hid::KEY_L | nn::hid::KEY_R;
    constexpr uint64_t kToggleMaskToggle = nn::hid::KEY_X | nn::hid::KEY_PLUS;
    bool pressed = ((buttons & kToggleMaskLR) == kToggleMaskLR) &&
        ((buttons & kToggleMaskToggle) != 0);
    bool prev_pressed = ((g_prev_buttons & kToggleMaskLR) == kToggleMaskLR) &&
        ((g_prev_buttons & kToggleMaskToggle) != 0);
    if (pressed && !prev_pressed) {
        bool next = !g_enabled.load(std::memory_order_relaxed);
        g_enabled.store(next, std::memory_order_relaxed);
#if RIVE_NVN_ENABLE_TOGGLE_DEBUG_CLEAR
        g_toggle_clear_pending.store(true, std::memory_order_relaxed);
#endif
        g_logged_render_attempt = false;
        if (next) {
#if RIVE_NVN_ENABLE_TOGGLE_DEBUG_CLEAR
            g_force_debug_clear.store(true, std::memory_order_relaxed);
            g_force_debug_clear_all.store(true, std::memory_order_relaxed);
            g_force_debug_clear_offscreen.store(true,
                                                std::memory_order_relaxed);
#endif
        }
        log_status("toggle");
#if RIVE_NVN_ENABLE_POOL_TEST_TOGGLE
        advance_pool_test_case();
#endif
        if (g_toggle_callback) {
            RiveRuntimeStatus status = {};
            rive_runtime_get_status(&status);
            g_toggle_callback(&status, buttons);
        }
    }
    g_prev_buttons = buttons;
}

void main_loop_hook(uint32_t* ptr, bool camera_only)
{
    update_toggle_input();
    if (g_main_loop_orig) {
        g_main_loop_orig(ptr, camera_only);
    }
}

bool ensure_artboard_loaded()
{
    RiveArtboard* artboard = g_artboard.load(std::memory_order_relaxed);
    if (artboard) {
        return true;
    }

    const uint8_t* data = g_pending_riv_data.load(std::memory_order_relaxed);
    size_t len = g_pending_riv_len.load(std::memory_order_relaxed);
    if (!data || len == 0) {
        set_error("artboard not set");
        return false;
    }
    if (!g_host.context) {
        set_error("context not ready");
        return false;
    }
    if (!g_pending_file) {
        RiveImportResult result = RIVE_IMPORT_MALFORMED;
        g_pending_file =
            rive_file_import_with_render_context(g_host.context,
                                                 data,
                                                 len,
                                                 &result);
        if (!g_pending_file) {
            set_error("riv import failed");
            debug_log("[rive] import with context failed result=%d",
                      static_cast<int>(result));
            return false;
        }
        g_pending_artboard = rive_file_artboard_default(g_pending_file);
        if (!g_pending_artboard) {
            set_error("artboard missing");
            debug_log("[rive] default artboard missing");
            return false;
        }
        if (!g_logged_riv_info) {
            const char* fingerprint = "????";
            char fingerprint_buf[5] = "????";
            if (len >= 4) {
                fingerprint_buf[0] = static_cast<char>(data[0]);
                fingerprint_buf[1] = static_cast<char>(data[1]);
                fingerprint_buf[2] = static_cast<char>(data[2]);
                fingerprint_buf[3] = static_cast<char>(data[3]);
                fingerprint_buf[4] = '\0';
                fingerprint = fingerprint_buf;
            }
            size_t artboard_count = rive_file_artboard_count(g_pending_file);
            char name_buf[64] = {0};
            size_t name_len = 0;
            if (artboard_count > 0) {
                name_len = rive_file_artboard_name(g_pending_file,
                                                   0,
                                                   name_buf,
                                                   sizeof(name_buf));
                if (name_len >= sizeof(name_buf)) {
                    name_len = sizeof(name_buf) - 1;
                }
                name_buf[name_len] = '\0';
            }
            debug_log("[rive] riv header=%s artboards=%zu first=%s",
                      fingerprint,
                      artboard_count,
                      name_buf[0] ? name_buf : "<none>");
            g_logged_riv_info = true;
        }
        debug_log("[rive] artboard imported with render context: %p",
                  g_pending_artboard);
    }

    g_artboard.store(g_pending_artboard, std::memory_order_relaxed);
    return g_pending_artboard != nullptr;
}

bool ensure_render_context(nvn::Queue* queue)
{
    if (!g_device) {
        set_error("device not ready");
        return false;
    }
    if (!queue) {
        set_error("queue not ready");
        return false;
    }
    if (!g_host.context) {
        RiveNVNContextDesc desc = {};
        desc.device = g_device;
        desc.queue = queue;
        nvn::WindowOriginMode origin = g_device->GetWindowOriginMode();
        const bool bottom_up = origin == nvn::WindowOriginMode::LOWER_LEFT;
        desc.clip_space_bottom_up = bottom_up ? 1 : 0;
        desc.framebuffer_bottom_up = bottom_up ? 1 : 0;
        ensure_default_allocator();
        if (g_allocator_set.load(std::memory_order_relaxed)) {
            desc.allocator = &g_allocator;
        }
        g_host.context = rive_nvn_render_context_new(&desc);
        if (!g_host.context) {
            set_error("rive_nvn_render_context_new failed");
            return false;
        }
        g_host.renderer = rive_renderer_new(g_host.context);
        if (!g_host.renderer) {
            set_error("rive_renderer_new failed");
            return false;
        }
    }
    return true;
}

bool is_overlay_command_buffer(const nvn::CommandBuffer* buffer)
{
    return g_overlay_cmd.initialized && buffer == &g_overlay_cmd.buffer;
}

static void overlay_command_memory_callback(nvn::CommandBuffer* cmd,
                                            nvn::CommandBufferMemoryEvent::Enum event,
                                            size_t min_size,
                                            void*)
{
    if (!cmd || !g_device) {
        return;
    }
    if (event == nvn::CommandBufferMemoryEvent::OUT_OF_COMMAND_MEMORY) {
        constexpr size_t kGrowCommandBytes = 8 * 1024 * 1024;
        size_t size = min_size > kGrowCommandBytes ? min_size : kGrowCommandBytes;
        size = align_up_size(size, 0x1000);

        OverlayCommandMemoryBlock* block =
            new (std::nothrow) OverlayCommandMemoryBlock();
        if (!block) {
            set_error("overlay cmd grow alloc failed");
            return;
        }
        block->memory = GlobalAllocator::AllocAligned(size, 0x1000);
        if (!block->memory) {
            delete block;
            set_error("overlay cmd grow mem failed");
            return;
        }

        nvn::MemoryPoolBuilder pool_builder;
        pool_builder.SetDefaults();
        pool_builder.SetDevice(g_device);
        pool_builder.SetFlags(nvn::MemoryPoolFlags::CPU_UNCACHED |
                      nvn::MemoryPoolFlags::GPU_CACHED)
            .SetStorage(block->memory, size);
        if (!block->pool.Initialize(&pool_builder)) {
            GlobalAllocator::Free(block->memory);
            delete block;
            set_error("overlay cmd grow pool failed");
            return;
        }
        block->size = size;
        cmd->AddCommandMemory(&block->pool, 0, size);
        g_overlay_cmd_blocks.push_back(block);
        debug_log("[rive] overlay cmd grow command=%zu", size);
        return;
    }

    if (event == nvn::CommandBufferMemoryEvent::OUT_OF_CONTROL_MEMORY) {
        constexpr size_t kGrowControlBytes = 128 * 1024;
        size_t size = min_size > kGrowControlBytes ? min_size : kGrowControlBytes;
        size = align_up_size(size, 8);
        void* memory = GlobalAllocator::AllocAligned(size, 8);
        if (!memory) {
            set_error("overlay cmd grow control failed");
            return;
        }
        cmd->AddControlMemory(memory, size);
        g_overlay_ctrl_blocks.push_back(memory);
        debug_log("[rive] overlay cmd grow control=%zu", size);
    }
}

bool ensure_overlay_command_buffer()
{
    if (g_overlay_cmd.initialized) {
        return true;
    }
    if (!g_device) {
        set_error("overlay cmd device missing");
        return false;
    }
    g_overlay_cmd_initializing.store(true, std::memory_order_relaxed);
    if (!g_overlay_cmd.buffer.Initialize(g_device)) {
        g_overlay_cmd_initializing.store(false, std::memory_order_relaxed);
        set_error("overlay cmd init failed");
        return false;
    }
    g_overlay_cmd_initializing.store(false, std::memory_order_relaxed);

    int cmd_align_value = 0;
    int ctl_align_value = 0;
    int min_cmd_value = 0;
    int min_ctl_value = 0;
    g_device->GetInteger(nvn::DeviceInfo::COMMAND_BUFFER_COMMAND_ALIGNMENT,
                         &cmd_align_value);
    g_device->GetInteger(nvn::DeviceInfo::COMMAND_BUFFER_CONTROL_ALIGNMENT,
                         &ctl_align_value);
    g_device->GetInteger(nvn::DeviceInfo::COMMAND_BUFFER_MIN_COMMAND_SIZE,
                         &min_cmd_value);
    g_device->GetInteger(nvn::DeviceInfo::COMMAND_BUFFER_MIN_CONTROL_SIZE,
                         &min_ctl_value);

    size_t cmd_align = cmd_align_value > 0
                           ? static_cast<size_t>(cmd_align_value)
                           : 4;
    size_t ctl_align = ctl_align_value > 0
                           ? static_cast<size_t>(ctl_align_value)
                           : 8;
    size_t cmd_size = min_cmd_value > 0
                          ? static_cast<size_t>(min_cmd_value)
                          : 0;
    size_t ctl_size = min_ctl_value > 0
                          ? static_cast<size_t>(min_ctl_value)
                          : 0;

    constexpr size_t kOverlayCommandBytes = 16 * 1024 * 1024;
    constexpr size_t kOverlayControlBytes = 256 * 1024;
    if (cmd_size < kOverlayCommandBytes) {
        cmd_size = kOverlayCommandBytes;
    }
    if (ctl_size < kOverlayControlBytes) {
        ctl_size = kOverlayControlBytes;
    }
    cmd_size = align_up_size(cmd_size, cmd_align);
    ctl_size = align_up_size(ctl_size, ctl_align);
    cmd_size = align_up_size(cmd_size, 0x1000);

    void* pool_memory = GlobalAllocator::AllocAligned(cmd_size, 0x1000);
    if (!pool_memory) {
        set_error("overlay cmd alloc failed");
        return false;
    }

    nvn::MemoryPoolBuilder pool_builder;
    pool_builder.SetDefaults()
        .SetDevice(g_device)
        .SetFlags(nvn::MemoryPoolFlags::CPU_UNCACHED |
                  nvn::MemoryPoolFlags::GPU_CACHED)
        .SetStorage(pool_memory, cmd_size);
    if (!g_overlay_cmd.pool.Initialize(&pool_builder)) {
        g_overlay_cmd.buffer.Finalize();
        GlobalAllocator::Free(pool_memory);
        set_error("overlay cmd pool init failed");
        return false;
    }
    g_overlay_cmd.buffer.AddCommandMemory(&g_overlay_cmd.pool, 0, cmd_size);

    void* control_memory = GlobalAllocator::AllocAligned(ctl_size, ctl_align);
    if (!control_memory) {
        g_overlay_cmd.buffer.Finalize();
        g_overlay_cmd.pool.Finalize();
        GlobalAllocator::Free(pool_memory);
        set_error("overlay cmd control alloc failed");
        return false;
    }
    g_overlay_cmd.buffer.AddControlMemory(control_memory, ctl_size);
    g_overlay_cmd.buffer.SetMemoryCallback(overlay_command_memory_callback);
    g_overlay_cmd.buffer.SetMemoryCallbackData(nullptr);

    g_overlay_cmd.pool_memory = pool_memory;
    g_overlay_cmd.pool_size = cmd_size;
    g_overlay_cmd.control_memory = control_memory;
    g_overlay_cmd.control_size = ctl_size;
    g_overlay_cmd.initialized = true;
    debug_log("[rive] overlay cmd init cmd=%zu control=%zu",
              cmd_size,
              ctl_size);
    return true;
}

bool ensure_command_buffer()
{
    if (g_device && (g_overlay_cmd.initialized || ensure_overlay_command_buffer())) {
        g_host.command_buffer = &g_overlay_cmd.buffer;
    } else if (!g_host.command_buffer && g_cmd_buffer) {
        g_host.command_buffer = g_cmd_buffer;
    }
    if (g_host.command_buffer) {
        return true;
    }
    set_error("command buffer missing");
    return false;
}

void reset_offscreen_target(OffscreenTarget* target)
{
    if (!target) {
        return;
    }
    if (target->depth_initialized) {
        target->depth_texture.Finalize();
        target->depth_pool.Finalize();
        target->depth_initialized = false;
    }
    if (target->depth_memory) {
        GlobalAllocator::Free(target->depth_memory);
        target->depth_memory = nullptr;
        target->depth_memory_size = 0;
    }
    if (target->initialized) {
        target->texture.Finalize();
        target->pool.Finalize();
        target->initialized = false;
    }
    if (target->memory) {
        GlobalAllocator::Free(target->memory);
        target->memory = nullptr;
        target->memory_size = 0;
    }
    target->width = 0;
    target->height = 0;
    target->depth = 1;
    target->levels = 1;
    target->samples = 0;
    target->stride = 0;
    target->format = nvn::Format::RGBA8;
    target->flags = nvn::TextureFlags(0);
    target->target = nvn::TextureTarget::TARGET_2D;
    target->depth_format = nvn::Format::DEPTH24_STENCIL8;
    target->depth_flags = nvn::TextureFlags(0);
    target->depth_target = nvn::TextureTarget::TARGET_2D;
}

void reset_offscreen()
{
    if (g_host.target_texture == &g_offscreen_msaa.texture ||
        g_host.target_texture == &g_offscreen_resolve.texture) {
        if (g_host.target) {
            rive_render_target_release(g_host.target);
            g_host.target = nullptr;
        }
        g_host.target_texture = nullptr;
        g_host.target_depth = nullptr;
        g_host.target_width = 0;
        g_host.target_height = 0;
        g_host.sample_count = 1;
    }
    reset_offscreen_target(&g_offscreen_msaa);
    reset_offscreen_target(&g_offscreen_resolve);
    g_blit.texture = nullptr;
    g_blit.handle = 0;
}

nvn::Format pick_offscreen_format(nvn::Format window_format, bool* out_overrode)
{
    bool overrode = false;
    nvn::Format format = window_format;
    switch (format) {
        case nvn::Format::RGBA8_SRGB:
            format = nvn::Format::RGBA8;
            overrode = true;
            break;
        case nvn::Format::BGRA8_SRGB:
            format = nvn::Format::BGRA8;
            overrode = true;
            break;
        case nvn::Format::RGBX8_SRGB:
            format = nvn::Format::RGBA8;
            overrode = true;
            break;
        case nvn::Format::BGRX8_SRGB:
            format = nvn::Format::BGRA8;
            overrode = true;
            break;
        case nvn::Format::RGBX8:
            format = nvn::Format::RGBA8;
            overrode = true;
            break;
        case nvn::Format::BGRX8:
            format = nvn::Format::BGRA8;
            overrode = true;
            break;
        default:
            break;
    }
    // NVN PLS storage images are rgba8, so keep the offscreen target RGBA8
    // to avoid undefined format conversions during resolve.
    if (format != nvn::Format::RGBA8) {
        format = nvn::Format::RGBA8;
        overrode = true;
    }
    if (out_overrode) {
        *out_overrode = overrode;
    }
    return format;
}

bool ensure_offscreen_target(OffscreenTarget* target,
                             nvn::Texture* window_texture,
                             uint32_t desired_samples,
                             bool needs_depth,
                             uint32_t desired_width,
                             uint32_t desired_height)
{
    if (!target) {
        set_error("offscreen target missing");
        return false;
    }
    if (!g_device || !window_texture) {
        set_error("offscreen missing window texture");
        return false;
    }
    int width = window_texture->GetWidth();
    int height = window_texture->GetHeight();
    int depth = window_texture->GetDepth();
    int levels = window_texture->GetLevels();
    ptrdiff_t stride = window_texture->GetStride();
    if (desired_width > 0) {
        width = static_cast<int>(desired_width);
        stride = 0;
    }
    if (desired_height > 0) {
        height = static_cast<int>(desired_height);
        stride = 0;
    }
    if (width <= 0 || height <= 0) {
        set_error("offscreen invalid size");
        return false;
    }

    bool format_overrode = false;
    const nvn::Format window_format = window_texture->GetFormat();
    const nvn::Format format = pick_offscreen_format(window_format,
                                                     &format_overrode);
    if (format_overrode) {
        static bool s_logged_offscreen_format = false;
        if (!s_logged_offscreen_format) {
            debug_log("[rive] offscreen format override window=%d offscreen=%d",
                      static_cast<int>(window_format),
                      static_cast<int>(format));
            s_logged_offscreen_format = true;
        }
    }
    int samples = static_cast<int>(desired_samples);
    if (samples <= 0) {
        samples = window_texture->GetSamples();
    }
    if (samples <= 0) {
        samples = 1;
    }
    nvn::TextureTarget target_type = window_texture->GetTarget();
    // Force offscreen targets to non-array types to avoid 2D_ARRAY view
    // mismatches when sampling in emulators.
    switch (target_type) {
        case nvn::TextureTarget::TARGET_2D_ARRAY:
        case nvn::TextureTarget::TARGET_CUBEMAP_ARRAY:
            target_type = nvn::TextureTarget::TARGET_2D;
            break;
        case nvn::TextureTarget::TARGET_2D_MULTISAMPLE_ARRAY:
            target_type = nvn::TextureTarget::TARGET_2D_MULTISAMPLE;
            break;
        default:
            break;
    }

    int flags_value = static_cast<int>(window_texture->GetFlags());
    flags_value &= ~static_cast<int>(nvn::TextureFlags::DISPLAY);
    if (flags_value == 0) {
        flags_value = static_cast<int>(nvn::TextureFlags::COMPRESSIBLE);
    }
    // Offscreen targets are sampled for compositing; force SAMPLED (and the copy flags we need) here.
    flags_value |= static_cast<int>(nvn::TextureFlags::SAMPLED) |
                   static_cast<int>(nvn::TextureFlags::COPY_SRC) |
                   static_cast<int>(nvn::TextureFlags::COPY_DEST);

    // NOTE: Do NOT set TextureFlags::IMAGE here. The atomic/PLS paths use dedicated image textures in
    // RenderContextNVNImpl, and marking the offscreen target as an image can cause emulator-side layout mismatches.
    if (samples > 1) {
        if (target_type == nvn::TextureTarget::TARGET_2D) {
            target_type = nvn::TextureTarget::TARGET_2D_MULTISAMPLE;
        } else if (target_type == nvn::TextureTarget::TARGET_2D_ARRAY) {
            target_type = nvn::TextureTarget::TARGET_2D_MULTISAMPLE;
        }
        levels = 1;
        if (stride > 0) {
            stride = 0;
            flags_value &=
                ~static_cast<int>(nvn::TextureFlags::LINEAR_RENDER_TARGET);
        }
        flags_value &= ~static_cast<int>(nvn::TextureFlags::LINEAR);
    }
    if (stride > 0) {
        flags_value |= static_cast<int>(nvn::TextureFlags::LINEAR_RENDER_TARGET);
    }
    const nvn::TextureFlags flags = nvn::TextureFlags(flags_value);
    const bool want_depth = needs_depth;
    const nvn::Format depth_format = nvn::Format::DEPTH24_STENCIL8;
    int depth_flags_value = static_cast<int>(nvn::TextureFlags::COMPRESSIBLE) |
                            static_cast<int>(nvn::TextureFlags::ADAPTIVE_ZCULL);
    nvn::TextureTarget depth_target = target_type;
    const nvn::TextureFlags depth_flags =
        nvn::TextureFlags(depth_flags_value);

    if (target->initialized &&
        target->width == static_cast<uint32_t>(width) &&
        target->height == static_cast<uint32_t>(height) &&
        target->depth == depth &&
        target->levels == levels &&
        target->samples == samples &&
        target->stride == stride &&
        target->format == format &&
        target->flags == flags &&
        target->target == target_type &&
        (!want_depth ||
         (target->depth_initialized &&
          target->depth_format == depth_format &&
          target->depth_flags == depth_flags &&
          target->depth_target == depth_target))) {
        return true;
    }

    reset_offscreen_target(target);

    nvn::TextureBuilder builder{};
    builder.SetDefaults();
    builder.SetDevice(g_device);
    builder.SetFlags(flags);
    builder.SetTarget(target_type);
    builder.SetSize2D(width, height);
    builder.SetDepth(depth);
    builder.SetLevels(levels);
    builder.SetFormat(format);
    builder.SetSwizzle(nvn::TextureSwizzle::R,
                nvn::TextureSwizzle::G,
                nvn::TextureSwizzle::B,
                nvn::TextureSwizzle::A);
    builder.SetSamples(samples > 1 ? samples : 0);
    if (stride > 0) {
        builder.SetStride(stride);
    }

    const size_t storage_size = builder.GetStorageSize();
    const size_t storage_alignment = builder.GetStorageAlignment();
    void* memory = GlobalAllocator::AllocAligned(storage_size, storage_alignment);
    if (!memory) {
        set_error("offscreen alloc failed");
        return false;
    }

    nvn::MemoryPoolFlags pool_flags =
        nvn::MemoryPoolFlags::CPU_UNCACHED | nvn::MemoryPoolFlags::GPU_CACHED;
    if ((flags_value & static_cast<int>(nvn::TextureFlags::COMPRESSIBLE)) != 0) {
        pool_flags |= nvn::MemoryPoolFlags::COMPRESSIBLE;
    }

    nvn::MemoryPoolBuilder pool_builder;
    pool_builder.SetDefaults();
    pool_builder.SetDevice(g_device);
    pool_builder.SetFlags(pool_flags);
    pool_builder.SetStorage(memory, storage_size);
    if (!target->pool.Initialize(&pool_builder)) {
        GlobalAllocator::Free(memory);
        set_error("offscreen pool init failed");
        return false;
    }

    builder.SetStorage(&target->pool, 0);
    if (!target->texture.Initialize(&builder)) {
        target->pool.Finalize();
        GlobalAllocator::Free(memory);
        set_error("offscreen texture init failed");
        return false;
    }

    init_texture_view(&target->view, target_type, format);
    target->memory = memory;
    target->memory_size = storage_size;
    target->width = static_cast<uint32_t>(width);
    target->height = static_cast<uint32_t>(height);
    target->depth = depth;
    target->levels = levels;
    target->samples = samples;
    target->stride = stride;
    target->format = format;
    target->flags = flags;
    target->target = target_type;
    target->initialized = true;

    if (want_depth) {
    nvn::TextureBuilder depth_builder{};
    depth_builder.SetDefaults();
    depth_builder.SetDevice(g_device);
    depth_builder.SetFlags(depth_flags);
    depth_builder.SetTarget(depth_target);
    depth_builder.SetSize2D(width, height);
    depth_builder.SetDepth(depth);
    depth_builder.SetLevels(levels);
    depth_builder.SetFormat(depth_format);
    depth_builder.SetSamples(samples > 1 ? samples : 0);
    depth_builder.SetDepthStencilMode(nvn::TextureDepthStencilMode::DEPTH);

        const size_t depth_storage_size = depth_builder.GetStorageSize();
        const size_t depth_storage_alignment =
            depth_builder.GetStorageAlignment();
        void* depth_memory =
            GlobalAllocator::AllocAligned(depth_storage_size,
                                          depth_storage_alignment);
        if (!depth_memory) {
            reset_offscreen_target(target);
            set_error("offscreen depth alloc failed");
            return false;
        }

        nvn::MemoryPoolFlags depth_pool_flags =
            nvn::MemoryPoolFlags::CPU_UNCACHED |
            nvn::MemoryPoolFlags::GPU_CACHED |
            nvn::MemoryPoolFlags::COMPRESSIBLE;

        nvn::MemoryPoolBuilder depth_pool_builder;
        depth_pool_builder.SetDefaults();
        depth_pool_builder.SetDevice(g_device);
        depth_pool_builder.SetFlags(depth_pool_flags);
        depth_pool_builder.SetStorage(depth_memory, depth_storage_size);
        if (!target->depth_pool.Initialize(&depth_pool_builder)) {
            GlobalAllocator::Free(depth_memory);
            reset_offscreen_target(target);
            set_error("offscreen depth pool init failed");
            return false;
        }

        depth_builder.SetStorage(&target->depth_pool, 0);
        if (!target->depth_texture.Initialize(&depth_builder)) {
            target->depth_pool.Finalize();
            GlobalAllocator::Free(depth_memory);
            reset_offscreen_target(target);
            set_error("offscreen depth texture init failed");
            return false;
        }

        init_texture_view(&target->depth_view, depth_target, depth_format);
        target->depth_memory = depth_memory;
        target->depth_memory_size = depth_storage_size;
        target->depth_format = depth_format;
        target->depth_flags = depth_flags;
        target->depth_target = depth_target;
        target->depth_initialized = true;
    }
    return true;
}

bool ensure_blit_state(nvn::Texture* texture)
{
    if (!g_device || !texture) {
        set_error("blit texture missing");
        return false;
    }

    if (!g_blit.allocator) {
        constexpr size_t kTextureCount = 0x100;
        constexpr size_t kSamplerCount = 0x100;
        constexpr size_t kDescriptorSize = 0x20;
        constexpr size_t kPoolAlign = 0x1000;
        const size_t raw_pool =
            (kTextureCount + kSamplerCount) * kDescriptorSize;
        const size_t pool_size =
            (raw_pool + (kPoolAlign - 1)) & ~(kPoolAlign - 1);

        g_blit.allocator = new (std::nothrow) GfxAllocator(g_device, pool_size);
        if (!g_blit.allocator) {
            set_error("blit pool alloc failed");
            return false;
        }

        const ptrdiff_t sampler_offset =
            g_blit.allocator->Allocate(kSamplerCount * kDescriptorSize);
        const ptrdiff_t texture_offset =
            g_blit.allocator->Allocate(kTextureCount * kDescriptorSize);

        if (!g_blit.sampler_pool.Initialize(&g_blit.allocator->GetPool(),
                                            sampler_offset,
                                            static_cast<int>(kSamplerCount))) {
            set_error("blit sampler pool init failed");
            return false;
        }
        if (!g_blit.texture_pool.Initialize(&g_blit.allocator->GetPool(),
                                            texture_offset,
                                            static_cast<int>(kTextureCount))) {
            set_error("blit texture pool init failed");
            return false;
        }

        nvn::SamplerBuilder sampler_builder{};
        sampler_builder.SetDefaults();
        sampler_builder.SetDevice(g_device);
        sampler_builder.SetMinMagFilter(nvn::MinFilter::LINEAR, nvn::MagFilter::LINEAR)
        sampler_builder.SetWrapMode(nvn::WrapMode::CLAMP_TO_EDGE,
                        nvn::WrapMode::CLAMP_TO_EDGE,
                        nvn::WrapMode::CLAMP_TO_EDGE);
        if (!g_blit.sampler.Initialize(&sampler_builder)) {
            set_error("blit sampler init failed");
            return false;
        }
        g_blit.sampler_pool.RegisterSampler(0, &g_blit.sampler);
        g_blit.initialized = true;
    }

    if (!g_blit.state_initialized) {
        g_blit.blend_state.SetDefaults();
        g_blit.blend_state.SetBlendTarget(0);
        g_blit.blend_state.SetBlendEquation(nvn::BlendEquation::ADD,
                                            nvn::BlendEquation::ADD);
        g_blit.blend_state.SetBlendFunc(nvn::BlendFunc::ONE,
                                        nvn::BlendFunc::ONE_MINUS_SRC_ALPHA,
                                        nvn::BlendFunc::ONE,
                                        nvn::BlendFunc::ONE_MINUS_SRC_ALPHA);

        g_blit.color_state.SetDefaults();
        g_blit.color_state.SetBlendEnable(0, true);

        g_blit.mask_state.SetDefaults();
        g_blit.mask_state.SetChannelMask(0, true, true, true, true);

        g_blit.depth_state.SetDefaults();
        g_blit.depth_state.SetDepthTestEnable(false);
        g_blit.depth_state.SetDepthWriteEnable(false);
        g_blit.depth_state.SetStencilTestEnable(false);

        g_blit.multisample_state.SetDefaults();
        g_blit.multisample_state.SetMultisampleEnable(false);

        g_blit.polygon_state.SetDefaults();
        g_blit.polygon_state.SetCullFace(nvn::Face::NONE);
        g_blit.polygon_state.SetFrontFace(nvn::FrontFace::CCW);

        g_blit.state_initialized = true;
    }

    if (g_blit.texture != texture) {
        init_texture_view(&g_blit.view, texture);
        g_blit.texture_pool.RegisterTexture(0, texture, &g_blit.view);
        g_blit.handle = g_device->GetTextureHandle(0, 0);
        g_blit.texture = texture;
    }

    return true;
}

void apply_draw_texture_state(nvn::CommandBuffer* cmd)
{
    if (!cmd) {
        return;
    }
    cmd->BindBlendState(&g_blit.blend_state);
    cmd->BindColorState(&g_blit.color_state);
    cmd->BindChannelMaskState(&g_blit.mask_state);
    cmd->BindDepthStencilState(&g_blit.depth_state);
    cmd->BindMultisampleState(&g_blit.multisample_state);
    cmd->BindPolygonState(&g_blit.polygon_state);
}

bool ensure_render_target(nvn::Texture* color,
                          nvn::Texture* depth,
                          uint32_t desired_samples)
{
    if (!color) {
        set_error("render target texture missing");
        return false;
    }
    uint32_t width = static_cast<uint32_t>(color->GetWidth());
    uint32_t height = static_cast<uint32_t>(color->GetHeight());
    uint32_t raw_samples = static_cast<uint32_t>(color->GetSamples());
    uint32_t samples = desired_samples ? desired_samples : raw_samples;
    if (samples == 0) {
        samples = 1;
    }
    if (g_host.target && g_host.target_texture == color &&
        g_host.target_depth == depth &&
        g_host.target_width == width && g_host.target_height == height &&
        g_host.sample_count == samples) {
        return true;
    }
    if (g_host.target) {
        rive_render_target_release(g_host.target);
        g_host.target = nullptr;
    }
    g_host.target_depth = nullptr;
    g_host.target = rive_nvn_render_target_new(
        width, height, color, depth, samples);
    g_host.target_texture = color;
    g_host.target_depth = depth;
    g_host.target_width = width;
    g_host.target_height = height;
    g_host.sample_count = samples;
    if (!g_host.target) {
        set_error("rive_nvn_render_target_new failed");
        return false;
    }
    return true;
}

bool render_rive(nvn::Queue* queue, nvn::CommandHandle* out_handle)
{
    if (!out_handle) {
        set_error("missing command handle");
        return false;
    }
    {
        static bool s_logged_render_enter = false;
        if (!s_logged_render_enter) {
            debug_log("[rive] render_rive enter");
            s_logged_render_enter = true;
        }
    }

    if (!ensure_render_context(queue)) {
        return false;
    }
    if (!ensure_artboard_loaded()) {
        return false;
    }

    RiveArtboard* artboard = g_artboard.load(std::memory_order_relaxed);
    if (!artboard) {
        set_error("artboard not set");
        return false;
    }

    if (g_display_texture_index < 0 ||
        g_display_texture_index >= g_window_texture_count) {
        set_error("window textures not ready");
        return false;
    }

    if (!ensure_command_buffer()) {
        return false;
    }

    nvn::Texture* color = g_window_textures[g_display_texture_index];
    if (!color) {
        set_error("window texture missing");
        return false;
    }
    if (g_log_window_info.load(std::memory_order_relaxed) &&
        !g_logged_window_info) {
        debug_log(
            "[rive] window tex format=%d target=%d flags=0x%08x stride=%lld samples=%d levels=%d depth=%d",
            static_cast<int>(color->GetFormat()),
            static_cast<int>(color->GetTarget()),
            static_cast<unsigned int>(color->GetFlags()),
            static_cast<long long>(color->GetStride()),
            color->GetSamples(),
            color->GetLevels(),
            color->GetDepth());
        g_logged_window_info = true;
    }

    int force_msaa_samples =
        g_force_msaa_samples.load(std::memory_order_relaxed);
    if (force_msaa_samples <= 1) {
        force_msaa_samples = 0;
    }
    const bool force_offscreen = force_msaa_samples > 1;

    bool use_offscreen =
        g_render_mode.load(std::memory_order_relaxed) ==
        RIVE_RUNTIME_RENDER_OFFSCREEN_BLIT;
    if (force_offscreen) {
        use_offscreen = true;
    }
    if (use_offscreen && g_supports_draw_texture <= 0 &&
        !RIVE_NVN_FORCE_COPY_TEXTURE) {
        if (force_offscreen) {
            set_error("msaa requires DrawTexture or CopyTexture");
            return false;
        }
        use_offscreen = false;
        debug_log("[rive] offscreen blit disabled (DrawTexture unsupported)");
    }
    nvn::Texture* render_color = color;
    nvn::Texture* render_depth = nullptr;
    OffscreenTarget* resolve_target = nullptr;
    OffscreenTarget* msaa_target = nullptr;
    uint32_t offscreen_width = 0;
    uint32_t offscreen_height = 0;
    if (use_offscreen) {
        const uint32_t window_width =
            static_cast<uint32_t>(color->GetWidth());
        const uint32_t window_height =
            static_cast<uint32_t>(color->GetHeight());
        const float art_w = rive_artboard_width(artboard);
        const float art_h = rive_artboard_height(artboard);
        constexpr float kMaxPlsDim = 512.0f;
        float scale = 1.0f;
        if (art_w > 0.0f && art_h > 0.0f) {
            const float max_dim = art_w > art_h ? art_w : art_h;
            if (max_dim > kMaxPlsDim) {
                scale = kMaxPlsDim / max_dim;
            }
        }
        uint32_t desired_w =
            art_w > 0.0f ? static_cast<uint32_t>(std::ceil(art_w * scale)) : 0;
        uint32_t desired_h =
            art_h > 0.0f ? static_cast<uint32_t>(std::ceil(art_h * scale)) : 0;
        if (desired_w == 0 || desired_w > window_width) {
            desired_w = window_width;
        }
        if (desired_h == 0 || desired_h > window_height) {
            desired_h = window_height;
        }
#if RIVE_NVN_FORCE_COPY_TEXTURE
        desired_w = window_width;
        desired_h = window_height;
#endif
        offscreen_width = desired_w;
        offscreen_height = desired_h;
        const uint32_t window_samples =
            static_cast<uint32_t>(color->GetSamples());
        const uint32_t desired_samples =
            force_msaa_samples > 1
                ? static_cast<uint32_t>(force_msaa_samples)
                : (window_samples > 1 ? window_samples : 1);
        resolve_target = &g_offscreen_resolve;
        if (desired_samples > 1) {
            msaa_target = &g_offscreen_msaa;
            if (!ensure_offscreen_target(msaa_target,
                                         color,
                                         desired_samples,
                                         true,
                                         offscreen_width,
                                         offscreen_height)) {
                return false;
            }
        }
        if (!ensure_offscreen_target(resolve_target,
                                     color,
                                     1,
                                     msaa_target == nullptr,
                                     offscreen_width,
                                     offscreen_height)) {
            return false;
        }
        render_color = msaa_target ? &msaa_target->texture
                                   : &resolve_target->texture;
        if (msaa_target && msaa_target->depth_initialized) {
            render_depth = &msaa_target->depth_texture;
        } else if (resolve_target && resolve_target->depth_initialized) {
            render_depth = &resolve_target->depth_texture;
        }
    } else {
        resolve_target = &g_offscreen_resolve;
        if (!ensure_offscreen_target(resolve_target,
                                     color,
                                     1,
                                     true,
                                     0,
                                     0)) {
            return false;
        }
        if (resolve_target->depth_initialized) {
            render_depth = &resolve_target->depth_texture;
        }
    }
    const uint32_t desired_render_samples =
        use_offscreen
            ? (msaa_target ? static_cast<uint32_t>(msaa_target->samples)
                           : static_cast<uint32_t>(resolve_target->samples))
            : 0;
    if (!ensure_render_target(render_color,
                              render_depth,
                              desired_render_samples)) {
        return false;
    }

    debug_log("[rive] render_rive advance artboard");
    rive_artboard_advance(artboard, 1.0f / 60.0f);
    debug_log("[rive] render_rive advance ok");

    RiveFrameDescriptor frame = {};
    frame.render_target_width = g_host.target_width;
    frame.render_target_height = g_host.target_height;
    const bool force_clear =
        !use_offscreen &&
        g_force_debug_clear.exchange(false, std::memory_order_relaxed);
    frame.load_action =
        (use_offscreen || force_clear)
            ? RIVE_LOAD_CLEAR
            : RIVE_LOAD_PRESERVE_RENDER_TARGET;
    frame.clear_color = force_clear ? 0xFFFF00FFu : 0;
    frame.msaa_sample_count = g_host.sample_count > 1 ? g_host.sample_count : 0;
    frame.disable_raster_ordering = RIVE_NVN_FORCE_RASTER_ORDERING ? 0 : 1;
#if RIVE_NVN_FORCE_RASTER_ORDERING
    static bool s_logged_raster_ordering = false;
    if (!s_logged_raster_ordering) {
        debug_log("[rive] raster ordering forced on");
        s_logged_raster_ordering = true;
    }
#endif
    frame.wireframe = 0;
    frame.fills_disabled = 0;
    frame.strokes_disabled = 0;
    frame.clockwise_fill_override = 0;

    nvn::CommandBuffer* cmd_buffer = g_host.command_buffer;
    if (!cmd_buffer) {
        set_error("command buffer missing");
        return false;
    }
    cmd_buffer->BeginRecording();

    if (!use_offscreen && render_depth) {
        nvn::CommandBuffer* cmd = g_host.command_buffer;
        nvn::TextureView color_view;
        init_texture_view(&color_view, render_color);
        nvn::TextureView depth_view;
        init_texture_view(&depth_view, render_depth);
        nvn::Texture* colors[] = {render_color};
        nvn::TextureView* color_views[] = {&color_view};
        cmd->SetRenderEnable(true);
        cmd->SetRasterizerDiscard(false);
        cmd->SetRenderTargets(1,
                              colors,
                              color_views,
                              render_depth,
                              &depth_view);
        cmd->ClearDepthStencil(1.0f, true, 0, 0xFF);
    }

    debug_log("[rive] render_rive begin frame");
    rive_render_context_begin_frame(g_host.context, &frame);
    debug_log("[rive] render_rive begin frame ok");

    RiveAABB content = {};
    if (!rive_artboard_bounds(artboard, &content)) {
        content.min_x = 0.0f;
        content.min_y = 0.0f;
        content.max_x = rive_artboard_width(artboard);
        content.max_y = rive_artboard_height(artboard);
    }
    RiveAABB frame_rect = {
        0.0f,
        0.0f,
        static_cast<float>(g_host.target_width),
        static_cast<float>(g_host.target_height),
    };
    RiveAlignment alignment = {0.0f, 0.0f};

    debug_log("[rive] render_rive draw start");
    rive_renderer_save(g_host.renderer);
    rive_renderer_align(g_host.renderer,
                        RIVE_FIT_CONTAIN,
                        alignment,
                        frame_rect,
                        content,
                        1.0f);
    debug_log("[rive] render_rive draw align ok");
    rive_renderer_draw_artboard(g_host.renderer, artboard);
    debug_log("[rive] render_rive draw artboard ok");
    rive_renderer_restore(g_host.renderer);
    debug_log("[rive] render_rive draw restore ok");

    g_host.frame++;
    RiveFlushResources flush = {};
    flush.render_target = g_host.target;
    flush.external_command_buffer = g_host.command_buffer;
    flush.current_frame_number = g_host.frame;
    flush.safe_frame_number = g_host.frame > 2 ? g_host.frame - 2 : 0;
    debug_log("[rive] render_rive flush");
    rive_render_context_flush(g_host.context, &flush);
    debug_log("[rive] render_rive flush ok");

    if (use_offscreen) {
        nvn::CommandBuffer* cmd = g_host.command_buffer;
        if (g_force_debug_clear_offscreen.exchange(false,
                                                    std::memory_order_relaxed)) {
            float clear_color[4] = {0.0f, 1.0f, 0.0f, 1.0f};
            nvn::TextureView clear_view;
            init_texture_view(&clear_view, render_color);
            const int clear_width = render_color->GetWidth();
            const int clear_height = render_color->GetHeight();
            nvn::CopyRegion region = {};
            region.xoffset = 0;
            region.yoffset = 0;
            region.zoffset = 0;
            region.width = clear_width;
            region.height = clear_height;
            region.depth = 1;
            cmd->ClearTexture(render_color,
                              &clear_view,
                              &region,
                              clear_color,
                              nvn::ClearColorMask(nvn::ClearColorMask::RGBA));
            debug_log("[rive] debug clear offscreen");
        }
        cmd->Barrier(nvn::BarrierBits::ORDER_FRAGMENTS |
                     nvn::BarrierBits::INVALIDATE_TEXTURE);
        if (msaa_target && resolve_target) {
            cmd->Downsample(&msaa_target->texture, &resolve_target->texture);
        }

        nvn::Texture* composite_src =
            resolve_target ? &resolve_target->texture : render_color;
#if RIVE_NVN_DEBUG_CLEAR_OFFSCREEN
        static bool s_logged_offscreen_clear = false;
        if (!s_logged_offscreen_clear) {
            debug_log("[rive] debug clear offscreen enabled");
            s_logged_offscreen_clear = true;
        }
        const float debug_green[4] = {0.0f, 1.0f, 0.0f, 1.0f};
        clear_texture_color(cmd, composite_src, debug_green);
#endif
        const bool use_draw_texture =
            g_supports_draw_texture > 0 && !RIVE_NVN_FORCE_COPY_TEXTURE;
        if (use_draw_texture) {
            nvn::TextureView color_view;
            init_texture_view(&color_view, color);
            nvn::TextureView* color_views[] = {&color_view};
            cmd->SetRenderEnable(true);
            cmd->SetRasterizerDiscard(false);
            cmd->SetRenderTargets(1, &color, color_views, nullptr, nullptr);
            if (!ensure_blit_state(composite_src)) {
                return false;
            }
            cmd->SetTexturePool(&g_blit.texture_pool);
            cmd->SetSamplerPool(&g_blit.sampler_pool);
            apply_draw_texture_state(cmd);

            const int dst_width = color->GetWidth();
            const int dst_height = color->GetHeight();
            cmd->SetViewport(0, 0, dst_width, dst_height);
            cmd->SetScissor(0, 0, dst_width, dst_height);

            const float src_width =
                static_cast<float>(resolve_target ? resolve_target->width
                                                  : g_host.target_width);
            const float src_height =
                static_cast<float>(resolve_target ? resolve_target->height
                                                  : g_host.target_height);
            const nvn::DrawTextureRegion src_region = {
                0.0f,
                0.0f,
                src_width,
                src_height,
            };
            float dst_draw_width = src_width;
            float dst_draw_height = src_height;
            if (dst_draw_width <= 0.0f || dst_draw_height <= 0.0f) {
                dst_draw_width = static_cast<float>(dst_width);
                dst_draw_height = static_cast<float>(dst_height);
            }
            if (dst_draw_width > static_cast<float>(dst_width) ||
                dst_draw_height > static_cast<float>(dst_height)) {
                const float scale_w =
                    static_cast<float>(dst_width) / dst_draw_width;
                const float scale_h =
                    static_cast<float>(dst_height) / dst_draw_height;
                const float scale = scale_w < scale_h ? scale_w : scale_h;
                dst_draw_width *= scale;
                dst_draw_height *= scale;
            }
            const float dst_x =
                (static_cast<float>(dst_width) - dst_draw_width) * 0.5f;
            const float dst_y =
                (static_cast<float>(dst_height) - dst_draw_height) * 0.5f;
            const nvn::DrawTextureRegion dst_region = {
                dst_x,
                dst_y,
                dst_draw_width,
                dst_draw_height,
            };
            cmd->DrawTexture(g_blit.handle, &dst_region, &src_region);
        } else {
#if RIVE_NVN_FORCE_COPY_TEXTURE
            static bool s_logged_force_copy = false;
            if (!s_logged_force_copy) {
                debug_log("[rive] offscreen blit forced to CopyTextureToTexture");
                s_logged_force_copy = true;
            }
#endif
            const int dst_width = color->GetWidth();
            const int dst_height = color->GetHeight();
            const int src_width = resolve_target
                                      ? static_cast<int>(resolve_target->width)
                                      : static_cast<int>(g_host.target_width);
            const int src_height = resolve_target
                                       ? static_cast<int>(resolve_target->height)
                                       : static_cast<int>(g_host.target_height);
            int copy_width = src_width < dst_width ? src_width : dst_width;
            int copy_height = src_height < dst_height ? src_height : dst_height;
#if RIVE_NVN_FORCE_COPY_TEXTURE
            static bool s_logged_copy_sizes = false;
            if (!s_logged_copy_sizes) {
                debug_log(
                    "[rive] copy blit sizes src=%dx%d dst=%dx%d copy=%dx%d",
                    src_width,
                    src_height,
                    dst_width,
                    dst_height,
                    copy_width,
                    copy_height);
                s_logged_copy_sizes = true;
            }
#endif
            const int dst_x = (dst_width - copy_width) / 2;
            const int dst_y = (dst_height - copy_height) / 2;
            nvn::CopyRegion src = {
                0,
                0,
                0,
                copy_width,
                copy_height,
                1,
            };
            nvn::CopyRegion dst = {
                dst_x,
                dst_y,
                0,
                copy_width,
                copy_height,
                1,
            };
            cmd->CopyTextureToTexture(composite_src,
                                      nullptr,
                                      &src,
                                      color,
                                      nullptr,
                                      &dst,
                                      nvn::CopyFlags::NONE);
        }
    }

    if (g_force_debug_clear_all.exchange(false, std::memory_order_relaxed)) {
        nvn::CommandBuffer* cmd = g_host.command_buffer;
        float clear_color[4] = {1.0f, 0.0f, 1.0f, 1.0f};
        nvn::TextureView color_view;
        nvn::TextureView* color_views[] = {&color_view};
        cmd->SetRenderEnable(true);
        cmd->SetRasterizerDiscard(false);
        for (int i = 0; i < g_window_texture_count; ++i) {
            nvn::Texture* tex = g_window_textures[i];
            if (!tex) {
                continue;
            }
            init_texture_view(&color_view, tex);
            const int width = tex->GetWidth();
            const int height = tex->GetHeight();
            nvn::CopyRegion region = {};
            region.xoffset = 0;
            region.yoffset = 0;
            region.zoffset = 0;
            region.width = width;
            region.height = height;
            region.depth = 1;
            cmd->ClearTexture(tex,
                              &color_view,
                              &region,
                              clear_color,
                              nvn::ClearColorMask(nvn::ClearColorMask::RGBA));
            nvn::Texture* colors[] = {tex};
            cmd->SetRenderTargets(1, colors, color_views, nullptr, nullptr);
            cmd->SetViewport(0, 0, width, height);
            cmd->SetScissor(0, 0, width, height);
            cmd->ClearColor(
                0,
                clear_color,
                nvn::ClearColorMask(nvn::ClearColorMask::RGBA));
        }
        debug_log("[rive] debug clear all window textures");
    }

    *out_handle = cmd_buffer->EndRecording();
    set_error("ok");
    return true;
}

void log_render_attempt_once(bool recorded)
{
    if (g_logged_render_attempt) {
        return;
    }
    RiveArtboard* artboard = g_artboard.load(std::memory_order_relaxed);
    float art_w = artboard ? rive_artboard_width(artboard) : 0.0f;
    float art_h = artboard ? rive_artboard_height(artboard) : 0.0f;
    RiveAABB bounds = {};
    int has_bounds = artboard ? rive_artboard_bounds(artboard, &bounds) : 0;
    debug_log(
        "[rive] render attempt recorded=%d last_error=%s artboard=%p artboard_w=%.2f artboard_h=%.2f bounds=%d [%.2f %.2f %.2f %.2f] target=%p target_w=%u target_h=%u textures=%d index=%d",
        recorded ? 1 : 0,
        g_last_error ? g_last_error : "none",
        artboard,
        art_w,
        art_h,
        has_bounds,
        bounds.min_x,
        bounds.min_y,
        bounds.max_x,
        bounds.max_y,
        g_host.target,
        g_host.target_width,
        g_host.target_height,
        g_window_texture_count,
        g_display_texture_index);
    g_logged_render_attempt = true;
}

[[maybe_unused]] void nvnQueueSubmitCommands_hook(nvn::Queue* queue,
                                 int count,
                                 const nvn::CommandHandle* handles)
{
    g_last_queue = queue;
    update_toggle_input();
    if (!g_queue_submit_orig) {
        set_error("queue submit missing");
        return;
    }

    const bool queue_ok = !g_queue || queue == g_queue;
    const bool enabled = g_enabled.load(std::memory_order_relaxed);
    if (!enabled) {
        g_logged_render_attempt = false;
        g_rendered_this_frame.store(false, std::memory_order_relaxed);
    }
    nvn::CommandHandle handle = {};
    bool recorded = false;
    if (enabled && queue_ok &&
        !g_render_in_present.load(std::memory_order_relaxed)) {
        bool should_render =
            !g_rendered_this_frame.exchange(true, std::memory_order_relaxed);
        if (should_render) {
            recorded = render_rive(queue, &handle);
            log_render_attempt_once(recorded);
            if (!recorded) {
                g_rendered_this_frame.store(false, std::memory_order_relaxed);
            }
        }
    }

    g_queue_submit_orig(queue, count, handles);

    if (recorded) {
        g_queue_submit_orig(queue, 1, &handle);
    } else if (!enabled) {
        set_error("disabled");
    }
}

void nvnQueuePresentTexture_hook(nvn::Queue* queue,
                                 nvn::Window* window,
                                 int texture_index)
{
    g_last_queue = queue;
    update_toggle_input();
    if (!g_queue_present_orig) {
        set_error("queue present missing");
        return;
    }
    const bool window_ok = !g_window || window == g_window;
    if (texture_index >= 0 && window_ok) {
        g_display_texture_index = texture_index;
    } else if (!window_ok && !g_logged_window_mismatch) {
        debug_log("[rive] present window mismatch window=%p expected=%p",
                  window,
                  g_window);
        g_logged_window_mismatch = true;
    }
    if (window_ok) {
        g_rendered_this_frame.store(false, std::memory_order_relaxed);
    }
    const bool render_in_present =
        g_render_in_present.load(std::memory_order_relaxed);
    if (!render_in_present) {
        g_queue_present_orig(queue, window, texture_index);
        return;
    }
    const bool enabled = g_enabled.load(std::memory_order_relaxed);
    bool render_guard = false;
    if (enabled && window_ok && g_host.command_buffer) {
        if (g_rendering.exchange(true)) {
            g_queue_present_orig(queue, window, texture_index);
            return;
        }
        render_guard = true;
        nvn::CommandBuffer* cmd = g_host.command_buffer;
        const bool using_overlay = is_overlay_command_buffer(cmd);
        const nvn::TexturePool* saved_tex_pool =
            using_overlay ? nullptr : g_cmd_texture_pool;
        const nvn::SamplerPool* saved_samp_pool =
            using_overlay ? nullptr : g_cmd_sampler_pool;
        bool resume_recording = false;
        if (!using_overlay && cmd &&
            g_game_cmd_recording.load(std::memory_order_relaxed)) {
            cmd->EndRecording();
            resume_recording = true;
        }
#if RIVE_NVN_ENABLE_TOGGLE_DEBUG_CLEAR
        if (g_toggle_clear_pending.load(std::memory_order_relaxed)) {
            nvn::Texture* clear_tex = nullptr;
            if (g_window_textures &&
                texture_index >= 0 &&
                texture_index < g_window_texture_count) {
                clear_tex = g_window_textures[texture_index];
            }
            if (clear_tex) {
                cmd->BeginRecording();
                clear_window_texture(cmd, clear_tex);
                nvn::CommandHandle clear_handle = cmd->EndRecording();
                queue->SubmitCommands(1, &clear_handle);
                g_toggle_clear_pending.store(false,
                                             std::memory_order_relaxed);
            }
        }
#endif
        nvn::CommandHandle handle = {};
        bool recorded = render_rive(queue, &handle);
        log_render_attempt_once(recorded);
        if (recorded) {
            queue->SubmitCommands(1, &handle);
        }
        if (!using_overlay && (saved_tex_pool || saved_samp_pool)) {
            cmd->BeginRecording();
            if (saved_tex_pool) {
                cmd->SetTexturePool(saved_tex_pool);
            }
            if (saved_samp_pool) {
                cmd->SetSamplerPool(saved_samp_pool);
            }
            nvn::CommandHandle restore_handle = cmd->EndRecording();
            queue->SubmitCommands(1, &restore_handle);
        }
        if (!using_overlay && resume_recording) {
            cmd->BeginRecording();
        }
    } else if (!enabled) {
        set_error("disabled");
    } else if (!window_ok) {
        set_error("window mismatch");
    } else if (!g_host.command_buffer) {
        set_error("command buffer missing");
    }
    if (render_guard) {
        g_rendering.store(false);
    }
    g_queue_present_orig(queue, window, texture_index);
}

void nvnWindowBuilderSetTextures_hook(nvn::WindowBuilder* builder,
                                      int count,
                                      nvn::Texture* const* textures)
{
    if (textures && count > 0) {
        nvn::Texture** next =
            new (std::nothrow) nvn::Texture*[count];
        if (next) {
            std::memcpy(next,
                        textures,
                        sizeof(nvn::Texture*) * count);
            if (builder == g_window_builder && g_window) {
                delete[] g_window_textures;
                g_window_textures = next;
                g_window_texture_count = count;
            } else {
                delete[] g_pending_window_textures;
                g_pending_window_textures = next;
                g_pending_window_texture_count = count;
                g_pending_window_builder = builder;
            }
        } else {
            set_error("window texture alloc failed");
            delete[] g_pending_window_textures;
            g_pending_window_textures = nullptr;
            g_pending_window_texture_count = 0;
            g_pending_window_builder = nullptr;
        }
    }
    g_window_set_textures_orig(builder, count, textures);
}

bool nvnWindowInitialize_hook(nvn::Window* window,
                              const nvn::WindowBuilder* builder)
{
    if (!g_window_init_orig) {
        return false;
    }
    bool ok = g_window_init_orig(window, builder);
    if (ok && builder) {
        g_window = window;
        g_window_builder = const_cast<nvn::WindowBuilder*>(builder);
        if (builder == g_pending_window_builder &&
            g_pending_window_textures) {
            delete[] g_window_textures;
            g_window_textures = g_pending_window_textures;
            g_window_texture_count = g_pending_window_texture_count;
            g_pending_window_textures = nullptr;
            g_pending_window_texture_count = 0;
            g_pending_window_builder = nullptr;
            debug_log("[rive] window initialized window=%p textures=%d",
                      window,
                      g_window_texture_count);
        }
    }
    return ok;
}

nvn::WindowAcquireTextureResult::Enum nvnWindowAcquireTexture_hook(
    nvn::Window* window,
    nvn::Sync* texture_available,
    int* index)
{
    auto ret =
        g_window_acquire_orig(window, texture_available, index);
    if (index && (!g_window || window == g_window)) {
        g_display_texture_index = *index;
    } else if (index && !g_logged_window_mismatch) {
        debug_log("[rive] acquire window mismatch window=%p expected=%p",
                  window,
                  g_window);
        g_logged_window_mismatch = true;
    }
    return ret;
}

void clear_window_texture(nvn::CommandBuffer* cmd, nvn::Texture* tex)
{
    const float clear_color[4] = {1.0f, 0.0f, 1.0f, 1.0f};
    clear_texture_color(cmd, tex, clear_color);
}

void clear_texture_color(nvn::CommandBuffer* cmd,
                         nvn::Texture* tex,
                         const float* color)
{
    if (!cmd || !tex || !color) {
        return;
    }
    const int width = tex->GetWidth();
    const int height = tex->GetHeight();
    if (width <= 0 || height <= 0) {
        return;
    }

    nvn::TextureView view;
    init_texture_view(&view, tex);

    nvn::CopyRegion region = {};
    region.xoffset = 0;
    region.yoffset = 0;
    region.zoffset = 0;
    region.width = width;
    region.height = height;
    region.depth = 1;

    cmd->SetRenderEnable(true);
    cmd->SetRasterizerDiscard(false);
    cmd->ClearTexture(tex,
                      &view,
                      &region,
                      color,
                      nvn::ClearColorMask(nvn::ClearColorMask::RGBA));

    const nvn::Texture* colors[] = {tex};
    const nvn::TextureView* views[] = {&view};
    cmd->SetRenderTargets(1, colors, views, nullptr, nullptr);
    cmd->SetViewport(0, 0, width, height);
    cmd->SetScissor(0, 0, width, height);
    cmd->ClearColor(0,
                    color,
                    nvn::ClearColorMask(nvn::ClearColorMask::RGBA));
}

bool nvnQueueInitialize_hook(nvn::Queue* queue,
                             const nvn::QueueBuilder* builder)
{
    if (!g_queue_init_orig) {
        return false;
    }
    bool ok = g_queue_init_orig(queue, builder);
    if (ok) {
        g_queue = queue;
        g_last_queue = queue;
        nvn::Device* device = g_device;
        if (!device) {
            device = resolve_device_from_queue_builder(builder);
        }
        if (device) {
            ensure_device_initialized(device);
        }
    }
    return ok;
}

void nvnCommandBufferBeginRecording_hook(nvn::CommandBuffer* buffer)
{
    if (g_command_buffer_begin_orig) {
        g_command_buffer_begin_orig(buffer);
    }
    if (!buffer) {
        return;
    }
    if (buffer == g_cmd_buffer) {
        g_game_cmd_recording.store(true, std::memory_order_relaxed);
    }
    if (is_overlay_command_buffer(buffer)) {
        g_overlay_cmd_recording.store(true, std::memory_order_relaxed);
    }
}

nvn::CommandHandle nvnCommandBufferEndRecording_hook(nvn::CommandBuffer* buffer)
{
    nvn::CommandHandle handle = {};
    if (g_command_buffer_end_orig) {
        handle = g_command_buffer_end_orig(buffer);
    }
    if (!buffer) {
        return handle;
    }
    if (buffer == g_cmd_buffer) {
        g_game_cmd_recording.store(false, std::memory_order_relaxed);
    }
    if (is_overlay_command_buffer(buffer)) {
        g_overlay_cmd_recording.store(false, std::memory_order_relaxed);
    }
    return handle;
}

bool nvnCommandBufferInitialize_hook(nvn::CommandBuffer* buffer,
                                     nvn::Device* device)
{
    if (!g_command_buffer_init_orig) {
        return false;
    }
    bool ok = g_command_buffer_init_orig(buffer, device);
    if (!ok) {
        return ok;
    }
    if (g_overlay_cmd_initializing.load(std::memory_order_relaxed)) {
        return ok;
    }
    if (device && !g_device) {
        g_device = device;
    }
    if (device && !g_device_get_proc_orig) {
        g_device_get_proc_orig =
            reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(
                device->GetProcAddress(kGetAddress));
    }
    ensure_device_initialized(device);
    if (g_cmd_buffer_count == RIVE_NVN_COMMAND_BUFFER_ID) {
        g_cmd_buffer = buffer;
        g_game_cmd_recording.store(false, std::memory_order_relaxed);
        if (!g_host.command_buffer && !g_overlay_cmd.initialized) {
            g_host.command_buffer = buffer;
        }
    }
    ++g_cmd_buffer_count;
    return ok;
}

void nvnCommandBufferSetTexturePool_hook(nvn::CommandBuffer* cmd_buf,
                                         const nvn::TexturePool* pool)
{
    if (cmd_buf && !is_overlay_command_buffer(cmd_buf)) {
        g_cmd_buffer = cmd_buf;
        g_cmd_texture_pool = pool;
        if (!g_overlay_cmd.initialized) {
            g_host.command_buffer = cmd_buf;
        }
    }
    if (g_command_set_texture_pool_orig) {
        g_command_set_texture_pool_orig(cmd_buf, pool);
    }
}

void nvnCommandBufferSetSamplerPool_hook(nvn::CommandBuffer* cmd_buf,
                                         const nvn::SamplerPool* pool)
{
    if (cmd_buf && !is_overlay_command_buffer(cmd_buf)) {
        g_cmd_buffer = cmd_buf;
        g_cmd_sampler_pool = pool;
        if (!g_overlay_cmd.initialized) {
            g_host.command_buffer = cmd_buf;
        }
    }
    if (g_command_set_sampler_pool_orig) {
        g_command_set_sampler_pool_orig(cmd_buf, pool);
    }
}

void nvnWindowSetCrop_hook(nvn::Window* window,
                           int x,
                           int y,
                           int w,
                           int h)
{
    if (g_window_set_crop_orig) {
        g_window_set_crop_orig(window, x, y, w, h);
    }
}

[[maybe_unused]] void install_window_hooks()
{
    if (!g_device ||
        (g_window_set_textures_orig && g_window_acquire_orig && g_window_init_orig)) {
        return;
    }
    if (!g_window_set_textures_orig) {
        void* addr =
            reinterpret_cast<void*>(g_device->GetProcAddress(kWindowSetTextures));
        if (!g_window_set_textures_orig &&
            should_hook_proc(addr,
                             reinterpret_cast<void*>(nvnWindowBuilderSetTextures_hook))) {
            A64HookFunction(addr,
                            reinterpret_cast<void*>(nvnWindowBuilderSetTextures_hook),
                            reinterpret_cast<void**>(&g_window_set_textures_orig));
        }
    }
    if (!g_window_init_orig) {
        void* addr =
            reinterpret_cast<void*>(g_device->GetProcAddress(kWindowInitialize));
        if (!g_window_init_orig &&
            should_hook_proc(addr,
                             reinterpret_cast<void*>(nvnWindowInitialize_hook))) {
            A64HookFunction(addr,
                            reinterpret_cast<void*>(nvnWindowInitialize_hook),
                            reinterpret_cast<void**>(&g_window_init_orig));
        }
    }
#if RIVE_NVN_HOOK_WINDOW_ACQUIRE
    if (!g_window_acquire_orig) {
        void* addr =
            reinterpret_cast<void*>(g_device->GetProcAddress(kWindowAcquireTexture));
        if (!g_window_acquire_orig &&
            should_hook_proc(addr,
                             reinterpret_cast<void*>(nvnWindowAcquireTexture_hook))) {
            A64HookFunction(addr,
                            reinterpret_cast<void*>(nvnWindowAcquireTexture_hook),
                            reinterpret_cast<void**>(&g_window_acquire_orig));
        }
    }
#endif
    debug_log("[rive] window hooks installed");
}

[[maybe_unused]] void install_queue_hooks()
{
    if (!g_device || (g_queue_submit_orig && g_queue_present_orig)) {
        return;
    }
    if (!g_queue_submit_orig) {
        void* submit_addr =
            reinterpret_cast<void*>(g_device->GetProcAddress(kQueueSubmit));
        debug_log("[rive] queue submit addr=%p", submit_addr);
        if (!g_queue_submit_orig &&
            should_hook_proc(submit_addr,
                             reinterpret_cast<void*>(nvnQueueSubmitCommands_hook))) {
            A64HookFunction(submit_addr,
                            reinterpret_cast<void*>(nvnQueueSubmitCommands_hook),
                            reinterpret_cast<void**>(&g_queue_submit_orig));
        }
    }
    if (!g_queue_present_orig) {
        void* addr =
            reinterpret_cast<void*>(g_device->GetProcAddress(kQueuePresent));
        if (!g_queue_present_orig &&
            should_hook_proc(addr,
                             reinterpret_cast<void*>(nvnQueuePresentTexture_hook))) {
            A64HookFunction(addr,
                            reinterpret_cast<void*>(nvnQueuePresentTexture_hook),
                            reinterpret_cast<void**>(&g_queue_present_orig));
        }
    }
    debug_log("[rive] queue hook installed");
}

nvn::GenericFuncPtr nvnDeviceGetProcAddress_hook(const nvn::Device* device,
                                                 const char* procName)
{
    if (!g_device_get_proc_orig) {
        return nullptr;
    }
    if (!g_device) {
        g_device = const_cast<nvn::Device*>(device);
    }
    ensure_device_initialized(g_device);
    nvn::GenericFuncPtr ptr =
        reinterpret_cast<nvn::GenericFuncPtr>(
            g_device_get_proc_orig(device, procName));
    if (!ptr || !procName) {
        return ptr;
    }

    if (std::strcmp(procName, kQueueInitialize) == 0) {
        if (!g_queue_init_orig) {
            g_queue_init_orig =
                reinterpret_cast<nvn::NVN_TYPE(QueueInitialize)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnQueueInitialize_hook);
    }
    if (std::strcmp(procName, kCommandBufferInitialize) == 0) {
        if (!g_command_buffer_init_orig) {
            g_command_buffer_init_orig =
                reinterpret_cast<nvn::NVN_TYPE(CommandBufferInitialize)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnCommandBufferInitialize_hook);
    }
    if (std::strcmp(procName, kCommandBufferBeginRecording) == 0) {
        if (!g_command_buffer_begin_orig) {
            g_command_buffer_begin_orig =
                reinterpret_cast<nvn::NVN_TYPE(CommandBufferBeginRecording)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnCommandBufferBeginRecording_hook);
    }
    if (std::strcmp(procName, kCommandBufferEndRecording) == 0) {
        if (!g_command_buffer_end_orig) {
            g_command_buffer_end_orig =
                reinterpret_cast<nvn::NVN_TYPE(CommandBufferEndRecording)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnCommandBufferEndRecording_hook);
    }
    if (std::strcmp(procName, kQueuePresent) == 0) {
        if (!g_queue_present_orig) {
            g_queue_present_orig =
                reinterpret_cast<nvn::NVN_TYPE(QueuePresentTexture)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnQueuePresentTexture_hook);
    }
    if (std::strcmp(procName, kQueueSubmit) == 0) {
        if (!g_queue_submit_orig) {
            g_queue_submit_orig =
                reinterpret_cast<nvn::NVN_TYPE(QueueSubmitCommands)>(ptr);
        }
        return ptr;
    }
    if (std::strcmp(procName, kCommandBufferSetTexturePool) == 0) {
        if (!g_command_set_texture_pool_orig) {
            g_command_set_texture_pool_orig =
                reinterpret_cast<nvn::NVN_TYPE(CommandBufferSetTexturePool)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnCommandBufferSetTexturePool_hook);
    }
    if (std::strcmp(procName, kCommandBufferSetSamplerPool) == 0) {
        if (!g_command_set_sampler_pool_orig) {
            g_command_set_sampler_pool_orig =
                reinterpret_cast<nvn::NVN_TYPE(CommandBufferSetSamplerPool)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnCommandBufferSetSamplerPool_hook);
    }
    if (std::strcmp(procName, kWindowSetCrop) == 0) {
        if (!g_window_set_crop_orig) {
            g_window_set_crop_orig =
                reinterpret_cast<nvn::NVN_TYPE(WindowSetCrop)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnWindowSetCrop_hook);
    }
    if (std::strcmp(procName, kWindowSetTextures) == 0) {
        if (!g_window_set_textures_orig) {
            g_window_set_textures_orig =
                reinterpret_cast<nvn::NVN_TYPE(WindowBuilderSetTextures)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnWindowBuilderSetTextures_hook);
    }
    if (std::strcmp(procName, kWindowInitialize) == 0) {
        if (!g_window_init_orig) {
            g_window_init_orig =
                reinterpret_cast<nvn::NVN_TYPE(WindowInitialize)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnWindowInitialize_hook);
    }
    if (std::strcmp(procName, kWindowAcquireTexture) == 0) {
#if RIVE_NVN_HOOK_WINDOW_ACQUIRE
        if (!g_window_acquire_orig) {
            g_window_acquire_orig =
                reinterpret_cast<nvn::NVN_TYPE(WindowAcquireTexture)>(ptr);
        }
        return reinterpret_cast<nvn::GenericFuncPtr>(
            &nvnWindowAcquireTexture_hook);
#else
        if (!g_window_acquire_orig) {
            g_window_acquire_orig =
                reinterpret_cast<nvn::NVN_TYPE(WindowAcquireTexture)>(ptr);
        }
        return ptr;
#endif
    }

    return ptr;
}

bool nvnDeviceInitialize_hook(nvn::Device* device,
                              const nvn::DeviceBuilder* builder)
{
    if (!g_device_init_orig) {
        return false;
    }

    bool ok = g_device_init_orig(device, builder);
    if (!ok) {
        return ok;
    }

    g_device = device;

    if (!g_device_get_proc_orig && g_bootstrap_orig) {
        g_device_get_proc_orig =
            reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(
                g_bootstrap_orig(kGetAddress));
    }
    if (!g_device_get_proc_orig) {
        g_device_get_proc_orig =
            reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(
                device->GetProcAddress(kGetAddress));
    }
    if (!g_device_get_proc_orig) {
        return ok;
    }
    ensure_device_initialized(device);
    return ok;
}

nvn::GenericFuncPtr nvnBootstrapLoader_hook(const char* symbol)
{
    g_bootstrap_active.store(true, std::memory_order_relaxed);
    nvn::GenericFuncPtr ret = g_bootstrap_orig(symbol);
    if (!ret || !symbol) {
        return ret;
    }
    if (std::strcmp(symbol, kDeviceInit) == 0) {
        if (!g_device_init_orig) {
            void* orig = nullptr;
            A64HookFunction(reinterpret_cast<void*>(ret),
                            reinterpret_cast<void*>(nvnDeviceInitialize_hook),
                            &orig);
            if (orig) {
                g_device_init_orig =
                    reinterpret_cast<nvn::NVN_TYPE(DeviceInitialize)>(orig);
            }
        }
        return ret;
    } else if (std::strcmp(symbol, kGetAddress) == 0) {
        if (!g_device_get_proc_orig) {
            void* orig = nullptr;
            A64HookFunction(reinterpret_cast<void*>(ret),
                            reinterpret_cast<void*>(nvnDeviceGetProcAddress_hook),
                            &orig);
            if (orig) {
                g_device_get_proc_orig =
                    reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(orig);
            } else {
                g_device_get_proc_orig =
                    reinterpret_cast<nvn::NVN_TYPE(DeviceGetProcAddress)>(ret);
            }
        }
        return ret;
    }
    return ret;
}

nvn::GenericFuncPtr bootstrap_hook_impl(const char* symbol,
                                        nvn::GenericFuncPtr original)
{
    if (original) {
        g_bootstrap_orig =
            reinterpret_cast<nvn::GenericFuncPtr (*)(const char*)>(original);
    }
    if (!g_bootstrap_orig) {
        set_error("bootstrap orig missing");
        return nullptr;
    }
    g_hooks_installed.store(true, std::memory_order_relaxed);
    return nvnBootstrapLoader_hook(symbol);
}

bool hook_symbol(const char* symbol, void* hook, void** orig)
{
    if (!symbol || !hook || !orig || *orig) {
        return false;
    }
    uintptr_t addr = 0;
    bool used_fallback = false;
    if (R_FAILED(nn::ro::LookupSymbol(&addr, symbol)) || addr < 0x1000) {
        nvn::GenericFuncPtr resolved = lookup_nvn_symbol(symbol);
        if (resolved) {
            addr = reinterpret_cast<uintptr_t>(resolved);
        }
#if RIVE_NVN_ADDR_FALLBACK
        if (addr < 0x1000) {
            if (std::strcmp(symbol, kDeviceInit) == 0) {
                addr = kNvnDeviceInitializeAddr;
            } else if (std::strcmp(symbol, kGetAddress) == 0) {
                addr = kNvnDeviceGetProcAddressAddr;
            } else if (std::strcmp(symbol, kQueueSubmit) == 0) {
                addr = kNvnQueueSubmitAddr;
            } else if (std::strcmp(symbol, kQueuePresent) == 0) {
                addr = kNvnQueuePresentAddr;
            } else {
                addr = 0;
            }
            used_fallback = addr >= 0x1000;
        }
#else
        addr = 0;
#endif
    }
    if (used_fallback && !is_address_in_text(addr)) {
        static bool s_logged_unmapped = false;
        if (!s_logged_unmapped) {
            debug_log("[rive] fallback addr not in text for %s", symbol);
            s_logged_unmapped = true;
        }
        addr = 0;
    }
    if (addr < 0x1000) {
        return false;
    }
    A64HookFunction(reinterpret_cast<void*>(addr), hook, orig);
    return *orig != nullptr;
}

} // namespace

extern "C" RIVE_EXPORT nvn::GenericFuncPtr rive_runtime_bootstrap_hook(
    const char* symbol,
    nvn::GenericFuncPtr original)
{
    return bootstrap_hook_impl(symbol, original);
}

extern "C" RIVE_EXPORT void rive_runtime_install_hooks()
{
    if (g_hooks_installed.load(std::memory_order_relaxed)) {
        return;
    }

    debug_log("[rive] installing bootstrap hook");
    set_error("install_hooks");
    nn::ro::Initialize();
    bool installed = false;
    void* bootstrap = reinterpret_cast<void*>(nvnBootstrapLoader);
    if (!g_bootstrap_orig && bootstrap) {
        A64HookFunction(
            bootstrap,
            reinterpret_cast<void*>(nvnBootstrapLoader_hook),
            reinterpret_cast<void**>(&g_bootstrap_orig));
        if (g_bootstrap_orig) {
            installed = true;
        }
    }
    if (!g_bootstrap_orig) {
        uintptr_t bootstrap_addr = 0;
        if (R_FAILED(nn::ro::LookupSymbol(&bootstrap_addr, "nvnBootstrapLoader")) ||
            bootstrap_addr < 0x1000) {
            debug_log("[rive] nvnBootstrapLoader missing");
        } else {
            void* bootstrap_ptr = reinterpret_cast<void*>(bootstrap_addr);
            A64HookFunction(
                bootstrap_ptr,
                reinterpret_cast<void*>(nvnBootstrapLoader_hook),
                reinterpret_cast<void**>(&g_bootstrap_orig));
            if (g_bootstrap_orig) {
                installed = true;
            }
        }
    }
#if RIVE_NVN_ADDR_FALLBACK
    if (!g_bootstrap_orig && kNvnBootstrapLoaderAddr >= 0x1000) {
        if (is_address_in_text(kNvnBootstrapLoaderAddr)) {
            A64HookFunction(
                reinterpret_cast<void*>(kNvnBootstrapLoaderAddr),
                reinterpret_cast<void*>(nvnBootstrapLoader_hook),
                reinterpret_cast<void**>(&g_bootstrap_orig));
            if (g_bootstrap_orig) {
                installed = true;
            }
        } else {
            debug_log("[rive] bootstrap fallback addr not in text");
        }
    }
#endif

    if (!g_nvn_loader_orig) {
        void* base = skyline::utils::getRegionAddress(skyline::utils::region::Text);
        if (base) {
            uintptr_t addr = reinterpret_cast<uintptr_t>(base) + kNvnLoaderOffset;
            if (is_address_in_text(addr)) {
                A64HookFunction(
                    reinterpret_cast<void*>(addr),
                    reinterpret_cast<void*>(nvn_loader_hook),
                    reinterpret_cast<void**>(&g_nvn_loader_orig));
                if (g_nvn_loader_orig) {
                    installed = true;
                }
            } else {
                debug_log("[rive] nvn loader addr not in text");
            }
        }
    }

    if (hook_symbol(kDeviceInit,
                    reinterpret_cast<void*>(nvnDeviceInitialize_hook),
                    reinterpret_cast<void**>(&g_device_init_orig))) {
        installed = true;
    }
    if (hook_symbol(kGetAddress,
                    reinterpret_cast<void*>(nvnDeviceGetProcAddress_hook),
                    reinterpret_cast<void**>(&g_device_get_proc_orig))) {
        installed = true;
    }
    if (hook_symbol(kQueuePresent,
                    reinterpret_cast<void*>(nvnQueuePresentTexture_hook),
                    reinterpret_cast<void**>(&g_queue_present_orig))) {
        installed = true;
    }
    if (hook_symbol(kQueueSubmit,
                    reinterpret_cast<void*>(nvnQueueSubmitCommands_hook),
                    reinterpret_cast<void**>(&g_queue_submit_orig))) {
        installed = true;
    }
    if (hook_symbol(kQueueInitialize,
                    reinterpret_cast<void*>(nvnQueueInitialize_hook),
                    reinterpret_cast<void**>(&g_queue_init_orig))) {
        installed = true;
    }
    if (hook_symbol(kCommandBufferInitialize,
                    reinterpret_cast<void*>(nvnCommandBufferInitialize_hook),
                    reinterpret_cast<void**>(&g_command_buffer_init_orig))) {
        installed = true;
    }
    if (hook_symbol(kCommandBufferBeginRecording,
                    reinterpret_cast<void*>(nvnCommandBufferBeginRecording_hook),
                    reinterpret_cast<void**>(&g_command_buffer_begin_orig))) {
        installed = true;
    }
    if (hook_symbol(kCommandBufferEndRecording,
                    reinterpret_cast<void*>(nvnCommandBufferEndRecording_hook),
                    reinterpret_cast<void**>(&g_command_buffer_end_orig))) {
        installed = true;
    }
    if (hook_symbol(kCommandBufferSetTexturePool,
                    reinterpret_cast<void*>(nvnCommandBufferSetTexturePool_hook),
                    reinterpret_cast<void**>(&g_command_set_texture_pool_orig))) {
        installed = true;
    }
    if (hook_symbol(kCommandBufferSetSamplerPool,
                    reinterpret_cast<void*>(nvnCommandBufferSetSamplerPool_hook),
                    reinterpret_cast<void**>(&g_command_set_sampler_pool_orig))) {
        installed = true;
    }
    if (hook_symbol(kWindowSetTextures,
                    reinterpret_cast<void*>(nvnWindowBuilderSetTextures_hook),
                    reinterpret_cast<void**>(&g_window_set_textures_orig))) {
        installed = true;
    }
    if (hook_symbol(kWindowInitialize,
                    reinterpret_cast<void*>(nvnWindowInitialize_hook),
                    reinterpret_cast<void**>(&g_window_init_orig))) {
        installed = true;
    }
#if RIVE_NVN_HOOK_WINDOW_ACQUIRE
    if (hook_symbol(kWindowAcquireTexture,
                    reinterpret_cast<void*>(nvnWindowAcquireTexture_hook),
                    reinterpret_cast<void**>(&g_window_acquire_orig))) {
        installed = true;
    }
#endif
    if (hook_symbol(kWindowSetCrop,
                    reinterpret_cast<void*>(nvnWindowSetCrop_hook),
                    reinterpret_cast<void**>(&g_window_set_crop_orig))) {
        installed = true;
    }

    if (installed) {
        g_hooks_installed.store(true, std::memory_order_relaxed);
        set_error("ok");
    } else {
        set_error("nvn hooks missing");
    }
}

extern "C" RIVE_EXPORT void rive_runtime_set_artboard(RiveArtboard* artboard)
{
    g_artboard.store(artboard, std::memory_order_relaxed);
    debug_log("[rive] artboard set: %p", artboard);
}

extern "C" RIVE_EXPORT void rive_runtime_set_enabled(int enabled)
{
    g_enabled.store(enabled != 0, std::memory_order_relaxed);
}

extern "C" RIVE_EXPORT void rive_runtime_set_allocator(const RiveNVNAllocator* allocator)
{
    if (allocator) {
        g_allocator = *allocator;
        g_allocator_set.store(true, std::memory_order_relaxed);
    } else {
        g_allocator = {};
        g_allocator_set.store(false, std::memory_order_relaxed);
    }
}

extern "C" RIVE_EXPORT void rive_runtime_set_render_mode_impl(RiveRuntimeRenderMode mode)
{
    g_render_mode.store(static_cast<int>(mode), std::memory_order_relaxed);
    g_logged_render_attempt = false;
    if (mode == RIVE_RUNTIME_RENDER_DIRECT) {
        reset_offscreen();
    }
}

extern "C" RIVE_EXPORT void rive_runtime_set_msaa_samples(int samples)
{
    int clamped = samples;
    if (clamped <= 1) {
        clamped = 0;
    } else if (clamped > 8) {
        clamped = 8;
    }
    g_force_msaa_samples.store(clamped, std::memory_order_relaxed);
    g_logged_render_attempt = false;
    debug_log("[rive] forced msaa samples=%d", clamped);
}

extern "C" RIVE_EXPORT int rive_runtime_install_main_loop_hook(uint64_t text_offset)
{
    if (g_main_loop_orig) {
        return 1;
    }
    install_input_hooks();
    if (text_offset == 0) {
        set_error("main loop offset missing");
        return 0;
    }
    void* base = skyline::utils::getRegionAddress(skyline::utils::region::Text);
    if (!base) {
        set_error("text base missing");
        return 0;
    }
    uintptr_t address = reinterpret_cast<uintptr_t>(base) + text_offset;
    A64HookFunction(
        reinterpret_cast<void*>(address),
        reinterpret_cast<void*>(main_loop_hook),
        reinterpret_cast<void**>(&g_main_loop_orig));
    if (g_main_loop_orig) {
        debug_log("[rive] main loop hook installed at 0x%llx", text_offset);
        return 1;
    }
    set_error("main loop hook failed");
    return 0;
}

extern "C" RIVE_EXPORT void rive_runtime_get_status(RiveRuntimeStatus* out_status)
{
    if (!out_status) {
        return;
    }
    out_status->version = 1;
    out_status->enabled = g_enabled.load(std::memory_order_relaxed) ? 1 : 0;
    out_status->hooks_installed =
        g_hooks_installed.load(std::memory_order_relaxed) ? 1 : 0;
    out_status->device_ready = g_device ? 1 : 0;
    out_status->queue_hooked = g_queue_submit_orig ? 1 : 0;
    out_status->window_hooked =
        (g_window_set_textures_orig && g_window_acquire_orig) ? 1 : 0;
    out_status->has_context = g_host.context ? 1 : 0;
    out_status->has_renderer = g_host.renderer ? 1 : 0;
    out_status->has_target = g_host.target ? 1 : 0;
    out_status->textures_count =
        static_cast<uint32_t>(g_window_texture_count);
    out_status->display_index = g_display_texture_index;
    out_status->allocator_set =
        g_allocator_set.load(std::memory_order_relaxed) ? 1 : 0;
    out_status->last_error = g_last_error;
    out_status->artboard = g_artboard.load(std::memory_order_relaxed);
    out_status->device = g_device;
    out_status->queue = g_last_queue;
}

extern "C" RIVE_EXPORT const char* rive_runtime_last_error()
{
    return g_last_error;
}

extern "C" RIVE_EXPORT void rive_runtime_set_toggle_callback_impl(RiveToggleCallback callback)
{
    g_toggle_callback = callback;
    install_input_hooks();
}

extern "C" bool rive_nvn_get_descriptor_pool_test_case(
    RiveDescriptorPoolTestCase* out_case)
{
    if (!out_case || !g_pool_test_valid.load(std::memory_order_relaxed)) {
        return false;
    }
    *out_case = g_pool_test_case;
    return true;
}

extern "C" uint32_t rive_nvn_get_descriptor_pool_test_version()
{
    return g_pool_test_version.load(std::memory_order_relaxed);
}

extern "C" void rive_nvn_set_descriptor_pool_test_case(
    const RiveDescriptorPoolTestCase* test_case,
    int index,
    int total)
{
    if (!test_case) {
        g_pool_test_valid.store(false, std::memory_order_relaxed);
        return;
    }
    g_pool_test_case = *test_case;
    g_pool_test_index.store(index, std::memory_order_relaxed);
    g_pool_test_total.store(total, std::memory_order_relaxed);
    g_pool_test_valid.store(true, std::memory_order_relaxed);
    g_pool_test_version.fetch_add(1, std::memory_order_relaxed);
}

extern "C" RIVE_EXPORT int rive_runtime_set_pending_riv_data(
    const uint8_t* data,
    size_t len)
{
    if (!data || len == 0) {
        return 0;
    }
    g_pending_riv_data.store(data, std::memory_order_relaxed);
    g_pending_riv_len.store(len, std::memory_order_relaxed);
    g_pending_file = nullptr;
    g_pending_artboard = nullptr;
    g_artboard.store(nullptr, std::memory_order_relaxed);
    g_logged_render_attempt = false;
    debug_log("[rive] pending riv data set len=%zu", len);
    return 1;
}
