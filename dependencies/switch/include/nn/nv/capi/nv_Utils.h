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
* @brief  This class provides graphics utilities.
*/

#pragma once

#ifdef __cplusplus
#include <nn/nn_Common.h>

namespace nv {

//! @name  Utilities
//! @{

/**
* @brief  Query status of No-Vsync capability.
*
* @details
*  This function can be used only for debugging.
*  The function returns the capability to render without vsync waits.
*  In other words, whether the driver allows to render with <tt>SwapInterval</tt> = <tt>0</tt>.
*
* @return  Returns <tt>true</tt> if rendering without vsync wait is allowed, and <tt>false</tt> otherwise.
*/
    bool IsCapableNoVsyncForDebug() NN_NOEXCEPT;

//! @}

}

#endif
