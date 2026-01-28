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

#include <nvn/nvn.h>

#include <nn/nn_Macro.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>
#include <nn/gfx/gfx_Enum.h>

#include <nn/gfx/detail/gfx_Declare.h>

namespace nn {
namespace gfx {

/**
* @brief  Class for interoperability with the NVN API resources.
*
* @details
* The creator of the original object has ownership of the object.
* <tt>Finalize</tt> cannot be called on a <tt>gfx</tt> object for which <tt>Initialize</tt> has not been called.
*
* The context that created the original object and the context using that object must either be the same or have co-ownership.
*/
template<>
class TInteroperation< ApiVariation< ApiTypeNvn > >
{
    NN_DISALLOW_COPY( TInteroperation );
    TInteroperation() NN_NOEXCEPT;

public:
/**
* @brief  The target for the low-level graphics API.
*/
    typedef ApiVariation< ApiTypeNvn > Target;

/**
* @brief  Converts the specified NVN device to a <tt>gfx</tt> device.
    *
* @param[out] pOutGfxDevice  A pointer for receiving the converted <tt>gfx</tt> device.
* @param[in] pNvnDevice  Pointer to the NVN device to convert.
    *
* @pre
    * - <tt><var>pOutGfxDevice</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxDevice</var></tt> is not initialized.
    * - <tt><var>pNvnDevice</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxDevice( TDevice< Target >* pOutGfxDevice, NVNdevice* pNvnDevice ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN queue to a <tt>gfx</tt> queue.
    *
* @param[out] pOutGfxQueue  Pointer for receiving the converted <tt>gfx</tt> queue.
* @param[in] pNvnQueue  Pointer to the NVN queue to convert.
* @param[in] pGfxDevice  Pointer to the device.
    *
* @pre
    * - <tt><var>pOutGfxQueue</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxQueue</var></tt> is not initialized.
    * - <tt><var>pNvnQueue</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pGfxDevice</var></tt> is initialized if <tt><var>pGfxDevice</var></tt> != <tt>NULL</tt>.
    *
* @details
*  <tt>nn::gfx::Queue::CopyToScanBuffer</tt> cannot be used in the post-conversion queue if <tt>NULL</tt> was specified for <tt><var>pGfxDevice</var></tt>.
*/
    static void ConvertToGfxQueue( TQueue< Target >* pOutGfxQueue,
        NVNqueue* pNvnQueue, TDevice< Target >* pGfxDevice ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN memory pool to a <tt>gfx</tt> memory pool.
    *
* @param[out] pOutGfxMemoryPool  Pointer for receiving the converted <tt>gfx</tt> memory pool.
* @param[in] pNvnMemoryPool  Pointer to the NVN memory pool to convert.
* @param[in] pMemory  The CPU memory when you create <tt><var>pNvnMemoryPool</var></tt>.
    *
* @pre
    * - <tt><var>pOutGfxMemoryPool</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxMemoryPool</var></tt> is not initialized.
    * - <tt><var>pNvnMemoryPool</var></tt> != <tt>NULL</tt>.
    *
* @details
*  The following purposes are unavailable when <tt>NULL</tt> is specified for <tt><var>pMemory</var></tt>.
    * - As a memory pool used by a buffer descriptor pool
    * - As a memory pool without the <tt>NVN_MEMORY_POOL_FLAGS_CPU_CACHED</tt> attribute when textures tiled for the production device are used on a PC
*/
    static void ConvertToGfxMemoryPool( TMemoryPool< Target >* pOutGfxMemoryPool,
        NVNmemoryPool* pNvnMemoryPool, void* pMemory ) NN_NOEXCEPT;

/**
* @brief  Converts the specified <tt>nvn</tt> descriptor pool to a <tt>gfx</tt> descriptor pool.
    *
* @param[out] pOutGfxDescriptorPool  Pointer for receiving the converted <tt>gfx</tt> descriptor pool.
* @param[in] pNvnTexturePool  Pointer to the NVN texture pool to convert.
    *
* @pre
    * - <tt><var>pOutGfxDescriptorPool</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxDescriptorPool</var></tt> is not initialized.
    * - <tt><var>pNvnTexturePool</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxDescriptorPool( TDescriptorPool< Target >* pOutGfxDescriptorPool,
        NVNtexturePool* pNvnTexturePool ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN sampler pool to a <tt>gfx</tt> descriptor pool.
    *
* @param[out] pOutGfxDescriptorPool  Pointer for receiving the converted <tt>gfx</tt> descriptor pool.
* @param[in] pNvnSamplerPool  Pointer to the NVN sampler pool to convert.
    *
* @pre
    * - <tt><var>pOutGfxDescriptorPool</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxDescriptorPool</var></tt> is not initialized.
    * - <tt><var>pNvnSamplerPool</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxDescriptorPool( TDescriptorPool< Target >* pOutGfxDescriptorPool,
        NVNsamplerPool* pNvnSamplerPool ) NN_NOEXCEPT;


/**
* @brief  Converts the specified NVN buffer to a <tt>gfx</tt> buffer.
    *
* @param[out] pOutGfxBuffer  Pointer for receiving the converted <tt>gfx</tt> buffer.
* @param[in] pNvnBuffer  Pointer to the NVN buffer to convert.
    *
* @pre
    * - <tt><var>pOutGfxBuffer</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxBuffer</var></tt> is not initialized.
    * - <tt><var>pNvnBuffer</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxBuffer( TBuffer< Target >* pOutGfxBuffer, NVNbuffer* pNvnBuffer ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN command buffer to a <tt>gfx</tt> command buffer.
    *
* @param[out] pOutGfxCommandBuffer  Pointer for receiving the converted <tt>gfx</tt> command buffer.
* @param[in] pDevice  Pointer to the device. This parameter could go away in future.
* @param[in] pNvnCommandBuffer  Pointer to the NVN command buffer to convert.
    *
* @pre
    * - <tt><var>pOutGfxCommandBuffer</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxCommandBuffer</var></tt> is not initialized.
    * - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pNvnCommandBuffer</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxCommandBuffer( TCommandBuffer< Target >* pOutGfxCommandBuffer,
        TDevice< Target >* pDevice, NVNcommandBuffer* pNvnCommandBuffer ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN sampler to a <tt>gfx</tt> sampler.
    *
* @param[out] pOutGfxSampler  Pointer for receiving the converted <tt>gfx</tt> sampler.
* @param[in] pNvnSampler  Pointer to the NVN sampler to convert.
    *
* @pre
    * - <tt><var>pOutGfxSampler</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxSampler</var></tt> is not initialized.
    * - <tt><var>pNvnSampler</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxSampler( TSampler< Target >* pOutGfxSampler,
        NVNsampler* pNvnSampler ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN program to a <tt>gfx</tt> shader.
    *
* @param[out] pOutGfxShader  Pointer for receiving the converted <tt>gfx</tt> shader.
* @param[in] pNvnProgram  Pointer to the NVN program to convert.
* @param[in] isSeparable  Boolean value for whether <tt><var>pNvnProgram</var></tt> was created separately.
* @param[in] stageBits  The stage held by <tt><var>pNvnProgram</var></tt>, represented by a combination of <tt>nn::gfx::ShaderStageBit</tt> instances.
    *
* @pre
    * - <tt><var>pOutGfxShader</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxShader</var></tt> is not initialized.
    * - <tt><var>pNvnProgram</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxShader( TShader< Target >* pOutGfxShader,
        NVNprogram* pNvnProgram, bool isSeparable, int stageBits ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN texture to a <tt>gfx</tt> texture.
    *
* @param[out] pOutGfxTexture  Pointer for receiving the converted <tt>gfx</tt> texture.
* @param[in] pNvnTexture  Pointer to the NVN texture to convert.
    *
* @pre
    * - <tt><var>pOutGfxTexture</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxTexture</var></tt> is not initialized.
    * - <tt><var>pNvnTexture</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxTexture( TTexture< Target >* pOutGfxTexture,
        NVNtexture* pNvnTexture ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN texture view to a <tt>gfx</tt> texture view.
    *
* @param[out] pOutGfxTextureView  Pointer for receiving the converted <tt>gfx</tt> texture view.
* @param[in] pNvnTexture  Pointer to the NVN texture to convert.
* @param[in] pNvnTextureView  Pointer to the NVN texture view to convert.
    *
* @pre
    * - <tt><var>pOutGfxTextureView</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxTextureView</var></tt> is not initialized.
    * - <tt><var>pNvnTexture</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pNvnTextureView</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxTextureView( TTextureView< Target >* pOutGfxTextureView,
        NVNtexture* pNvnTexture, NVNtextureView* pNvnTextureView ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN texture view to a <tt>gfx</tt> color target view.
    *
* @param[out] pOutGfxColorTargetView  Pointer for receiving the converted <tt>gfx</tt> color target view.
* @param[in] pNvnTexture  Pointer to the NVN texture to convert.
* @param[in] pNvnTextureView  Pointer to the NVN texture view to convert.
    *
* @pre
    * - <tt><var>pOutGfxColorTargetView</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxColorTargetView</var></tt> is not initialized.
    * - <tt><var>pNvnTexture</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pNvnTextureView</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxColorTargetView( TColorTargetView< Target >* pOutGfxColorTargetView,
        NVNtexture* pNvnTexture, NVNtextureView* pNvnTextureView ) NN_NOEXCEPT;

/**
* @brief  Converts the specified NVN texture view to a <tt>gfx</tt> depth stencil view.
    *
* @param[out] pOutGfxDepthStencilView  Pointer for receiving the converted <tt>gfx</tt> depth stencil view.
* @param[in] pNvnTexture  Pointer to the NVN texture to convert.
* @param[in] pNvnTextureView  Pointer to the NVN texture view to convert.
    *
* @pre
    * - <tt><var>pOutGfxDepthStencilView</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pOutGfxDepthStencilView</var></tt> is not initialized.
    * - <tt><var>pNvnTexture</var></tt> != <tt>NULL</tt>.
    * - <tt><var>pNvnTextureView</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertToGfxDepthStencilView( TDepthStencilView< Target >* pOutGfxDepthStencilView,
        NVNtexture* pNvnTexture, NVNtextureView* pNvnTextureView ) NN_NOEXCEPT;

/**
* @brief  Converts the specified <tt>gfx</tt> image format to the <tt>nvn</tt> format.
    *
* @param[in] gfxImageFormat  The <tt>gfx</tt> image format to convert.
    *
* @return  Returns the converted <tt>nvn</tt> format.
*/
    static NVNformat ConvertToNvnFormat( ImageFormat gfxImageFormat ) NN_NOEXCEPT;

/**
* @brief  Converts the specified <tt>gfx</tt> attribute format to the <tt>nvn</tt> format.
    *
* @param[in] gfxAttributeFormat  The <tt>gfx</tt> attribute format to convert.
    *
* @return  Returns the converted <tt>nvn</tt> format.
*/
    static NVNformat ConvertToNvnFormat( AttributeFormat gfxAttributeFormat ) NN_NOEXCEPT;
};

}
}
