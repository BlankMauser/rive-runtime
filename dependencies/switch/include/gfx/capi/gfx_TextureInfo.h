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
* @brief  Declarations for API resources for texture initialization information.
*/

#pragma once

#include <limits>

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_DataAccessorConverter.h>
#include <nn/gfx/gfx_TextureInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>

#if !defined( NN_GFX_CONFIG_DISABLE_TINFO )

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_TextureInfo-api.nvn.8.h>
#endif

#endif

namespace nn {
namespace gfx {

class TextureMipRange;
class TextureArrayRange;
class TextureSubresourceRange;

/**
* @brief  The class representing the information for initializing a texture.
*/
class TextureInfo
    : public detail::DataContainer< TextureInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TextureInfo() NN_NOEXCEPT
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
    * - SetImageStorageDimension( nn::gfx::ImageStorageDimension_2d );
    * - SetImageFormat( nn::gfx::ImageFormat_Undefined );
    * - SetGpuAccessFlags( 0 );
    * - SetTileMode( nn::gfx::TileMode_Optimal );
    * - SetWidth( 1 );
    * - SetHeight( 1 );
    * - SetDepth( 1 );
    * - SetMipCount( 1 );
    * - SetArrayLength( 0 );
    * - SetSwizzle( 0 );
    * - SetMultiSampleCount( 1 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the dimension of the image data.
    *
* @param[in] value  The dimension of the image data.
    *
* @post
    * - The dimension of the image data has been set.
*/
    void SetImageStorageDimension( ImageStorageDimension value ) NN_NOEXCEPT
    {
        this->imageStorageDimension = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the image format.
    *
* @param[in] value  Image format.
    *
* @post
    * - The image format is set.
*/
    void SetImageFormat( ImageFormat value ) NN_NOEXCEPT
    {
        this->imageFormat = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets the method of access for the GPU.
    *
* @param[in] value  A means of GPU access comprising a combination of <tt>nn::gfx::GpuAccess</tt> values.
    *
* @post
    * - The access method for the GPU is set.
*/
    void SetGpuAccessFlags( int value ) NN_NOEXCEPT
    {
        this->gpuAccessFlags = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets the tiling mode.
    *
* @param[in] value  Tiling mode.
    *
* @post
    * - The tiling mode is set.
*/
    void SetTileMode( TileMode value ) NN_NOEXCEPT
    {
        this->tileMode = static_cast< Bit16 >( value );
    }

/**
* @brief  Sets the width of the base level image.
    *
* @param[in] value  The width of the base level image.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The base level image width is set.
*/
    void SetWidth( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->width = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the height of the base level image.
    *
* @param[in] value  Height of the base level image.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The base level image height is set.
*/
    void SetHeight( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->height = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the height of the base level image.
    *
* @param[in] value  Depth of the base level image.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The base level image depth is set.
*/
    void SetDepth( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->depth = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the length of the array.
    *
* @param[in] value  The length of the array.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The length of the array is set.
*/
    void SetArrayLength( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->arrayLength = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the swizzling base value.
    *
* @param[in] value  Swizzling base value.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The swizzling base value is set.
*/
    void SetSwizzle( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->swizzle = static_cast< uint16_t >( value );
    }

/**
* @brief  Sets the number of multisamples.
    *
* @param[in] value  Number of multisamples.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The number of multisamples is set.
*/
    void SetMultiSampleCount( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->multisampleCount = static_cast< uint16_t >( value );
    }

/**
* @brief  Sets the number of mipmaps.
    *
* @param[in] value  Number of mipmaps, including the base level.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The number of mipmaps is set.
*/
    void SetMipCount( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->mipCount = static_cast< uint16_t >( value );
    }

/**
* @brief  Gets the dimension of the image data.
    *
* @return  Returns the dimension of the image data.
*/
    ImageStorageDimension GetImageStorageDimension() const NN_NOEXCEPT
    {
        return static_cast< ImageStorageDimension >( this->imageStorageDimension );
    }

/**
* @brief  Gets the image format.
    *
* @return  Returns the image format.
*/
    ImageFormat GetImageFormat() const NN_NOEXCEPT
    {
        return static_cast< ImageFormat >( this->imageFormat );
    }

/**
* @brief  Gets the method of access for the GPU.
    *
* @return  Returns the access method for the GPU.
*/
    int GetGpuAccessFlags() const NN_NOEXCEPT
    {
        return static_cast< int >( this->gpuAccessFlags );
    }

/**
* @brief  Gets the tiling mode.
    *
* @return  Returns the tiling mode.
*/
    TileMode GetTileMode() const NN_NOEXCEPT
    {
        return static_cast< TileMode >( this->tileMode );
    }

/**
* @brief  Gets the width of the base level image.
    *
* @return  Returns the width of the base level image.
*/
    int GetWidth() const NN_NOEXCEPT
    {
        return static_cast< int >( this->width );
    }

/**
* @brief  Gets the height of the base level image.
    *
* @return  Returns the height of the base level image.
*/
    int GetHeight() const NN_NOEXCEPT
    {
        return static_cast< int >( this->height );
    }

/**
* @brief  Gets the depth of the base level image.
    *
* @return  Returns the depth of the base level image.
*/
    int GetDepth() const NN_NOEXCEPT
    {
        return static_cast< int >( this->depth );
    }

/**
* @brief  Gets the number of mipmaps.
    *
* @return  Returns the number of mipmaps.
*/
    int GetMipCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->mipCount );
    }

/**
* @brief  Gets the array length.
    *
* @return  Returns the array length.
*/
    int GetArrayLength() const NN_NOEXCEPT
    {
        return static_cast< int >( this->arrayLength );
    }

/**
* @brief  Gets the swizzling base value.
    *
* @return  Returns the swizzling base value.
*/
    int GetSwizzle() const NN_NOEXCEPT
    {
        return static_cast< int >( this->swizzle );
    }

/**
* @brief  Gets the number of multisamples.
    *
* @return  Returns the number of multisamples.
*/
    int GetMultisampleCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->multisampleCount );
    }
};

/**
* @brief  The class representing the information for initializing a texture view.
*/
class TextureViewInfo
    : public detail::DataContainer< TextureViewInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TextureViewInfo() NN_NOEXCEPT
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
    * - SetImageDimension( nn::gfx::ImageDimension_2d );
    * - SetDepthStencilTextureMode( nn::gfx::DepthStencilFetchMode_DepthComponent );
    * - SetImageFormat( nn::gfx::ImageFormat_Undefined );
    * - EditSubresourceRange().SetDefault();
    * - SetChannelMapping( nn::gfx::ChannelMapping_Red, nn::gfx::ChannelMapping_Green,
*  nn::gfx::ChannelMapping_Blue, nn::gfx::ChannelMapping_Alpha );
    * - SetTexturePtr( NULL );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the image dimensions.
    *
* @param[in] value  The dimension of the image.
    *
* @post
    * - The dimension of the image has been set.
    *
* @details
    * The value to set must be compatible with the dimensions of the texture set with <tt>SetTexturePtr</tt>.
*/
    void SetImageDimension( ImageDimension value ) NN_NOEXCEPT
    {
        this->imageDimension = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the fetch mode for a depth stencil texture.
    *
* @param[in] value  Fetch mode for depth stencil textures.
    *
* @post
    * - Fetch mode for depth stencil texture is set.
    *
* @details
    * Set only for depth stencil texture. Setting is exclusive with <tt>SetChannelMapping</tt>.
*/
    void SetDepthStencilTextureMode( DepthStencilFetchMode value ) NN_NOEXCEPT
    {
        this->depthStencilTextureMode = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the image format.
    *
* @param[in] value  Image format.
    *
* @post
    * - The image format is set.
    *
* @details
    * The value to set must be compatible with the format of the texture set with <tt>SetTexturePtr</tt>.
*/
    void SetImageFormat( ImageFormat value ) NN_NOEXCEPT
    {
        this->imageFormat = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets the texture to access.
    *
* @tparam TTarget  The low-level graphics API for the texture.
    *
* @param[in] value  Pointer to the texture to access.
    *
* @post
    * - The texture to access is set.
    *
* @details
*  <tt><var>TTarget</var></tt> must be the same as <tt><var>TTarget</var></tt> for the texture view you intend to initialize.
*/
    template< typename TTarget >
    void SetTexturePtr( const TTexture< TTarget >* value ) NN_NOEXCEPT
    {
        this->pTexture = value;
    }

/**
* @brief  Sets the texture to access.
    *
* @param[in] value  Pointer to the texture to access.
    *
* @post
    * - The texture to access is set.
    *
* @details
*  If you are setting any value other than <tt>NULL</tt>, call the version with a template argument.
*/
    void SetTexturePtr( const void* value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value == NULL );
        this->pTexture = value;
    }

/**
* @brief  Sets RGBA element mapping.
    *
* @param[in] red  Mapping for the red element.
* @param[in] green  Mapping for the green element.
* @param[in] blue  Mapping for the blue element.
* @param[in] alpha  Mapping for the alpha element.
    *
* @post
    * - RGBA element mapping is set.
    *
* @details
    * Set only for color texture. This setting is exclusive with <tt>SetDepthStencilTextureMode</tt>.
*/
    void SetChannelMapping( ChannelMapping red, ChannelMapping green,
        ChannelMapping blue, ChannelMapping alpha ) NN_NOEXCEPT
    {
        this->channelMapping[ 0 ] = static_cast< Bit8 >( red );
        this->channelMapping[ 1 ] = static_cast< Bit8 >( green );
        this->channelMapping[ 2 ] = static_cast< Bit8 >( blue );
        this->channelMapping[ 3 ] = static_cast< Bit8 >( alpha );
    }

/**
* @brief  Edits the image range to access.
    *
* @return  Returns a reference to the image range to reference.
    *
* @details
    * The range to edit must be within the image range for the texture set with <tt>SetTexturePtr</tt>.
*/
    TextureSubresourceRange& EditSubresourceRange() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->subresourceRange );
    }

/**
* @brief  Gets the dimension of the image.
    *
* @return  Returns the dimension of the image.
*/
    ImageDimension GetImageDimension() const NN_NOEXCEPT
    {
        return static_cast< ImageDimension >( this->imageDimension );
    }

/**
* @brief  Gets the fetch mode for a depth stencil texture.
    *
* @return  Returns the fetch mode for a depth stencil texture.
*/
    DepthStencilFetchMode GetDepthStencilTextureMode() const NN_NOEXCEPT
    {
        return static_cast< DepthStencilFetchMode >( this->depthStencilTextureMode );
    }

/**
* @brief  Gets the image format.
    *
* @return  Returns the image format.
*/
    ImageFormat GetImageFormat() const NN_NOEXCEPT
    {
        return static_cast< ImageFormat >( this->imageFormat );
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets the texture to access.
    *
* @return  Returns a pointer to a <code>nn::gfx::Texture</code>-type texture to access.
    *
* @details
    * Assign the value returned by this function to a <tt>nn::gfx::Texture</tt>-type pointer.
*/
    const Texture* GetTexturePtr() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetTexturePtr() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( this->pTexture.ptr );
    }
#endif

/**
* @brief  Gets the element mapping.
    *
* @param[in] channel  Color element of the mapping to get.
    *
* @return  Returns the mapping of an element.
*/
    ChannelMapping GetChannelMapping( ColorChannel channel ) const NN_NOEXCEPT
    {
        return static_cast< ChannelMapping >( this->channelMapping[ channel ] );
    }

/**
* @brief  Gets the image range to access.
    *
* @return  Returns the image range to access.
*/
    const TextureSubresourceRange& GetSubresourceRange() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->subresourceRange );
    }
};

/**
* @brief  Class representing the information for initializing the color target view.
*/
class ColorTargetViewInfo
    : public detail::DataContainer< ColorTargetViewInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    ColorTargetViewInfo() NN_NOEXCEPT
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
    * - SetImageDimension( nn::gfx::ImageDimension_2D );
    * - SetImageFormat( nn::gfx::ImageFormat_Undefined );
    * - SetMipLevel( 0 );
    * - EditArrayRange().SetDefault();
    * - SetTexturePtr( NULL );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the image dimensions.
    *
* @param[in] value  The dimension of the image.
    *
* @post
    * - The dimension of the image has been set.
    *
* @details
    * The dimension to set must be compatible with the dimensions of the texture set with <tt>SetTexturePtr</tt>.
*/
    void SetImageDimension( ImageDimension value ) NN_NOEXCEPT
    {
        this->imageDimension = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the image format.
    *
* @param[in] value  Image format.
    *
* @post
    * - The image format is set.
    *
* @details
    * The format to set must be compatible with the format of the texture set with <tt>SetTexturePtr</tt>.
*/
    void SetImageFormat( ImageFormat value ) NN_NOEXCEPT
    {
        this->imageFormat = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets a single mipmap level to access.
    *
* @param[in] value  Mipmap level to access.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The single mipmap level to access is set.
    *
* @details
    * The value to set must be within the mipmap range for the texture set with <tt>SetTexturePtr</tt>.
*/
    void SetMipLevel( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->mipLevel = static_cast< uint16_t >( value );
    }

/**
* @brief  Sets the texture to access.
    *
* @tparam TTarget  The low-level graphics API for the texture.
    *
* @param[in] value  Pointer to the texture to access.
    *
* @post
    * - The texture to access is set.
    *
* @details
    * The format of the texture to access must be a color format.
*  <tt><var>TTarget</var></tt> must be the same as <tt><var>TTarget</var></tt> for the texture view you intend to initialize.
*/
    template< typename TTarget >
    void SetTexturePtr( const TTexture< TTarget >* value ) NN_NOEXCEPT
    {
        this->pTexture = value;
    }

/**
* @brief  Sets the texture to access.
    *
* @param[in] value  Pointer to the texture to access.
    *
* @post
    * - The texture to access is set.
    *
* @details
*  If you are setting any value other than <tt>NULL</tt>, call the version with a template argument.
*/
    void SetTexturePtr( const void* value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value == NULL );
        this->pTexture = value;
    }

/**
* @brief  Edits the array range to access.
    *
* @return  Returns the array range to reference.
    *
* @details
    * The content to edit must be within the array for the texture set with <tt>SetTexturePtr</tt>.
*/
    TextureArrayRange& EditArrayRange() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->arrayRange );
    }

/**
* @brief  Gets the dimension of the image.
    *
* @return  Returns the dimension of the image.
*/
    ImageDimension GetImageDimension() const NN_NOEXCEPT
    {
        return static_cast< ImageDimension >( this->imageDimension );
    }

/**
* @brief  Gets the image format.
    *
* @return  Returns the image format.
*/
    ImageFormat GetImageFormat() const NN_NOEXCEPT
    {
        return static_cast< ImageFormat >( this->imageFormat );
    }

/**
* @brief  Gets the mipmap level to reference.
    *
* @return  Returns the mipmap level to reference.
*/
    int GetMipLevel() const NN_NOEXCEPT
    {
        return static_cast< int >( this->mipLevel );
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets the texture to access.
    *
* @return  Returns a pointer to a <code>nn::gfx::Texture</code>-type texture to access.
    *
* @details
    * Assign the value returned by this function to a <tt>nn::gfx::Texture</tt>-type pointer.
*/
    const Texture* GetTexturePtr() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetTexturePtr() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( this->pTexture.ptr );
    }
#endif

/**
* @brief  Gets the array range to access.
    *
* @return  Returns a reference to the texture range to reference.
*/
    const TextureArrayRange& GetArrayRange() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->arrayRange );
    }
};

/**
* @brief  Class representing the information for initializing the depth stencil view.
*/
class DepthStencilViewInfo
    : public detail::DataContainer< DepthStencilViewInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    DepthStencilViewInfo() NN_NOEXCEPT
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
    * - SetImageDimension( nn::gfx::ImageDimension_2d );
    * - SetMipLevel( 0 );
    * - EditArrayRange().SetDefault();
    * - SetTexturePtr( NULL );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the image dimensions.
    *
* @param[in] value  The dimension of the image.
    *
* @post
    * - The dimension of the image has been set.
    *
* @details
    * The image to set must be compatible with the dimensions of the texture set with <tt>SetTexturePtr</tt>.
*/
    void SetImageDimension( ImageDimension value ) NN_NOEXCEPT
    {
        this->imageDimension = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets a single mipmap level to access.
    *
* @param[in] value  Mipmap level to access.
    *
* @post
    * - The single mipmap level to access is set.
*/
    void SetMipLevel( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->mipLevel = static_cast< uint16_t >( value );
    }

/**
* @brief  Sets the texture to access.
    *
* @tparam TTarget  The low-level graphics API for the texture.
    *
* @param[in] value  Pointer to the texture to access.
    *
* @post
    * - The texture to access is set.
    *
* @details
    * The format of the texture to access must be a depth stencil format.
*  <tt><var>TTarget</var></tt> must be the same as <tt><var>TTarget</var></tt> for the texture view you intend to initialize.
*/
    template< typename TTarget >
    void SetTexturePtr( const TTexture< TTarget >* value ) NN_NOEXCEPT
    {
        this->pTexture = value;
    }

/**
* @brief  Sets the texture to access.
    *
* @param[in] value  Pointer to the texture to access.
    *
* @post
    * - The texture to access is set.
    *
* @details
*  If you are setting any value other than <tt>NULL</tt>, call the version with a template argument.
*/
    void SetTexturePtr( const void* value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value == NULL );
        this->pTexture = value;
    }

/**
* @brief  Edits the array range to access.
    *
* @return  Returns the array range to reference.
*/
    TextureArrayRange& EditArrayRange() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->arrayRange );
    }

/**
* @brief  Gets the dimension of the image.
    *
* @return  Returns the dimension of the image.
*/
    ImageDimension GetImageDimension() const NN_NOEXCEPT
    {
        return static_cast< ImageDimension >( this->imageDimension );
    }

/**
* @brief  Gets a single mipmap level to access.
    *
* @return  Returns the single mipmap level to reference.
*/
    int GetMipLevel() const NN_NOEXCEPT
    {
        return static_cast< int >( this->mipLevel );
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets the texture to access.
    *
* @return  Returns a pointer to a <code>nn::gfx::Texture</code>-type texture to access.
    *
* @details
    * Assign the value returned by this function to a <tt>nn::gfx::Texture</tt>-type pointer.
*/
    const Texture* GetTexturePtr() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetTexturePtr() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( this->pTexture.ptr );
    }
#endif

/**
* @brief  Gets the array range to access.
    *
* @return  Returns the array range to reference.
*/
    const TextureArrayRange& GetArrayRange() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->arrayRange );
    }
};

/**
* @brief  Class that indicates a range of texture mipmaps.
*/
class TextureMipRange
    : public detail::DataContainer< TextureMipRangeData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TextureMipRange() NN_NOEXCEPT
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
    * - SetMinMipLevel( 0 );
    * - SetMipCount( 1 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the minimum mipmap level.
    *
* @param[in] value  Minimum mipmap level.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The minimum mipmap level is set.
*/
    void SetMinMipLevel( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->minMipLevel = static_cast< uint16_t >( value );
    }

/**
* @brief  Sets the number of mipmaps.
    *
* @param[in] value  Number of mipmaps.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The number of mipmaps is set.
*/
    void SetMipCount( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->mipCount = static_cast< uint16_t >( value );
    }

/**
* @brief  Gets the minimum mipmap level.
    *
* @return  Returns the minimum mipmap level.
*/
    int GetMinMipLevel() const NN_NOEXCEPT
    {
        return static_cast< int >( this->minMipLevel );
    }

/**
* @brief  Gets the number of mipmaps.
    *
* @return  Returns the number of mipmaps.
*/
    int GetMipCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->mipCount );
    }
};

/**
* @brief  Class that indicates a texture array range.
*/
class TextureArrayRange
    : public detail::DataContainer< TextureArrayRangeData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TextureArrayRange() NN_NOEXCEPT
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
    * - SetBaseArrayIndex( 0 );
    * - SetArrayLength( 1 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the base value of an array index.
    *
* @param[in] value  Array index base value.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The array index base value is set.
*/
    void SetBaseArrayIndex( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->baseArrayIndex = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the length of the array.
    *
* @param[in] value  The length of the array.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The length of the array is set.
*/
    void SetArrayLength( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->arrayLength = static_cast< uint32_t >( value );
    }

/**
* @brief  Gets the base value of an array index.
    *
* @return  Returns the array index base value.
*/
    int GetBaseArrayIndex() const NN_NOEXCEPT
    {
        return static_cast< int >( this->baseArrayIndex );
    }

/**
* @brief  Gets the array length.
    *
* @return  Returns the array length.
*/
    int GetArrayLength() const NN_NOEXCEPT
    {
        return static_cast< int >( this->arrayLength );
    }
};


/**
* @brief  Class that indicates an image range in a texture.
*/
class TextureSubresourceRange
    : public detail::DataContainer< TextureSubresourceRangeData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TextureSubresourceRange() NN_NOEXCEPT
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
    * - EditMipRange().SetDefault();
    * - EditArrayRange().SetDefault();
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Edits a mipmap range.
    *
* @return  Returns a reference to a mipmap range.
*/
    TextureMipRange& EditMipRange() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->mipRange );
    }

/**
* @brief  Edits an array range.
    *
* @return  Returns a reference to an array range.
*/
    TextureArrayRange& EditArrayRange() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->arrayRange );
    }

/**
* @brief  Gets a mipmap range.
    *
* @return  Returns a reference to a mipmap range.
*/
    const TextureMipRange& GetMipRange() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->mipRange );
    }

/**
* @brief  Gets an array range.
    *
* @return  Returns a reference to an array range.
*/
    const TextureArrayRange& GetArrayRange() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->arrayRange );
    }
};

/**
* @brief  Class that indicates a specific image in a texture.
*/
class TextureSubresource
    : public detail::DataContainer< TextureSubresourceData >
{
public:
/**
    * Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TextureSubresource() NN_NOEXCEPT
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
    * - SetMipLevel( 0 );
    * - SetArrayIndex( 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets a single mipmap level.
    *
* @param[in] value  The mipmap level.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The mipmap level is set.
*/
    void SetMipLevel( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->mipLevel = static_cast< uint16_t >( value );
    }

/**
* @brief  Sets a single array index.
    *
* @param[in] value  The array index.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The array index is set.
*/
    void SetArrayIndex( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->arrayIndex = static_cast< uint32_t >( value );
    }

/**
* @brief  Gets a mipmap level.
    *
* @return  Returns the mipmap level.
*/
    int GetMipLevel() const NN_NOEXCEPT
    {
        return static_cast< int >( this->mipLevel );
    }

/**
* @brief  Gets an array index.
    *
* @return  Returns the array index.
*/
    int GetArrayIndex() const NN_NOEXCEPT
    {
        return static_cast< int >( this->arrayIndex );
    }
};

/**
* @brief  Class that indicates a range of texture copy operations.
*/
class TextureCopyRegion
    : public detail::DataContainer< TextureCopyRegionData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TextureCopyRegion() NN_NOEXCEPT
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
    * - SetOffsetU( 0 );
    * - SetOffsetV( 0 );
    * - SetOffsetW( 0 );
    * - SetWidth( 1 );
    * - SetHeight( 1 );
    * - SetDepth( 1 );
    * - EditSubresource().SetDefault();
    * - SetArrayLength( 1 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the offset for the u-coordinate.
    *
* @param[in] value  U-coordinate offset.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The u-coordinate offset is set.
*/
    void SetOffsetU( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->offsetU = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the offset for the v-coordinate.
    *
* @param[in] value  V-coordinate offset.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The v-coordinate offset is set.
*/
    void SetOffsetV( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->offsetV = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the offset for the w-coordinate.
    *
* @param[in] value  W-coordinate offset.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The w-coordinate offset is set.
*/
    void SetOffsetW( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->offsetW = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the width.
    *
* @param[in] value  The width.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The width is set.
*/
    void SetWidth( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->width = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the height.
    *
* @param[in] value  The height.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The height is set.
*/
    void SetHeight( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->height = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the depth.
    *
* @param[in] value  Depth.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The depth is set.
*/
    void SetDepth( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->depth = static_cast< uint32_t >( value );
    }

/**
* @brief  Edits the parameter that specifies an image.
    *
* @return  Returns a reference to the parameter that specifies an image.
*/
    TextureSubresource& EditSubresource() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->subresource );
    }

/**
* @brief  Sets the length of the array.
    *
* @param[in] value  The length of the array.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The length of the array is set.
*/
    void SetArrayLength( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->arrayLength = static_cast< uint32_t >( value );
    }

/**
* @brief  Gets the offset for the u-coordinate.
    *
* @return  Returns the u-coordinate offset.
*/
    int GetOffsetU() const NN_NOEXCEPT
    {
        return static_cast< int >( this->offsetU );
    }

/**
* @brief  Gets the offset for the v-coordinate.
    *
* @return  Returns the v-coordinate offset.
*/
    int GetOffsetV() const NN_NOEXCEPT
    {
        return static_cast< int >( this->offsetV );
    }

/**
* @brief  Gets the offset for the w-coordinate.
    *
* @return  Returns the w-coordinate offset.
*/
    int GetOffsetW() const NN_NOEXCEPT
    {
        return static_cast< int >( this->offsetW );
    }

/**
* @brief  Gets the width.
    *
* @return  Returns the width.
*/
    int GetWidth() const NN_NOEXCEPT
    {
        return static_cast< int >( this->width );
    }

/**
* @brief  Gets the height.
    *
* @return  Returns the height.
*/
    int GetHeight() const NN_NOEXCEPT
    {
        return static_cast< int >( this->height );
    }

/**
* @brief  Gets the depth.
    *
* @return  Returns the depth.
*/
    int GetDepth() const NN_NOEXCEPT
    {
        return static_cast< int >( this->depth );
    }

/**
* @brief  Gets the parameter that specifies an image.
    *
* @return  Returns a reference to the parameter that specifies an image.
*/
    const TextureSubresource& GetSubresource() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->subresource );
    }

/**
* @brief  Gets the array length.
    *
* @return  Returns the array length.
*/
    int GetArrayLength() const NN_NOEXCEPT
    {
        return static_cast< int >( this->arrayLength );
    }
};

/**
* @brief  The class representing the range of the copy operation between a buffer and a texture.
*/
class BufferTextureCopyRegion
    : public detail::DataContainer< BufferTextureCopyRegionData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    BufferTextureCopyRegion() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting all parameters to their default values.
    *
* @post
    * - The various parameters are configured.
    *
* @details
    * Equivalent to calling the following.
    * - SetBufferOffset( 0 );
    * - SetBufferImageWidth( 0 );
    * - SetBufferImageHeight( 0 );
    * - EditTextureCopyRegion().SetDefault();
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the offset in the buffer.
    *
* @param[in] value  The offset in the buffer, in bytes.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The offset in the buffer is set.
*/
    void SetBufferOffset( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->bufferOffset = value;
    }

/**
* @brief  Sets the image width in the buffer.
    *
* @param[in] value  The width of the image in the buffer, in pixels.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The width of the image in the buffer is set.
*/
    void SetBufferImageWidth( int value ) NN_NOEXCEPT
    {
        this->bufferImageWidth = value;
    }

/**
* @brief  Sets the image height in the buffer.
    *
* @param[in] value  The height of the image in the buffer.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The height of the image in the buffer is set.
    *
* @details
    * When <tt>0</tt> is specified, this is considered to be the same as <tt>GetTextureCopyRegion().GetHeight()</tt>.
*/
    void SetBufferImageHeight( int value ) NN_NOEXCEPT
    {
        this->bufferImageHeight = value;
    }

/**
* @brief  Edits the information on the texture copy region.
    *
* @return  Returns a reference to the information for the texture copy region.
*/
    TextureCopyRegion& EditTextureCopyRegion() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->textureCopyRegion );
    }

/**
* @brief  Gets the offset in the buffer.
    *
* @return  Returns the offset in the buffer, in bytes.
*/
    int GetBufferOffset() const NN_NOEXCEPT
    {
        return this->bufferOffset;
    }

/**
* @brief  Gets the width of the image in the buffer.
    *
* @return  Returns the width of the image in the buffer, in pixels.
*/
    int GetBufferImageWidth() const NN_NOEXCEPT
    {
        return this->bufferImageWidth;
    }

/**
* @brief  Gets the height of the image in the buffer.
    *
* @return  Returns the height of the image in the buffer.
*/
    int GetBufferImageHeight() const NN_NOEXCEPT
    {
        return this->bufferImageHeight;
    }

/**
* @brief  Gets the information on the texture copy region.
    *
* @return  Returns a reference to the information for the texture copy region.
*/
    const TextureCopyRegion& GetTextureCopyRegion() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->textureCopyRegion );
    }
};

/**
* @brief  Graphics abstraction layer representing information for initializing a texture.
*/
template< typename TTarget >
class TTextureInfo
    : public detail::TargetInfoImpl< detail::TextureInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, TextureInfo >::Type
{
    typedef typename detail::TargetInfoImpl< detail::TextureInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, TextureInfo >::Type Impl;

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
    static void ConvertFromInfo( TTextureInfo< TTarget >* pDstInfo, const TextureInfo& info ) NN_NOEXCEPT
    {
        return detail::InfoHelper::ConvertFromInfo< Impl >( pDstInfo, info );
    }

/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TTextureInfo() NN_NOEXCEPT
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
    * - SetImageStorageDimension( nn::gfx::ImageStorageDimension_2d );
    * - SetImageFormat( nn::gfx::ImageFormat_Undefined );
    * - SetGpuAccessFlags( 0 );
    * - SetTileMode( nn::gfx::TileMode_Optimal );
    * - SetWidth( 1 );
    * - SetHeight( 1 );
    * - SetDepth( 1 );
    * - SetMipCount( 1 );
    * - SetArrayLength( 0 );
    * - SetSwizzle( 0 );
    * - SetMultiSampleCount( 1 );
*/
    void SetDefault() NN_NOEXCEPT
    {
        return Impl::SetDefault();
    }

/**
* @brief  Sets the dimension of the image data.
    *
* @param[in] value  The dimension of the image data.
    *
* @post
    * - The dimension of the image data has been set.
*/
    void SetImageStorageDimension( ImageStorageDimension value ) NN_NOEXCEPT
    {
        return Impl::SetImageStorageDimension( value );
    }

/**
* @brief  Sets the image format.
    *
* @param[in] value  Image format.
    *
* @post
    * - The image format is set.
*/
    void SetImageFormat( ImageFormat value ) NN_NOEXCEPT
    {
        return Impl::SetImageFormat( value );
    }

/**
* @brief  Sets the method of access for the GPU.
    *
* @param[in] value  A means of GPU access comprising a combination of <tt>nn::gfx::GpuAccess</tt> values.
    *
* @post
    * - The access method for the GPU is set.
*/
    void SetGpuAccessFlags( int value ) NN_NOEXCEPT
    {
        return Impl::SetGpuAccessFlags( value );
    }

/**
* @brief  Sets the tiling mode.
    *
* @param[in] value  Tiling mode.
    *
* @post
    * - The tiling mode is set.
*/
    void SetTileMode( TileMode value ) NN_NOEXCEPT
    {
        return Impl::SetTileMode( value );
    }

/**
* @brief  Sets the width of the base level image.
    *
* @param[in] value  The width of the base level image.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The base level image width is set.
*/
    void SetWidth( int value ) NN_NOEXCEPT
    {
        return Impl::SetWidth( value );
    }

/**
* @brief  Sets the height of the base level image.
    *
* @param[in] value  Height of the base level image.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The base level image height is set.
*/
    void SetHeight( int value ) NN_NOEXCEPT
    {
        return Impl::SetHeight( value );
    }

/**
* @brief  Sets the height of the base level image.
    *
* @param[in] value  Depth of the base level image.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The base level image depth is set.
*/
    void SetDepth( int value ) NN_NOEXCEPT
    {
        return Impl::SetDepth( value );
    }

/**
* @brief  Sets the length of the array.
    *
* @param[in] value  The length of the array.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The length of the array is set.
*/
    void SetArrayLength( int value ) NN_NOEXCEPT
    {
        return Impl::SetArrayLength( value );
    }

/**
* @brief  Sets the swizzling base value.
    *
* @param[in] value  Swizzling base value.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The swizzling base value is set.
*/
    void SetSwizzle( int value ) NN_NOEXCEPT
    {
        return Impl::SetSwizzle( value );
    }

/**
* @brief  Sets the number of multisamples.
    *
* @param[in] value  Number of multisamples.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
    *
* @post
    * - The number of multisamples is set.
*/
    void SetMultiSampleCount( int value ) NN_NOEXCEPT
    {
        return Impl::SetMultiSampleCount( value );
    }

/**
* @brief  Sets the number of mipmaps.
    *
* @param[in] value  Number of mipmaps, including the base level.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt>.
    *
* @post
    * - The number of mipmaps is set.
*/
    void SetMipCount( int value ) NN_NOEXCEPT
    {
        return Impl::SetMipCount( value );
    }
};

}
}
