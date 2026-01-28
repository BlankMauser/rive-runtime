#pragma once
#include "drawable.hpp"
#include "managed/allocator.hpp"
#include "utils.hpp"
#include <optional>

template<typename _IndexType>
class IndexBuffer : public Drawable {
    static_assert((sizeof(_IndexType) >> 1) <= 2);

public:
    IndexBuffer(nvn::Device* device, size_t max_capacity)
        : start(nullptr),
            end(nullptr),
            eos(nullptr),
            allocator(nullptr),
            buffer(nullptr),
            primitive(nvn::DrawPrimitive::TRIANGLES),
            index_type((nvn::IndexType::Enum)(sizeof(_IndexType) >> 1)),
            base_vertex(-1),
            vertex_count(-1)
    {
        size_t size_in_bytes = max_capacity * sizeof(_IndexType);
        this->allocator = new GfxAllocator(device, size_in_bytes);
        this->buffer = new nvn::Buffer;

        ptrdiff_t buffer_offset = allocator->Allocate(size_in_bytes);
        nvn::BufferBuilder builder;
        builder
            .SetDefaults()
            .SetDevice(device)
            .SetStorage(&this->allocator->GetPool(), buffer_offset, size_in_bytes);

        SL_ASSERTM(this->buffer->Initialize(&builder), "Failed to initialize index buffer");

        this->start = (_IndexType*)this->buffer->Map();
        this->end = this->start;
        this->eos = this->start + max_capacity;
    }

    ~IndexBuffer() {
        this->buffer->Finalize();

        delete buffer;
        delete allocator;
    }

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) = delete;

    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) = delete;

    bool SafePush(_IndexType index) {
        if (this->end == this->eos)
            return false;

        *this->end++ = index;
        return true;
    }

    bool SafeResize(size_t size, std::optional<_IndexType> index = {}) {
        if ((this->start + size) >= this->eos)
            return false;

        if (index) {
            for (; this->end < (this->start + size); this->end++)
                *this->end = index.value();
            return true;
        }

        this->end = this->start + size;
        return true;
    }

    void Clear() {
        SL_ASSERTM(this->SafeResize(0), "Failed to set size of IndexBuffer");
    }

    size_t Length() {
        return static_cast<size_t>(end - start);
    }

    size_t Capacity() {
        return static_cast<size_t>(eos - start);
    }

    void SetSubArray(int start, int length) {
        base_vertex = start;
        vertex_count = length;
    }

    void SetPrimitive(nvn::DrawPrimitive primitive) {
        this->primitive = primitive;
    }

    virtual void Update(nvn::CommandBuffer*) override {}

    virtual void Draw(nvn::CommandBuffer* cmdbuf) override {
        if (base_vertex > -1) {
            cmdbuf->DrawElements(primitive, index_type, (vertex_count == -1) ? Length() - base_vertex : vertex_count, buffer->GetAddress() + (base_vertex * sizeof(_IndexType)));
        } else {
            cmdbuf->DrawElements(primitive, index_type, Length(), buffer->GetAddress());
        }
    }

private:
    _IndexType* start;
    _IndexType* end;
    _IndexType* eos;

    GfxAllocator* allocator;
    nvn::Buffer* buffer;
    nvn::DrawPrimitive primitive;
    nvn::IndexType index_type;
    int base_vertex;
    int vertex_count;
};