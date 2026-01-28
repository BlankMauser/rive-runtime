/*--------------------------------------------------------------------------------*
  Copyright Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/

#pragma once

#include <nn/nn_Common.h>

#include <nn/gfx/gfx_Config.h>

namespace nn {
namespace gfx {

/**
* @brief  Enumerated type representing the low-level graphics APIs.
*/
enum LowLevelApi
{
    LowLevelApi_Common = NN_GFX_CONFIG_API_TYPE_COMMON //!<  Shared by all low-level APIs.
};

/**
* @brief  Enumerated type representing the low-level graphics API.
*/
enum Version
{
    Version_All = -1 //!<  All versions.
};

/**
* @brief  Structure representing the low-level graphics API type.
*
* @tparam api  The type of the low-level graphics API represented by <tt>LowLevelApi_*</tt>.
*/
template< int api >
struct ApiType
{
    static const int value = api;
};

/**
* @brief  Structure representing the low-level graphics API version.
*
* @tparam version  The version value for the low-level graphics API.
*/
template< int version >
struct ApiVersion
{
    static const int value = version;
};

/**
* @brief  Structure representing the low-level graphics API default version.
*
* @tparam TType  The target low-level graphics API.
*/
template< typename TType >
struct DefaultVersion;

/**
* @brief  Structure representing the target low-level graphics API version.
*
* @tparam TTarget  The target low-level graphics API.
*/
template< typename TTarget >
struct TargetVersion
{
    typedef typename TTarget::Version Version;
};

/**
* @brief  Structure representing the low-level graphics API variation.
*
* @tparam TType  The type of the low-level graphics API.
* @tparam TVersion  The version of the low-level graphics API.
*/
template< typename TType, typename TVersion = typename TargetVersion< TType >::Version >
struct ApiVariation
{
    typedef TType Type;
    typedef TVersion Version;
    typedef ApiVariation< Type, Version > Variation;
};


/**
* @brief  Structure representing the low-level graphics API settings.
*
* @tparam TType  The target low-level graphics API.
*/
template< typename TType >
struct ApiTypeConfig
{
    typedef TType Type;
    typedef typename DefaultVersion< Type >::Version DefaultVersion;
    typedef typename TargetVersion< Type >::Version TargetVersion;
    typedef ApiVariation< Type, TargetVersion > TargetVariation;
};

namespace detail {

template< typename T, typename U >
struct HasVariation;
template< typename T >
struct HasVariation< T, typename T::Variation >
{
    typedef void Type;
};

template< typename T, int N = sizeof( T ) >
struct ExistsImpl
{
    typedef void Type;
};

template< typename TApiType, typename X = void >
struct TargetVariation
{
    typedef typename ApiTypeConfig< TApiType >::TargetVariation Type;
};
template< typename TVariation >
struct TargetVariation< TVariation, typename HasVariation<
    TVariation, typename TVariation::Variation >::Type >
{
    typedef typename TVariation::Variation Type;
};

template< typename TInfoImpl, typename TInfo, typename X = void >
struct TargetInfoImpl
{
    typedef TInfo Type;
};
template< typename TInfoImpl, typename TInfo >
struct TargetInfoImpl< TInfoImpl, TInfo, typename ExistsImpl< TInfoImpl >::Type >
{
    typedef TInfoImpl Type;
};

}

}
}
