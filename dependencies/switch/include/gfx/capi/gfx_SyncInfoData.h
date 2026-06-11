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
* @brief  Declarations of API resources for synchronous object initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing information for initializing a fence.
*/
struct FenceInfoData
{
    char reserved[ 16 ]; //!< This is a reserved region.
};

/**
* @brief  The structure representing information for initializing a semaphore.
*/
struct SemaphoreInfoData
{
    char reserved[ 16 ]; //!< This is a reserved region.
};

}
}
