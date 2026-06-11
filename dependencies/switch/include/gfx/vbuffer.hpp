#pragma once
#include "bindable.hpp"
#include "managed/allocator.hpp"
#include "utils.hpp"

#include <optional>

/**
 * @brief Manages pushing, resizing, and clearing vertices in a vertex buffer for use with graphics pipelines.
 * 
 * @tparam VertexType the type that will be used by the GPU/shaders
 */
template<typename VertexType>
class VertexBuffer : public Bindable {
public:
    /**
     * Constructs a vertex buffer with the specified type and a maximum capacity of the specified number of elements.
     * @param device The device for the current graphics context.
     * @param max_capacity The maximum number of elements this buffer can hold
     * @exception Aborts if the buffer fails to initialize
     */
    VertexBuffer(nvn::Device* device, size_t max_capacity) : allocator(nullptr), buffer(nullptr), bind_id(0) {
        size_t size_in_bytes = max_capacity * sizeof(VertexType);
        this->allocator = new GfxAllocator(device, size_in_bytes);
        this->buffer = new nvn::Buffer;

        ptrdiff_t buffer_offset = allocator->Allocate(size_in_bytes);
        nvn::BufferBuilder builder;
        builder
            .SetDefaults()
            .SetDevice(device)
            .SetStorage(&this->allocator->GetPool(), buffer_offset, size_in_bytes);

        SL_ASSERTM(this->buffer->Initialize(&builder), "Failed to initialize vertex buffer.");
        
        this->start = (VertexType*)this->buffer->Map();
        this->end = this->start;
        this->eos = this->start + max_capacity;
    }

    ~VertexBuffer() {
        this->buffer->Finalize();
        
        delete buffer;
        delete allocator;
    }

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    /**
     * Attempts to push a new vertex to the buffer
     * @param v The vertex to push
     * @return Whether or not there was enough memory to perform the push
     */
    bool SafePush(VertexType v) {
        if (this->end == this->eos)
            return false;
        *this->end++ = v;
        return true;
    }

    /**
     * Attempts to resize the vertex buffer with an optional default value
     * @param v The optional vertex to use if the buffer is being resized to a greater value
     * @return Whether or not there was enough memory to resize the buffer
     */
    bool SafeResize(size_t size, std::optional<VertexType> v = {}) {
        if ((this->start + size) >= this->eos)
            return false;
        if (v) {
            for (; this->end < (this->start + size); this->end++)
                *this->end = v.value();
            return true;
        }
        this->end = this->start + size;
        return true;
    }

    /**
     * Clears the buffer by resetting its size to zero. Effectively the same as SafeResize(0)
     * @exception Aborts if SafeResize fails
     */
    void Clear() {
        SL_ASSERTM(this->SafeResize(0), "Failed to set size of VertexBuffer to zero.");
    }

    /**
     * Sets the ID which the VertexBuffer will use to bind to the pipeline
     * @param id The ID to bind with
     */
    constexpr void SetId(int id) { this->bind_id = id; }

    size_t Length() {
        return static_cast<size_t>(end - start);
    }

    size_t Capacity() {
        return static_cast<size_t>(eos - start);
    }

    virtual void Bind(nvn::CommandBuffer* cmdbuf) override {
        cmdbuf->BindVertexBuffer(bind_id, buffer->GetAddress(), sizeof(VertexType) * static_cast<size_t>(end - start));
    }

private:
    // Basically handle this like a vector
    VertexType* start;
    VertexType* end;
    VertexType* eos;

    GfxAllocator* allocator;
    nvn::Buffer*  buffer;

    int bind_id;
};