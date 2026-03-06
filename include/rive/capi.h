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
void rive_nvn_render_buffer_set_gpu_range(void* buffer,
                                          uint64_t gpu_address,
                                          size_t size_in_bytes);
void rive_render_target_release(RiveRenderTarget* target);
uint32_t rive_render_target_width(const RiveRenderTarget* target);
uint32_t rive_render_target_height(const RiveRenderTarget* target);

typedef struct RiveNVNContextDesc
{
    void* device;               /* nvn::Device* */
    void* queue;                /* nvn::Queue* */
    void* get_proc_address;     /* nvnDeviceGetProcAddress function pointer (optional, resolved from device if NULL) */
    uint32_t max_texture_size;
    uint8_t clip_space_bottom_up;
    uint8_t framebuffer_bottom_up;
    const RiveNVNAllocator* allocator;
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

typedef enum RiveNVNInternalBufferSlot
{
    RIVE_NVN_INTERNAL_BUFFER_FLUSH_UNIFORM = 0,
    RIVE_NVN_INTERNAL_BUFFER_IMAGE_DRAW_UNIFORM = 1,
    RIVE_NVN_INTERNAL_BUFFER_PATH = 2,
    RIVE_NVN_INTERNAL_BUFFER_PAINT = 3,
    RIVE_NVN_INTERNAL_BUFFER_PAINT_AUX = 4,
    RIVE_NVN_INTERNAL_BUFFER_CONTOUR = 5,
} RiveNVNInternalBufferSlot;

typedef enum RiveNVNShaderResourceSlot
{
    RIVE_NVN_RESOURCE_FLUSH_UNIFORM = 0,
    RIVE_NVN_RESOURCE_PATH_BASE_INSTANCE_UNIFORM = 1,
    RIVE_NVN_RESOURCE_IMAGE_DRAW_UNIFORM = 2,
    RIVE_NVN_RESOURCE_PATH = 3,
    RIVE_NVN_RESOURCE_PAINT = 4,
    RIVE_NVN_RESOURCE_PAINT_AUX = 5,
    RIVE_NVN_RESOURCE_CONTOUR = 6,
    RIVE_NVN_RESOURCE_COVERAGE = 7,
    RIVE_NVN_RESOURCE_TESS_VERTEX_TEXTURE = 8,
    RIVE_NVN_RESOURCE_GRAD_TEXTURE = 9,
    RIVE_NVN_RESOURCE_FEATHER_TEXTURE = 10,
    RIVE_NVN_RESOURCE_ATLAS_TEXTURE = 11,
    RIVE_NVN_RESOURCE_IMAGE_TEXTURE = 12,
    RIVE_NVN_RESOURCE_IMAGE_SAMPLER = 13,
    RIVE_NVN_RESOURCE_DST_COLOR_TEXTURE = 14,
} RiveNVNShaderResourceSlot;

typedef struct RiveNVNGpuCodeSection
{
    const void* control;
    uint32_t control_size;
    const void* code;
    uint32_t code_size;
} RiveNVNGpuCodeSection;

typedef struct RiveNVNGpuCodeSections
{
    RiveNVNGpuCodeSection vertex;
    RiveNVNGpuCodeSection fragment;
} RiveNVNGpuCodeSections;

/* Create the NVN render context implementation (caller owns the returned pointer). */
RiveRenderContextImpl* rive_nvn_render_context_impl_new(
    const RiveNVNContextDesc* desc);

/* Convenience: creates RenderContextImpl + wraps it in RenderContext in one call. */
RiveRenderContext* rive_nvn_render_context_new(
    const RiveNVNContextDesc* desc);
void rive_nvn_set_prefer_spirv_input(int enabled);
int rive_nvn_uses_spirv_input(void);
int rive_nvn_validate_glslc_output(const void* output_blob,
                                   size_t output_size,
                                   int require_reflection);
uint32_t rive_nvn_shader_unique_key(uint32_t draw_type,
                                    uint32_t shader_features,
                                    uint32_t interlock_mode,
                                    uint32_t shader_misc_flags);
int rive_nvn_register_program(RiveRenderContextImpl* impl,
                              uint32_t shader_key,
                              void* program,
                              int spirv_input,
                              const void* glslc_output_blob,
                              size_t glslc_output_size,
                              int require_reflection);
void rive_nvn_set_internal_buffer_gpu_range(RiveRenderContextImpl* impl,
                                            uint32_t slot,
                                            uint64_t gpu_address,
                                            size_t size_in_bytes);
int rive_nvn_set_texture_handle(RiveRenderContextImpl* impl,
                                uint32_t slot,
                                uint64_t texture_handle);
int rive_nvn_set_image_handle(RiveRenderContextImpl* impl,
                              uint32_t slot,
                              uint64_t image_handle);
int rive_nvn_glslc_compile_validate(const void* vertex_data,
                                    size_t vertex_size,
                                    const void* fragment_data,
                                    size_t fragment_size,
                                    int spirv_input,
                                    int require_reflection);
int rive_nvn_compile_and_register_program(RiveRenderContextImpl* impl,
                                          uint32_t shader_key,
                                          const void* vertex_data,
                                          size_t vertex_size,
                                          const void* fragment_data,
                                          size_t fragment_size,
                                          int spirv_input,
                                          int require_reflection);
int rive_nvn_extract_gpu_code_sections(const void* output_blob,
                                       size_t output_size,
                                       RiveNVNGpuCodeSections* out_sections);

/*
 * NVN initialization and session API.
 * Call rive_nvn_initialize once before any other rive_nvn_* function.
 * Then create one or more sessions to render artboards.
 */

/* Initialize NVN function pointer globals.  Must be called once before any
 * other rive_nvn_* function.  Safe to call multiple times (idempotent). */
void rive_nvn_initialize(void* device, void* get_proc_address);

typedef struct RiveNVNSession RiveNVNSession;

typedef struct RiveNVNSessionDesc
{
    void* device;               /* nvn::Device* */
    void* queue;                /* nvn::Queue* */
    void* get_proc_address;     /* optional if rive_nvn_initialize already called */
    const RiveNVNAllocator* allocator;  /* optional custom allocator */
    uint8_t clip_space_bottom_up;       /* 1 for NVN (GL-style) */
    uint8_t framebuffer_bottom_up;      /* depends on nvnDeviceGetWindowOriginMode */
} RiveNVNSessionDesc;

typedef struct RiveNVNFrameDesc
{
    void* color_texture;        /* nvn::Texture* — target to render into */
    void* depth_texture;        /* nvn::Texture* — optional, session creates if NULL */
    void* command_buffer;       /* nvn::CommandBuffer* — must NOT be recording */
    uint32_t width;
    uint32_t height;
    uint32_t msaa_sample_count; /* 0 or 1 = no MSAA */
    RiveLoadAction load_action;
    uint32_t clear_color;       /* ARGB when load_action == CLEAR */
    RiveFit fit;
    RiveAlignment alignment;
    float scale_factor;         /* UI scale, typically 1.0 */
    uint8_t disable_raster_ordering; /* 1: prefer atomics/msaa over raster ordering */
    uint8_t clockwise_fill_override; /* 1: force clockwise path fill */
    uint64_t frame_number;      /* monotonic frame counter for resource management */
    uint64_t safe_frame_number; /* oldest frame still in flight */
} RiveNVNFrameDesc;

/* Create a new rendering session. */
RiveNVNSession* rive_nvn_session_new(const RiveNVNSessionDesc* desc);
void rive_nvn_session_release(RiveNVNSession* session);

/* Access internals for advanced use (e.g. multi-artboard, custom transforms). */
RiveRenderContext* rive_nvn_session_context(RiveNVNSession* session);
RiveRenderer* rive_nvn_session_renderer(RiveNVNSession* session);

/* Render one artboard to the target.  Records commands into
 * desc->command_buffer.  Returns 1 on success, 0 on error. */
int rive_nvn_session_render_artboard(
    RiveNVNSession* session,
    RiveArtboard* artboard,
    const RiveNVNFrameDesc* frame);

/* Manual begin/end for multi-artboard or custom transform rendering.
 * Between begin and end, use rive_nvn_session_renderer() to draw. */
int rive_nvn_session_begin_frame(RiveNVNSession* session,
                                  const RiveNVNFrameDesc* frame);
int rive_nvn_session_end_frame(RiveNVNSession* session);

const char* rive_nvn_session_last_error(const RiveNVNSession* session);

/*
 * Optional hook-based runtime API.
 * These are only available when linking with rive_nvn_hooks and are used by
 * game plugins (e.g. skyline NRO) that intercept NVN calls to inject rive
 * rendering.  Library consumers that provide their own device/queue should
 * use the RiveNVNContextDesc API above instead.
 */
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
