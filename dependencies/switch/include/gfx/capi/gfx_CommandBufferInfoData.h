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
* @brief  Declarations of API resources for the data in the information used to initialize a command buffer.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing the information for initializing a command buffer.
*/
struct CommandBufferInfoData
{
    Bit8 commandBufferType; //!<  The <tt>nn::gfx::CommandBufferType</tt> representation of the command buffer type.
    char reserved2; //!<  This is a reserved region.
    Bit16 queueCapability; //!<  A combination of <tt>nn::gfx::QueueCapability</tt> values representing the queue features to be presented.

    char reserved[ 28 ]; //!<  This is a reserved region.
};

}
}
