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
* @brief  Declarations of API resources for the data in the information used to initialize a descriptor pool.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure representing the information for initializing a descriptor pool.
*/
struct DescriptorPoolInfoData
{
    Bit8 descriptorPoolType; //!<  The type of the descriptor pool, as represented by <tt>nn::gfx::DescriptorPoolType</tt>.
    char reserved2[ 3 ]; //!<  This is a reserved region.
    uint32_t slotCount; //!<  The number of slots storing descriptors.

    char reserved[ 24 ]; //!<  This is a reserved region.
};

}
}
