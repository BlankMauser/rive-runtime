#pragma once

#include "rive/refcnt.hpp"

#include <memory>

namespace rive
{
class ArtboardInstance;
class Factory;
class File;
class LinearAnimationInstance;
class StateMachineInstance;
} // namespace rive

struct RiveFile
{
    std::shared_ptr<rive::Factory> factory;
    rive::rcp<rive::File> file;
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
    std::unique_ptr<rive::LinearAnimationInstance> animation;
};

struct RiveStateMachine
{
    std::shared_ptr<rive::Factory> factory;
    std::shared_ptr<rive::ArtboardInstance> artboard;
    std::unique_ptr<rive::StateMachineInstance> machine;
};
