#include "gfx/shader.hpp"
#include "gfx/managed/memory.hpp"
#include "utils.hpp"

/**
 * Constructs an empty DataSet
 */
ShaderProgram::DataSet::DataSet() : code(), control() {}

/**
 * Constructs a DataSet based off of the contents of two files.
 * @param code_path The filepath to a file containing the shader's code section.
 * @param control_path The filepath to a file containing the shader's control section.
 */
ShaderProgram::DataSet::DataSet(const char* code_path, const char* control_path) : DataSet() {
    {
        void* data = nullptr;
        int64_t size = 0;
        read_file(code_path, &data, &size);
        size_t usize = static_cast<size_t>(size);
        this->code.resize(usize);
        memcpy(this->code.data(), data, usize);
    }
    {
        void* data = nullptr;
        int64_t size = 0;
        read_file(control_path, &data, &size);
        size_t usize = static_cast<size_t>(size);
        this->control.resize(usize);
        memcpy(this->control.data(), data, usize);
    }
}

/**
 * Constructs a DataSet with two previously-initialized vectors.
 * @param code The vector containing the shader's code section.
 * @param control The vector containing the shader's control section.
 */
ShaderProgram::DataSet::DataSet(std::vector<uint8_t>&& code, std::vector<uint8_t>&& control) : code(std::move(code)), control(std::move(control)) {}

ShaderProgram::DataSet::DataSet(DataSet&& other) : code(std::move(other.code)), control(std::move(other.control)) {}

ShaderProgram::DataSet& ShaderProgram::DataSet::operator=(DataSet&& other) {
    this->code = std::move(other.code);
    this->control = std::move(other.control);
    return *this;
}

/**
 * Checks whether or not the DataSet has valid code and control sections
 */
bool ShaderProgram::DataSet::IsComplete() const {
    return code.size() > 0 && control.size() > 0;
}

ShaderProgram::ShaderProgram() : shaders({}), program(nullptr), allocator(nullptr), buffers(), shader_data(), control_memory(nullptr) {}

ShaderProgram::~ShaderProgram() {
    this->Finalize();
}

/**
 * Returns a read/write reference to the DataSet for the specified shader.
 */
ShaderProgram::DataSet& ShaderProgram::operator[](ShaderStage stage) {
    return this->shaders[static_cast<size_t>(stage)];
}

/**
 * Returns a const reference to the DataSet for the specified shader.
 */
const ShaderProgram::DataSet& ShaderProgram::operator[](ShaderStage stage) const {
    return this->shaders[static_cast<size_t>(stage)];
}

/**
 * Initializes the ShaderProgram. Different from the constructor, 
 * as the ShaderProgram needs to have shaders set.
 * @param device The device used in this graphics context.
 * @return If the ShaderProgram was initialized successfully, or true if it was already initialized.
 * @exception Abort when either vertex or fragment shaders are missing.
 */
bool ShaderProgram::Initialize(nvn::Device* device) {
    constexpr size_t SHADER_COUNT   = sizeof(shaders) / sizeof(DataSet);
    constexpr size_t MEM_ALIGN      = 0x100;
    static const nvn::MemoryPoolFlags SHADER_FLAGS = nvn::MemoryPoolFlags::CPU_UNCACHED | nvn::MemoryPoolFlags::GPU_CACHED | nvn::MemoryPoolFlags::SHADER_CODE;
    if (this->program)
        return true;

    ShaderProgram& self = *this;

    SL_ASSERTM(self[ShaderStage::Vertex].IsComplete() && self[ShaderStage::Fragment].IsComplete(), "ShaderProgram requires at least Vertex and Fragment shaders");

    size_t required_buffer_size = 1024; // GPU requires some extra memory at the end of a shader buffer
    size_t required_control_size = 0;

    // Iterate through each shader and check if it's going to be used. If it is, then we need reserve memory for both the code and control sections
    // SL_ALIGN aligns up to the nearest multiple of `align`. If `size` is 0, the result is still 0.
    for (int i = 0; i < SHADER_COUNT; i++) {
        required_buffer_size += SL_ALIGN(shaders[i].code.size(), MEM_ALIGN);
        required_control_size += SL_ALIGN(shaders[i].control.size(), MEM_ALIGN);
    }

    this->allocator = new GfxAllocator(device, required_buffer_size, SHADER_FLAGS);
    this->control_memory = GlobalAllocator::AllocAligned(required_control_size, MEM_ALIGN);

    // Reserve a whole memory pool for just our shader code.
    ptrdiff_t code_start_offset = this->allocator->Allocate(required_buffer_size, 0x100);
    void* code_memory = this->allocator->GetPool().Map() + code_start_offset;

    // Copy the control and code memory into our new allocated memory.
    for (size_t i = 0, code_offset = 0, control_offset = 0; i < SHADER_COUNT; i++) {
        memcpy(this->control_memory + control_offset, shaders[i].control.data(), shaders[i].control.size());
        memcpy(code_memory + code_offset, shaders[i].code.data(), shaders[i].code.size());
        control_offset += SL_ALIGN(shaders[i].control.size(), MEM_ALIGN);
        code_offset += SL_ALIGN(shaders[i].code.size(), MEM_ALIGN);
    }

    nvn::BufferBuilder builder;
    builder.SetDefaults().SetDevice(device);

    auto& code_pool = this->allocator->GetPool();

    program_bits = static_cast<nvn::ShaderStageBits>(0);

    // We can reuse the same buffer builder as long as we change the storage
    // In here, we have to continue the loop if our shader is not complete because
    // we are also generating the bitmask for the shader bits which we will use when
    // we bind our program to the pipeline.

    // We only need a buffer and shader data for the valid shader code
    for (size_t i = 0, code_offset = 0, control_offset = 0; i < SHADER_COUNT; i++) {
        if (!shaders[i].IsComplete())
            continue;

        program_bits |= GetBitsForStage(static_cast<ShaderStage>(i));

        buffers.push_back(new nvn::Buffer);
        shader_data.push_back(nvn::ShaderData {});

        builder.SetStorage(&code_pool, code_start_offset + static_cast<ptrdiff_t>(code_offset), shaders[i].code.size());
        buffers.back()->Initialize(&builder);

        shader_data.back().control = this->control_memory + control_offset;
        shader_data.back().data = buffers.back()->GetAddress();

        // Keep track of offsets
        code_offset += SL_ALIGN(shaders[i].code.size(), MEM_ALIGN);
        control_offset += SL_ALIGN(shaders[i].control.size(), MEM_ALIGN);
    }

    this->program = new nvn::Program;

    // Error handling isn't the best here, it would be better if I could return a rust-like result or something
    // but ultimately this will likely be fine. We can't extract useful errors from NVN anyways unless we built
    // with a debug version of nnsdk.
    return program->Initialize(device) ? program->SetShaders(buffers.size(), shader_data.data()) : false;
}

/**
 * Frees up resources consumed by ShaderProgram::Initialize. Allows ShaderProgram::Initialize to be called again afterwards.
 */
void ShaderProgram::Finalize() {
    if (!program)
        return;

    program->Finalize();
    for (auto* buf : buffers)
        delete buf;
    buffers.clear();
    shader_data.clear();
    GlobalAllocator::Free(control_memory);
    delete allocator;
    delete program;
    program = nullptr;
}

nvn::ShaderStageBits ShaderProgram::GetBitsForStage(ShaderStage stage) {
    return static_cast<nvn::ShaderStageBits>(1 << static_cast<uint32_t>(stage));
}

void ShaderProgram::Bind(nvn::CommandBuffer* cmdbuf) {
    if (!this->program)
        return;

    cmdbuf->BindProgram(program, program_bits);
}