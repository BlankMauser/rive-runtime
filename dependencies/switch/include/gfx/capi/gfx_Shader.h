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
* @brief  Declarations of API resources for shaders.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_ShaderInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_Shader-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_Shader-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_Shader-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_Shader-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_Shader-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing a shader.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TShader
    : public detail::ShaderImpl< typename detail::TargetVariation< TTarget >::Type >
{
    NN_DISALLOW_COPY( TShader );

    typedef detail::ShaderImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing the shader.
*/
    typedef ShaderInfo InfoType;

/**
* @brief  Gets the alignment required for the binary code.
*
* @param[in] pDevice  Pointer to the device.
*
* @return  Returns the alignment required for the binary code.
*/
    static size_t GetBinaryCodeAlignment( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::GetBinaryCodeAlignment( pDevice );
    }

/**
* @brief  Constructor.
*/
    TShader() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes the shader.
*
* @param[in] pDevice  Pointer to the device.
* @param[in] info  Information for initialization purposes.
*
* @return  Returns the result of shader initialization.
* @retval ShaderInitializeResult_Success  Succeeded.
* @retval ShaderInitializeResult_InvalidFormat  The shader format specified in <tt><var>info</var></tt> is not valid in this environment.
* @retval ShaderInitializeResult_SetupFailed  Shader setup failed due to a compiling failure or other problem.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The shader is not initialized.
*
* @post
*  - The shader is initialized.
*/
    ShaderInitializeResult Initialize( TDevice< Target >* pDevice, const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( pDevice, info );
    }

/**
* @brief  Finalizes the shader.
*
* @param[in] pDevice  Pointer to the device.
*
* @pre
*  - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pDevice</var></tt> is initialized.
*  - The shader is initialized.
*
* @post
*  - The shader is not initialized.
*/
    void Finalize( TDevice< Target >* pDevice ) NN_NOEXCEPT
    {
        return Impl::Finalize( pDevice );
    }

/**
* @brief  Gets the slot number of a shader interface.
*
* @param[in] stage  Target shader stage
* @param[in] shaderInterfaceType  The target interface type.
* @param[in] pName  Pointer to the name of the target interface.
*
* @pre
*  - The shader is initialized.
*  - <tt><var>pName</var></tt> != <tt>NULL</tt>.
*
* @return
*  Returns the slot number of the specified interface. Returns a negative value if the specified interface cannot be found.
*
* @details
*  Note that this function might return a different value than the one explicitly written in the shader source code.
*  Use the value returned by this function when setting resources or other operations where the slot number is required.
*/
    int GetInterfaceSlot( ShaderStage stage, ShaderInterfaceType shaderInterfaceType,
        const char* pName ) const NN_NOEXCEPT
    {
        return Impl::GetInterfaceSlot( stage, shaderInterfaceType, pName );
    }

/**
* @brief  Gets the size of compute shader work groups.
*
* @param[out] pOutWorkGroupSizeX  Pointer to the region storing the size of the work group's x dimension for the obtained compute shader.
* @param[out] pOutWorkGroupSizeY  Pointer to region storing the size of the work group's y dimension for the obtained compute shader.
* @param[out] pOutWorkGroupSizeZ  Pointer to region storing the size of the work group's z-dimension for the obtained compute shader.
*
* @pre
*  - The shader is initialized.
*  - <tt><var>pOutWorkGroupSizeX</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutWorkGroupSizeY</var></tt> != <tt>NULL</tt>.
*  - <tt><var>pOutWorkGroupSizeZ</var></tt> != <tt>NULL</tt>.
*/
    void GetWorkGroupSize( int* pOutWorkGroupSizeX, int* pOutWorkGroupSizeY,
        int* pOutWorkGroupSizeZ ) const NN_NOEXCEPT
    {
        return Impl::GetWorkGroupSize( pOutWorkGroupSizeX, pOutWorkGroupSizeY, pOutWorkGroupSizeZ );
    }

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
};

}
}
