#pragma once
#include "bindable.hpp"

class Drawable {
protected:
    Drawable() = default;

public:
    ~Drawable() = default;

    Drawable(const Drawable&) = delete;
    Drawable(Drawable&&) = delete;

    Drawable& operator=(const Drawable&) = delete;
    Drawable& operator=(Drawable&&) = delete;

    virtual void Update(nvn::CommandBuffer* buffer) = 0;
    virtual void Draw(nvn::CommandBuffer* buffer) = 0;
};