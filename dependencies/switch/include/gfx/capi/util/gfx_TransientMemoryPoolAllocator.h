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
#include <nn/gfx.h>

#include "detail/gfx_OffsetRange.h"
#include "detail/gfx_OffsetRingBuffer.h"

namespace nn{ namespace gfx{ namespace util{

    //! @brief  Allocator that manages the memory in the memory pool that is temporarily used.
    //! @details
    //!  Dynamically allocates the memory pool memory that is temporarily used during rendering.
    //!  Also provides a feature to deallocate all memory at the same time after rendering completes.
    class TransientMemoryPoolAllocator
    {
        NN_DISALLOW_COPY(TransientMemoryPoolAllocator);

    public:
        //! @brief  The maximum value for the memory size that can be managed with this class.
        //! @details  The maximum value for a size available within the implementation.
        static const size_t SizeMax = static_cast<size_t>(detail::OffsetRingBuffer::SizeMax);

        //! @brief  The maximum value for the alignment that can be used with this class.
        //! @details  The maximum value for an alignment available within the implementation.
        static const size_t AlignmentMax = static_cast<size_t>(detail::OffsetRingBuffer::AlignmentMax);

        //! @brief  Gets an invalid offset.
        //! @details
        //!  This value is returned if memory allocation failed.
        static const ptrdiff_t InvalidOffset = detail::OffsetRingBuffer::InvalidOffset;
    public:
        //! @brief  Instantiates an object with default parameters (default constructor).
        TransientMemoryPoolAllocator() NN_NOEXCEPT;

        //! @brief  Specifies the memory pool and the range for the offset to be managed, and then initializes.
        //! @param[in] pMemoryPool  The memory pool.
        //! @param[in] baseOffset  The start of the offset for the memory to manage.
        //! @param[in] size  The length, in bytes, of the memory to manage.
        //! @param[in] allocatableAlignmentMax  The maximum alignment required for the memory allocated from this allocator.
        //! @param[in] historyLengthMax  The maximum number of history entries to record.
        //! @pre  <tt>IsInitialized()</tt> == <tt>false</tt>.
        //! @pre  <tt><var>pMemoryPool</var></tt> must be a pointer to a valid memory pool.
        //! @pre  <tt><var>baseOffset</var></tt> >= <tt>0</tt>.
        //! @pre  <tt><var>baseOffset</var></tt> % <tt><var>allocatableAlignmentMax</var></tt> == <tt>0</tt>.
        //! @pre  <tt><var>size</var></tt> >= <tt>1</tt> && <tt><var>size</var></tt> <= <tt>SizeMax</tt>.
        //! @pre  <tt><var>allocatableAlignmentMax</var></tt> <= <tt>AlignmentMax</tt>.
        //! @pre  <tt><var>allocatableAlignmentMax</var></tt> must be a power of 2.
        //! @pre  <tt><var>historyLengthMax</var></tt> >= <tt>1</tt>.
        //! @pre  There must be a memory block configured to have the required alignment size, set with <tt>SetMemory()</tt>.
        //! @post  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @post  <tt>IsRecording()</tt> == <tt>false</tt>.
        //! @post  <tt>GetHistoryLength()</tt> == <tt>0</tt>.
        //! @details
        //!  This object targets the memory region with the range specified in the memory pool for management.
        //!  A contiguous valid range must be specified for the memory region.
        //!
        //!  <tt><var>baseOffset</var></tt> must be an integer multiple of <tt><var>allocatableAlignmentMax</var></tt>.
        //!  You can specify an alignment with a value that is at most equal to that specified in <tt><var>allocatableAlignmentMax</var></tt>, using <tt>Allocate()</tt>.
        //!
        //!  Calling this instance for the same instance is not thread-safe.
        void Initialize(
            nn::gfx::MemoryPool* pMemoryPool,
            ptrdiff_t baseOffset,
            size_t size,
            size_t allocatableAlignmentMax,
            int historyLengthMax
            ) NN_NOEXCEPT;

        //! @brief  Destroys this object.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @post  <tt>IsInitialized()</tt> == <tt>false</tt>.
        //! @details
        //!  Calling this instance for the same instance is not thread-safe.
        void Finalize() NN_NOEXCEPT;

        //! @brief  Determines whether this object is initialized.
        //! @return  Returns <tt>true</tt> when initialized. Returns <tt>false</tt> otherwise.
        //! @details
        //!  Becomes initialized, using <tt>Initialize()</tt>.
        //!  Becomes uninitialized, using <tt>Finalize()</tt>.
        bool IsInitialized() const NN_NOEXCEPT;

        //! @brief  Determines whether allocation for the memory from this object has started.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @return  Returns <tt>true</tt> when memory allocation has started. Returns <tt>false</tt> otherwise.
        //! @details
        //!  Success for <tt>Begin()</tt> triggers the start of memory allocation.
        //!  <tt>End()</tt> triggers the end of memory allocation.
        bool IsRecording() const NN_NOEXCEPT;

        //! @brief  Gets the size, in bytes, of the memory block required to initialize the object.
        //! @param[in] historyLengthMax  The maximum number of history entries for the object to record.
        //! @pre  <tt><var>historyLengthMax</var></tt> >= <tt>1</tt>.
        //! @return  Returns the size, in bytes, of the memory block required to initialize the object.
        //! @details
        //!  You must use <tt>SetMemory()</tt> to configure the memory block before calling <tt>Initialize()</tt>.
        //!  The size of the memory block configured with <tt>SetMemory()</tt> must be at least as large as the value obtained with this function.
        //!  This function is thread-safe.
        static size_t GetRequiredMemorySize(int historyLengthMax) NN_NOEXCEPT;

        //! @brief  Gets the alignment, in bytes, of the memory block required to initialize the object.
        //! @return  Returns the alignment, in bytes, of the memory block required to initialize the object.
        //! @details
        //!  You must use <tt>SetMemory()</tt> to configure the memory block before calling <tt>Initialize()</tt>.
        //!  The address of the memory block configured with <tt>SetMemory()</tt> must be a multiple of the value obtained with this function.
        //!  This function is thread-safe.
        static size_t GetRequiredMemoryAlignment() NN_NOEXCEPT;

        //! @brief  Sets the memory for use by this object.
        //! @param[in] pMemory  Pointer to the memory block.
        //! @param[in] size  The size (in bytes) of the memory block.
        //! @pre  <tt>IsInitialized()</tt> == <tt>false</tt>.
        //! @post  The memory to use is in the configured state.
        //! @details
        //!  Sets the memory for use by this object.
        //!  This function must be called before object initialization.
        //!  You can get values for the memory size and alignment. Set these values using <tt>GetRequiredMemorySize()</tt> and <tt>GetRequiredMemoryAlignment()</tt>.
        //!  <tt><var>pMemory</var></tt> must not be freed before this object has been destroyed.
        //!  Calling this instance for the same instance is not thread-safe.
        void SetMemory(void* pMemory, size_t size) NN_NOEXCEPT;

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

        //! @brief  Begins memory allocation.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>false</tt>.
        //! @pre  <tt>GetHistoryLength()</tt> < <tt>GetHistoryLengthMax()</tt>.
        //! @post  <tt>IsRecording()</tt> == <tt>true</tt>.
        //! @details
        //!  Calling this instance for the same instance is not thread-safe.
        void Begin() NN_NOEXCEPT;

        //! @brief  Ends memory allocation.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>true</tt>.
        //! @post  <tt>IsRecording()</tt> == <tt>false</tt>.
        //! @post  The range of the memory allocated between calls to the immediately prior <tt>Begin()</tt> function and the <tt>End()</tt> function is recorded.
        //! @post  The value returned by <tt>GetHistoryLength()</tt> is incremented by 1.
        //! @details
        //!  The history is recorded even when there is no memory allocated between calls to the immediately prior <tt>Begin()</tt> function and the <tt>End()</tt> function.
        //!  Calling this instance for the same instance is not thread-safe.
        //!  Free()
        void End() NN_NOEXCEPT;

        //! @brief  Releases the oldest recorded memory from among those recorded by this object.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>GetHistoryLength()</tt> > <tt>0</tt>.
        //! @post  Releases the oldest memory recorded in the history.
        //! @post  The value returned by <tt>GetHistoryLength()</tt> is decremented by 1.
        //! @details
        //!  The memory allocated between the calls to <tt>Begin()</tt> and <tt>End()</tt> is treated as a single unit and released.
        //!  The memory allocated individually using <tt>Allocate()</tt> cannot be released on an individual basis.
        //!  Any released memory becomes immediately available for allocation.
        //!  Multiply calling this instance for the same instance is not thread-safe.
        //!  Calling both this function for the same instance and the function that allocates memory at the same time is thread-safe.
        //!  End()
        void Free() NN_NOEXCEPT;

        //! @brief  Allocates memory.
        //! @param[in] size  The length, in bytes, of the memory to allocate.
        //! @param[in] alignment  The alignment, in bytes, of the memory to allocate.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>true</tt>.
        //! @pre  <tt><var>alignment</var></tt> <= <tt>GetAllocatableAlignmentMax()</tt>.
        //! @pre  <tt><var>alignment</var></tt> must be a power of 2.
        //! @return  Returns the offset from the start of the allocated memory.
        //!  Returns <tt>InvalidOffset</tt> when memory allocation fails.
        //! @details
        //!  For <tt><var>alignment</var></tt>, you must specify a value that is at most equal to that specified for <tt><var>allocatableAlignmentMax</var></tt> during <tt>Initialize()</tt>.
        //!  This function is thread-safe.
        //!  Can be called simultaneously with other functions allocating memory.
        ptrdiff_t Allocate(size_t size, size_t alignment) NN_NOEXCEPT;

        //! @brief  Returns the maximum number of history entries that this object can record.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @return  Returns the maximum number of history entries that this object can record.
        //! @details
        //!  This function is thread-safe.
        int GetHistoryLengthMax() const NN_NOEXCEPT;

        //! @brief  Returns the number of history entries that this object has currently recorded.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @return  Returns the number of history entries that this object has currently recorded.
        //! @details
        //!  The history is incremented by 1 when <tt>End()</tt> is called.
        //!  The history is decremented by 1 when <tt>Free()</tt> is called.
        //!  If this function returns the same value as <tt>GetHistoryLengthMax()</tt>, <tt>Begin()</tt> will fail.
        //!  This function is thread-safe.
        int GetHistoryLength() const NN_NOEXCEPT;

        //! @brief  Enters the history for the 0th allocation.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>false</tt>.
        //! @post  <tt>GetHistoryLength()</tt> == <tt>GetHistoryLengthMax()</tt>.
        //! @details
        //!  Adds to the history for the 0th allocation until the history is full.
        //!  Equivalent to the following code.
        //!
        //! @code
        //!  TransientMemoryPoolAllocator transient;
        //!  while(transient.GetHistoryLength() < transient.GetHistoryLengthMax())
        //! {
        //!  transient.Begin();
        //!  transient.End();
        //! }
        //! @endcode
        //!
        //!  A history added with this function will be recorded as a newer history when a history has already been recorded.
        //!  Calling this instance for the same instance is not thread-safe.
        void FillHistory() NN_NOEXCEPT;

    private:
        nn::gfx::MemoryPool* m_pMemoryPool;
        detail::OffsetRingBuffer m_OffsetRingBuffer;
        ptrdiff_t m_AllocatableAlignmentMax;

        detail::OffsetRange* m_pHistory;
        size_t m_HistoryMemorySize;
        int m_HistoryRingSize;
        int m_HistoryHead;
        int m_HistoryTail;

        bool m_IsInitialized;
    };

}}}
