#ifndef RIVE_CAPI_H_
#define RIVE_CAPI_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RiveFile RiveFile;
typedef struct RiveArtboard RiveArtboard;
typedef struct RiveLinearAnimation RiveLinearAnimation;
typedef struct RiveStateMachine RiveStateMachine;
typedef struct RiveRenderer RiveRenderer;
typedef struct RiveRenderContext RiveRenderContext;
typedef struct RiveRenderContextImpl RiveRenderContextImpl;
typedef struct RiveRenderTarget RiveRenderTarget;
typedef struct RiveNVNAllocator RiveNVNAllocator;

typedef struct RiveAABB
{
    float min_x;
    float min_y;
    float max_x;
    float max_y;
} RiveAABB;

typedef struct RiveMat2D
{
    float values[6];
} RiveMat2D;

typedef enum RiveFit
{
    RIVE_FIT_FILL = 0,
    RIVE_FIT_CONTAIN = 1,
    RIVE_FIT_COVER = 2,
    RIVE_FIT_FIT_WIDTH = 3,
    RIVE_FIT_FIT_HEIGHT = 4,
    RIVE_FIT_NONE = 5,
    RIVE_FIT_SCALE_DOWN = 6,
    RIVE_FIT_LAYOUT = 7,
} RiveFit;

typedef struct RiveAlignment
{
    float x;
    float y;
} RiveAlignment;

typedef enum RiveLoadAction
{
    RIVE_LOAD_CLEAR = 0,
    RIVE_LOAD_PRESERVE_RENDER_TARGET = 1,
    RIVE_LOAD_DONT_CARE = 2,
} RiveLoadAction;

typedef struct RiveFrameDescriptor
{
    uint32_t render_target_width;
    uint32_t render_target_height;
    RiveLoadAction load_action;
    uint32_t clear_color;
    uint32_t msaa_sample_count;
    uint8_t disable_raster_ordering;
    uint8_t wireframe;
    uint8_t fills_disabled;
    uint8_t strokes_disabled;
    uint8_t clockwise_fill_override;
} RiveFrameDescriptor;

typedef struct RiveFlushResources
{
    RiveRenderTarget* render_target;
    void* external_command_buffer;
    uint64_t current_frame_number;
    uint64_t safe_frame_number;
} RiveFlushResources;

typedef enum RiveImportResult
{
    RIVE_IMPORT_SUCCESS = 0,
    RIVE_IMPORT_UNSUPPORTED_VERSION = 1,
    RIVE_IMPORT_MALFORMED = 2,
} RiveImportResult;

RiveFile* rive_file_import(const uint8_t* data,
                           size_t data_size,
                           RiveImportResult* out_result);
RiveFile* rive_file_import_with_render_context(
    RiveRenderContext* render_context,
    const uint8_t* data,
    size_t data_size,
    RiveImportResult* out_result);

void rive_file_release(RiveFile* file);

size_t rive_file_artboard_count(const RiveFile* file);

size_t rive_file_artboard_name(const RiveFile* file,
                               size_t index,
                               char* buffer,
                               size_t buffer_size);

RiveArtboard* rive_file_artboard_default(RiveFile* file);
RiveArtboard* rive_file_artboard_at(RiveFile* file, size_t index);
RiveArtboard* rive_file_artboard_named(RiveFile* file, const char* name);

void rive_artboard_release(RiveArtboard* artboard);
int rive_artboard_advance(RiveArtboard* artboard, float elapsed_seconds);
float rive_artboard_width(const RiveArtboard* artboard);
float rive_artboard_height(const RiveArtboard* artboard);
float rive_artboard_original_width(const RiveArtboard* artboard);
float rive_artboard_original_height(const RiveArtboard* artboard);
int rive_artboard_bounds(const RiveArtboard* artboard, RiveAABB* out_bounds);
int rive_artboard_world_bounds(const RiveArtboard* artboard,
                               RiveAABB* out_bounds);

int rive_compute_alignment(RiveFit fit,
                           RiveAlignment alignment,
                           RiveAABB frame,
                           RiveAABB content,
                           float scale_factor,
                           RiveMat2D* out_matrix);

size_t rive_artboard_animation_count(const RiveArtboard* artboard);
size_t rive_artboard_animation_name(const RiveArtboard* artboard,
                                    size_t index,
                                    char* buffer,
                                    size_t buffer_size);
RiveLinearAnimation* rive_artboard_animation_at(RiveArtboard* artboard,
                                                size_t index);
RiveLinearAnimation* rive_artboard_animation_named(RiveArtboard* artboard,
                                                   const char* name);

void rive_linear_animation_release(RiveLinearAnimation* animation);
int rive_linear_animation_advance(RiveLinearAnimation* animation,
                                  float elapsed_seconds);
void rive_linear_animation_apply(RiveLinearAnimation* animation, float mix);
int rive_linear_animation_advance_and_apply(RiveLinearAnimation* animation,
                                            float elapsed_seconds,
                                            float mix);
float rive_linear_animation_time(const RiveLinearAnimation* animation);
void rive_linear_animation_set_time(RiveLinearAnimation* animation, float time);

size_t rive_artboard_state_machine_count(const RiveArtboard* artboard);
size_t rive_artboard_state_machine_name(const RiveArtboard* artboard,
                                        size_t index,
                                        char* buffer,
                                        size_t buffer_size);
RiveStateMachine* rive_artboard_state_machine_at(RiveArtboard* artboard,
                                                 size_t index);
RiveStateMachine* rive_artboard_state_machine_named(RiveArtboard* artboard,
                                                    const char* name);

void rive_state_machine_release(RiveStateMachine* machine);
int rive_state_machine_advance(RiveStateMachine* machine,
                               float elapsed_seconds);
int rive_state_machine_set_bool(RiveStateMachine* machine,
                                const char* name,
                                int value);
int rive_state_machine_set_number(RiveStateMachine* machine,
                                  const char* name,
                                  float value);
int rive_state_machine_fire_trigger(RiveStateMachine* machine,
                                    const char* name);

RiveRenderContext* rive_render_context_new(RiveRenderContextImpl* impl);
void rive_render_context_release(RiveRenderContext* context);
void rive_render_context_begin_frame(RiveRenderContext* context,
                                     const RiveFrameDescriptor* desc);
void rive_render_context_logical_flush(RiveRenderContext* context);
void rive_render_context_flush(RiveRenderContext* context,
                               const RiveFlushResources* resources);
void rive_render_context_release_resources(RiveRenderContext* context);

RiveRenderer* rive_renderer_new(RiveRenderContext* context);
void rive_renderer_release(RiveRenderer* renderer);
void rive_renderer_save(RiveRenderer* renderer);
void rive_renderer_restore(RiveRenderer* renderer);
void rive_renderer_transform(RiveRenderer* renderer, const RiveMat2D* matrix);
void rive_renderer_translate(RiveRenderer* renderer, float x, float y);
void rive_renderer_scale(RiveRenderer* renderer, float x, float y);
void rive_renderer_rotate(RiveRenderer* renderer, float radians);
void rive_renderer_modulate_opacity(RiveRenderer* renderer, float opacity);
void rive_renderer_draw_artboard(RiveRenderer* renderer, RiveArtboard* artboard);
void rive_renderer_align(RiveRenderer* renderer,
                         RiveFit fit,
                         RiveAlignment alignment,
                         RiveAABB frame,
                         RiveAABB content,
                         float scale_factor);

RiveRenderTarget* rive_nvn_render_target_new(uint32_t width,
                                             uint32_t height,
                                             void* color_texture,
                                             void* depth_texture,
                                             uint32_t sample_count);
void rive_render_target_release(RiveRenderTarget* target);
uint32_t rive_render_target_width(const RiveRenderTarget* target);
uint32_t rive_render_target_height(const RiveRenderTarget* target);

typedef struct RiveNVNContextDesc
{
    void* device;
    void* queue;
    uint32_t max_texture_size;
    uint8_t clip_space_bottom_up;
    uint8_t framebuffer_bottom_up;
    const RiveNVNAllocator* allocator;
    uint8_t force_non_pls_path;
} RiveNVNContextDesc;

typedef void* (*RiveNVNAllocFn)(size_t size, size_t alignment, void* user);
typedef void* (*RiveNVNReallocFn)(void* ptr, size_t new_size, void* user);
typedef void (*RiveNVNFreeFn)(void* ptr, void* user);

typedef struct RiveNVNAllocator
{
    RiveNVNAllocFn alloc;
    RiveNVNReallocFn realloc;
    RiveNVNFreeFn free;
    void* user;
} RiveNVNAllocator;

typedef struct RiveRuntimeStatus
{
    uint32_t version;
    uint32_t enabled;
    uint32_t hooks_installed;
    uint32_t device_ready;
    uint32_t queue_hooked;
    uint32_t window_hooked;
    uint32_t has_context;
    uint32_t has_renderer;
    uint32_t has_target;
    uint32_t textures_count;
    int32_t display_index;
    uint32_t allocator_set;
    const char* last_error;
    void* artboard;
    void* device;
    void* queue;
} RiveRuntimeStatus;

typedef void (*RiveRuntimeToggleCallback)(const RiveRuntimeStatus* status,
                                          uint64_t buttons);

typedef enum RiveRuntimeRenderMode
{
    RIVE_RUNTIME_RENDER_DIRECT = 0,
    RIVE_RUNTIME_RENDER_OFFSCREEN_BLIT = 1,
} RiveRuntimeRenderMode;

RiveRenderContextImpl* rive_nvn_render_context_impl_new(
    const RiveNVNContextDesc* desc);
RiveRenderContext* rive_nvn_render_context_new(
    const RiveNVNContextDesc* desc);

void rive_runtime_install_hooks(void);
void rive_runtime_set_artboard(RiveArtboard* artboard);
void rive_runtime_set_enabled(int enabled);
void rive_runtime_set_allocator(const RiveNVNAllocator* allocator);
void rive_runtime_set_render_mode(RiveRuntimeRenderMode mode);
int rive_runtime_install_main_loop_hook(uint64_t text_offset);
void rive_runtime_get_status(RiveRuntimeStatus* out_status);
const char* rive_runtime_last_error(void);
void rive_runtime_set_toggle_callback(RiveRuntimeToggleCallback callback);
int rive_runtime_set_pending_riv_data(const uint8_t* data, size_t len);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
