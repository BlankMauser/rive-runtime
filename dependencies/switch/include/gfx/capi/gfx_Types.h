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
* @brief  Type definitions.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_TargetConfig.h>

#include <nn/gfx/detail/gfx_Declare.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL )
    #include <nn/gfx/gfx_Types-api.gl.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX )
    #include <nn/gfx/gfx_Types-api.gx.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN )
    #include <nn/gfx/gfx_Types-api.nvn.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D )
    #include <nn/gfx/gfx_Types-api.d3d.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK )
    #include <nn/gfx/gfx_Types-api.vk.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX )
    #include <nn/gfx/gfx_Types-api.ex.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  The type definition representing a buffer.
*
* @see
*  nn::gfx::TBuffer
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TBuffer< TargetConfig::Variation > Buffer;

/**
* @brief  The type definition representing a buffer texture view.
*
* @see
*  nn::gfx::TBufferTextureView
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TBufferTextureView< TargetConfig::Variation > BufferTextureView;

/**
* @brief  The type definition representing a command buffer.
*
* @see
*  nn::gfx::TCommandBuffer
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TCommandBuffer< TargetConfig::Variation > CommandBuffer;

/**
* @brief  The type definition representing a descriptor pool.
*
* @see
*  nn::gfx::TDescriptorPool
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TDescriptorPool< TargetConfig::Variation > DescriptorPool;

/**
* @brief  The type definition representing a device.
*
* @see
*  nn::gfx::TDevice
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TDevice< TargetConfig::Variation > Device;

/**
* @brief  The type definition representing a memory pool.
*
* @see
*  nn::gfx::TMemoryPool
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TMemoryPool< TargetConfig::Variation > MemoryPool;

/**
* @brief  The type definition representing a pipeline.
*
* @see
*  nn::gfx::TPipeline
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TPipeline< TargetConfig::Variation > Pipeline;

/**
* @brief  Type definition representing a queue.
*
* @see
*  nn::gfx::TQueue
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TQueue< TargetConfig::Variation > Queue;

/**
* @brief  The type definition representing a sampler.
*
* @see
*  nn::gfx::TSampler
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TSampler< TargetConfig::Variation > Sampler;

/**
* @brief  The type definition representing a shader.
*
* @see
*  nn::gfx::TShader
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TShader< TargetConfig::Variation > Shader;

/**
* @brief  The type definition representing a rasterizer state.
*
* @see
*  nn::gfx::TRasterizerState
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TRasterizerState< TargetConfig::Variation > RasterizerState;

/**
* @brief  The type definition representing a blend state.
*
* @see
*  nn::gfx::TBlendState
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TBlendState< TargetConfig::Variation > BlendState;

/**
* @brief  The type definition representing a depth stencil state.
*
* @see
*  nn::gfx::TDepthStencilState
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TDepthStencilState< TargetConfig::Variation > DepthStencilState;

/**
* @brief  The type definition representing a vertex state.
*
* @see
*  nn::gfx::TVertexState
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TVertexState< TargetConfig::Variation > VertexState;

/**
* @brief  The type definition representing a tessellation state.
*
* @see
*  nn::gfx::TTessellationState
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TTessellationState< TargetConfig::Variation > TessellationState;

/**
* @brief  The type definition representing a viewport scissor state.
*
* @see
*  nn::gfx::TViewportScissorState
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TViewportScissorState< TargetConfig::Variation > ViewportScissorState;

/**
* @brief  The type definition representing a swap chain.
*
* @see
*  nn::gfx::TSwapChain
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TSwapChain< TargetConfig::Variation > SwapChain;

/**
* @brief  The type definition representing a fence.
*
* @see
*  nn::gfx::TFence
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TFence< TargetConfig::Variation > Fence;

/**
* @brief  The type definition representing a semaphore.
*
* @see
*  nn::gfx::TSemaphore
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TSemaphore< TargetConfig::Variation > Semaphore;

/**
* @brief  The type definition representing a texture.
*
* @see
*  nn::gfx::TTexture
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TTexture< TargetConfig::Variation > Texture;

/**
* @brief  The type definition representing a texture view.
*
* @see
*  nn::gfx::TTextureView
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TTextureView< TargetConfig::Variation > TextureView;

/**
* @brief  The type definition representing a color target view.
*
* @see
*  nn::gfx::TColorTargetView
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TColorTargetView< TargetConfig::Variation > ColorTargetView;

/**
* @brief  The type definition representing a depth stencil view.
*
* @see
*  nn::gfx::TDepthStencilView
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TDepthStencilView< TargetConfig::Variation > DepthStencilView;

/**
* @brief  The type definition representing a buffer used for timestamps.
*
* @see
*  nn::gfx::TTimestampBuffer
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TTimestampBuffer< TargetConfig::Variation > TimestampBuffer;

/**
* @brief  The type definition representing a buffer used for queries.
*
* @see
*  nn::gfx::TQueryBuffer
*
* @details
*  To specify the target low-level graphics API explicitly, use the special version with the suffix.
*/
typedef TQueryBuffer< TargetConfig::Variation > QueryBuffer;

}
}
