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
* @brief  Declarations of API resources for buffer data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>

#include <nn/gfx/detail/gfx_Common-api.gl.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing <tt>Buffer</tt> (GL4 special edition).
*/
template<>
struct BufferImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    enum Flag
    {
        Flag_Shared,
        Flag_FlushExplicit
    };

    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved[ 2 ]; //!<  This is a reserved region.
    detail::GlHandle hBuffer; //!<  The buffer handle.
    detail::Ptr< detail::DeviceImpl< ApiVariationGl4 > > pGfxDevice; //!<  Pointer to the device.
    detail::Ptr< void > pMapped; //!<  The map pointer.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

/**
* @brief  The structure representing <tt>BufferTextureView</tt>. (GL4 special edition.)
*/
template<>
struct BufferTextureViewImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    enum Flag
    {
        Flag_Shared
    };

    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved[ 2 ]; //!<  This is a reserved region.

    detail::GlHandle hBufferTexture; //!<  The buffer texture handle.
};

}
}
