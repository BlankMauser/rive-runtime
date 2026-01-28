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
* @brief  Declarations for API resources for state data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>
#include <nn/gfx/gfx_StateInfoData.h>

#include <nn/gfx/detail/gfx_Common-api.gl.h>
#include <nn/gfx/detail/gfx_Declare.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a rasterizer state (GL4 special edition).
*/
template<>
struct RasterizerStateImplData< ApiVariationGl4 >
{
    enum Flag
    {
        Flag_CullEnable,
        Flag_RasterDisable,
        Flag_MultisampleEnable,
        Flag_DepthClampEnable,
        Flag_PolygonOffsetEnable,
        Flag_ConservativeRasterEnable
    };
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    Bit8 state; //!<  The state of the object.
    char reserved; //!<  This is a reserved region.
    nn::util::BitPack16 flag; //!<  The flags.
    detail::GlEnum polygonMode; //!<  The polygon mode.
    detail::GlEnum frontFace; //!<  The front face.
    detail::GlEnum cullFace; //!<  The culling mode.
    float slopeScaledDepthBias; //!<  The value to add to the depth value, scaled by the maximum depth.
    float depthBias; //!<  The value to add to the depth value.
    uint32_t sampleMask; //!<  The sample mask.
    float depthBiasClamp; //!<  The maximum value to add to the depth value.
};

/**
* @brief  The structure representing a blend state (GL4 special edition).
*/
template<>
struct BlendStateImplData< ApiVariationGl4 >
{
/**
    * The structure representing a blend target state (GL4 special edition).
*/
    struct BlendTargetState
    {
        enum Flag
        {
            Flag_BlendEnable = BlendTargetStateInfoData::Flag_BlendEnable
        };

        nn::util::BitPack8 flag; //!<  The flags.
        Bit8 colorMask; //!<  The color mask.
        char reserved[ 2 ]; //!<  This is a reserved region.
        detail::GlEnum srcRGB; //!<  The blend factor of the source color channels.
        detail::GlEnum dstRGB; //!<  The blend factor of the destination color channels.
        detail::GlEnum srcAlpha; //!<  The blend factor of the source alpha channel.
        detail::GlEnum dstAlpha; //!<  The blend factor of the destination alpha channel.
        detail::GlEnum modeRGB; //!<  The color channel blend function.
        detail::GlEnum modeAlpha; //!<  The alpha channel blend function.
    };

    enum Flag
    {
        Flag_AlphaToCoverageEnable = BlendStateInfoData::Flag_AlphaToCoverageEnable,
        Flag_IndependentBlendEnable = BlendStateInfoData::Flag_IndependentBlendEnable,
        Flag_LogicOpEnable = BlendStateInfoData::Flag_LogicOperationEnable
    };
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    Bit8 state; //!<  The state of the object.
    char reserved; //!<  This is a reserved region.
    nn::util::BitPack16 flag; //!<  The flags.
    detail::GlEnum logicOp; //!<  The logic operation.
    float blendColor[ 4 ]; //!<  The blend constant.
    int32_t blendTargetCount; //!<  The number of blend targets.
    uint32_t memorySize; //!<  The working memory size, in bytes.
    detail::Ptr< BlendTargetState > pTargetArray; //!<  The pointer to the array of blend target states.
};

/**
* @brief  The structure representing a depth stencil state (GL4 special edition).
*/
template<>
struct DepthStencilStateImplData< ApiVariationGl4 >
{
/**
* @brief  The structure representing a stencil state (GL4 special edition).
*/
    struct StencilState
    {
        detail::GlEnum sfail; //!<  The operation when the stencil test fails.
        detail::GlEnum dpfail; //!<  The operation when the depth test fails.
        detail::GlEnum dppass; //!<  The operation when the depth test succeeds.
        detail::GlEnum func; //!<  The stencil test comparison function.
        int32_t ref; //!<  The stencil reference value.
        uint32_t mask; //!<  The stencil mask.
    };

    enum Flag
    {
        Flag_DepthTestEnable = DepthStencilStateInfoData::Flag_DepthTestEnable,
        Flag_DepthWriteEnable = DepthStencilStateInfoData::Flag_DepthWriteEnable,
        Flag_StencilTestEnable = DepthStencilStateInfoData::Flag_StencilTestEnable,
        Flag_DepthBoundsTestEnable = DepthStencilStateInfoData::Flag_DepthBoundsTestEnable
    };
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    Bit8 state; //!<  The state of the object.
    char reserved; //!<  This is a reserved region.
    nn::util::BitPack16 flag; //!<  The flags.
    detail::GlEnum depthFunc; //!<  The depth test comparison function.
    StencilState frontStencil; //!<  The front face stencil state.
    StencilState backStencil; //!<  The back face stencil state.
};

/**
* @brief  The structure representing the vertex state (GL4 special edition).
*/
template<>
struct VertexStateImplData< ApiVariationGl4 >
{
/**
* @brief  The structure representing the vertex attribute state (GL4 special edition).
*/
    struct AttributeState
    {
        detail::GlBool normalized; //!<  Whether it is normalized.
        char reserved[ 3 ]; //!<  This is a reserved region.
        int32_t slot; //!<  The slot number in the shader.
        int32_t size; //!<  The number of elements.
        detail::GlEnum type; //!<  The vertex attribute type.
        uint32_t offset; //!<  The offset in the buffer, in bytes.
        uint32_t bindingIndex; //!<  The buffer index.
        Bit32 typeFormat; //!<  The vertex attribute format.
    };
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    Bit8 state; //!<  The state of the object.
    char reserved[ 3 ]; //!<  This is a reserved region.
    int32_t attributeCount; //!<  The number of vertex attributes.
    int32_t bufferCount; //!<  The number of vertex buffers.
    uint32_t memorySize; //!<  The size of the working memory.
    detail::Ptr< void > pWorkMemory; //!<  A pointer to the working memory.

    // pWorkMemory
    //    AttributeState[ attributeCount ]
    //    uint32_t[ bufferCount ]
};

/**
* @brief  The structure representing a tessellation state (GL4 special edition).
*/
template<>
struct TessellationStateImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    Bit8 state; //!<  The state of the object.
    char reserved[ 3 ]; //!<  This is a reserved region.
    int32_t patchControlPointCount; //!<  The number of patch control points.
};

/**
* @brief  The structure representing a viewport scissor state (GL4 special edition).
*/
template<>
struct ViewportScissorStateImplData< ApiVariationGl4 >
{
    enum Flag
    {
        Flag_ScissorEnable = ViewportScissorStateInfoData::Flag_ScissorEnable
    };
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flag; //!<  The flags.
    char reserved[ 2 ]; //!<  This is a reserved region.
    int32_t viewportCount; //!<  The number of viewports.
    uint32_t memorySize; //!<  The working memory size, in bytes.
    char reserved2[ 4 ]; //!<  This is a reserved region.
    float viewport[ 4 ];
    double depthRange[ 2 ];
    int32_t scissor[ 4 ];
    detail::Ptr< void > pWorkMemory; //!<  A pointer to the working memory.
};

}
}
