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
* @brief  Declarations of API resources for allocator data.
*/

#pragma once

#include <nn/nn_Allocator.h>

namespace nn {
namespace gfx {

/**
* @brief  The type of the function that reallocates memory.
*/
typedef void* ( *ReallocateFunction )( void* pMemory, size_t size, size_t alignment, void* pUserData );

/**
* @brief  Structure representing the allocator.
*/
struct AllocatorData
{
    nn::AlignedAllocateFunctionWithUserData pAllocateFunction; //!<  Pointer to the function that is called when allocating memory.
    nn::FreeFunctionWithUserData pFreeFunction; //!<  Pointer to the function that is called when releasing memory.
    ReallocateFunction pReallocateFunction; //!<  Pointer to the function that is called when reallocating memory.
    void* pUserData; //!<  Pointer to the user data.
};

}
}
