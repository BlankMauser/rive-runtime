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
* @brief  Declarations for API resources for state data (NVN8 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>
#include <nn/gfx/gfx_StateInfoData.h>

#include <nn/gfx/detail/gfx_Declare.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a rasterizer state (NVN8 special edition).
*/
template<>
struct RasterizerStateImplData< ApiVariationNvn8 >
{
    // NVN State object containers.
    Bit32 nvnPolygonState;
    char nvnMultisampleState[ 24 ];

    Bit32 nvnSampleMask;
    float nvnDepthBias;
    float nvnDepthBiasClamp;
    float nvnSlopeScaledDepthBias;

    enum Flag
    {
        Flag_MultisampleEnabled,
        Flag_DepthClipEnabled,
        Flag_RasterEnabled,
        Flag_ConservativeRasterEnabled
    };

    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags;
    char reserved[ 2 ]; //!<  This is a reserved region.
};

/**
* @brief  The structure representing a blend state (NVN8 special edition).
*/
template<>
struct BlendStateImplData< ApiVariationNvn8 >
{
    detail::Ptr< void > pNvnBlendStateData;

    Bit32 nvnColorState;
    Bit32 nvnChannelMaskState;

    float nvnBlendConstant[ 4 ];
    Bit32 memorySize;

    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    Bit8 state; //!<  The state of the object.
    Bit8 targetCount;
    char reserved[ 2 ]; //!<  This is a reserved region.
};

/**
* @brief  The structure representing a depth stencil state (NVN8 special edition).
*/
template<>
struct DepthStencilStateImplData< ApiVariationNvn8 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    enum Flag
    {
        Flag_DepthBoundsTestEnable = DepthStencilStateInfoData::Flag_DepthBoundsTestEnable
    };

    char nvnDepthStencilState[ 8 ];
    Bit32 nvnStencilValueMask;
    Bit32 nvnStencilMask;
    Bit32 nvnStencilBackRef;
    Bit32 nvnStencilFrontRef;

    Bit8 state; //!<  The state of the object.
    char reserved; //!<  This is a reserved region.
    nn::util::BitPack16 flag;

};

/**
* @brief  The structure representing the vertex state (NVN8 special edition).
*/
template<>
struct VertexStateImplData< ApiVariationNvn8 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    Bit8 state; //!<  The state of the object.
    char reserved[ 3 ]; //!<  This is a reserved region.
    int32_t vertexStreamStateCount;
    int32_t vertexAttributeStateCount;
    uint32_t memorySize;

    detail::Ptr< void > pNvnVertexStreamState;
    detail::Ptr< void > pNvnVertexAttribState;
};

template<>
struct TessellationStateImplData< ApiVariationNvn8 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    Bit8 state;
    char reserved[ 3 ]; //!<  This is a reserved region.
    uint32_t patchSize;
};

/**
* @brief  The structure representing a viewport scissor state (NVN8 special edition).
*/
template<>
struct ViewportScissorStateImplData< ApiVariationNvn8 >
{
    detail::Ptr< void > pWorkMemory; //!<  A pointer to the working memory.
    // pWorkMemory
    //    float viewportArray[ viewportCount * 4 ];
    //    double depthRangeArray[ viewportCount * 2 ];
    //    int32_t scissorArray[ viewportCount * 4 ];

    int32_t viewportCount; //!<  The number of viewports.
    uint32_t memorySize; //!<  The working memory size, in bytes.

    float viewport[ 4 ];
    double depthRange[ 2 ];
    int32_t scissor[ 4 ];

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
};

}
}
