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
* @brief  Declarations of API resources for the information used to initialize a buffer.
*/

#pragma once

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_BufferInfoData.h>

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/detail/gfx_Declare.h>

#if !defined( NN_GFX_CONFIG_DISABLE_TINFO )

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_BufferInfo-api.nvn.8.h>
#endif

#endif

namespace nn {
namespace gfx {

/**
* @brief  The class representing information for initializing a buffer.
*/
class BufferInfo
    : public detail::DataContainer< BufferInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    BufferInfo() NN_NOEXCEPT
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
    * - SetSize( 0 );
    * - SetGpuAccessFlags( 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the size of the buffer.
    *
* @param[in] value  The size of the buffer, in bytes.
    *
* @post
    * - The size of the buffer has been configured.
*/
    void SetSize( size_t value ) NN_NOEXCEPT
    {
        this->size = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the method of access for the GPU.
    *
* @param[in] value  Access flags comprising a combination of <tt>nn::gfx::GpuAccess</tt>.
    *
* @post
    * - The access method for the GPU is set.
*/
    void SetGpuAccessFlags( int value ) NN_NOEXCEPT
    {
        this->gpuAccessFlag = static_cast< Bit32 >( value );
    }

/**
* @brief  Gets the buffer size.
    *
* @return  Returns the size of the buffer.
*/
    size_t GetSize() const NN_NOEXCEPT
    {
        return static_cast< size_t >( this->size );
    }

/**
* @brief  Gets the method of access for the GPU.
    *
* @return  Returns the access method for the GPU.
*/
    int GetGpuAccessFlags() const NN_NOEXCEPT
    {
        return static_cast< int >( this->gpuAccessFlag );
    }
};

/**
* @brief  The class representing the information for initializing a buffer texture view.
*/
class BufferTextureViewInfo
    : public detail::DataContainer< BufferTextureViewInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    BufferTextureViewInfo()
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
    * - SetImageFormat( ImageFormat_Undefined );
    * - SetOffset( 0 );
    * - SetSize( 0 );
    * - SetBufferPtr( NULL );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the image format for parsing the content of the buffer.
    *
* @param[in] value  Image format.
    *
* @post
    * - The image format for parsing the content of the buffer is set.
*/
    void SetImageFormat( ImageFormat value ) NN_NOEXCEPT
    {
        this->format = static_cast<Bit32>( value );
    }

/**
* @brief  Sets the offset from the start of the buffer to reference.
    *
* @param[in] value  The offset, in bytes, from the start of the buffer.
    *
* @post
    * - The offset from the start of the buffer to reference is set.
*/
    void SetOffset( ptrdiff_t value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value >= 0 );
        this->offset = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the size of the buffer to reference.
    *
* @param[in] value  The size, in bytes, to reference.
    *
* @post
    * - The size of the buffer to reference is set.
*/
    void SetSize( size_t value ) NN_NOEXCEPT
    {
        this->size = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the buffer to reference.
    *
* @tparam TTarget  The low-level graphics API for the buffer.
    *
* @param[in] value  Pointer to the buffer to reference.
    *
* @post
    * - The buffer to reference is set.
    *
* @details
*  <tt><var>TTarget</var></tt> must be the same as the <tt><var>TTarget</var></tt> for the buffer texture view you intend to initialize.
*/
    template< typename TTarget >
    void SetBufferPtr( const TBuffer< TTarget >* value ) NN_NOEXCEPT
    {
        this->pBuffer = value;
    }

/**
* @brief  Sets the buffer to reference.
    *
* @param[in] value  Pointer to the buffer to reference.
    *
* @post
    * - The buffer to reference is set.
    *
* @details
*  If you are setting any value other than <tt>NULL</tt>, call the version with a template argument.
*/
    void SetBufferPtr( const void* value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value == NULL );
        this->pBuffer = value;
    }

/**
* @brief  Gets the image format for parsing the content of the buffer.
    *
* @return  Returns the image format for parsing the content of the buffer.
*/
    ImageFormat GetImageFormat() const NN_NOEXCEPT
    {
        return static_cast< ImageFormat >( this->format );
    }

/**
* @brief  Gets the offset from the start of the buffer to reference.
    *
* @return  Returns the offset, in bytes, from the start of the buffer to reference.
*/
    ptrdiff_t GetOffset() const NN_NOEXCEPT
    {
        return this->offset;
    }

/**
* @brief  Gets the size of the buffer to reference.
    *
* @return  Returns the size, in bytes, of the buffer to reference.
*/
    size_t GetSize() const NN_NOEXCEPT
    {
        return this->size;
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets the buffer to reference.
    *
* @return  Returns a pointer to the <tt>nn::gfx::Buffer</tt>-type buffer to reference.
    *
* @details
    * Assign a <tt>nn::gfx::Buffer</tt>-type pointer for this function's return value.
*/
    const Buffer* GetBufferPtr() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetBufferPtr() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( this->pBuffer.ptr );
    }
#endif
};

/**
* @brief  Graphics abstraction layer representing information for initializing a buffer.
*/
template< typename TTarget >
class TBufferInfo
    : public detail::TargetInfoImpl< detail::BufferInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, BufferInfo >::Type
{
    typedef typename detail::TargetInfoImpl< detail::BufferInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, BufferInfo >::Type Impl;

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
    static void ConvertFromInfo( TBufferInfo< TTarget >* pDstInfo, const BufferInfo& info ) NN_NOEXCEPT
    {
        return detail::InfoHelper::ConvertFromInfo< Impl >( pDstInfo, info );
    }

/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TBufferInfo() NN_NOEXCEPT
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
    * - SetSize( 0 );
    * - SetGpuAccessFlags( 0 );
*/
    void SetDefault() NN_NOEXCEPT
    {
        return Impl::SetDefault();
    }

/**
* @brief  Sets the size of the buffer.
    *
* @param[in] value  The size of the buffer, in bytes.
    *
* @post
    * - The size of the buffer has been configured.
*/
    void SetSize( size_t value ) NN_NOEXCEPT
    {
        return Impl::SetSize( value );
    }

/**
* @brief  Sets the method of access for the GPU.
    *
* @param[in] value  Access flags comprising a combination of <tt>nn::gfx::GpuAccess</tt>.
    *
* @post
    * - The access method for the GPU is set.
*/
    void SetGpuAccessFlags( int value ) NN_NOEXCEPT
    {
        return Impl::SetGpuAccessFlags( value );
    }
};

}
}
