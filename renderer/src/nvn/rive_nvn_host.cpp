/*
 * Copyright 2026 Rive
 */

#include "rive/capi.h"
#include <string>

struct RiveNVNSession
{
    RiveRenderContext* context = nullptr;
    RiveRenderer* renderer = nullptr;
    RiveRenderTarget* frameTarget = nullptr;
    RiveNVNFrameDesc pendingFrame = {};
    bool frameActive = false;
    std::string lastError;
};

namespace
{
static void set_session_error(RiveNVNSession* session, const char* message)
{
    if (session != nullptr)
    {
        session->lastError = message != nullptr ? message : "unknown";
    }
}
} // namespace

extern "C"
{
void rive_nvn_initialize(void* device, void* get_proc_address)
{
    (void)device;
    (void)get_proc_address;
}

RiveNVNSession* rive_nvn_session_new(const RiveNVNSessionDesc* desc)
{
    if (desc == nullptr)
    {
        return nullptr;
    }

    RiveNVNContextDesc contextDesc = {};
    contextDesc.device = desc->device;
    contextDesc.queue = desc->queue;
    contextDesc.get_proc_address = desc->get_proc_address;
    contextDesc.clip_space_bottom_up = desc->clip_space_bottom_up;
    contextDesc.framebuffer_bottom_up = desc->framebuffer_bottom_up;
    contextDesc.max_texture_size = 0;
    contextDesc.allocator = desc->allocator;

    RiveRenderContext* context = rive_nvn_render_context_new(&contextDesc);
    if (context == nullptr)
    {
        return nullptr;
    }

    RiveRenderer* renderer = rive_renderer_new(context);
    if (renderer == nullptr)
    {
        rive_render_context_release(context);
        return nullptr;
    }

    RiveNVNSession* session = new RiveNVNSession();
    session->context = context;
    session->renderer = renderer;
    return session;
}

void rive_nvn_session_release(RiveNVNSession* session)
{
    if (session == nullptr)
    {
        return;
    }
    if (session->frameTarget != nullptr)
    {
        rive_render_target_release(session->frameTarget);
    }
    rive_renderer_release(session->renderer);
    rive_render_context_release(session->context);
    delete session;
}

RiveRenderContext* rive_nvn_session_context(RiveNVNSession* session)
{
    return session != nullptr ? session->context : nullptr;
}

RiveRenderer* rive_nvn_session_renderer(RiveNVNSession* session)
{
    return session != nullptr ? session->renderer : nullptr;
}

int rive_nvn_session_begin_frame(RiveNVNSession* session,
                                 const RiveNVNFrameDesc* frame)
{
    if (session == nullptr || frame == nullptr || session->context == nullptr ||
        session->renderer == nullptr)
    {
        return 0;
    }
    if (frame->color_texture == nullptr || frame->command_buffer == nullptr ||
        frame->width == 0 || frame->height == 0)
    {
        set_session_error(session, "invalid frame descriptor");
        return 0;
    }

    if (session->frameTarget != nullptr)
    {
        rive_render_target_release(session->frameTarget);
        session->frameTarget = nullptr;
    }
    session->frameTarget = rive_nvn_render_target_new(frame->width,
                                                      frame->height,
                                                      frame->color_texture,
                                                      frame->depth_texture,
                                                      frame->msaa_sample_count);
    if (session->frameTarget == nullptr)
    {
        set_session_error(session, "failed to create render target");
        return 0;
    }

    RiveFrameDescriptor frameDesc = {};
    frameDesc.render_target_width = frame->width;
    frameDesc.render_target_height = frame->height;
    frameDesc.load_action = frame->load_action;
    frameDesc.clear_color = frame->clear_color;
    frameDesc.msaa_sample_count = frame->msaa_sample_count;
    frameDesc.disable_raster_ordering = frame->disable_raster_ordering != 0;
    frameDesc.wireframe = 0;
    frameDesc.fills_disabled = 0;
    frameDesc.strokes_disabled = 0;
    frameDesc.clockwise_fill_override = frame->clockwise_fill_override != 0;
    rive_render_context_begin_frame(session->context, &frameDesc);

    session->pendingFrame = *frame;
    session->frameActive = true;
    session->lastError.clear();
    return 1;
}

int rive_nvn_session_end_frame(RiveNVNSession* session)
{
    if (session == nullptr || !session->frameActive || session->context == nullptr ||
        session->frameTarget == nullptr)
    {
        return 0;
    }

    RiveFlushResources resources = {};
    resources.render_target = session->frameTarget;
    resources.external_command_buffer = session->pendingFrame.command_buffer;
    resources.current_frame_number = session->pendingFrame.frame_number;
    resources.safe_frame_number = session->pendingFrame.safe_frame_number;
    rive_render_context_flush(session->context, &resources);

    rive_render_target_release(session->frameTarget);
    session->frameTarget = nullptr;
    session->frameActive = false;
    return 1;
}

int rive_nvn_session_render_artboard(RiveNVNSession* session,
                                     RiveArtboard* artboard,
                                     const RiveNVNFrameDesc* frame)
{
    if (session == nullptr || artboard == nullptr || frame == nullptr)
    {
        return 0;
    }
    if (!rive_nvn_session_begin_frame(session, frame))
    {
        return 0;
    }

    RiveAABB frameAABB = {};
    frameAABB.min_x = 0.0f;
    frameAABB.min_y = 0.0f;
    frameAABB.max_x = static_cast<float>(frame->width);
    frameAABB.max_y = static_cast<float>(frame->height);

    RiveAABB content = {};
    content.min_x = 0.0f;
    content.min_y = 0.0f;
    content.max_x = rive_artboard_width(artboard);
    content.max_y = rive_artboard_height(artboard);

    rive_renderer_save(session->renderer);
    rive_renderer_align(
        session->renderer, frame->fit, frame->alignment, frameAABB, content, frame->scale_factor);
    rive_renderer_draw_artboard(session->renderer, artboard);
    rive_renderer_restore(session->renderer);

    return rive_nvn_session_end_frame(session);
}

const char* rive_nvn_session_last_error(const RiveNVNSession* session)
{
    if (session == nullptr || session->lastError.empty())
    {
        return "";
    }
    return session->lastError.c_str();
}

static RiveRuntimeStatus g_runtimeStatus = {};
static std::string g_runtimeLastError;
static RiveRuntimeToggleCallback g_runtimeToggleCallback = nullptr;

void rive_runtime_install_hooks(void)
{
    g_runtimeStatus.hooks_installed = 0;
}

void rive_runtime_set_artboard(RiveArtboard* artboard)
{
    g_runtimeStatus.artboard = artboard;
}

void rive_runtime_set_enabled(int enabled)
{
    g_runtimeStatus.enabled = enabled ? 1u : 0u;
}

void rive_runtime_set_allocator(const RiveNVNAllocator* allocator)
{
    g_runtimeStatus.allocator_set = allocator != nullptr ? 1u : 0u;
}

void rive_runtime_set_render_mode(RiveRuntimeRenderMode mode)
{
    (void)mode;
}

int rive_runtime_install_main_loop_hook(uint64_t text_offset)
{
    (void)text_offset;
    g_runtimeLastError = "runtime hooks are not implemented in this build";
    return 0;
}

void rive_runtime_get_status(RiveRuntimeStatus* out_status)
{
    if (out_status != nullptr)
    {
        *out_status = g_runtimeStatus;
        out_status->last_error = g_runtimeLastError.c_str();
    }
}

const char* rive_runtime_last_error(void)
{
    return g_runtimeLastError.c_str();
}

void rive_runtime_set_toggle_callback(RiveRuntimeToggleCallback callback)
{
    g_runtimeToggleCallback = callback;
    (void)g_runtimeToggleCallback;
}

int rive_runtime_set_pending_riv_data(const uint8_t* data, size_t len)
{
    if (data == nullptr || len == 0)
    {
        g_runtimeLastError = "invalid rive payload";
        return 0;
    }
    g_runtimeLastError = "hot-loading .riv payload is not implemented yet";
    return 0;
}
}
