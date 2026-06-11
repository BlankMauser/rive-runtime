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
* @brief  Declarations of API resources for the data in the information used to initialize a buffer.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing information for initializing a buffer.
*/
struct BufferInfoData
{
    uint32_t size; //!<  The byte size of the buffer.
    Bit32 gpuAccessFlag; //!<  A combination of <tt>nn::gfx::GpuAccess</tt> values representing the GPU access modes.

    char reserved[ 8 ]; //!<  This is a reserved region.
};

/**
* @brief  The structure representing the information for initializing a buffer texture view.
*/
struct BufferTextureViewInfoData
{
    Bit32 format; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the image format used to parse the content of the buffer.
    uint32_t offset; //!<  The offset, in bytes, from the start of the buffer.
    uint32_t size; //!<  The size, in bytes, of the buffer to reference.
    char reserved2[ 4 ]; //!<  This is a reserved region.
    detail::Ptr< const void > pBuffer; //!<  The pointer to the buffer to reference.

    char reserved[ 8 ];
};

}
}
