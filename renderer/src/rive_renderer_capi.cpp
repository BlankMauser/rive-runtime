#include "rive/capi.h"
#include "rive/capi_internal.hpp"
#include "rive/artboard.hpp"
#include "rive/file.hpp"
#include "rive/renderer.hpp"
#include "rive/renderer/render_context.hpp"
#include "rive/renderer/render_context_impl.hpp"
#include "rive/renderer/capi_renderer.hpp"
#include "rive/renderer/rive_renderer.hpp"
#include "rive/span.hpp"

#include <new>

struct RiveRenderContext
{
    std::unique_ptr<rive::gpu::RenderContext> context;
};

struct RiveRenderer
{
    std::unique_ptr<rive::RiveRenderer> renderer;
};

RiveRenderContext* rive_render_context_new(RiveRenderContextImpl* impl)
{
    if (!impl)
    {
        return nullptr;
    }

    RiveRenderContext* wrapper = new (std::nothrow) RiveRenderContext();
    if (!wrapper)
    {
        return nullptr;
    }

    auto impl_ptr = std::unique_ptr<rive::gpu::RenderContextImpl>(
        reinterpret_cast<rive::gpu::RenderContextImpl*>(impl));
    wrapper->context =
        std::make_unique<rive::gpu::RenderContext>(std::move(impl_ptr));
    return wrapper;
}

static RiveImportResult to_c_result(rive::ImportResult result)
{
    switch (result)
    {
        case rive::ImportResult::success:
            return RIVE_IMPORT_SUCCESS;
        case rive::ImportResult::unsupportedVersion:
            return RIVE_IMPORT_UNSUPPORTED_VERSION;
        case rive::ImportResult::malformed:
        default:
            return RIVE_IMPORT_MALFORMED;
    }
}

RiveFile* rive_file_import_with_render_context(RiveRenderContext* render_context,
                                               const uint8_t* data,
                                               size_t data_size,
                                               RiveImportResult* out_result)
{
    if (out_result)
    {
        *out_result = RIVE_IMPORT_MALFORMED;
    }
    if (!render_context || !render_context->context || !data || data_size == 0)
    {
        return nullptr;
    }

    rive::ImportResult result = rive::ImportResult::malformed;
    auto file = rive::File::import(
        rive::Span<const uint8_t>(data, data_size),
        render_context->context.get(),
        &result);
    if (out_result)
    {
        *out_result = to_c_result(result);
    }
    if (!file)
    {
        return nullptr;
    }

    RiveFile* wrapper = new (std::nothrow) RiveFile();
    if (!wrapper)
    {
        return nullptr;
    }
    wrapper->factory = std::shared_ptr<rive::Factory>(
        render_context->context.get(),
        [](rive::Factory*) {});
    wrapper->file = std::move(file);
    return wrapper;
}

void rive_render_context_release(RiveRenderContext* context)
{
    delete context;
}

void rive_render_context_begin_frame(RiveRenderContext* context,
                                     const RiveFrameDescriptor* desc)
{
    if (!context || !context->context || !desc)
    {
        return;
    }

    rive::gpu::RenderContext::FrameDescriptor frame = {};
    frame.renderTargetWidth = desc->render_target_width;
    frame.renderTargetHeight = desc->render_target_height;
    frame.loadAction = static_cast<rive::gpu::LoadAction>(desc->load_action);
    frame.clearColor = desc->clear_color;
    frame.msaaSampleCount = desc->msaa_sample_count;
    frame.disableRasterOrdering = desc->disable_raster_ordering != 0;
    frame.wireframe = desc->wireframe != 0;
    frame.fillsDisabled = desc->fills_disabled != 0;
    frame.strokesDisabled = desc->strokes_disabled != 0;
    frame.clockwiseFillOverride = desc->clockwise_fill_override != 0;

    context->context->beginFrame(frame);
}

void rive_render_context_logical_flush(RiveRenderContext* context)
{
    if (!context || !context->context)
    {
        return;
    }
    context->context->logicalFlush();
}

void rive_render_context_flush(RiveRenderContext* context,
                               const RiveFlushResources* resources)
{
    if (!context || !context->context || !resources)
    {
        return;
    }

    rive::gpu::RenderContext::FlushResources flush = {};
    flush.renderTarget =
        reinterpret_cast<rive::gpu::RenderTarget*>(resources->render_target);
    flush.externalCommandBuffer = resources->external_command_buffer;
    flush.currentFrameNumber = resources->current_frame_number;
    flush.safeFrameNumber = resources->safe_frame_number;
    context->context->flush(flush);
}

void rive_render_context_release_resources(RiveRenderContext* context)
{
    if (!context || !context->context)
    {
        return;
    }
    context->context->releaseResources();
}

RiveRenderer* rive_renderer_new(RiveRenderContext* context)
{
    if (!context || !context->context)
    {
        return nullptr;
    }

    RiveRenderer* wrapper = new (std::nothrow) RiveRenderer();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->renderer =
        std::make_unique<rive::RiveRenderer>(context->context.get());
    return wrapper;
}

void rive_renderer_release(RiveRenderer* renderer)
{
    delete renderer;
}

void rive_renderer_save(RiveRenderer* renderer)
{
    if (!renderer || !renderer->renderer)
    {
        return;
    }
    renderer->renderer->save();
}

void rive_renderer_restore(RiveRenderer* renderer)
{
    if (!renderer || !renderer->renderer)
    {
        return;
    }
    renderer->renderer->restore();
}

void rive_renderer_transform(RiveRenderer* renderer, const RiveMat2D* matrix)
{
    if (!renderer || !renderer->renderer || !matrix)
    {
        return;
    }
    const float* v = matrix->values;
    renderer->renderer->transform(rive::Mat2D(v[0], v[1], v[2], v[3], v[4], v[5]));
}

void rive_renderer_translate(RiveRenderer* renderer, float x, float y)
{
    if (!renderer || !renderer->renderer)
    {
        return;
    }
    renderer->renderer->translate(x, y);
}

void rive_renderer_scale(RiveRenderer* renderer, float x, float y)
{
    if (!renderer || !renderer->renderer)
    {
        return;
    }
    renderer->renderer->scale(x, y);
}

void rive_renderer_rotate(RiveRenderer* renderer, float radians)
{
    if (!renderer || !renderer->renderer)
    {
        return;
    }
    renderer->renderer->rotate(radians);
}

void rive_renderer_modulate_opacity(RiveRenderer* renderer, float opacity)
{
    if (!renderer || !renderer->renderer)
    {
        return;
    }
    renderer->renderer->modulateOpacity(opacity);
}

void rive_renderer_draw_artboard(RiveRenderer* renderer, RiveArtboard* artboard)
{
    if (!renderer || !renderer->renderer || !artboard || !artboard->artboard)
    {
        return;
    }
    artboard->artboard->draw(renderer->renderer.get());
}

void rive_renderer_align(RiveRenderer* renderer,
                         RiveFit fit,
                         RiveAlignment alignment,
                         RiveAABB frame,
                         RiveAABB content,
                         float scale_factor)
{
    if (!renderer || !renderer->renderer)
    {
        return;
    }
    rive::Mat2D matrix = rive::computeAlignment(
        static_cast<rive::Fit>(fit),
        rive::Alignment(alignment.x, alignment.y),
        rive::AABB(frame.min_x, frame.min_y, frame.max_x, frame.max_y),
        rive::AABB(content.min_x, content.min_y, content.max_x, content.max_y),
        scale_factor);
    renderer->renderer->transform(matrix);
}

void rive_render_target_release(RiveRenderTarget* target)
{
    delete target;
}

uint32_t rive_render_target_width(const RiveRenderTarget* target)
{
    return target ? target->width() : 0;
}

uint32_t rive_render_target_height(const RiveRenderTarget* target)
{
    return target ? target->height() : 0;
}
