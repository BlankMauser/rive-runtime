#pragma once
#include "bindable.hpp"
#include "managed/allocator.hpp"

enum class ShaderStage {
    Vertex      = 0,
    Fragment    = 1,
    Geometry    = 2,
    TessControl = 3,
    TessEval    = 4,
    Compute     = 5
};

/**
 * @brief A class to store and manage NVN shader data with RAII.
 */
class ShaderProgram : public Bindable {
public:
    /**
     * @brief A data type to help manage the code and control sections of a shader. Supports move constructors, not copy constructors.
     */
    struct DataSet {
        std::vector<uint8_t> code;
        std::vector<uint8_t> control;

        DataSet();
        DataSet(const char* code_path, const char* control_path);
        DataSet(std::vector<uint8_t>&& code, std::vector<uint8_t>&& control);
        ~DataSet() = default;

        DataSet(const DataSet&) = delete;
        DataSet(DataSet&& other);
        DataSet& operator=(const DataSet&) = delete;
        DataSet& operator=(DataSet&& other);

        bool IsComplete() const;
    };

public:
    ShaderProgram();
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = delete;

    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&&) = delete;

    DataSet& operator[](ShaderStage stage);
    const DataSet& operator[](ShaderStage stage) const;

    bool Initialize(nvn::Device* device);
    void Finalize();

    static nvn::ShaderStageBits GetBitsForStage(ShaderStage stage);

    virtual void Bind(nvn::CommandBuffer* cmdbuf) override;

private:
    DataSet                 shaders[6];
    nvn::Program*           program;
    nvn::ShaderStageBits    program_bits;

    GfxAllocator*                   allocator;
    std::vector<nvn::Buffer*>       buffers;
    std::vector<nvn::ShaderData>    shader_data;

    void* control_memory;
};