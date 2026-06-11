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
* @brief  Declarations for API resources related to pipelines.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_PipelineInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_RequiredMemory.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_Pipeline-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_Pipeline-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_Pipeline-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_Pipeline-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_Pipeline-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_Pipeline-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a pipeline.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TPipeline
    : public detail::PipelineImpl< typename detail::TargetVariation< TTarget >::Type >
    , private detail::RequiredMemory< detail::PipelineImpl<
        typename detail::TargetVariation< TTarget >::Type > >
{
    NN_DISALLOW_COPY( TPipeline );

    typedef detail::PipelineImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the graphics pipeline.
*/
    typedef GraphicsPipelineInfo GraphicsInfoType;

/**
* @brief  The information class for initializing the compute pipeline.
*/
    typedef ComputePipelineInfo ComputeInfoType;

/**
* @brief  Required memory information.
*/
    enum RequiredMemoryInfo
    {
        RequiredMemoryInfo_Alignment = detail::RequiredMemory< Impl >::MemoryInfoImpl::RequiredMemoryInfo_Alignment, //!<  The required alignment. Alignment is not required if set to <tt>1</tt>.
    };

/**
* @brief  Gets the size of the memory that is required.
*
* @param[in] info  Information for initializing the graphics pipeline.
*
* @return  Returns the size of the memory that is required, in bytes.
*/
    static size_t GetRequiredMemorySize( const GraphicsInfoType& info ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetRequiredMemorySize( info );
    }

/**
* @brief  Gets the size of the memory that is required.
*
* @param[in] info  Information for initializing the compute pipeline.
*
* @return  Returns the size of the memory that is required, in bytes.
*/
    static size_t GetRequiredMemorySize( const ComputeInfoType& info ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetRequiredMemorySize( info );
    }

/**
* @brief  Constructor.
*/
    TPipeline() NN_NOEXCEPT
    {
    }

/**
* @brief  Sets the required memory.
*
* @param[in] pMemory  Pointer to the memory to set.
* @param[in] size  Size of the memory to set, in bytes.
*
* @pre
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, it is aligned to <tt>RequiredMemoryInfo_Alignment</tt>.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, <tt><var>size</var></tt> == <tt>0</tt>.
*
* @post
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, the required memory is set.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, the required memory is not set.
*/
    void SetMemory( void* pMemory, size_t size ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::SetMemory( pMemory, size );
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    void* GetMemory() NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    const void* GetMemory() const NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Initializes the graphics pipeline.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The pipeline is not initialized.
*  - If the value returned by <tt>GetRequiredMemorySize</tt> with the same <tt><var>info</var></tt> argument is larger than <tt>0</tt>, the required memory is set to that size or greater.
*
* @post
*  - The pipeline has been initialized as a graphics pipeline.
*/
    void Initialize( TDevice< Target >* pDevice, const GraphicsInfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Initializes the compute pipeline.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The pipeline is not initialized.
*  - If the value returned by <tt>GetRequiredMemorySize</tt> with the same <tt><var>info</var></tt> argument is larger than <tt>0</tt>, the required memory is set to that size or greater.
*
* @post
*  - The pipeline has been initialized as a compute pipeline.
*/
    void Initialize( TDevice< Target >* pDevice, const ComputeInfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Finalizes the pipeline.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The pipeline is initialized.
*
* @post
*  - The pipeline is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
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
