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
* @brief  Defines the utility function that adds debugging labels to <tt>nn::gfx</tt> objects.
*/

#pragma once

#include <nn/gfx.h>

namespace nn {
namespace gfx {
namespace util {

/**
* @brief  Adds debugging labels to <tt>nn::gfx::MemoryPool</tt>.
*
* @param[in] pMemoryPool  Pointer to the memory pool that adds debugging labels.
* @param[in] label  Debugging label string.
*
*/
template< typename TTarget >
void SetMemoryPoolDebugLabel( TMemoryPool< TTarget >* pMemoryPool, const char* label ) NN_NOEXCEPT;

/**
* @brief  Adds debugging labels to <tt>nn::gfx::Buffer</tt>.
*
* @param[in] pBuffer  Pointer to the buffer that adds debugging labels.
* @param[in] label  Debugging label string.
*
*/
template< typename TTarget >
void SetBufferDebugLabel( TBuffer< TTarget >* pBuffer, const char* label ) NN_NOEXCEPT;

/**
* @brief  Adds debugging labels to <tt>nn::gfx::Texture</tt>.
*
* @param[in] pTexture  Pointer to the texture for which to add debugging labels.
* @param[in] label  Debugging label string.
*
*/
template< typename TTarget >
void SetTextureDebugLabel( TTexture< TTarget >* pTexture, const char* label ) NN_NOEXCEPT;

/**
* @brief  Adds debugging labels to <tt>nn::gfx::Sampler</tt>.
*
* @param[in] pSampler  Pointer to the sampler to which to add debugging labels.
* @param[in] label  Debugging label string.
*
*/
template< typename TTarget >
void SetSamplerDebugLabel( TSampler< TTarget >* pSampler, const char* label) NN_NOEXCEPT;

} // namespace util
} // namespace gfx
} // namespace nn
