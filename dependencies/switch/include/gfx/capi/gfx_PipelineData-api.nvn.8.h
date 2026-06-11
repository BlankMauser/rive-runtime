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
* @brief  Declarations of API resources for pipeline data (NVN8 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Common-api.nvn.h>
#include <nn/gfx/detail/gfx_State-api.nvn.8.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing the pipeline (NVN8 special edition).
*/
template<>
struct PipelineImplData< ApiVariationNvn8 >
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
    Bit8 nnPipelineType; //!<  The pipeline type represented by <tt>nn::gfx::PipelineType</tt>.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved; //!<  This is a reserved region.
    Bit32 memorySize;

    detail::VertexStateImpl< ApiVariationNvn8 >::DataType nnVertexState;
    detail::BlendStateImpl< ApiVariationNvn8 >::DataType nnBlendState;
    detail::RasterizerStateImpl< ApiVariationNvn8 >::DataType nnRasterizerState;
    detail::DepthStencilStateImpl< ApiVariationNvn8 >::DataType nnDepthStencilState;
    detail::TessellationStateImpl< ApiVariationNvn8 >::DataType nnTessellationState;

    detail::Ptr< const detail::ShaderImpl< ApiVariationNvn8 > > pShader; //!<  Shader.
    detail::Ptr< void > pWorkMemory;

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
