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
* @brief  Declarations for API resources related to states.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_StateInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_RequiredMemory.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_State-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_State-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_State-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_State-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_State-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_State-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a rasterizer state.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TRasterizerState
    : public detail::RasterizerStateImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TRasterizerState );

    typedef detail::RasterizerStateImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the rasterizer state.
*/
    typedef RasterizerStateInfo InfoType;

/**
* @brief  Constructor.
*/
    TRasterizerState() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the rasterizer state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The rasterizer state is not initialized.
*
* @post
*  - The rasterizer state is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Finalizes the rasterizer state.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The rasterizer state is initialized.
*
* @post
*  - The rasterizer state is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

/**
* @brief  Graphics abstraction layer representing a blend state.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TBlendState
    : public detail::BlendStateImpl< typename detail::TargetVariation< TTarget >::Type >
    , private detail::RequiredMemory< detail::BlendStateImpl<
        typename detail::TargetVariation< TTarget >::Type > >
{
    NN_DISALLOW_COPY( TBlendState );

    typedef detail::BlendStateImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the blend state.
*/
    typedef BlendStateInfo InfoType;

/**
* @brief  Required memory information.
*/
    enum RequiredMemoryInfo
    {
        RequiredMemoryInfo_Alignment = detail::RequiredMemory< Impl >::MemoryInfoImpl::RequiredMemoryInfo_Alignment //!<  The required alignment. Alignment is not required if set to <tt>1</tt>.
    };

/**
* @brief  Gets the size of the memory that is required.
*
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the size of the memory that is required, in bytes.
*/
    static size_t GetRequiredMemorySize( const InfoType& info ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetRequiredMemorySize( info );
    }

/**
* @brief  Constructor.
*/
    TBlendState() NN_NOEXCEPT
    {
    }

/**
* @brief  Sets the required memory.
*
* @param[in] pMemory  Pointer to the memory to set.
* @param[in] size  Size of the memory to set, in bytes.
*
* @pre
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, it is aligned to <tt>RequiredMemoryInfo_Alignment</tt>.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, <tt><var>size</var></tt> == <tt>0</tt>.
*
* @post
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, the required memory is set.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, the required memory is not set.
*/
    void SetMemory( void* pMemory, size_t size ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::SetMemory( pMemory, size );
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    void* GetMemory() NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    const void* GetMemory() const NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Initializes the blend state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The blend state is not initialized.
*  - If the value returned by <tt>GetRequiredMemorySize</tt> with the same <tt><var>info</var></tt> argument is larger than <tt>0</tt>, the required memory is set to that size or greater.
*
* @post
*  - The blend state is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
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
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

/**
* @brief  Graphics abstraction layer representing a depth stencil state.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TDepthStencilState
    : public detail::DepthStencilStateImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TDepthStencilState );

    typedef detail::DepthStencilStateImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the depth stencil state.
*/
    typedef DepthStencilStateInfo InfoType;

/**
* @brief  Constructor.
*/
    TDepthStencilState() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the depth stencil state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The depth stencil state is not initialized.
*
* @post
*  - The depth stencil state is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Finalizes the depth stencil state.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The depth stencil state is initialized.
*
* @post
*  - The depth stencil state is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

/**
* @brief  Graphics abstraction layer representing a vertex state.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TVertexState
    : public detail::VertexStateImpl< typename detail::TargetVariation< TTarget >::Type >
    , private detail::RequiredMemory< detail::VertexStateImpl<
        typename detail::TargetVariation< TTarget >::Type > >
{
    NN_DISALLOW_COPY( TVertexState );

    typedef detail::VertexStateImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the vertex state.
*/
    typedef VertexStateInfo InfoType;

/**
* @brief  Required memory information.
*/
    enum RequiredMemoryInfo
    {
        RequiredMemoryInfo_Alignment = detail::RequiredMemory< Impl >::MemoryInfoImpl::RequiredMemoryInfo_Alignment //!<  The required alignment. Alignment is not required if set to <tt>1</tt>.
    };

/**
* @brief  Gets the size of the memory that is required.
*
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the size of the memory that is required, in bytes.
*/
    static size_t GetRequiredMemorySize( const InfoType& info ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetRequiredMemorySize( info );
    }

/**
* @brief  Constructor.
*/
    TVertexState() NN_NOEXCEPT
    {
    }

/**
* @brief  Sets the required memory.
*
* @param[in] pMemory  Pointer to the memory to set.
* @param[in] size  Size of the memory to set, in bytes.
*
* @pre
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, it is aligned to <tt>RequiredMemoryInfo_Alignment</tt>.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, <tt><var>size</var></tt> == <tt>0</tt>.
*
* @post
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, the required memory is set.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, the required memory is not set.
*/
    void SetMemory( void* pMemory, size_t size ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::SetMemory( pMemory, size );
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    void* GetMemory() NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    const void* GetMemory() const NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Initializes the vertex state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
* @param[in] pVertexShader  Pointer to the target vertex shader of the vertex state.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - If <tt><var>pVertexShader</var></tt> is not <tt>NULL</tt>, it is initialized.
*  - The vertex state is not initialized.
*  - If the value returned by <tt>GetRequiredMemorySize</tt> with the same <tt><var>info</var></tt> argument is larger than <tt>0</tt>, the required memory is set to that size or greater.
*
* @post
*  - The vertex state is initialized.
*
* @details
*  <tt><var>pVertexShader</var></tt> is bound by name if it is not <tt>NULL</tt>.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info,
        const TShader< Target >* pVertexShader = NULL ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info, pVertexShader );
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
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

/**
* @brief  Graphics abstraction layer representing a tessellation state.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TTessellationState
    : public detail::TessellationStateImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TTessellationState );

    typedef detail::TessellationStateImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the tessellation state.
*/
    typedef TessellationStateInfo InfoType;

/**
* @brief  Constructor.
*/
    TTessellationState() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the tessellation state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The tessellation state is not initialized.
*
* @post
*  - The tessellation state is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Destroys the tessellation state.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The tessellation state is initialized.
*
* @post
*  - The tessellation state is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

/**
* @brief  Graphics abstraction layer representing a viewport scissor state.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TViewportScissorState
    : public detail::ViewportScissorStateImpl< typename detail::TargetVariation< TTarget >::Type >
    , private detail::RequiredMemory< detail::ViewportScissorStateImpl<
        typename detail::TargetVariation< TTarget >::Type > >
{
    NN_DISALLOW_COPY( TViewportScissorState );

    typedef detail::ViewportScissorStateImpl<
        typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the viewport scissor state.
*/
    typedef ViewportScissorStateInfo InfoType;

/**
* @brief  Required memory information.
*/
    enum RequiredMemoryInfo
    {
        RequiredMemoryInfo_Alignment = detail::RequiredMemory< Impl >::MemoryInfoImpl::RequiredMemoryInfo_Alignment //!<  The required alignment. Alignment is not required if set to <tt>1</tt>.
    };

/**
* @brief  Gets the size of the memory that is required.
*
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the size of the memory that is required, in bytes.
*
* @details
*  When there is only one viewport, there is no memory required and the function returns <tt>0</tt>.
*/
    static size_t GetRequiredMemorySize( const InfoType& info ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetRequiredMemorySize( info );
    }

/**
* @brief  Constructor.
*/
    TViewportScissorState() NN_NOEXCEPT
    {
    }

/**
* @brief  Sets the required memory.
*
* @param[in] pMemory  Pointer to the memory to set.
* @param[in] size  Size of the memory to set, in bytes.
*
* @pre
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, it is aligned to <tt>RequiredMemoryInfo_Alignment</tt>.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, <tt><var>size</var></tt> == <tt>0</tt>.
*
* @post
*  - If <tt><var>pMemory</var></tt> is not <tt>NULL</tt>, the required memory is set.
*  - If <tt><var>pMemory</var></tt> is <tt>NULL</tt>, the required memory is not set.
*/
    void SetMemory( void* pMemory, size_t size ) NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::SetMemory( pMemory, size );
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    void* GetMemory() NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Gets the required memory that is set.
*
* @return  Returns a pointer to the memory when that required memory is set; otherwise, returns <tt>NULL</tt>.
*/
    const void* GetMemory() const NN_NOEXCEPT
    {
        return detail::RequiredMemory< Impl >::MemoryFuncImpl::GetMemory();
    }

/**
* @brief  Initializes the viewport scissor state.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The viewport scissor state is not initialized.
*  - If the value returned by <tt>GetRequiredMemorySize</tt> with the same <tt><var>info</var></tt> argument is larger than <tt>0</tt>, the required memory is set to that size or greater.
*
* @post
*  - The viewport scissor state is initialized.
*/
    void Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
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
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }
};

}
}
