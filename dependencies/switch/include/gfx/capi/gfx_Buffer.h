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
* @brief  Declarations of API resources for buffers.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_BufferInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_Buffer-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_Buffer-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_Buffer-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_Buffer-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_Buffer-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_Buffer-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

class GpuAddress;

/**
* @brief  Graphics abstraction layer representing a buffer.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TBuffer
    : public detail::BufferImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TBuffer );

    typedef detail::BufferImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing a buffer.
*/
    typedef BufferInfo InfoType;

/**
* @brief  Boolean value indicating whether a memory pool is required at initialization time.
*/
    static const bool IsMemoryPoolRequired = Impl::IsMemoryPoolRequired;

/**
* @brief  Gets the alignment required for the buffer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment required for the buffer. Alignment is not required if set to <tt>1</tt>.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*/
    static size_t GetBufferAlignment( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::GetBufferAlignment( pDevice, info );
    }

/**
* @brief  Gets the alignment required for the buffer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment required for the buffer. Alignment is not required if set to <tt>1</tt>.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*/
    static size_t GetBufferAlignment( TDevice< Target >* pDevice, const TBufferInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::GetBufferAlignment( pDevice, info );
    }

/**
* @brief  Constructor.
*/
    TBuffer() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a buffer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pMemoryPool  Pointer to the memory pool in which to place the buffer.
* @param[in] memoryPoolOffset  Offset, in bytes, to the memory pool where the buffer is placed.
* @param[in] memoryPoolSize  Size, in bytes, of the memory pool for the buffer to use.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The buffer is not initialized.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>pMemoryPool</var></tt> != <tt>NULL</tt>.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>memoryPoolSize</var></tt> is larger than the size set by <tt><var>info</var></tt>.
*
* @post
*  - The buffer is initialized.
*
* @details
*  If <tt>IsMemoryPoolRequired</tt> is <tt>false</tt> and <tt><var>pMemoryPool</var></tt> is specified, the content of the specified memory pool is used as the default.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info,
        TMemoryPool< Target >* pMemoryPool, ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info, pMemoryPool, memoryPoolOffset, memoryPoolSize );
    }

/**
* @brief  Initializes a buffer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pMemoryPool  Pointer to the memory pool where the buffer is set.
* @param[in] memoryPoolOffset  Offset, in bytes, to the memory pool where the buffer is placed.
* @param[in] memoryPoolSize  Size, in bytes, of the memory pool for the buffer to use.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The buffer is not initialized.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>pMemoryPool</var></tt> != <tt>NULL</tt>.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>memoryPoolSize</var></tt> is larger than the size set by <tt><var>info</var></tt>.
*
* @post
*  - The buffer is initialized.
*
* @details
*  If <tt>IsMemoryPoolRequired</tt> is <tt>false</tt> and <tt><var>pMemoryPool</var></tt> is specified, the content of the specified memory pool is used as the default.
*/
    void Initialize( TDevice< Target >* pDevice, const TBufferInfo< Target >& info,
        TMemoryPool< Target >* pMemoryPool, ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info, pMemoryPool, memoryPoolOffset, memoryPoolSize );
    }

/**
* @brief  Destroys the buffer.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The buffer is initialized.
*  - The buffer is not mapped.
*
* @post
*  - The buffer is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Maps the buffer for access from the CPU.
*
* @return
*  Returns the pointer to the start of the mapped buffer.
*
* @pre
*  - The buffer is initialized.
*
* @post
*  - The buffer is mapped.
*
* @details
*  This function does not deal with CPU cache.
*  To view values as updated by the GPU, disable CPU cache using <tt>nn::gfx::Buffer::InvalidateMappedRange</tt>.
*/
    void* Map() const NN_NOEXCEPT
    {
        return Impl::Map();
    }

/**
* @brief  Maps the buffer for access from the CPU.
*
* @tparam T  The type of the element when receiving the mapped pointer.
*
* @return
*  Returns the pointer to the start of the mapped buffer.
*
* @pre
*  - The buffer is initialized.
*
* @post
*  - The buffer is mapped.
*
* @details
*  This function does not deal with CPU cache.
*  To view values as updated by the GPU, disable CPU cache using <tt>nn::gfx::Buffer::InvalidateMappedRange</tt>.
*/
    template< typename T >
    T* Map() const NN_NOEXCEPT
    {
        return Impl::template Map< T >();
    }

/**
* @brief  Unmaps the buffer to indicate that access from the CPU is finished.
*
* @pre
*  - The buffer is mapped.
*
* @post
*  - The buffer is not mapped.
*
* @details
*  This function does not deal with CPU cache.
*  To enable access to written content by the GPU, use <tt>nn::gfx::Buffer::FlushMappedRange</tt> to flush the CPU cache.
*/
    void Unmap() const NN_NOEXCEPT
    {
        return Impl::Unmap();
    }

/**
* @brief  Flushes the CPU cache written in the map to memory.
*
* @param[in] offset  The offset, in bytes, from the start of the buffer to the start of the range to flush.
* @param[in] size  The size, in bytes, of the range to flush.
*
* @pre
*  - The buffer is mapped.
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
* @param[in] offset  The offset, in bytes, from the start of the buffer to the start of the range to invalidate.
* @param[in] size  The size, in bytes, of the range to invalidate.
*
* @pre
*  - The buffer is mapped.
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
* @brief  Gets the starting address of the buffer used for GPU access.
*
* @param[out] pOutGpuAddress  Pointer to the location for storing the GPU address.
*
* @pre
*  - The buffer is initialized.
*/
    void GetGpuAddress( GpuAddress* pOutGpuAddress ) const NN_NOEXCEPT
    {
        return Impl::GetGpuAddress( pOutGpuAddress );
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
*  - The buffer is initialized.
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

/**
* @brief  Graphics abstraction layer representing a buffer texture view.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TBufferTextureView
    : public detail::BufferTextureViewImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TBufferTextureView );

    typedef detail::BufferTextureViewImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing a buffer texture view.
*/
    typedef BufferTextureViewInfo InfoType;

/**
* @brief  Gets the alignment required for the view offset.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment, in bytes, required for the view offset. Alignment is not required if set to <tt>1</tt>.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*/
    static size_t GetOffsetAlignment( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::GetOffsetAlignment( pDevice, info );
    }

/**
* @brief  Constructor.
*/
    TBufferTextureView() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the buffer texture view.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The buffer texture view is not initialized.
*
* @post
*  - The buffer texture view is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys the buffer texture view.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The buffer texture view is initialized.
*
* @post
*  - The buffer texture view is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

}
}
