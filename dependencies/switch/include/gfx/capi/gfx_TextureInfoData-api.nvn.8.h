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
* @brief  Declarations of API resources for the data in the information used to initialize a texture (NVN8 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nvn/nvn.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>

#include <nn/gfx/detail/gfx_Common-api.nvn.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing information for initializing a texture (NVN8 special edition).
*/
template<>
struct TextureInfoImplData< ApiVariationNvn8 >
{
    NVNtextureBuilder nvnTextureBuilder; //!<  The <tt>nvn</tt> texture builder.
    Bit8 imageStorageDimension; //!<  The <tt>nn::gfx::ImageStorageDimension</tt> representation of the image (data) dimensions.
    char reserved; //!<  This is a reserved region.
    uint16_t multisampleCount; //!<  The number of multisamples.
    Bit16 tileMode; //!<  The <tt>nn::gfx::TileMode</tt> representation of the tiling mode.
    char reserved2[ 2 ]; //!<  This is a reserved region.
    uint32_t arrayLength; //!<  The length of the array.
    Bit32 gpuAccessFlags; //!<  A combination of <tt>nn::gfx::GpuAccess</tt> values representing the GPU access modes.
    Bit32 imageFormat; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the image format.
    uint32_t width; //!<  The width.
    uint32_t height; //!<  The height.
    uint32_t depth; //!<  The depth.
};

}
}
