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
* @brief  Definitions shared by the various features of the <tt>gfx</tt> API.
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Config.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL )
    #include <nn/gfx/gfx_Variation-api.gl.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN )
    #include <nn/gfx/gfx_Variation-api.nvn.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX )
    #include <nn/gfx/gfx_Variation-api.gx.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D )
    #include <nn/gfx/gfx_Variation-api.d3d.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK )
    #include <nn/gfx/gfx_Variation-api.vk.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX )
    #include <nn/gfx/gfx_Variation-api.ex.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Structure representing the range.
*/
struct Range
{
    ptrdiff_t offset; //!<  The offset from the start, in bytes.
    size_t size; //!<  The size, in bytes.
};

/**
* @brief  The parameter passed when there is an out-of-memory event.
*/
struct OutOfMemoryEventArg
{
    size_t minRequiredSize; //!<  The minimum required amount of memory, in bytes.
};

/**
* @brief  Union representing the clear color value.
*/
union ClearColorValue
{
    float valueFloat[ 4 ]; //!<  The clear color represented by floating-point values in the order of red component, green component, blue component, and alpha component.
    int32_t valueInt[ 4 ]; //!<  The clear color represented by signed integers in the order of red component, green component, blue component, and alpha component.
    uint32_t valueUint[ 4 ]; //!<  The clear color represented by unsigned integers in the order of red component, green component, blue component, and alpha component.
};

/**
* @brief  Determines whether an object has been initialized.
*
* @tparam TTarget  The target low-level graphics API.
* @tparam TObject  The type of the object.
*
* @param[in] obj  The target object.
*
* @return  Returns a Boolean value indicating whether the target object has been initialized.
*/
template< typename TTarget, template< typename > class TObject >
bool IsInitialized( const TObject< TTarget >& obj ) NN_NOEXCEPT
{
    return obj.ToData()->state != TObject< TTarget >::DataType::State_NotInitialized;
}

}
}
