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
* @brief  Declarations of API resources for texture data (NVN8 special edition).
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
* @brief  The structure representing a texture (NVN8 special edition).
*/
template<>
struct TextureImplData< ApiVariationNvn8 >
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

    detail::Ptr< void > pNvnTexture; //!<  Pointer to an nvn texture.

    NN_ALIGNAS( 8 ) char nvnTexture[ 192 ]; //!<  The nvn texture storage.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

/**
* @brief  The structure representing a texture view (NVN8 special edition).
*/
template<>
struct TextureViewImplData< ApiVariationNvn8 >
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

    detail::Ptr< void > pNvnTexture; //!<  Pointer to an nvn texture.
    detail::Ptr< void > pNvnTextureView; //!<  Pointer to an nvn texture view.
    NN_ALIGNAS( 8 ) char nvnTextureView[ 40 ]; // The nvn texture view storage.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

/**
* @brief  The structure representing a color target view (NVN8 special edition).
*/
template<>
struct ColorTargetViewImplData< ApiVariationNvn8 >
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

    detail::Ptr< void > pNvnTexture; //!<  Pointer to an nvn texture.
    detail::Ptr< void > pNvnTextureView; //!<  Pointer to an nvn texture view.
    NN_ALIGNAS( 8 ) char nvnTextureView[ 40 ]; //!<  The nvn texture view storage.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

/**
* @brief  The structure representing a depth stencil view (NVN8 special edition).
*/
template<>
struct DepthStencilViewImplData< ApiVariationNvn8 >
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

    detail::Ptr< void > pNvnTexture; //!<  Pointer to an nvn texture.
    detail::Ptr< void > pNvnTextureView; //!<  Pointer to an nvn texture view.
    NN_ALIGNAS( 8 ) char nvnTextureView[ 40 ]; //!<  The nvn texture view storage.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
