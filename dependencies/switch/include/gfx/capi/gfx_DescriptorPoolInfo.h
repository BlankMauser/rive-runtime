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
* @brief  Declarations of API resources for the information used when initializing a descriptor pool.
*/

#pragma once

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_DescriptorPoolInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  Class representing the information for initializing a descriptor pool.
*/
class DescriptorPoolInfo
    : public detail::DataContainer< DescriptorPoolInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - Each parameter is initialized to zero.
*/
    DescriptorPoolInfo() NN_NOEXCEPT
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
*  - <tt>SetDescriptorPoolType( nn::gfx::DescriptorPoolType_BufferView )</tt>
*  - <tt>SetSlotCount( 0 )</tt>
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the type of the descriptor pool.
*
* @param[in] value  The type of the descriptor pool.
*
* @post
*  - The type of the descriptor pool is set.
*/
    void SetDescriptorPoolType( DescriptorPoolType value ) NN_NOEXCEPT
    {
        this->descriptorPoolType = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the number of slots in the descriptor pool.
*
* @param[in] value  The number of descriptor pool slots.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt>.
*
* @post
*  - The number of descriptor pool slots is set.
*/
    void SetSlotCount( int value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value >= 0 );
        this->slotCount = static_cast< uint32_t >( value );
    }

/**
* @brief  Gets the type of the descriptor pool.
*
* @return  Returns the type of the descriptor pool.
*/
    DescriptorPoolType GetDescriptorPoolType() const NN_NOEXCEPT
    {
        return static_cast< DescriptorPoolType >( this->descriptorPoolType );
    }

/**
* @brief  Gets the number of slots in the descriptor pool.
*
* @return  Returns the number of descriptor pool slots.
*/
    int GetSlotCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->slotCount );
    }
};

}
}
