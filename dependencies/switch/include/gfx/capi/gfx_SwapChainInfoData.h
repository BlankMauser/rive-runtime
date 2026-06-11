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
* @brief  Declarations of API resources for swap chain initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace vi {

class Layer;

}
}

namespace nn {
namespace gfx {

/**
* @brief  Represents the information for initializing a swap chain.
*/
struct SwapChainInfoData
{
    uint8_t bufferCount; //!<  The number of scan buffers.
    char reserved2[ 3 ]; //!<  This is a reserved region.
    Bit32 format; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the scan buffer format.
    uint32_t width; //!<  The width of the scan buffer.
    uint32_t height; //!<  The height of the scan buffer.

    char reserved3[ 8 ]; //!<  This is a reserved region.
    detail::Ptr< nn::vi::Layer > pLayer; //!<  Pointer to the layer.

    char reserved[ 30 ]; //!<  This is a reserved region.
};

}
}
