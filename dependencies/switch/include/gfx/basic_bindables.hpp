#pragma once

#include "nvn/nvn.hpp"
#include "bindable.hpp"
#include "utils.hpp"

#define MAKE_BASIC_BINDABLE(NvnTypeName) \
class NvnTypeName : public Bindable { \
private: \
    nvn:: NvnTypeName data; \
    \
public: \
    NvnTypeName() { \
        data.SetDefaults(); \
    } \
    \
    inline nvn:: NvnTypeName * operator->() { \
        return &data; \
    } \
    \
    virtual void Bind(nvn::CommandBuffer* cmdbuf) override {\
        cmdbuf->Bind ## NvnTypeName (&data); \
    } \
}; \

MAKE_BASIC_BINDABLE(BlendState);
MAKE_BASIC_BINDABLE(ChannelMaskState);
MAKE_BASIC_BINDABLE(ColorState);
MAKE_BASIC_BINDABLE(DepthStencilState);
MAKE_BASIC_BINDABLE(MultisampleState);
MAKE_BASIC_BINDABLE(PolygonState);

class VertexAttribState : public Bindable {
private:
    std::vector<nvn::VertexAttribState> data;

public:
    VertexAttribState(size_t count) : data({}) {
        data.resize(count);
        for (auto& element : data)
            element.SetDefaults();
    }

    nvn::VertexAttribState& operator[](size_t index) {
        SL_ASSERTM(index < data.size(), "VertexAttribState::operator[] failed: index is out of bounds");
        return data[index];
    }

    virtual void Bind(nvn::CommandBuffer* cmdbuf) override {
        cmdbuf->BindVertexAttribState(data.size(), data.data());
    }
};

class VertexStreamState : public Bindable {
private:
    std::vector<nvn::VertexStreamState> data;

public:
    VertexStreamState(size_t count) : data({}) {
        data.resize(count);
        for (auto& element : data)
            element.SetDefaults();
    }

    nvn::VertexStreamState& operator[](size_t index) {
        SL_ASSERTM(index < data.size(), "VertexStreamState::operator[] failed: index is out of bounds");
        return data[index];
    }

    virtual void Bind(nvn::CommandBuffer* cmdbuf) override {
        cmdbuf->BindVertexStreamState(data.size(), data.data());
    }
};