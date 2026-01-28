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
* @brief  Declarations of APIs for user data resource data.
*/

#pragma once

#include <nn/util/util_BinTypes.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure indicating user data resources.
*/
struct ResUserDataData
{
    nn::util::BinPtrToString pName; //!<  The name.
    nn::util::BinTPtr< void > pData; //!<  Pointer to the data.
    uint32_t count; //!<  The number of data instances.
    uint8_t type; //!<  The <tt>nn::gfx::ResUserData::Type</tt> representation of the data type.

    char reserved[ 43 ]; //!<  This is a reserved region.
};

}
}
