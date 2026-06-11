/*--------------------------------------------------------------------------------*
  Copyright Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/

/**
* @file
* @brief  Declarations of API resources for enums.
*/

#pragma once

#include <nn/nn_Macro.h>

namespace nn {
namespace gfx {

namespace detail {

enum FilterModeBit
{
    FilterModeBit_Point = 1,
    FilterModeBit_Linear = 2,
    FilterModeBit_MinFilterShift = 4,
    FilterModeBit_MagFilterShift = 2,
    FilterModeBit_MipFilterShift = 0,
    FilterModeBit_MinPoint = FilterModeBit_Point << FilterModeBit_MinFilterShift,
    FilterModeBit_MinLinear = FilterModeBit_Linear << FilterModeBit_MinFilterShift,
    FilterModeBit_MagPoint = FilterModeBit_Point << FilterModeBit_MagFilterShift,
    FilterModeBit_MagLinear = FilterModeBit_Linear << FilterModeBit_MagFilterShift,
    FilterModeBit_MipPoint = FilterModeBit_Point << FilterModeBit_MipFilterShift,
    FilterModeBit_MipLinear = FilterModeBit_Linear << FilterModeBit_MipFilterShift,

    FilterModeBit_MinFilterMask = 0x03 << FilterModeBit_MinFilterShift,
    FilterModeBit_MagFilterMask = 0x03 << FilterModeBit_MagFilterShift,
    FilterModeBit_MipFilterMask = 0x03 << FilterModeBit_MipFilterShift,

    FilterModeBit_Anisotropic = 0x40,
    FilterModeBit_Comparison = 0x80,
    FilterModeBit_Minimum = 0x0100,
    FilterModeBit_Maximum = 0x0200
};

}

/**
* @brief  Logic operations.
*
* @details
*  In these descriptions of enumerators, <tt><var>src</var></tt> refers to the source value, and <tt><var>dst</var></tt> refers to the destination value.
*/
enum LogicOperation
{
    LogicOperation_Clear, //!<  Represents <tt>0</tt>.
    LogicOperation_And, //!<  Represents <tt><var>src</var></tt> & <tt><var>dst</var></tt>.
    LogicOperation_AndReverse, //!<  Represents <tt><var>src</var></tt> & ~<tt><var>dst</var></tt>.
    LogicOperation_Copy, //!<  Represents <tt><var>src</var></tt>.
    LogicOperation_AndInverted, //!<  Represents ~<tt><var>src</var></tt> & <tt><var>dst</var></tt>.
    LogicOperation_NoOp, //!<  Represents <tt><var>dst</var></tt>.
    LogicOperation_Xor, //!<  Represents <tt><var>src</var></tt> ^ <tt><var>dst</var></tt>.
    LogicOperation_Or, //!<  <tt><var>src</var></tt> | Represents <tt><var>dst</var></tt>.
    LogicOperation_Nor, //!< ~( <tt><var>src</var></tt> | Represents <tt><var>dst</var></tt>).
    LogicOperation_Equiv, //!<  Represents ~( <tt><var>src</var></tt> ^ <tt><var>dst</var></tt> ).
    LogicOperation_Invert, //!<  Represents ~<tt><var>dst</var></tt>.
    LogicOperation_OrReverse, //!<  <tt><var>src</var></tt> | Represents ~<tt><var>dst</var></tt>.
    LogicOperation_CopyInverted, //!<  Represents ~<tt><var>src</var></tt>.
    LogicOperation_OrInverted, //!<  <tt><var>~src</var></tt> | Represents <tt><var>dst</var></tt>.
    LogicOperation_Nand, //!<  Represents ~( <tt><var>src</var></tt> & <tt><var>dst</var></tt> ).
    LogicOperation_Set, //!<  Represents <tt>1</tt>.

    LogicOperation_End
};

/**
* @brief  Blend functions.
*
* @details
*  In these descriptions of enumerators, <tt><var>src</var></tt> refers to the source value, <tt><var>srcfactor</var></tt> to the source blend factor, <tt><var>dst</var></tt> to the destination value, and <tt><var>dstfactor</var></tt> to the destination factor.
*/
enum BlendFunction
{
    BlendFunction_Add, //!<  Represents <tt><var>src</var></tt> × <tt><var>srcfactor</var></tt> + <tt><var>dst</var></tt> × <tt><var>dstfactor</var></tt>.
    BlendFunction_Subtract, //!<  Represents <tt><var>src</var></tt> × <tt><var>srcfactor</var></tt> - <tt><var>dst</var></tt> × <tt><var>dstfactor</var></tt>.
    BlendFunction_ReverseSubtract, //!<  Represents <tt><var>dst</var></tt> * <tt><var>dstfactor</var></tt> - <tt><var>src</var></tt> * <tt><var>srcfactor</var></tt>.
    BlendFunction_Min, //!<  Represents min( <tt><var>src</var></tt>, <tt><var>dst</var></tt> ).
    BlendFunction_Max, //!<  Represents max( <tt><var>src</var></tt>, <tt><var>dst</var></tt> ).

    BlendFunction_End
};

/**
* @brief  Blend factors.
*
* @details
*  In these descriptions of enumerators, <tt><var>src0</var></tt> refers to the source value of index 0, <tt><var>src1</var></tt> refers to the source value of index 1, <tt><var>const</var></tt> refers to the blend factor, and <tt><var>dst</var></tt> refers to the destination value.
*/
enum BlendFactor
{
    BlendFactor_Zero, //!<  Represents <tt>0</tt>.
    BlendFactor_One, //!<  Represents <tt>1</tt>.
    BlendFactor_SourceColor, //!<  Represents <tt><var>src0</var></tt>.
    BlendFactor_OneMinusSourceColor, //!<  Represents <tt>1</tt> - <tt><var>src0</var></tt>.
    BlendFactor_DestinationColor, //!<  Represents <tt><var>dst</var></tt>.
    BlendFactor_OneMinusDestinationColor, //!<  Represents <tt>1</tt> - <tt><var>dst</var></tt>.
    BlendFactor_SourceAlpha, //!<  Represents <tt><var>src0</var>.alpha</tt>.
    BlendFactor_OneMinusSourceAlpha, //!<  Represents <tt>1</tt> - <tt><var>src0</var>.alpha</tt>.
    BlendFactor_DestinationAlpha, //!<  Represents <tt><var>dstA</var></tt>.
    BlendFactor_OneMinusDestinationAlpha, //!<  Represents <tt>1</tt> - <tt><var>dst</var>.alpha</tt>.
    BlendFactor_ConstantColor, //!<  Represents <tt><var>const</var></tt>.
    BlendFactor_OneMinusConstantColor, //!<  Represents <tt>1</tt> - <tt><var>const</var></tt>.
    BlendFactor_ConstantAlpha, //!<  Represents <tt><var>const</var>.alpha</tt>.
    BlendFactor_OneMinusConstantAlpha, //!<  Represents <tt>1</tt> - <tt><var>const</var>.alpha</tt>.
    BlendFactor_SourceAlphaSaturate, //!<  For RGB, represents min( <tt><var>src0</var>.alpha</tt>, <tt>1</tt> - <tt><var>dst</var>.alpha</tt> ). For alpha, represents <tt>1</tt>.
    BlendFactor_Source1Color, //!<  Represents <tt><var>src1</var></tt>.
    BlendFactor_OneMinusSource1Color, //!<  Represents <tt>1</tt> - <tt><var>src1</var></tt>.
    BlendFactor_Source1Alpha, //!<  Represents <tt><var>src1</var>.alpha</tt>.
    BlendFactor_OneMinusSource1Alpha, //!<  Represents <tt>1</tt> - <tt><var>src1</var>.alpha</tt>.

    BlendFactor_End
};

/**
* @brief  Stencil operations.
*/
enum StencilOperation
{
    StencilOperation_Keep, //!<  Stores the current value.
    StencilOperation_Zero, //!<  Sets zero.
    StencilOperation_Replace, //!<  Replaces with a reference value.
    StencilOperation_IncrementClamp, //!<  Increments. If at the maximum value, does not change.
    StencilOperation_DecrementClamp, //!<  Decrements. If <tt>0</tt>, does not change.
    StencilOperation_Invert, //!<  Inverts bits.
    StencilOperation_IncrementWrap, //!<  Increments. If at the maximum value, set to <tt>0</tt>.
    StencilOperation_DecrementWrap, //!<  Decrements. If <tt>0</tt>, set to the maximum value.

    StencilOperation_End
};

/**
* @brief  Channel masks.
*/
enum ChannelMask
{
    ChannelMask_Red = 0x01, //!<  The red component.
    ChannelMask_Green = 0x02, //!<  The green component.
    ChannelMask_Blue = 0x04, //!<  The blue component.
    ChannelMask_Alpha = 0x08, //!<  The alpha component.
    ChannelMask_All = ( ChannelMask_Red | ChannelMask_Green
        | ChannelMask_Blue | ChannelMask_Alpha ) //!<  All components.
};

/**
* @brief  The primitive topology.
*/
enum PrimitiveTopology
{
    PrimitiveTopology_PointList, //!<  List of points.
    PrimitiveTopology_LineList, //!<  List of lines.
    PrimitiveTopology_LineStrip, //!<  Line strips.
    PrimitiveTopology_TriangleList, //!<  List of triangles.
    PrimitiveTopology_TriangleStrip, //!<  Triangle strips.
    PrimitiveTopology_LineListAdjacency, //!<  List of lines with adjacency information.
    PrimitiveTopology_LineStripAdjacency, //!<  Line strips with adjacency information.
    PrimitiveTopology_TriangleListAdjacency, //!<  List of triangles with adjacency information.
    PrimitiveTopology_TriangleStripAdjacency, //!<  Triangle strips with adjacency information.
    PrimitiveTopology_PatchList, //!<  List of patches.

    PrimitiveTopology_End
};

/**
* @brief  The primitive topology type.
*/
enum PrimitiveTopologyType
{
    PrimitiveTopologyType_Undefined, //!<  Unknown.
    PrimitiveTopologyType_Point, //!<  Point.
    PrimitiveTopologyType_Line, //!<  Line.
    PrimitiveTopologyType_Triangle, //!<  Triangle.
    PrimitiveTopologyType_Patch, //!<  Patch.

    PrimitiveTopologyType_End
};

/**
* @brief  Conservative rasterization mode.
*/
enum ConservativeRasterizationMode
{
    ConservativeRasterizationMode_Disable, //!<  Conservative rasterization mode is disabled.
    ConservativeRasterizationMode_Enable, //!<  Conservative rasterization mode is enabled.

    ConservativeRasterizationMode_End
};

/**
* @brief  The index format.
*/
enum IndexFormat
{
    IndexFormat_Uint8, //!<  8-bit unsigned integer.
    IndexFormat_Uint16, //!<  16-bit unsigned integer.
    IndexFormat_Uint32, //!<  32-bit unsigned integer.

    IndexFormat_End
};

/**
* @brief  Fill modes.
*/
enum FillMode
{
    FillMode_Wireframe = 1, //!<  Wireframe.
    FillMode_Solid, //!<  Fill inside polygon.

    FillMode_End
};

/**
* @brief  The culling mode.
*/
enum CullMode
{
    CullMode_None, //!<  No culling.
    CullMode_Front, //!<  Front-face culling.
    CullMode_Back, //!<  Back-face culling.

    CullMode_End
};

/**
* @brief  Definitions for which face is the front face.
*/
enum FrontFace
{
    FrontFace_Ccw, //!<  Counter-clockwise is the front face.
    FrontFace_Cw, //!<  Clockwise is the front face.

    FrontFace_End
};

/**
* @brief  Modes for calculating addresses outside the texture boundary.
*/
enum TextureAddressMode
{
    TextureAddressMode_Repeat, //!<  Repeat the address inside the boundary.
    TextureAddressMode_Mirror, //!<  Flip and repeat the address inside the boundary.
    TextureAddressMode_ClampToEdge, //!<  Clamp to the edge.
    TextureAddressMode_ClampToBorder, //!<  Clamp to the border color.
    TextureAddressMode_MirrorClampToEdge, //!<  If negative, repeat the address inside the boundary only once and then clamp to the edge.

    TextureAddressMode_End
};

/**
* @brief  Texture sampling filter modes.
*/
enum FilterMode
{
    FilterMode_MinPoint_MagPoint_MipPoint = detail::FilterModeBit_MinPoint |
        detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Point minification filter, point magnification filter, point mipmap filter.
    FilterMode_MinPoint_MagPoint_MipLinear = detail::FilterModeBit_MinPoint |
        detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear,//!<  Point minification filter, point magnification filter, linear mipmap filter.
    FilterMode_MinPoint_MagLinear_MipPoint = detail::FilterModeBit_MinPoint |
        detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Point minification filter, linear magnification filter, point mipmap filter.
    FilterMode_MinPoint_MagLinear_MipLinear = detail::FilterModeBit_MinPoint |
        detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Point minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_MinLinear_MagPoint_MipPoint = detail::FilterModeBit_MinLinear |
        detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Linear minification filter, point magnification filter, point mipmap filter.
    FilterMode_MinLinear_MagPoint_MipLinear = detail::FilterModeBit_MinLinear |
        detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear, //!<  Linear minification filter, point magnification filter, linear mipmap filter.
    FilterMode_MinLinear_MagLinear_MipPoint = detail::FilterModeBit_MinLinear |
        detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Linear minification filter, linear magnification filter, point mipmap filter.
    FilterMode_MinLinear_MagLinear_MipLinear = detail::FilterModeBit_MinLinear |
        detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Linear minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_Anisotropic = detail::FilterModeBit_Anisotropic | detail::FilterModeBit_MinLinear |
        detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Anisotropic filter.
    FilterMode_Comparison_MinPoint_MagPoint_MipPoint = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Comparison mode, point minification filter, point magnification filter, point mipmap filter.
    FilterMode_Comparison_MinPoint_MagPoint_MipLinear = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear, //!<  Comparison mode, point minification filter, point magnification filter, linear mipmap filter.
    FilterMode_Comparison_MinPoint_MagLinear_MipPoint = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Comparison mode, point minification filter, linear magnification filter, point mipmap filter.
    FilterMode_Comparison_MinPoint_MagLinear_MipLinear = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Comparison mode, point minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_Comparison_MinLinear_MagPoint_MipPoint = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Comparison mode, linear minification filter, point magnification filter, point mipmap filter.
    FilterMode_Comparison_MinLinear_MagPoint_MipLinear = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear, //!<  Comparison mode, linear minification filter, point magnification filter, linear mipmap filter.
    FilterMode_Comparison_MinLinear_MagLinear_MipPoint = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Comparison mode, linear minification filter, linear magnification filter, point mipmap filter.
    FilterMode_Comparison_MinLinear_MagLinear_MipLinear = detail::FilterModeBit_Comparison |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Comparison mode, linear minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_Comparison_Anisotropic = detail::FilterModeBit_Comparison | detail::FilterModeBit_Anisotropic |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Comparison mode, anisotropic filter.
    FilterMode_Minimum_MinPoint_MagPoint_MipPoint = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Minimum reduction, point minification filter, point magnification filter, point mipmap filter.
    FilterMode_Minimum_MinPoint_MagPoint_MipLinear = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear,//!<  Minimum reduction, point minification filter, point magnification filter, linear mipmap filter.
    FilterMode_Minimum_MinPoint_MagLinear_MipPoint = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Minimum reduction, point minification filter, linear magnification filter, point mipmap filter.
    FilterMode_Minimum_MinPoint_MagLinear_MipLinear = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Minimum reduction, point minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_Minimum_MinLinear_MagPoint_MipPoint = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Minimum reduction, linear minification filter, point magnification filter, point mipmap filter.
    FilterMode_Minimum_MinLinear_MagPoint_MipLinear = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear, //!<  Minimum reduction, linear minification filter, point magnification filter, linear mipmap filter.
    FilterMode_Minimum_MinLinear_MagLinear_MipPoint = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Minimum reduction, linear minification filter, linear magnification filter, point mipmap filter.
    FilterMode_Minimum_MinLinear_MagLinear_MipLinear = detail::FilterModeBit_Minimum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Minimum reduction, linear minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_Minimum_Anisotropic = detail::FilterModeBit_Minimum | detail::FilterModeBit_Anisotropic |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Minimum reduction, anisotropic filter.
    FilterMode_Maximum_MinPoint_MagPoint_MipPoint = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Maximum reduction, point minification filter, point magnification filter, point mipmap filter.
    FilterMode_Maximum_MinPoint_MagPoint_MipLinear = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear,//!<  Maximum reduction, point minification filter, point magnification filter, linear mipmap filter.
    FilterMode_Maximum_MinPoint_MagLinear_MipPoint = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Maximum reduction, point minification filter, linear magnification filter, point mipmap filter.
    FilterMode_Maximum_MinPoint_MagLinear_MipLinear = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinPoint | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Maximum reduction, point minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_Maximum_MinLinear_MagPoint_MipPoint = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipPoint, //!<  Maximum reduction, linear minification filter, point magnification filter, point mipmap filter.
    FilterMode_Maximum_MinLinear_MagPoint_MipLinear = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagPoint | detail::FilterModeBit_MipLinear, //!<  Maximum reduction, linear minification filter, point magnification filter, linear mipmap filter.
    FilterMode_Maximum_MinLinear_MagLinear_MipPoint = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipPoint, //!<  Maximum reduction, linear minification filter, linear magnification filter, point mipmap filter.
    FilterMode_Maximum_MinLinear_MagLinear_MipLinear = detail::FilterModeBit_Maximum |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Maximum reduction, linear minification filter, linear magnification filter, linear mipmap filter.
    FilterMode_Maximum_Anisotropic = detail::FilterModeBit_Maximum | detail::FilterModeBit_Anisotropic |
        detail::FilterModeBit_MinLinear | detail::FilterModeBit_MagLinear | detail::FilterModeBit_MipLinear, //!<  Maximum reduction, anisotropic filter.
};

/**
* @brief  Comparison functions.
*/
enum ComparisonFunction
{
    ComparisonFunction_Never, //!<  Represents <tt>false</tt>.
    ComparisonFunction_Less, //!<  Represents <tt><var>lhs</var></tt> < <tt><var>rhs</var></tt>.
    ComparisonFunction_Equal, //!<  Represents <tt><var>lhs</var></tt> == <tt><var>rhs</var></tt>.
    ComparisonFunction_LessEqual, //!<  Represents <tt><var>lhs</var></tt> <= <tt><var>rhs</var></tt>.
    ComparisonFunction_Greater, //!<  Represents <tt><var>lhs</var></tt> > <tt><var>rhs</var></tt>.
    ComparisonFunction_NotEqual, //!<  Represents <tt><var>lhs</var></tt> != <tt><var>rhs</var></tt>.
    ComparisonFunction_GreaterEqual, //!<  Represents <tt><var>lhs</var></tt> >= <tt><var>rhs</var></tt>.
    ComparisonFunction_Always, //!<  Represents <tt>true</tt>.

    ComparisonFunction_End
};

/**
* @brief  Texture border color types.
*/
enum TextureBorderColorType
{
    TextureBorderColorType_White, //!<  Represents ( <tt>1</tt>, <tt>1</tt>, <tt>1</tt>, <tt>1</tt> ).
    TextureBorderColorType_TransparentBlack, //!<  Represents ( <tt>0</tt>, <tt>0</tt>, <tt>0</tt>, <tt>0</tt> ).
    TextureBorderColorType_OpaqueBlack, //!<  Represents ( <tt>0</tt>, <tt>0</tt> <tt>0</tt>, <tt>1</tt> ).

    TextureBorderColorType_End
};

/**
* @brief  The dimension of the image data.
*/
enum ImageStorageDimension
{
    ImageStorageDimension_Undefined,
    ImageStorageDimension_1d, //!<  One dimension.
    ImageStorageDimension_2d, //!<  Two dimensions.
    ImageStorageDimension_3d //!<  Three dimensions.
};

/**
* @brief  Image dimensions.
*/
enum ImageDimension
{
    ImageDimension_1d, //!<  One dimension.
    ImageDimension_2d, //!<  Two dimensions.
    ImageDimension_3d, //!<  Three dimensions.
    ImageDimension_CubeMap, //!<  A cubemap image.
    ImageDimension_1dArray, //!<  One dimensional array.
    ImageDimension_2dArray, //!<  Two dimensional array.
    ImageDimension_2dMultisample, //!<  A multisample image.
    ImageDimension_2dMultisampleArray, //!<  A multisample image array.
    ImageDimension_CubeMapArray, //!<  A cubemap image array.

    ImageDimension_End
};

/**
* @brief  Channel formats.
*
* @details
*  The packing format is listed in order from the least significant bit.
*/
enum ChannelFormat
{
    ChannelFormat_Undefined, //!<  Undefined format.
    ChannelFormat_R4_G4, //!<  Two-component, 8-bit format (each component 4 bits).
    ChannelFormat_R8, //!<  Single-component, 8-bit format.
    ChannelFormat_R4_G4_B4_A4, //!<  Four-component, 16-bit format (each component 4 bits).
    ChannelFormat_A4_B4_G4_R4, //!<  Four-component, 16-bit inverted format (each component 4 bits).
    ChannelFormat_R5_G5_B5_A1, //!<  Four-component, 16-bit format (first three components 5 bits, last component 1 bit).
    ChannelFormat_A1_B5_G5_R5, //!<  Four-component, 16-bit reversed format (first component 1 bit, last three components 5 bits).
    ChannelFormat_R5_G6_B5, //!<  Three-component, 16-bit format (5 bits, 6 bits, 5 bits).
    ChannelFormat_B5_G6_R5, //!<  Three-component, 16-bit reversed format (5 bits, 6 bits, 5 bits).
    ChannelFormat_R8_G8, //!<  Two-component, 16-bit format (each component 8 bits).
    ChannelFormat_R16, //!<  Single-component, 16-bit format.
    ChannelFormat_R8_G8_B8_A8, //!<  Four-component, 32-bit format (each component 8 bits).
    ChannelFormat_B8_G8_R8_A8, //!<  Four-component, 32-bit format (each component 8 bits). The first three components in reversed format.
    ChannelFormat_R9_G9_B9_E5, //!<  Exponent format, where the first three components share the last component as an exponent.
    ChannelFormat_R10_G10_B10_A2, //!<  Four-component, 32-bit format (first three components 10 bits, last component 2 bits).
    ChannelFormat_R11_G11_B10, //!<  Three-component, 32-bit format (11 bits, 11 bits, 10 bits).
    ChannelFormat_B10_G11_R11, //!<  Three-component, 32-bit reversed format (10 bits, 11 bits, 11 bits).
    ChannelFormat_R10_G11_B11, //!<  Three-component, 32-bit format (10 bits, 11 bits, 11 bits).
    ChannelFormat_R16_G16, //!<  Two-component, 32-bit format (each component 16 bits).
    ChannelFormat_R24_G8, //!<  Two-component, 32-bit format (24 bits, 8 bits).
    ChannelFormat_R32, //!<  Single-component, 32-bit format.
    ChannelFormat_R16_G16_B16_A16, //!<  Four-component, 64-bit format (each component 16 bits).
    ChannelFormat_R32_G8_X24, //!<  Three-component, 64-bit format (32 bits, 8 bits, and 24 bits of padding).
    ChannelFormat_R32_G32, //!<  Two-component, 64-bit format (each component 32 bits).
    ChannelFormat_R32_G32_B32, //!<  Three-component, 96-bit format (each component 32 bits).
    ChannelFormat_R32_G32_B32_A32, //!<  Four-component, 128-bit format (each component 32 bits).
    ChannelFormat_Bc1, //!<  BC1 compression format.
    ChannelFormat_Bc2, //!<  BC2 compression format.
    ChannelFormat_Bc3, //!<  BC3 compression format.
    ChannelFormat_Bc4, //!<  BC4 compression format.
    ChannelFormat_Bc5, //!<  BC5 compression format.
    ChannelFormat_Bc6, //!<  BC6 compression format.
    ChannelFormat_Bc7, //!<  BC7 compression format.
    ChannelFormat_Eac_R11, //!<  EAC R11 compressed format.
    ChannelFormat_Eac_R11_G11, //!<  EAC R11 G11 compressed format.
    ChannelFormat_Etc1, //!<  ETC1 compression format.
    ChannelFormat_Etc2, //!<  ETC2 compression format.
    ChannelFormat_Etc2_Mask, //!<  1-bit alpha ETC2 compression format.
    ChannelFormat_Etc2_Alpha, //!<  ETC2 with alpha compression format.
    ChannelFormat_Pvrtc1_2Bpp, //!<  PVRTC1 2bpp compression format.
    ChannelFormat_Pvrtc1_4Bpp, //!<  PVRTC1 4bpp compression format.
    ChannelFormat_Pvrtc1_Alpha_2Bpp, //!<  PVRTC1 2bpp with alpha compression format.
    ChannelFormat_Pvrtc1_Alpha_4Bpp, //!<  PVRTC1 4bpp with alpha compression format.
    ChannelFormat_Pvrtc2_Alpha_2Bpp, //!<  PVRTC2 2bpp with alpha compression format.
    ChannelFormat_Pvrtc2_Alpha_4Bpp, //!<  PVRTC2 4bpp with alpha compression format.
    ChannelFormat_Astc_4x4, //!<  ASTC 4x4 compression format.
    ChannelFormat_Astc_5x4, //!<  ASTC 5x4 compression format.
    ChannelFormat_Astc_5x5, //!<  ASTC 5x5 compression format.
    ChannelFormat_Astc_6x5, //!<  ASTC 6x5 compression format.
    ChannelFormat_Astc_6x6, //!<  ASTC 6x6 compression format.
    ChannelFormat_Astc_8x5, //!<  ASTC 8x5 compression format.
    ChannelFormat_Astc_8x6, //!<  ASTC 8x6 compression format.
    ChannelFormat_Astc_8x8, //!<  ASTC 8x8 compression format.
    ChannelFormat_Astc_10x5, //!<  ASTC 10x5 compression format.
    ChannelFormat_Astc_10x6, //!<  ASTC 10x6 compression format.
    ChannelFormat_Astc_10x8, //!<  ASTC 10x8 compression format.
    ChannelFormat_Astc_10x10, //!<  ASTC 10x10 compression format.
    ChannelFormat_Astc_12x10, //!<  ASTC 12x10 compression format.
    ChannelFormat_Astc_12x12, //!<  ASTC 12x12 compression format.
    ChannelFormat_B5_G5_R5_A1, //!<  Four-component, 16-bit format (first three components 5 bits, last component 1 bit).

    ChannelFormat_End
};

/**
* @brief  Type formats.
*/
enum TypeFormat
{
    TypeFormat_Undefined, //!<  Undefined format.
    TypeFormat_Unorm, //!<  Unsigned normalized integer.
    TypeFormat_Snorm, //!<  Signed normalized integer.
    TypeFormat_Uint, //!<  Unsigned integer.
    TypeFormat_Sint, //!<  Signed integer.
    TypeFormat_Float, //!<  Floating-point number.
    TypeFormat_UnormSrgb, //!<  SRGB format.
    TypeFormat_DepthStencil, //!<  Depth stencil format.
    TypeFormat_UintToFloat, //!<  Unsigned integer converted to floating-point.
    TypeFormat_SintToFloat, //!<  Signed integer converted to floating-point.
    TypeFormat_Ufloat, //!<  Unsigned floating-point number.

    TypeFormat_End,

    TypeFormat_Bits = 8
};


/**
* @brief  Image formats.
*
* @details
*  The packing format is listed in order from the least significant bit.
*/
enum ImageFormat
{
    ImageFormat_Undefined = 0, //!<  Undefined format.
    ImageFormat_R8_Unorm = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Single-component, 8-bit, unsigned-normalized format.
    ImageFormat_R8_Snorm = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Single-component, 8-bit, signed-normalized format.
    ImageFormat_R8_Uint = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Single-component, 8-bit, unsigned-integer format.
    ImageFormat_R8_Sint = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Single-component, 8-bit, signed-integer format.
    ImageFormat_R4_G4_B4_A4_Unorm = ( ChannelFormat_R4_G4_B4_A4 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 16-bit, unsigned-normalized format (each component 4 bits).
    ImageFormat_A4_B4_G4_R4_Unorm = ( ChannelFormat_A4_B4_G4_R4 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 16-bit, unsigned-normalized inverted format (each component 4 bits).
    ImageFormat_R5_G5_B5_A1_Unorm = ( ChannelFormat_R5_G5_B5_A1 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 16-bit, unsigned-normalized format (first three components 5 bits, last component 1 bit).
    ImageFormat_A1_B5_G5_R5_Unorm = ( ChannelFormat_A1_B5_G5_R5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 16-bit unsigned-normalized format (first component 1 bit, last three components 5 bits).
    ImageFormat_R5_G6_B5_Unorm = ( ChannelFormat_R5_G6_B5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Three-component, 16-bit, unsigned-normalized format (5 bits, 6 bits, 5 bits).
    ImageFormat_B5_G6_R5_Unorm = ( ChannelFormat_B5_G6_R5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Three-component, 16-bit, unsigned-normalized-reversed format (5 bits, 6 bits, 5 bits).
    ImageFormat_R8_G8_Unorm = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Two-component, 16-bit, unsigned-normalized format (each component 8 bits).
    ImageFormat_R8_G8_Snorm = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Two-component, 16-bit, signed-normalized format (each component 8 bits).
    ImageFormat_R8_G8_Uint = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Two-component, 16-bit, unsigned-integer format (each component 8 bits).
    ImageFormat_R8_G8_Sint = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Two-component, 16-bit, signed-integer format (each component 8 bits).
    ImageFormat_R16_Unorm = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Single-component, 16-bit, unsigned-normalized format.
    ImageFormat_R16_Snorm = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Single-component, 16-bit, signed-normalized format.
    ImageFormat_R16_Uint = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Single-component, 16-bit, unsigned-integer format.
    ImageFormat_R16_Sint = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Single-component, 16-bit, signed-integer format.
    ImageFormat_R16_Float = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Single-component, 16-bit, floating-point format.
    ImageFormat_D16_Unorm = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_DepthStencil, //!<  Single-component, 16-bit, depth stencil format.
    ImageFormat_R8_G8_B8_A8_Unorm = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 32-bit, unsigned-normalized format (each component 8 bits).
    ImageFormat_R8_G8_B8_A8_Snorm = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Four-component, 32-bit, signed-normalized format (each component 8 bits).
    ImageFormat_R8_G8_B8_A8_Uint = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 32-bit, unsigned-integer format (each component 8 bits).
    ImageFormat_R8_G8_B8_A8_Sint = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 32-bit, signed-integer format (each component 8 bits).
    ImageFormat_R8_G8_B8_A8_UnormSrgb = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  Four-component, 32-bit, SRGB format (each component 8 bits).
    ImageFormat_B8_G8_R8_A8_Unorm = ( ChannelFormat_B8_G8_R8_A8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 32-bit, unsigned-normalized format (each component 8 bits). The first three components in reversed format.
    ImageFormat_B8_G8_R8_A8_Snorm = ( ChannelFormat_B8_G8_R8_A8 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Four-component, 32-bit, signed-normalized format (each component 8 bits). The first three components in reversed format.
    ImageFormat_B8_G8_R8_A8_Uint = ( ChannelFormat_B8_G8_R8_A8 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 32-bit, unsigned-integer format (each component 8 bits). The first three components in reversed format.
    ImageFormat_B8_G8_R8_A8_Sint = ( ChannelFormat_B8_G8_R8_A8 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 32-bit, signed-integer format (each component 8 bits). The first three components in reversed format.
    ImageFormat_B8_G8_R8_A8_UnormSrgb = ( ChannelFormat_B8_G8_R8_A8 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  Four-component, 32-bit, SRGB format (each component 8 bits). The first three components in reversed format.
    ImageFormat_R9_G9_B9_E5_SharedExp = ( ChannelFormat_R9_G9_B9_E5 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Exponent format, where the first three components share the last component as an exponent.
    ImageFormat_R10_G10_B10_A2_Unorm = ( ChannelFormat_R10_G10_B10_A2 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 32-bit, unsigned-normalized format (first three components 10 bits, last component 2 bits).
    ImageFormat_R10_G10_B10_A2_Uint = ( ChannelFormat_R10_G10_B10_A2 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 32-bit, unsigned-integer format (first three components 10 bits, last component 2 bits).
    ImageFormat_R11_G11_B10_Float = ( ChannelFormat_R11_G11_B10 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Three-component, 32-bit, floating-point format (11 bits, 11 bits, 10 bits).
    ImageFormat_B10_G11_R11_Float = ( ChannelFormat_B10_G11_R11 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Three-component, 32-bit, floating-point format (10 bits, 11 bits, 11 bits).
    ImageFormat_R16_G16_Unorm = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Two-component, 32-bit, unsigned-normalized format (each component 16 bits).
    ImageFormat_R16_G16_Snorm = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Two-component, 32-bit, signed-normalized format (each component 16 bits).
    ImageFormat_R16_G16_Uint = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Two-component, 32-bit, unsigned-integer format (each component 16 bits).
    ImageFormat_R16_G16_Sint = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Two-component, 32-bit, signed-integer format (each component 16 bits).
    ImageFormat_R16_G16_Float = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Two-component, 32-bit, floating-point format (each component 16 bits).
    ImageFormat_D24_Unorm_S8_Uint = ( ChannelFormat_R24_G8 << TypeFormat_Bits ) | TypeFormat_DepthStencil, //!<  Two-component, 32-bit, depth stencil format (24 bits, 8 bits).
    ImageFormat_R32_Uint = ( ChannelFormat_R32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Single-component, 32-bit, unsigned-integer format.
    ImageFormat_R32_Sint = ( ChannelFormat_R32 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Single-component, 32-bit, signed-integer format.
    ImageFormat_R32_Float = ( ChannelFormat_R32 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Single-component, 32-bit, floating-point format.
    ImageFormat_D32_Float = ( ChannelFormat_R32 << TypeFormat_Bits ) | TypeFormat_DepthStencil, //!<  Single-component, 32-bit, depth stencil format.
    ImageFormat_R16_G16_B16_A16_Unorm = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 64-bit, unsigned-normalized format (each component 16 bits).
    ImageFormat_R16_G16_B16_A16_Snorm = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Four-component, 64-bit, signed-normalized format (each component 16 bits).
    ImageFormat_R16_G16_B16_A16_Uint = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 64-bit, unsigned-integer format (each component 16 bits).
    ImageFormat_R16_G16_B16_A16_Sint = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 64-bit, signed-integer format (each component 16 bits).
    ImageFormat_R16_G16_B16_A16_Float = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Four-component, 64-bit, floating-point format (each component 16 bits).
    ImageFormat_D32_Float_S8_Uint_X24 = ( ChannelFormat_R32_G8_X24 << TypeFormat_Bits ) | TypeFormat_DepthStencil, //!<  Three-component, 64-bit, depth stencil format (32 bits, 8 bits, and 24 bits of padding).
    ImageFormat_R32_G32_Uint = ( ChannelFormat_R32_G32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Two-component, 64-bit, unsigned-integer format (each component 32 bits).
    ImageFormat_R32_G32_Sint = ( ChannelFormat_R32_G32<< TypeFormat_Bits ) | TypeFormat_Sint, //!<  Two-component, 64-bit, signed-integer format (each component 32 bits).
    ImageFormat_R32_G32_Float = ( ChannelFormat_R32_G32 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Two-component, 64-bit, floating-point format (each component 32 bits).
    ImageFormat_R32_G32_B32_Uint = ( ChannelFormat_R32_G32_B32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Three-component, 96-bit, unsigned-integer format (each component 32 bits).
    ImageFormat_R32_G32_B32_Sint = ( ChannelFormat_R32_G32_B32 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Three-component, 96-bit, signed-integer format (each component 32 bits).
    ImageFormat_R32_G32_B32_Float = ( ChannelFormat_R32_G32_B32 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Three-component, 96-bit, floating-point format (each component 32 bits).
    ImageFormat_R32_G32_B32_A32_Uint = ( ChannelFormat_R32_G32_B32_A32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 128-bit, unsigned-integer format (each component 32 bits).
    ImageFormat_R32_G32_B32_A32_Sint = ( ChannelFormat_R32_G32_B32_A32 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 128-bit, signed-integer format (each component 32 bits).
    ImageFormat_R32_G32_B32_A32_Float = ( ChannelFormat_R32_G32_B32_A32 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Four-component, 128-bit, floating-point format (each component 32 bits).

    ImageFormat_Bc1_Unorm = ( ChannelFormat_Bc1 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  BC1 compression, unsigned-normalized format.
    ImageFormat_Bc1_UnormSrgb = ( ChannelFormat_Bc1 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  BC1 compression, SRGB format.
    ImageFormat_Bc2_Unorm = ( ChannelFormat_Bc2 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  BC2 compression, unsigned-normalized format.
    ImageFormat_Bc2_UnormSrgb = ( ChannelFormat_Bc2 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  BC2 compression, SRGB format.
    ImageFormat_Bc3_Unorm = ( ChannelFormat_Bc3 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  BC3 compression, unsigned-normalized format.
    ImageFormat_Bc3_UnormSrgb = ( ChannelFormat_Bc3 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  BC3 compression, SRGB format.
    ImageFormat_Bc4_Unorm = ( ChannelFormat_Bc4 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  BC4 compression, unsigned-normalized format.
    ImageFormat_Bc4_Snorm = ( ChannelFormat_Bc4 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  BC4 compression, signed-normalized format.
    ImageFormat_Bc5_Unorm = ( ChannelFormat_Bc5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  BC5 compression, unsigned-normalized format.
    ImageFormat_Bc5_Snorm = ( ChannelFormat_Bc5 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  BC5 compression, signed-normalized format.
    ImageFormat_Bc6_Float = ( ChannelFormat_Bc6 << TypeFormat_Bits ) | TypeFormat_Float, //!<  BC6 compression, floating-point format.
    ImageFormat_Bc6_Ufloat = ( ChannelFormat_Bc6 << TypeFormat_Bits ) | TypeFormat_Ufloat, //!<  BC6 compression, unsigned-floating-point format.
    ImageFormat_Bc7_Unorm = ( ChannelFormat_Bc7 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  BC7 compression, unsigned-normalized format.
    ImageFormat_Bc7_UnormSrgb = ( ChannelFormat_Bc7 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  BC7 compression, SRGB format.
    ImageFormat_Eac_R11_Unorm = ( ChannelFormat_Eac_R11 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  EAC R11 compression, unsigned-normalized format.
    ImageFormat_Eac_R11_Snorm = ( ChannelFormat_Eac_R11 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  EAC R11 compression, signed-normalized format.
    ImageFormat_Eac_R11_G11_Unorm = ( ChannelFormat_Eac_R11_G11 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  EAC R11 G11 compression, unsigned-normalized format.
    ImageFormat_Eac_R11_G11_Snorm = ( ChannelFormat_Eac_R11_G11 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  EAC R11 G11 compression, signed-normalized format.
    ImageFormat_Etc1_Unorm = ( ChannelFormat_Etc1 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ETC1 compression, unsigned-normalized format.
    ImageFormat_Etc2_Unorm = ( ChannelFormat_Etc2 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ETC2 compression, unsigned-normalized format.
    ImageFormat_Etc2_UnormSrgb = ( ChannelFormat_Etc2 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ETC2 compression, SRGB format.
    ImageFormat_Etc2_Mask_Unorm = ( ChannelFormat_Etc2_Mask << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  1-bit alpha ETC2 compression, unsigned-normalized format.
    ImageFormat_Etc2_Mask_UnormSrgb = ( ChannelFormat_Etc2_Mask << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  1-bit alpha ETC2 compression, SRGB format.
    ImageFormat_Etc2_Alpha_Unorm = ( ChannelFormat_Etc2_Alpha << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Normalized and unsigned ETC2 compression format with alpha.
    ImageFormat_Etc2_Alpha_UnormSrgb = ( ChannelFormat_Etc2_Alpha << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ETC2 with alpha compression, SRGB format.
    ImageFormat_Pvrtc1_2Bpp_Unorm = ( ChannelFormat_Pvrtc1_2Bpp << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  PVRTC1 2bpp with alpha compression, unsigned-normalized format.
    ImageFormat_Pvrtc1_2Bpp_UnormSrgb = ( ChannelFormat_Pvrtc1_2Bpp << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  PVRTC1 2bpp compression, SRGB format.
    ImageFormat_Pvrtc1_4Bpp_Unorm = ( ChannelFormat_Pvrtc1_4Bpp << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  PVRTC1 4bpp compression, normalized format.
    ImageFormat_Pvrtc1_4Bpp_UnormSrgb = ( ChannelFormat_Pvrtc1_4Bpp << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  PVRTC1 4bpp compression, SRGB format.
    ImageFormat_Pvrtc1_Alpha_2Bpp_Unorm = ( ChannelFormat_Pvrtc1_Alpha_2Bpp << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  PVRTC1 2bpp with alpha compression, unsigned-normalized format.
    ImageFormat_Pvrtc1_Alpha_2Bpp_UnormSrgb = ( ChannelFormat_Pvrtc1_Alpha_2Bpp << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  PVRTC1 2bpp with alpha compression, SRGB format.
    ImageFormat_Pvrtc1_Alpha_4Bpp_Unorm = ( ChannelFormat_Pvrtc1_Alpha_4Bpp << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  PVRTC1 4bpp with alpha compression, unsigned-normalized format.
    ImageFormat_Pvrtc1_Alpha_4Bpp_UnormSrgb = ( ChannelFormat_Pvrtc1_Alpha_4Bpp << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  PVTC1 4bpp with alpha compression, SRGB format.
    ImageFormat_Pvrtc2_Alpha_2Bpp_Unorm = ( ChannelFormat_Pvrtc2_Alpha_2Bpp << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  PVRTC2 2bpp with alpha compression, unsigned-normalized format.
    ImageFormat_Pvrtc2_Alpha_2Bpp_UnormSrgb = ( ChannelFormat_Pvrtc2_Alpha_2Bpp << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  PVRTC2 2bpp with alpha compression, SRGB format.
    ImageFormat_Pvrtc2_Alpha_4Bpp_Unorm = ( ChannelFormat_Pvrtc2_Alpha_4Bpp << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  PVRTC2 4bpp with alpha compression, unsigned-normalized format.
    ImageFormat_Pvrtc2_Alpha_4Bpp_UnormSrgb = ( ChannelFormat_Pvrtc2_Alpha_4Bpp << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  PVRTC2 4bpp with alpha compression, SRGB format.
    ImageFormat_Astc_4x4_Unorm = ( ChannelFormat_Astc_4x4 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 4×4 compression, unsigned-normalized format.
    ImageFormat_Astc_4x4_UnormSrgb = ( ChannelFormat_Astc_4x4 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 4x4 compression, SRGB format.
    ImageFormat_Astc_5x4_Unorm = ( ChannelFormat_Astc_5x4 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 5×4 compression, unsigned-normalized format.
    ImageFormat_Astc_5x4_UnormSrgb = ( ChannelFormat_Astc_5x4 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 5x4 compression, SRGB format.
    ImageFormat_Astc_5x5_Unorm = ( ChannelFormat_Astc_5x5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 5×5 compression, unsigned-normalized format.
    ImageFormat_Astc_5x5_UnormSrgb = ( ChannelFormat_Astc_5x5 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 5x5 compression, SRGB format.
    ImageFormat_Astc_6x5_Unorm = ( ChannelFormat_Astc_6x5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 6×5 compression, unsigned-normalized format.
    ImageFormat_Astc_6x5_UnormSrgb = ( ChannelFormat_Astc_6x5 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 6x5 compression, SRGB format.
    ImageFormat_Astc_6x6_Unorm = ( ChannelFormat_Astc_6x6 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 6×6 compression, unsigned-normalized format.
    ImageFormat_Astc_6x6_UnormSrgb = ( ChannelFormat_Astc_6x6 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 6x6 compression, SRGB format.
    ImageFormat_Astc_8x5_Unorm = ( ChannelFormat_Astc_8x5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 8×5 compression, unsigned-normalized format.
    ImageFormat_Astc_8x5_UnormSrgb = ( ChannelFormat_Astc_8x5 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 8x5 compression, SRGB format.
    ImageFormat_Astc_8x6_Unorm = ( ChannelFormat_Astc_8x6 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 8×6 compression, unsigned-normalized format.
    ImageFormat_Astc_8x6_UnormSrgb = ( ChannelFormat_Astc_8x6 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 8x6 compression, SRGB format.
    ImageFormat_Astc_8x8_Unorm = ( ChannelFormat_Astc_8x8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 8×8 compression, unsigned-normalized format.
    ImageFormat_Astc_8x8_UnormSrgb = ( ChannelFormat_Astc_8x8 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 8x8 compression, SRGB format.
    ImageFormat_Astc_10x5_Unorm = ( ChannelFormat_Astc_10x5 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 10x5 compression, unsigned-normalized format.
    ImageFormat_Astc_10x5_UnormSrgb = ( ChannelFormat_Astc_10x5 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 10x5 compression, SRGB format.
    ImageFormat_Astc_10x6_Unorm = ( ChannelFormat_Astc_10x6 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 10x6 compression, unsigned-normalized format.
    ImageFormat_Astc_10x6_UnormSrgb = ( ChannelFormat_Astc_10x6 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 10x6 compression, SRGB format.
    ImageFormat_Astc_10x8_Unorm = ( ChannelFormat_Astc_10x8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 10x8 compression, unsigned-normalized format.
    ImageFormat_Astc_10x8_UnormSrgb = ( ChannelFormat_Astc_10x8 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 10x8 compression, SRGB format.
    ImageFormat_Astc_10x10_Unorm = ( ChannelFormat_Astc_10x10 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 10x10 compression, unsigned-normalized format.
    ImageFormat_Astc_10x10_UnormSrgb = ( ChannelFormat_Astc_10x10 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 10x10 compression, SRGB format.
    ImageFormat_Astc_12x10_Unorm = ( ChannelFormat_Astc_12x10 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 12x10 compression, unsigned-normalized format.
    ImageFormat_Astc_12x10_UnormSrgb = ( ChannelFormat_Astc_12x10 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 12x10 compression, SRGB format.
    ImageFormat_Astc_12x12_Unorm = ( ChannelFormat_Astc_12x12 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  ASTC 12x12 compression, unsigned-normalized format.
    ImageFormat_Astc_12x12_UnormSrgb = ( ChannelFormat_Astc_12x12 << TypeFormat_Bits ) | TypeFormat_UnormSrgb, //!<  ASTC 12x12 compression, SRGB format.

    ImageFormat_B5_G5_R5_A1_Unorm = ( ChannelFormat_B5_G5_R5_A1 << TypeFormat_Bits ) | TypeFormat_Unorm //!<  Four-component, 16-bit, unsigned-normalized format (first three components 5 bits, last component 1 bit).
};

/**
* @brief  Vertex attribute formats.
*/
enum AttributeFormat
{
    AttributeFormat_Undefined = 0, //!<  Undefined format.
    AttributeFormat_4_4_Unorm = ( ChannelFormat_R4_G4 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Two-component, 8-bit, unsigned-normalized format (each component 4 bits).
    AttributeFormat_8_Unorm = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Single-component, 8-bit, unsigned-normalized format.
    AttributeFormat_8_Snorm = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Single-component, 8-bit, signed-normalized format.
    AttributeFormat_8_Uint = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Single-component, 8-bit, unsigned-integer format.
    AttributeFormat_8_Sint = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Single-component, 8-bit, signed-integer format.
    AttributeFormat_8_UintToFloat = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_UintToFloat, //!<  Single-component, 8-bit, unsigned-integer converted to floating-point.
    AttributeFormat_8_SintToFloat = ( ChannelFormat_R8 << TypeFormat_Bits ) | TypeFormat_SintToFloat, //!<  Single-component, 8-bit, signed-integer converted to floating-point.
    AttributeFormat_8_8_Unorm = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Two-component, 16-bit, unsigned-normalized format (each component 8 bits).
    AttributeFormat_8_8_Snorm = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Two-component, 16-bit, signed-normalized format (each component 8 bits).
    AttributeFormat_8_8_Uint = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Two-component, 16-bit, unsigned-integer format (each component 8 bits).
    AttributeFormat_8_8_Sint = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Two-component, 16-bit, signed-integer format (each component 8 bits).
    AttributeFormat_8_8_UintToFloat = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_UintToFloat, //!<  Two-component, 16-bit, unsigned-integer format (each component 8 bits) converted to floating-point.
    AttributeFormat_8_8_SintToFloat = ( ChannelFormat_R8_G8 << TypeFormat_Bits ) | TypeFormat_SintToFloat, //!<  Two-component, 16-bit, signed-integer format (each component 8 bits) converted to floating-point.
    AttributeFormat_16_Unorm = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Single-component, 16-bit, unsigned-normalized format.
    AttributeFormat_16_Snorm = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Single-component, 16-bit, signed-normalized format.
    AttributeFormat_16_Uint = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Single-component, 16-bit, unsigned-integer format.
    AttributeFormat_16_Sint = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Single-component, 16-bit, signed-integer format.
    AttributeFormat_16_Float = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Single-component, 16-bit, floating-point format.
    AttributeFormat_16_UintToFloat = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_UintToFloat, //!<  Single-component, 16-bit, unsigned-integer converted to floating-point.
    AttributeFormat_16_SintToFloat = ( ChannelFormat_R16 << TypeFormat_Bits ) | TypeFormat_SintToFloat, //!<  Single-component, 16-bit, signed-integer converted to floating-point.
    AttributeFormat_8_8_8_8_Unorm = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 32-bit, unsigned-normalized format (each component 8 bits).
    AttributeFormat_8_8_8_8_Snorm = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Four-component, 32-bit, signed-normalized format (each component 8 bits).
    AttributeFormat_8_8_8_8_Uint = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 32-bit, unsigned-integer format (each component 8 bits).
    AttributeFormat_8_8_8_8_Sint = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 32-bit, signed-integer format (each component 8 bits).
    AttributeFormat_8_8_8_8_UintToFloat = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_UintToFloat, //!<  Four-component, 32-bit, unsigned-integer format (each component 8 bits) converted to floating-point.
    AttributeFormat_8_8_8_8_SintToFloat = ( ChannelFormat_R8_G8_B8_A8 << TypeFormat_Bits ) | TypeFormat_SintToFloat, //!<  Four-component, 32-bit, signed-integer format (each component 8 bits) converted to floating-point.
    AttributeFormat_10_10_10_2_Unorm = ( ChannelFormat_R10_G10_B10_A2 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 32-bit, unsigned-normalized format (first three components 10 bits, last component 2 bits).
    AttributeFormat_10_10_10_2_Snorm = ( ChannelFormat_R10_G10_B10_A2 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Four-component, 32-bit, signed-normalized format (first three components 10 bits, last component 2 bits).
    AttributeFormat_10_10_10_2_Uint = ( ChannelFormat_R10_G10_B10_A2 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 32-bit, unsigned-integer format (first three components 10 bits, last component 2 bits).
    AttributeFormat_10_10_10_2_Sint = ( ChannelFormat_R10_G10_B10_A2 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 32-bit, signed-integer format (first three components 10 bits, last component 2 bits).
    AttributeFormat_16_16_Unorm = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Two-component, 32-bit, unsigned-normalized format (each component 16 bits).
    AttributeFormat_16_16_Snorm = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Two-component, 32-bit, signed-normalized format (each component 16 bits).
    AttributeFormat_16_16_Uint = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Two-component, 32-bit, unsigned-integer format (each component 16 bits).
    AttributeFormat_16_16_Sint = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Two-component, 32-bit, signed-integer format (each component 16 bits).
    AttributeFormat_16_16_Float = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Two-component, 32-bit, floating-point format (each component 16 bits).
    AttributeFormat_16_16_UintToFloat = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_UintToFloat, //!<  Two-component, 32-bit, unsigned-integer format (each component 16 bits) converted to floating-point.
    AttributeFormat_16_16_SintToFloat = ( ChannelFormat_R16_G16 << TypeFormat_Bits ) | TypeFormat_SintToFloat, //!<  Two-component, 32-bit, signed-integer format (each component 16 bits) converted to floating-point.
    AttributeFormat_32_Uint = ( ChannelFormat_R32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Single-component, 32-bit, unsigned-integer format.
    AttributeFormat_32_Sint = ( ChannelFormat_R32 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Single-component, 32-bit, signed-integer format.
    AttributeFormat_32_Float = ( ChannelFormat_R32 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Single-component, 32-bit, floating-point format.
    AttributeFormat_16_16_16_16_Unorm = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Unorm, //!<  Four-component, 64-bit, unsigned-normalized format (each component 16 bits).
    AttributeFormat_16_16_16_16_Snorm = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Snorm, //!<  Four-component, 64-bit, signed-normalized format (each component 16 bits).
    AttributeFormat_16_16_16_16_Uint = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 64-bit, unsigned-integer format (each component 16 bits).
    AttributeFormat_16_16_16_16_Sint = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 64-bit, signed-integer format (each component 16 bits).
    AttributeFormat_16_16_16_16_Float = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Four-component, 64-bit, floating-point format (each component 16 bits).
    AttributeFormat_16_16_16_16_UintToFloat = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_UintToFloat, //!<  Four-component, 64-bit, unsigned-integer format (each component 16 bits) converted to floating-point.
    AttributeFormat_16_16_16_16_SintToFloat = ( ChannelFormat_R16_G16_B16_A16 << TypeFormat_Bits ) | TypeFormat_SintToFloat, //!<  Four-component, 64-bit, signed-integer format (each component 16 bits) converted to floating-point.
    AttributeFormat_32_32_Uint = ( ChannelFormat_R32_G32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Two-component, 64-bit, unsigned-integer format (each component 32 bits).
    AttributeFormat_32_32_Sint = ( ChannelFormat_R32_G32 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Two-component, 64-bit, signed-integer format (each component 32 bits).
    AttributeFormat_32_32_Float = ( ChannelFormat_R32_G32 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Two-component, 64-bit, floating-point format (each component 32 bits).
    AttributeFormat_32_32_32_Uint = ( ChannelFormat_R32_G32_B32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Three-component, 96-bit, unsigned-integer format (each component 32 bits).
    AttributeFormat_32_32_32_Sint = ( ChannelFormat_R32_G32_B32 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Three-component, 96-bit, signed-integer format (each component 32 bits).
    AttributeFormat_32_32_32_Float = ( ChannelFormat_R32_G32_B32 << TypeFormat_Bits ) | TypeFormat_Float, //!<  Three-component, 96-bit, floating-point format (each component 32 bits).
    AttributeFormat_32_32_32_32_Uint = ( ChannelFormat_R32_G32_B32_A32 << TypeFormat_Bits ) | TypeFormat_Uint, //!<  Four-component, 128-bit, unsigned-integer format (each component 32 bits).
    AttributeFormat_32_32_32_32_Sint = ( ChannelFormat_R32_G32_B32_A32 << TypeFormat_Bits ) | TypeFormat_Sint, //!<  Four-component, 128-bit, signed-integer format (each component 32 bits).
    AttributeFormat_32_32_32_32_Float = ( ChannelFormat_R32_G32_B32_A32 << TypeFormat_Bits ) | TypeFormat_Float //!<  Four-component, 128-bit, floating-point format (each component 32 bits).
};

/**
* @brief  Methods of access for the GPU.
*/
enum GpuAccess
{
    GpuAccess_Read = 0x01, //!<  Read access.
    GpuAccess_Write = 0x02, //!<  Write access.
    GpuAccess_VertexBuffer = 0x04, //!<  Access as vertex buffer.
    GpuAccess_IndexBuffer = 0x08, //!<  Access as an index buffer.
    GpuAccess_ConstantBuffer = 0x10, //!<  Access as a constant buffer.
    GpuAccess_Texture = 0x20, //!<  Access as texture.
    GpuAccess_UnorderedAccessBuffer = 0x40, //!<  Access as an unordered access buffer.
    GpuAccess_ColorBuffer = 0x80, //!<  Access as a color buffer.
    GpuAccess_DepthStencil = 0x0100, //!<  Access as a depth stencil buffer.
    GpuAccess_IndirectBuffer = 0x0200, //!<  Access as parameter buffer for indirect draw or indirect dispatch.
    GpuAccess_ScanBuffer = 0x0400, //!<  Access as a scan buffer.
    GpuAccess_QueryBuffer = 0x0800, //!<  Access as a query write destination.
    GpuAccess_Descriptor = 0x1000, //!<  Access as a descriptor.
    GpuAccess_ShaderCode = 0x2000, //!<  Access as shader code.
    GpuAccess_Image = 0x4000 //!<  Access as image.
};

/**
* @brief  Methods of access for the CPU.
*/
enum CpuAccess
{
    CpuAccess_Read = 0x01, //!<  Read access.
    CpuAccess_Write = 0x02 //!<  Write access.
};

/**
* @brief  Memory priorities.
*/
enum MemoryPriority
{
    MemoryPriority_Low, //!<  Low priority.
    MemoryPirority_Middle, //!<  Middle priority.
    MemoryPriority_High, //!<  High priority.

    MemoryPriority_End
};

/**
* @brief  Tiling modes.
*/
enum TileMode
{
    TileMode_Optimal, //!<  GPU-optimized tiling.
    TileMode_Linear, //!<  Linear tiling.

    TileMode_End
};

/**
* @brief  The shader stage.
*/
enum ShaderStage
{
    ShaderStage_Vertex, //!<  Vertex shader.
    ShaderStage_Hull, //!<  Hull shader.
    ShaderStage_Domain, //!<  Domain shader.
    ShaderStage_Geometry, //!<  Geometry shader.
    ShaderStage_Pixel, //!<  Pixel shader.
    ShaderStage_Compute, //!<  Compute shader.

    ShaderStage_End
};

/**
* @brief  Shader code types.
*/
enum ShaderCodeType
{
    ShaderCodeType_Binary, //!<  Compiled binary.
    ShaderCodeType_Ir, //!<  Intermediate-language representation.
    ShaderCodeType_Source, //!<  Uncompiled source.
    ShaderCodeType_SourceArray, //!<  Uncompiled source array.

    ShaderCodeType_End
};

/**
* @brief  Shader source formats.
*/
enum ShaderSourceFormat
{
    ShaderSourceFormat_Glsl, //!<  GLSL shader language.
    ShaderSourceFormat_Hlsl, //!<  HLSL shader language.

    ShaderSourceFormat_End
};

/**
* @brief  Channel mappings.
*/
enum ChannelMapping
{
    ChannelMapping_Zero, //!<  Channel map with zero.
    ChannelMapping_One, //!<  Channel map with one.
    ChannelMapping_Red, //!<  Channel map with the red component.
    ChannelMapping_Green, //!<  Channel map with the green component.
    ChannelMapping_Blue, //!<  Channel map with the blue component.
    ChannelMapping_Alpha, //!<  Channel map with the alpha component.

    ChannelMapping_End
};

/**
* @brief  Depth-stencil texture fetch modes.
*/
enum DepthStencilFetchMode
{
    DepthStencilFetchMode_DepthComponent, //!<  Fetches the depth component.
    DepthStencilFetchMode_StencilIndex, //!<  Fetches the stencil component.

    DepthStencilFetchMode_End
};

/**
* @brief  Depth-stencil texture clear modes.
*/
enum DepthStencilClearMode
{
    DepthStencilClearMode_Depth = 0x01, //!<  Clears the depth component.
    DepthStencilClearMode_Stencil = 0x02, //!<  Clears the stencil component.
    DepthStencilClearMode_DepthStencil = //!<  Clears the stencil component and the depth component.
        DepthStencilClearMode_Depth | DepthStencilClearMode_Stencil
};

/**
* @brief  Vertex attribute input modes.
*/
enum AttributeInput
{
    AttributeInput_PerVertex, //!<  Input vertex attributes on a per-vertex basis.
    AttributeInput_PerInstance, //!<  Input vertex attributes on a per-instance basis.

    AttributeInput_End
};

/**
* @brief  Shader interface types.
*/
enum ShaderInterfaceType
{
    ShaderInterfaceType_Input, //!<  Input interface.
    ShaderInterfaceType_Output, //!<  Output interface.
    ShaderInterfaceType_Sampler, //!<  Sampler interface.
    ShaderInterfaceType_ConstantBuffer, //!<  Constant buffer interface.
    ShaderInterfaceType_UnorderedAccessBuffer, //!<  Unordered access buffer interface.
    ShaderInterfaceType_Image, //!<  Image interface.
    ShaderInterfaceType_SeparateTexture, //!<  Texture interface when no sampler is included.
    ShaderInterfaceType_SeparateSampler, //!<  Sampler interface when no texture is included.

    ShaderInterfaceType_End
};

/**
* @brief  Queue capabilities.
*/
enum QueueCapability
{
    QueueCapability_Graphics = 0x01, //!<  Has graphics capabilities.
    QueueCapability_Compute = 0x02, //!<  Has computational capabilities.
    QueueCapability_Copy = 0x04 //!<  Has copy capabilities.
};

/**
* @brief  Color components.
*/
enum ColorChannel
{
    ColorChannel_Red, //!<  The red component.
    ColorChannel_Green, //!<  The green component.
    ColorChannel_Blue, //!<  The blue component.
    ColorChannel_Alpha, //!<  The alpha component.

    ColorChannel_End
};

/**
* @brief  Descriptor pool types.
*/
enum DescriptorPoolType
{
    DescriptorPoolType_BufferView, //!<  Buffer view.
    DescriptorPoolType_TextureView, //!<  Texture view.
    DescriptorPoolType_Sampler, //!<  Sampler.

    DescriptorPoolType_End
};

/**
* @brief  Descriptor slot types.
*/
enum DescriptorSlotType
{
    DescriptorSlotType_ConstantBuffer, //!<  Constant buffer.
    DescriptorSlotType_UnorderedAccessBuffer, //!<  Unordered access buffer.
    DescriptorSlotType_TextureSampler, //!<  Texture sampler.

    DescriptorSlotType_End
};

/**
* @brief  Type of pipeline.
*/
enum PipelineType
{
    PipelineType_Graphics, //!<  Graphics pipeline.
    PipelineType_Compute, //!<  Computational pipeline.

    PipelineType_End
};

/**
* @brief  The memory pool attribute.
*/
enum MemoryPoolProperty
{
    MemoryPoolProperty_CpuInvisible = 0x01, //!<  Not visible from the CPU.
    MemoryPoolProperty_CpuUncached = 0x02, //!<  Not cached by the CPU.
    MemoryPoolProperty_CpuCached = 0x04, //!<  Cached by the CPU.
    MemoryPoolProperty_GpuInvisible = 0x08, //!<  Not visible from the GPU.
    MemoryPoolProperty_GpuUncached = 0x10, //!<  Not cached by the GPU.
    MemoryPoolProperty_GpuCached = 0x20, //!<  Cached by the GPU.
    MemoryPoolProperty_ShaderCode = 0x40, //!<  Includes shader code.
    MemoryPoolProperty_Compressible = 0x80 //!<  Supports compressible resources.
};

/**
* @brief  The type of the command buffer.
*/
enum CommandBufferType
{
    CommandBufferType_Direct, //!<  Command buffer directly submitted to the queue.
    CommandBufferType_Nested, //!<  Nested command buffer called from a command buffer.

    CommandBufferType_End
};

/**
* @brief  Buffer state.
*/
enum BufferState
{
    BufferState_Undefined = 0x00, //!<  Undefined state.
    BufferState_DataTransfer = 0x01, //!<  Data transfer state.
    BufferState_CopySource = 0x02, //!<  Copy source state.
    BufferState_CopyDestination = 0x04, //!<  Copy destination state.
    BufferState_VertexBuffer = 0x08, //!<  Vertex buffer state.
    BufferState_IndexBuffer = 0x10, //!<  Index buffer state.
    BufferState_ConstantBuffer = 0x20, //!<  Constant buffer state.
    BufferState_UnorderedAccessBuffer = 0x40, //!<  Unordered access buffer state.
    BufferState_IndirectArgument = 0x80, //!<  Indirect buffer state.
    BufferState_QueryBuffer = 0x0100 //!<  Query buffer state.
};

/**
* @brief  Texture state.
*/
enum TextureState
{
    TextureState_Undefined = 0x00, //!<  Undefined state.
    TextureState_DataTransfer = 0x01, //!<  Data transfer state.
    TextureState_CopySource = 0x02, //!<  Copy source state.
    TextureState_CopyDestination = 0x04, //!<  Copy destination state.
    TextureState_ShaderRead = 0x08, //!<  Graphics shader read state.
    TextureState_ShaderWrite = 0x10, //!<  Graphics shader write state.
    TextureState_ColorTarget = 0x20, //!<  Color target state.
    TextureState_DepthRead = 0x40, //!<  Depth read state.
    TextureState_DepthWrite = 0x80, //!<  Depth write state.
    TextureState_Clear = 0x0100, //!<  Clear state.
    TextureState_ResolveSource = 0x0200, //!<  Multisampling resolution origin state.
    TextureState_ResolveDestination = 0x0400, //!<  Multisampling resolution destination state.
    TextureState_Present = 0x800 //!<  The display state.
};

/**
* @brief  Shader stage bit.
*/
enum ShaderStageBit
{
    ShaderStageBit_Vertex = 0x01, //!<  The vertex shader stage.
    ShaderStageBit_Hull = 0x02, //!<  The Hull shader stage.
    ShaderStageBit_Domain = 0x04, //!<  The domain shader stage.
    ShaderStageBit_Geometry = 0x08, //!<  The geometry shader stage.
    ShaderStageBit_Pixel = 0x10, //!<  The pixel shader stage.
    ShaderStageBit_Compute = 0x20, //!<  The compute shader stage.
    ShaderStageBit_All = ShaderStageBit_Vertex | ShaderStageBit_Hull | ShaderStageBit_Domain
        | ShaderStageBit_Geometry | ShaderStageBit_Pixel | ShaderStageBit_Compute //!<  All shader stages.
};

/**
* @brief  Pipeline stage bit.
*/
enum PipelineStageBit
{
    PipelineStageBit_VertexInput = 0x01, //!<  The vertex input stage.
    PipelineStageBit_VertexShader = 0x02, //!<  The vertex shader stage.
    PipelineStageBit_HullShader = 0x04, //!<  The Hull shader stage.
    PipelineStageBit_DomainShader = 0x08, //!<  The domain shader stage.
    PipelineStageBit_GeometryShader = 0x10, //!<  The geometry shader stage.
    PipelineStageBit_PixelShader = 0x20, //!<  The pixel shader stage.
    PipelineStageBit_RenderTarget = 0x40, //!<  The write to render target stage.
    PipelineStageBit_ComputeShader = 0x80 //!<  The compute shader stage.
};

/**
* @brief  Debug modes.
*/
enum DebugMode
{
    DebugMode_Disable, //!<  Disabled.
    DebugMode_Enable, //!<  Enabled.
    DebugMode_Full, //!<  All debugging features are enabled.

    DebugMode_End
};

/**
* @brief  Query targets.
*/
enum QueryTarget
{
    QueryTarget_Timestamp, //!<  The timestamp.
    QueryTarget_SamplesPassed, //!<  The number of samples passing the fragment test.
    QueryTarget_InputVertices, //!<  The number of input vertices.
    QueryTarget_InputPrimitives, //!<  The number of input primitives.
    QueryTarget_VertexShaderInvocations, //!<  The number of vertex shader calls.
    QueryTarget_GeometryShaderInvocations, //!<  The number of geometry shader calls.
    QueryTarget_GeometryShaderPrimitives, //!<  The number of primitives that are generated with a geometry shader.
    QueryTarget_ClippingInputPrimitives, //!<  The number of primitives that are processed with a clipping stage.
    QueryTarget_ClippingOutputPrimitives, //!<  The number of primitives that are generated with a clipping stage.
    QueryTarget_PixelShaderInvocations, //!<  The number of pixel shader calls.
    QueryTarget_HullShaderInvocations, //!<  The number of hull shader calls.
    QueryTarget_DomainShaderInvocations, //!<  The number of domain shader calls.
    QueryTarget_ComputeShaderInvocations, //!<  The number of compute shader calls.

    QueryTarget_End
};

/**
* @brief  The class for the image copy process.
*/
enum ImageCopyFlag
{
    ImageCopyFlag_LinearFilter = 0x01 //!<  Use linear filtering for scaling when copying.
};

/**
* @brief  Gets the results of shader initialization.
*/
enum ShaderInitializeResult
{
    ShaderInitializeResult_Success = 0, //!<  Shader was initialized successfully.
    ShaderInitializeResult_InvalidType, //!<  Invalid shader code type.
    ShaderInitializeResult_InvalidFormat, //!<  Invalid shader code format.
    ShaderInitializeResult_SetupFailed //!<  Shader setup failed.
};

/**
* @brief  Gets the results of the synchronization process.
*/
enum SyncResult
{
    SyncResult_Success = 0, //!<  Synchronization succeeded.
    SyncResult_TimeoutExpired //!<  The process timed out.
};

/**
* @brief  The result of acting to acquire the scan buffer.
*/
enum AcquireScanBufferResult
{
    AcquireScanBufferResult_Success = 0, //!<  Acquiring the scan buffer succeeded.
    AcquireScanBufferResult_Failed //!<  Acquiring the scan buffer failed.
};

/**
* @brief  Flags for image format properties.
*/
enum ImageFormatPropertyFlag
{
    ImageFormatPropertyFlag_Texture = 0x01, //!<  Can be used as a texture.
    ImageFormatPropertyFlag_ColorTarget = 0x02, //!<  Can be used as a color target.
    ImageFormatPropertyFlag_Image = 0x04, //!<  Can be used as an image.
    ImageFormatPropertyFlag_DepthStencil = 0x08 //! <
};

}
}
