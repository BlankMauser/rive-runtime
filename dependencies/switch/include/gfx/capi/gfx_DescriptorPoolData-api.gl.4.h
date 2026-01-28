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
* @brief  Declarations of API resources for descriptor pool data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>

#include <nn/gfx/detail/gfx_Common-api.gl.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a descriptor pool (GL4 special edition).
*/
template<>
struct DescriptorPoolImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized,
        State_Begun
    };

    Bit8 state; //!<  The state of the object.
    Bit8 descriptorPoolType; //!<  The descriptor pool type.
    char reserved[ 2 ]; //!<  This is a reserved region.
    uint32_t slotCount; //!<  The number of descriptor pool slots.
    detail::Ptr< void > pMemory; //!<  A pointer to descriptor pool memory.

    detail::Ptr< void > userPtr; //!<  A user pointer.
};

}
}
