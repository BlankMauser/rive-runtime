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
* @brief  Declarations of API resources for shader initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/util/util_BitPack.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure that represents the information for initializing a shader.
*/
struct ShaderInfoData
{
    enum
    {
        Flag_SeparationEnable,
        Flag_ResShader
    };

    nn::util::BitPack8 flags; //!<  The flags.
    Bit8 codeType; //!<  The <tt>nn::gfx::ShaderCodeType</tt> representation of the code type.
    Bit8 sourceFormat; //!<  The <tt>nn::gfx::ShaderSourceFormat</tt> representation of the source format.
    char reserved2; //!<  This is a reserved region.
    Bit32 binaryFormat; //!<  The binary format.
    detail::Ptr< const void > pVertexShaderCode; //!<  Pointer to the vertex shader code.
    detail::Ptr< const void > pHullShaderCode; //!<  Pointer to the hull shader code.
    detail::Ptr< const void > pDomainShaderCode; //!<  Pointer to the domain shader code.
    detail::Ptr< const void > pGeometryShaderCode; //!<  Pointer to the geometry shader code.
    detail::Ptr< const void > pPixelShaderCode; //!<  Pointer to the pixel shade code.
    detail::Ptr< const void > pComputeShaderCode; //!<  Pointer to the compute shader code.

    char reserved[ 40 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing shader code.
*/
struct ShaderCode
{
    uint32_t codeSize; //!<  The code size, in bytes.
    uint32_t decompressedCodeSize; //!<  The code size in bytes after running decompression using <tt>nn::util::DecompressZlib</tt>. <tt>0</tt> when <tt><var>pCode</var></tt> is not compressed.
    detail::Ptr< const void > pCode; //!<  Pointer to the code.

    char reserved[ 16 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing the source array code. Used for shaders with a code type of <tt>nn::gfx::ShaderCodeType_SourceArray</tt>.
*/
struct SourceArrayCode
{
/**
* @brief  Maximum length of the code array.
*/
    static const int MaxCodeArrayLength = 64;

    uint16_t codeArrayLength; //!<  Length of the code array.
    char reserved2[ 6 ]; //!<  This is a reserved region.
    detail::Ptr< const uint32_t > pCodeSizeArray; //!<  The pointer to the array of code sizes.
    detail::Ptr< detail::Ptr< const void > > pCodePtrArray; //!<  Pointer to the array of pointers to codes.

    char reserved[ 8 ]; //!<  This is a reserved region.
};

}
}
