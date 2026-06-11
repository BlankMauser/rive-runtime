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
* @brief  Declarations for API resources related to synchronization.
*/

#pragma once

#include <nn/nn_TimeSpan.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_SyncInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_Sync-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_Sync-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_Sync-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_Sync-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_Sync-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_Sync-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a fence.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TFence
    : public detail::FenceImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TFence );

    typedef detail::FenceImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the fence.
*/
    typedef FenceInfo InfoType;

/**
* @brief  Constructor.
*/
    TFence() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a fence.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - Fence is not initialized.
*
* @post
*  - Fence is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys a fence.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - Fence is initialized.
*
* @post
*  - Fence is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Determines whether a fence is in a signaled state.
*
* @return
*  Returns a Boolean value representing whether the fence is in a signaled state.
*
* @pre
*  - The fence is set in the queue.
*/
    bool IsSignaled() NN_NOEXCEPT
    {
        return Impl::IsSignaled();
    }

/**
* @brief  Synchronizes fences to a signaled state.
*
* @param[in] timeout  Maximum length of time to wait for synchronization.
*
* @return  Returns the synchronous processing result.
* @retval SyncResult_Success  Succeeded.
* @retval SyncResult_TimeoutExpired  The time specified by <tt><var>timeout</var></tt> passed before the fence went into a signaled state.
*
* @pre
*  - The fence is set in the queue.
*
* @details
*  Control is not returned until either the fence goes into a signaled state or the specified time has passed.
*/
    SyncResult Sync( TimeSpan timeout ) NN_NOEXCEPT
    {
        return Impl::Sync( timeout );
    }
};

/**
* @brief  Graphics abstraction layer representing a semaphore.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TSemaphore
    : public detail::SemaphoreImpl< typename detail::TargetVariation< TTarget >::Type >
{
    typedef detail::SemaphoreImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

    NN_DISALLOW_COPY( TSemaphore );

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the semaphore.
*/
    typedef SemaphoreInfo InfoType;

/**
* @brief  Constructor.
*/
    TSemaphore() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the semaphore.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - Semaphore is not initialized.
*
* @post
*  - Semaphore is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys a semaphore.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - Semaphore is initialized.
*
* @post
*  - Semaphore is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

}
}
