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
* @brief  Declarations for API resources related to conversions between data and accessors.
*/

#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] accessor  The target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< typename TAccessor::DataType > AccessorToData( TAccessor& accessor ) NN_NOEXCEPT
{
    return accessor.ToData();
}

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] accessor  The target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< volatile typename TAccessor::DataType > AccessorToData( volatile TAccessor& accessor ) NN_NOEXCEPT
{
    return accessor.ToData();
}

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] accessor  The target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< volatile const typename TAccessor::DataType > AccessorToData( volatile const TAccessor& accessor ) NN_NOEXCEPT
{
    return accessor.ToData();
}

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] accessor  The target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< const typename TAccessor::DataType > AccessorToData( const TAccessor& accessor ) NN_NOEXCEPT
{
    return accessor.ToData();
}

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] pAccessor  Pointer to the target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< typename TAccessor::DataType > AccessorToData( TAccessor* pAccessor ) NN_NOEXCEPT
{
    return pAccessor->ToData();
}

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] pAccessor  Pointer to the target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< const typename TAccessor::DataType > AccessorToData( const TAccessor* pAccessor ) NN_NOEXCEPT
{
    return pAccessor->ToData();
}

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] pAccessor  Pointer to the target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< volatile typename TAccessor::DataType > AccessorToData( volatile TAccessor* pAccessor ) NN_NOEXCEPT
{
    return pAccessor->ToData();
}

/**
* @brief  Converts an accessor to data.
*
* @tparam TAccessor  The accessor type.
*
* @param[in] pAccessor  Pointer to the target accessor.
*
* @return  Returns a temporary class for getting the converted data.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to a data type that corresponds to the accessor type.
*/
template< typename TAccessor >
inline detail::Caster< volatile const typename TAccessor::DataType > AccessorToData( volatile const TAccessor* pAccessor ) NN_NOEXCEPT
{
    return pAccessor->ToData();
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] data  The target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< detail::DataContainer< TData > > DataToAccessor( TData& data ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( data );
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] data  The target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< const detail::DataContainer< TData > > DataToAccessor( const TData& data ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( data );
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] data  The target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< volatile detail::DataContainer< TData > > DataToAccessor( volatile TData& data ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( data );
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] data  The target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< volatile const detail::DataContainer< TData > > DataToAccessor( volatile const TData& data ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( data );
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] pData  Pointer to the target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< detail::DataContainer< TData > > DataToAccessor( TData* pData ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( *pData );
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] pData  Pointer to the target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< const detail::DataContainer< TData > > DataToAccessor( const TData* pData ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( *pData );
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] pData  Pointer to the target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< volatile detail::DataContainer< TData > > DataToAccessor( volatile TData* pData ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( *pData );
}

/**
* @brief  Converts the data to an accessor.
*
* @tparam TData  The data type.
*
* @param[in] pData  Pointer to the target data.
*
* @return  Returns a temporary class for getting the converted accessor.
*
* @details
*  For the value returned by this function, assign a reference or a pointer to an accessor type that corresponds to the data type.
*/
template< typename TData >
inline detail::Caster< volatile const detail::DataContainer< TData > > DataToAccessor( volatile const TData* pData ) NN_NOEXCEPT
{
    return detail::DataContainer< TData >::DataToAccessor( *pData );
}

}
}
