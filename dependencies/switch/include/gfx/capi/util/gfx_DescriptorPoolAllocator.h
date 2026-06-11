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

#include <nn/gfx.h>
#include <nn/mem/mem_NumberLineAllocator.h>


namespace nn {
namespace gfx {
namespace util {


//! @brief  This allocator is for breaking slots in a descriptor pool into smaller units for use.
//! @details  Management-region memory is allocated and freed with a callback function specified by the user.
class DescriptorPoolAllocator
{
    NN_DISALLOW_COPY( DescriptorPoolAllocator );
    NN_DISALLOW_MOVE( DescriptorPoolAllocator );

public:
    //! @brief  The maximum number of slots that can be managed with this class.
    static const int SlotCountMax = 0x1000000;

    //! @brief  Represents an invalid index.
    static const int InvalidIndex = -1;

    //! @brief  Instantiates an object with default parameters (default constructor).
    DescriptorPoolAllocator() NN_NOEXCEPT;

    //! @brief  Initializes.
    //! @param[in] pAllocateFunction  The callback function for allocating a management region.
    //! @param[in] pAllocateFunctionUserData  The user-defined parameter called when allocating the management region.
    //! @param[in] pFreeFunction  The callback function for freeing a management region.
    //! @param[in] pFreeFunctionUserData  The user-defined parameter called when freeing the management region.
    //! @param[in] pDescriptorPool  The descriptor pool.
    //! @param[in] baseSlotIndex  The index of the start of the descriptor slot to use.
    //! @param[in] slotCount  The number of descriptor slots to use.
    //! @param[in] isThreadSafe  Flag indicating whether to thread-safe call the <tt>Allocate()</tt> and <tt>Free()</tt> functions.
    //! @pre  <tt>IsInitialized()</tt> == <tt>false</tt>.
    //! @pre  <tt><var>pAllocateFunction</var></tt> must be a pointer to a valid callback function.
    //! @pre  <tt><var>pFreeFunction</var></tt> must be a pointer to a valid callback function.
    //! @pre  <tt><var>pDescriptorPool</var></tt> must be a pointer to a valid descriptor pool.
    //! @pre  <tt><var>baseSlotIndex</var></tt> >= <tt>0</tt>.
    //! @pre  <tt><var>slotCount</var></tt> >= <tt>1</tt> && <tt><var>slotCount</var></tt> <= <tt>SlotCountMax</tt>.
    //! @post  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @details
    //!  This function is not thread-safe.
    void Initialize(
        nn::mem::MallocCallback pAllocateFunction,
        void* pAllocateFunctionUserData,
        nn::mem::FreeCallback pFreeFunction,
        void* pFreeFunctionUserData,
        nn::gfx::DescriptorPool* pDescriptorPool,
        int baseSlotIndex,
        int slotCount,
        bool isThreadSafe
        ) NN_NOEXCEPT;

    //! @brief  Finalizes the instance.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @post  <tt>IsInitialized()</tt> == <tt>false</tt>.
    //! @details
    //!  This function is not thread-safe.
    void Finalize() NN_NOEXCEPT;

    //! @brief  Determines whether this object is initialized.
    //! @return  Returns <tt>true</tt> when initialized. Returns <tt>false</tt> otherwise.
    //! @details
    //!  Becomes initialized, using <tt>Initialize()</tt>.
    //!  Becomes uninitialized, using <tt>Finalize()</tt>.
    bool IsInitialized() const NN_NOEXCEPT;

    //! @brief  Assigns a segment.
    //! @param[in] count  The length of the segment to allocate.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @pre  <tt><var>count</var></tt> >= <tt>0</tt>.
    //! @return  Returns the segment's starting index when allocation succeeded; otherwise returns <tt>InvalidIndex</tt>.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    int Allocate(int count) NN_NOEXCEPT;

    //! @brief  Frees an assigned segment.
    //! @param[in] indexSlot  The starting index for the segment to release.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @pre  <tt><var>indexSlot</var></tt> must be the start index for the segment allocated from the allocator.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    void Free(int indexSlot) NN_NOEXCEPT;

    //! @brief  Gets the descriptor pool configured for this object.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the descriptor pool that is currently set.
    //! @details
    //!  This function is thread-safe.
    nn::gfx::DescriptorPool* GetDescriptorPool() const NN_NOEXCEPT;

    //! @brief  Gets the index for the start of the descriptor slots managed by this object.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the index for the start of the managed descriptor slots.
    //! @details
    //!  This function is thread-safe.
    int GetBaseSlotIndex() const NN_NOEXCEPT;

    //! @brief  Gets the number of descriptor slots that this object is managing.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the number of managed descriptor slots.
    //! @details
    //!  This function is thread-safe.
    int GetSlotCount() const NN_NOEXCEPT;

    //! @brief  Gets the size of the specified allocated segment.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @pre  <tt><var>indexSlot</var></tt> must be the start index for the segment allocated from the allocator.
    //! @param[in] indexSlot  The starting index of the specified allocated segment for which to obtain the size.
    //! @return  Returns the size of the specified allocated segment.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    int GetSizeOf(int indexSlot) NN_NOEXCEPT;

    //! @brief  Gets the current total amount of free space in the allocator.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the total size of the empty area.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    int GetTotalFreeSize() NN_NOEXCEPT;

    //! @brief  Gets the largest size that can be allocated from the allocator.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the size that can be allocated.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    int GetAllocatableSize() NN_NOEXCEPT;

    //! @brief  Displays the allocator information.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @details
    //!  For more information about the output format, see NintendoSDK Documents.
    void Dump() NN_NOEXCEPT;

private:
    nn::mem::NumberLineAllocator m_Impl;
    nn::gfx::DescriptorPool* m_pDescriptorPool;
    int m_BaseSlotIndex;
    int m_SlotCount;
    bool m_IsInitialized;
};

} // namespace util
} // namespace gfx
} // namespace nn
