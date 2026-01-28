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
* @brief  Declarations of API resources for descriptor slots.
*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing a descriptor slot.
*/
struct DescriptorSlotData
{
    uint64_t value; //!<  The value of the descriptor slot.
};

/**
* @brief  The class representing a descriptor slot.
*/
class DescriptorSlot
    : public detail::DataContainer< DescriptorSlotData >
{
public:
/**
* @brief  Constructor.
*/
    DescriptorSlot() NN_NOEXCEPT
    {
        this->value = InvalidValue;
    }

/**
* @brief  Offsets the descriptor slot to point to a different descriptor.
    *
* @param[in] offset  The offset value.
    *
* @details
*  For <tt><var>offset</var></tt>, specify a multiple of the value obtained by <tt>nn::gfx::DescriptorPool::GetDescriptorSlotIncrementSize</tt>.
*/
    void Offset( ptrdiff_t offset ) NN_NOEXCEPT
    {
        this->value += offset;
    }

/**
* @brief  Determines whether the obtained slot is a valid slot.
    *
* @return  A Boolean value indicating whether the obtained slot is a valid slot.
    *
* @details
    * This function does not evaluate the validity of the indicated descriptor.
*/
    bool IsValid() const NN_NOEXCEPT
    {
        return this->value != InvalidValue;
    }

/**
* @brief  Invalidates a descriptor slot.
    *
* @post
    * - The descriptor slot is invalid.
*/
    void Invalidate() NN_NOEXCEPT
    {
        this->value = InvalidValue;
    }

private:
    static const uint64_t InvalidValue = static_cast< uint64_t >( -1 );
};

}
}
