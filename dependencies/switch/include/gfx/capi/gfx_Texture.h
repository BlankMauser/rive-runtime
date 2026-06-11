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
* @brief  Declarations of API resources for textures.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_TextureInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_UserPtr.h>
#include <nn/gfx/detail/gfx_Misc.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_Texture-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_Texture-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_Texture-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_Texture-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_Texture-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_Texture-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a texture.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TTexture
    : public detail::TextureImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TTexture );

    typedef detail::TextureImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the sampler.
*/
    typedef TextureInfo InfoType;

/**
* @brief  Boolean value indicating whether a memory pool is required at initialization time.
*/
    static const bool IsMemoryPoolRequired = Impl::IsMemoryPoolRequired;

/**
* @brief  Calculates the alignment requested by the pointer of the mipmap data base level data pointer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment requested by the initial data of the mipmap data.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @details
*  A return value of <tt>1</tt> indicates that no alignment was requested.
*/
    static size_t CalculateMipDataAlignment( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataAlignment( pDevice, info );
    }

/**
* @brief  Calculates the alignment requested by the pointer of the mipmap data base level data pointer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the alignment requested by the initial data of the mipmap data.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @details
*  A return value of <tt>1</tt> indicates that no alignment was requested.
*/
    static size_t CalculateMipDataAlignment( TDevice< Target >* pDevice, const TTextureInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataAlignment( pDevice, info );
    }

/**
* @brief  Calculates the total size requested by the mipmap data.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the overall size for the mipmap data, including the base level, in bytes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*/
    static size_t CalculateMipDataSize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataSize( pDevice, info );
    }

/**
* @brief  Calculates the total size requested by the mipmap data.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the overall size for the mipmap data, including the base level, in bytes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*/
    static size_t CalculateMipDataSize( TDevice< Target >* pDevice, const TTextureInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataSize( pDevice, info );
    }

/**
* @brief  Calculates the alignment required of the pointer to the base level data of the mipmap data and the overall size of the mipmap data.
*
* @param[out] pOutSize  Pointer for storing the overall size of the mipmap data.
* @param[out] pOutAlignment  Pointer for storing the alignment required of the first of the mipmap data.
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pOutSize</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutAlignment</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @details
*  This function gets the values that were obtained by <tt>CalculateMipDataSize()</tt> and <tt>CalculateMipDataAlignment()</tt>. Depending on the low-level API, this can reduce the computational overhead compared to making individual calls to these functions.
*/
    static void CalculateMipDataSizeAndAlignment( size_t* pOutSize, size_t* pOutAlignment, TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataSizeAndAlignment( pOutSize, pOutAlignment, pDevice, info );
    }

/**
* @brief  Calculates the alignment required of the pointer to the base level data of the mipmap data and the overall size of the mipmap data.
*
* @param[out] pOutSize  Pointer for storing the overall size of the mipmap data.
* @param[out] pOutAlignment  Pointer for storing the alignment required of the first of the mipmap data.
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pOutSize</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutAlignment</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @details
*  This function gets the values that were obtained by <tt>CalculateMipDataSize()</tt> and <tt>CalculateMipDataAlignment()</tt>. Depending on the low-level API, this can reduce the computational overhead compared to making individual calls to these functions.
*/
    static void CalculateMipDataSizeAndAlignment( size_t* pOutSize, size_t* pOutAlignment, TDevice< Target >* pDevice, const TTextureInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataSizeAndAlignment( pOutSize, pOutAlignment, pDevice, info );
    }

/**
* @brief  Calculates the appropriate offset from the base level data pointer for each mipmap data.
*
* @param[out] pMipOffsets  Pointer to an array that has <tt><var>storesinfo</var>.GetMipCount</tt> elements for storing mipmap offsets.
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pMipOffsets</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*/
    static void CalculateMipDataOffsets( ptrdiff_t* pMipOffsets, TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataOffsets( pMipOffsets, pDevice, info );
    }

/**
* @brief  Calculates the appropriate offset from the base level data pointer for each mipmap data.
*
* @param[out] pMipOffsets  Pointer to an array that has <tt><var>storesinfo</var>.GetMipCount</tt> elements for storing mipmap offsets.
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pMipOffsets</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*/
    static void CalculateMipDataOffsets( ptrdiff_t* pMipOffsets, TDevice< Target >* pDevice, const TTextureInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::CalculateMipDataOffsets( pMipOffsets, pDevice, info );
    }

/**
* @brief  Gets the line feed for the linear texture.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the line feed in bytes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @details
*  The line feed is expressed as the number of bytes from one pixel in one column to the same pixel in the same column but in the next row.
*/
    static size_t GetRowPitch( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::GetRowPitch( pDevice, info );
    }

/**
* @brief  Gets the line feed for the linear texture.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the line feed in bytes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @details
*  The line feed is expressed as the number of bytes from one pixel in one column to the same pixel in the same column but in the next row.
*/
    static size_t GetRowPitch( TDevice< Target >* pDevice, const TTextureInfo< Target >& info ) NN_NOEXCEPT
    {
        return Impl::GetRowPitch( pDevice, info );
    }

/**
* @brief  Constructor.
*/
    TTexture() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a texture.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pMemoryPool  Pointer to the memory pool where the texture mipmap data is placed.
* @param[in] memoryPoolOffset  Offset to the memory pool where the texture's mipmap data is placed, in bytes.
* @param[in] memoryPoolSize  The size, in bytes, of the memory pool the texture uses.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The sampler is not initialized.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>pMemoryPool</var></tt> != <tt>NULL</tt>.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>memoryPoolSize</var></tt> is larger than the size obtained by <tt>CalculateMipDataSize</tt>.
*
* @post
*  - The sampler is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info,
        TMemoryPool< Target >* pMemoryPool, ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info, pMemoryPool, memoryPoolOffset, memoryPoolSize );
    }

/**
* @brief  Initializes a texture.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pMemoryPool  Pointer to the memory pool where the texture mipmap data is placed.
* @param[in] memoryPoolOffset  Offset to the memory pool where the texture's mipmap data is placed, in bytes.
* @param[in] memoryPoolSize  The size, in bytes, of the memory pool the texture uses.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The sampler is not initialized.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>pMemoryPool</var></tt> != <tt>NULL</tt>.
*  - If <tt>IsMemoryPoolRequired</tt> is <tt>true</tt>, <tt><var>memoryPoolSize</var></tt> is larger than the size obtained by <tt>CalculateMipDataSize</tt>.
*
* @post
*  - The sampler is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const TTextureInfo< Target >& info,
        TMemoryPool< Target >* pMemoryPool, ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info, pMemoryPool, memoryPoolOffset, memoryPoolSize );
    }

/**
* @brief  Destroys a texture.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The sampler is initialized.
*
* @post
*  - The sampler is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
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
*  - The sampler is initialized.
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
* @brief  Graphics abstraction layer representing a texture view.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TTextureView
    : public detail::TextureViewImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TTextureView );

    typedef detail::TextureViewImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing a texture view.
*/
    typedef TextureViewInfo InfoType;

/**
* @brief  Constructor.
*/
    TTextureView() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a texture view.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The texture view is not initialized.
*
* @post
*  - The texture view is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys a texture view.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The texture view is initialized.
*
* @post
*  - The texture view is not initialized.
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

/**
* @brief  Graphics abstraction layer representing a color target view.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TColorTargetView
    : public detail::ColorTargetViewImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TColorTargetView );

    typedef detail::ColorTargetViewImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the color target view.
*/
    typedef ColorTargetViewInfo InfoType;

/**
* @brief  Constructor.
*/
    TColorTargetView() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a color target view.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The color target view is not initialized.
*
* @post
*  - The color target view is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys the color target view.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The color target view is initialized.
*
* @post
*  - The color target view is not initialized.
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

/**
* @brief  Graphics abstraction layer representing a depth stencil view.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TDepthStencilView
    : public detail::DepthStencilViewImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TDepthStencilView );

    typedef detail::DepthStencilViewImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the depth stencil view.
*/
    typedef DepthStencilViewInfo InfoType;

/**
* @brief  Constructor.
*/
    TDepthStencilView() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the depth stencil view.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The depth stencil view is not initialized.
*
* @post
*  - The depth stencil view is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys the depth stencil view.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The depth stencil view is initialized.
*
* @post
*  - The depth stencil view is not initialized.
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

/**
* @brief  Gets the properties of the image format.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[out] pOutImageFormatProperty  Pointer to the location to store the obtained image format properties.
* @param[in] pDevice  Pointer to the device.
* @param[in] imageFormat  The image format to get information about.
*
* @pre
*  - <tt><var>pOutImageFormatProperty</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @post
*  - The region pointed to by <tt><var>pOutImageFormatProperty</var></tt> stores the property information for the image format.
*/
template< typename TTarget >
inline void GetImageFormatProperty( ImageFormatProperty* pOutImageFormatProperty,
    TDevice< TTarget >* pDevice, ImageFormat imageFormat ) NN_NOEXCEPT
{
    return detail::GetImageFormatProperty< typename detail::TargetVariation<
        TTarget >::Type >( pOutImageFormatProperty, pDevice, imageFormat );
}

}
}
