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
* @brief  Declarations of API resources for state initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Enum.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure that represents the information for initializing a multisample state.
*/
struct MultisampleStateInfoData
{
    enum Flag
    {
        Flag_AlphaToCoverageEnable,
    };
    uint8_t sampleCount; //!<  The number of samples.
    char reserved2; //!<  This is a reserved region.
    nn::util::BitPack16 flag; //!<  The flags.
    uint32_t sampleMask; //!<  The sample mask.

    char reserved[ 8 ]; //!<  This is a reserved region.

    // SampleCoverage
};

/**
* @brief  The structure representing information for initializing a rasterizer state.
*/
struct RasterizerStateInfoData
{
    enum Flag
    {
        Flag_RasterDisable,
        Flag_MultisampleEnable,
        Flag_DepthClipDisable,
        Flag_ScissorEnable
    };

    Bit8 fillMode; //!<  The <tt>nn::gfx::FillMode</tt> representation of the fill mode.
    Bit8 frontFace; //!<  The <tt>nn::gfx::FrontFace</tt> representation of the front face.
    Bit8 cullMode; //!<  The <tt>nn::gfx::CullMode</tt> representation of the culling mode.
    Bit8 primitiveTopologyType; //!<  The <tt>nn::gfx::PrimitiveTopologyType</tt> representation of the primitive topology type.
    nn::util::BitPack16 flag; //!<  The flags.
    Bit8 conservativeRasterizationMode; //!<  The <tt>nn::gfx::ConservativeRasterizationMode</tt> representation of the conservative rasterization mode.
    char reserved2; //!<  This is a reserved region.
    float slopeScaledDepthBias; //!<  The value to add to the pixel depth value, scaled according to the maximum depth slope.
    int32_t depthBias; //!<  The value to add to the pixel depth value.
    float depthBiasClamp; //!<  The maximum value to add to the pixel depth value.
    char reserved3[ 4 ]; //!<  This is a reserved region.

    MultisampleStateInfoData multisample; //!<  The multisample state.

    char reserved[ 24 ]; //!<  This is a reserved region.

    // PointSize
    // LineWidth
    // VertexReuse
};

/**
* @brief  Structure that represents the information for initializing a blend target state.
*/
struct BlendTargetStateInfoData
{
    enum Flag
    {
        Flag_BlendEnable
    };

    nn::util::BitPack8 flag; //!<  The flags.
    Bit8 sourceColorBlendFactor; //!<  The <tt>nn::gfx::BlendFactor</tt> representation of the blend factor for the source color channels.
    Bit8 destinationColorBlendFactor; //!<  The <tt>nn::gfx::BlendFactor</tt> representation of the blend factor for the destination color channels.
    Bit8 colorBlendFunction; //!<  The <tt>nn::gfx::BlendFunction</tt> representation of the color channel blend function.
    Bit8 sourceAlphaBlendFactor; //!<  The <tt>nn::gfx::BlendFactor</tt> representation of the blend factor for the source alpha channel.
    Bit8 destinationAlphaBlendFactor; //!<  The <tt>nn::gfx::BlendFactor</tt> representation of the blend factor for the destination alpha channel.
    Bit8 alphaBlendFunction; //!<  The <tt>nn::gfx::BlendFunction</tt> representation of the alpha channel blend function.
    Bit8 channelMask; //!<  The <tt>nn::gfx::ChannelMask</tt> representation of the channel mask.

    char reserved[ 24 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a blend state.
*/
struct BlendStateInfoData
{
    enum Flag
    {
        Flag_AlphaToCoverageEnable,
        Flag_DualSourceBlendEnable,
        Flag_IndependentBlendEnable,
        Flag_LogicOperationEnable,
    };

    uint8_t blendTargetCount; //!<  The number of blend target states.
    Bit8 logicOperation; //!<  The <tt>nn::gfx::LogicOperation</tt> representation of the logical operation.
    nn::util::BitPack16 flag; //!<  The flags.
    float blendConstant[ 4 ]; //!<  The blend constant.
    char reserved2[ 4 ]; //!<  This is a reserved region.
    detail::Ptr< const BlendTargetStateInfoData > pBlendTargetArray; //!<  The pointer to the array of blend target states.

    char reserved[ 16 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a stencil state.
*/
struct StencilStateInfoData
{
    Bit8 stencilFailOperation; //!<  The <tt>nn::gfx::StencilOperation</tt> representation of the operation to perform when the stencil test fails.
    Bit8 depthFailOperation; //!<  The <tt>nn::gfx::StencilOperation</tt> representation of the operation to perform when the depth test fails.
    Bit8 depthPassOperation; //!<  The <tt>nn::gfx::StencilOperation</tt> representation of the operation to perform when the depth test passes.
    Bit8 comparisonFunction; //!<  The <tt>nn::gfx::ComparisonFunction</tt> representation of the stencil test's comparison function.
    uint8_t stencilRef; //!<  The stencil reference value.

    char reserved[ 11 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a depth stencil state.
*/
struct DepthStencilStateInfoData
{
    enum Flag
    {
        Flag_DepthTestEnable,
        Flag_DepthWriteEnable,
        Flag_StencilTestEnable,
        Flag_DepthBoundsTestEnable
    };

    Bit8 depthComparisonFunction; //!<  The <tt>nn::gfx::ComparisonFunction</tt> representation of the depth test's comparison function.
    uint8_t stencilReadMask; //!<  The mask to apply to stencil read operations.
    uint8_t stencilWriteMask; //!<  The mask to apply to stencil write operations.
    char reserved2; //!<  This is a reserved region.
    nn::util::BitPack16 flag; //!<  The flags.
    char reserved3[ 2 ]; //!<  This is a reserved region.
    StencilStateInfoData frontStencil; //!<  The front face stencil state.
    StencilStateInfoData backStencil; //!<  The back face stencil state.

    char reserved[ 24 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a color target state.
*/
struct ColorTargetStateInfoData
{
    Bit32 format; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the color format.

    char reserved[ 28 ];
};

/**
* @brief  Structure that represents the information for initializing a render target state.
*/
struct RenderTargetStateInfoData
{
    uint8_t colorTargetCount; //!<  The number of color targets.
    char reserved2[ 3 ]; //!<  This is a reserved region.
    Bit32 depthStencilFormat; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the depth stencil format.
    detail::Ptr< const ColorTargetStateInfoData > pColorTargetStateArray; //!<  Pointer to an array of color target states.

    char reserved[ 16 ];
};

/**
* @brief  Structure that represents the information for initializing a vertex attribute state.
*/
struct VertexAttributeStateInfoData
{
    uint8_t semanticIndex; //!<  The semantic index.
    char reserved2; //!<  This is a reserved region.
    int16_t shaderSlot; //!<  The slot number in the shader.
    uint16_t bufferIndex; //!<  The vertex buffer index.
    char reserved3[ 2 ]; //!<  This is a reserved region.
    uint32_t offset; //!<  The offset in the buffer, in bytes.
    Bit32 format; //!<  The <tt>nn::gfx::AttributeFormat</tt> representation of the vertex attribute format.
    detail::Ptr< const char > pName; //!<  Pointer to the name.

    char reserved[ 16 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a vertex buffer state.
*/
struct VertexBufferStateInfoData
{
    int32_t stride; //!<  The stride.
    uint32_t divisor; //!<  The instance divisor.

    char reserved[ 8 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a vertex state.
*/
struct VertexStateInfoData
{
    uint16_t attributeCount; //!<  The number of vertex attributes.
    uint16_t bufferCount; //!<  The number of vertex buffers.
    char reserved2[ 4 ]; //!<  This is a reserved region.
    detail::Ptr< const VertexAttributeStateInfoData > pAttributeArray; //!<  Pointer to the array of vertex attribute states.
    detail::Ptr< const VertexBufferStateInfoData > pBufferArray; //!<  The pointer to the array of vertex buffer states.

    char reserved[ 24 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a blend state.
*/
struct TessellationStateInfoData
{
    uint16_t patchControlPointCount; //!<  The number of patch control points.

    char reserved[ 30 ];
};

/**
* @brief  Structure that represents information for initializing a depth range.
*/
struct DepthRangeInfoData
{
    float minDepth; //!<  The minimum depth.
    float maxDepth; //!<  The maximum depth.

    char reserved[ 8 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a viewport state.
*/
struct ViewportStateInfoData
{
    float originX; //!<  The x-coordinate of the origin.
    float originY; //!<  The y-coordinate of the origin.
    float width; //!<  The width.
    float height; //!<  The height.

    DepthRangeInfoData depthRange; //!<  The depth range.

    char reserved[ 16 ];
};

/**
* @brief  Structure that represents the information for initializing a scissor state.
*/
struct ScissorStateInfoData
{
    uint32_t originX; //!<  The x-coordinate of the origin.
    uint32_t originY; //!<  The y-coordinate of the origin.
    uint32_t width; //!<  The width.
    uint32_t height; //!<  The height.

    char reserved[ 16 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a viewport scissor state.
*/
struct ViewportScissorStateInfoData
{
    enum Flag
    {
        Flag_ScissorEnable
    };

    nn::util::BitPack8 flag; //!<  The flags.
    char reserved2; //!<  This is a reserved region.
    uint16_t viewportCount; //!<  The number of viewports.
    uint16_t scissorCount; //!<  The number of scissors.
    char reserved3[ 2 ]; //!<  This is a reserved region.
    detail::Ptr< const ViewportStateInfoData > pViewportArray; //!<  Pointer to the viewport state array.
    detail::Ptr< const ScissorStateInfoData > pScissorArray; //!<  Pointer to the scissor state array.

    char reserved[ 8 ]; //!<  This is a reserved region.
};

}
}
