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
* @brief  Declarations of API resources for the information used to initialize a command buffer.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>
#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_CommandBufferInfoData.h>

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  The class representing the information for initializing a command buffer.
*/
class CommandBufferInfo
    : public detail::DataContainer< CommandBufferInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    CommandBufferInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
    *
* @post
    * - The various parameters are configured.
    *
* @details
    * Equivalent to calling the following.
    * - SetCommandBufferType( nn::gfx::CommandBufferType_Direct );
    * - SetQueueCapability( nn::gfx::QueueCapability_Graphics |
*  nn::gfx::QueueCapability_Compute | nn::gfx::QueueCapability_Copy );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the type of the command buffer.
    *
* @param[in] value  The type of the command buffer.
    *
* @post
    * - The type of command buffer has been set.
*/
    void SetCommandBufferType( CommandBufferType value ) NN_NOEXCEPT
    {
        this->commandBufferType = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the submit destination queue capability.
    *
* @param[in] value  Sets the submiit destination queue capability as a combination of <tt>nn::gfx::QueueCapability</tt> values.
    *
* @post
    * - The submit destination queue capability is set.
*/
    void SetQueueCapability( int value ) NN_NOEXCEPT
    {
        this->queueCapability = static_cast< Bit16 >( value );
    }

/**
* @brief  Gets the type of the command buffer.
    *
* @return  Returns the type of command buffer.
*/
    CommandBufferType GetCommandBufferType() const NN_NOEXCEPT
    {
        return static_cast< CommandBufferType >( this->commandBufferType );
    }

/**
* @brief  Gets the submit destination queue capability.
    *
* @return  Returns the submit destination queue capability.
*/
    int GetQueueCapability() const NN_NOEXCEPT
    {
        return this->queueCapability;
    }
};

}
}
