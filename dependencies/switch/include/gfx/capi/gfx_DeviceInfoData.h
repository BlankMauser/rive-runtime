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
* @brief  Declarations of API resources for device initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

#include <nn/gfx/detail/gfx_Misc.h>

namespace nn {
namespace gfx {

/**
* @brief  The structure representing the information for initializing a device.
*/
struct DeviceInfoData
{
    Bit8 debugMode; //!<  The <tt>nn::gfx::DebugMode</tt> representation of the debug mode.
    char reserved2[ 3 ]; //!<  This is a reserved region.
    uint16_t apiMajorVersion;
    uint16_t apiMinorVersion;

    char reserved[ 56 ]; //!<  This is a reserved region.
};

}
}
