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
* @brief  Declarations of API resources for device initialization information.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>
#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_DeviceInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The class representing the information for initializing a device.
*/
class DeviceInfo
    : public detail::DataContainer< DeviceInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - Each parameter is initialized to zero.
*/
    DeviceInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  Helper function to set each parameter to the default value.
*
* @post
*  - Each parameter is set.
*
* @details
*  Equivalent to calling the following.
*  - SetDebugMode( nn::gfx::DebugMode_Disable );
*  - SetTileCacheMode( nn::gfx::TileCacheMode_Disable );
*  - SetApiVersion( 0, 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the debug mode.
*
* @param[in] value  Debug mode.
*
* @post
*  - The debug mode is set.
*/
    void SetDebugMode( DebugMode value ) NN_NOEXCEPT
    {
        this->debugMode = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the API version.
*
* @param[in] majorVersion  Major version of the API.
* @param[in] minorVersion  Minor version of the API.
*
* @post
*  - The API version is set.
*/
    void SetApiVersion( int majorVersion, int minorVersion ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( majorVersion >= 0 );
        NN_SDK_REQUIRES( minorVersion >= 0 );
        this->apiMajorVersion = static_cast< uint16_t >( majorVersion );
        this->apiMinorVersion = static_cast< uint16_t >( minorVersion );
    }

/**
* @brief  Sets the debug mode.
*
* @return  Returns the debug mode.
*/
    DebugMode GetDebugMode() const NN_NOEXCEPT
    {
        return static_cast< DebugMode >( this->debugMode );
    }

/**
* @brief  Gets the major version of the API.
*
* @return  Returns the major version of the API.
*/
    int GetApiMajorVersion() const NN_NOEXCEPT
    {
        return static_cast< int >( this->apiMajorVersion );
    }

/**
* @brief  Gets the minor version of the API.
*
* @return  Returns the minor version of the API.
*/
    int GetApiMinorVersion() const NN_NOEXCEPT
    {
        return static_cast< int >( this->apiMinorVersion );
    }
};

}
}
