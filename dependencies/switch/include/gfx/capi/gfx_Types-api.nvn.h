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
* @brief  Type definitions (NVN special edition).
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>
#include <nn/gfx/gfx_Device.h>

#include <nn/gfx/detail/gfx_Declare.h>

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/gfx_Types-api.nvn.8.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  The type definition representing a buffer (NVN special edition).
*/
typedef TBuffer< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Buffer, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a buffer texture view (NVN special edition).
*/
typedef TBufferTextureView< ApiTypeNvn >
    NN_MACRO_CONCATENATE( BufferTextureView, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a command buffer (NVN special edition).
*/
typedef TCommandBuffer< ApiTypeNvn >
    NN_MACRO_CONCATENATE( CommandBuffer, NN_GFX_NVN_SUFFIX );

/**
* @brief  The structure representing a descriptor pool (NVN special edition)
*/
typedef TDescriptorPool< ApiTypeNvn >
    NN_MACRO_CONCATENATE( DescriptorPool, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a device (NVN special edition).
*/
typedef TDevice< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Device, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a memory pool (NVN special edition).
*/
typedef TMemoryPool< ApiTypeNvn >
    NN_MACRO_CONCATENATE( MemoryPool, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a pipeline (NVN special edition).
*/
typedef TPipeline< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Pipeline, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a queue (NVN special edition).
*/
typedef TQueue< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Queue, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing the sampler (NVN special edition).
*/
typedef TSampler< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Sampler, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a shader (NVN special edition).
*/
typedef TShader< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Shader, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a rasterizer state (NVN special edition).
*/
typedef TRasterizerState< ApiTypeNvn >
    NN_MACRO_CONCATENATE( RasterizerState, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a blend state (NVN special edition).
*/
typedef TBlendState< ApiTypeNvn >
    NN_MACRO_CONCATENATE( ColorState, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a depth stencil state (NVN special edition).
*/
typedef TDepthStencilState< ApiTypeNvn >
    NN_MACRO_CONCATENATE( DepthStencilState, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing the vertex state (NVN special edition).
*/
typedef TVertexState< ApiTypeNvn >
    NN_MACRO_CONCATENATE( VertexState, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a tessellation state (NVN special edition).
*/
typedef TTessellationState< ApiTypeNvn >
    NN_MACRO_CONCATENATE( TessellationState, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a viewport scissor state (NVN special edition).
*/
typedef TViewportScissorState< ApiTypeNvn >
    NN_MACRO_CONCATENATE( ViewportScissorState, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a swap chain (NVN special edition).
*/
typedef TSwapChain< ApiTypeNvn >
    NN_MACRO_CONCATENATE( SwapChain, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a fence (NVN special edition).
*/
typedef TFence< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Fence, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a semaphore (NVN special edition).
*/
typedef TSemaphore< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Semaphore, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a texture (NVN special edition).
*/
typedef TTexture< ApiTypeNvn >
    NN_MACRO_CONCATENATE( Texture, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a texture view (NVN special edition).
*/
typedef TTextureView< ApiTypeNvn >
    NN_MACRO_CONCATENATE( TextureView, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a color target view (NVN special edition).
*/
typedef TColorTargetView< ApiTypeNvn >
    NN_MACRO_CONCATENATE( ColorTargetView, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a depth stencil view (NVN special edition).
*/
typedef TDepthStencilView< ApiTypeNvn >
    NN_MACRO_CONCATENATE( DepthStencilView, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a buffer used for timestamps (NVN special edition).
*/
typedef TTimestampBuffer< ApiTypeNvn >
    NN_MACRO_CONCATENATE( TimestampBuffer, NN_GFX_NVN_SUFFIX );

/**
* @brief  The type definition representing a buffer used for queries (NVN special edition).
*/
typedef TQueryBuffer< ApiTypeNvn >
    NN_MACRO_CONCATENATE( QueryBuffer, NN_GFX_NVN_SUFFIX );

/**
* @brief  Initializes the <tt>gfx</tt> library (NVN special edition).
*
* @post
*  The <tt>gfx</tt> library is initialized.
*/
inline void NN_MACRO_CONCATENATE( Initialize, NN_GFX_NVN_SUFFIX )() NN_NOEXCEPT
{
    return detail::Initialize< ApiTypeNvn >();
}

/**
* @brief  Finalizes the <tt>gfx</tt> library (NVN special edition).
*
* @post
*  The <tt>gfx</tt> library is finalized.
*/
inline void NN_MACRO_CONCATENATE( Finalize, NN_GFX_NVN_SUFFIX )() NN_NOEXCEPT
{
    return detail::Finalize< ApiTypeNvn >();
}

/**
* @brief  Gets the properties of the image format (NVN special edition).
*
* @param[out] pOutImageFormatProperty  Pointer to the place to store the obtained image format properties.
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
inline void GetImageFormatPropertyNvn(
    ImageFormatProperty* pOutImageFormatProperty, TDevice< typename
    detail::TargetVariation< ApiTypeNvn >::Type >* pDevice, ImageFormat imageFormat ) NN_NOEXCEPT
{
    return detail::GetImageFormatProperty< typename detail::TargetVariation<
        ApiTypeNvn >::Type >( pOutImageFormatProperty, pDevice, imageFormat );
}

/**
* @brief  Gets the time between two timestamps (NVN special edition).
*
* @param[in] startTimestampValue  The starting-point timestamp.
* @param[in] endTimestampValue  The ending-point timestamp.
*
* @return  Returns the time between the specified starting and ending points.
*
* @details
*  For the timestamp values, you can use the values obtained by <tt>nn::gfx::TimestampBuffer::GetValue</tt>.
*/
inline nn::TimeSpan GetDurationNvn(
    int64_t startTimestampValue, int64_t endTimestampValue ) NN_NOEXCEPT
{
    return detail::GetDuration< typename detail::TargetVariation<
        ApiTypeNvn >::Type >( startTimestampValue, endTimestampValue );
}

}
}
