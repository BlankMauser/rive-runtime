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
* @brief  API declarations for the layout of buffers that the GPU reads and writes.
*/

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_TargetConfig.h>

#include <nn/gfx/detail/gfx_Declare.h>

#if defined( NN_GFX_CONFIG_INCLUDE_GL4 )
    #include <nn/gfx/detail/gfx_BufferLayout-api.gl.4.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_BufferLayout-api.nvn.8.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_GX2 )
    #include <nn/gfx/detail/gfx_BufferLayout-api.gx.2.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_D3D11 )
    #include <nn/gfx/detail/gfx_BufferLayout-api.d3d.11.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_VK1 )
    #include <nn/gfx/detail/gfx_BufferLayout-api.vk.1.h>
#endif

#if defined( NN_GFX_CONFIG_INCLUDE_EX1 )
    #include <nn/gfx/detail/gfx_BufferLayout-api.ex.1.h>
#endif

namespace nn {
namespace gfx {

/**
* @brief  Graphics abstraction layer representing the buffer used for timestamps.
*
* @tparam TTarget  The target low-level graphics API.
*
* @details
*  This class represents the layout of content written by the GPU.
*  It does not express low-level graphics API objects.
*/
template< typename TTarget >
class TTimestampBuffer
    : public detail::TimestampBufferImpl< typename detail::TargetVariation< TTarget >::Type >
{
    typedef detail::TimestampBufferImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  Gets the time stamp value.
*
* @return  Returns the timestamp value.
*/
    int64_t GetValue() const NN_NOEXCEPT
    {
        return Impl::GetValue();
    }
};

/**
* @brief  Graphics abstraction layer representing the layout for the buffer used for queries.
*
* @tparam TTarget  The target low-level graphics API.
*
* @details
*  This class represents the layout of content written by the GPU.
*  It does not express low-level graphics API objects.
*/
template< typename TTarget >
class TQueryBuffer
    : public detail::QueryBufferImpl< typename detail::TargetVariation< TTarget >::Type >
{
    typedef detail::QueryBufferImpl< typename detail::TargetVariation< TTarget >::Type > Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename Impl::Target Target;

/**
* @brief  Gets the query result.
*
* @return  Returns the query result.
*/
    int64_t GetValue() const NN_NOEXCEPT
    {
        return Impl::GetValue();
    }
};

/**
* @brief  Gets the time between two timestamps.
*
* @param[in] startTimestampValue  The starting-point timestamp.
* @param[in] endTimestampValue  The ending-point timestamp.
*
* @return  Returns the time between the specified starting and ending points.
*
* @details
*  For the timestamp values, you can use the values obtained by <tt>nn::gfx::TimestampBuffer::GetValue</tt>.
*/
inline nn::TimeSpan GetDuration( int64_t startTimestampValue, int64_t endTimestampValue ) NN_NOEXCEPT
{
    return detail::GetDuration< TargetConfig::Variation >( startTimestampValue, endTimestampValue );
}

}
}
