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
* @brief  Declarations of API resources for swap chain data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#if !defined( NN_BUILD_CONFIG_OS_SUPPORTS_WIN32 )
    #error "The OS type is not set to Win32."
#endif

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>
#include <nn/gfx/gfx_TextureData-api.gl.4.h>

#include <nn/gfx/detail/gfx_Common-api.gl.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a swap chain (GL4 special edition).
*/
template<>
struct SwapChainImplData< ApiVariationGl4 >
{
    typedef void* WndHandle;
    typedef void* DcHandle;

    enum State
    {
        State_NotInitialized,
        State_Initialized
    };

    enum Flag
    {
        Flag_Acquired,
        Flag_Copied
    };

    static const int MaxScanBuffer = 6;

    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flag; //!<  The flags.
    int8_t scanBufferCount; //!<  The number of scan buffers.
    int8_t currentScanBufferIndex; //!<  The current scan buffer index.
    char reserved[ 4 ]; //!<  This is a reserved region.
    detail::Ptr< void > hWnd; //!<  The window handle.
    detail::Ptr< void > hDc; //!<  The device context.
    detail::Ptr< detail::DeviceImpl< ApiVariationGl4 > > pGfxDevice; //!<  Pointer to the device.

    TextureImplData< ApiVariationGl4 > scanBuffers[ MaxScanBuffer ]; // The scan buffer.
    ColorTargetViewImplData< ApiVariationGl4 > scanBufferViews[ MaxScanBuffer ]; //!<  The scan buffer view.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
