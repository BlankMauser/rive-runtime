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
* @brief  Declarations of API resources for data about the layout of the buffers accessed by the GPU for reading and writing (NVN8 special edition).
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Variation-api.nvn.h>

#include <nn/gfx/detail/gfx_Declare.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing <tt>TimestampBuffer</tt> (NVN8 special edition).
*/
template<>
struct TimestampBufferImplData< ApiVariationNvn8 >
{
    char reserved[ 8 ]; //!<  This is a reserved region.
    uint64_t value; //!<  The timestamp value.
};

/**
* @brief  The structure representing <tt>QueryBuffer</tt> (NVN8 special edition).
*/
template<>
struct QueryBufferImplData< ApiVariationNvn8 >
{
    uint64_t value; //!<  The query result value.
    uint64_t timestamp; //!<  The timestamp value when the query result was written.
};

}
}
