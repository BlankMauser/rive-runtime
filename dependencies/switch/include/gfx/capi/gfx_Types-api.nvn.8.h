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
* @brief  Type definitions (NVN8 special edition).
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>
#include <nn/gfx/gfx_Device.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Core-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Texture-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#include <nn/gfx/detail/gfx_BufferLayout-api.nvn.8.h>

namespace nn {
namespace gfx {

/**
* @brief  The type definition representing a buffer (NVN8 special edition).
*/
typedef TBuffer< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Buffer, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a buffer texture view (NVN8 special edition).
*/
typedef TBufferTextureView< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( BufferTextureView, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a command buffer (NVN8 special edition).
*/
typedef TCommandBuffer< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( CommandBuffer, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a device (NVN8 special edition).
*/
typedef TDevice< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Device, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a pipeline (NVN8 special edition).
*/
typedef TPipeline< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Pipeline, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a queue (NVN8 special edition).
*/
typedef TQueue< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Queue, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing the sampler (NVN8 special edition).
*/
typedef TSampler< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Sampler, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a shader (NVN8 special edition).
*/
typedef TShader< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Shader, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a rasterizer state (NVN8 special edition).
*/
typedef TRasterizerState< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( RasterizerState, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a blend state (NVN8 special edition).
*/
typedef TBlendState< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( BlendState, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a depth stencil state (NVN8 special edition).
*/
typedef TDepthStencilState< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( DepthStencilState, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing the vertex state (NVN8 special edition).
*/
typedef TVertexState< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( VertexState, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a tessellation state (NVN8 special edition).
*/
typedef TTessellationState< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( TessellationState, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a viewport scissor state (NVN8 special edition).
*/
typedef TViewportScissorState< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( ViewportScissorState, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a swap chain (NVN8 special edition).
*/
typedef TSwapChain< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( SwapChain, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a fence (NVN8 special edition).
*/
typedef TFence< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Fence, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a semaphore (NVN8 special edition).
*/
typedef TSemaphore< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Semaphore, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a texture (NVN8 special edition).
*/
typedef TTexture< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( Texture, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a texture view (NVN8 special edition).
*/
typedef TTextureView< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( TextureView, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a color target view (NVN8 special edition).
*/
typedef TColorTargetView< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( ColorTargetView, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a depth stencil view (NVN8 special edition).
*/
typedef TDepthStencilView< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( DepthStencilView, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition for the class for interoperability (NVN8 special edition).
*/
typedef TInteroperation< ApiVariation< ApiTypeNvn > >
    NN_MACRO_CONCATENATE( Interoperation, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a buffer used for timestamps (NVN8 special edition).
*/
typedef TTimestampBuffer< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( TimestampBuffer, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  The type definition representing a buffer used for queries (NVN8 special edition).
*/
typedef TQueryBuffer< ApiVariationNvn8 >
    NN_MACRO_CONCATENATE( QueryBuffer, NN_MACRO_CONCATENATE( NN_GFX_NVN_SUFFIX, 8 ) );

/**
* @brief  Initializes the <tt>gfx</tt> library (NVN8 special edition).
*
* @post
*  The <tt>gfx</tt> library is initialized.
*/
inline void NN_MACRO_CONCATENATE( Initialize, NN_MACRO_CONCATENATE(
    NN_GFX_NVN_SUFFIX, 8 ) )() NN_NOEXCEPT
{
    return detail::Initialize< ApiVariationNvn8 >();
}

/**
* @brief  Finalizes the <tt>gfx</tt> library (NVN8 special edition).
*
* @post
*  The <tt>gfx</tt> library is finalized.
*/
inline void NN_MACRO_CONCATENATE( Finalize, NN_MACRO_CONCATENATE(
    NN_GFX_NVN_SUFFIX, 8 ) )() NN_NOEXCEPT
{
    return detail::Finalize< ApiVariationNvn8 >();
}

/**
* @brief  Gets the properties of the image format (NVN8 special edition).
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
inline void GetImageFormatPropertyNvn8( ImageFormatProperty* pOutImageFormatProperty,
    TDevice< ApiVariationNvn8 >* pDevice, ImageFormat imageFormat ) NN_NOEXCEPT
{
    return detail::GetImageFormatProperty< ApiVariationNvn8 >(
        pOutImageFormatProperty, pDevice, imageFormat );
}

/**
* @brief  Gets the time between two timestamps (NVN8 special edition).
*
* @param[in] startTimestampValue  The starting-point timestamp.
* @param[in] endTimestampValue  The ending-point timestamp.
*
* @return  Returns the time between the specified starting and ending points.
*
* @details
*  For the timestamp values, you can use the values obtained by <tt>nn::gfx::TimestampBuffer::GetValue</tt>.
*/
inline nn::TimeSpan GetDurationNvn8( int64_t startTimestampValue, int64_t endTimestampValue ) NN_NOEXCEPT
{
    return detail::GetDuration< ApiVariationNvn8 >( startTimestampValue, endTimestampValue );
}

}
}
