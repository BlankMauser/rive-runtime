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
* @brief  Declarations of API resources for pipeline data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>

#include <nn/gfx/detail/gfx_Common-api.gl.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Shader-api.gl.4.h>
#include <nn/gfx/detail/gfx_State-api.gl.4.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing the pipeline (GL4 special edition).
*/
template<>
struct PipelineImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    enum Flag
    {
        Flag_HasTessellationState
    };

    Bit8 state; //!<  The state of the object.
    Bit8 pipelineType; //!<  The pipeline type.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved; //!<  This is a reserved region.
    uint32_t memorySize; //!<  The size of the working memory.
    detail::RasterizerStateImpl< ApiVariationGl4 >::DataType rasterizerState; //!<  Rasterizer state.
    detail::BlendStateImpl< ApiVariationGl4 >::DataType blendState; //!<  Blend state.
    detail::DepthStencilStateImpl< ApiVariationGl4 >::DataType depthStencilState; //!<  Depth stencil state.
    detail::VertexStateImpl< ApiVariationGl4 >::DataType vertexState; //!<  Vertex state.
    detail::TessellationStateImpl< ApiVariationGl4 >::DataType tessellationState; //!<  Tessellation state.
    detail::Ptr< const detail::ShaderImpl< ApiVariationGl4 > > pShader; //!<  Shader.
    detail::Ptr< void > pWorkMemory; //!<  A pointer to the working memory.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
