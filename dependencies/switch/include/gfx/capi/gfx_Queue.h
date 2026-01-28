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
* @brief  API declarations for queues.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_QueueInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_Queue-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_Queue-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_Queue-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_Queue-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_Queue-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_Queue-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a queue.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TQueue
    : public detail::QueueImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TQueue );

    typedef detail::QueueImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing a queue.
*/
    typedef QueueInfo InfoType;

/**
* @brief  Constructor.
*/
    TQueue() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the queue.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The queue is not initialized.
*
* @post
*  - The queue is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Initializes the queue.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The queue is not initialized.
*
* @post
*  - The queue is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const TQueueInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys the queue.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The queue is initialized.
*
* @post
*  - The queue is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Submits commands for execution.
*
* @param[in] pCommandBuffer  Pointer to the command buffer.
* @param[in] pFence  Pointer to a fence to synchronize the end of the commands.
*
* @pre
*  - The queue is initialized.
*  - <tt><var>pCommandBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pCommandBuffer</var></tt> is initialized.
*  - <tt><var>pCommandBuffer</var></tt> is not started.
*  - If <tt><var>pFence</var></tt> != <tt>NULL</tt>, <tt><var>pFence</var></tt> is initialized.
*
* @post
*  - The commands are submitted.
*
* @details
*  The synchronization fence is not submitted if <tt><var>pFence</var></tt> is <tt>NULL</tt>.
*/
    void ExecuteCommand( TCommandBuffer< Target >* pCommandBuffer,
        TFence< Target >* pFence ) NN_NOEXCEPT
    {
        return Impl::ExecuteCommand( pCommandBuffer, pFence );
    }

/**
* @brief  Flushes the submitted commands.
*
* @pre
*  - The queue is initialized.
*
* @post
*  - The submitted commands have been flushed.
*/
    void Flush() NN_NOEXCEPT
    {
        return Impl::Flush();
    }

/**
* @brief  Synchronizes the execution of submitted commands.
*
* @pre
*  - The queue is initialized.
*
* @post
*  - All submitted commands have finished execution on the device.
*
* @details
*  This function does not return until all commands have finished executing on the device.
*/
    void Sync() NN_NOEXCEPT
    {
        return Impl::Sync();
    }

/**
* @brief  Submits a command that sets a semaphore.
*
* @param[in] pSemaphore  Pointer to the semaphore.
*
* @pre
*  - The queue is initialized.
*  - <tt><var>pSemaphore</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSemaphore</var></tt> is initialized.
*
* @post
*  - The command to set the semaphore is submitted.
*/
    void SetSemaphore( TSemaphore< Target >* pSemaphore ) NN_NOEXCEPT
    {
        return Impl::SetSemaphore( pSemaphore );
    }

/**
* @brief  Submits a command that synchronizes a semaphore.
*
* @param[in] pSemaphore  Pointer to the semaphore set on the queue.
*
* @pre
*  - The queue is initialized.
*  - <tt><var>pSemaphore</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSemaphore</var></tt> is initialized.
*
* @post
*  - The command to synchronize the semaphore is submitted.
*/
    void SyncSemaphore( const TSemaphore< Target >* pSemaphore ) NN_NOEXCEPT
    {
        return Impl::SyncSemaphore( pSemaphore );
    }

/**
* @brief  Submits a command to copy a color target to a scan buffer.
*
* @deprecated  To be deprecated. Get the scan buffer using the <tt>nn::gfx::SwapChain::GetCurrentScanBuffer()</tt> function and perform the operation on that obtained scan buffer.
*
* @param[in] pSwapChain  Pointer to a swap chain that references the scan buffer.
* @param[in] pColorTarget  Pointer to the color target.
*
* @pre
*  - The queue is initialized.
*  - <tt><var>pSwapChain</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pColorTarget</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSwapChain</var></tt> is initialized.
*  - <tt><var>pColorTarget</var></tt> is initialized.
*
* @post
*  - The command to copy the color target to a scan buffer has been submitted.
*/
    void CopyToScanBuffer( TSwapChain< Target >* pSwapChain,
        const TColorTargetView< Target >* pColorTarget ) NN_NOEXCEPT
    {
        return Impl::CopyToScanBuffer( pSwapChain, pColorTarget );
    }

/**
* @brief  Copies the content of the swap chain to the display.
*
* @param[in] pSwapChain  Pointer to the swap chain.
* @param[in] presentInterval  Screen V-sync count.
*
* @pre
*  - The queue is initialized.
*  - <tt><var>pSwapChain</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSwapChain</var></tt> is initialized.
*
* @post
*  - The command to draw to the display is submitted.
*
* @details
*  Display V-sync is not used when <tt><var>presentInterval</var></tt> is set to <tt>0</tt>.
*  Calls might not return until vertical synchronization has occurred because of things like the dependency on low-level graphics APIs.
*  To make sure that synchronization is occurring in the CPU, call <tt>Sync</tt> after this.
*/
    void Present( TSwapChain< Target >* pSwapChain, int presentInterval ) NN_NOEXCEPT
    {
        return Impl::Present( pSwapChain, presentInterval );
    }

/**
* @brief  Sets an optional user pointer.
*
* @param[in] value  The user pointer to set.
*
* @post
*  - The user pointer is set.
*/
    void SetUserPtr( void* value ) NN_NOEXCEPT
    {
        return SetUserPtrImpl( this, value );
    }

/**
* @brief  Gets the optional user pointer that has been set.
*
* @return  Returns the optional user pointer that has been set.
*/
    void* GetUserPtr() NN_NOEXCEPT
    {
        return GetUserPtrImpl( this );
    }

/**
* @brief  Gets the optional user pointer that has been set.
*
* @return  Returns the optional user pointer that has been set.
*/
    const void* GetUserPtr() const NN_NOEXCEPT
    {
        return GetUserPtrImpl( this );
    }
};

}
}
