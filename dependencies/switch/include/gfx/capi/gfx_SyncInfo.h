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
* @brief  Declarations of API resources for synchronization object initialization information.
*/

#pragma once

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_SyncInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  The class representing information for initializing a fence.
*/
class FenceInfo
    : public detail::DataContainer< FenceInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - Each parameter is initialized to zero.
*/
    FenceInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  Helper function to set each parameter to the default value.
*
* @post
*  - Each parameter is set.
*
* @details
*  The values that are set are not the same as zero-initialization.
*/
    void SetDefault() NN_NOEXCEPT;
};

/**
* @brief  The class representing information for initializing a semaphore.
*/
class SemaphoreInfo
    : public detail::DataContainer< SemaphoreInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - Each parameter is initialized to zero.
*/
    SemaphoreInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  Helper function to set each parameter to the default value.
*
* @post
*  - Each parameter is set.
*
* @details
*  The values that are set are not the same as zero-initialization.
*/
    void SetDefault() NN_NOEXCEPT;
};

}
}
