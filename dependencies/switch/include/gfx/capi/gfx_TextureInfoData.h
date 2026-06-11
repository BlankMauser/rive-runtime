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
* @brief  Declarations of API resources for texture initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure that indicates a range of texture mipmaps.
*/
struct TextureMipRangeData
{
    uint16_t minMipLevel; //!<  The minimum mipmap level.
    uint16_t mipCount; //!<  The number of mipmaps.

    char reserved[ 12 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that indicates a texture array range.
*/
struct TextureArrayRangeData
{
    uint32_t baseArrayIndex; //!<  Array index base value.
    uint32_t arrayLength; //!<  The length of the array.

    char reserved[ 8 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that indicates an image range in a texture.
*/
struct TextureSubresourceRangeData
{
    TextureMipRangeData mipRange; //!<  The mipmap range.
    TextureArrayRangeData arrayRange; //!<  The array range.
};

/**
* @brief  The structure representing the information for initializing a texture.
*/
struct TextureInfoData
{
    enum Flag
    {
        Flag_SpecifyTextureLayout,
        Flag_SparseBinding,
        Flag_SparseResidency,
        Flag_ResTexture
    };

    nn::util::BitPack8 flags; //!<  The flags.
    Bit8 imageStorageDimension; //!<  The <tt>nn::gfx::ImageStorageDimension</tt> representation of the image (data) dimensions.
    Bit16 tileMode; //!<  The <tt>nn::gfx::TileMode</tt> representation of the tiling mode.
    uint16_t swizzle; //!<  Default value for swizzling.
    uint16_t mipCount; //!<  The number of mipmaps.
    uint16_t multisampleCount; //!<  The number of multisamples.
    char reserved2[ 2 ]; //!<  This is a reserved region.
    Bit32 imageFormat; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the image format.
    Bit32 gpuAccessFlags; //!<  A combination of <tt>nn::gfx::GpuAccess</tt> values representing the GPU access modes.
    uint32_t width; //!<  The width.
    uint32_t height; //!<  The height.
    uint32_t depth; //!<  The depth.
    uint32_t arrayLength; //!<  The length of the array.
    char textureLayout[ 8 ]; //!<  The texture layout.

    char reserved[ 20 ]; //!<  This is a reserved region.
};

/**
* @brief  The structure representing the information for initializing a texture view.
*/
struct TextureViewInfoData
{
    Bit8 imageDimension; //!<  The <tt>nn::gfx::ImageDimension</tt> representation of the image dimensions.
    Bit8 depthStencilTextureMode; //!<  The <tt>nn::gfx::DepthStencilFetchMode</tt> representation of the texture fetch mode.
    char reserved2[ 2 ]; //!<  This is a reserved region.
    Bit32 imageFormat; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the image format.
    Bit8 channelMapping[ 4 ]; //!<  The <tt>nn::gfx::ChannelMapping</tt> representation of how elements are mapped in RGBA order.
    char reserved3[ 4 ]; //!<  This is a reserved region.
    TextureSubresourceRangeData subresourceRange; //!<  Image range to access.
    detail::Ptr< const void > pTexture; //!<  Texture to access.

    char reserved[ 8 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure that represents the information for initializing a color target view.
*/
struct ColorTargetViewInfoData
{
    Bit8 imageDimension; //!<  The <tt>nn::gfx::ImageDimension</tt> representation of the image dimensions.
    char reserved2; //!<  This is a reserved region.
    uint16_t mipLevel; //!<  The mipmap level to access.
    Bit32 imageFormat; //!<  The <tt>nn::gfx::ImageFormat</tt> representation of the image format.
    TextureArrayRangeData arrayRange; //!<  The array range to access.
    detail::Ptr< const void > pTexture; //!<  Texture to access.

    char reserved[ 16 ];
};

/**
* @brief  Structure representing the information for initializing the depth stencil view.
*/
struct DepthStencilViewInfoData
{
    Bit8 imageDimension; //!<  The <tt>nn::gfx::ImageDimension</tt> representation of the image dimensions.
    char reserved2; //!<  This is a reserved region.
    uint16_t mipLevel; //!<  The mipmap level to access.
    char reserved3[ 4 ]; //!<  This is a reserved region.
    TextureArrayRangeData arrayRange; //!<  The array range to access.
    detail::Ptr< const void > pTexture; //!<  Texture to access.

    char reserved[ 16 ]; //!<  This is a reserved region.
    // Format.
};

/**
* @brief  Structure that indicates a specific image in a texture.
*/
struct TextureSubresourceData
{
    uint16_t mipLevel; //!<  The mipmap level.
    char reserved[ 2 ]; //!<  This is a reserved region.
    uint32_t arrayIndex; //!<  The array index.
};

/**
* @brief  Structure that indicates a range of texture copy operations.
*/
struct TextureCopyRegionData
{
    uint32_t offsetU; //!<  The u-coordinate offset.
    uint32_t offsetV; //!<  The v-coordinate offset.
    uint32_t offsetW; //!<  The w-coordinate offset.
    uint32_t width; //!<  The width.
    uint32_t height; //!<  The height.
    uint32_t depth; //!<  The depth.
    TextureSubresourceData subresource; //!<  Parameters that identify an image.
    uint32_t arrayLength; //!<  The array length.
};

/**
* @brief  Structure that indicates a range of copy operations among buffer textures.
*/
struct BufferTextureCopyRegionData
{
    uint32_t bufferOffset; //!<  The buffer offset, in bytes.
    uint32_t bufferImageWidth; //!<  The width of the image in the buffer.
    uint32_t bufferImageHeight; //!<  The height of the image in the buffer.
    TextureCopyRegionData textureCopyRegion; //!<  The texture copy region.
};

/**
* @brief  The structure representing the image format properties.
*/
struct ImageFormatProperty
{
    Bit32 propertyFlags; //!<  A combination of <tt>nn::gfx::ImageFormatPropertyFlag</tt> values representing property flags for the <tt>TileMode_Optimal</tt> texture.
    Bit32 linearPropertyFlags; //!<  A combination of <tt>nn::gfx::ImageFormatPropertyFlag</tt> values representing property flags for the <tt>TileMode_Linear</tt> texture.
};

}
}
