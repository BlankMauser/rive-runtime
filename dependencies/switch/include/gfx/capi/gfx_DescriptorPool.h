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
* @brief  Declarations of API resources for descriptor pools.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>

#include <nn/gfx/gfx_DescriptorPoolInfo.h>
#include <nn/gfx/gfx_DescriptorSlot.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_RequiredMemory.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_DescriptorPool-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_DescriptorPool-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_DescriptorPool-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_DescriptorPool-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_DescriptorPool-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_DescriptorPool-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a descriptor pool.
*/
template< typename TTarget >
class TDescriptorPool
    : public detail::DescriptorPoolImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TDescriptorPool );

    typedef detail::DescriptorPoolImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing a descriptor pool.
*/
    typedef DescriptorPoolInfo InfoType;

/**
* @brief  Calculates the size of the descriptor pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the size of the descriptor pool.
*/
    static size_t CalculateDescriptorPoolSize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::CalculateDescriptorPoolSize( pDevice, info );
    }

/**
* @brief  Gets the alignment required for the descriptor pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment required for the descriptor pool.
*/
    static size_t GetDescriptorPoolAlignment( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::GetDescriptorPoolAlignment( pDevice, info );
    }

/**
* @brief  Calculates the size required to increment the descriptor slot by one.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] type  The type of the descriptor pool.
*
* @return  Returns the size, in bytes, required to increment the descriptor slot by one.
*/
    static ptrdiff_t GetDescriptorSlotIncrementSize( TDevice< Target >* pDevice, DescriptorPoolType type ) NN_NOEXCEPT
    {
        return Impl::GetDescriptorSlotIncrementSize( pDevice, type );
    }

/**
* @brief  Constructor.
*/
    TDescriptorPool() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a descriptor pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pMemoryPool  Pointer to the memory pool where the descriptor pool is placed.
* @param[in] memoryPoolOffset  The offset, in bytes, to the memory pool where the descriptor pool is placed.
* @param[in] memoryPoolSize  The size of the memory pool, in bytes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The descriptor pool is not initialized.
*  - <tt><var>pMemoryPool</var></tt> != <tt>NULL</tt>.
*  - <tt><var>memoryPoolSize</var></tt> is at least the size calculated by <tt>CalculateDescriptorPoolSize</tt>.
*
* @post
*  - The descriptor pool is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info,
        TMemoryPool< Target >* pMemoryPool, ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info, pMemoryPool, memoryPoolOffset, memoryPoolSize );
    }

/**
* @brief  Destroys a descriptor pool.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The descriptor pool is initialized.
*  - The process of updating the descriptor pool has not started.
*
* @post
*  - The descriptor pool is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Starts updating the descriptor pool.
*
* @pre
*  - The descriptor pool is initialized.
*  - The process of updating the descriptor pool has not started.
*
* @post
*  - The process of updating the descriptor pool has started.
*/
    void BeginUpdate() NN_NOEXCEPT
    {
        return Impl::BeginUpdate();
    }

/**
* @brief  Ends updating the descriptor pool.
*
* @pre
*  - The process of updating the descriptor pool has started.
*
* @post
*  - The process of updating the descriptor pool has not started.
*/
    void EndUpdate() NN_NOEXCEPT
    {
        return Impl::EndUpdate();
    }

/**
* @brief  Sets a buffer view in the specified slot.
*
* @param[in] indexSlot  The target slot number.
* @param[in] gpuAddress  GPU address for the buffer.
* @param[in] size  The size of the buffer to set.
*
* @pre
*  - The value of <tt><var>indexSlot</var></tt> is less than the number of descriptor pool slots.
*  - The process of updating the descriptor pool has started.
*  - The type of the descriptor pool is a buffer.
*
* @post
*  - A buffer view is set in the specified slot.
*/
    void SetBufferView( int indexSlot, const GpuAddress& gpuAddress, size_t size ) NN_NOEXCEPT
    {
        return Impl::SetBufferView( indexSlot, gpuAddress, size );
    }

/**
* @brief  Sets a sampler in the specified slot.
*
* @param[in] indexSlot  The target slot number.
* @param[in] pSampler  The target sampler.
*
* @pre
*  - The value of <tt><var>indexSlot</var></tt> is less than the number of descriptor pool slots.
*  - <tt><var>pSampler</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSampler</var></tt> is initialized.
*  - The process of updating the descriptor pool has started.
*  - The type of the descriptor pool is a sampler.
*
* @post
*  - A sampler is set in the specified slot.
*/
    void SetSampler( int indexSlot, const TSampler< Target >* pSampler ) NN_NOEXCEPT
    {
        return Impl::SetSampler( indexSlot, pSampler );
    }

/**
* @brief  Sets a texture view in the specified slot.
*
* @param[in] indexSlot  The target slot number.
* @param[in] pTextureView  The target texture view.
*
* @pre
*  - The value of <tt><var>indexSlot</var></tt> is less than the number of descriptor pool slots.
*  - <tt><var>pTextureView</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pTextureView</var></tt> is initialized.
*  - The process of updating the descriptor pool has started.
*  - The descriptor pool is a texture view type.
*
* @post
*  - A texture view is set in the specified slot.
*/
    void SetTextureView( int indexSlot, const TTextureView< Target >* pTextureView ) NN_NOEXCEPT
    {
        return Impl::SetTextureView( indexSlot, pTextureView );
    }

/**
* @brief  Configures an image to the specified slot.
*
* @param[in] indexSlot  The target slot number.
* @param[in] pImage  The target image.
*
* @pre
*  - The value of <tt><var>indexSlot</var></tt> is less than the number of descriptor pool slots.
*  - <tt><var>pImage</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pImage</var></tt> is initialized.
*  - The process of updating the descriptor pool has started.
*  - The descriptor pool is a texture view type.
*
* @post
*  - An image is set in the specified slot.
*/
    void SetImage( int indexSlot, const TTextureView< Target >* pImage ) NN_NOEXCEPT
    {
        return Impl::SetImage( indexSlot, pImage );
    }

/**
* @brief  Sets a buffer texture view in the specified slot.
*
* @param[in] indexSlot  The target slot number.
* @param[in] pBufferTextureView  The target buffer texture view.
*
* @pre
*  - The value of <tt><var>indexSlot</var></tt> is less than the number of descriptor pool slots.
*  - <tt><var>pBufferTextureView</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pBufferTextureView</var></tt> is initialized.
*  - The process of updating the descriptor pool has started.
*  - The descriptor pool is a texture view type.
*
* @post
*  - A buffer texture view has been set in the specified slot.
*/
    void SetBufferTextureView( int indexSlot,
        const TBufferTextureView< Target >* pBufferTextureView ) NN_NOEXCEPT
    {
        return Impl::SetBufferTextureView( indexSlot, pBufferTextureView );
    }

/**
* @brief  Sets a buffer image in the specified slot.
*
* @param[in] indexSlot  The target slot number.
* @param[in] pBufferTextureView  The target buffer texture view.
*
* @pre
*  - The value of <tt><var>indexSlot</var></tt> is less than the number of descriptor pool slots.
*  - <tt><var>pBufferTextureView</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pBufferTextureView</var></tt> is initialized.
*  - The process of updating the descriptor pool has started.
*  - The descriptor pool is a texture view type.
*
* @post
*  - A buffer image has been set in the specified slot.
*/
    void SetBufferImage( int indexSlot,
        const TBufferTextureView< Target >* pBufferTextureView ) NN_NOEXCEPT
    {
        return Impl::SetBufferImage( indexSlot, pBufferTextureView );
    }

/**
* @brief  Gets a descriptor slot.
*
* @param[out] pOutDescriptorSlot  Pointer for receiving the descriptor slot.
* @param[in] indexSlot  The target slot number.
*
* @pre
*  - The value of <tt><var>indexSlot</var></tt> is less than the number of descriptor pool slots.
*  - The descriptor pool is initialized.
*/
    void GetDescriptorSlot( DescriptorSlot* pOutDescriptorSlot, int indexSlot ) const NN_NOEXCEPT
    {
        return Impl::GetDescriptorSlot( pOutDescriptorSlot, indexSlot );
    }

/**
* @brief  Gets the index of the descriptor slot.
*
* @param[in] descriptorSlot  The descriptor slot that queries the index.
*
* @return  Returns the index of <tt><var>descriptorSlot</var></tt> in the descriptor pool.
*
* @pre
*  - <tt><var>descriptorSlot</var></tt> is a descriptor slot obtained from this descriptor pool.
*  - The descriptor pool is initialized.
*/
    int GetDescriptorSlotIndex( const DescriptorSlot& descriptorSlot ) const NN_NOEXCEPT
    {
        return Impl::GetDescriptorSlotIndex( descriptorSlot );
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
