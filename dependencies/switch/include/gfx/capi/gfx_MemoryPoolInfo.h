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
* @brief  Declarations of API resources for the information used when initializing a memory pool.
*/

#pragma once

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_MemoryPoolInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

#if !defined( NN_GFX_CONFIG_DISABLE_TINFO )

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_MemoryPoolInfo-api.nvn.8.h>
#endif

#endif

namespace nn {
namespace gfx {

/**
* @brief  Class representing the information for initializing a memory pool.
*/
class MemoryPoolInfo
    : public detail::DataContainer< MemoryPoolInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    MemoryPoolInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
    *
* @post
    * - The various parameters are configured.
    *
* @details
    * Equivalent to calling the following.
    * - SetMemoryPoolProperty( nn::gfx::MemoryPoolProperty_CpuUncached | nn::gfx::MemoryPoolProperty_GpuCached );
    * - SetPoolMemory( NULL, 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the properties of the memory pool.
    *
* @param[in] value  The properties of the memory pool, described as a combination of <tt>nn::gfx::MemoryPoolProperty</tt> objects.
    *
* @post
    * - The memory pool properties are set.
    *
* @details
    * To specify a value, you must specify one of the following: <tt>nn::gfx::MemoryPoolProperty_CpuInvisible</tt>, <tt>nn::gfx::MemoryPoolProperty_CpuUncached</tt>, or <tt>nn::gfx::MemoryPoolProperty_CpuCached</tt>; and one of the following: <tt>nn::gfx::MemoryPoolProperty_GpuInvisible</tt>, <tt>nn::gfx::MemoryPoolProperty_GpuUncached</tt>, or <tt>nn::gfx::MemoryPoolProperty_GpuCached</tt>.
*/
    void SetMemoryPoolProperty( int value ) NN_NOEXCEPT
    {
        this->memoryPoolProperty = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets memory for the pool.
    *
* @param[in] value  Pointer to the memory.
* @param[in] size  The memory size, in bytes.
    *
* @post
    * - Memory for the pool is set.
*/
    void SetPoolMemory( void* value, size_t size ) NN_NOEXCEPT
    {
        this->pMemory = value;
        this->memorySize = static_cast< uint32_t >( size );
    }

/**
* @brief  Gets the memory pool characteristics.
    *
* @return  Returns the properties of the memory pool, described as a combination of <tt>nn::gfx::MemoryPoolProperty</tt> objects.
*/
    int GetMemoryPoolProperty() const NN_NOEXCEPT
    {
        return static_cast< int >( this->memoryPoolProperty );
    }

/**
* @brief  Gets memory for the pool.
    *
* @return  Returns a pointer to memory for the pool.
*/
    void* GetPoolMemory() const NN_NOEXCEPT
    {
        return this->pMemory;
    }

/**
* @brief  Gets the size of the memory for the pool.
    *
* @return  Returns the size of the memory for the pool.
*/
    size_t GetPoolMemorySize() const NN_NOEXCEPT
    {
        return this->memorySize;
    }
};

/**
* @brief  Graphics abstraction layer representing information for initializing the memory pool.
*/
template< typename TTarget >
class TMemoryPoolInfo
    : public detail::TargetInfoImpl< detail::MemoryPoolInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, MemoryPoolInfo >::Type
{
    typedef typename detail::TargetInfoImpl< detail::MemoryPoolInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, MemoryPoolInfo >::Type Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename detail::TargetVariation< TTarget >::Type Target;

/**
* @brief  Converts common-version information to special edition information.
    *
* @param[in] pDstInfo  Pointer to the destination for the converted special edition information.
* @param[in] info  The common-version information that serves as the source.
    *
* @pre
    * - <tt><var>pDstInfo</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertFromInfo( TMemoryPoolInfo< TTarget >* pDstInfo, const MemoryPoolInfo& info ) NN_NOEXCEPT
    {
        return detail::InfoHelper::ConvertFromInfo< Impl >( pDstInfo, info );
    }

/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TMemoryPoolInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
    *
* @post
    * - The various parameters are configured.
    *
* @details
    * Equivalent to calling the following.
    * - SetMemoryPoolProperty( nn::gfx::MemoryPoolProperty_CpuUncached | nn::gfx::MemoryPoolProperty_GpuCached );
    * - SetPoolMemory( NULL, 0 );
*/
    void SetDefault() NN_NOEXCEPT
    {
        return Impl::SetDefault();
    }

/**
* @brief  Sets the properties of the memory pool.
    *
* @param[in] value  The properties of the memory pool, described as a combination of <tt>nn::gfx::MemoryPoolProperty</tt> objects.
    *
* @post
    * - The memory pool properties are set.
    *
* @details
    * To specify a value, you must specify one of the following: <tt>nn::gfx::MemoryPoolProperty_CpuInvisible</tt>, <tt>nn::gfx::MemoryPoolProperty_CpuUncached</tt>, or <tt>nn::gfx::MemoryPoolProperty_CpuCached</tt>; and one of the following: <tt>nn::gfx::MemoryPoolProperty_GpuInvisible</tt>, <tt>nn::gfx::MemoryPoolProperty_GpuUncached</tt>, or <tt>nn::gfx::MemoryPoolProperty_GpuCached</tt>.
*/
    void SetMemoryPoolProperty( int value ) NN_NOEXCEPT
    {
        return Impl::SetMemoryPoolProperty( value );
    }

/**
* @brief  Sets memory for the pool.
    *
* @param[in] value  Pointer to the memory.
* @param[in] size  The memory size, in bytes.
    *
* @post
    * - Memory for the pool is set.
*/
    void SetPoolMemory( void* value, size_t size ) NN_NOEXCEPT
    {
        return Impl::SetPoolMemory( value, size );
    }
};

}
}
