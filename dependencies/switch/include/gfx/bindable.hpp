#pragma once
#include "nvn/nvn.hpp"
#include <vector>
#include <initializer_list>

class Bindable {
protected:
    Bindable() {}
public:
    ~Bindable() = default;

    Bindable(const Bindable&) = delete;
    Bindable(Bindable&&) = delete;

    Bindable& operator=(const Bindable&) = delete;
    Bindable& operator=(Bindable&&) = delete;

    virtual void Bind(nvn::CommandBuffer* buffer) = 0;
};