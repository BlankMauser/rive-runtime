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
* @brief  Declarations of API resources for GPU addresses.
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure representing the GPU address.
*/
struct GpuAddressData
{
    uint64_t value; //!<  The GPU address.
    uint64_t impl; //!<  This value is used internally.
};

/**
* @brief  The class representing the GPU address.
*/
class GpuAddress
    : public detail::DataContainer< GpuAddressData >
{
public:
/**
* @brief  Constructor.
*/
    GpuAddress() NN_NOEXCEPT
    {
    }

/**
* @brief  Offsets the address.
*
* @param[in] offset  The offset, in bytes.
*/
    void Offset( ptrdiff_t offset ) NN_NOEXCEPT
    {
        this->value += offset;
    }
};

}
}
