#include "rive/capi.h"

#include "rive/animation/linear_animation_instance.hpp"
#include "rive/animation/state_machine_instance.hpp"
#include "rive/artboard.hpp"
#include "rive/file.hpp"
#include "rive/span.hpp"
#include "utils/no_op_factory.hpp"

#include <cstring>
#include <memory>
#include <new>
#include <string>
#include <utility>

using rive::File;
using rive::ImportResult;
using rive::LinearAnimationInstance;
using rive::NoOpFactory;
using rive::StateMachineInstance;
using rive::Span;

struct RiveFile
{
    std::shared_ptr<rive::Factory> factory;
    rive::rcp<File> file;
};

struct RiveArtboard
{
    std::shared_ptr<rive::Factory> factory;
    std::shared_ptr<rive::ArtboardInstance> artboard;
};

struct RiveLinearAnimation
{
    std::shared_ptr<rive::Factory> factory;
    std::shared_ptr<rive::ArtboardInstance> artboard;
    std::unique_ptr<LinearAnimationInstance> animation;
};

struct RiveStateMachine
{
    std::shared_ptr<rive::Factory> factory;
    std::shared_ptr<rive::ArtboardInstance> artboard;
    std::unique_ptr<StateMachineInstance> machine;
};

static RiveImportResult to_c_result(ImportResult result)
{
    switch (result)
    {
        case ImportResult::success:
            return RIVE_IMPORT_SUCCESS;
        case ImportResult::unsupportedVersion:
            return RIVE_IMPORT_UNSUPPORTED_VERSION;
        case ImportResult::malformed:
        default:
            return RIVE_IMPORT_MALFORMED;
    }
}

static size_t copy_string(const std::string& value,
                          char* buffer,
                          size_t buffer_size)
{
    size_t length = value.size();
    if (!buffer || buffer_size == 0)
    {
        return length;
    }

    size_t copy_size = length;
    if (copy_size >= buffer_size)
    {
        copy_size = buffer_size - 1;
    }

    if (copy_size > 0)
    {
        std::memcpy(buffer, value.data(), copy_size);
    }
    buffer[copy_size] = '\0';
    return length;
}

RiveFile* rive_file_import(const uint8_t* data,
                           size_t data_size,
                           RiveImportResult* out_result)
{
    if (out_result)
    {
        *out_result = RIVE_IMPORT_MALFORMED;
    }
    if (!data || data_size == 0)
    {
        return nullptr;
    }

    RiveFile* wrapper = new (std::nothrow) RiveFile();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = std::shared_ptr<rive::Factory>(
        new (std::nothrow) NoOpFactory());
    if (!wrapper->factory)
    {
        delete wrapper;
        return nullptr;
    }

    ImportResult result = ImportResult::malformed;
    wrapper->file = File::import(Span<const uint8_t>(data, data_size),
                                 wrapper->factory.get(),
                                 &result,
                                 nullptr);
    if (out_result)
    {
        *out_result = to_c_result(result);
    }
    if (!wrapper->file)
    {
        delete wrapper;
        return nullptr;
    }

    return wrapper;
}

void rive_file_release(RiveFile* file)
{
    delete file;
}

size_t rive_file_artboard_count(const RiveFile* file)
{
    if (!file || !file->file)
    {
        return 0;
    }
    return file->file->artboardCount();
}

size_t rive_file_artboard_name(const RiveFile* file,
                               size_t index,
                               char* buffer,
                               size_t buffer_size)
{
    if (!file || !file->file)
    {
        return 0;
    }

    return copy_string(file->file->artboardNameAt(index),
                       buffer,
                       buffer_size);
}

RiveArtboard* rive_file_artboard_default(RiveFile* file)
{
    if (!file || !file->file)
    {
        return nullptr;
    }

    std::unique_ptr<rive::ArtboardInstance> instance =
        file->file->artboardDefault();
    if (!instance)
    {
        return nullptr;
    }

    RiveArtboard* wrapper = new (std::nothrow) RiveArtboard();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = file->factory;
    wrapper->artboard =
        std::shared_ptr<rive::ArtboardInstance>(instance.release());
    return wrapper;
}

RiveArtboard* rive_file_artboard_at(RiveFile* file, size_t index)
{
    if (!file || !file->file)
    {
        return nullptr;
    }

    std::unique_ptr<rive::ArtboardInstance> instance =
        file->file->artboardAt(index);
    if (!instance)
    {
        return nullptr;
    }

    RiveArtboard* wrapper = new (std::nothrow) RiveArtboard();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = file->factory;
    wrapper->artboard =
        std::shared_ptr<rive::ArtboardInstance>(instance.release());
    return wrapper;
}

RiveArtboard* rive_file_artboard_named(RiveFile* file, const char* name)
{
    if (!file || !file->file || !name)
    {
        return nullptr;
    }

    std::unique_ptr<rive::ArtboardInstance> instance =
        file->file->artboardNamed(name);
    if (!instance)
    {
        return nullptr;
    }

    RiveArtboard* wrapper = new (std::nothrow) RiveArtboard();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = file->factory;
    wrapper->artboard =
        std::shared_ptr<rive::ArtboardInstance>(instance.release());
    return wrapper;
}

void rive_artboard_release(RiveArtboard* artboard)
{
    delete artboard;
}

int rive_artboard_advance(RiveArtboard* artboard, float elapsed_seconds)
{
    if (!artboard || !artboard->artboard)
    {
        return 0;
    }

    return artboard->artboard->advance(elapsed_seconds) ? 1 : 0;
}

float rive_artboard_width(const RiveArtboard* artboard)
{
    if (!artboard || !artboard->artboard)
    {
        return 0.0f;
    }

    return artboard->artboard->width();
}

float rive_artboard_height(const RiveArtboard* artboard)
{
    if (!artboard || !artboard->artboard)
    {
        return 0.0f;
    }

    return artboard->artboard->height();
}

float rive_artboard_original_width(const RiveArtboard* artboard)
{
    if (!artboard || !artboard->artboard)
    {
        return 0.0f;
    }

    return artboard->artboard->originalWidth();
}

float rive_artboard_original_height(const RiveArtboard* artboard)
{
    if (!artboard || !artboard->artboard)
    {
        return 0.0f;
    }

    return artboard->artboard->originalHeight();
}

size_t rive_artboard_animation_count(const RiveArtboard* artboard)
{
    if (!artboard || !artboard->artboard)
    {
        return 0;
    }

    return artboard->artboard->animationCount();
}

size_t rive_artboard_animation_name(const RiveArtboard* artboard,
                                    size_t index,
                                    char* buffer,
                                    size_t buffer_size)
{
    if (!artboard || !artboard->artboard)
    {
        return 0;
    }

    return copy_string(artboard->artboard->animationNameAt(index),
                       buffer,
                       buffer_size);
}

RiveLinearAnimation* rive_artboard_animation_at(RiveArtboard* artboard,
                                                size_t index)
{
    if (!artboard || !artboard->artboard)
    {
        return nullptr;
    }

    std::unique_ptr<LinearAnimationInstance> instance =
        artboard->artboard->animationAt(index);
    if (!instance)
    {
        return nullptr;
    }

    RiveLinearAnimation* wrapper = new (std::nothrow) RiveLinearAnimation();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = artboard->factory;
    wrapper->artboard = artboard->artboard;
    wrapper->animation = std::move(instance);
    return wrapper;
}

RiveLinearAnimation* rive_artboard_animation_named(RiveArtboard* artboard,
                                                   const char* name)
{
    if (!artboard || !artboard->artboard || !name)
    {
        return nullptr;
    }

    std::unique_ptr<LinearAnimationInstance> instance =
        artboard->artboard->animationNamed(name);
    if (!instance)
    {
        return nullptr;
    }

    RiveLinearAnimation* wrapper = new (std::nothrow) RiveLinearAnimation();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = artboard->factory;
    wrapper->artboard = artboard->artboard;
    wrapper->animation = std::move(instance);
    return wrapper;
}

void rive_linear_animation_release(RiveLinearAnimation* animation)
{
    delete animation;
}

int rive_linear_animation_advance(RiveLinearAnimation* animation,
                                  float elapsed_seconds)
{
    if (!animation || !animation->animation)
    {
        return 0;
    }

    return animation->animation->advance(elapsed_seconds) ? 1 : 0;
}

void rive_linear_animation_apply(RiveLinearAnimation* animation, float mix)
{
    if (!animation || !animation->animation)
    {
        return;
    }

    animation->animation->apply(mix);
}

int rive_linear_animation_advance_and_apply(RiveLinearAnimation* animation,
                                            float elapsed_seconds,
                                            float mix)
{
    if (!animation || !animation->animation)
    {
        return 0;
    }

    bool keep_going = animation->animation->advance(elapsed_seconds);
    animation->animation->apply(mix);
    return keep_going ? 1 : 0;
}

float rive_linear_animation_time(const RiveLinearAnimation* animation)
{
    if (!animation || !animation->animation)
    {
        return 0.0f;
    }

    return animation->animation->time();
}

void rive_linear_animation_set_time(RiveLinearAnimation* animation, float time)
{
    if (!animation || !animation->animation)
    {
        return;
    }

    animation->animation->time(time);
}

size_t rive_artboard_state_machine_count(const RiveArtboard* artboard)
{
    if (!artboard || !artboard->artboard)
    {
        return 0;
    }

    return artboard->artboard->stateMachineCount();
}

size_t rive_artboard_state_machine_name(const RiveArtboard* artboard,
                                        size_t index,
                                        char* buffer,
                                        size_t buffer_size)
{
    if (!artboard || !artboard->artboard)
    {
        return 0;
    }

    return copy_string(artboard->artboard->stateMachineNameAt(index),
                       buffer,
                       buffer_size);
}

RiveStateMachine* rive_artboard_state_machine_at(RiveArtboard* artboard,
                                                 size_t index)
{
    if (!artboard || !artboard->artboard)
    {
        return nullptr;
    }

    std::unique_ptr<StateMachineInstance> instance =
        artboard->artboard->stateMachineAt(index);
    if (!instance)
    {
        return nullptr;
    }

    RiveStateMachine* wrapper = new (std::nothrow) RiveStateMachine();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = artboard->factory;
    wrapper->artboard = artboard->artboard;
    wrapper->machine = std::move(instance);
    return wrapper;
}

RiveStateMachine* rive_artboard_state_machine_named(RiveArtboard* artboard,
                                                    const char* name)
{
    if (!artboard || !artboard->artboard || !name)
    {
        return nullptr;
    }

    std::unique_ptr<StateMachineInstance> instance =
        artboard->artboard->stateMachineNamed(name);
    if (!instance)
    {
        return nullptr;
    }

    RiveStateMachine* wrapper = new (std::nothrow) RiveStateMachine();
    if (!wrapper)
    {
        return nullptr;
    }

    wrapper->factory = artboard->factory;
    wrapper->artboard = artboard->artboard;
    wrapper->machine = std::move(instance);
    return wrapper;
}

void rive_state_machine_release(RiveStateMachine* machine)
{
    delete machine;
}

int rive_state_machine_advance(RiveStateMachine* machine,
                               float elapsed_seconds)
{
    if (!machine || !machine->machine)
    {
        return 0;
    }

    return machine->machine->advance(elapsed_seconds) ? 1 : 0;
}

int rive_state_machine_set_bool(RiveStateMachine* machine,
                                const char* name,
                                int value)
{
    if (!machine || !machine->machine || !name)
    {
        return 0;
    }

    rive::SMIBool* input = machine->machine->getBool(name);
    if (!input)
    {
        return 0;
    }

    input->value(value != 0);
    return 1;
}

int rive_state_machine_set_number(RiveStateMachine* machine,
                                  const char* name,
                                  float value)
{
    if (!machine || !machine->machine || !name)
    {
        return 0;
    }

    rive::SMINumber* input = machine->machine->getNumber(name);
    if (!input)
    {
        return 0;
    }

    input->value(value);
    return 1;
}

int rive_state_machine_fire_trigger(RiveStateMachine* machine,
                                    const char* name)
{
    if (!machine || !machine->machine || !name)
    {
        return 0;
    }

    rive::SMITrigger* input = machine->machine->getTrigger(name);
    if (!input)
    {
        return 0;
    }

    input->fire();
    return 1;
}
