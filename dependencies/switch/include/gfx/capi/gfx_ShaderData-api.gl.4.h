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
* @brief  Declarations of API resources for shader data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>
#include <nn/gfx/gfx_ShaderInfoData.h>

#include <nn/gfx/detail/gfx_Common-api.gl.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a shader (GL4 special edition).
*/
template<>
struct ShaderImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    enum Flag
    {
        Flag_SeparationEnable = ShaderInfoData::Flag_SeparationEnable,
        Flag_Shared
    };

    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved[ 2 ]; //!<  This is a reserved region.
    union
    {
        detail::GlHandle hCombinedProgram; //!<  Combined program handle.
        detail::GlHandle hVertexProgram; //!<  Vertex program handle.
    };
    detail::GlHandle hHullProgram; //!<  The hull program handle.
    detail::GlHandle hDomainProgram; //!<  The domain program handle.
    detail::GlHandle hGeometryProgram; //!<  The geometry program handle.
    detail::GlHandle hPixelProgram; //!<  The pixel program handle.
    detail::GlHandle hComputeProgram; //!<  The compute program handle.
    char reserved2[ 4 ]; //!<  This is a reserved region.
    detail::Ptr< detail::DeviceImpl< ApiVariationGl4 > > pGfxDevice; //!<  Pointer to the device.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
