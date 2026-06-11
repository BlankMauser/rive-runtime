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
* @brief  Declarations of API resources for sampler initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure that represents the information for initializing a sampler.
*/
struct SamplerInfoData
{
    Bit8 addressU; //!<  The <tt>nn::gfx::TextureAddressMode</tt> representation of the u-coordinates' address mode.
    Bit8 addressV; //!<  The <tt>nn::gfx::TextureAddressMode</tt> representation of the v-coordinates' address mode.
    Bit8 addressW; //!<  The <tt>nn::gfx::TextureAddressMode</tt> representation of the w-coordinates' address mode.
    Bit8 comparisonFunction; //!<  The <tt>nn::gfx::ComparisonFunction</tt> representation of the comparison function.
    Bit8 borderColorType; //!<  The <tt>nn::gfx::BorderColorType</tt> representation of the border color type.
    uint8_t maxAnisotropy; //!<  Maximum sample count for anisotropic filtering.
    Bit16 filterMode; //!<  The <tt>nn::gfx::FilterMode</tt> representation of the filter mode.
    float minLod; //!<  Minimum mipmap level of detail.
    float maxLod; //!<  Maximum mipmap level of detail.
    float lodBias; //!<  Mipmap level offset value.

    char reserved[ 12 ]; //!<  This is a reserved region.
};

}
}
