// Types for NVN
#pragma once
#include <cstdint>
#include <cstddef>

#define GUARANTEE_32B(name) LARGE_##name = 0x7FFFFFF

// Shortcut for defining struct/class definitions for the NVN enum types
#define ENUM_CLASS(Class) \
    private: \
        Enum m_Internal; \
    public: \
        Class() {} \
        Class(const Class& src) : m_Internal(src.m_Internal) {} \
        Class(Enum value) : m_Internal(value) {} \
        operator Enum() const \
            { return (Enum) m_Internal; } \
        inline bool operator == (const Class& other) const \
            { return m_Internal == other.m_Internal; } \
        inline bool operator != (const Class& other) const \
            { return m_Internal != other.m_Internal; } \
        inline bool operator == (const Enum& other) const \
            { return m_Internal == other; } \
        inline bool operator != (const Enum& other) const \
            { return m_Internal != other; }

// Bitwise operators for NVN bitfields
#define BITFIELD_CLASS(Class) \
    private: \
        int32_t m_Internal; \
    public: \
        Class() {} \
        Class(const Class& src) : m_Internal(src.m_Internal) {} \
        Class(int32_t value) : m_Internal(value) {} \
        operator int32_t() const \
            { return m_Internal; } \
        inline bool operator == (const Class& other) const \
            { return m_Internal == other.m_Internal; } \
        inline bool operator != (const Class& other) const \
            { return m_Internal != other.m_Internal; } \
        inline bool operator == (const Enum& other) const \
            { return m_Internal == (int32_t)other; } \
        inline bool operator != (const Enum& other) const \
            { return m_Internal != (int32_t)other; } \
        inline Class operator | (const Class& other) \
            { return Class(m_Internal | other.m_Internal); } \
        inline Class operator & (const Class& other) const \
            { return Class(m_Internal & other.m_Internal); } \
        inline Class operator ^ (const Class& other) const \
            { return Class(m_Internal ^ other.m_Internal); } \
        inline Class& operator |= (const Class& other) \
            { m_Internal |= other.m_Internal; return *this; } \
        inline Class& operator &= (const Class& other) \
            { m_Internal &= other.m_Internal; return *this; } \
        inline Class& operator ^= (const Class& other) \
            { m_Internal ^= other.m_Internal; return *this; } \
        inline Class operator | (const Enum& other) const \
            { return Class(m_Internal | (int32_t)other); } \
        inline Class operator & (const Enum& other) const \
            { return Class(m_Internal & (int32_t)other); } \
        inline Class operator ^ (const Enum& other) const \
            { return Class(m_Internal ^ (int32_t)other); } \
        inline Class& operator |= (const Enum& other) \
            { m_Internal |= other; return *this; } \
        inline Class& operator &= (const Enum& other) \
            { m_Internal &= other; return *this; } \
        inline Class& operator ^= (const Enum& other) \
            { m_Internal ^= other; return *this; }



namespace nvn {
    typedef uint64_t BufferAddress;
    typedef uint64_t CommandHandle;
    typedef uint64_t TextureHandle;
    typedef uint64_t ImageHandle;
    typedef uint64_t TextureAddress;
    typedef void*    NativeWindow;
    typedef int32_t  StorageClass;
    typedef void*    SubroutineLinkageMapPtr;

    class DeviceBuilder;
    class Device;
    class QueueBuilder;
    class Queue;
    class CommandBuffer;
    class BlendState;
    class ChannelMaskState;
    class ColorState;
    class DepthStencilState;
    class MultisampleState;
    class PolygonState;
    class VertexAttribState;
    class VertexStreamState;
    class Program;
    class MemoryPoolBuilder;
    class MemoryPool;
    class TexturePool;
    class SamplerPool;
    class BufferBuilder;
    class Buffer;
    class Texture;
    class TextureBuilder;
    class TextureView;
    class SamplerBuilder;
    class Sampler;
    class Sync;
    class Window;
    class WindowBuilder;

    struct DeviceInfo {
        enum Enum {
            API_MAJOR_VERSION = 0,
            API_MINOR_VERSION = 1,
            UNIFORM_BUFFER_BINDINGS_PER_STAGE = 2,
            MAX_UNIFORM_BUFFER_SIZE = 3,
            UNIFORM_BUFFER_ALIGNMENT = 4,
            COLOR_BUFFER_BINDINGS = 5,
            VERTEX_BUFFER_BINDINGS = 6,
            TRANSFORM_FEEDBACK_BUFFER_BINDINGS = 7,
            SHADER_STORAGE_BUFFER_BINDINGS_PER_STAGE = 8,
            TEXTURE_BINDINGS_PER_STAGE = 9,
            COUNTER_ALIGNMENT = 10,
            TRANSFORM_FEEDBACK_BUFFER_ALIGNMENT = 11,
            TRANSFORM_FEEDBACK_CONTROL_ALIGNMENT = 12,
            INDIRECT_DRAW_ALIGNMENT = 13,
            VERTEX_ATTRIBUTES = 14,
            TEXTURE_DESCRIPTOR_SIZE = 15,
            SAMPLER_DESCRIPTOR_SIZE = 16,
            RESERVED_TEXTURE_DESCRIPTORS = 17,
            RESERVED_SAMPLER_DESCRIPTORS = 18,
            COMMAND_BUFFER_COMMAND_ALIGNMENT = 19,
            COMMAND_BUFFER_CONTROL_ALIGNMENT = 20,
            COMMAND_BUFFER_MIN_COMMAND_SIZE = 21,
            COMMAND_BUFFER_MIN_CONTROL_SIZE = 22,
            SHADER_SCRATCH_MEMORY_SCALE_FACTOR_MINIMUM = 23,
            SHADER_SCRATCH_MEMORY_SCALE_FACTOR_RECOMMENDED = 24,
            SHADER_SCRATCH_MEMORY_ALIGNMENT = 25,
            SHADER_SCRATCH_MEMORY_GRANULARITY = 26,
            MAX_TEXTURE_ANISOTROPY = 27,
            MAX_COMPUTE_WORK_GROUP_SIZE_X = 28,
            MAX_COMPUTE_WORK_GROUP_SIZE_Y = 29,
            MAX_COMPUTE_WORK_GROUP_SIZE_Z = 30,
            MAX_COMPUTE_WORK_GROUP_SIZE_THREADS = 31,
            MAX_COMPUTE_DISPATCH_WORK_GROUPS_X = 32,
            MAX_COMPUTE_DISPATCH_WORK_GROUPS_Y = 33,
            MAX_COMPUTE_DISPATCH_WORK_GROUPS_Z = 34,
            IMAGE_BINDINGS_PER_STAGE = 35,
            MAX_TEXTURE_POOL_SIZE = 36,
            MAX_SAMPLER_POOL_SIZE = 37,
            MAX_VIEWPORTS = 38,
            MEMPOOL_TEXTURE_OBJECT_PAGE_ALIGNMENT = 39,
            SUPPORTS_MIN_MAX_FILTERING = 40,
            SUPPORTS_STENCIL8_FORMAT = 41,
            SUPPORTS_ASTC_FORMATS = 42,
            L2_SIZE = 43,
            MAX_TEXTURE_LEVELS = 44,
            MAX_TEXTURE_LAYERS = 45,
            GLSLC_MAX_SUPPORTED_GPU_CODE_MAJOR_VERSION = 46,
            GLSLC_MIN_SUPPORTED_GPU_CODE_MAJOR_VERSION = 47,
            GLSLC_MAX_SUPPORTED_GPU_CODE_MINOR_VERSION = 48,
            GLSLC_MIN_SUPPORTED_GPU_CODE_MINOR_VERSION = 49,
            SUPPORTS_CONSERVATIVE_RASTER = 50,
            SUBPIXEL_BITS = 51,
            MAX_SUBPIXEL_BIAS_BITS = 52,
            INDIRECT_DISPATCH_ALIGNMENT = 53,
            ZCULL_SAVE_RESTORE_ALIGNMENT = 54,
            SHADER_SCRATCH_MEMORY_COMPUTE_SCALE_FACTOR_MINIMUM = 55,
            LINEAR_TEXTURE_STRIDE_ALIGNMENT = 56,
            LINEAR_RENDER_TARGET_STRIDE_ALIGNMENT = 57,
            MEMORY_POOL_PAGE_SIZE = 58,
            SUPPORTS_ZERO_FROM_UNMAPPED_VIRTUAL_POOL_PAGES = 59,
            UNIFORM_BUFFER_UPDATE_ALIGNMENT = 60,
            MAX_TEXTURE_SIZE = 61,
            MAX_BUFFER_TEXTURE_SIZE = 62,
            MAX_3D_TEXTURE_SIZE = 63,
            MAX_CUBE_MAP_TEXTURE_SIZE = 64,
            MAX_RECTANGLE_TEXTURE_SIZE = 65,
            SUPPORTS_PASSTHROUGH_GEOMETRY_SHADERS = 66,
            SUPPORTS_VIEWPORT_SWIZZLE = 67,
            SUPPORTS_SPARSE_TILED_PACKAGED_TEXTURES = 68,
            SUPPORTS_ADVANCED_BLEND_MODES = 69,
            MAX_PRESENT_INTERVAL = 70,
            SUPPORTS_DRAW_TEXTURE = 71,
            SUPPORTS_TARGET_INDEPENDENT_RASTERIZATION = 72,
            SUPPORTS_FRAGMENT_COVERAGE_TO_COLOR = 73,
            SUPPORTS_POST_DEPTH_COVERAGE = 74,
            SUPPORTS_IMAGES_USING_TEXTURE_HANDLES = 75,
            SUPPORTS_SAMPLE_LOCATIONS = 76,
            MAX_SAMPLE_LOCATION_TABLE_ENTRIES = 77,
            SHADER_CODE_MEMORY_POOL_PADDING_SIZE = 78,
            MAX_PATCH_SIZE = 79,
            QUEUE_COMMAND_MEMORY_GRANULARITY = 80,
            QUEUE_COMMAND_MEMORY_MIN_SIZE = 81,
            QUEUE_COMMAND_MEMORY_DEFAULT_SIZE = 82,
            QUEUE_COMPUTE_MEMORY_GRANULARITY = 83,
            QUEUE_COMPUTE_MEMORY_MIN_SIZE = 84,
            QUEUE_COMPUTE_MEMORY_DEFAULT_SIZE = 85,
            QUEUE_COMMAND_MEMORY_MIN_FLUSH_THRESHOLD = 86,
            SUPPORTS_FRAGMENT_SHADER_INTERLOCK = 87,
            MAX_TEXTURES_PER_WINDOW = 88,
            MIN_TEXTURES_PER_WINDOW = 89,
            GUARANTEE_32B(DEVICE_INFO)
        };
        ENUM_CLASS(DeviceInfo);
    };

    struct DeviceError {
        enum Enum {
            ACCESS_VIOLATION = 1,
            GUARANTEE_32B(DEVICE_ERROR)
        };
        ENUM_CLASS(DeviceError);
    };

    struct TextureTarget {
        enum Enum {
            TARGET_1D = 0,
            TARGET_2D = 1,
            TARGET_3D = 2,
            TARGET_1D_ARRAY = 3,
            TARGET_2D_ARRAY = 4,
            TARGET_2D_MULTISAMPLE = 5,
            TARGET_2D_MULTISAMPLE_ARRAY = 6,
            TARGET_RECTANGLE = 7,
            TARGET_CUBEMAP = 8,
            TARGET_CUBEMAP_ARRAY = 9,
            TARGET_BUFFER = 10,
            GUARANTEE_32B(TEXTURE_TARGET)
        };
        ENUM_CLASS(TextureTarget);
    };

    struct TextureSwizzle {
        enum Enum {
            ZERO = 0,
            ONE = 1,
            R = 2,
            G = 3,
            B = 4,
            A = 5,
            GUARANTEE_32B(TEXTURE_SWIZZLE)
        };
        ENUM_CLASS(TextureSwizzle);
    };

    struct TextureDepthStencilMode {
        enum Enum {
            DEPTH = 0x00000000,
            STENCIL = 0x00000001,
            GUARANTEE_32B(TEXTURE_DEPTH_STENCIL_MODE),
        };
        ENUM_CLASS(TextureDepthStencilMode);
    };

    struct Format {
        enum Enum {
            NONE = 0x00000000,
            R8 = 0x00000001,
            R8SN = 0x00000002,
            R8UI = 0x00000003,
            R8I = 0x00000004,
            R16F = 0x00000005,
            R16 = 0x00000006,
            R16SN = 0x00000007,
            R16UI = 0x00000008,
            R16I = 0x00000009,
            R32F = 0x0000000A,
            R32UI = 0x0000000B,
            R32I = 0x0000000C,
            RG8 = 0x0000000D,
            RG8SN = 0x0000000E,
            RG8UI = 0x0000000F,
            RG8I = 0x00000010,
            RG16F = 0x00000011,
            RG16 = 0x00000012,
            RG16SN = 0x00000013,
            RG16UI = 0x00000014,
            RG16I = 0x00000015,
            RG32F = 0x00000016,
            RG32UI = 0x00000017,
            RG32I = 0x00000018,
            RGB8 = 0x00000019,
            RGB8SN = 0x0000001A,
            RGB8UI = 0x0000001B,
            RGB8I = 0x0000001C,
            RGB16F = 0x0000001D,
            RGB16 = 0x0000001E,
            RGB16SN = 0x0000001F,
            RGB16UI = 0x00000020,
            RGB16I = 0x00000021,
            RGB32F = 0x00000022,
            RGB32UI = 0x00000023,
            RGB32I = 0x00000024,
            RGBA8 = 0x00000025,
            RGBA8SN = 0x00000026,
            RGBA8UI = 0x00000027,
            RGBA8I = 0x00000028,
            RGBA16F = 0x00000029,
            RGBA16 = 0x0000002A,
            RGBA16SN = 0x0000002B,
            RGBA16UI = 0x0000002C,
            RGBA16I = 0x0000002D,
            RGBA32F = 0x0000002E,
            RGBA32UI = 0x0000002F,
            RGBA32I = 0x00000030,
            STENCIL8 = 0x00000031,
            DEPTH16 = 0x00000032,
            DEPTH24 = 0x00000033,
            DEPTH32F = 0x00000034,
            DEPTH24_STENCIL8 = 0x00000035,
            DEPTH32F_STENCIL8 = 0x00000036,
            RGBX8_SRGB = 0x00000037,
            RGBA8_SRGB = 0x00000038,
            RGBA4 = 0x00000039,
            RGB5 = 0x0000003A,
            RGB5A1 = 0x0000003B,
            RGB565 = 0x0000003C,
            RGB10A2 = 0x0000003D,
            RGB10A2UI = 0x0000003E,
            R11G11B10F = 0x0000003F,
            RGB9E5F = 0x00000040,
            RGB_DXT1 = 0x00000041,
            RGBA_DXT1 = 0x00000042,
            RGBA_DXT3 = 0x00000043,
            RGBA_DXT5 = 0x00000044,
            RGB_DXT1_SRGB = 0x00000045,
            RGBA_DXT1_SRGB = 0x00000046,
            RGBA_DXT3_SRGB = 0x00000047,
            RGBA_DXT5_SRGB = 0x00000048,
            RGTC1_UNORM = 0x00000049,
            RGTC1_SNORM = 0x0000004A,
            RGTC2_UNORM = 0x0000004B,
            RGTC2_SNORM = 0x0000004C,
            BPTC_UNORM = 0x0000004D,
            BPTC_UNORM_SRGB = 0x0000004E,
            BPTC_SFLOAT = 0x0000004F,
            BPTC_UFLOAT = 0x00000050,
            R8_UI2F = 0x00000051,
            R8_I2F = 0x00000052,
            R16_UI2F = 0x00000053,
            R16_I2F = 0x00000054,
            R32_UI2F = 0x00000055,
            R32_I2F = 0x00000056,
            RG8_UI2F = 0x00000057,
            RG8_I2F = 0x00000058,
            RG16_UI2F = 0x00000059,
            RG16_I2F = 0x0000005A,
            RG32_UI2F = 0x0000005B,
            RG32_I2F = 0x0000005C,
            RGB8_UI2F = 0x0000005D,
            RGB8_I2F = 0x0000005E,
            RGB16_UI2F = 0x0000005F,
            RGB16_I2F = 0x00000060,
            RGB32_UI2F = 0x00000061,
            RGB32_I2F = 0x00000062,
            RGBA8_UI2F = 0x00000063,
            RGBA8_I2F = 0x00000064,
            RGBA16_UI2F = 0x00000065,
            RGBA16_I2F = 0x00000066,
            RGBA32_UI2F = 0x00000067,
            RGBA32_I2F = 0x00000068,
            RGB10A2SN = 0x00000069,
            RGB10A2I = 0x0000006A,
            RGB10A2_UI2F = 0x0000006B,
            RGB10A2_I2F = 0x0000006C,
            RGBX8 = 0x0000006D,
            RGBX8SN = 0x0000006E,
            RGBX8UI = 0x0000006F,
            RGBX8I = 0x00000070,
            RGBX16F = 0x00000071,
            RGBX16 = 0x00000072,
            RGBX16SN = 0x00000073,
            RGBX16UI = 0x00000074,
            RGBX16I = 0x00000075,
            RGBX32F = 0x00000076,
            RGBX32UI = 0x00000077,
            RGBX32I = 0x00000078,
            RGBA_ASTC_4x4 = 0x00000079,
            RGBA_ASTC_5x4 = 0x0000007A,
            RGBA_ASTC_5x5 = 0x0000007B,
            RGBA_ASTC_6x5 = 0x0000007C,
            RGBA_ASTC_6x6 = 0x0000007D,
            RGBA_ASTC_8x5 = 0x0000007E,
            RGBA_ASTC_8x6 = 0x0000007F,
            RGBA_ASTC_8x8 = 0x00000080,
            RGBA_ASTC_10x5 = 0x00000081,
            RGBA_ASTC_10x6 = 0x00000082,
            RGBA_ASTC_10x8 = 0x00000083,
            RGBA_ASTC_10x10 = 0x00000084,
            RGBA_ASTC_12x10 = 0x00000085,
            RGBA_ASTC_12x12 = 0x00000086,
            RGBA_ASTC_4x4_SRGB = 0x00000087,
            RGBA_ASTC_5x4_SRGB = 0x00000088,
            RGBA_ASTC_5x5_SRGB = 0x00000089,
            RGBA_ASTC_6x5_SRGB = 0x0000008A,
            RGBA_ASTC_6x6_SRGB = 0x0000008B,
            RGBA_ASTC_8x5_SRGB = 0x0000008C,
            RGBA_ASTC_8x6_SRGB = 0x0000008D,
            RGBA_ASTC_8x8_SRGB = 0x0000008E,
            RGBA_ASTC_10x5_SRGB = 0x0000008F,
            RGBA_ASTC_10x6_SRGB = 0x00000090,
            RGBA_ASTC_10x8_SRGB = 0x00000091,
            RGBA_ASTC_10x10_SRGB = 0x00000092,
            RGBA_ASTC_12x10_SRGB = 0x00000093,
            RGBA_ASTC_12x12_SRGB = 0x00000094,
            BGR565 = 0x00000095,
            BGR5 = 0x00000096,
            BGR5A1 = 0x00000097,
            A1BGR5 = 0x00000098,
            BGRX8 = 0x00000099,
            BGRA8 = 0x0000009A,
            BGRX8_SRGB = 0x0000009B,
            BGRA8_SRGB = 0x0000009C,
            GUARANTEE_32B(FORMAT),
        };
        ENUM_CLASS(Format);
    };

    struct BlendFunc {
        enum Enum {
            ZERO = 0x00000001,
            ONE = 0x00000002,
            SRC_COLOR = 0x00000003,
            ONE_MINUS_SRC_COLOR = 0x00000004,
            SRC_ALPHA = 0x00000005,
            ONE_MINUS_SRC_ALPHA = 0x00000006,
            DST_ALPHA = 0x00000007,
            ONE_MINUS_DST_ALPHA = 0x00000008,
            DST_COLOR = 0x00000009,
            ONE_MINUS_DST_COLOR = 0x0000000A,
            SRC_ALPHA_SATURATE = 0x0000000B,
            SRC1_COLOR = 0x00000010,
            ONE_MINUS_SRC1_COLOR = 0x00000011,
            SRC1_ALPHA = 0x00000012,
            ONE_MINUS_SRC1_ALPHA = 0x00000013,
            CONSTANT_COLOR = 0x00000061,
            ONE_MINUS_CONSTANT_COLOR = 0x00000062,
            CONSTANT_ALPHA = 0x00000063,
            ONE_MINUS_CONSTANT_ALPHA = 0x00000064,
            GUARANTEE_32B(BLEND_FUNC),
        };
        ENUM_CLASS(BlendFunc);
    };

    struct BlendAdvancedMode {
        enum Enum {
            BLEND_NONE = 0x00000000,
            BLEND_ZERO = 0x00000005,
            BLEND_SRC = 0x00000006,
            BLEND_DST = 0x00000007,
            BLEND_SRC_OVER = 0x00000008,
            BLEND_DST_OVER = 0x00000009,
            BLEND_SRC_IN = 0x0000000A,
            BLEND_DST_IN = 0x0000000B,
            BLEND_SRC_OUT = 0x0000000C,
            BLEND_DST_OUT = 0x0000000D,
            BLEND_SRC_ATOP = 0x0000000E,
            BLEND_DST_ATOP = 0x0000000F,
            BLEND_XOR = 0x00000010,
            BLEND_PLUS = 0x00000011,
            BLEND_PLUS_CLAMPED = 0x00000012,
            BLEND_PLUS_CLAMPED_ALPHA = 0x00000013,
            BLEND_PLUS_DARKER = 0x00000014,
            BLEND_MULTIPLY = 0x00000015,
            BLEND_SCREEN = 0x00000016,
            BLEND_OVERLAY = 0x00000017,
            BLEND_DARKEN = 0x00000018,
            BLEND_LIGHTEN = 0x00000019,
            BLEND_COLORDODGE = 0x0000001A,
            BLEND_COLORBURN = 0x0000001B,
            BLEND_HARDLIGHT = 0x0000001C,
            BLEND_SOFTLIGHT = 0x0000001D,
            BLEND_DIFFERENCE = 0x0000001E,
            BLEND_MINUS = 0x00000001F,
            BLEND_MINUS_CLAMPED = 0x00000020,
            BLEND_EXCLUSION = 0x00000021,
            BLEND_CONTRAST = 0x00000022,
            BLEND_INVERT = 0x00000023,
            BLEND_INVERT_RGB = 0x00000024,
            BLEND_INVERT_OVG = 0x00000025,
            BLEND_LINEARDODGE = 0x00000026,
            BLEND_LINEARBURN = 0x00000027,
            BLEND_VIVIDLIGHT = 0x00000028,
            BLEND_LINEARLIGHT = 0x00000029,
            BLEND_PINLIGHT = 0x0000002A,
            BLEND_HARDMIX = 0x0000002B,
            BLEND_RED = 0x0000002C,
            BLEND_GREEN = 0x0000002D,
            BLEND_BLUE = 0x0000002E,
            BLEND_HSL_HUE = 0x0000002F,
            BLEND_HSL_SATURATION = 0x00000030,
            BLEND_HSL_COLOR = 0x00000031,
            BLEND_HSL_LUMINOSITY = 0x00000032,
            GUARANTEE_32B(BLEND_ADVANCED_MODE),
        };
        ENUM_CLASS(BlendAdvancedMode);
    };

    struct BlendAdvancedOverlap {
        enum Enum {
            UNCORRELATED = 0x00000000,
            DISJOINT = 0x00000001,
            CONJOINT = 0x00000002,
            GUARANTEE_32B(BLEND_ADVANCED_OVERLAP),
        };
        ENUM_CLASS(BlendAdvancedOverlap);
    };

    struct BlendEquation {
        enum Enum {
            ADD = 0x00000001,
            SUB = 0x00000002,
            REVERSE_SUB = 0x00000003,
            MIN = 0x00000004,
            MAX = 0x00000005,
            GUARANTEE_32B(BLEND_EQUATION),
        };
        ENUM_CLASS(BlendEquation);
    };

    struct LogicOp {
        enum Enum {
            CLEAR = 0x00000000,
            AND = 0x00000001,
            AND_REVERSE = 0x00000002,
            COPY = 0x00000003,
            AND_INVERTED = 0x00000004,
            NOOP = 0x00000005,
            XOR = 0x00000006,
            OR = 0x00000007,
            NOR = 0x00000008,
            EQUIV = 0x00000009,
            INVERT = 0x0000000A,
            OR_REVERSE = 0x0000000B,
            COPY_INVERTED = 0x0000000C,
            OR_INVERTED = 0x0000000D,
            NAND = 0x0000000E,
            SET = 0x0000000F,
            GUARANTEE_32B(LOGIC_OP),
        };
        ENUM_CLASS(LogicOp);
    };

    struct AlphaFunc {
        enum Enum {
            NEVER = 0x00000001,
            LESS = 0x00000002,
            EQUAL = 0x00000003,
            LEQUAL = 0x00000004,
            GREATER = 0x00000005,
            NOTEQUAL = 0x00000006,
            GEQUAL = 0x00000007,
            ALWAYS = 0x00000008,
            GUARANTEE_32B(ALPHA_FUNC),
        };
        ENUM_CLASS(AlphaFunc);
    };

    struct DrawPrimitive {
        enum Enum {
            POINTS = 0x00000000,
            LINES = 0x00000001,
            LINE_LOOP = 0x00000002,
            LINE_STRIP = 0x00000003,
            TRIANGLES = 0x00000004,
            TRIANGLE_STRIP = 0x00000005,
            TRIANGLE_FAN = 0x00000006,
            QUADS = 0x00000007,
            QUAD_STRIP = 0x00000008,
            POLYGON = 0x00000009,
            LINES_ADJACENCY = 0x0000000A,
            LINE_STRIP_ADJACENCY = 0x0000000B,
            TRIANGLES_ADJACENCY = 0x0000000C,
            TRIANGLE_STRIP_ADJACENCY = 0x0000000D,
            PATCHES = 0x0000000E,
            GUARANTEE_32B(DRAW_PRIMITIVE),
        };
        ENUM_CLASS(DrawPrimitive);
    };

    struct IndexType {
        enum Enum {
            UNSIGNED_BYTE = 0x00000000,
            UNSIGNED_SHORT = 0x00000001,
            UNSIGNED_INT = 0x00000002,
            GUARANTEE_32B(INDEX_TYPE),
        };
        ENUM_CLASS(IndexType);
    };

    struct DepthFunc {
        enum Enum {
            NEVER = 0x00000001,
            LESS = 0x00000002,
            EQUAL = 0x00000003,
            LEQUAL = 0x00000004,
            GREATER = 0x00000005,
            NOTEQUAL = 0x00000006,
            GEQUAL = 0x00000007,
            ALWAYS = 0x00000008,
            GUARANTEE_32B(DEPTH_FUNC),
        };
        ENUM_CLASS(DepthFunc);
    };

    struct MagFilter {
        enum Enum {
            NEAREST = 0x00000000,
            LINEAR = 0x00000001,
            GUARANTEE_32B(MAG_FILTER),
        };
        ENUM_CLASS(MagFilter);
    };

    struct MinFilter {
        enum Enum {
            NEAREST = 0x00000000,
            LINEAR = 0x00000001,
            NEAREST_MIPMAP_NEAREST = 0x00000002,
            LINEAR_MIPMAP_NEAREST = 0x00000003,
            NEAREST_MIPMAP_LINEAR = 0x00000004,
            LINEAR_MIPMAP_LINEAR = 0x00000005,
            GUARANTEE_32B(MIN_FILTER),
        };
        ENUM_CLASS(MinFilter);
    };

    struct WrapMode {
        enum Enum {
            CLAMP = 0x00000000,
            REPEAT = 0x00000001,
            MIRROR_CLAMP = 0x00000002,
            MIRROR_CLAMP_TO_EDGE = 0x00000003,
            MIRROR_CLAMP_TO_BORDER = 0x00000004,
            CLAMP_TO_BORDER = 0x00000005,
            MIRRORED_REPEAT = 0x00000006,
            CLAMP_TO_EDGE = 0x00000007,
            GUARANTEE_32B(WRAP_MODE),
        };
        ENUM_CLASS(WrapMode);
    };

    struct CompareMode {
        enum Enum {
            NONE = 0x00000000,
            COMPARE_R_TO_TEXTURE = 0x00000001,
            GUARANTEE_32B(COMPARE_MODE),
        };
        ENUM_CLASS(CompareMode);
    };

    struct CompareFunc {
        enum Enum {
            NEVER = 0x00000001,
            LESS = 0x00000002,
            EQUAL = 0x00000003,
            LEQUAL = 0x00000004,
            GREATER = 0x00000005,
            NOTEQUAL = 0x00000006,
            GEQUAL = 0x00000007,
            ALWAYS = 0x00000008,
            GUARANTEE_32B(COMPARE_FUNC),
        };
        ENUM_CLASS(CompareFunc);
    };

    struct SamplerReduction {
        enum Enum {
            AVERAGE = 0x00000000,
            MIN = 0x00000001,
            MAX = 0x00000002,
            GUARANTEE_32B(SAMPLER_REDUCTION),
        };
        ENUM_CLASS(SamplerReduction);
    };

    struct Face {
        enum Enum {
            NONE = 0x00000000,
            FRONT = 0x00000001,
            BACK = 0x00000002,
            FRONT_AND_BACK = 0x00000003,
            GUARANTEE_32B(FACE),
        };
        ENUM_CLASS(Face);
    };

    struct StencilFunc {
        enum Enum {
            NEVER = 0x00000001,
            LESS = 0x00000002,
            EQUAL = 0x00000003,
            LEQUAL = 0x00000004,
            GREATER = 0x00000005,
            NOTEQUAL = 0x00000006,
            GEQUAL = 0x00000007,
            ALWAYS = 0x00000008,
            GUARANTEE_32B(STENCIL_FUNC),
        };
        ENUM_CLASS(StencilFunc);
    };

    struct StencilOp {
        enum Enum {
            KEEP = 0x00000001,
            ZERO = 0x00000002,
            REPLACE = 0x00000003,
            INCR = 0x00000004,
            DECR = 0x00000005,
            INVERT = 0x00000006,
            INCR_WRAP = 0x00000007,
            DECR_WRAP = 0x00000008,
            GUARANTEE_32B(STENCIL_OP),
        };
        ENUM_CLASS(StencilOp);
    };

    struct FrontFace {
        enum Enum {
            CW = 0x00000000,
            CCW = 0x00000001,
            GUARANTEE_32B(FRONT_FACE),
        };
        ENUM_CLASS(FrontFace);
    };

    struct PolygonMode {
        enum Enum {
            POINT = 0x00000000,
            LINE = 0x00000001,
            FILL = 0x00000002,
            GUARANTEE_32B(POLYGON_MODE),
        };
        ENUM_CLASS(PolygonMode);
    };

    struct PolygonOffsetEnable {
        enum Enum {
            NONE = 0x00000000,
            POINT = 0x00000001,
            LINE = 0x00000002,
            FILL = 0x00000004,
            GUARANTEE_32B(POLYGON_OFFSET_ENABLE),
        };
        BITFIELD_CLASS(PolygonOffsetEnable);
    };

    struct SyncCondition {
        enum Enum {
            ALL_GPU_COMMANDS_COMPLETE = 0x00000000,
            GRAPHICS_WORLD_SPACE_COMPLETE = 0x00000001,
            GUARANTEE_32B(SYNC_CONDITION),
        };
        ENUM_CLASS(SyncCondition);
    };

    struct SyncWaitResult {
        enum Enum {
            ALREADY_SIGNALED = 0x00000000,
            CONDITION_SATISFIED = 0x00000001,
            TIMEOUT_EXPIRED = 0x00000002,
            FAILED = 0x00000003,
            GUARANTEE_32B(SYNC_WAIT_RESULT),
        };
        ENUM_CLASS(SyncWaitResult);
    };

    struct DeviceWaitForErrorResult {
        enum Enum {
            TIMEOUT_EXPIRED = 0x00000000,
            GPU_ERROR = 0x00000001,
            DEVICE_FINALIZED = 0x00000002,
            GUARANTEE_32B(DEVICE_WAIT_FOR_ERROR_RESULT),
        };
        ENUM_CLASS(DeviceWaitForErrorResult);
    };

    struct QueueAcquireTextureResult {
        enum Enum {
            SUCCESS = 0x00000000,
            NATIVE_ERROR = 0x00000001,
            GUARANTEE_32B(QUEUE_ACQUIRE_TEXTURE_RESULT),
        };
        ENUM_CLASS(QueueAcquireTextureResult);
    };

    struct WindowAcquireTextureResult {
        enum Enum {
            SUCCESS = 0x00000000,
            NATIVE_ERROR = 0x00000001,
            GUARANTEE_32B(WINDOW_ACQUIRE_TEXTURE_RESULT),
        };
        ENUM_CLASS(WindowAcquireTextureResult);
    };

    struct ShaderStage {
        enum Enum {
            VERTEX = 0x00000000,
            FRAGMENT = 0x00000001,
            GEOMETRY = 0x00000002,
            TESS_CONTROL = 0x00000003,
            TESS_EVALUATION = 0x00000004,
            COMPUTE = 0x00000005,
            GUARANTEE_32B(SHADER_STAGE),
        };
        ENUM_CLASS(ShaderStage);
    };

    struct TiledCacheAction {
        enum Enum {
            ENABLE = 1,
            DISABLE = 2,
            FLUSH = 3,
            FLUSH_NO_TILING = 4,
            ENABLE_RENDER_TARGET_BINNING = 5,
            DISABLE_RENDER_TARGET_BINNING = 6,
            GUARANTEE_32B(TILED_CACHE_ACTION),
        };
        ENUM_CLASS(TiledCacheAction);
    };

    struct ShaderStageBits {
        enum Enum {
            VERTEX = 0x00000001,
            FRAGMENT = 0x00000002,
            GEOMETRY = 0x00000004,
            TESS_CONTROL = 0x00000008,
            TESS_EVALUATION = 0x00000010,
            COMPUTE = 0x00000020,
            ALL_GRAPHICS_BITS = 0x0000001F,
            GUARANTEE_32B(SHADER_STAGE_BITS),
        };
        BITFIELD_CLASS(ShaderStageBits);
    };

    struct SyncFlagBits {
        enum Enum {
            FLUSH_FOR_CPU = 0x00000001,
            GUARANTEE_32B(SYNC_FLAG_BITS),
        };
        BITFIELD_CLASS(SyncFlagBits);
    };

    struct DeviceFlagBits {
        enum Enum {
            DEBUG_ENABLE = 0x00000001,
            DEBUG_SKIP_CALLS_ON_ERROR = 0x00000002,
            DEBUG_DRAW_VALIDATION = 0x00000004,
            DEFERRED_FINALIZE = 0x00000008,
            DEBUG_DRAW_VALIDATION_HEAVY = 0x00000010,
            DEBUG_ENABLE_LEVEL_0 = 0x00000020,
            DEBUG_ENABLE_LEVEL_1 = 0x00000040,
            DEBUG_ENABLE_LEVEL_2 = 0x00000001,
            DEBUG_ENABLE_LEVEL_3 = 0x00000004,
            DEBUG_ENABLE_LEVEL_4 = 0x00000010,
            GUARANTEE_32B(DEVICE_FLAG_BITS),
        };
        BITFIELD_CLASS(DeviceFlagBits);
    };

    struct ClearColorMask {
        enum Enum {
            R = 0x00000001,
            G = 0x00000002,
            B = 0x00000004,
            A = 0x00000008,
            RGBA = 0x0000000F,
            GUARANTEE_32B(CLEAR_COLOR_MASK),
        };
        BITFIELD_CLASS(ClearColorMask);
    };

    struct DebugCallbackSource {
        enum Enum {
            API = 0x00000000,
            GUARANTEE_32B(DEBUG_CALLBACK_SOURCE),
        };
        ENUM_CLASS(DebugCallbackSource);
    };

    struct DebugCallbackType {
        enum Enum {
            API_ERROR = 0x00000000,
            API_WARNING = 0x00000001,
            GUARANTEE_32B(DEBUG_CALLBACK_TYPE),
        };
        ENUM_CLASS(DebugCallbackType);
    };

    struct DebugCallbackSeverity {
        enum Enum {
            HIGH = 0x00000000,
            MEDIUM = 0x00000001,
            LOW = 0x00000002,
            NOTIFICATION = 0x00000003,
            GUARANTEE_32B(DEBUG_CALLBACK_SEVERITY),
        };
        ENUM_CLASS(DebugCallbackSeverity);
    };

    struct MemoryPoolFlags {
        enum Enum {
            CPU_NO_ACCESS = 0x00000001,
            CPU_UNCACHED = 0x00000002,
            CPU_CACHED = 0x00000004,
            GPU_NO_ACCESS = 0x00000008,
            GPU_UNCACHED = 0x00000010,
            GPU_CACHED = 0x00000020,
            SHADER_CODE = 0x00000040,
            COMPRESSIBLE = 0x00000080,
            PHYSICAL = 0x00000100,
            VIRTUAL = 0x000000200,
            GUARANTEE_32B(MEMORY_POOL_FLAGS),
        };
        BITFIELD_CLASS(MemoryPoolFlags);
    };

    struct CounterType {
        enum Enum {
            TIMESTAMP = 0x00000000,
            SAMPLES_PASSED = 0x00000001,
            INPUT_VERTICES = 0x00000002,
            INPUT_PRIMITIVES = 0x00000003,
            VERTEX_SHADER_INVOCATIONS = 0x00000004,
            TESS_CONTROL_SHADER_INVOCATIONS = 0x00000005,
            TESS_EVALUATION_SHADER_INVOCATIONS = 0x00000006,
            GEOMETRY_SHADER_INVOCATIONS = 0x00000007,
            FRAGMENT_SHADER_INVOCATIONS = 0x00000008,
            TESS_EVALUATION_SHADER_PRIMITIVES = 0x00000009,
            GEOMETRY_SHADER_PRIMITIVES = 0x0000000A,
            CLIPPER_INPUT_PRIMITIVES = 0x0000000B,
            CLIPPER_OUTPUT_PRIMITIVES = 0x0000000C,
            PRIMITIVES_GENERATED = 0x0000000D,
            TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x0000000E,
            ZCULL_STATS = 0x0000000F,
            TIMESTAMP_TOP = 0x00000010,
            GUARANTEE_32B(COUNTER_TYPE),
        };
        ENUM_CLASS(CounterType);
    };

    struct CommandBufferMemoryEvent {
        enum Enum {
            OUT_OF_COMMAND_MEMORY = 0x00000000,
            OUT_OF_CONTROL_MEMORY = 0x00000001,
            GUARANTEE_32B(COMMAND_BUFFER_MEMORY_EVENT),
        };
        ENUM_CLASS(CommandBufferMemoryEvent);
    };

    struct ConditionalRenderMode {
        enum Enum {
            RENDER_IF_EQUAL = 0,
            RENDER_IF_NOT_EQUAL = 1,
            GUARANTEE_32B(CONDITIONAL_RENDER_MODE),
        };
        ENUM_CLASS(ConditionalRenderMode);
    };

    struct WindowOriginMode {
        enum Enum {
            LOWER_LEFT = 0,
            UPPER_LEFT = 1,
            GUARANTEE_32B(WINDOW_ORIGIN_MODE),
        };
        ENUM_CLASS(WindowOriginMode);
    };

    struct DepthMode {
        enum Enum {
            NEAR_IS_MINUS_W = 0,
            NEAR_IS_ZERO = 1,
            GUARANTEE_32B(DEPTH_MODE),
        };
        ENUM_CLASS(DepthMode);
    };

    struct TextureFlags {
        enum Enum {
            DISPLAY = 0x00000001,
            VIDEO_DECODE = 0x00000002,
            IMAGE = 0x00000004,
            COMPRESSIBLE = 0x00000008,
            LINEAR = 0x00000010,
            SPARSE = 0x00000020,
            LINEAR_RENDER_TARGET = 0x00000040,
            ADAPTIVE_ZCULL = 0x00000080,
            DEPTH16_PREFER_FAST_CLEAR = 0x00000100,
            GUARANTEE_32B(TEXTURE_FLAGS),
        };
        BITFIELD_CLASS(TextureFlags);
    };

    struct BarrierBits {
        enum Enum {
            ORDER_PRIMITIVES = 0x00000001,
            ORDER_FRAGMENTS = 0x00000002,
            ORDER_FRAGMENTS_TILED = 0x00000004,
            ORDER_INDIRECT_DATA = 0x00000008,
            INVALIDATE_TEXTURE = 0x00000010,
            INVALIDATE_SHADER = 0x00000020,
            INVALIDATE_TEXTURE_DESCRIPTOR = 0x00000040,
            INVALIDATE_ZCULL = 0x00000080,
            GUARANTEE_32B(BARRIER_BITS),
        };
        BITFIELD_CLASS(BarrierBits);
    };

    struct CopyFlags {
        enum Enum {
            LINEAR_FILTER = 0x00000001,
            NONE = 0x00000000,
            GUARANTEE_32B(COPY_FLAGS),
        };
        BITFIELD_CLASS(CopyFlags);
    };

    struct ViewportSwizzle {
        enum Enum {
            POSITIVE_X = 0,
            NEGATIVE_X = 1,
            POSITIVE_Y = 2,
            NEGATIVE_Y = 3,
            POSITIVE_Z = 4,
            NEGATIVE_Z = 5,
            POSITIVE_W = 6,
            NEGATIVE_W = 7,
            GUARANTEE_32B(VIEWPORT_SWIZZLE),
        };
        ENUM_CLASS(ViewportSwizzle);
    };

    struct CoverageModulationMode {
        enum Enum {
            NONE = 0x00000000,
            RGB = 0x00000001,
            ALPHA = 0x00000002,
            RGBA = 0x00000003,
            GUARANTEE_32B(COVERAGE_MODULATION_MODE),
        };
        ENUM_CLASS(CoverageModulationMode);
    };

    struct QueueFlags {
        enum Enum {
            NO_FRAGMENT_INTERLOCK = 0x00000001,
            NONE = 0x00000000,
            GUARANTEE_32B(QUEUE_FLAGS),
        };
        BITFIELD_CLASS(QueueFlags);
    };

    struct ShaderData {
        BufferAddress data;
        const void* control;
    };

    struct QueueGetErrorResult {
        enum Enum {
            NO_ERROR = 0x00000000,
            GPU_ERROR_UNKNOWN = 0x00000001,
            GPU_ERROR_MMU_FAULT = 0x00000002,
            GPU_ERROR_PBDMA_EXCEPTION = 0x00000003,
            GPU_ERROR_ENGINE_EXCEPTION = 0x00000004,
            GPU_ERROR_TIMEOUT = 0x00000005,
            GUARANTEE_32B(QUEUE_GET_ERROR_RESULT),
        };
        ENUM_CLASS(QueueGetErrorResult);
    };

    struct MemoryAccess {
        enum Enum {
            MEMORY_ACCESS_READ = 0x00000000,
            MEMORY_ACCESS_WRITE = 0x00000001,
            GUARANTEE_32B(MEMORY_ACCESS),
        };
        ENUM_CLASS(MemoryAccess);
    };

    union QueueErrorInfo {
        struct {
            uint64_t faultAddress;
            MemoryAccess::Enum accessType;
        } mmuFault;
        uint8_t unknown[64];
    };

    struct DrawArraysIndirectData {
        int count;
        int instanceCount;
        int first;
        int baseInstance;
    };

    struct DrawElementsIndirectData {
        int count;
        int instanceCount;
        int firstIndex;
        int baseVertex;
        int baseInstance;
    };

    struct DispatchComputeIndirectData {
        int groupsX;
        int groupsY;
        int groupsZ;
    };

    struct CounterData {
        uint64_t counter;
        uint64_t timestamp;
    };

    struct DeviceErrorData {
        DeviceError::Enum error;
        Queue* queue;
        uint8_t unknown[64];
    };

    struct Rectangle {
        int x;
        int y;
        int width;
        int height;
    };

    struct MappingRequest {
        MemoryPool* physicalPool;
        int64_t physicalOffset;
        int64_t virtualOffset;
        uint64_t size;
        StorageClass storageClass;
    };

    struct CopyRegion {
        int xoffset;
        int yoffset;
        int zoffset;
        int width;
        int height;
        int depth;
    };

    struct TextureSparseTileLayout {
        int numTiledLevels;
        int tileWidth;
        int tileHeight;
        int tileDepth;
        uint8_t unknown[16];
    };

    struct PackagedTextureLayout {
        char layout[8];
    };

    struct BufferRange {
        BufferAddress address;
        uint64_t size;
    };

    struct DrawTextureRegion {
        float x0;
        float y0;
        float x1;
        float y1;
    };
    typedef void (*GenericFuncPtr)();
    typedef GenericFuncPtr (*GetProcAddressPtr)(Device*, const char*);
    typedef void (*DebugCallback)(DebugCallbackSource::Enum, DebugCallbackType::Enum, int, DebugCallbackSeverity::Enum, const char*, void*);
    typedef void (*CommandBufferMemoryCallback)(CommandBuffer*, CommandBufferMemoryEvent::Enum, size_t, void*);
}