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


//! @brief  This allocator is for breaking memory in a large memory pool into smaller units for use.
//! @details  Management-region memory is allocated and freed with a callback function specified by the user.
class MemoryPoolAllocator
{
    NN_DISALLOW_COPY( MemoryPoolAllocator );
    NN_DISALLOW_MOVE( MemoryPoolAllocator );

public:
    //! @brief  The size of memory unit that this class will manage.
    //! @details  Internally, a memory pool as large as <tt>AllocatorUnitSize</tt> will be consumed even when a smaller size is allocated.
    static const size_t AllocatorUnitSize = (1 << 8);

    //! @brief  The maximum value for the number of units that can be managed with this class.
    static const size_t AllocatorUnitCountMax = 0x1000000;

    //! @brief  The maximum value for the memory size that can be managed with this class.
    static const size_t SizeMax = AllocatorUnitSize * (AllocatorUnitCountMax - 1);

    //! @brief  The maximum value for the alignment that can be used with this class.
    static const size_t AlignmentMax = (1 << 17);

    //! @brief  Gets an invalid offset.
    static const ptrdiff_t InvalidOffset = -1;

    //! @brief  This mode is for allocation and release.
    //! @details
    //!  Specifies the behavior when allocating and releasing segments.
    //!  By default, a value of <tt>AllocationMode_NoOption</tt> is specified.
    enum AllocationMode {
        AllocationMode_NoOption = 0,            //!<  If a segment longer than 256 is released, the region is combined with adjacent empty regions.
        AllocationMode_CoalesceAdjacentArea = 1 //!<  Constantly combine with adjacent empty regions upon release. While the running efficiency is lower than <tt>AllocationMode_NoOption</tt>, it can suppress fragmentation within the allocator.
    };

    //! @brief  Instantiates an object with default parameters (default constructor).
    MemoryPoolAllocator() NN_NOEXCEPT;

    //! @brief  Initializes.
    //! @param[in] pAllocateFunction  The callback function for allocating a management region.
    //! @param[in] pAllocateFunctionUserData  The user-defined parameter called when allocating the management region.
    //! @param[in] pFreeFunction  The callback function for freeing a management region.
    //! @param[in] pFreeFunctionUserData  The user-defined parameter called when freeing the management region.
    //! @param[in] pMemoryPool  The memory pool.
    //! @param[in] baseOffset  The offset for the start to the memory pool to use.
    //! @param[in] size  The size of memory pool to use.
    //! @param[in] allocatableAlignmentMax  The maximum value for the specified alignment when assigning a segment.
    //! @param[in] isThreadSafe  Flag indicating whether to thread-safe call the <tt>Allocate()</tt> and <tt>Free()</tt> functions.
    //! @pre  <tt>IsInitialized()</tt> == <tt>false</tt>.
    //! @pre  <tt><var>pAllocateFunction</var></tt> must be a pointer to a valid callback function.
    //! @pre  <tt><var>pFreeFunction</var></tt> must be a pointer to a valid callback function.
    //! @pre  <tt><var>pMemoryPool</var></tt> must be a pointer to a valid memory pool.
    //! @pre  <tt><var>baseOffset</var></tt> >= <tt>0</tt>.
    //! @pre  <tt><var>baseOffset</var></tt> % <tt><var>allocatableAlignmentMax</var></tt> == <tt>0</tt>.
    //! @pre  <tt><var>size</var></tt> >= <tt>1</tt> && <tt><var>size</var></tt> <= <tt>SizeMax</tt>.
    //! @pre  <tt><var>allocatableAlignmentMax</var></tt> >= <tt>1</tt> && <tt><var>allocatableAlignmentMax</var></tt> <= <tt>AlignmentMax</tt>.
    //! @pre  <tt><var>allocatableAlignmentMax</var></tt> must be a power of 2.
    //! @post  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @details
    //!  This function is not thread-safe.
    void Initialize(
        nn::mem::MallocCallback pAllocateFunction,
        void* pAllocateFunctionUserData,
        nn::mem::FreeCallback pFreeFunction,
        void* pFreeFunctionUserData,
        nn::gfx::MemoryPool* pMemoryPool,
        ptrdiff_t baseOffset,
        size_t size,
        size_t allocatableAlignmentMax,
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
    //! @param[in] size  The length of the segment to allocate.
    //! @param[in] alignment  The alignment of the segment to allocate.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @pre  <tt><var>alignment</var></tt> >= <tt>1</tt> && <tt><var>alignment</var></tt> <= <tt>GetAllocatableAlignmentMax()</tt>.
    //! @pre  <tt><var>alignment</var></tt> must be a power of 2.
    //! @return  Returns the segment's starting offset when allocation succeeded; otherwise returns <tt>InvalidOffset</tt>.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    ptrdiff_t Allocate(size_t size, size_t alignment) NN_NOEXCEPT;

    //! @brief  Frees an assigned segment.
    //! @param[in] offset  The start of the offset for the segment to free.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @pre  <tt><var>offset</var></tt> must be the start offset for the segment allocated from the allocator.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    void Free(ptrdiff_t offset) NN_NOEXCEPT;

    //! @brief  Gets the memory pool configured for this object.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the memory pool that is currently set.
    //! @details
    //!  This function is thread-safe.
    nn::gfx::MemoryPool* GetMemoryPool() const NN_NOEXCEPT;

    //! @brief  Gets the offset for the start of the memory region managed by this object.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the offset from the start of the managed memory region.
    //! @details
    //!  This function is thread-safe.
    ptrdiff_t GetBaseOffset() const NN_NOEXCEPT;

    //! @brief  Gets the size, in bytes, for the memory region managed by this object.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the size, in bytes, for the managed memory region.
    //! @details
    //!  This function is thread-safe.
    size_t GetSize() const NN_NOEXCEPT;

    //! @brief  Gets the maximum alignment, in bytes, that can be used when allocating memory from this object.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the maximum alignment, in bytes, that can be used when allocating memory.
    //! @details
    //!  This function is thread-safe.
    size_t GetAllocatableAlignmentMax() const NN_NOEXCEPT;

    //! @brief  Gets the size of the specified allocated segment.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @pre  <tt><var>offset</var></tt> must be the start offset for the segment allocated from the allocator.
    //! @param[in] offset  The starting offset for the specified allocated segment for which to get the size.
    //! @return  Returns the size of the specified allocated segment.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    size_t GetSizeOf(ptrdiff_t offset) NN_NOEXCEPT;

    //! @brief  Gets the total available memory for the allocator.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the total size of the empty area.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    size_t GetTotalFreeSize() NN_NOEXCEPT;

    //! @brief  Gets the largest size that can be allocated from the allocator.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the size that can be allocated.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    size_t GetAllocatableSize() NN_NOEXCEPT;

    //! @brief  Sets the mode to use for allocation and release.
    //! @param[in] allocationMode  Mode for allocation and release.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @details
    //!  By default, a value of <tt>AllocationMode_NoOption</tt> is specified.
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    void SetAllocationMode(AllocationMode allocationMode) NN_NOEXCEPT;

    //! @brief  Gets the mode to use for allocation and release.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @return  Returns the mode to use for allocation and release.
    //! @details
    //!  This function is thread-safe when <tt>true</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter during <tt>Initialize()</tt>.
    //!  This function is not thread-safe when <tt>false</tt> is passed to the <tt><var>isThreadSafe</var></tt> parameter.
    AllocationMode GetAllocationMode() const NN_NOEXCEPT;

    //! @brief  Displays the information in the allocator.
    //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
    //! @details
    //!  For more information about the output format, see NintendoSDK Documents.
    void Dump() NN_NOEXCEPT;

private:
    nn::mem::NumberLineAllocator m_Impl;
    nn::gfx::MemoryPool* m_pMemoryPool;
    ptrdiff_t m_BaseOffset;
    size_t m_Size;
    size_t m_AllocatableAlignmentMax;
    bool m_IsInitialized;
};

} // namespace util
} // namespace gfx
} // namespace nn
