#pragma once
#include "bindable.hpp"
#include "managed/allocator.hpp"
#include "utils.hpp"

#include <vector>

template<typename BufferStruct>
class UniformBuffer : public Bindable {
public:
    UniformBuffer(nvn::Device* device, size_t count)
        : uniforms({}),
            allocator(nullptr),
            bind_id(0),
            bind_index(0),
            stage(nvn::ShaderStage::VERTEX)
        {
        size_t size_of_struct = sizeof(BufferStruct);
        size_of_struct = SL_ALIGN(size_of_struct, 0x100);

        size_t size_in_bytes = count * size_of_struct;

        this->allocator = new GfxAllocator(device, size_in_bytes);

        this->uniforms.resize(count);

        nvn::BufferBuilder builder;
        builder
            .SetDefaults()
            .SetDevice(device);

        for (size_t i = 0; i < count; i++) {
            ptrdiff_t buffer_offset = allocator->Allocate(size_of_struct);
            builder.SetStorage(&this->allocator->GetPool(), buffer_offset, size_of_struct);

            nvn::Buffer* buffer = new nvn::Buffer;

            SL_ASSERTM(buffer->Initialize(&builder), "UniformBuffer::UniformBuffer failed: failed to initialize buffer");

            this->uniforms[i] = buffer;
        }
    }

    ~UniformBuffer() {
        for (nvn::Buffer* buffer : this->uniforms) {
            buffer->Finalize();
            delete buffer;
        }

        delete allocator;
    }

    UniformBuffer(const UniformBuffer&) = delete;
    UniformBuffer(UniformBuffer&&) = delete;

    UniformBuffer& operator=(const UniformBuffer&) = delete;
    UniformBuffer& operator=(UniformBuffer&&) = delete;

    void Set(BufferStruct value, size_t index) {
        SL_ASSERTM(index < uniforms.size(), "UniformBuffer::Set failed: index is out of bounds");

        BufferStruct* ptr = (BufferStruct*)uniforms[index]->Map();
        *ptr = value;
        uniforms[index]->FlushMappedRange(0, SL_ALIGN(sizeof(BufferStruct), 0x100));
    }

    const BufferStruct* Get(size_t index) {
        SL_ASSERTM(index < uniforms.size(), "UniformBuffer::Get failed: index is out of bounds");
        return (BufferStruct*)uniforms[index]->Map();
    }

    constexpr void SetId(int id) { this->bind_id = id; }
    constexpr void SetStage(nvn::ShaderStage stage) { this->stage = stage; }
    void SetIndex(size_t index) { 
        SL_ASSERTM(index < uniforms.size(), "UniformBuffer::SetIndex failed: index is out of bounds");
        this->bind_index = index;
    }

    virtual void Bind(nvn::CommandBuffer* cmdbuf) override {
        cmdbuf->BindUniformBuffer(stage, bind_id, uniforms[bind_index]->GetAddress(), sizeof(BufferStruct));
    }

    void Update(nvn::CommandBuffer* cmdbuf, const BufferStruct* data) {
        cmdbuf->UpdateUniformBuffer(uniforms[bind_index]->GetAddress(), sizeof(BufferStruct), 0, sizeof(BufferStruct), data);
    }

private:
    std::vector<nvn::Buffer*> uniforms;

    GfxAllocator* allocator;

    int bind_id;
    size_t bind_index;
    nvn::ShaderStage stage;
};