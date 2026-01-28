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
* @brief  Type definitions (GL4 special edition).
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>
#include <nn/gfx/gfx_Device.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Core-api.gl.4.h>
#include <nn/gfx/detail/gfx_Texture-api.gl.4.h>
#include <nn/gfx/detail/gfx_Device-api.gl.4.h>
#include <nn/gfx/detail/gfx_BufferLayout-api.gl.4.h>

namespace nn {
namespace gfx {

/**
* @brief  The type definition representing a buffer (GL4 special edition).
*/
typedef TBuffer< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Buffer, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a buffer texture view (GL4 special edition).
*/
typedef TBufferTextureView< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( BufferTextureView, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a command buffer (GL4 special edition).
*/
typedef TCommandBuffer< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( CommandBuffer, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a descriptor pool (GL4 special edition).
*/
typedef TDescriptorPool< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( DescriptorPool, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a device (GL4 special edition).
*/
typedef TDevice< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Device, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a memory pool (GL4 special edition).
*/
typedef TMemoryPool< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( MemoryPool, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a pipeline (GL4 special edition).
*/
typedef TPipeline< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Pipeline, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a queue (GL4 special edition).
*/
typedef TQueue< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Queue, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a sampler (GL4 special edition).
*/
typedef TSampler< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Sampler, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a shader (GL4 special edition).
*/
typedef TShader< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Shader, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a rasterizer state (GL4 special edition).
*/
typedef TRasterizerState< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( RasterizerState, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a blend state (GL4 special edition).
*/
typedef TBlendState< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( BlendState, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a depth stencil state (GL4 special edition).
*/
typedef TDepthStencilState< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( DepthStencilState, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a vertex state (GL4 special edition).
*/
typedef TVertexState< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( VertexState, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The structure representing a tessellation state (GL4 special edition).
*/
typedef TTessellationState< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( TessellationState, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a viewport scissor state (GL4 special edition).
*/
typedef TViewportScissorState< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( ViewportScissorState, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a swap chain (GL4 special edition).
*/
typedef TSwapChain< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( SwapChain, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a fence (GL4 special edition).
*/
typedef TFence< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Fence, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a semaphore (GL4 special edition).
*/
typedef TSemaphore< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Semaphore, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a texture (GL4 special edition).
*/
typedef TTexture< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Texture, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a texture view (GL4 special edition).
*/
typedef TTextureView< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( TextureView, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a color target view (GL4 special edition).
*/
typedef TColorTargetView< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( ColorTargetView, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a depth stencil view (GL4 special edition).
*/
typedef TDepthStencilView< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( DepthStencilView, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  Call type definition for interoperability (GL4 special edition).
*/
typedef TInteroperation< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( Interoperation, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a buffer used for timestamps (GL4 special edition).
*/
typedef TTimestampBuffer< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( TimestampBuffer, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  The type definition representing a buffer used for queries (GL4 special edition).
*/
typedef TQueryBuffer< ApiVariationGl4 >
    NN_MACRO_CONCATENATE( QueryBuffer, NN_MACRO_CONCATENATE( NN_GFX_GL_SUFFIX, 4 ) );

/**
* @brief  Initializes the <tt>gfx</tt> library (GL4 special edition).
*
* @post
*  The <tt>gfx</tt> library is initialized.
*/
inline void NN_MACRO_CONCATENATE( Initialize, NN_MACRO_CONCATENATE(
    NN_GFX_GL_SUFFIX, 4 ) )() NN_NOEXCEPT
{
    return detail::Initialize< ApiVariationGl4 >();
}

/**
* @brief  Finalizes the <tt>gfx</tt> library (GL4 special edition).
*
* @post
*  The <tt>gfx</tt> library is finalized.
*/
inline void NN_MACRO_CONCATENATE( Finalize, NN_MACRO_CONCATENATE(
    NN_GFX_GL_SUFFIX, 4 ) )() NN_NOEXCEPT
{
    return detail::Finalize< ApiVariationGl4 >();
}

/**
* @brief  Gets the properties of the image format (GL4 special edition).
*
* @param[out] pOutImageFormatProperty  Pointer to the location to store the obtained image format properties.
* @param[in] pDevice  Pointer to the device.
* @param[in] imageFormat  The image format to get information about.
*
* @pre
*  - <tt><var>pOutImageFormatProperty</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*
* @post
*  - The region pointed to by <tt><var>pOutImageFormatProperty</var></tt> stores the property information for the image format.
*/
inline void GetImageFormatPropertyGl4( ImageFormatProperty* pOutImageFormatProperty,
    TDevice< ApiVariationGl4 >* pDevice, ImageFormat imageFormat ) NN_NOEXCEPT
{
    return detail::GetImageFormatProperty< ApiVariationGl4 >(
        pOutImageFormatProperty, pDevice, imageFormat );
}

/**
* @brief  Gets the time between two timestamps (GL4 special edition).
*
* @param[in] startTimestampValue  The starting-point timestamp.
* @param[in] endTimestampValue  The ending-point timestamp.
*
* @return  Returns the time between the specified starting and ending points.
*
* @details
*  For the timestamp values, you can use the values obtained by <tt>nn::gfx::TimestampBuffer::GetValue</tt>.
*/
inline nn::TimeSpan GetDurationGl4(
    int64_t startTimestampValue, int64_t endTimestampValue ) NN_NOEXCEPT
{
    return detail::GetDuration< ApiVariationGl4 >( startTimestampValue, endTimestampValue );
}

}
}
