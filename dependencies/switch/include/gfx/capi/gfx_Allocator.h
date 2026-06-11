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
* @brief  Declarations for API resources for the allocator.
*/

#pragma once

#include <nn/nn_Allocator.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_AllocatorData.h>

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/detail/gfx_Declare.h>

namespace nn {
namespace gfx {

/**
* @brief  Class for representing the allocator.
*/
class Allocator
    : public detail::DataContainer< AllocatorData >
{
public:

/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    Allocator() NN_NOEXCEPT
    {
    }

/**
* @brief  Sets the function that allocates memory.
*
* @param[in] pAllocate  Pointer to the function that allocates memory.
*
* @post
*  - If <tt><var>pAllocate</var></tt> != <tt>NULL</tt>, the function that allocates memory is set.
*  - If <tt><var>pAllocate</var></tt> == <tt>NULL</tt>, the function that allocates memory is not set.
*/
    void SetAllocateFunction( nn::AlignedAllocateFunctionWithUserData pAllocate ) NN_NOEXCEPT
    {
        this->pAllocateFunction = pAllocate;
    }

/**
* @brief  Sets the function that releases memory.
*
* @param[in] pFree  Pointer to the function that releases memory.
*
* @post
*  - If <tt><var>pFree</var></tt> != <tt>NULL</tt>, the function that releases memory is set.
*  - If <tt><var>pFree</var></tt> == <tt>NULL</tt>, the function that releases memory is not set.
*/
    void SetFreeFunction( nn::FreeFunctionWithUserData pFree ) NN_NOEXCEPT
    {
        this->pFreeFunction = pFree;
    }

/**
* @brief  Sets the function that reallocates memory.
*
* @param[in] pReallocate  Pointer to the function that reallocates memory.
*
* @post
*  - If <tt><var>pReallocate</var></tt> != <tt>NULL</tt>, the function that reallocates memory is set.
*  - If <tt><var>pAllocate</var></tt> == <tt>NULL</tt>, the function that reallocates memory is not set.
*/
    void SetReallocateFunction( ReallocateFunction pReallocate ) NN_NOEXCEPT
    {
        this->pReallocateFunction = pReallocate;
    }

/**
* @brief  Sets user data.
*
* @param[in] pData  Pointer to the user data.
*
* @post
*  - If <tt><var>pUserData</var></tt> != <tt>NULL</tt>, user data is set.
*  - If <tt><var>pUserData</var></tt> == <tt>NULL</tt>, user data is not set.
*/
    void SetUserData( void* pData ) NN_NOEXCEPT
    {
        this->pUserData = pData;
    }

/**
* @brief  Gets a pointer to the function that allocates memory.
*
* @return  Returns a pointer to the function that allocates memory.
*/
    nn::AlignedAllocateFunctionWithUserData GetAllocateFunction() const NN_NOEXCEPT
    {
        return this->pAllocateFunction;
    }

/**
* @brief  Gets a pointer to the function that releases memory.
*
* @return  Returns a pointer to the function that releases memory.
*/
    nn::FreeFunctionWithUserData GetFreeFunction() const NN_NOEXCEPT
    {
        return this->pFreeFunction;
    }

/**
* @brief  Gets a pointer to the function that reallocates memory.
*
* @return  Returns a pointer to the function that reallocates memory.
*/
    ReallocateFunction GetReallocateFunction() const NN_NOEXCEPT
    {
        return this->pReallocateFunction;
    }

/**
* @brief  Gets a pointer to the user data.
*
* @return  Returns a pointer to the user data.
*/
    void* GetUserData() const NN_NOEXCEPT
    {
        return this->pUserData;
    }
};

/**
* @brief  Sets the memory allocator.
*
* @pre
*  - If <tt><var>pAllocator</var></tt> != <tt>NULL</tt>, <tt><var>pAllocator</var>->GetAllocateFunction()</tt> != <tt>NULL</tt> and <tt><var>pAllocator</var>->GetFreeFunction()</tt> != <tt>NULL</tt> are satisfied.
* @post
*  - If <tt><var>pAllocator</var></tt> != <tt>NULL</tt>, the allocator is set.
*  - If <tt><var>pAllocator</var></tt> == <tt>NULL</tt>, the allocator is not set.
*
* @details
*  If an allocator is set, memory that is allocated dynamically in the <tt>gfx</tt> library is allocated through the allocator.
*  If an allocator is not set, memory that is allocated dynamically in the <tt>gfx</tt> library is allocated though methods that depend on the <tt>gfx</tt> implementation.
*  Call this function only once before calling <tt>nn::gfx::Initialize</tt>. The behavior is undefined if this function is called after calling <tt>nn::gfx::Initialize</tt>.
*/
void SetAllocator( const Allocator* pAllocator ) NN_NOEXCEPT;

}
}
