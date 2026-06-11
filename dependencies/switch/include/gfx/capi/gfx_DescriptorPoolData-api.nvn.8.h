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
* @brief  Declarations of API resources for descriptor pool data (NVN8 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a descriptor pool (NVN8 special edition).
*/
template<>
struct DescriptorPoolImplData< ApiVariationNvn8 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized,
        State_Begun
    };

    enum Flag
    {
        Flag_Shared
    };

    Bit8 state; //!<  The state of the object.
    Bit8 descriptorPoolType; //!<  The type of the descriptor pool, as represented by <tt>nn::gfx::DescriptorPoolType</tt>.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved; //!<  This is a reserved region.
    int32_t slotCount; //!<  The number of descriptor pool slots.
    int32_t reservedSlots;
    char reserved2[ 4 ]; //!<  This is a reserved region.

    detail::Ptr< void > pDescriptorPool;

    NN_ALIGNAS( 8 ) char nvnDescriptorPool[ 32 ];

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
