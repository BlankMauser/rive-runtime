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
* @brief  Declarations of API resources for pipeline initialization information.
*/

#pragma once

#include <nn/gfx/gfx_DataAccessorConverter.h>
#include <nn/gfx/gfx_PipelineInfoData.h>
#include <nn/gfx/gfx_ShaderInfo.h>
#include <nn/gfx/gfx_StateInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  The class representing the information for initializing a graphics pipeline.
*/
class GraphicsPipelineInfo
    : public detail::DataContainer< GraphicsPipelineInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - Each parameter is initialized to zero.
*/
    GraphicsPipelineInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  Helper function to set each parameter to the default value.
    *
* @post
    * - Each parameter is set.
    *
* @details
    * Equivalent to calling the following.
    * - SetRasterizerStateInfo( NULL );
    * - SetBlendStateInfo( NULL );
    * - SetDepthStencilStateInfo( NULL );
    * - SetRenderTargetStateInfo( NULL );
    * - SetVertexStateInfo( NULL );
    * - SetRenderTargetStateInfo( NULL );
    * - SetShaderPtr( NULL );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the rasterizer state information.
    *
* @param[in] value  Pointer to the rasterizer state information.
    *
* @post
    * - The rasterizer state information is set.
    *
* @details
    * The content being pointed to can be destroyed after the object is initialized.
*/
    void SetRasterizerStateInfo( const RasterizerStateInfo* value ) NN_NOEXCEPT
    {
        this->pRasterizerState.ptr = nn::gfx::AccessorToData( value );
    }

/**
* @brief  Sets blend state information.
    *
* @param[in] value  Pointer to the blend state information.
    *
* @post
    * - The blend state information is set.
    *
* @details
    * The content being pointed to can be destroyed after the object is initialized.
*/
    void SetBlendStateInfo( const BlendStateInfo* value ) NN_NOEXCEPT
    {
        this->pBlendState.ptr = nn::gfx::AccessorToData( value );
    }

/**
* @brief  Sets the depth stencil state information.
    *
* @param[in] value  Pointer to the stencil state information.
    *
* @post
    * - The depth stencil state information is set.
    *
* @details
    * The content being pointed to can be destroyed after the object is initialized.
*/
    void SetDepthStencilStateInfo( const DepthStencilStateInfo* value ) NN_NOEXCEPT
    {
        this->pDepthStencilState.ptr = nn::gfx::AccessorToData( value );
    }

/**
* @brief  Sets render target state information.
    *
* @param[in] value  Pointer to the render target state information.
    *
* @post
    * - The render target state information is set.
    *
* @details
    * The content being pointed to can be destroyed after the object is initialized.
*/
    void SetRenderTargetStateInfo( const RenderTargetStateInfo* value ) NN_NOEXCEPT
    {
        this->pRenderTargetState.ptr = nn::gfx::AccessorToData( value );
    }

/**
* @brief  Sets vertex state information.
    *
* @param[in] value  Pointer to the vertex target state information.
    *
* @post
    * - The vertex state information is set.
    *
* @details
    * The content being pointed to can be destroyed after the object is initialized.
*/
    void SetVertexStateInfo( const VertexStateInfo* value ) NN_NOEXCEPT
    {
        this->pVertexState.ptr = nn::gfx::AccessorToData( value );
    }

/**
* @brief  Configures the tessellation state data.
    *
* @param[in] value  Pointer to the tessellation state data.
    *
* @post
    * - The tessellation state data is set.
    *
* @details
    * The content being pointed to can be destroyed after the object is initialized.
*/
    void SetTessellationStateInfo( const TessellationStateInfo* value ) NN_NOEXCEPT
    {
        this->pTessellationState.ptr = nn::gfx::AccessorToData( value );
    }

/**
* @brief  Sets a pointer to the shader.
    *
* @tparam TTarget  The low-level graphics API for the shader.
    *
* @param[in] value  Pointer to the shader.
    *
* @post
    * - The pointer to the shader is set.
    *
* @details
*  <tt><var>TTarget</var></tt> must be the same as <tt><var>TTarget</var></tt> for the pipeline you intend to initialize.
*/
    template< typename TTarget >
    void SetShaderPtr( const TShader< TTarget >* value ) NN_NOEXCEPT
    {
        this->pShader = value;
    }

/**
* @brief  Sets a pointer to the shader.
    *
* @param[in] value  Pointer to the vertex shader.
    *
* @post
    * - The pointer to the shader is set.
    *
* @details
*  If you are setting any value other than <tt>NULL</tt>, call the version with a template argument.
*/
    void SetShaderPtr( const void* value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value == NULL );
        this->pShader = value;
    }

/**
* @brief  Gets the rasterizer state information.
    *
* @return  Returns a pointer to the rasterizer state information.
*/
    const RasterizerStateInfo* GetRasterizerStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pRasterizerState.ptr );
    }

/**
* @brief  Gets the blend state information.
    *
* @return  Returns a pointer to the blend state information.
*/
    const BlendStateInfo* GetBlendStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pBlendState.ptr );
    }

/**
* @brief  Gets the depth stencil state information.
    *
* @return  Returns a pointer to the depth stencil state information.
*/
    const DepthStencilStateInfo* GetDepthStencilStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pDepthStencilState.ptr );
    }

/**
* @brief  Gets the render target state information.
    *
* @return  Returns a pointer to the render target state information.
*/
    const RenderTargetStateInfo* GetRenderTargetStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pRenderTargetState.ptr );
    }

/**
* @brief  Gets the vertex state information.
    *
* @return  Returns a pointer to the vertex state information.
*/
    const VertexStateInfo* GetVertexStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pVertexState.ptr );
    }

/**
* @brief  Gets the tessellation state data.
    *
* @return  Returns a pointer to the tessellation state data.
*/
    const TessellationStateInfo* GetTessellationStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pTessellationState.ptr );
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a pointer to the shader.
    *
* @return  Returns the pointer to the shader.
    *
* @details
    * Assign a <tt>nn::gfx::Shader</tt>-type pointer for the return value of this function.
*/
    const Shader* GetShaderPtr() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetShaderPtr() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( pShader.ptr );
    }
#endif
};

/**
* @brief  The class representing the information for initializing a compute pipeline.
*/
class ComputePipelineInfo
    : public detail::DataContainer< ComputePipelineInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - Each parameter is initialized to zero.
*/
    ComputePipelineInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  Helper function to set each parameter to the default value.
    *
* @post
    * - Each parameter is set.
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets a pointer to the shader.
    *
* @tparam TTarget  The low-level graphics API for the shader.
    *
* @param[in] value  Pointer to the vertex shader.
    *
* @post
    * - The pointer to the shader is set.
    *
* @details
*  <tt><var>TTarget</var></tt> must be the same as <tt><var>TTarget</var></tt> for the pipeline you intend to initialize.
*/
    template< typename TTarget >
    void SetShaderPtr( const TShader< TTarget >* value ) NN_NOEXCEPT
    {
        this->pShader = value;
    }

/**
* @brief  Sets a pointer to the shader.
    *
* @param[in] value  Pointer to the vertex shader.
    *
* @post
    * - The pointer to the shader is set.
    *
* @details
*  If you are setting any value other than <tt>NULL</tt>, call the version with a template argument.
*/
    void SetShaderPtr( const void* value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value == NULL );
        this->pShader = value;
    }

#if defined( NN_BUILD_FOR_DOCUMENT_GENERATION )
/**
* @brief  Gets a pointer to the shader.
    *
* @return  Returns the pointer to the shader.
    *
* @details
    * Assign a <tt>nn::gfx::Shader</tt>-type pointer for the return value of this function.
*/
    const Shader* GetShaderPtr() const NN_NOEXCEPT;
#else
    detail::Caster< const void > GetShaderPtr() const NN_NOEXCEPT
    {
        return detail::Caster< const void >( pShader.ptr );
    }
#endif
};

}
}
