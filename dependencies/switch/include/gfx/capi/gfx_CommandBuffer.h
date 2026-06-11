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
* @brief  Declarations for API resources for the command buffer.
*/

#pragma once

#include <nn/nn_Macro.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_CommandBufferInfo.h>
#include <nn/gfx/gfx_TextureInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_RequiredMemory.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_CommandBuffer-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_CommandBuffer-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_CommandBuffer-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_CommandBuffer-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_CommandBuffer-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_CommandBuffer-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

class GpuAddress;
class DescriptorSlot;
class ViewportStateInfo;
class ScissorStateInfo;

/**
* @brief  Graphics abstraction layer representing a command buffer.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TCommandBuffer
    : public detail::CommandBufferImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TCommandBuffer );

    typedef detail::CommandBufferImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the command buffer.
*/
    typedef CommandBufferInfo InfoType;

/**
* @brief  The type for a callback function that takes insufficient memory events.
*/
    typedef void ( *OutOfMemoryEventCallback )(
        TCommandBuffer< Target >* pCommandBuffer, const OutOfMemoryEventArg& arg );

/**
* @brief  Gets the alignment required for command memory.
*
* @param[in] pDevice  Pointer to the device.
*
* @return  Returns the alignment required for command memory.
*/
    static size_t GetCommandMemoryAlignment( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::GetCommandMemoryAlignment( pDevice );
    }

/**
* @brief  Gets the required alignment from control memory.
*
* @param[in] pDevice  Pointer to the device.
*
* @return  Returns the required alignment to control memory.
*/
    static size_t GetControlMemoryAlignment( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::GetControlMemoryAlignment( pDevice );
    }

/**
* @brief  Constructor.
*/
    TCommandBuffer() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the command buffer.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The command buffer is not initialized.
*
* @post
*  - The command buffer is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys the command buffer.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The command buffer is initialized.
*  - Addition of commands has not begun.
*
* @post
*  The command buffer is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Adds command memory.
*
* @param[in] pMemoryPool  Pointer to the memory pool where command memory is placed.
* @param[in] memoryPoolOffset  Offset to the memory pool where command memory is placed, in bytes.
* @param[in] memorySize  Size of the command memory to add, in bytes.
*
* @pre
*  - The command buffer is initialized.
*  - <tt><var>pMemoryPool</var></tt> != <tt>NULL</tt>.
*
* @post
*  - Command memory has been added.
*/
    void AddCommandMemory( TMemoryPool< Target >* pMemoryPool,
        ptrdiff_t memoryPoolOffset, size_t memorySize ) NN_NOEXCEPT
    {
        return Impl::AddCommandMemory( pMemoryPool, memoryPoolOffset, memorySize );
    }

/**
* @brief  Adds control memory.
*
* @param[in] pMemory  Pointer to the control memory to add.
* @param[in] memorySize  Size of the control memory to add, in bytes.
*
* @pre
*  - The command buffer is initialized.
*  - <tt><var>pMemory</var></tt> != <tt>NULL</tt>.
*
* @post
*  - Control memory has been added.
*/
    void AddControlMemory( void* pMemory, size_t memorySize ) NN_NOEXCEPT
    {
        return Impl::AddControlMemory( pMemory, memorySize );
    }

/**
* @brief  Sets a callback to receive the event when there is insufficient command memory.
*
* @param[in] pEventCallback  Pointer to a callback to receive the insufficient command memory event.
*
* @pre
*  - The command buffer is initialized.
*
* @post
*  - If <tt><var>pEventCallback</var></tt> != <tt>NULL</tt>, the callback to receive the insufficient command memory event has been set.
*  - If <tt><var>pEventCallback</var></tt> = <tt>NULL</tt>, the callback to receive the insufficient command memory event has not been set.
*/
    void SetOutOfCommandMemoryEventCallback( OutOfMemoryEventCallback pEventCallback ) NN_NOEXCEPT
    {
        return Impl::SetOutOfCommandMemoryEventCallback( pEventCallback );
    }

/**
* @brief  Sets a callback to receive the event when there is insufficient control memory.
*
* @param[in] pEventCallback  Pointer to a callback to receive the insufficient control memory event.
*
* @pre
*  - The command buffer is initialized.
*
* @post
*  - If <tt><var>pEventCallback</var></tt> != <tt>NULL</tt>, the callback to receive the insufficient control memory event has been set.
*  - If <tt><var>pEventCallback</var></tt> = <tt>NULL</tt>, the callback to receive the insufficient control memory event has not been set.
*/
    void SetOutOfControlMemoryEventCallback( OutOfMemoryEventCallback pEventCallback ) NN_NOEXCEPT
    {
        return Impl::SetOutOfControlMemoryEventCallback( pEventCallback );
    }

/**
* @brief  Restores command memory and control memory to their initial states.
*
* @post
*  - Command memory and control memory have been restored to their initial states.
*
* @details
*  Used for the low level graphics API that automatically allocates memory.
*  All previously issued commands must have completed execution by the GPU before calling this function.
*/
    void Reset() NN_NOEXCEPT
    {
        return Impl::Reset();
    }

/**
* @brief  Begins the process of adding commands to the command buffer.
*
* @pre
*  - The command buffer is initialized.
*  - Addition of commands has not begun.
*
* @post
*  - The process of adding commands has begun.
*/
    void Begin() NN_NOEXCEPT
    {
        return Impl::Begin();
    }

/**
* @brief  Ends the process of adding commands to the command buffer.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - Addition of commands has not begun.
*/
    void End() NN_NOEXCEPT
    {
        return Impl::End();
    }

/**
* @brief  Adds a command to dispatch a computational process.
*
* @param[in] groupCountX  The number of x-dimension groups.
* @param[in] groupCountY  The number of y-dimension groups.
* @param[in] groupCountZ  The number of z-dimension groups.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to dispatch a computational process has been added.
*
* @details
*  There are restrictions on the number of groups that can be specified. For more information, see the documentation for the low-level graphics API.
*
* @platformbegin{GX}
*  This function is not supported.
* @platformend
*/
    void Dispatch( int groupCountX, int groupCountY, int groupCountZ ) NN_NOEXCEPT
    {
        return Impl::Dispatch( groupCountX, groupCountY, groupCountZ );
    }

/**
* @brief  Adds a draw command.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] vertexCount  The number of vertices to draw.
* @param[in] vertexOffset  The offset to the starting vertex.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - Draw commands are being added.
*/
    void Draw( PrimitiveTopology primitiveTopology, int vertexCount, int vertexOffset ) NN_NOEXCEPT
    {
        return Impl::Draw( primitiveTopology, vertexCount, vertexOffset );
    }

/**
* @brief  Adds an instantiated draw command.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] vertexCountPerInstance  The number of vertices per instance being drawn.
* @param[in] vertexOffset  The offset to the starting vertex.
* @param[in] instanceCount  The number of instances to draw.
* @param[in] baseInstance  The starting instance.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - Instantiated draw commands are being added.
*/
    void Draw( PrimitiveTopology primitiveTopology, int vertexCountPerInstance,
        int vertexOffset, int instanceCount, int baseInstance ) NN_NOEXCEPT
    {
        return Impl::Draw( primitiveTopology, vertexCountPerInstance, vertexOffset,
            instanceCount, baseInstance );
    }

/**
* @brief  Adds an indexed draw command.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] indexFormat  The format of the index buffer.
* @param[in] indexBufferAddress  GPU address for the index buffer.
* @param[in] indexCount  The number of indexes to draw.
* @param[in] baseVertex  The base vertex to add to each index.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The indexed draw command has been added.
*/
    void DrawIndexed( PrimitiveTopology primitiveTopology, IndexFormat indexFormat,
        const GpuAddress& indexBufferAddress, int indexCount, int baseVertex ) NN_NOEXCEPT
    {
        return Impl::DrawIndexed( primitiveTopology, indexFormat, indexBufferAddress, indexCount, baseVertex );
    }

/**
* @brief  Adds an indexed, instantiated draw command.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] indexFormat  The format of the index buffer.
* @param[in] indexBufferAddress  GPU address for the index buffer.
* @param[in] indexCountPerInstance  The number of indexes per instance being rendered.
* @param[in] baseVertex  The base vertex to add to each index.
* @param[in] instanceCount  The number of instances to draw.
* @param[in] baseInstance  The starting instance.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - An indexed, instantiated draw command has been added.
*/
    void DrawIndexed( PrimitiveTopology primitiveTopology, IndexFormat indexFormat,
        const GpuAddress& indexBufferAddress, int indexCountPerInstance,
        int baseVertex, int instanceCount, int baseInstance ) NN_NOEXCEPT
    {
        return Impl::DrawIndexed( primitiveTopology, indexFormat, indexBufferAddress,
            indexCountPerInstance, baseVertex, instanceCount, baseInstance );
    }

/**
* @brief  Adds a command to dispatch a computational process that gets parameters from the buffer.
*
* @param[in] indirectBufferAddress  GPU address for the buffer storing the parameters.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - A command to dispatch a computational process that gets parameters from the buffer has been added.
*/
    void DispatchIndirect( const GpuAddress& indirectBufferAddress ) NN_NOEXCEPT
    {
        return Impl::DispatchIndirect( indirectBufferAddress );
    }

/**
* @brief  Adds an instantiated draw command that gets parameters from the buffer.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] indirectBufferAddress  GPU address for the buffer storing the parameters.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - An instantiated draw command that gets parameters from the buffer has been added.
*/
    void DrawIndirect( PrimitiveTopology primitiveTopology, const GpuAddress& indirectBufferAddress ) NN_NOEXCEPT
    {
        return Impl::DrawIndirect( primitiveTopology, indirectBufferAddress );
    }

/**
* @brief  Adds an indexed, instantiated draw command to get parameters from the buffer.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] indexFormat  The format of the index buffer.
* @param[in] indexBufferAddress  GPU address for the index buffer.
* @param[in] indirectBufferAddress  GPU address for the buffer storing the parameters.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - An indexed, instantiated draw command to get parameters from the buffer has been added.
*
* @details
*  In the GL version, <tt><var>indexBufferAddress</var></tt> must be the starting address obtained from <tt>Buffer</tt>.
*  Set the offset using the parameter in <tt><var>indirectBufferAddress</var></tt>.
*
*/
    void DrawIndexedIndirect( PrimitiveTopology primitiveTopology, IndexFormat indexFormat,
        const GpuAddress& indexBufferAddress, const GpuAddress& indirectBufferAddress ) NN_NOEXCEPT
    {
        return Impl::DrawIndexedIndirect( primitiveTopology, indexFormat, indexBufferAddress, indirectBufferAddress );
    }

/**
* @brief  Adds a render command that gets parameters and a render count from the buffer.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] indirectBufferAddress  GPU address for the buffer storing the parameters.
* @param[in] countBufferAddress  GPU address for the buffer storing the render count.
* @param[in] maxDrawCount  The maximum render count.
* @param[in] stride  The stride, in bytes, between each element in <tt><var>indirectBufferAddress</var></tt>.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - A render command that gets parameters and a render count from the buffer is added.
*/
    void MultiDrawIndirectCount( PrimitiveTopology primitiveTopology,
        const GpuAddress& indirectBufferAddress, const GpuAddress& countBufferAddress,
        int maxDrawCount, ptrdiff_t stride ) NN_NOEXCEPT
    {
        return Impl::MultiDrawIndirectCount( primitiveTopology,
            indirectBufferAddress, countBufferAddress, maxDrawCount, stride );
    }

/**
* @brief  Adds an indexed render command to get parameters and a render count from the buffer.
*
* @param[in] primitiveTopology  Primitive topology of the draw target.
* @param[in] indexFormat  The format of the index buffer.
* @param[in] indexBufferAddress  GPU address for the index buffer.
* @param[in] indirectBufferAddress  GPU address for the buffer storing the parameters.
* @param[in] countBufferAddress  GPU address for the buffer storing the render count.
* @param[in] maxDrawCount  The maximum render count.
* @param[in] stride  The stride, in bytes, between each element in <tt><var>indirectBufferAddress</var></tt>.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - An indexed instantiated render command to get parameters and a render count from the buffer has been added.
*
* @details
*  In the GL version, <tt><var>indexBufferAddress</var></tt> must be the starting address obtained from <tt>Buffer</tt>.
*  Set the offset using the parameter in <tt><var>indirectBufferAddress</var></tt>.
*
*/
    void MultiDrawIndexedIndirectCount( PrimitiveTopology primitiveTopology, IndexFormat indexFormat,
        const GpuAddress& indexBufferAddress, const GpuAddress& indirectBufferAddress,
        const GpuAddress& countBufferAddress, int maxDrawCount, ptrdiff_t stride ) NN_NOEXCEPT
    {
        return Impl::MultiDrawIndexedIndirectCount( primitiveTopology, indexFormat,
            indexBufferAddress, indirectBufferAddress, countBufferAddress, maxDrawCount, stride );
    }

/**
* @brief  Adds a command that sets a pipeline.
*
* @param[in] pPipeline  Pointer to the pipeline.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pPipeline</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pPipeline</var></tt> is initialized.
*
* @post
*  - The command to set the pipeline has been added.
*/
    void SetPipeline( const TPipeline< Target >* pPipeline ) NN_NOEXCEPT
    {
        return Impl::SetPipeline( pPipeline );
    }

/**
* @brief  Adds a command that sets render targets.
*
* @param[in] colorTargetCount  The number of color targets.
* @param[in] ppColorTargets  Pointer to the array of color target pointers.
* @param[in] pDepthStencil  Pointer to the depth stencil.
*
* @pre
*  - The process of adding commands has begun.
*  - For each of the <tt><var>colorTargetCount</var></tt> elements of <tt><var>ppColorTargets</var></tt>, the color target is initialized if the value is not <tt>NULL</tt>.
*  - <tt><var>pDepthStencil</var></tt> is initialized if <tt><var>pDepthStencil</var></tt> != <tt>NULL</tt>.
*
* @post
*  - The command to set render targets has been added.
*/
    void SetRenderTargets( int colorTargetCount, const TColorTargetView< Target >* const * ppColorTargets,
        const TDepthStencilView< Target >* pDepthStencil ) NN_NOEXCEPT
    {
        return Impl::SetRenderTargets( colorTargetCount, reinterpret_cast< const
            detail::ColorTargetViewImpl< Target >* const * >( ppColorTargets ), pDepthStencil );
    }

/**
* @brief  Adds a command that sets a vertex buffer.
*
* @param[in] bufferIndex  The index of the buffer to set.
* @param[in] vertexBufferAddress  GPU address for the vertex buffer.
* @param[in] stride  The per-vertex stride for the buffer.
* @param[in] size  Size of the vertex buffer.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to set the vertex buffer has been added.
*/
    void SetVertexBuffer( int bufferIndex, const GpuAddress& vertexBufferAddress,
        ptrdiff_t stride, size_t size ) NN_NOEXCEPT
    {
        return Impl::SetVertexBuffer( bufferIndex, vertexBufferAddress, stride, size );
    }

/**
* @brief  Add a command that sets a viewport scissor state.
*
* @param[in] pViewportScissorState  Pointer to the viewport scissor state.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pViewportScissorState</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pViewportScissorState</var></tt> is initialized.
*
* @post
*  - The command to set the viewport scissor state has been added.
*/
    void SetViewportScissorState( const TViewportScissorState< Target >* pViewportScissorState ) NN_NOEXCEPT
    {
        return Impl::SetViewportScissorState( pViewportScissorState );
    }

/**
* @brief  Adds a command to copy a buffer.
*
* @param[in] pDstBuffer  Pointer to the destination buffer being copied to.
* @param[in] dstOffset  The offset from the start of the destination buffer.
* @param[in] pSrcBuffer  Pointer to the source buffer being copied from.
* @param[in] srcOffset  The offset from the start of the source buffer.
* @param[in] size  The copy size, in bytes.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstBuffer</var></tt> is initialized.
*  - <tt><var>pSrcBuffer</var></tt> is initialized.
*
* @post
*  - A command to copy a buffer has been added.
*
* @details
*  The copy source and copy destination regions of memory cannot overlap.
*
*/
    void CopyBuffer( TBuffer< Target >* pDstBuffer, ptrdiff_t dstOffset,
        const TBuffer< Target >* pSrcBuffer, ptrdiff_t srcOffset, size_t size ) NN_NOEXCEPT
    {
        return Impl::CopyBuffer( pDstBuffer, dstOffset, pSrcBuffer, srcOffset, size );
    }

/**
* @brief  Adds a command that copies an image.
*
* @param[in] pDstTexture  Pointer to the texture being copied to.
* @param[in] dstSubresource  Reference to the parameter representing the particular image to copy to.
* @param[in] dstOffsetU  The u-coordinate offset of the copy destination.
* @param[in] dstOffsetV  The v-coordinate offset of the copy destination.
* @param[in] dstOffsetW  The w-coordinate offset of the copy destination.
* @param[in] pSrcTexture  Pointer to the texture being copied from.
* @param[in] srcCopyRegion  Reference to a parameter representing the destination region.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstTexture</var></tt> is initialized.
*  - <tt><var>pSrcTexture</var></tt> is initialized.
*
* @post
*  - The command to copy the image has been added.
*
* @details
*  The copy source and copy destination regions of memory cannot overlap.
*/
    void CopyImage( TTexture< Target >* pDstTexture, const TextureSubresource& dstSubresource,
        int dstOffsetU, int dstOffsetV, int dstOffsetW, const TTexture< Target >* pSrcTexture,
        const TextureCopyRegion& srcCopyRegion ) NN_NOEXCEPT
    {
        return Impl::CopyImage( pDstTexture, dstSubresource, dstOffsetU,
            dstOffsetV, dstOffsetW, pSrcTexture, srcCopyRegion );
    }

/**
* @brief  Adds a command to copy from a buffer to an image.
*
* @param[in] pDstTexture  Pointer to the texture being copied to.
* @param[in] pSrcBuffer  Pointer to the source buffer being copied from.
* @param[in] copyRegion  Reference to a parameter representing the destination region.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstTexture</var></tt> is initialized.
*  - <tt><var>pSrcBuffer</var></tt> is initialized.
*
* @post
*  - The command to copy from the buffer to the image has been added.
*/
    void CopyBufferToImage( TTexture< Target >* pDstTexture, const TBuffer< Target >* pSrcBuffer,
        const BufferTextureCopyRegion& copyRegion  ) NN_NOEXCEPT
    {
        return Impl::CopyBufferToImage( pDstTexture, pSrcBuffer, copyRegion );
    }

/**
* @brief  Adds a command to copy from an image to a buffer.
*
* @param[in] pDstBuffer  Pointer to the destination buffer being copied to.
* @param[in] pSrcTexture  Pointer to the texture being copied from.
* @param[in] copyRegion  Reference to a parameter representing the destination region.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstBuffer</var></tt> is initialized.
*  - <tt><var>pSrcTexture</var></tt> is initialized.
*
* @post
*  - The command to copy from the image to the buffer has been added.
*/
    void CopyImageToBuffer( TBuffer< Target >* pDstBuffer, const TTexture< Target >* pSrcTexture,
        const BufferTextureCopyRegion& copyRegion ) NN_NOEXCEPT
    {
        return Impl::CopyImageToBuffer( pDstBuffer, pSrcTexture, copyRegion );
    }

/**
* @brief  Adds a command to copy from a buffer to an image.
*
* @deprecated  Deprecated. Use the version with three parameters, <tt>CopyBufferToImage</tt>.
*
* @param[in] pDstTexture  Pointer to the texture being copied to.
* @param[in] dstRegion  Reference to a parameter representing the destination region.
* @param[in] pSrcBuffer  Pointer to the source buffer being copied from.
* @param[in] srcOffset  The offset from the start of the source buffer, in bytes.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstTexture</var></tt> is initialized.
*  - <tt><var>pSrcTexture</var></tt> is initialized.
*
* @post
*  - The command to copy from the buffer to the image has been added.
*/
    void CopyBufferToImage( TTexture< Target >* pDstTexture, const TextureCopyRegion& dstRegion,
        const TBuffer< Target >* pSrcBuffer, ptrdiff_t srcOffset ) NN_NOEXCEPT
    {
        return Impl::CopyBufferToImage( pDstTexture, dstRegion, pSrcBuffer, srcOffset );
    }

/**
* @brief  Adds a command to copy from an image to a buffer.
*
* @deprecated  Deprecated. Use the version with three parameters, <tt>CopyImageToBuffer</tt>.
*
* @param[in] pDstBuffer  Pointer to the destination buffer being copied to.
* @param[in] dstOffset  The offset from the start of the destination buffer, in bytes.
* @param[in] pSrcTexture  Pointer to the texture being copied from.
* @param[in] srcRegion  Reference to a parameter representing the destination region.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstTexture</var></tt> is initialized.
*  - <tt><var>pSrcTexture</var></tt> is initialized.
*
* @post
*  - The command to copy from the image to the buffer has been added.
*/
    void CopyImageToBuffer( TBuffer< Target >* pDstBuffer, ptrdiff_t dstOffset,
        const TTexture< Target >* pSrcTexture, const TextureCopyRegion& srcRegion ) NN_NOEXCEPT
    {
        return Impl::CopyImageToBuffer( pDstBuffer, dstOffset, pSrcTexture, srcRegion );
    }

/**
* @brief  Adds a command to copy a scaled image.
*
* @param[in] pDstTexture  Pointer to the texture being copied to.
* @param[in] dstRegion  The range to copy to.
* @param[in] pSrcTexture  Pointer to the texture being copied from.
* @param[in] srcRegion  The range to copy from.
* @param[in] copyFlags  Copy flags, represented by a combination of <tt>nn::gfx::ImageCopyFlag</tt> instances.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcTetxure</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstTexture</var></tt> is initialized.
*  - <tt><var>pSrcTexture</var></tt> is initialized.
*
* @post
*  - The command to copy the scaled image has been added.
*/
    void BlitImage( TTexture< Target >* pDstTexture, const TextureCopyRegion& dstRegion,
        const TTexture< Target >* pSrcTexture, const TextureCopyRegion& srcRegion, int copyFlags ) NN_NOEXCEPT
    {
        return Impl::BlitImage( pDstTexture, dstRegion, pSrcTexture, srcRegion, copyFlags );
    }

/**
* @brief  Adds a command to clear the buffer.
*
* @param[in] pBuffer  Pointer to the buffer to clear.
* @param[in] offset  The offset, in bytes, from the start of the buffer where clearing starts.
* @param[in] size  The size to clear, in bytes.
* @param[in] value  Value to clear.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>offset</var></tt> >= <tt>0</tt>.
*  - <tt><var>offset</var></tt> is a multiple of 4.
*  - <tt><var>size</var></tt> is a multiple of 4.
*
* @post
*  - The command to clear the buffer has been added.
*/
    void ClearBuffer( TBuffer< Target >* pBuffer, ptrdiff_t offset, size_t size, uint32_t value ) NN_NOEXCEPT
    {
        return Impl::ClearBuffer( pBuffer, offset, size, value );
    }

/**
* @brief  Adds a command that clears a color target.
*
* @param[in] pColorTarget  Pointer to the color target.
* @param[in] red  The red component of the color to clear.
* @param[in] green  The green component of the color to clear.
* @param[in] blue  The blue component of the color to clear.
* @param[in] alpha  The alpha component of the color to clear.
* @param[in] pArrayRange  Pointer to the array range to clear.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pColorTarget</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pColorTarget</var></tt> is initialized.
*
* @post
*  - The command to clear the color target has been added.
*
* @details
*  Only used to clear floating-point format.
*  Use <tt>nn::gfx::CommandBuffer::ClearColorTarget</tt> to clear signed integer or unsigned integer format.
*  Clears all of the array range specified by <tt><var>pArrayRange</var></tt>.
*  If <tt>NULL</tt> has been specified for <tt><var>pArrayRange</var></tt>, the entire array range is cleared.
*/
    void ClearColor( TColorTargetView< Target >* pColorTarget, float red, float green,
        float blue, float alpha, const TextureArrayRange* pArrayRange ) NN_NOEXCEPT
    {
        return Impl::ClearColor( pColorTarget, red, green, blue, alpha, pArrayRange );
    }

/**
* @brief  Adds a command that clears a color target.
*
* @param[in] pColorTarget  Pointer to the color target.
* @param[in] clearColor  The color to clear.
* @param[in] pArrayRange  Pointer to the array range to clear.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pColorTarget</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pColorTarget</var></tt> is initialized.
*
* @post
*  - The command to clear the color target has been added.
*
* @details
*  Clears all of the array range specified by <tt><var>pArrayRange</var></tt>.
*  If <tt>NULL</tt> has been specified for <tt><var>pArrayRange</var></tt>, the entire array range is cleared.
*/
    void ClearColorTarget( TColorTargetView< Target >* pColorTarget,
        const ClearColorValue& clearColor, const TextureArrayRange* pArrayRange ) NN_NOEXCEPT
    {
        return Impl::ClearColorTarget( pColorTarget, clearColor, pArrayRange );
    }

/**
* @brief  Adds a command that clears a depth stencil.
*
* @param[in] pDepthStencil  Pointer to the depth stencil.
* @param[in] depth  The depth value to clear.
* @param[in] stencil  The stencil value to clear to.
* @param[in] clearMode  The clear mode that defines whether to clear depth, stencil, or both.
* @param[in] pArrayRange  Pointer to the array range to clear.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDepthStencil</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDepthStencil</var></tt> is initialized.
*
* @post
*  - The command to clear the depth stencil has been added.
*
* @details
*  Clears all of the array range specified by <tt><var>pArrayRange</var></tt>.
*  If <tt>NULL</tt> has been specified for <tt><var>pArrayRange</var></tt>, the entire array range is cleared.
*/
    void ClearDepthStencil( TDepthStencilView< Target >* pDepthStencil, float depth,
        int stencil, DepthStencilClearMode clearMode, const TextureArrayRange* pArrayRange ) NN_NOEXCEPT
    {
        return Impl::ClearDepthStencil( pDepthStencil, depth, stencil, clearMode, pArrayRange );
    }

/**
* @brief  Resolves a multi-sample color target into a single sample texture.
*
* @param[in] pDstTexture  Pointer to the texture being resolved to.
* @param[in] dstMipLevel  The mipmap level for the texture being resolved to.
* @param[in] dstStartArrayIndex  The starting index of the texture array being resolved to.
* @param[in] pSrcColorTarget  Pointer to the source color target being resolved.
* @param[in] pSrcArrayRange  Pointer to the array range of source color target being resolved.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDstTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSrcColorTarget</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDstTexture</var></tt> is initialized.
*  - <tt><var>pSrcColorTarget</var></tt> is initialized.
*
* @post
*  - The command to resolve the multi-sample color target has been added.
*
* @details
*  Resolves the full array range specified by <tt><var>pSrcArrayRange</var></tt>, starting from <tt><var>dstStartArrayIndex</var></tt>.
*  If <tt><var>pSrcArrayRange</var></tt> is <tt>NULL</tt>, the entire array range is resolved.
*/
    void Resolve( TTexture< Target >* pDstTexture, int dstMipLevel, int dstStartArrayIndex,
        const TColorTargetView< Target >* pSrcColorTarget, const TextureArrayRange* pSrcArrayRange ) NN_NOEXCEPT
    {
        return Impl::Resolve( pDstTexture, dstMipLevel, dstStartArrayIndex, pSrcColorTarget, pSrcArrayRange );
    }

/**
* @brief  Flushes the GPU write cache in memory.
*
* @param[in] gpuAccessFlags  The memory accessed by the GPU that you want to flush, specified as a combination of <tt>nn::gfx::GpuAccess</tt> enumerators.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to flush the memory cache has been added.
*/
    void FlushMemory( int gpuAccessFlags ) NN_NOEXCEPT
    {
        return Impl::FlushMemory( gpuAccessFlags );
    }

/**
* @brief  Invalidates the GPU write cache in memory.
*
* @param[in] gpuAccessFlags  The memory accessed by the GPU that you want to invalidate, specified as a combination of <tt>nn::gfx::GpuAccess</tt> enumerators.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to invalidate the memory cache has been added.
*/
    void InvalidateMemory( int gpuAccessFlags ) NN_NOEXCEPT
    {
        return Impl::InvalidateMemory( gpuAccessFlags );
    }

/**
* @brief  Adds a command to call a different command buffer.
*
* @param[in] pNestedCommandBuffer  The nested command buffer.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pNestedCommandBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pNestedCommandBuffer</var></tt> is initialized.
*  - <tt><var>pNestedCommandBuffer</var></tt> has completed adding commands.
*  - <tt><var>pNestedCommandBuffer</var></tt> is a nested command buffer.
*
* @post
*  - A command to call a different command buffer has been added.
*/
    void CallCommandBuffer( const TCommandBuffer< Target >* pNestedCommandBuffer ) NN_NOEXCEPT
    {
        return Impl::CallCommandBuffer( pNestedCommandBuffer );
    }

/**
* @brief  Adds a command added to a different command buffer.
*
* @param[in] pNestedCommandBuffer  The nested command buffer.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pNestedCommandBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pNestedCommandBuffer</var></tt> is initialized.
*  - <tt><var>pNestedCommandBuffer</var></tt> has completed adding commands.
*  - <tt><var>pNestedCommandBuffer</var></tt> is a nested command buffer.
*
* @post
*  - The command added to a different command buffer has been added.
*/
    void CopyCommandBuffer( const TCommandBuffer< Target >* pNestedCommandBuffer ) NN_NOEXCEPT
    {
        return Impl::CopyCommandBuffer( pNestedCommandBuffer );
    }

/**
* @brief  Adds a command to transition the buffer state.
*
* @param[in] pBuffer  Pointer to the target buffer.
* @param[in] oldState  The previous buffer state, represented by a combination of <tt>nn::gfx::BufferState</tt> enumerators.
* @param[in] oldStageBits  The previous shader stage, represented by a combination of <tt>nn::gfx::PipelineStageBit</tt> instances.
* @param[in] newState  The buffer state to transition to, represented by a combination of <tt>nn::gfx::BufferState</tt> enumerators.
* @param[in] newStageBits  The post-transition shader stage, represented by a combination of <tt>nn::gfx::PipelineStageBit</tt> instances.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pBuffer</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pBuffer</var></tt> is initialized.
*
* @post
*  - The command to transition the buffer state has been added.
*/
    void SetBufferStateTransition( TBuffer< Target >* pBuffer, int oldState,
        int oldStageBits, int newState, int newStageBits ) NN_NOEXCEPT
    {
        return Impl::SetBufferStateTransition( pBuffer, oldState, oldStageBits, newState, newStageBits );
    }

/**
* @brief  Adds a command to transition the texture state.
*
* @param[in] pTexture  Pointer to the target texture.
* @param[in] pRange  Target subresource range.
* @param[in] oldState  The previous texture state, represented by a combination of <tt>nn::gfx::TextureState</tt> instances.
* @param[in] oldStageBits  The previous shader stage, represented by a combination of <tt>nn::gfx::PipelineStageBit</tt> instances.
* @param[in] newState  The texture state to transition to, represented by a combination of <tt>nn::gfx::TextureState instances</tt>.
* @param[in] newStageBits  The post-transition shader stage, represented by a combination of <tt>nn::gfx::PipelineStageBit</tt> instances.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pTexture</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pTexture</var></tt> is initialized.
*
* @post
*  - The command to transition the texture state has been added.
*
* @details
*  The entire range is targeted when <tt><var>pRange</var></tt> == <tt>NULL</tt>.
*/
    void SetTextureStateTransition( TTexture< Target >* pTexture, TextureSubresourceRange* pRange,
        int oldState, int oldStageBits, int newState, int newStageBits ) NN_NOEXCEPT
    {
        return Impl::SetTextureStateTransition( pTexture, pRange, oldState, oldStageBits, newState, newStageBits );
    }

/**
* @brief  Sets a descriptor pool.
*
* @param[in] pDescriptorPool  Pointer to the target descriptor pool.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The descriptor pool has been set.
*/
    void SetDescriptorPool( const TDescriptorPool< Target >* pDescriptorPool ) NN_NOEXCEPT
    {
        return Impl::SetDescriptorPool( pDescriptorPool );
    }

/**
* @brief  Adds a command to start a query.
*
* @param[in] target  The query target to start.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>target</var></tt> is not <tt>QueryTarget_Timestamp</tt>.
*
* @post
*  - The command to start a query has been added.
*/
    void BeginQuery( QueryTarget target ) NN_NOEXCEPT
    {
        return Impl::BeginQuery( target );
    }

/**
* @brief  Adds a command to end a query and write the results to a buffer.
*
* @param[in] dstBufferAddress  Address of the buffer into which to write results.
* @param[in] target  The query target to end.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>target</var></tt> is not <tt>QueryTarget_Timestamp</tt>.
*
* @post
*  - A command to end a query and write the results to a buffer has been added.
*
* @details
*  The written value and its format are dependent on the low-level graphics API in use.
*/
    void EndQuery( const GpuAddress& dstBufferAddress, QueryTarget target ) NN_NOEXCEPT
    {
        return Impl::EndQuery( dstBufferAddress, target );
    }

/**
* @brief  Sets the range for the depth bounds test.
*
* @param[in] minDepthBounds  The minimum range to use for the depth bounds test.
* @param[in] maxDepthBounds  The maximum range to use for the depth bounds test.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The range for the depth bounds test has been set.
*
* @details
*  If the depth bounds test is enabled in the depth stencil test that has been set,
*  this function must be called before subsequent draw calls.
*  If the depth bounds test is disabled in the depth stencil test that has been set,
*  this function does not need to be called until the next time it gets enabled.
*/
    void SetDepthBounds( float minDepthBounds, float maxDepthBounds ) NN_NOEXCEPT
    {
        return Impl::SetDepthBounds( minDepthBounds, maxDepthBounds );
    }

/**
* @brief  Sets the width of the line primitive.
*
* @param[in] lineWidth  Width of the line primitive in pixels.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The width of the line primitive is set.
*/
    void SetLineWidth( float lineWidth ) NN_NOEXCEPT
    {
        return Impl::SetLineWidth( lineWidth );
    }

/**
* @brief  Adds a command that sets a viewport.
*
* @param[in] firstViewport  Index of the first viewport to set.
* @param[in] viewportCount  The number of contiguous viewports to set.
* @param[in] pViewports  Pointer to an array of viewport information having <tt><var>viewportCount</var></tt> number of elements.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to set the viewport has been added.
*
* @details
*  Updates the viewports with indexes <tt><var>firstViewport</var></tt> through (<tt><var>firstViewport</var></tt> + <tt><var>viewportCount</var></tt> – <tt>1</tt>).
*  Updates the viewports with the indexes (<tt><var>firstViewport</var></tt> + <em>i</em>), where <em>i</em> is the <em>i</em>th element of the array indicated by <tt><var>pViewports</var></tt>.
*/
    void SetViewports( int firstViewport, int viewportCount,
        const ViewportStateInfo* pViewports ) NN_NOEXCEPT
    {
        return Impl::SetViewports( firstViewport, viewportCount, pViewports );
    }

/**
* @brief  Adds a command that sets a scissor.
*
* @param[in] firstScissor  Index of the first scissor to set.
* @param[in] scissorCount  The number of contiguous scissors to set.
* @param[in] pScissors  Pointer to a scissor data array having <tt><var>scissorCount</var></tt> number of elements.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to set a scissor has been added.
*
* @details
*  Updates scissors with indexes ranging from <tt><var>firstScissor</var></tt> to <tt><var>firstScissor</var></tt> + <tt><var>scissorCount</var></tt> – <tt>1</tt>.
*  Updates a scissor that is the <em>i</em>th element of the array indicated by <tt><var>pScissors</var></tt>, with an index equal to the sum of <tt><var>firstScissor</var></tt> and <em>i</em>.
*/
    void SetScissors( int firstScissor, int scissorCount,
        const ScissorStateInfo* pScissors ) NN_NOEXCEPT
    {
        return Impl::SetScissors( firstScissor, scissorCount, pScissors );
    }

/**
* @brief  Adds a command to write a timestamp value to a buffer.
*
* @param[in] dstBufferAddress  Address of the buffer into which to write results.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - A command to write a timestamp to a buffer has been added.
*
* @details
*  The written value and its format are dependent on the low-level graphics API in use.
*/
    void WriteTimestamp( const GpuAddress& dstBufferAddress ) NN_NOEXCEPT
    {
        return Impl::WriteTimestamp( dstBufferAddress );
    }

/**
* @brief  Updates the specified range of the specified buffer with a command.
*
* @param[in] dstBufferAddress  The address of the buffer to update.
* @param[in] bufferSize  The bound size, in bytes, of the buffer being updated.
* @param[in] dstOffset  The offset, in bytes, in the buffer where updating begins.
* @param[in] dataSize  The number of bytes of data to update.
* @param[in] pData  Pointer to the source data to update.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>dstOffset</var></tt> >= <tt>0</tt>.
*  - <tt><var>dstOffset</var></tt> + <tt><var>dataSize</var></tt> <= <tt><var>bufferSize</var></tt>.
*  - If <tt><var>dataSize</var></tt> > <tt>0</tt>, <tt><var>pData</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pData</var></tt> points to data that is at least <tt><var>dataSize</var></tt> in size.
*
* @post
*  - A command to update the buffer range with a command has been added.
*/
    void UpdateBuffer( const GpuAddress& dstBufferAddress, size_t bufferSize,
        ptrdiff_t dstOffset, size_t dataSize, const void* pData ) NN_NOEXCEPT
    {
        return Impl::UpdateBuffer( dstBufferAddress, bufferSize, dstOffset, dataSize, pData );
    }

/**
* @brief  Pushes a debug group onto the debug group stack for annotating a specific range for debugging.
*
* @param[in] description  Pointer to the annotation sentence string for the null-terminated debug group.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>description</var></tt> != <tt>NULL</tt>.
*
* @details
*  Annotates the range delineated by <tt>PushDebugGroup</tt> and <tt>PopDebugGroup</tt>.
*  Debug groups can be arranged into hierarchies. <tt>PushDebugGroup</tt> and <tt>PopDebugGroup</tt> do not need to be used in pairs.
*  However, you do need paired sets of <tt>PushDebugGroup</tt> and <tt>PopDebugGroup</tt> for the final submission to the queue.
*/
    void PushDebugGroup( const char* description ) NN_NOEXCEPT
    {
        return Impl::PushDebugGroup( description );
    }

/**
* @brief  Pops the currently active debug group from the debug group stack.
*
* @pre
*  - The process of adding commands has begun.
*
* @details
*  Annotates the range delineated by <tt>PushDebugGroup</tt> and <tt>PopDebugGroup</tt>.
*  Debug groups can be arranged into hierarchies. <tt>PushDebugGroup</tt> and <tt>PopDebugGroup</tt> do not need to be used in pairs.
*  However, you do need paired sets of <tt>PushDebugGroup</tt> and <tt>PopDebugGroup</tt> for the final submission to the queue.
*/
    void PopDebugGroup() NN_NOEXCEPT
    {
        return Impl::PopDebugGroup();
    }

    //! @name  Using a Descriptor Pool
    // @{

/**
* @brief  Adds a command to set a constant buffer.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] constantBufferDescriptor  Descriptor of the target constant buffer.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to set a constant buffer has been added.
*/
    void SetConstantBuffer( int slot, ShaderStage stage, const DescriptorSlot& constantBufferDescriptor ) NN_NOEXCEPT
    {
        return Impl::SetConstantBuffer( slot, stage, constantBufferDescriptor );
    }

/**
* @brief  Adds a command to set an unordered access buffer.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] unorderedAccessBufferDescriptor  Descriptor of the target unordered access buffer.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to set an unordered access buffer has been added.
*/
    void SetUnorderedAccessBuffer( int slot, ShaderStage stage, const DescriptorSlot& unorderedAccessBufferDescriptor ) NN_NOEXCEPT
    {
        return Impl::SetUnorderedAccessBuffer( slot, stage, unorderedAccessBufferDescriptor );
    }

/**
* @brief  Adds a command that sets a texture and a sampler.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] textureDescriptor  Descriptor of the target texture.
* @param[in] samplerDescriptor  Descriptor of the target sampler.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>slot</var></tt> >= <tt>0</tt>.
*
* @post
*  - The command to set a texture and sampler has been added.
*/
    void SetTextureAndSampler( int slot, ShaderStage stage,
        const DescriptorSlot& textureDescriptor, const DescriptorSlot& samplerDescriptor ) NN_NOEXCEPT
    {
        return Impl::SetTextureAndSampler( slot, stage, textureDescriptor, samplerDescriptor );
    }

/**
* @brief  Adds a command that sets a texture.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] textureDescriptor  Descriptor of the target texture.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>slot</var></tt> >= <tt>0</tt>.
*
* @post
*  - A command that sets a texture has been added.
*
* @details
*  Sets a texture independently rather than in combination with a sampler.
*  You can use this to set a texture using the GLSL shading language function <tt>texelFetch</tt>.
*  To set the texture together with a sampler, use <tt>SetTextureAndSampler</tt>.
*/
    void SetTexture( int slot, ShaderStage stage, const DescriptorSlot& textureDescriptor ) NN_NOEXCEPT
    {
        return Impl::SetTexture( slot, stage, textureDescriptor );
    }

/**
* @brief  Adds a command that sets an image.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] imageDescriptor  Descriptor for the target image.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>slot</var></tt> >= <tt>0</tt>.
*
* @post
*  - The command to set an image has been added.
*/
    void SetImage( int slot, ShaderStage stage, const DescriptorSlot& imageDescriptor ) NN_NOEXCEPT
    {
        return Impl::SetImage( slot, stage, imageDescriptor );
    }

    // @}

    //! @name  Cases Where a Descriptor Pool Is Not Used
    // @{

/**
* @brief  Adds a command that sets a texture and a sampler.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] pTextureView  Pointer to the texture view.
* @param[in] pSampler  Pointer to the sampler.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pTextureView</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pTextureView</var></tt> is initialized.
*  - <tt><var>pSampler</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pSampler</var></tt> is initialized.
*
* @post
*  - The command to set a texture and sampler has been added.
*
* @details
*  For <tt><var>slot</var></tt>, specify the number queried from the shader.
*/
    void SetTextureAndSampler( int slot, ShaderStage stage,
        const TTextureView< Target >* pTextureView,
        const TSampler< Target >* pSampler ) NN_NOEXCEPT
    {
        return Impl::SetTextureAndSampler( slot, stage, pTextureView, pSampler );
    }

/**
* @brief  Adds a command that sets an image.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] pImage  Pointer to the target image.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pImage</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pImage</var></tt> is initialized.
*
* @post
*  - The command to set an image has been added.
*
* @details
*  For <tt><var>slot</var></tt>, specify the number queried from the shader.
*/
    void SetImage( int slot, ShaderStage stage, const TTextureView< Target >* pImage ) NN_NOEXCEPT
    {
        return Impl::SetImage( slot, stage, pImage );
    }

/**
* @brief  Adds a command to set a constant buffer.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] constantBufferAddress  GPU address for the constant buffer.
* @param[in] size  Size of the constant buffer.
*
* @pre
*  - The process of adding commands has begun.
*
* @post
*  - The command to set a constant buffer has been added.
*
* @details
*  For <tt><var>slot</var></tt>, specify the number queried from the shader.
*/
    void SetConstantBuffer( int slot, ShaderStage stage,
        const GpuAddress& constantBufferAddress, size_t size ) NN_NOEXCEPT
    {
        return Impl::SetConstantBuffer( slot, stage, constantBufferAddress, size );
    }

/**
* @brief  Adds a command to set an unordered access buffer.
*
* @param[in] slot  The slot for the target being set.
* @param[in] stage  The shader stage for the target being set.
* @param[in] unorderedAccessBufferAddress  GPU address for the unordered access buffer.
* @param[in] size  Size of the unordered access buffer.
*
* @pre
*  - The process of adding commands has begun.

* @post
*  - The command to set an unordered access buffer has been added.
*
* @details
*  For <tt><var>slot</var></tt>, specify the number queried from the shader.
*/
    void SetUnorderedAccessBuffer( int slot, ShaderStage stage,
        const GpuAddress& unorderedAccessBufferAddress, size_t size ) NN_NOEXCEPT
    {
        return Impl::SetUnorderedAccessBuffer( slot, stage, unorderedAccessBufferAddress, size );
    }

    // @}

    //! @name  Not Using the Pipeline
    // @{

/**
* @brief  Adds a command that sets a shader.
*
* @param[in] pShader  Pointer to the shader.
* @param[in] stageBits  The shader stage to set, represented by a combination of <tt>nn::gfx::ShaderStageBit</tt> instances.
*
* @pre
*  - The process of adding commands has begun.
*  - If <tt><var>pShader</var></tt> != <tt>NULL</tt>, <tt><var>pShader</var></tt> is initialized.
*
* @post
*  - The command to set a shader has been added.
*
* @details
*  If <tt><var>pShader</var></tt> == <tt>NULL</tt> or the stage indicated by <tt><var>stageBits</var></tt> is not in <tt><var>pShader</var></tt>, the target stage is disabled.
*
* @platformbegin{GX}
*  The stage deactivation feature is not handled. Call the <tt>GX2SetShaderMode</tt> function of the GX2 API directly as required.
* @platformend
*/
    void SetShader( const TShader< Target >* pShader, int stageBits ) NN_NOEXCEPT
    {
        return Impl::SetShader( pShader, stageBits );
    }

/**
* @brief  Adds a command to set the rasterizer state.
*
* @param[in] pRasterizerState  Pointer to the rasterizer state.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pRasterizerState</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pRasterizerState</var></tt> is initialized.
*
* @post
*  - The command to set the rasterizer state has been added.
*/
    void SetRasterizerState( const TRasterizerState< Target >* pRasterizerState ) NN_NOEXCEPT
    {
        return Impl::SetRasterizerState( pRasterizerState );
    }

/**
* @brief  Adds a command that sets the blend state.
*
* @param[in] pBlendState  Pointer to the blend state.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pBlendState</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pBlendState</var></tt> is initialized.
*
* @post
*  - The command to set blend state has been added.
*/
    void SetBlendState( const TBlendState< Target >* pBlendState ) NN_NOEXCEPT
    {
        return Impl::SetBlendState( pBlendState );
    }

/**
* @brief  Adds a command that sets the depth stencil state.
*
* @param[in] pDepthStencilState  Pointer to the depth stencil state.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pDepthStencilState</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDepthStencilState</var></tt> is initialized.
*
* @post
*  - The command to set the depth stencil state has been added.
*/
    void SetDepthStencilState( const TDepthStencilState< Target >* pDepthStencilState ) NN_NOEXCEPT
    {
        return Impl::SetDepthStencilState( pDepthStencilState );
    }

/**
* @brief  Adds a command that sets the vertex state.
*
* @param[in] pVertexState  Pointer to the vertex state.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pVertexState</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pVertexState</var></tt> is initialized.
*
* @post
*  The command to set the vertex state has been added.
*/
    void SetVertexState( const TVertexState< Target >* pVertexState ) NN_NOEXCEPT
    {
        return Impl::SetVertexState( pVertexState );
    }

/**
* @brief  Adds a command to set the tessellation state.
*
* @param[in] pTessellationState  Pointer to the target tessellation state.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pTessellationState</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pTessellationState</var></tt> is initialized.
*
* @post
*  The command to set the tessellation state has been added.
*/
    void SetTessellationState( const TTessellationState< Target >* pTessellationState ) NN_NOEXCEPT
    {
        return Impl::SetTessellationState( pTessellationState );
    }

    // @}

/**
* @brief  Sets an optional user pointer.
*
* @param[in] value  The user pointer to set.
*
* @post
*  - The user pointer is set.
*/
    void SetUserPtr( void* value ) NN_NOEXCEPT
    {
        return SetUserPtrImpl( this, value );
    }

/**
* @brief  Gets the optional user pointer that has been set.
*
* @return  Returns the optional user pointer that has been set.
*/
    void* GetUserPtr() NN_NOEXCEPT
    {
        return GetUserPtrImpl( this );
    }

/**
* @brief  Gets the optional user pointer that has been set.
*
* @return  Returns the optional user pointer that has been set.
*/
    const void* GetUserPtr() const NN_NOEXCEPT
    {
        return GetUserPtrImpl( this );
    }

    //! @name  For the GL4 Version
    // @{

/**
* @brief  The type for a callback for user-defined commands. This type definition is specific to the GL4 version.
*/
    typedef void ( *Gl4UserCommandCallbackType )( const void* pParam );

/**
* @brief  Adds a user-defined command. This function is specific to the GL4 version.
*
* @param[in] pCallback  Pointer to the callback for the executing command.
* @param[in] pParam  Parameter for the executing callback command.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pCallback</var></tt> != <tt>NULL</tt>.
*
* @post
*  A user-defined command has been added.
*
* @details
*  Use this function when you want to directly call the GL API while executing commands.
*  This function can only be called with the GL4 version.
*/
    void Gl4SetUserCommand( Gl4UserCommandCallbackType pCallback, const void* pParam ) NN_NOEXCEPT
    {
        return Impl::Gl4SetUserCommand( pCallback, pParam );
    }

/**
* @brief  Adds a user-defined command and parameter. This function is specific to the GL4 version.
*
* @param[in] pCallback  Pointer to the callback for the executing command.
* @param[in] pParam  Pointer to the parameter.
* @param[in] paramSize  The size of the parameter.
*
* @pre
*  - The process of adding commands has begun.
*  - <tt><var>pCallback</var></tt> != <tt>NULL</tt>.
*
* @post
*  A user-defined command and parameter has been added.
*
* @details
*  Use this function when you want to directly call the GL API while executing commands.
*  This function can only be called with the GL4 version.
*  A parameter of size <tt><var>paramSize</var></tt> from the placed indicated by <tt><var>pParam</var></tt> is copied and added to command memory for use as the argument for a callback function.
*/
    void Gl4SetUserCommandDynamic( Gl4UserCommandCallbackType pCallback, const void* pParam, size_t paramSize ) NN_NOEXCEPT
    {
        return Impl::Gl4SetUserCommandDynamic( pCallback, pParam, paramSize );
    }

    // @}
};

}
}
