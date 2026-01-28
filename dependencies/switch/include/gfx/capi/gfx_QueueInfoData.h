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
* @brief  Declarations of API resources for queue initialization information data.
*/

#pragma once

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>

namespace nn {
namespace gfx {

/**
* @brief  Structure that represents the information for initializing a queue.
*/
struct QueueInfoData
{
    Bit16 capability; //!<  A combination of <tt>nn::gfx::QueueCapability</tt> values representing queue features.

    char reserved[ 30 ]; //!<  This is a reserved region.
};

}
}
