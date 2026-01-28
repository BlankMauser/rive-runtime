/*--------------------------------------------------------------------------------*
  Copyright Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/

#pragma once

#include <nn/gfx/util/detail/gfx_TextureCompressor-common.h>

namespace nn {
namespace gfx {
namespace util {

//-----------------------------------------------------
//! @brief  Data class for the texture compression destination.
//-----------------------------------------------------
class TextureCompressorTargetInfo
{
    NN_DISALLOW_COPY(TextureCompressorTargetInfo);
public:

/**
* @brief  Constructor.
*/
    TextureCompressorTargetInfo() NN_NOEXCEPT;

/**
* @brief  Destructor.
*/
    ~TextureCompressorTargetInfo() NN_NOEXCEPT;

/**
* @brief  Sets the compression destination texture information.
*
* @param[in] textureInfo  The <tt>nn::gfx::TextureInfo</tt> used when initializing the compression destination texture.
* @param[in] pTexture  Pointer to the compression destination texture.
*
* @pre
*  - <tt><var>pTexture</var></tt> != <tt>NULL</tt>.
*  - <tt>nn::gfx::IsInitialized(*<var>pTexture</var>)</tt>
*/
    void SetTexture(const nn::gfx::Texture::InfoType& textureInfo, nn::gfx::Texture* pTexture) NN_NOEXCEPT;

/**
* @brief  Gets the compression destination texture information.
* @return  Returns the compression destination texture information.
* @pre  Value set using <tt>SetTexture()</tt>.
*/
    nn::gfx::Texture::InfoType GetTextureInfo() const NN_NOEXCEPT;

/**
* @brief  Gets the compression destination texture pointer.
* @return  Returns the compression destination texture pointer.
* @details  Returns <tt>NULL</tt> when no value was set using <tt>SetTexture()</tt>.
*/
    nn::gfx::Texture* GetTexture() const NN_NOEXCEPT;

private:

    nn::gfx::Texture*           m_pTexture;
    nn::gfx::Texture::InfoType  m_TextureInfo;

};


//-------------------------------------------------
//! @brief  Class that compresses a texture.
//-------------------------------------------------
class TextureCompressor
{
    NN_DISALLOW_COPY(TextureCompressor);

public:

    static const int SupportedFormatCount = 10;

public:

/**
* @brief  Constructor.
*/
    TextureCompressor() NN_NOEXCEPT;

/**
* @brief  Destructor.
* @pre  ! <tt>IsInitialized()</tt>
*/
    ~TextureCompressor() NN_NOEXCEPT;

/**
* @brief  Initializes the object needed for texture compression.
*
* @param[in] pDevice  Pointer for the device.
*
* @pre
*  - ! <tt>IsInitialized()</tt>
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt>nn::gfx::IsInitialized(*<var>pDevice</var>)</tt>
*
* @post
*  - <tt>IsInitialized()</tt>
*/
    void Initialize(nn::gfx::Device* pDevice) NN_NOEXCEPT;

/**
* @brief  Destroys the object needed for texture compression.
* @pre  <tt>IsInitialized()</tt>
* @post  ! <tt>IsInitialized()</tt>
*/
    void Finalize() NN_NOEXCEPT;

/**
* @brief  Determines whether initialized.
* @return  Returns whether initialized.
*/
    bool IsInitialized() const NN_NOEXCEPT;

/**
* @brief  Adds a shader to use for texture compression.
*
* @param[in] targetFormat  Compression format for adding the shader.
* @param[in] pShader  Pointer to the shader that will compress to suit the format.
*
* @pre
*  - <tt>IsInitialized()</tt>
*  - <tt>IsSupportedFormat(<var>targetFormat</var>)</tt>
*  - <tt><var>pShader</var></tt> != <tt>NULL</tt>.
*  - <tt>nn::gfx::IsInitialized(*<var>pShader</var>)</tt>
*
* @details
*  - You must add a shader for each compression format.
*  - A pointer will be overwritten when you pass a pointer for a separate shader as an argument for the same format.
*/
    void RegisterCompressionShader(nn::gfx::ImageFormat targetFormat,const nn::gfx::Shader* pShader) NN_NOEXCEPT;

/**
* @brief  Unregisters a shader.
*
* @param[in] targetFormat  Format that corresponds to the shader you unregister.
*
* @pre
*  - <tt>IsInitialized()</tt>
*  - <tt>IsSupportedFormat(<var>targetFormat</var>)</tt>
*
* @details
*  - Note that, prior to calling this function, commands created using <tt>MakeCommand()</tt> are referencing shaders.
*  - You do not need to call this function after destroying shaders with <tt>Finalize()</tt>.
*/
    void UnregisterCompressionShader(nn::gfx::ImageFormat targetFormat) NN_NOEXCEPT;

/**
* @brief  Gets whether the specified compression format is supported.
* @param[in] format  Format that performs a supported confirmation.
* @return  Returns whether the specified compression format is supported.
*/
    static bool IsSupportedFormat(nn::gfx::ImageFormat format) NN_NOEXCEPT;

/**
* @brief  Creates a command to compress a texture.
*
* @param[in] pCommandBuffer  Pointer for the command buffer that writes the compression.
* @param[in] srcTextureDescriptorSlot  Descriptor slot for the compression source texture.
* @param[in] samplerDescriptorSlot  Descriptor slot added by the sampler to use when loading compression source texture values.
* @param[in] targetTextureInfo  Compression destination texture information.
*
* @pre
*  - <tt>IsInitialized()</tt>
*  - <tt><var>pCommandBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt>nn::gfx::IsInitialized(*<var>pCommandBuffer</var>)</tt>
*  - <tt>IsSupportedFormat(<var>destFormat</var>)</tt>
*  - <tt><var>destTextureInfo</var></tt> must store the compression destination information using <tt>SetTextureInfo()</tt> and <tt>SetTextureStorage()</tt>.
*  - The number of mipmaps configured to <tt><var>targetTexturInfo</var></tt> must be 15 or less.
*  - The length of the array configured to <tt><var>targetTexturInfo</var></tt> must be 65535 or less.
*  - A shader that corresponds to the compression format must be added.
*
* @post
*  - Commands that perform texture compression are recorded to the command buffer passed using <tt><var>pCommandBuffer</var></tt>.
*
* @details
*  - You must not destroy any shaders added when creating compression commands until those commands run.
*  - You must not destroy any compression destination textures until those commands run.
*/
    void MakeCommand(
        nn::gfx::CommandBuffer* pCommandBuffer,
        const nn::gfx::DescriptorSlot& srcTextureDescriptorSlot,
        const nn::gfx::DescriptorSlot& samplerDescriptorSlot,
        const TextureCompressorTargetInfo& targetTextureInfo
        ) const NN_NOEXCEPT;

private:
    const nn::gfx::Shader* GetShader(nn::gfx::ImageFormat imageFormat) const NN_NOEXCEPT;

private:
    detail::TextureCompressorCommonState m_CommonState;
    const nn::gfx::Shader* m_pShaders[SupportedFormatCount];
};


}
}
}
