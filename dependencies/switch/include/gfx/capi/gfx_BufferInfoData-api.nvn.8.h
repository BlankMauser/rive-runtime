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
* @brief  Declarations of API resources for the data in the information used to initialize a buffer (NVN8 special edition).
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
* @brief  The structure representing information for initializing a buffer (NVN8 special edition).
*/
template<>
struct BufferInfoImplData< ApiVariationNvn8 >
{
    NVNbufferBuilder nvnBufferBuilder; //!<  The <tt>nvn</tt> buffer builder.
    uint32_t size; //!<  The byte size of the buffer.
    Bit32 gpuAccessFlags; //!<  A combination of <tt>nn::gfx::GpuAccess</tt> values representing the GPU access modes.
};

}
}
