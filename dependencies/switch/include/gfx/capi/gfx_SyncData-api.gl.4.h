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
* @brief  Declarations of API resources for synchronization data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a fence (GL4 special edition).
*/
template<>
struct FenceImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    enum Flag
    {
        Flag_Signaled
    };
    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved[ 6 ]; //!<  This is a reserved region.
    detail::Ptr< void > glSync; //!<   Synchronization object.
    detail::Ptr< detail::QueueImpl< ApiVariationGl4 > > pQueue; //!<   Pointer to the queue.
};

/**
* @brief  The structure representing a semaphore (GL4 special edition).
*/
template<>
struct SemaphoreImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized
    };
    enum Flag
    {
        Flag_Signaled
    };
    Bit8 state; //!<  The state of the object.
    nn::util::BitPack8 flags; //!<  The flags.
    char reserved[ 6 ]; //!<  This is a reserved region.
    detail::Ptr< void > glSync; //!<   Synchronization object.
    detail::Ptr< detail::QueueImpl< ApiVariationGl4 > > pQueue; //!<   Pointer to the queue.
};

}
}
