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
#include <nn/util/util_TypedStorage.h>
#include "gfx_TransientBufferAllocator.h"

namespace nn{ namespace gfx{ namespace util{

    //! @brief  Class that wraps <tt>TransientBufferAllocator</tt> and the memory block needed for its initialization, and creates an object.
    //! @tparam THistoryLengthMax  The maximum number of <tt>TransientBufferAllocator</tt> history entries to record.
    //! @see  TransientBufferAllocator
    template<int THistoryLengthMax>
    class TransientBufferAllocatorHolder
    {
        NN_DISALLOW_COPY(TransientBufferAllocatorHolder);

    public:

        //! @brief  The maximum number of <tt>TransientBufferAllocator</tt> history entries that will be created.
        static const int HistoryLengthMax = THistoryLengthMax;

    public:

        //!@ brief Gets a default constructor.
        TransientBufferAllocatorHolder() NN_NOEXCEPT
        {
        }

        //! @brief  Initializes <tt>TransientBufferAllocator</tt>, which will be wrapped with this object.
        //! @param[in] pBuffer  The buffer.
        //! @param[in] baseOffset  The start of the offset for the region to manage.
        //! @param[in] size  The size, in bytes, of the region to manage.
        //! @param[in] allocatableAlignmentMax  The maximum alignment required for the region allocated from this allocator.
        //! @pre  This object must be uninitialized.
        //! @pre  The preconditions for each parameter are the same as those for <tt>TransientBufferAllocator::Initialize()</tt>.
        //! @post  This object is initialized.
        //! @see  TransientBufferAllocator::Initialize()
        //! @details
        //!  Initializes an instance of <tt>TransientBufferAllocator</tt>, to be wrapped by this object using the specified parameters.
        //!  The memory region wrapped in this object is used for the memory block to use for initialization.
        //!  <tt>HistoryLengthMax</tt> can specify the maximum number of history entries.
        //!  Calling this instance for the same instance is not thread-safe.
        void Initialize(
            nn::gfx::Buffer* pBuffer,
            ptrdiff_t baseOffset,
            size_t size,
            size_t allocatableAlignmentMax
            ) NN_NOEXCEPT
        {
            NN_SDK_REQUIRES(!m_Instance.IsInitialized());
            NN_SDK_ASSERT_EQUAL(sizeof(m_Memory), m_Instance.GetRequiredMemorySize(THistoryLengthMax));
            NN_SDK_ASSERT_GREATER_EQUAL(NN_ALIGNOF(detail::OffsetRange), m_Instance.GetRequiredMemoryAlignment());
            m_Instance.SetMemory(&m_Memory[0], sizeof(m_Memory));
            m_Instance.Initialize(pBuffer, baseOffset, size, allocatableAlignmentMax, THistoryLengthMax);
        }

        //! @brief  Destroys <tt>TransientBufferAllocator</tt>, which is wrapped with this object.
        //! @pre  This object must be initialized.
        //! @post  This object is uninitialized.
        //! @details
        //!  Calling this instance for the same instance is not thread-safe.
        void Finalize() NN_NOEXCEPT
        {
            NN_SDK_REQUIRES(m_Instance.IsInitialized());
            m_Instance.Finalize();
        }

        //! @brief  Gets <tt>TransientBufferAllocator</tt>, which is wrapped by this object.
        //! @return  Returns a pointer to <tt>TransientBufferAllocator</tt>, which is wrapped by this object.
        //! @details
        //!  The initialization and destruction of the obtained <tt>TransientBufferAllocator</tt> occurs with the <tt>Initialize()</tt> and <tt>Finalize()</tt> functions for this object.
        //!  The lifetime of the obtained <tt>TransientBufferAllocator</tt> is the same as the lifetime for this object.
        //!  This function is thread-safe.
        TransientBufferAllocator* Get() NN_NOEXCEPT
        {
            return &m_Instance;
        }

        //! @brief  Gets <tt>TransientBufferAllocator</tt>, which is wrapped by this object.
        //! @return  Returns a pointer to <tt>TransientBufferAllocator</tt>, which is wrapped by this object.
        //! @details
        //!  The initialization and destruction of the obtained <tt>TransientBufferAllocator</tt> occurs with the <tt>Initialize()</tt> and <tt>Finalize()</tt> functions for this object.
        //!  The lifetime of the obtained <tt>TransientBufferAllocator</tt> is the same as the lifetime for this object.
        //!  This function is thread-safe.
        const TransientBufferAllocator* Get() const NN_NOEXCEPT
        {
            return &m_Instance;
        }

    private:
        TransientBufferAllocator m_Instance;
        detail::OffsetRange m_Memory[THistoryLengthMax + 1];
    };

}}}
