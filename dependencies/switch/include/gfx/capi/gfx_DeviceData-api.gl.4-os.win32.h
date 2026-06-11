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
* @brief  Declarations of API resources for device data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#if !defined( NN_BUILD_CONFIG_OS_SUPPORTS_WIN32 )
    #error "The OS type is not set to Win32."
#endif

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>
#include <nn/gfx/gfx_DeviceInfoData.h>

#include <nn/gfx/detail/gfx_Common-api.gl.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a device (GL4 special edition).
*/
template<>
struct DeviceImplData< ApiVariationGl4 >
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
    Bit8 debugMode; //!<  Debug mode.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved; //!<  This is a reserved region.
    uint32_t maxColorAttachments; //!<  Maximum number of color attachments.
    uint32_t alignmentConstantBuffer; //!<  Alignment of the constant buffer.
    uint32_t alignmentUnorderedAccessBuffer; //!<  Alignment of the unordered access buffer.
    detail::Ptr< void > hWnd; //!<  The window handle.
    detail::Ptr< void > hDc; //!<  The device context.
    detail::GlRenderingContext renderingContext; //!<  The rendering context.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
