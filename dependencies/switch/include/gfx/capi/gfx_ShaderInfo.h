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
* @brief  Declarations of API resources for shader initialization information.
*/

#pragma once

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_ShaderInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  Represents the information for initializing a shader.
*/
class ShaderInfo
    : public detail::DataContainer< ShaderInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - Each parameter is initialized to zero.
*/
    ShaderInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  Helper function to set each parameter to the default value.
    *
* @post
    * - Each parameter is set.
    *
* @details
    * Equivalent to calling the following.
    * - SetSeparationEnabled( false );
    * - SetCodeType( nn::gfx::ShaderCodeType_Source );
    * - SetSourceFormat( nn::gfx::ShaderSourceFormat_Glsl );
    * - SetBinaryFormat( 0 );
    * - SetShaderCodePtr( nn::gfx::ShaderStage_Vertex, NULL );
    * - SetShaderCodePtr( nn::gfx::ShaderStage_Hull, NULL );
    * - SetShaderCodePtr( nn::gfx::ShaderStage_Domain, NULL );
    * - SetShaderCodePtr( nn::gfx::ShaderStage_Geometry, NULL );
    * - SetShaderCodePtr( nn::gfx::ShaderStage_Pixel, NULL );
    * - SetShaderCodePtr( nn::gfx::ShaderStage_Compute, NULL );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Enables or disables shader separate.
    *
* @param[in] value  Boolean value indicating whether to enable shader separate.
    *
* @post
    * - Shader separate is set to be enabled or disabled.
*/
    void SetSeparationEnabled( bool value ) NN_NOEXCEPT
    {
        this->flags.SetBit( Flag_SeparationEnable, value );
    }

/**
* @brief  Sets the type of code to set with <tt>SetCodePtr</tt>.
    *
* @param[in] value  Code type.
    *
* @post
    * - The code type is set.
    *
* @details
*  We cannot recommend using <tt>nn::gfx::ShaderCodeType_Source</tt> and <tt>nn::gfx::ShaderCodeType_SourceArray</tt> from the perspectives of speed and memory efficiency.
*/
    void SetCodeType( ShaderCodeType value ) NN_NOEXCEPT
    {
        this->codeType = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the source format when code type is set to source.
    *
* @param[in] value  Source format.
    *
* @post
    * - The source format is set.
*/
    void SetSourceFormat( ShaderSourceFormat value ) NN_NOEXCEPT
    {
        this->sourceFormat = static_cast< uint8_t >( value );
    }

/**
* @brief  Sets the binary format when the code type is set to binary.
    *
* @param[in] value  Binary format.
    *
* @post
    * - The binary format is set.
    *
* @details
*  In the GL version, sets the <tt><var>binaryFormat</var></tt> to get when retrieving the program binaries.
    *
* @platformbegin{GX}
    * This parameter does not affect object initialization.
* @platformend
*/
    void SetBinaryFormat( int value ) NN_NOEXCEPT
    {
        this->binaryFormat = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets the shader code.
    *
* @param[in] shaderStage  Target shader stage
* @param[in] pCode  Pointer to the shader code.
    *
* @post
    * - The shader code is set.
    *
* @details
*  Make sure that <tt><var>pCode</var></tt> points to <tt>nn::gfx::ShaderCode</tt>, <tt>nn::gfx::SourceArrayCode</tt>, or a structure unique to the low level graphics API.
*/
    void SetShaderCodePtr( ShaderStage shaderStage, const void* pCode ) NN_NOEXCEPT;

/**
* @brief  Determines whether shader separate is enabled.
    *
* @return  Returns a boolean value indicating whether shader separate is enabled.
*/
    bool IsSeparationEnabled() const NN_NOEXCEPT
    {
        return this->flags.GetBit( Flag_SeparationEnable );
    }

/**
* @brief  Gets the code type.
    *
* @return
    * - Returns the code type.
*/
    ShaderCodeType GetCodeType() const NN_NOEXCEPT
    {
        return static_cast< ShaderCodeType >( this->codeType );
    }

/**
* @brief  Gets the binary format.
    *
* @return  Returns the binary format.
*/
    int GetBinaryFormat() const NN_NOEXCEPT
    {
        return static_cast< int >( this->binaryFormat );
    }

/**
* @brief  Gets the source format.
    *
* @return  Returns the source format.
*/
    ShaderSourceFormat GetSourceFormat() const NN_NOEXCEPT
    {
        return static_cast< ShaderSourceFormat >( this->sourceFormat );
    }

/**
* @brief  Gets a pointer to the shader code.
    *
* @return  Returns a pointer to the shader code.
*/
    const void* GetShaderCodePtr( ShaderStage shaderStage ) const NN_NOEXCEPT;
};

}
}
