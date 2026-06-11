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

#include "detail/gfx_IndexRange.h"
#include "detail/gfx_IndexRingBuffer.h"

namespace nn{ namespace gfx{ namespace util{

    //! @brief  The descriptor pool that manages the descriptor slots for temporary use.
    //! @details
    //!  Dynamically allocates the descriptor slots that are temporarily used during rendering.
    //!  Also provides a feature to deallocate all slots at the same time after rendering completes.
    class TransientDescriptorAllocator
    {
        NN_DISALLOW_COPY(TransientDescriptorAllocator);

    public:
        //! @brief  The maximum number of slots that can be managed with this class.
        static const int SlotCountMax = detail::IndexRingBuffer::IndexCountMax;

        //! @brief  Represents an invalid index.
        //! @details
        //!  This value is returned if the allocation of a descriptor slot index failed.
        static const int InvalidIndex = detail::IndexRingBuffer::InvalidIndex;
    public:
        //! @brief  Instantiates an object with default parameters (default constructor).
        TransientDescriptorAllocator() NN_NOEXCEPT;

        //! @brief  Specifies the descriptor pool and the range of slots, and then initializes.
        //! @param[in] pDescriptorPool  The descriptor pool.
        //! @param[in] baseSlotIndex  The index of the start of the descriptor slot to use.
        //! @param[in] slotCount  The number of descriptor slots to use.
        //! @param[in] historyLengthMax  The maximum number of history entries to record.
        //! @pre  <tt>IsInitialized()</tt> == <tt>false</tt>.
        //! @pre  <tt><var>pDescriptorPool</var></tt> must be a pointer to a valid descriptor pool.
        //! @pre  <tt><var>baseSlotIndex</var></tt> >= <tt>0</tt>.
        //! @pre  <tt><var>slotCount</var></tt> >= <tt>1</tt> && <tt><var>slotCount</var></tt> <= <tt>SlotCountMax</tt>.
        //! @pre  <tt><var>historyLengthMax</var></tt> >= <tt>1</tt>.
        //! @pre  There must be a memory block configured to have the required alignment size, set with <tt>SetMemory()</tt>.
        //! @post  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @post  <tt>IsRecording()</tt> == <tt>false</tt>.
        //! @post  <tt>GetHistoryLength()</tt> == <tt>0</tt>.
        //! @details
        //!  This object targets the range of slots specified in the descriptor pool for management.
        //!  A contiguous valid range must be specified for the slots.
        //!  Calling this instance for the same instance is not thread-safe.
        void Initialize(
            nn::gfx::DescriptorPool* pDescriptorPool,
            int baseSlotIndex,
            int slotCount,
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

        //! @brief  Determines whether acquisition of the descriptor slots from this object has started.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @return  Returns <tt>true</tt> when acquisition has started. Returns <tt>false</tt> otherwise.
        //! @details
        //!  Success for <tt>Begin()</tt> triggers the start of slot acquisition.
        //!  <tt>End()</tt> triggers the end of slot acquisition.
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

        //! @brief  Begins getting descriptor slots.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>false</tt>.
        //! @pre  <tt>GetHistoryLength()</tt> < <tt>GetHistoryLengthMax()</tt>.
        //! @post  <tt>IsRecording()</tt> == <tt>true</tt>.
        //! @details
        //!  Calling this instance for the same instance is not thread-safe.
        void Begin() NN_NOEXCEPT;

        //! @brief  Ends descriptor slot acquisition.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>true</tt>.
        //! @post  <tt>IsRecording()</tt> == <tt>false</tt>.
        //! @post  The range of descriptor slots obtained between calls to the immediately prior <tt>Begin()</tt> function and the <tt>End()</tt> function is recorded.
        //! @post  The value returned by <tt>GetHistoryLength()</tt> is incremented by 1.
        //! @details
        //!  The history is recorded even when there are no slots obtained between calls to the immediately prior <tt>Begin()</tt> function and the <tt>End()</tt> function.
        //!  Calling this instance for the same instance is not thread-safe.
        //!  Free()
        void End() NN_NOEXCEPT;

        //! @brief  Releases the oldest recorded descriptor slot from among those recorded by this object.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>GetHistoryLength()</tt> > <tt>0</tt>.
        //! @post  Releases the oldest descriptor slot recorded in the history.
        //! @post  The value returned by <tt>GetHistoryLength()</tt> is decremented by 1.
        //! @details
        //!  Release of the slots occurs one at a time in the interval between calls to <tt>Begin()</tt> and <tt>End()</tt>.
        //!  The slots obtained individually using <tt>Allocate()</tt> cannot be released on an individual basis.
        //!  Any released slots becomes immediately available for acquisition.
        //!  Multiply calling this instance for the same instance is not thread-safe.
        //!  Calling both this function for the same instance and the function that acquires slots at the same time is thread-safe.
        //!  End()
        void Free() NN_NOEXCEPT;

        //! @brief  Reacquires one descriptor slot.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>true</tt>.
        //! @return  Returns an index for the newly acquired descriptor slot.
        //!  Returns <tt>InvalidIndex</tt> when descriptor slot acquisition fails.
        //! @details
        //!  This function is thread-safe.
        //!  Can be called simultaneously with other functions that acquire or release slots.
        int Allocate() NN_NOEXCEPT;

        //! @brief  Reacquires contiguous descriptor slots.
        //! @param[in] count  The number of descriptor slots to acquire.
        //! @pre  <tt>IsInitialized()</tt> == <tt>true</tt>.
        //! @pre  <tt>IsRecording()</tt> == <tt>true</tt>.
        //! @pre  <tt><var>count</var></tt> >= <tt>0</tt>.
        //! @return  Returns an index for the start of the newly acquired descriptor slots.
        //!  Returns <tt>InvalidIndex</tt> when descriptor slot acquisition fails.
        //! @details
        //!  <tt>InvalidIndex</tt> is returned when <tt><var>count</var></tt> == <tt>0</tt>.
        //!  This function is thread-safe.
        //!  Can be called simultaneously with other functions that acquire or release slots.
        int Allocate(int count) NN_NOEXCEPT;

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
        //!  TransientDescriptorAllocator transient;
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
        nn::gfx::DescriptorPool* m_pDescriptorPool;
        detail::IndexRingBuffer m_SlotIndexRingBuffer;

        detail::IndexRange* m_pHistory;
        size_t m_HistoryMemorySize;
        int m_HistoryRingSize;
        int m_HistoryHead;
        int m_HistoryTail;

        bool m_IsInitialized;
    };

}}}
