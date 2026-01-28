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
* @brief  Declarations of API resources for devices.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_DeviceInfo.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_RequiredMemory.h>
#include <nn/gfx/detail/gfx_UserPtr.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_Device-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_Device-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_Device-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_Device-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_Device-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

class DisplayHandle;

/**
* @brief  Graphics abstraction layer representing a device.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
class TDevice
    : public detail::DeviceImpl< typename detail::TargetVariation< TTarget >::Type >
    , private detail::RequiredMemory< detail::DeviceImpl<
        typename detail::TargetVariation< TTarget >::Type > >
{
    NN_DISALLOW_COPY( TDevice );

    typedef detail::DeviceImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  The information class for initializing a device.
*/
    typedef DeviceInfo InfoType;

/**
* @brief  Required memory information.
*/
    enum RequiredMemoryInfo
    {
        RequiredMemoryInfo_Alignment = detail::RequiredMemory< Impl >::MemoryInfoImpl::RequiredMemoryInfo_Alignment
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
    TDevice() NN_NOEXCEPT
    {
    }

/**
* @brief  Initializes a device.
*
* @param[in] info  Information for initialization purposes.
*
* @post
*  - The device is initialized.
*/
    void Initialize( const InfoType& info ) NN_NOEXCEPT
    {
        return Impl::Initialize( info );
    }

/**
* @brief  Finalizes a device.
*
* @post
*  - The device is not initialized.
*/
    void Finalize() NN_NOEXCEPT
    {
        return Impl::Finalize();
    }

/**
* @brief  Sets an optional user pointer.
*
* @param[in] value  The user pointer to set.
*
* @post
*  - The user pointer has been set.
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
