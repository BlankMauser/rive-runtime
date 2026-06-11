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
* @brief  Declarations of API resources for memory pools.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_MemoryPoolInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_MemoryPool-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_MemoryPool-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_MemoryPool-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_MemoryPool-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_MemoryPool-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_MemoryPool-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a memory pool.
*/
template< typename TTarget >
class TMemoryPool
    : public detail::MemoryPoolImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TMemoryPool );

    typedef detail::MemoryPoolImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  Information class for initializing a memory pool.
*/
    typedef MemoryPoolInfo InfoType;

/**
* @brief  Gets the alignment required of memory for the pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment required of memory for the pool. Alignment is not required if set to <tt>1</tt>.
*/
    static size_t GetPoolMemoryAlignment( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::GetPoolMemoryAlignment( pDevice, info );
    }

/**
* @brief  Gets the alignment required of memory for the pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment required of memory for the pool. Alignment is not required if set to <tt>1</tt>.
*/
    static size_t GetPoolMemoryAlignment( TDevice< Target >* pDevice, const TMemoryPoolInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::GetPoolMemoryAlignment( pDevice, info );
    }

/**
* @brief  Gets the size granularity required of memory for the pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the size granularity required of memory for the pool. The size of memory for the pool must be a multiple of this value.
*/
    static size_t GetPoolMemorySizeGranularity( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::GetPoolMemorySizeGranularity( pDevice, info );
    }

/**
* @brief  Gets the size granularity required of memory for the pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the size granularity required of memory for the pool. The size of memory for the pool must be a multiple of this value.
*/
    static size_t GetPoolMemorySizeGranularity( TDevice< Target >* pDevice, const TMemoryPoolInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::GetPoolMemorySizeGranularity( pDevice, info );
    }

/**
* @brief  Constructor.
*/
    TMemoryPool() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a memory pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The memory pool is not initialized.
*
* @post
*  - The memory pool is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Initializes a memory pool.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The memory pool is not initialized.
*
* @post
*  - The memory pool is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const TMemoryPoolInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys a memory pool.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The memory pool is initialized.
*
* @post
*  - The memory pool is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Maps the memory pool for access from the CPU.
*
* @return
*  Returns a pointer to the start of the mapped memory pool.
*
* @pre
*  - The memory pool is initialized.
*
* @post
*  - The memory pool is mapped.
*
* @details
*  This function does not deal with CPU cache.
*  To view values as updated by the GPU, disable CPU cache using <tt>nn::gfx::MemoryPool::InvalidateMappedRange</tt>.
*  In the GL version, rewriting the memory pool has no effect on initialized resources.
*/
    void* Map() const NN_NOEXCEPT
    {
        return Impl::Map();
    }

/**
* @brief  Maps the memory pool for access from the CPU.
*
* @tparam T  The type of the element when receiving the mapped pointer.
*
* @return
*  Returns a pointer to the start of the mapped memory pool.
*
* @pre
*  - The memory pool is initialized.
*
* @post
*  - The memory pool is mapped.
*
* @details
*  This function does not deal with CPU cache.
*  To view values as updated by the GPU, disable CPU cache using <tt>nn::gfx::MemoryPool::InvalidateMappedRange</tt>.
*  In the GL version, rewriting the memory pool has no effect on initialized resources.
*/
    template< typename T >
    T* Map() const NN_NOEXCEPT
    {
        return Impl::template Map< T >();
    }

/**
* @brief  Unmaps the memory pool to indicate that access from the CPU has ended.
*
* @pre
*  - The memory pool is mapped.
*
* @post
*  - The memory pool is not mapped.
*
* @details
*  This function does not deal with CPU cache.
*  To enable access to written content by the GPU, use <tt>nn::gfx::MemoryPool::FlushMappedRange</tt> to flush the CPU cache.
*/
    void Unmap() const NN_NOEXCEPT
    {
        return Impl::Unmap();
    }

/**
* @brief  Flushes the CPU cache written in the map to memory.
*
* @param[in] offset  The offset, in bytes, from the start of the memory pool to the start of the range to flush.
* @param[in] size  The size, in bytes, of the range to flush.
*
* @pre
*  - The memory pool is mapped.
*
* @post
*  - The content in the specified range of cache has been flushed.
*
* @details
*  Flushes the specified range of CPU cache, in units of cache line size.
*/
    void FlushMappedRange( ptrdiff_t offset, size_t size ) const NN_NOEXCEPT
    {
        return Impl::FlushMappedRange( offset, size );
    }

/**
* @brief  Invalidates CPU cache to reference the latest values in the map.
*
* @param[in] offset  The offset, in bytes, from the start of the memory pool to the start of the range to invalidate.
* @param[in] size  The size, in bytes, of the range to invalidate.
*
* @pre
*  - The memory pool is mapped.
*
* @post
*  - The content in the specified range of cache has been invalidated.
*
* @details
*  Invalidates the specified range of CPU cache, in units of cache line size.
*/
    void InvalidateMappedRange( ptrdiff_t offset, size_t size ) const NN_NOEXCEPT
    {
        return Impl::InvalidateMappedRange( offset, size );
    }

/**
* @brief  Configures a label for debugging.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] label  Pointer to the null-terminated label string.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The memory pool is initialized.
*
* @details
*  Newly specified labels overwrite settings when a label has already been configured.
*  Configured labels are removed when <tt><var>label</var></tt> is set to <tt>NULL</tt>.
*
*/
    void SetDebugLabel( TDevice< Target >* pDevice, const char* label ) NN_NOEXCEPT
    {
        return detail::DebugLabelHelper::SetDebugLabel< Impl >( this, pDevice, label );
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
