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
* @brief  Declarations of API resources for swap chains.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_SwapChainInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_SwapChain-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_SwapChain-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_SwapChain-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_SwapChain-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_SwapChain-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_SwapChain-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a swap chain.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TSwapChain
    : public detail::SwapChainImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TSwapChain );

    typedef detail::SwapChainImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the swap chain.
*/
    typedef SwapChainInfo InfoType;

/**
* @brief  Boolean value indicating whether a memory pool is required at initialization time.
*/
    static const bool IsMemoryPoolRequired = Impl::IsMemoryPoolRequired;

/**
* @brief  Gets the alignment required for the scan buffer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment required for the scan buffer. Alignment is not required if set to <tt>1</tt>.
*/
    static size_t GetScanBufferAlignment( TDevice< Target >* pDevice, const InfoType& info )
    {
        return Impl::GetScanBufferAlignment( pDevice, info );
    }

/**
* @brief  Calculates the size of the scan buffer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the scan buffer size.
*/
    static size_t CalculateScanBufferSize( TDevice< Target >* pDevice, const InfoType& info )
    {
        return Impl::CalculateScanBufferSize( pDevice, info );
    }

/**
* @brief  Constructor.
*/
    TSwapChain() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the swap chain.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pMemoryPool  Pointer to the memory pool in which to place the scan buffer.
* @param[in] memoryPoolOffset  Offset to the memory pool where the scan buffer is set, in bytes.
* @param[in] memoryPoolSize  Size of the memory pool the scan buffer uses, in bytes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The swap chain is not initialized.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>pMemoryPool</var></tt> != <tt>NULL</tt>.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>memoryPoolSize</var></tt> is larger than the size obtained by <tt>CalculateScanBufferSize</tt>.
*
* @post
*  - The swap chain is initialized.
*
* @details
*  The memory pool being passed must have been created to be compressible.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info,
        TMemoryPool< Target >* pMemoryPool, ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info, pMemoryPool, memoryPoolOffset, memoryPoolSize );
    }

/**
* @brief  Destroys a swap chain.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The swap chain is initialized.
*
* @post
*  - The swap chain is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Gets the scan buffer views.
*
* @param[in] ppOutScanBufferArray  Pointer to the array for receiving the pointers to the scan buffer views.
* @param[in] maxScanBufferCount  The maximum number of scan buffer view pointers to receive.
*
* @return  Returns the number of scan buffers with swap chains when <tt><var>ppOutScanBufferArray</var></tt> is a null value. Returns the number of scan buffers obtained when that is not the case.
*
* @pre
*  - The swap chain is initialized.
*  - The number of array elements specified using <tt><var>ppOutScanBufferArray</var></tt> must be at least <tt><var>maxScanBufferCount</var></tt>.
*/
    int GetScanBufferViews( TColorTargetView< Target >** ppOutScanBufferArray,
        int maxScanBufferCount ) NN_NOEXCEPT
    {
        return Impl::GetScanBufferViews( ppOutScanBufferArray, maxScanBufferCount );
    }

/**
* @brief  Gets the scan buffers.
*
* @param[in] ppOutScanBufferTextureArray  Pointer to the array for receiving the pointers to the scan buffers.
* @param[in] maxScanBufferTextureCount  The maximum number of scan buffer pointers to receive.
*
* @return  Returns the number of scan buffers with swap chains when <tt><var>ppOutScanBufferTextureArray</var></tt> is a null value. Returns the number of scan buffers obtained when that is not the case.
*
* @pre
*  - The swap chain is initialized.
*  - The number of array elements specified using <tt><var>ppOutScanBufferTextureArray</var></tt> must be at least <tt><var>maxScanBufferTextureCount</var></tt>.
*/
    int GetScanBuffers( TTexture< Target >** ppOutScanBufferTextureArray,
        int maxScanBufferTextureCount ) NN_NOEXCEPT
    {
        return Impl::GetScanBuffers( ppOutScanBufferTextureArray, maxScanBufferTextureCount );
    }

/**
* @brief  Gets the scan buffer index for the next <tt>Present</tt> target.
*
* @param[out] pOutScanBufferIndex  The pointer for receiving the scan buffer index that is the next <tt>Present</tt> target.
* @param[in] pSemaphore  The pointer to the semaphore that is signaled when the target scan buffer becomes available.
* @param[in] pFence  The pointer to the fence that is signaled when the target scan buffer becomes available.
*
* @return  Returns the result of acting to acquire the scan buffer.
* @retval AcquireScanBufferResult_Success  Acquiring the scan buffer succeeded.
* @retval AcquireScanBufferResult_Failed  Acquiring the scan buffer failed.
*
* @pre
*  - The swap chain is initialized.
*  - <tt><var>pOutScanBufferIndex</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSemaphore</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSemaphore</var></tt> is initialized.
*  - <tt><var>pSemaphore</var></tt> is not in the signaled state.
*  - If <tt><var>pFence</var></tt> != <tt>NULL</tt>, <tt><var>pFence</var></tt> is initialized.
*  - If <tt><var>pFence</var></tt> != <tt>NULL</tt>, <tt><var>pFence</var></tt> is not in the signaled state.
*
* @details
*  In the GL version, <tt>Sync</tt> does not have any effect on <tt><var>pSemaphore</var></tt> and <tt><var>pFence</var></tt>.
*/
    AcquireScanBufferResult AcquireNextScanBufferIndex( int* pOutScanBufferIndex,
        TSemaphore< Target >* pSemaphore, TFence< Target >* pFence ) NN_NOEXCEPT
    {
        return Impl::AcquireNextScanBufferIndex( pOutScanBufferIndex, pSemaphore, pFence );
    }

/**
* @brief  Gets the scan buffer index for the next <tt>Present</tt> target.
*
* @deprecated  To be deprecated. Use the version of <tt>AcquireNextScanBufferIndex</tt> that has three parameters. In addition, this cannot be used in combination with the new function.
*
* @return  Returns the scan buffer index for the next <tt>Present</tt> target.
*
* @pre
*  - The swap chain is initialized.
*/
    int AcquireNextScanBufferIndex() NN_NOEXCEPT
    {
        return Impl::AcquireNextScanBufferIndex();
    }

/**
* @brief  Gets the scan buffer view for the next <tt>Present</tt> target.
*
* @deprecated  To be deprecated. Use the version of <tt>AcquireNextScanBufferIndex</tt> that has three parameters. In addition, this cannot be used in combination with the new function.
*
* @return  Returns the scan buffer view for the next <tt>Present</tt> target.
*
* @pre
*  - The swap chain is initialized.
*
* @details
*  It must be called before <tt>nn::gfx::Queue::CopyToScanBuffer</tt> when using it with <tt>nn::gfx::Queue::CopyToScanBuffer</tt>.
*/
    TColorTargetView< Target >* AcquireNextScanBufferView() NN_NOEXCEPT
    {
        return static_cast< TColorTargetView< Target >* >( Impl::AcquireNextScanBufferView() );
    }

/**
* @brief  Gets the scan buffer for the next <tt>Present</tt> target.
*
* @deprecated  To be deprecated. Use the version of <tt>AcquireNextScanBufferIndex</tt> that has three parameters. In addition, this cannot be used in combination with the new function.
*
* @return  Returns the scan buffer for the next <tt>Present</tt> target.
*
* @pre
*  - The swap chain is initialized.
*/
    TTexture< Target >* AcquireNextScanBuffer() NN_NOEXCEPT
    {
        return static_cast< TTexture< Target >* >( Impl::AcquireNextScanBuffer() );
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
