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
* @brief  Declarations of API resources for command buffer data (GL4 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a command buffer (GL4 special edition).
*/
template<>
struct CommandBufferImplData< ApiVariationGl4 >
{
    enum State
    {
        State_NotInitialized,
        State_Initialized,
        State_Begun,
        State_Callback
    };

    Bit8 state; //!<  The state of the object.
    Bit8 commandBufferType; //!<  The type of the command buffer.
    Bit16 queueCapability; //!<  Capabilities of the submit destination queue.
    uint32_t commandMemorySize; //!<  The size of the command memory.
    uint32_t controlMemorySize; //!<  The size of the control memory.
    char reserved[ 4 ]; //!<  This is a reserved region.
    detail::Ptr< detail::DeviceImpl< ApiVariationGl4 > > pGfxDevice; //!<  Pointer to the device.
    detail::Ptr< const void > pCommandList; //!<  A pointer to the command list.
    detail::Ptr< const void > pHeadCommandMemory; //!<  A pointer to the start of the command memory.
    detail::Ptr< void > pCommandMemory; //!<  A pointer to the command memory.
    detail::Ptr< const void > pHeadControlMemory; //!<  A pointer to the start of the control memory.
    detail::Ptr< void > pControlMemory; //!<  A pointer to the control memory.
    detail::Ptr< void () > pOutOfCommandMemoryCallback; //!<  A pointer to a callback called when there is insufficient command memory.
    detail::Ptr< void () > pOutOfControlMemoryCallback; //!<  A pointer to a callback called when there is insufficient control memory.

    detail::Ptr< void > userPtr; //!<  Pointer to the user data.

    char defaultControlMemory[ 40 ]; //!<  The default control memory.
};

}
}
