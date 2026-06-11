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
* @brief  API declarations for shader resource file data.
*/

#pragma once

#include <nn/util/util_BinaryFormat.h>
#include <nn/util/util_ResDic.h>

#include <nn/gfx/gfx_ShaderInfo.h>

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/gfx_ResShaderData-api.nvn.h>
#endif

struct nngfxToolShaderCompilerShaderReflection;

namespace nn {
namespace gfx {

struct ResShaderProgramData;
struct ResShaderVariationData;
struct ResShaderContainerData;
struct ResShaderFileData;
struct ResShaderReflectionStageData;
struct ResShaderReflectionStageData2;
struct ResShaderReflectionData;

/**
* @brief  Structure representing shader program resources.
*/
struct ResShaderProgramData
{
    ShaderInfoData info; //!<  The information for initializing a shader.
    uint32_t objSize; //!<  The maximum size, in bytes, for the memory for holding shader objects.
    char reserved2[ 4 ]; //!<  This is a reserved region.
    nn::util::BinTPtr< void > pObj; //!<  Pointer to the shader object.

    nn::util::BinTPtr< ResShaderVariationData > pParent; //!<  Pointer to the shader stage that holds this shader program.

    nn::util::BinTPtr< ResShaderReflectionData > pShaderReflection; //!<  Pointer to the shader reflection resource.
    nn::util::BinTPtr< nngfxToolShaderCompilerShaderReflection > pShaderCompilerReflection; //!<  Pointer to all reflection data exported from the shader compiler.

    char reserved[ 24 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing shader variation resources.
*/
struct ResShaderVariationData
{
    nn::util::BinTPtr< ResShaderProgramData > pSourceProgram; //!<  Pointer to the source shader program.
    nn::util::BinTPtr< ResShaderProgramData > pIntermediateLanguageProgram; //!<  Pointer to the intermediate language representation shader program.
    nn::util::BinTPtr< ResShaderProgramData > pBinaryProgram; //!<  Pointer to the binary shader program.

    nn::util::BinTPtr< ResShaderContainerData > pParent; //!<  Pointer to the shader container that maintains this shader stage.

    char reserved[ 32 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing shader container resources.
*/
struct ResShaderContainerData
{
    nn::util::BinaryBlockHeader blockHeader; //!<  The block header.

    uint16_t targetApiType; //!<  The <tt>nn::gfx::LowLevelApi</tt> representation of the target API type.
    uint16_t targetApiVersion; //!<  The target API resource version.
    uint8_t targetCodeType; //!<  The <tt>nn::gfx::ShaderCodeType</tt> representation of the target code type.
    char reserved2[ 3 ]; //!<  This is a reserved region.
    uint32_t compilerVersion; //!<  The compiler version.

    uint32_t shaderVariationCount; //!<  The number of shader variations.
    nn::util::BinTPtr< ResShaderVariationData > pShaderVariationArray; //!<  Pointer to the array of shader variations.

    nn::util::BinTPtr< void > pShaderBinaryPool; //!<  Pointer to the shader binary pool.

    uint64_t lowLevelCompilerVersion; //!<  The version of the low-level compiler.

    char reserved[ 40 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing shader file resources.
*/
struct ResShaderFileData
{
    nn::util::BinaryFileHeader fileHeader; //!<  The file header.

    char reserved[ 64 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing the shader reflection resource for each stage.
*/
struct ResShaderReflectionStageData
{
    nn::util::BinTPtr< nn::util::ResDic > pShaderInputDic; //!<  Pointer to the shader input dictionary.
    nn::util::BinTPtr< nn::util::ResDic > pShaderOutputDic; //!<  Pointer to the shader output dictionary.
    nn::util::BinTPtr< nn::util::ResDic > pSamplerDic; //!<  Pointer to the sampler dictionary.
    nn::util::BinTPtr< nn::util::ResDic > pConstantBufferDic; //!<  Pointer to the constant buffer dictionary.
    nn::util::BinTPtr< nn::util::ResDic > pUnorderedAccessBufferDic; //!<  Pointer to the unordered access buffer dictionary.

    int32_t offsetShaderOutput; //!<  Start position of the shader output information in the array.
    int32_t offsetSampler; //!<  Start position of the sampler information in the array.
    int32_t offsetConstantBuffer; //!<  Start position of the constant buffer information in the array.
    int32_t offsetUnorderedAccessBuffer; //!<  Start position of the unordered access buffer information in the array.
    nn::util::BinTPtr< int32_t > pShaderSlotArray; //!<  Pointer to the array of shader slots.

    uint32_t computeWorkGroupSizeX; //!<  Size of the work group's x-dimension for the compute shader.
    uint32_t computeWorkGroupSizeY; //!<  Size of the work group's y-dimension for the compute shader.
    uint32_t computeWorkGroupSizeZ; //!<  Size of the work group's z-dimension for the compute shader.

    int32_t offsetImage; //!<  Start position for image data in the array.

    nn::util::BinTPtr< nn::util::ResDic > pImageDic; //!<  Pointer to the image dictionary.

    nn::util::BinTPtr< ResShaderReflectionStageData2 > pReflectionStageData2; //!<  Pointer to the rest of the reflection data.
};

/**
* @brief  The structure representing the shader reflection resource for each stage subsequent to <tt>ResShaderReflectionStageData</tt>.
*/
struct ResShaderReflectionStageData2
{
    nn::util::BinTPtr< nn::util::ResDic > pSeparateTextureDic; //!<  Pointer to the separate texture dictionary.
    nn::util::BinTPtr< nn::util::ResDic > pSeparateSamplerDic; //!<  Pointer to the separate sampler dictionary.
    int32_t offsetSeparateTexture; //!<  Start position of the texture information in the array.
    int32_t offsetSeparateSampler; //!<  Start position of the sampler information in the array.

    nn::util::BinTPtr< int32_t > pShaderSetArray; //!<  Pointer to the descriptor sets array of the shader.

    char reserved[ 16 ]; //!<  This is a reserved region.
};

/**
* @brief  Structure representing shader reflection resources.
*/
struct ResShaderReflectionData
{
    nn::util::BinTPtr< ResShaderReflectionStageData > pVertexReflection; //!<  Pointer to the reflection resource of a vertex shader.
    nn::util::BinTPtr< ResShaderReflectionStageData > pHullReflection; //!<  Pointer to the reflection resource of a hull shader.
    nn::util::BinTPtr< ResShaderReflectionStageData > pDomainReflection; //!<  Pointer to the reflection resource of a domain shader.
    nn::util::BinTPtr< ResShaderReflectionStageData > pGeometryReflection; //!<  Pointer to the reflection resource of a geometry shader.
    nn::util::BinTPtr< ResShaderReflectionStageData > pPixelReflection; //!<  Pointer to the reflection resource of a pixel shader.
    nn::util::BinTPtr< ResShaderReflectionStageData > pComputeReflection; //!<  Pointer to the reflection resource of a compute shader.

    char reserved[ 16 ]; //!<  This is a reserved region.
};

}
}
