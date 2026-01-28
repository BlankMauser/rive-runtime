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
* @brief  Definitions for types (GL special edition).
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>
#include <nn/gfx/gfx_Device.h>

#include <nn/gfx/detail/gfx_Declare.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/gfx_Types-api.gl.4.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  The type definition representing a buffer (GL special edition).
*/
typedef TBuffer< ApiTypeGl >
    NN_MACRO_CONCATENATE( Buffer, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a buffer texture view (GL special edition).
*/
typedef TBufferTextureView< ApiTypeGl >
    NN_MACRO_CONCATENATE( BufferTextureView, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a command buffer (GL special edition).
*/
typedef TCommandBuffer< ApiTypeGl >
    NN_MACRO_CONCATENATE( CommandBuffer, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a descriptor pool (GL special edition).
*/
typedef TDescriptorPool< ApiTypeGl >
    NN_MACRO_CONCATENATE( DescriptorPool, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a device (GL special edition).
*/
typedef TDevice< ApiTypeGl >
    NN_MACRO_CONCATENATE( Device, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a memory pool (GL special edition).
*/
typedef TMemoryPool< ApiTypeGl >
    NN_MACRO_CONCATENATE( MemoryPool, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a pipeline (GL special edition).
*/
typedef TPipeline< ApiTypeGl >
    NN_MACRO_CONCATENATE( Pipeline, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a queue (GL special edition).
*/
typedef TQueue< ApiTypeGl >
    NN_MACRO_CONCATENATE( Queue, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing the sampler (GL special edition).
*/
typedef TSampler< ApiTypeGl >
    NN_MACRO_CONCATENATE( Sampler, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a shader (GL special edition).
*/
typedef TShader< ApiTypeGl >
    NN_MACRO_CONCATENATE( Shader, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a rasterizer state (GL special edition).
*/
typedef TRasterizerState< ApiTypeGl >
    NN_MACRO_CONCATENATE( RasterizerState, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a blend state (GL special edition).
*/
typedef TBlendState< ApiTypeGl >
    NN_MACRO_CONCATENATE( BlendState, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a depth stencil state (GL special edition).
*/
typedef TDepthStencilState< ApiTypeGl >
    NN_MACRO_CONCATENATE( DepthStencilState, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing the vertex state (GL special edition).
*/
typedef TVertexState< ApiTypeGl >
    NN_MACRO_CONCATENATE( VertexState, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a tessellation state (GL special edition).
*/
typedef TTessellationState< ApiTypeGl >
    NN_MACRO_CONCATENATE( TessellationState, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a viewport scissor state (GL special edition).
*/
typedef TViewportScissorState< ApiTypeGl >
    NN_MACRO_CONCATENATE( ViewportScissorState, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a swap chain (GL special edition).
*/
typedef TSwapChain< ApiTypeGl >
    NN_MACRO_CONCATENATE( SwapChain, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a fence (GL special edition).
*/
typedef TFence< ApiTypeGl >
    NN_MACRO_CONCATENATE( Fence, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a semaphore (GL special edition).
*/
typedef TSemaphore< ApiTypeGl >
    NN_MACRO_CONCATENATE( Semaphore, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a texture (GL special edition).
*/
typedef TTexture< ApiTypeGl >
    NN_MACRO_CONCATENATE( Texture, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a texture view (GL special edition).
*/
typedef TTextureView< ApiTypeGl >
    NN_MACRO_CONCATENATE( TextureView, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a color target view (GL special edition).
*/
typedef TColorTargetView< ApiTypeGl >
    NN_MACRO_CONCATENATE( ColorTargetView, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a depth stencil view (GL special edition).
*/
typedef TDepthStencilView< ApiTypeGl >
    NN_MACRO_CONCATENATE( DepthStencilView, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a buffer used for timestamps (GL special edition).
*/
typedef TTimestampBuffer< ApiTypeGl >
    NN_MACRO_CONCATENATE( TimestampBuffer, NN_GFX_GL_SUFFIX );

/**
* @brief  The type definition representing a buffer used for queries (GL special edition).
*/
typedef TQueryBuffer< ApiTypeGl >
    NN_MACRO_CONCATENATE( QueryBuffer, NN_GFX_GL_SUFFIX );

/**
* @brief  Initializes the <tt>gfx</tt> library (GL special edition).
*
* @post
*  The <tt>gfx</tt> library is initialized.
*/
inline void NN_MACRO_CONCATENATE( Initialize, NN_GFX_GL_SUFFIX )() NN_NOEXCEPT
{
    return detail::Initialize< ApiTypeGl >();
}

/**
* @brief  Finalizes the <tt>gfx</tt> library (GL special edition).
*
* @post
*  The <tt>gfx</tt> library is finalized.
*/
inline void NN_MACRO_CONCATENATE( Finalize, NN_GFX_GL_SUFFIX )() NN_NOEXCEPT
{
    return detail::Finalize< ApiTypeGl >();
}

/**
* @brief  Gets the properties of the image format (GL special edition).
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
inline void GetImageFormatPropertyGl(
    ImageFormatProperty* pOutImageFormatProperty, TDevice< typename
    detail::TargetVariation< ApiTypeGl >::Type >* pDevice, ImageFormat imageFormat ) NN_NOEXCEPT
{
    return detail::GetImageFormatProperty< typename detail::TargetVariation<
        ApiTypeGl >::Type >( pOutImageFormatProperty, pDevice, imageFormat );
}

/**
* @brief  Gets the time between two timestamps (GL special edition).
*
* @param[in] startTimestampValue  The starting-point timestamp.
* @param[in] endTimestampValue  The ending-point timestamp.
*
* @return  Returns the time between the specified starting and ending points.
*
* @details
*  For the timestamp values, you can use the values obtained by <tt>nn::gfx::TimestampBuffer::GetValue</tt>.
*/
inline nn::TimeSpan GetDurationGl(
    int64_t startTimestampValue, int64_t endTimestampValue ) NN_NOEXCEPT
{
    return detail::GetDuration< typename detail::TargetVariation<
        ApiTypeGl >::Type >( startTimestampValue, endTimestampValue );
}

}
}
