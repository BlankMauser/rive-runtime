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
* @brief  Declarations of API resources for texture resource files.
*/

#pragma once

#include <nn/util/util_AccessorBase.h>

#include <nn/gfx/gfx_MemoryPoolInfo.h>
#include <nn/gfx/gfx_TextureInfo.h>
#include <nn/gfx/gfx_ResTextureData.h>

#include <nn/gfx/detail/gfx_Declare.h>

namespace nn {
namespace gfx {

/**
* @brief  Class representing texture resources.
*/
class ResTexture
    : public nn::util::AccessorBase< ResTextureData >
{
    NN_DISALLOW_COPY( ResTexture );

public:
/**
* @brief  The signature of the texture resource.
*/
    static const int Signature = NN_UTIL_CREATE_SIGNATURE_4( 'B', 'R', 'T', 'I' );

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static ResTexture* ToAccessor( ResTextureData* pData ) NN_NOEXCEPT
    {
        return static_cast< ResTexture* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static ResTexture& ToAccessor( ResTextureData& data ) NN_NOEXCEPT
    {
        return static_cast< ResTexture& >( data );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static const ResTexture* ToAccessor( const ResTextureData* pData ) NN_NOEXCEPT
    {
        return static_cast< const ResTexture* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static const ResTexture& ToAccessor( const ResTextureData& data ) NN_NOEXCEPT
    {
        return static_cast< const ResTexture& >( data );
    }

/**
* @brief  Gets the information for initializing the texture.
*
* @return  Returns a pointer to the information for initializing the texture.
*/
    TextureInfo* GetTextureInfo() NN_NOEXCEPT
    {
        return DataToAccessor( this->textureInfoData );
    }

/**
* @brief  Gets the information for initializing the texture.
*
* @return  Returns a pointer to the information for initializing the texture.
*/
    const TextureInfo* GetTextureInfo() const NN_NOEXCEPT
    {
        return DataToAccessor( this->textureInfoData );
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a texture object.
*
* @return  Returns a pointer to a <tt>nn::gfx::Texture</tt>-type texture object.
*
* @details
*  Assign a pointer of type <tt>nn::gfx::Texture</tt> for the return value of this function.
*/
    Texture* GetTexture() NN_NOEXCEPT;
#else
    detail::Caster< void > GetTexture() NN_NOEXCEPT
    {
        return detail::Caster< void >( this->pTexture.Get() );
    }
#endif

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a texture object.
*
* @return  Returns a pointer to a <tt>nn::gfx::Texture</tt>-type texture object.
*
* @details
*  Assign a pointer of type <tt>nn::gfx::Texture</tt> for the return value of this function.
*/
    const Texture* GetTexture() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetTexture() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( this->pTexture.Get() );
    }
#endif

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a texture view object.
*
* @return  Returns a pointer to a <tt>nn::gfx::TextureView</tt>-type texture object.
*
* @details
*  Assign a pointer of type <tt>nn::gfx::TextureView</tt> for the return value of this function.
*/
    TextureView* GetTextureView() NN_NOEXCEPT;
#else
    detail::Caster< void > GetTextureView() NN_NOEXCEPT
    {
        return detail::Caster< void >( this->pTextureView.Get() );
    }
#endif

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a texture view object.
*
* @return  Returns a pointer to a <tt>nn::gfx::TextureView</tt>-type texture object.
*
* @details
*  Assign a pointer of type <tt>nn::gfx::TextureView</tt> for the return value of this function.
*/
    const TextureView* GetTextureView() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetTextureView() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( this->pTextureView.Get() );
    }
#endif

/**
* @brief  Initializes a texture.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The texture is not initialized.
*  - The texture resource file to which the texture belongs is initialized.
*
* @post
*  - The texture is initialized.
*
* @details
*  Performs processing equivalent to that of the <tt>Initialize</tt> function of the <tt>nn::gfx::Texture</tt> and <tt>nn::gfx::TextureView</tt> classes.
*/
    template< typename TTarget >
    void Initialize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT;

/**
* @brief  Destroys the texture.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The texture is initialized.
*
* @post
*  - The texture is not initialized.
*
* @details
*  Performs processing equivalent to that of the <tt>Finalize</tt> function of the <tt>nn::gfx::Texture</tt> and <tt>nn::gfx::TextureView</tt> classes.
*/
    template< typename TTarget >
    void Finalize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT;

/**
* @brief  Gets the name of the texture.
*
* @return  Returns a pointer to the string that represents the name of the texture.
*/
    const char* GetName() const NN_NOEXCEPT
    {
        return this->pName.Get()->GetData();
    }

/**
* @brief  Gets the storage size of the texture, in bytes
*
* @return  Returns the storage size of the texture, in bytes.
*/
    size_t GetDataSize() const NN_NOEXCEPT
    {
        return this->textureDataSize;
    }

/**
* @brief  Gets user data.
*
* @param[in] index  The index for the user data to get.
*
* @return  Returns a pointer to the user data.
*/
    ResUserData* GetUserData( int index ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT_RANGE( index, 0, this->pUserDataDic.Get()->GetCount() );
        return &this->pUserDataArray.Get()[ index ];
    }

/**
* @brief  Gets user data.
*
* @param[in] index  The index for the user data to get.
*
* @return  Returns a pointer to the user data.
*/
    const ResUserData* GetUserData( int index ) const NN_NOEXCEPT
    {
        NN_SDK_ASSERT_RANGE( index, 0, this->pUserDataDic.Get()->GetCount() );
        return &this->pUserDataArray.Get()[ index ];
    }

/**
* @brief  Gets the user data dictionary.
*
* @return  Returns a pointer to the user data dictionary.
*/
    const nn::util::ResDic* GetUserDataDic() const NN_NOEXCEPT
    {
        return this->pUserDataDic.Get();
    }

/**
* @brief  Sets an optional descriptor slot.
*
* @param[in] value  The optional descriptor slot to set.
*
* @post
*  - The optional descriptor slot is set.
*/
    void SetUserDescriptorSlot( const DescriptorSlot& value ) NN_NOEXCEPT
    {
        this->userDescriptorSlot = AccessorToData( value );
    }

/**
* @brief  Gets the optional descriptor slot.
*
* @param[in] pOutDescriptorSlot  A pointer for storing the optional descriptor slot that was set.
*
* @pre
*  - <tt><var>pOutDescriptorSlot</var></tt> != <tt>NULL</tt>.
*  - The optional descriptor slot is set.
*/
    void GetUserDescriptorSlot( DescriptorSlot* pOutDescriptorSlot ) const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES_NOT_NULL( pOutDescriptorSlot );
        DescriptorSlot::DataType* pOutDescriptorSlotData = AccessorToData( pOutDescriptorSlot );
        *pOutDescriptorSlotData = this->userDescriptorSlot;
    }
};

/**
* @brief  The texture resource file.
*/
class ResTextureFile
    : public nn::util::AccessorBase< ResTextureFileData >
{
    NN_DISALLOW_COPY( ResTextureFile );

public:
/**
* @brief  The signature of the texture resource file.
*/
    static const int64_t Signature = NN_UTIL_CREATE_SIGNATURE_8('B', 'N', 'T', 'X', 0, 0, 0, 0);

/**
* @brief  The major version of the texture resource file.
*/
    static const int MajorVersion = 4;

/**
* @brief  The minor version of the texture resource file.
*/
    static const int MinorVersion = 1;

/**
* @brief  The micro version of the texture resource file.
*/
    static const int MicroVersion = 0;

/**
* @brief  Gets the maximum value for alignment required for texture resources.
*
* @return  Returns the maximum value for alignment required for texture resources.
*
* @details
*  The precise alignment for each resource is listed in the file header.
*/
    static size_t GetMaxFileAlignment() NN_NOEXCEPT;

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static ResTextureFile* ToAccessor( ResTextureFileData* pData ) NN_NOEXCEPT
    {
        return static_cast< ResTextureFile* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static ResTextureFile& ToAccessor( ResTextureFileData& data ) NN_NOEXCEPT
    {
        return static_cast< ResTextureFile& >( data );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static const ResTextureFile* ToAccessor( const ResTextureFileData* pData ) NN_NOEXCEPT
    {
        return static_cast< const ResTextureFile* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static const ResTextureFile& ToAccessor( const ResTextureFileData& data ) NN_NOEXCEPT
    {
        return static_cast< const ResTextureFile& >( data );
    }

/**
* @brief  Determines whether the binary data is a valid texture file.
*
* @param[in] ptr  Pointer to the binary data.
*
* @return  Returns a Boolean indicating whether the specified binary data is valid as a texture file.
*
* @pre
*  - <tt><var>ptr</var></tt> != <tt>NULL</tt>.
*/
    static bool IsValid( const void* ptr ) NN_NOEXCEPT;

/**
* @brief  Casts binary data to a texture resource file type.
*
* @param[in] ptr  Pointer to the binary data to cast.
*
* @return  Returns a pointer to the cast texture resource file.
*
* @pre
*  - <tt><var>ptr</var></tt> != <tt>NULL</tt>.
*
* @details
*  Do not cast directly. Use this function instead.
*/
    static ResTextureFile* ResCast( void* ptr ) NN_NOEXCEPT;

/**
* @brief  Initializes a texture resource file.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The texture resource file is not initialized.
*
* @post
*  - The texture resource file is initialized.
*/
    template< typename TTarget >
    void Initialize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT;

/**
* @brief  Initializes a texture resource file.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] pMemoryPool  The memory pool where the texture resource file is located.
* @param[in] memoryPoolOffset  The offset, in bytes, to the location of the texture resource file in <tt><var>pMemoryPool</var></tt>.
* @param[in] memoryPoolSize  The size, in bytes, of the pool in <tt><var>pMemoryPool</var></tt>.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @post
*  - The texture resource file is initialized.
*
* @details
*  If <tt><var>pMemoryPool</var></tt> == <tt>NULL</tt>, the function uses a memory pool that holds texture resources to initialize a texture resource file.
*/
    template< typename TTarget >
    void Initialize( TDevice< TTarget >* pDevice, TMemoryPool< TTarget >* pMemoryPool,
        ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT;

/**
* @brief  Destroys a texture resource file.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The texture resource file is initialized.
*
* @post
*  - The texture resource file is not initialized.
*/
    template< typename TTarget >
    void Finalize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT;

/**
* @brief  Gets a texture resource.
*
* @param[in] index  The index for the texture resource to get.
*
* @return  Returns the texture resource.
*/
    ResTexture* GetResTexture( int index ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( index >= 0 && index < static_cast< int >( this->textureContainerData.textureCount ) );
        NN_SDK_ASSERT( this->textureContainerData.pTexturePtrArray.Get() );
        return this->textureContainerData.pTexturePtrArray.Get()[ index ].Get();
    }

/**
* @brief  Gets a texture resource.
*
* @param[in] index  The index for the texture resource to get.
*
* @return  Returns the texture resource.
*/
    const ResTexture* GetResTexture( int index ) const NN_NOEXCEPT
    {
        NN_SDK_ASSERT( index >= 0 && index < static_cast< int >( this->textureContainerData.textureCount ) );
        NN_SDK_ASSERT( this->textureContainerData.pTexturePtrArray.Get() );
        return this->textureContainerData.pTexturePtrArray.Get()[ index ].Get();
    }

/**
* @brief  Gets a texture dictionary.
*
* @return  Returns a pointer to the texture dictionary.
*/
    const nn::util::ResDic* GetTextureDic() const NN_NOEXCEPT
    {
        return this->textureContainerData.pTextureDic.Get();
    }

/**
* @brief  Gets the file header.
*
* @return  Returns the file header.
*
* @see
*  nn::util::BinaryFileHeader
*
* @details
*  This can be used when you want to manually control relocation, for example.
*/
    nn::util::BinaryFileHeader* GetBinaryFileHeader() NN_NOEXCEPT
    {
        return &this->fileHeader;
    }

/**
* @brief  Gets the file header.
*
* @return  Returns the file header.
*
* @see
*  nn::util::BinaryFileHeader
*/
    const nn::util::BinaryFileHeader* GetBinaryFileHeader() const NN_NOEXCEPT
    {
        return &this->fileHeader;
    }
};

template< typename TTarget >
inline void ResTexture::Initialize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
{
    NN_SDK_ASSERT( this->pTexture.Get() );
    NN_SDK_ASSERT( this->pTextureView.Get() );
    const TextureInfo& textureInfo = DataToAccessor( this->textureInfoData );
    ptrdiff_t poolOffset = this->pResTextureContainerData.Get()->memoryPoolOffsetBase +
        nn::util::BytePtr( this->pResTextureContainerData.Get()->pTextureData.Get(),
        sizeof( nn::util::BinaryBlockHeader ) ).Distance( this->pMipPtrArray.Get()[ 0 ].Get() );
    static_cast< TTexture< TTarget >* >( this->pTexture.Get() )->Initialize( pDevice,
        textureInfo, static_cast< TMemoryPool< TTarget >* >(
        this->pResTextureContainerData.Get()->pCurrentMemoryPool.Get() ), poolOffset, this->textureDataSize );

    TextureViewInfo textureViewInfo;
    textureViewInfo.SetDefault();
    textureViewInfo.SetImageDimension( static_cast< ImageDimension >( this->imageDimension ) );
    textureViewInfo.SetChannelMapping( static_cast< ChannelMapping >( this->channelMapping[ 0 ] ),
        static_cast< ChannelMapping >( this->channelMapping[ 1 ] ),
        static_cast< ChannelMapping >( this->channelMapping[ 2 ] ),
        static_cast< ChannelMapping >( this->channelMapping[ 3 ] ) );
    textureViewInfo.SetImageFormat( textureInfo.GetImageFormat() );
    textureViewInfo.SetTexturePtr( static_cast< TTexture< TTarget >* >( this->pTexture.Get() ) );
    textureViewInfo.EditSubresourceRange().EditArrayRange().SetArrayLength( textureInfo.GetArrayLength() );
    textureViewInfo.EditSubresourceRange().EditMipRange().SetMipCount( textureInfo.GetMipCount() );
    static_cast< TTextureView< TTarget >* >( this->pTextureView.Get() )->Initialize( pDevice, textureViewInfo );
}

template< typename TTarget >
inline void ResTexture::Finalize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
{
    NN_SDK_ASSERT( this->pTexture.Get() );
    NN_SDK_ASSERT( this->pTextureView.Get() );
    static_cast< TTexture< TTarget >* >( this->pTexture.Get() )->Finalize( pDevice );
    static_cast< TTextureView< TTarget >* >( this->pTextureView.Get() )->Finalize( pDevice );
}

template< typename TTarget >
inline void ResTextureFile::Initialize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
{
    return Initialize< TTarget >( pDevice, NULL, 0, 0 );
}

template< typename TTarget >
inline void ResTextureFile::Initialize( TDevice< TTarget >* pDevice, TMemoryPool< TTarget >* pMemoryPool,
    ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
{
    NN_SDK_REQUIRES_NOT_NULL( pDevice );
    NN_SDK_ASSERT( nn::util::is_aligned( memoryPoolOffset, this->fileHeader.GetAlignment() ) );
    NN_UNUSED( memoryPoolSize );

    if( pMemoryPool )
    {
        this->textureContainerData.pCurrentMemoryPool.Set( pMemoryPool );
        this->textureContainerData.memoryPoolOffsetBase = static_cast< uint32_t >(
            memoryPoolOffset + nn::util::BytePtr( this ).Distance( nn::util::BytePtr(
            this->textureContainerData.pTextureData.Get(), sizeof( nn::util::BinaryBlockHeader ) ).Get() ) );
    }
    else
    {
        NN_SDK_ASSERT_NOT_NULL( this->textureContainerData.pTextureMemoryPool.Get() );
        MemoryPoolInfo memoryPoolInfo;
        memoryPoolInfo.SetMemoryPoolProperty( MemoryPoolProperty_CpuInvisible | MemoryPoolProperty_GpuCached );
        memoryPoolInfo.SetPoolMemory( nn::util::BytePtr( this->textureContainerData.pTextureData.Get(),
            sizeof( nn::util::BinaryBlockHeader ) ).Get(), static_cast< nn::util::BinaryBlockHeader* >(
            this->textureContainerData.pTextureData.Get() )->GetBlockSize() - sizeof( nn::util::BinaryBlockHeader ) );
        static_cast< TMemoryPool< TTarget >* >(
            this->textureContainerData.pTextureMemoryPool.Get() )->Initialize( pDevice, memoryPoolInfo );
        this->textureContainerData.pCurrentMemoryPool.Set( this->textureContainerData.pTextureMemoryPool.Get() );
        this->textureContainerData.memoryPoolOffsetBase = 0;
    }
}

template< typename TTarget >
inline void ResTextureFile::Finalize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
{
    NN_SDK_REQUIRES_NOT_NULL( pDevice );
    NN_SDK_ASSERT( this->textureContainerData.pCurrentMemoryPool.Get() );
    if( this->textureContainerData.pCurrentMemoryPool.Get() == this->textureContainerData.pTextureMemoryPool.Get() )
    {
        static_cast< TMemoryPool< TTarget >* >(
            this->textureContainerData.pTextureMemoryPool.Get() )->Finalize( pDevice );
    }
    this->textureContainerData.pCurrentMemoryPool.Set( NULL );
}

}
}
