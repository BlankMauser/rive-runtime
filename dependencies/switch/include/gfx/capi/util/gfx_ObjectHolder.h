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
* @brief  For the classes available in <tt>nn::gfx</tt>, defines the wrapper class
*  that wraps the necessary memory as a member when additional memory is requested.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/util/util_BytePtr.h>
#include <nn/gfx.h>
#include <nn/gfx/util/detail/gfx_AlignedStorage.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/util/detail/gfx_ObjectHolder-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/util/detail/gfx_ObjectHolder-api.nvn.8.h>
#endif

#if defined ( NN_GFX_CONFIG_INCLUDE_VK1 )
#include <nn/gfx/util/detail/gfx_ObjectHolder-api.vk.1.h>
#endif

#if defined ( NN_GFX_CONFIG_INCLUDE_EX1 )
#include <nn/gfx/util/detail/gfx_ObjectHolder-api.ex.1.h>
#endif

NN_PRAGMA_PUSH_WARNINGS
NN_DISABLE_WARNING_DEPRECATED_DECLARATIONS

namespace nn {
namespace gfx {
namespace util {

/**
* @brief  A wrapper class that allocates the necessary additional memory as a member to <tt>nn::gfx::BlendState</tt>.
*  The necessary value is taken as a template parameter because the amount of memory to allocate is set statically.
*
* @tparam TBlendTargetCount  The number of blend targets. Specify a value that is equal to or greater than the blend target state information count specified in <tt>nn::gfx::BlendStateInfo::SetBlendTargetStateInfoArray()</tt>.
*/
template<int TBlendTargetCount>
class BlendStateHolder
{
    NN_DISALLOW_COPY(BlendStateHolder);

public:

/**
* @brief  Constructor.
*/
    BlendStateHolder() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the blend state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>info.GetBlendTargetCount()</var></tt> <= <tt>TBlendTargetCount</tt>
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The blend state is not initialized.
*
* @post
*  - The blend state is initialized.
*/
    void Initialize(nn::gfx::Device* pDevice, const nn::gfx::BlendState::InfoType& info) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( info.GetBlendTargetCount() <= TBlendTargetCount );

        NN_SDK_ASSERT( nn::gfx::BlendState::GetRequiredMemorySize(info) <= sizeof(m_Memory) );
        NN_SDK_ASSERT( nn::util::BytePtr(&m_Memory).IsAligned(nn::gfx::BlendState::RequiredMemoryInfo_Alignment) );

        m_Object.SetMemory(&m_Memory, nn::gfx::BlendState::GetRequiredMemorySize(info));
        m_Object.Initialize(pDevice, info);
    }

/**
* @brief  Finalizes the blend state.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The blend state is initialized.
*
* @post
*  - The blend state is not initialized.
*/
    void Finalize(nn::gfx::Device* pDevice) NN_NOEXCEPT
    {
        m_Object.Finalize(pDevice);
    }

/**
* @brief  Gets a blend state instance.
*
* @return  Returns a blend state instance.
*/
    nn::gfx::BlendState* Get() NN_NOEXCEPT
    {
        return &m_Object;
    }

/**
* @brief  Gets a blend state instance.
*
* @return  Returns a blend state instance.
*/
    const nn::gfx::BlendState* Get() const NN_NOEXCEPT
    {
        return &m_Object;
    }

private:
    typename nn::gfx::util::detail::AlignedStorage<
        detail::BlendStateHolderRequiredMemorySize<TBlendTargetCount>::Value,
        nn::gfx::BlendState::RequiredMemoryInfo_Alignment
    >::Type m_Memory;

    nn::gfx::BlendState m_Object;
};

/**
* @brief  A wrapper class that allocates the necessary additional memory as a member to <tt>nn::gfx::VertexState</tt>.
*  The necessary value is taken as a template parameter because the amount of memory to allocate is set statically.
*
* @tparam TVertexAttributeCount  The number of vertex attributes. Specify a value that is equal to or greater than the vertex attribute state information count specified in <tt>nn::gfx::VertexStateInfo::SetVertexAttributeStateInfoArray()</tt>.
* @tparam TVertexBufferCount  The number of vertex buffers. Specify a value that is equal to or greater than the vertex buffer state information count specified in <tt>nn::gfx::VertexStateInfo::SetVertexBufferStateInfoArray()</tt>.
*/
template<int TVertexAttributeCount, int TVertexBufferCount>
class VertexStateHolder
{
    NN_DISALLOW_COPY(VertexStateHolder);

public:

/**
* @brief  Constructor.
*/
    VertexStateHolder() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the vertex state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pVertexShader  Pointer to the target vertex shader of the vertex state.
*
* @pre
*  - <tt>info.GetVertexAttributeCount()</tt> <= <tt>TVertexAttributeCount</tt>.
*  - <tt>info.GetVertexBufferCount()</tt> <= <tt>TVertexBufferCount</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - If <tt><var>pVertexShader</var></tt> is not <tt>NULL</tt>, it is initialized.
*  - The vertex state is not initialized.
*
* @post
*  - The vertex state is initialized.
*
* @details
*  <tt><var>pVertexShader</var></tt> is bound by name if it is not <tt>NULL</tt>.
*/
    void Initialize(nn::gfx::Device* pDevice, const nn::gfx::VertexState::InfoType& info, const nn::gfx::Shader* pVertexShader = NULL) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( info.GetVertexAttributeCount() <= TVertexAttributeCount );
        NN_SDK_REQUIRES( info.GetVertexBufferCount() <= TVertexBufferCount );

        NN_SDK_ASSERT( nn::gfx::VertexState::GetRequiredMemorySize(info) <= sizeof(m_Memory) );
        NN_SDK_ASSERT( nn::util::BytePtr(&m_Memory).IsAligned(nn::gfx::VertexState::RequiredMemoryInfo_Alignment) );

        m_Object.SetMemory(&m_Memory, nn::gfx::VertexState::GetRequiredMemorySize(info));
        m_Object.Initialize(pDevice, info, pVertexShader);
    }

/**
* @brief  Finalizes the vertex state.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The vertex state is initialized.
*
* @post
*  - The vertex state is not initialized.
*/
    void Finalize(nn::gfx::Device* pDevice) NN_NOEXCEPT
    {
        m_Object.Finalize(pDevice);
    }

/**
* @brief  Gets a vertex state instance.
*
* @return  Returns a vertex state instance.
*/
    nn::gfx::VertexState* Get() NN_NOEXCEPT
    {
        return &m_Object;
    }

/**
* @brief  Gets a vertex state instance.
*
* @return  Returns a vertex state instance.
*/
    const nn::gfx::VertexState* Get() const NN_NOEXCEPT
    {
        return &m_Object;
    }

private:
    typename nn::gfx::util::detail::AlignedStorage<
        detail::VertexStateHolderRequiredMemorySize<TVertexAttributeCount, TVertexBufferCount>::Value,
        nn::gfx::VertexState::RequiredMemoryInfo_Alignment
    >::Type m_Memory;

    nn::gfx::VertexState m_Object;
};

/**
* @brief  A wrapper class that allocates the necessary additional memory as a member to <tt>nn::gfx::ViewportScissorState</tt>.
*
* @tparam TViewportCount  The number of viewports. Specify a value that is equal to or greater than the viewport state information count specified in <tt>nn::gfx::ViewportScissorState::SetViewportStateInfoArray()</tt>.
*/
template<int TViewportCount>
class ViewportScissorStateHolder
{
    NN_DISALLOW_COPY(ViewportScissorStateHolder);

public:

/**
* @brief  Constructor.
*/
    ViewportScissorStateHolder() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the viewport scissor state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>info</var>.GetViewportCount()</tt> <= <tt>TViewportCount</tt>.
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The viewport scissor state is not initialized.
*
* @post
*  - The viewport scissor state is initialized.
*/
    void Initialize(nn::gfx::Device* pDevice, const nn::gfx::ViewportScissorState::InfoType& info) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( info.GetViewportCount() <= TViewportCount );

        NN_SDK_ASSERT( nn::gfx::ViewportScissorState::GetRequiredMemorySize(info) <= sizeof(m_Memory) );
        NN_SDK_ASSERT( nn::util::BytePtr(&m_Memory).IsAligned(nn::gfx::ViewportScissorState::RequiredMemoryInfo_Alignment) );

        m_Object.SetMemory(&m_Memory, nn::gfx::ViewportScissorState::GetRequiredMemorySize(info));
        m_Object.Initialize(pDevice, info);
    }

/**
* @brief  Finalizes the viewport scissor state.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The viewport scissor state is initialized.
*
* @post
*  - The viewport scissor state is not initialized.
*/
    void Finalize(nn::gfx::Device* pDevice) NN_NOEXCEPT
    {
        m_Object.Finalize(pDevice);
    }

/**
* @brief  Gets a viewport scissor state instance.
*
* @return  Returns a viewport scissor state instance.
*/
    nn::gfx::ViewportScissorState* Get() NN_NOEXCEPT
    {
        return &m_Object;
    }

/**
* @brief  Gets a viewport scissor state instance.
*
* @return  Returns a viewport scissor state instance.
*/
    const nn::gfx::ViewportScissorState* Get() const NN_NOEXCEPT
    {
        return &m_Object;
    }

private:
    typename nn::gfx::util::detail::AlignedStorage<
        detail::ViewportScissorStateHolderRequiredMemorySize<TViewportCount>::Value,
        nn::gfx::ViewportScissorState::RequiredMemoryInfo_Alignment
    >::Type m_Memory;

    nn::gfx::ViewportScissorState m_Object;
};

/**
* @brief  A wrapper class that allocates the necessary additional memory as a member when using <tt>nn::gfx::Pipeline</tt> as a graphics pipeline.
*  The necessary value is taken as a template parameter because the amount of memory to allocate is set statically.
*
* @tparam TBlendTargetCount  The number of blend targets. for the <tt>nn::gfx:: :: BlendStateInfo</tt> that is passed to <tt>nn::gfx:: :: GraphicsPipelineInfo::SetBlendStateInfo()</tt>,
*  Specify a value that is equal to or greater than the blend target state information count specified in <tt>nn::gfx::BlendStateInfo::SetBlendTargetStateInfoArray()</tt>.
* @tparam TVertexAttributeCount  The number of vertex attributes. For the <tt>nn::gfx::VertexStateInfo</tt> that is passed to <tt>nn::gfx::GraphicsPipelineInfo::SetVertexStateInfo()</tt>,
*  Specify a value that is equal to or greater than the vertex attribute state information count specified in <tt>nn::gfx::VertexStateInfo::SetVertexAttributeStateInfoArray()</tt>.
* @tparam TVertexBufferCount  The number of vertex buffers. For the <tt>nn::gfx::VertexStateInfo</tt> that is passed to <tt>nn::gfx::GraphicsPipelineInfo::SetVertexStateInfo()</tt>,
*  Specify a value that is equal to or greater than the vertex buffer state information count specified in <tt>nn::gfx::VertexStateInfo::SetVertexBufferStateInfoArray()</tt>.
*/
template<int TBlendTargetCount, int TVertexAttributeCount, int TVertexBufferCount>
class GraphicsPipelineHolder
{
    NN_DISALLOW_COPY(GraphicsPipelineHolder);

public:

/**
* @brief  Constructor.
*/
    GraphicsPipelineHolder() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the graphics pipeline.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>info</var>.GetBlendStateInfo()->GetBlendTargetCount()</tt> <= <tt>TBlendTargetCount</tt>.
*  - <tt><var>info</var>.GetVertexStateInfo()->GetVertexAttributeCount()</tt> <= <tt>TVertexAttributeCount</tt>.
*  - <tt><var>info</var>.GetVertexStateInfo()->GetVertexBufferCount()</tt> <= <tt>TVertexBufferCount</tt>
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The pipeline is not initialized.
*
* @post
*  - The pipeline has been initialized as a graphics pipeline.
*/
    void Initialize(nn::gfx::Device* pDevice, const nn::gfx::Pipeline::GraphicsInfoType& info) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( info.GetBlendStateInfo()->GetBlendTargetCount() <= TBlendTargetCount );
        NN_SDK_REQUIRES( info.GetVertexStateInfo()->GetVertexAttributeCount() <= TVertexAttributeCount );
        NN_SDK_REQUIRES( info.GetVertexStateInfo()->GetVertexBufferCount() <= TVertexBufferCount );

        NN_SDK_ASSERT( nn::gfx::Pipeline::GetRequiredMemorySize(info) <= sizeof(m_Memory) );
        NN_SDK_ASSERT( nn::util::BytePtr(&m_Memory).IsAligned(nn::gfx::Pipeline::RequiredMemoryInfo_Alignment) );

        m_Object.SetMemory(&m_Memory, nn::gfx::Pipeline::GetRequiredMemorySize(info));
        m_Object.Initialize(pDevice, info);
    }

/**
* @brief  Finalizes the pipeline.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The pipeline is initialized.
*
* @post
*  - The pipeline is not initialized.
*/    void Finalize(nn::gfx::Device* pDevice) NN_NOEXCEPT
    {
        m_Object.Finalize(pDevice);
    }

/**
* @brief  Gets a pipeline instance.
*
* @return  Returns a pipeline instance.
*/
    nn::gfx::Pipeline* Get() NN_NOEXCEPT
    {
        return &m_Object;
    }

/**
* @brief  Gets a pipeline instance.
*
* @return  Returns a pipeline instance.
*/
    const nn::gfx::Pipeline* Get() const NN_NOEXCEPT
    {
        return &m_Object;
    }

private:
    typename nn::gfx::util::detail::AlignedStorage<
        detail::GraphicsPipelineHolderRequiredMemorySize<
            TBlendTargetCount,
            TVertexAttributeCount,
            TVertexBufferCount
        >::Value,
        nn::gfx::Pipeline::RequiredMemoryInfo_Alignment
    >::Type m_Memory;

    nn::gfx::Pipeline m_Object;
};

/**
* @brief  A wrapper class that allocates the necessary additional memory as a member when using <tt>nn::gfx::Pipeline</tt> as a compute pipeline.
*
*/
class ComputePipelineHolder
{
    NN_DISALLOW_COPY(ComputePipelineHolder);

public:

/**
* @brief  Constructor.
*/
    ComputePipelineHolder() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the compute pipeline.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The pipeline is not initialized.
*
* @post
*  - The pipeline has been initialized as a compute pipeline.
*/
    void Initialize(nn::gfx::Device* pDevice, const nn::gfx::Pipeline::ComputeInfoType& info) NN_NOEXCEPT
    {
        m_Object.SetMemory(&m_Memory, nn::gfx::Pipeline::GetRequiredMemorySize(info));
        m_Object.Initialize(pDevice, info);
    }

/**
* @brief  Finalizes the pipeline.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The pipeline is initialized.
*
* @post
*  - The pipeline is not initialized.
*/
    void Finalize(nn::gfx::Device* pDevice) NN_NOEXCEPT
    {
        m_Object.Finalize(pDevice);
    }

/**
* @brief  Gets a pipeline instance.
*
* @return  Returns a pipeline instance.
*/
    nn::gfx::Pipeline* Get() NN_NOEXCEPT
    {
        return &m_Object;
    }

/**
* @brief  Gets a pipeline instance.
*
* @return  Returns a pipeline instance.
*/
    const nn::gfx::Pipeline* Get() const NN_NOEXCEPT
    {
        return &m_Object;
    }

private:
    nn::gfx::util::detail::AlignedStorage<
        detail::ComputePipelineHolderRequiredMemorySize::Value,
        nn::gfx::Pipeline::RequiredMemoryInfo_Alignment
    >::Type m_Memory;

    nn::gfx::Pipeline m_Object;
};

}
}
}

NN_PRAGMA_POP_WARNINGS
