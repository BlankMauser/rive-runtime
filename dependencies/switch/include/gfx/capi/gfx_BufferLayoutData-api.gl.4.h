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
* @brief  GL4-specific declarations of the API for layout data for buffers that are read and written by the GPU.
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.gl.h>

#include <nn/gfx/detail/gfx_Declare.h>

namespace nn {
namespace gfx {

/**
* @brief  The GL4-specific structure representing <tt>TimestampBuffer</tt>.
*/
template<>
struct TimestampBufferImplData< ApiVariationGl4 >
{
    uint64_t value; //!<  The timestamp value.
};

/**
* @brief  The GL4-specific structure representing <tt>QueryBuffer</tt>.
*/
template<>
struct QueryBufferImplData< ApiVariationGl4 >
{
    uint64_t value; //!<  The query result value.
};

}
}
