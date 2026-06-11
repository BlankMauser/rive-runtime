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
* @brief  Declarations of API resources for swap chain initialization.
*/

#pragma once

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_SwapChainInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  Represents the information for initializing a swap chain.
*/
class SwapChainInfo
    : public detail::DataContainer< SwapChainInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - Each parameter is initialized to zero.
*/
    SwapChainInfo() NN_NOEXCEPT
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
*  - <tt>SetBufferCount( 2 );</tt>
*  - <tt>SetFormat( nn::gfx::ImageFormat_R8_G8_B8_A8_Unorm );</tt>
*  - <tt>SetWidth( 1280 );</tt>
*  - <tt>SetHeight( 720 );</tt>
*  - <tt>SetLayer( NULL );</tt>
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the layer.
*
* @param[in] value  Pointer to the layer.
*
* @post
*  - The layer has been set.
*
* @see
*  nn::vi::Layer
*/
    void SetLayer( nn::vi::Layer* value ) NN_NOEXCEPT
    {
        this->pLayer = value;
    }

/**
* @brief  Sets the rendering format.
*
* @param[in] value  The rendering format.
*
* @post
*  - The rendering format is set.
*/
    void SetFormat( ImageFormat value ) NN_NOEXCEPT
    {
        this->format = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets the number of scan buffers.
*
* @param[in] value  The number of scan buffers.
*
* @post
*  - The number of scan buffers is set.
*/
    void SetBufferCount( int value ) NN_NOEXCEPT
    {
        this->bufferCount = static_cast< uint8_t >( value );
    }

/**
* @brief  Sets the width of the scan buffer.
*
* @param[in] value  Width of the scan buffer.
*
* @post
*  - The width of the scan buffer is set.
*/
    void SetWidth( int value ) NN_NOEXCEPT
    {
        this->width = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the height of the scan buffer.
*
* @param[in] value  Height of the scan buffer.
*
* @post
*  - The height of the scan buffer is set.
*/
    void SetHeight( int value ) NN_NOEXCEPT
    {
        this->height = static_cast< uint32_t >( value );
    }

/**
* @brief  Gets the layer.
*
* @return  Returns a pointer to the layer.
*
* @see
*  nn::vi::Layer
*/
    nn::vi::Layer* GetLayer() const NN_NOEXCEPT
    {
        return this->pLayer;
    }

/**
* @brief  Gets the rendering format.
*
* @return  Returns the rendering format.
*/
    ImageFormat GetFormat() const NN_NOEXCEPT
    {
        return static_cast< ImageFormat >( this->format );
    }

/**
* @brief  Gets the number of scan buffers.
*
* @return  Returns the number of scan buffers.
*/
    int GetBufferCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->bufferCount );
    }

/**
* @brief  Gets the width of the scan buffer.
*
* @return  Returns the width of the scan buffer.
*/
    int GetWidth() const NN_NOEXCEPT
    {
        return static_cast< int >( this->width );
    }

/**
* @brief  Gets the height of the scan buffer.
*
* @return  Returns the height of the scan buffer.
*/
    int GetHeight() const NN_NOEXCEPT
    {
        return static_cast< int >( this->height );
    }
};

}
}
