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
* @brief  Declarations of API resources for queue initialization information.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>
#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_QueueInfoData.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/detail/gfx_DataContainer.h>

#if !defined( NN_GFX_CONFIG_DISABLE_TINFO )

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_QueueInfo-api.nvn.8.h>
#endif

#endif

namespace nn {
namespace gfx {

/**
* @brief  Represents the information for initializing a queue.
*/
class QueueInfo
    : public detail::DataContainer< QueueInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    QueueInfo() NN_NOEXCEPT
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
    * - SetCapability( nn::gfx::QueueCapability_Graphics |
*  nn::gfx::QueueCapability_Compute | nn::gfx::QueueCapability_Copy );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the queue capability.
    *
* @param[in] value  Queue capability as a combination of <tt>nn::gfx::QueueCapability</tt> values.
    *
* @post
    * The queue capability is set.
*/
    void SetCapability( int value ) NN_NOEXCEPT
    {
        this->capability = static_cast< Bit16 >( value );
    }

/**
* @brief  Gets the queue capability.
    *
* @return  Returns the queue capability as a combination of <tt>nn::gfx::QueueCapability</tt> values.
*/
    int GetCapability() const NN_NOEXCEPT
    {
        return this->capability;
    }
};

/**
* @brief  Graphics abstraction layer representing information for initializing a queue.
*/
template< typename TTarget >
class TQueueInfo
    : public detail::TargetInfoImpl< detail::QueueInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, QueueInfo >::Type
{
    typedef typename detail::TargetInfoImpl< detail::QueueInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, QueueInfo >::Type Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename detail::TargetVariation< TTarget >::Type Target;

/**
* @brief  Converts common-version information to special edition information.
    *
* @param[in] pDstInfo  Pointer to the destination for the converted special edition information.
* @param[in] info  The common-version information that will serve as the source.
    *
* @pre
    * - <tt><var>pDstInfo</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertFromInfo( TQueueInfo< TTarget >* pDstInfo, const QueueInfo& info ) NN_NOEXCEPT
    {
        return detail::InfoHelper::ConvertFromInfo< Impl >( pDstInfo, info );
    }

/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TQueueInfo() NN_NOEXCEPT
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
    * - SetCapability( nn::gfx::QueueCapability_Graphics |
*  nn::gfx::QueueCapability_Compute | nn::gfx::QueueCapability_Copy );
*/
    void SetDefault() NN_NOEXCEPT
    {
        return Impl::SetDefault();
    }

/**
* @brief  Sets the queue capability.
    *
* @param[in] value  Queue capability as a combination of <tt>nn::gfx::QueueCapability</tt> values.
    *
* @post
    * The queue capability is set.
*/
    void SetCapability( int value ) NN_NOEXCEPT
    {
        return Impl::SetCapability( value );
    }
};

}
}
