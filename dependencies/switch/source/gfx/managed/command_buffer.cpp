#include "gfx/managed/command_buffer.hpp"
#include "gfx/managed/memory.hpp"

#include "utils.hpp"

GfxCommandBuffer::GfxCommandBuffer(nvn::Device* device, size_t command_size, size_t control_size)
    : command_memory(nullptr),
        command_block_addr(0),
        command_size(command_size),
        control_memory(nullptr),
        control_size(control_size),
        cmd_buffer(nullptr)
{
    int command_align, control_align;

    device->GetInteger(nvn::DeviceInfo::COMMAND_BUFFER_COMMAND_ALIGNMENT, &command_align);
    device->GetInteger(nvn::DeviceInfo::COMMAND_BUFFER_CONTROL_ALIGNMENT, &control_align);

    this->cmd_buffer = new nvn::CommandBuffer;

    SL_ASSERTM(
        this->cmd_buffer->Initialize(device),
        "GfxCommandBuffer::GfxCommandBuffer failed: command buffer failed to initialize"
    );

    this->command_size = SL_ALIGN(this->command_size, command_align);
    this->control_size = SL_ALIGN(this->control_size, control_align);

    this->command_memory = new GfxAllocator(device, this->command_size);
    this->command_block_addr = this->command_memory->Allocate(command_size, command_align);
    this->control_memory = GlobalAllocator::AllocAligned(control_size, control_align);

    this->Reset();
}

GfxCommandBuffer::~GfxCommandBuffer() {
    cmd_buffer->Finalize();
    delete cmd_buffer;

    GlobalAllocator::Free(control_memory);

    delete command_memory;
}

nvn::CommandBuffer* GfxCommandBuffer::Get() {
    return this->cmd_buffer;
}

const nvn::CommandBuffer* GfxCommandBuffer::Get() const {
    return this->cmd_buffer;
}

void GfxCommandBuffer::Reset() {
    cmd_buffer->AddCommandMemory(&command_memory->GetPool(), command_block_addr, command_size);
    cmd_buffer->AddControlMemory(control_memory, control_size);
}

void GfxCommandBuffer::Begin() {
    this->cmd_buffer->BeginRecording();
}

nvn::CommandHandle GfxCommandBuffer::End() {
    return this->cmd_buffer->EndRecording();
}