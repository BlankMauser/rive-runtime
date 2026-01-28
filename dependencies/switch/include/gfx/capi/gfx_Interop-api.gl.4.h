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

#include <nn/nn_Macro.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>
#include <nn/gfx/gfx_Enum.h>

#include <nn/gfx/detail/gfx_Declare.h>

struct HGLRC__;

namespace nn {
namespace gfx {

/**
* @brief  Class for interoperability with the GL4 API resources.
*
* @details
*  The creator of the original object has ownership of the object.
*  <tt>Finalize</tt> cannot be called on a <tt>gfx</tt> object for which <tt>Initialize</tt> has not been called.
*
*  The context that created the original object and the context using that object must either be the same or have co-ownership.
*/
template<>
class TInteroperation< ApiVariationGl4 >
{
    NN_DISALLOW_COPY( TInteroperation );
    TInteroperation() NN_NOEXCEPT;

public:
/**
* @brief  The target for the low-level graphics API.
*/
    typedef ApiVariationGl4 Target;

/**
* @brief  The type of the GL handle.
*/
    typedef unsigned int GlHandleType;

/**
* @brief  The GL enumerated type.
*/
    typedef unsigned int GlEnumType;

/**
* @brief  Converts the specified GL4 buffer to a <tt>gfx</tt> buffer.
*
* @param[out] pOutGfxBuffer  A pointer for receiving the converted <tt>gfx</tt> buffer.
* @param[in] pDevice  Pointer to the device.
* @param[in] hGl4Buffer  The GL4 buffer to convert.
*
* @pre
*  - <tt><var>pOutGfxBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutGfxBuffer</var></tt> is not initialized.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>hGl4Buffer</var></tt> is a valid GL4 buffer object.
*/
    static void ConvertToGfxBuffer( TBuffer< Target >* pOutGfxBuffer,
        TDevice< Target >* pDevice, GlHandleType hGl4Buffer ) NN_NOEXCEPT;

/**
* @brief  Converts the specified Windows GL rendering context to a <tt>gfx</tt> device.
*
* @param[out] pOutGfxDevice  A pointer for receiving the converted <tt>gfx</tt> device.
* @param[in] hGlRc  The GL rendering context to convert.
*
* @pre
*  - <tt><var>pOutGfxDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>hGlRc</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxDevice( TDevice< Target >* pOutGfxDevice, HGLRC__* hGlRc ) NN_NOEXCEPT;

/**
* @brief  Converts the specified GL4 sampler to a <tt>gfx</tt> sampler.
*
* @param[out] pOutGfxSampler  Specifies a pointer for receiving the converted <tt>gfx</tt> sampler.
* @param[in] hGl4Sampler  The GL4 sampler to convert.
*
* @pre
*  - <tt><var>pOutGfxSampler</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutGfxSampler</var></tt> is not initialized.
*  - <tt><var>hGl4Sampler</var></tt> is a valid GL4 sampler object.
*/
    static void ConvertToGfxSampler( TSampler< Target >* pOutGfxSampler,
        GlHandleType hGl4Sampler ) NN_NOEXCEPT;

/**
* @brief  Converts the specified GL4 program to a <tt>gfx</tt> shader.
*
* @param[out] pOutGfxShader  A pointer for receiving the converted <tt>gfx</tt> shader.
* @param[in] pDevice  Pointer to the device.
* @param[in] hGl4Program  The GL4 program to convert.
*
* @pre
*  - <tt><var>pOutGfxShader</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutGfxShader</var></tt> is not initialized.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>hGl4Program</var></tt> is a valid GL4 program object.
*
* @details
*  <tt><var>hGl4Program</var></tt> must be either <tt>GL_PROGRAM_SEPARABLE</tt> or <tt>GL_FALSE</tt>.
*/
    static void ConvertToGfxShader( TShader< Target >* pOutGfxShader,
        TDevice< Target >* pDevice, GlHandleType hGl4Program ) NN_NOEXCEPT;

/**
* @brief  Converts the specified GL4 texture to a <tt>gfx</tt> texture.
*
* @param[out] pOutGfxTexture  A pointer for receiving the converted <tt>gfx</tt> texture.
* @param[in] hGl4Texture  The GL4 texture to convert.
* @param[in] gl4BindTarget  The texture's <tt>GL_TEXTURE_TARGET</tt>.
* @param[in] imageFormat  The texture's image format.
*
* @pre
*  - <tt><var>pOutGfxTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutGfxTexture</var></tt> is not initialized.
*  - <tt><var>hGl4Texture</var></tt> is a valid GL4 texture object.
*
* @details
*  If the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt> is not <tt>GL_NONE</tt>, <tt><var>gl4BindTarget</var></tt> must match the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt>.
*/
    static void ConvertToGfxTexture( TTexture< Target >* pOutGfxTexture,
        GlHandleType hGl4Texture, GlEnumType gl4BindTarget, ImageFormat imageFormat ) NN_NOEXCEPT;

/**
    *@brief  Converts the specified GL4 texture to a <tt>gfx</tt> texture view.
*
* @param[out] pOutGfxTextureView  A pointer for receiving the converted <tt>gfx</tt> texture view.
* @param[in] hGl4Texture  The GL4 texture to convert.
* @param[in] gl4BindTarget  The texture's <tt>GL_TEXTURE_TARGET</tt>.
*
* @pre
*  - <tt><var>pOutGfxTextureView</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutGfxTextureView</var></tt> is not initialized.
*  - <tt><var>hGl4Texture</var></tt> is a valid GL texture object.
*
* @details
*  If the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt> is not <tt>GL_NONE</tt>, <tt><var>gl4BindTarget</var></tt> must match the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt>.
*/
    static void ConvertToGfxTextureView( TTextureView< Target >* pOutGfxTextureView,
        GlHandleType hGl4Texture, GlEnumType gl4BindTarget ) NN_NOEXCEPT;

/**
* @brief  Converts the specified GL4 texture to a <tt>gfx</tt> color target view.
*
* @param[out] pOutGfxColorTargetView  A pointer for receiving the converted <tt>gfx</tt> color target view.
* @param[in] hGl4Texture  The GL4 texture to convert.
* @param[in] gl4BindTarget  The texture's <tt>GL_TEXTURE_TARGET</tt>.
*
* @pre
*  - <tt><var>pOutGfxColorTargetView</var></tt> != <tt>NULLM</tt>.
*  - <tt><var>pOutGfxColorTargetView</var></tt> is not initialized.
*  - <tt><var>hGl4Texture</var></tt> is a valid GL texture object.
*
* @details
*  If the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt> is not <tt>GL_NONE</tt>, <tt><var>gl4BindTarget</var></tt> must match the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt>.
*/
    static void ConvertToGfxColorTargetView( TColorTargetView< Target >* pOutGfxColorTargetView,
        GlHandleType hGl4Texture, GlEnumType gl4BindTarget ) NN_NOEXCEPT;

/**
* @brief  Converts the specified GL4 texture to a <tt>gfx</tt> depth stencil view.
*
* @param[out] pOutGfxDepthStencilView  A pointer for receiving the converted <tt>gfx</tt> depth stencil view.
* @param[in] hGl4Texture  The GL4 texture to convert.
* @param[in] gl4BindTarget  The texture's <tt>GL_TEXTURE_TARGET</tt>.
* @param[in] gl4InternalFormat  The texture's <tt>GL_TEXTURE_INTERNAL_FORMAT</tt>.
*
* @pre
*  - <tt><var>pOutGfxDepthStencilView</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutGfxDepthStencilView</var></tt> is not initialized.
*  - <tt><var>hGl4Texture</var></tt> is a valid GL texture object.
*
* @details
*  If the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt> is not <tt>GL_NONE</tt>, <tt><var>gl4BindTarget</var></tt> must match the <tt>GL_TEXTURE_TARGET</tt> of <tt><var>hGl4Texture</var></tt>.
*/
    static void ConvertToGfxDepthStencilView( TDepthStencilView< Target >* pOutGfxDepthStencilView,
        GlHandleType hGl4Texture, GlEnumType gl4BindTarget, GlEnumType gl4InternalFormat ) NN_NOEXCEPT;
};

}
}
