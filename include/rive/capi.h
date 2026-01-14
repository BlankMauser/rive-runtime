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

typedef enum RiveImportResult
{
    RIVE_IMPORT_SUCCESS = 0,
    RIVE_IMPORT_UNSUPPORTED_VERSION = 1,
    RIVE_IMPORT_MALFORMED = 2,
} RiveImportResult;

RiveFile* rive_file_import(const uint8_t* data,
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif
