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
* @brief  Declarations for API resources related to shader resource files.
*/

#pragma once

#include <nn/util/util_AccessorBase.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_DataAccessorConverter.h>
#include <nn/gfx/gfx_ResShaderData.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_ResShaderImpl.h>

namespace nn {
namespace gfx {

/**
* @brief  Class representing shader program resources.
*/
class ResShaderProgram
    : public nn::util::AccessorBase< ResShaderProgramData >
{
    NN_DISALLOW_COPY( ResShaderProgram );

    typedef detail::ResShaderProgramImpl Impl;

public:
/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static ResShaderProgram* ToAccessor( ResShaderProgramData* pData ) NN_NOEXCEPT
    {
        return static_cast< ResShaderProgram* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static ResShaderProgram& ToAccessor( ResShaderProgramData& data ) NN_NOEXCEPT
    {
        return static_cast< ResShaderProgram& >( data );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static const ResShaderProgram* ToAccessor( const ResShaderProgramData* pData ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderProgram* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static const ResShaderProgram& ToAccessor( const ResShaderProgramData& data ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderProgram& >( data );
    }

/**
* @brief  Gets the information for initializing the shader.
*
* @return  Returns a pointer to the information for initializing the shader.
*/
    ShaderInfo* GetShaderInfo() NN_NOEXCEPT
    {
        return DataToAccessor( this->info );
    }

/**
* @brief  Gets the information for initializing the shader.
*
* @return  Returns a pointer to the information for initializing the shader.
*/
    const ShaderInfo* GetShaderInfo() const NN_NOEXCEPT
    {
        return DataToAccessor( this->info );
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a shader object.
*
* @return  Returns a pointer to a <tt>nn::gfx::Shader</tt>-type shader object.
*
* @details
*  Assign the value returned by this function to a <tt>nn::gfx::Shader</tt>-type pointer.
*/
    Shader* GetShader() NN_NOEXCEPT;
#else
    detail::Caster< void > GetShader() NN_NOEXCEPT
    {
        return detail::Caster< void >( this->pObj.Get() );
    }
#endif

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a shader object.
*
* @return  Returns a pointer to a <tt>nn::gfx::Shader</tt>-type shader object.
*
* @details
*  Assign the value returned by this function to a <tt>nn::gfx::Shader</tt>-type pointer.
*/
    const Shader* GetShader() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetShader() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( this->pObj.Get() );
    }
#endif

/**
* @brief  Gets reflection data exported from the shader compiler.
*
* @return  Returns a pointer to the reflection data exported from the shader compiler.
*
* @details
*  The option to include the reflection data exported from the shader compiler must be specified during shader conversion.
*  For more information, see the shader converter documentation.
*/
    const nngfxToolShaderCompilerShaderReflection*
        GetShaderCompilerReflection() const NN_NOEXCEPT
    {
        return this->pShaderCompilerReflection.Get();
    }

/**
* @brief  Initializes the shader.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @return  Returns the result of shader initialization.
* @retval ShaderInitializeResult_Success  Succeeded.
* @retval ShaderInitializeResult_InvalidFormat  The shader format specified in <tt><var>info</var></tt> is not valid in this environment.
* @retval ShaderInitializeResult_SetupFailed  Shader setup failed due to a compiling failure or other problem.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The shader is not initialized.
*  - The shader container that the shader is associated with is initialized.
*
* @post
*  - The shader is initialized.
*
* @details
*  Performs processing equivalent to the processing of the <tt>Initialize</tt> function in <tt>nn::gfx::Shader</tt>.
*/
    template< typename TTarget >
    ShaderInitializeResult Initialize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( this->objSize >= sizeof( TShader< TTarget > ) );
        NN_SDK_ASSERT( this->pObj.Get() );
        return static_cast< TShader< TTarget >* >(
            this->pObj.Get() )->Initialize( pDevice, DataToAccessor( this->info ) );
    }

/**
* @brief  Finalizes the shader.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The shader is initialized.
*
* @post
*  - The shader is not initialized.
*
* @details
*  Performs processing equivalent to the processing of the <tt>Finalize</tt> function in <tt>nn::gfx::Shader</tt>.
*/
    template< typename TTarget >
    void Finalize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( this->pObj.Get() );
        static_cast< TShader< TTarget >* >( this->pObj.Get() )->Finalize( pDevice );
    }

/**
* @brief  Gets the recommended size of scratch memory needed to work the shader, in bytes.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @return
*  - Returns the recommended size of scratch memory needed to work the shader, in bytes.
*
* @details
*  This function can only be called with the Nvn version.
*  The intended name of this function was <tt>NvnGetRecommendedScratchMemorySize</tt> but it was misspelled and the name is being retained for the sake of compatibility.
*/
    template< typename TTarget >
    size_t NvnGetRecommendedScrachMemorySize( TDevice< TTarget >* pDevice ) const NN_NOEXCEPT
    {
        return Impl::NvnGetRecommendedScrachMemorySize( this, pDevice );
    }
};

/**
* @brief  Class representing shader variation.
*/
class ResShaderVariation
    : public nn::util::AccessorBase< ResShaderVariationData >
{
    NN_DISALLOW_COPY( ResShaderVariation );

public:
/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static ResShaderVariation* ToAccessor( ResShaderVariationData* pData ) NN_NOEXCEPT
    {
        return static_cast< ResShaderVariation* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static ResShaderVariation& ToAccessor( ResShaderVariationData& data ) NN_NOEXCEPT
    {
        return static_cast< ResShaderVariation& >( data );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static const ResShaderVariation* ToAccessor( const ResShaderVariationData* pData ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderVariation* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static const ResShaderVariation& ToAccessor( const ResShaderVariationData& data ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderVariation& >( data );
    }

/**
* @brief  Gets the shader program resource.
*
* @param[in] codeType  The type of code for the shader program resources to get.
*
* @return  Returns the shader program resource.
*/
    ResShaderProgram* GetResShaderProgram( ShaderCodeType codeType ) NN_NOEXCEPT
    {
        return const_cast< ResShaderProgram* >( static_cast<
            const ResShaderVariation* >( this )->GetResShaderProgram( codeType ) );
    }

/**
* @brief  Gets the shader program resource.
*
* @param[in] codeType  The type of code for the shader program resources to get.
*
* @return  Returns the shader program resource.
*
* @details
*  When getting the <tt>ShaderCodeType_SourceArray</tt> type, specify <tt>ShaderCodeType_Source</tt>.
*/
    const ResShaderProgram* GetResShaderProgram( ShaderCodeType codeType ) const NN_NOEXCEPT
    {
        static const nn::util::BinTPtr< ResShaderProgramData >
            ResShaderVariationData::*s_pResShaderProgramDataTable[] =
        {
            &ResShaderVariationData::pBinaryProgram,
            &ResShaderVariationData::pIntermediateLanguageProgram,
            &ResShaderVariationData::pSourceProgram,
            NULL
        };
        return ResShaderProgram::ToAccessor( ( this->*s_pResShaderProgramDataTable[ codeType ] ).Get() );
    }
};

/**
* @brief  Class representing shader container resources.
*
* @details
*  Maintains multiple shaders as shader container variations.
*/
class ResShaderContainer
    : public nn::util::AccessorBase< ResShaderContainerData >
{
    NN_DISALLOW_COPY( ResShaderContainer );

    typedef detail::ResShaderContainerImpl Impl;

public:
/**
* @brief  The shader container resource signature.
*/
    static const int Signature = NN_UTIL_CREATE_SIGNATURE_4( 'g', 'r', 's', 'c' );

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static ResShaderContainer* ToAccessor( ResShaderContainerData* pData ) NN_NOEXCEPT
    {
        return static_cast< ResShaderContainer* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static ResShaderContainer& ToAccessor( ResShaderContainerData& data ) NN_NOEXCEPT
    {
        return static_cast< ResShaderContainer& >( data );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static const ResShaderContainer* ToAccessor( const ResShaderContainerData* pData ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderContainer* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static const ResShaderContainer& ToAccessor( const ResShaderContainerData& data ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderContainer& >( data );
    }

/**
* @brief  Initializes the shader container.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The shader container is not initialized.
*
* @post
*  - The shader container is not initialized.
*/
    template< typename TTarget >
    void Initialize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Initialize( this, pDevice );
    }

/**
* @brief  Initializes the shader container.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] pMemoryPool  A memory pool that holds a shader container.
* @param[in] memoryPoolOffset  The byte offset to the shader container in <tt><var>pMemoryPool</var></tt>.
* @param[in] memoryPoolSize  The size, in bytes, of the pool in <tt><var>pMemoryPool</var></tt>.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @post
*  - The shader container is not initialized.
*
* @details
*  When <tt><var>pMemoryPool</var></tt> == <tt>NULL</tt>, initialize using a memory pool with a shader container.
*/
    template< typename TTarget >
    void Initialize( TDevice< TTarget >* pDevice, TMemoryPool< TTarget >* pMemoryPool,
        ptrdiff_t memoryPoolOffset, size_t memoryPoolSize ) NN_NOEXCEPT
    {
        return Impl::Initialize( this, pDevice, pMemoryPool, memoryPoolOffset, memoryPoolSize );
    }

/**
* @brief  Finalizes the shader container.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The shader container is not initialized.
*
* @post
*  - The shader container is not initialized.
*/
    template< typename TTarget >
    void Finalize( TDevice< TTarget >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( this, pDevice );
    }

/**
* @brief  Gets the shader program resource.
*
* @param[in] index  The variation index for the shader program resource to get.
*
* @return  Returns the shader program resource.
*
* @pre
*  - <tt><var>index</var></tt> >= <tt>0</tt> && <tt><var>index</var></tt> < <tt>GetShaderVariationCount()</tt>.
*/
    ResShaderProgram* GetResShaderProgram( int index ) NN_NOEXCEPT
    {
        ResShaderVariation* pResShaderVariation = GetResShaderVariation( index );
        NN_SDK_ASSERT_NOT_NULL( pResShaderVariation );
        return pResShaderVariation->GetResShaderProgram(
            static_cast< ShaderCodeType >( this->targetCodeType ) );
    }

/**
* @brief  Gets the shader program resource.
*
* @param[in] index  The variation index for the shader program resource to get.
*
* @return  Returns the shader program resource.
*
* @pre
*  - <tt><var>index</var></tt> >= <tt>0</tt> && <tt><var>index</var></tt> < <tt>GetShaderVariationCount()</tt>.
*/
    const ResShaderProgram* GetResShaderProgram( int index ) const NN_NOEXCEPT
    {
        const ResShaderVariation* pResShaderVariation = GetResShaderVariation( index );
        NN_SDK_ASSERT_NOT_NULL( pResShaderVariation );
        return pResShaderVariation->GetResShaderProgram(
            static_cast< ShaderCodeType >( this->targetCodeType ) );
    }

/**
* @brief  Gets the shader variation resource.
*
* @param[in] index  The variation index for the shader program resource to get.
*
* @return  Returns the shader variation resource.
*
* @pre
*  - <tt><var>index</var></tt> >= <tt>0</tt> && <tt><var>index</var></tt> < <tt>GetShaderVariationCount()</tt>.
*/
    ResShaderVariation* GetResShaderVariation( int index ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES_RANGE( index, 0, static_cast< int >( this->shaderVariationCount ) );
        NN_SDK_ASSERT( this->pShaderVariationArray.Get() );
        return ResShaderVariation::ToAccessor( this->pShaderVariationArray.Get() + index );
    }

/**
* @brief  Gets the shader variation resource.
*
* @param[in] index  The variation index for the shader program resource to get.
*
* @return  Returns the shader variation resource.
*
* @pre
*  - <tt><var>index</var></tt> >= <tt>0</tt> && <tt><var>index</var></tt> < <tt>GetShaderVariationCount()</tt>.
*/
    const ResShaderVariation* GetResShaderVariation( int index ) const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES_RANGE( index, 0, static_cast< int >( this->shaderVariationCount ) );
        NN_SDK_ASSERT( this->pShaderVariationArray.Get() );
        return ResShaderVariation::ToAccessor( this->pShaderVariationArray.Get() + index );
    }

/**
* @brief  Gets the number of shader variations.
*
* @return  Returns the number of shader variations.
*/
    int GetShaderVariationCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->shaderVariationCount );
    }
};

/**
* @brief  A shader resource file.
*/
class ResShaderFile
    : public nn::util::AccessorBase< ResShaderFileData >
{
    NN_DISALLOW_COPY( ResShaderFile );

public:
/**
* @brief  The shader resource file signature.
*/
    static const int64_t Signature = NN_UTIL_CREATE_SIGNATURE_8( 'B', 'N', 'S', 'H', 0, 0, 0, 0 );

/**
* @brief  The shader resource file major version.
*/
    static const int MajorVersion = 2;

/**
* @brief  The shader resource file minor version.
*/
    static const int MinorVersion = 1;

/**
* @brief  The shader resource file micro version.
*/
    static const int MicroVersion = 12;

/**
* @brief  Gets the maximum alignment value requested by the shader file resource.
*
* @return  Returns the maximum alignment value requested by the shader file resource.
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
    static ResShaderFile* ToAccessor( ResShaderFile::value_type* pData ) NN_NOEXCEPT
    {
        return static_cast< ResShaderFile* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static ResShaderFile& ToAccessor( ResShaderFile::value_type& data ) NN_NOEXCEPT
    {
        return static_cast< ResShaderFile& >( data );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] pData  Pointer to the data to convert.
*
* @return  Returns a pointer to the converted accessor.
*/
    static const ResShaderFile* ToAccessor( const ResShaderFile::value_type* pData ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderFile* >( pData );
    }

/**
* @brief  Converts the data to an accessor.
*
* @param[in] data  Reference to the data to convert.
*
* @return  Returns a reference to the converted accessor.
*/
    static const ResShaderFile& ToAccessor( const ResShaderFile::value_type& data ) NN_NOEXCEPT
    {
        return static_cast< const ResShaderFile& >( data );
    }

/**
* @brief  Determines whether the binary data is a valid shader file.
*
* @param[in] ptr  Pointer to the binary data.
*
* @return  Returns a Boolean indicating whether the specified binary data is a valid shader file.
*
* @pre
*  - <tt><var>ptr</var></tt> != <tt>NULL</tt>.
*/
    static bool IsValid( const void* ptr ) NN_NOEXCEPT;

/**
* @brief  Casts binary data to a shader resource file type.
*
* @param[in] ptr  Pointer to the binary data to cast.
*
* @return  Returns a pointer to the cast shader resource file.
*
* @pre
*  - <tt><var>ptr</var></tt> != <tt>NULL</tt>.
*
* @details
*  Do not cast directly. Use this function instead.
*/
    static ResShaderFile* ResCast( void* ptr ) NN_NOEXCEPT;

/**
* @brief  Gets the shader container resources.
*
* @return  Returns a pointer to the shader container resources.
*/
    ResShaderContainer* GetShaderContainer() NN_NOEXCEPT
    {
        return ResShaderContainer::ToAccessor( reinterpret_cast<
            ResShaderContainerData* >( this->fileHeader.GetFirstBlock() ) );
    }

/**
* @brief  Gets the shader container resources.
*
* @return  Returns a pointer to the shader container resources.
*/
    const ResShaderContainer* GetShaderContainer() const NN_NOEXCEPT
    {
        return ResShaderContainer::ToAccessor( reinterpret_cast<
            const ResShaderContainerData* >( this->fileHeader.GetFirstBlock() ) );
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

/**
* @brief  Gets the maximum recommended shader scratch memory size from among the specified shaders.
*
* @tparam TTarget  The target low-level graphics API.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] ppResShaderFileArray  Pointer to an array of shader file resource pointers.
* @param[in] shaderFileCount  Number of elements in the <tt><var>pResShaderFileArray</var></tt> array.
*
* @return  Returns the maximum recommended shader scratch memory size from among the specified shaders.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - When <tt><var>shaderFileCount</var></tt> > <tt>0</tt>, <tt><var>pResShaderFileArray</var></tt> != <tt>NULL</tt>.
*
* @details
*  This function can only be called with the Nvn version.
*/
template< typename TTarget >
size_t NvnGetMaxRecommendedScratchMemorySize( TDevice< TTarget >* pDevice,
    const ResShaderFile* const* ppResShaderFileArray, int shaderFileCount ) NN_NOEXCEPT;

}
}
