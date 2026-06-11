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
* @brief  Declarations of API resources for buffer data (NVN8 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>
#include <nn/gfx/detail/gfx_Common-api.nvn.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing <tt>Buffer</tt> (NVN8 special edition).
*/
template<>
struct BufferImplData< ApiVariationNvn8 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    enum Flag
    {
        Flag_Shared,
        Flag_CpuCached
    };

    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved[ 6 ]; //!<  This is a reserved region.

    detail::Ptr< void > pNvnBuffer; //!<  Pointer to the <tt>nvn</tt> buffer.

    NN_ALIGNAS( 8 ) char nvnBuffer[ 48 ]; // NVNbuffer structure.

    detail::Ptr< void > userPtr; //!<  User pointer.
};

/**
* @brief  The structure representing <tt>BufferTextureView</tt> (NVN8 special edition).
*/
template<>
struct BufferTextureViewImplData< ApiVariationNvn8 >
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
    char reserved[ 6 ]; //!<  This is a reserved region.

    char nvnTexture[ 192 ]; //!<  An <tt>nvn</tt> texture.

    detail::Ptr< void > pNvnTexture; //!<  Pointer to an <tt>nvn</tt> texture.
};

}
}
