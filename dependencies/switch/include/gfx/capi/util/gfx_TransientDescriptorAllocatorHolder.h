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
#include "gfx_TransientDescriptorAllocator.h"

namespace nn{ namespace gfx{ namespace util{

    //! @brief  Class that wraps <tt>TransientDescriptorAllocator</tt> and the memory block needed for its initialization and creates an object.
    //! @tparam THistoryLengthMax  The maximum number of <tt>TransientDescriptorAllocator</tt> history entries to record.
    //! @see  <tt>TransientDescriptorAllocator</tt>
    template<int THistoryLengthMax>
    class TransientDescriptorAllocatorHolder
    {
        NN_DISALLOW_COPY(TransientDescriptorAllocatorHolder);

    public:

        //! @brief  The maximum number of <tt>TransientDescriptorAllocator</tt> history entries that will be created.
        static const int HistoryLengthMax = THistoryLengthMax;

    public:

        //! @brief  Instantiates an object with default parameters (default constructor).
        TransientDescriptorAllocatorHolder() NN_NOEXCEPT
        {
        }

        //! @brief  Initializes the <tt>TransientDescriptorAllocator</tt> instance that will be wrapped with this object.
        //! @param[in] pDescriptorPool  The descriptor pool.
        //! @param[in] baseSlotIndex  The index of the start of the descriptor slot to use.
        //! @param[in] slotCount  The number of descriptor slots to use.
        //! @pre  This object must be uninitialized.
        //! @pre  The preconditions for each parameter are the same as those for <tt>TransientDescriptorAllocator::Initialize()</tt>.
        //! @post  This object is initialized.
        //! @see  <tt>TransientDescriptorAllocator::Initialize()</tt>
        //! @details
        //!  Initializes an instance of <tt>TransientDescriptorAllocator</tt>, to be wrapped by this object using the specified parameters.
        //!  The memory region wrapped in this object is used for the memory block to use for initialization.
        //!  <tt>HistoryLengthMax</tt> can specify the maximum number of history entries.
        //!  Calling this instance for the same instance is not thread-safe.
        void Initialize(
            nn::gfx::DescriptorPool* pDescriptorPool,
            int baseSlotIndex,
            int slotCount
            ) NN_NOEXCEPT
        {
            NN_SDK_REQUIRES(!m_Instance.IsInitialized());
            NN_SDK_ASSERT_EQUAL(sizeof(m_Memory), m_Instance.GetRequiredMemorySize(THistoryLengthMax));
            NN_SDK_ASSERT_GREATER_EQUAL(NN_ALIGNOF(detail::IndexRange), m_Instance.GetRequiredMemoryAlignment());
            m_Instance.SetMemory(&m_Memory[0], sizeof(m_Memory));
            m_Instance.Initialize(pDescriptorPool, baseSlotIndex, slotCount, THistoryLengthMax);
        }

        //! @brief  Frees <tt>TransientDescriptorAllocator</tt>, which is wrapped with this object.
        //! @pre  This object must be initialized.
        //! @post  This object is uninitialized.
        //! @details
        //!  Calling this instance for the same instance is not thread-safe.
        void Finalize() NN_NOEXCEPT
        {
            NN_SDK_REQUIRES(m_Instance.IsInitialized());
            m_Instance.Finalize();
        }

        //! @brief  Gets <tt>TransientDescriptorAllocator</tt>, which is wrapped by this object.
        //! @return  Returns a pointer to <tt>TransientDescriptorAllocator</tt>, which is wrapped by this object.
        //! @details
        //!  The initialization and destruction of the obtained <tt>TransientDescriptorAllocator</tt> occurs with the <tt>Initialize()</tt> and <tt>Finalize()</tt> functions for this object.
        //!  The lifetime of the obtained <tt>TransientDescriptorAllocator</tt> is the same as the lifetime for this object.
        //!  This function is thread-safe.
        TransientDescriptorAllocator* Get() NN_NOEXCEPT
        {
            return &m_Instance;
        }

        //! @brief  Gets <tt>TransientDescriptorAllocator</tt>, which is wrapped by this object.
        //! @return  Returns a pointer to <tt>TransientDescriptorAllocator</tt>, which is wrapped by this object.
        //! @details
        //!  The initialization and destruction of the obtained <tt>TransientDescriptorAllocator</tt> occurs with the <tt>Initialize()</tt> and <tt>Finalize()</tt> functions for this object.
        //!  The lifetime of the obtained <tt>TransientDescriptorAllocator</tt> is the same as the lifetime for this object.
        //!  This function is thread-safe.
        const TransientDescriptorAllocator* Get() const NN_NOEXCEPT
        {
            return &m_Instance;
        }

    private:
        TransientDescriptorAllocator m_Instance;
        detail::IndexRange m_Memory[THistoryLengthMax + 1];
    };

}}}
