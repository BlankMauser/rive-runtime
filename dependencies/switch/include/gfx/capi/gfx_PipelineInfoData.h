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
* @brief  Declarations of API resources for pipeline initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

struct RasterizerStateInfoData;
struct BlendStateInfoData;
struct DepthStencilStateInfoData;
struct RenderTargetStateInfoData;
struct VertexStateInfoData;
struct TessellationStateInfoData;

/**
* @brief  The structure representing the information for initializing a graphics pipeline.
*/
struct GraphicsPipelineInfoData
{
    detail::Ptr< const RasterizerStateInfoData > pRasterizerState; //!<  Pointer to the rasterizer state.
    detail::Ptr< const BlendStateInfoData > pBlendState; //!<  Pointer to the blend state.
    detail::Ptr< const DepthStencilStateInfoData > pDepthStencilState; //!<  Pointer to the depth stencil state.
    detail::Ptr< const RenderTargetStateInfoData > pRenderTargetState; //!<  Pointer to the render target state.
    detail::Ptr< const VertexStateInfoData > pVertexState; //!<  Pointer to the vertex state.
    detail::Ptr< const void > pShader; //!<  Pointer to the shader.
    detail::Ptr< const TessellationStateInfoData > pTessellationState; //!<  Pointer to the tessellation state.

    char reserved[ 16 ]; //!<  This is a reserved region.
};

/**
* @brief  The structure representing the information for initializing a compute pipeline.
*/
struct ComputePipelineInfoData
{
    detail::Ptr< const void > pShader; //!<  Pointer to the shader.

    char reserved[ 24 ]; //!<  This is a reserved region.
};

}
}
