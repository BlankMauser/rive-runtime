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
* @brief  Declarations of API resources for command buffer data (NVN8 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/detail/gfx_Common-api.nvn.h>
#include <nn/gfx/detail/gfx_Buffer-api.nvn.8.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a command buffer (NVN8 special edition).
*/
template<>
struct CommandBufferImplData< ApiVariationNvn8 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized,
        State_Begun
    };

    enum Flag
    {
        Flag_Shared,
        Flag_ConservativeRasterSupported
    };

    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved[ 6 ]; //!<  This is a reserved region.

    detail::Ptr< detail::DeviceImpl< ApiVariationNvn8 > > pNnDevice;

    struct
    {
        char reserved[160];
    }nvnCommandBuffer;

    detail::Ptr< void > pNvnCommandBuffer;
    detail::NvnHandle  hNvnCommandBuffer;
    char reserved2[ 4 ]; //!<  This is a reserved region.

    detail::Ptr< void () > pOutOfCommandMemoryCallback; // Pointer to the callback called when there is insufficient command memory.
    detail::Ptr< void () > pOutOfControlMemoryCallback; //!<  Pointer to the callback called when there is insufficient control memory.

    detail::Ptr< void > userPtr;
};

}
}
