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
* @brief  Declarations of API resources for texture resource file data.
*/

#pragma once

#include <nn/util/util_BinaryFormat.h>
#include <nn/util/util_ResDic.h>

#include <nn/gfx/gfx_TextureInfoData.h>
#include <nn/gfx/gfx_DescriptorSlot.h>
#include <nn/gfx/gfx_ResUserData.h>

namespace nn {
namespace gfx {

class ResTexture;
class ResTextureFile;
struct ResTextureData;
struct ResTextureContainerData;
struct ResTextureFileData;

/**
* @brief  Structure representing the texture resource.
*/
struct ResTextureData
{
    nn::util::BinaryBlockHeader blockHeader; //!<  The block header.

    TextureInfoData textureInfoData; //!<  Information for initializing the texture.

    uint32_t textureDataSize; //!<  The size of the texture data.
    uint32_t alignment; //!<  The alignment.
    Bit8 channelMapping[ 4 ]; //!<  The <tt>nn::gfx::ChannelMapping</tt> representation of how channels are mapped in RGBA order.
    Bit8 imageDimension; //!<  The <tt>nn::gfx::ImageDimension</tt> representation of the image dimensions.
    char reserved[ 3 ]; //!<  This is a reserved region.
    nn::util::BinPtrToString pName; //!<  The name of the texture.
    nn::util::BinTPtr< ResTextureContainerData > pResTextureContainerData; //!<  Pointer to the texture container resource.
    nn::util::BinTPtr< nn::util::BinTPtr< void > > pMipPtrArray; //!<  Pointer to the array of pointers for the texture data at each mipmap level.
    nn::util::BinTPtr< ResUserData > pUserDataArray; //!<  Pointer to the array of user data.

    nn::util::BinTPtr< void > pTexture; //!<  Pointer to the texture object.
    nn::util::BinTPtr< void > pTextureView; //!<  Pointer to the texture view.

    DescriptorSlotData userDescriptorSlot; //!<  The user descriptor slot.

    nn::util::BinTPtr< nn::util::ResDic > pUserDataDic; //!<  Pointer to the user data dictionary.
};

/**
* @brief  Structure representing the texture container.
*/
struct ResTextureContainerData
{
    char targetPlatform[ 4 ]; //!<  Target Platform
    uint32_t textureCount; //!<  The number of textures.
    nn::util::BinTPtr< nn::util::BinTPtr< ResTexture > > pTexturePtrArray; //!<  Pointer to the array of texture resource pointers.
    nn::util::BinTPtr< void > pTextureData; //!<  Pointer to the texture data block.
    nn::util::BinTPtr< nn::util::ResDic > pTextureDic; //!<  Pointer to the texture name dictionary.

    nn::util::BinTPtr< void > pTextureMemoryPool; //!<  Pointer to the memory pool for textures.

    nn::util::BinTPtr< void > pCurrentMemoryPool; //!<  Pointer to the memory pool currently being used by the texture container.
    uint32_t memoryPoolOffsetBase; //!<  The base value for the offset in the memory pool.

    char reserved[ 4 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing the texture resource file.
*/
struct ResTextureFileData
{
    nn::util::BinaryFileHeader fileHeader; //!<  The file header.
    ResTextureContainerData textureContainerData; //!<  The texture container resource.
};

}
}
