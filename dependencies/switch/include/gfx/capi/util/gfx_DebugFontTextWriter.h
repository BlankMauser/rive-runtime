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
#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/util/util_Vector.h>

#if defined(NN_GFX_UTIL_DEBUGFONT_USE_DEFAULT_LOCALE_CHARSET) && defined(NN_BUILD_CONFIG_OS_WIN)
#define NN_GFX_UTIL_DEBUGFONT_USE_DEFAULT_LOCALE_CHARSET_VALUE true
#else
#define NN_GFX_UTIL_DEBUGFONT_USE_DEFAULT_LOCALE_CHARSET_VALUE false
#endif


namespace nn {
namespace gfx {
namespace util {

namespace detail {
class DebugFontTextWriterImpl;
} // namespace detail

//------------------------------------------------------------------------------
//! @brief  The class representing the information for initializing the class for rendering the debug font.
//------------------------------------------------------------------------------
class DebugFontTextWriterInfo
{
    NN_DISALLOW_COPY(DebugFontTextWriterInfo);

public:

/**
* @brief  Constructor.
*
* @post
*  - Each parameter is initialized to the default value.
*/
    DebugFontTextWriterInfo() NN_NOEXCEPT
    {
        this->SetDefault();
    }

/**
* @brief  Helper function to set each parameter to the default value.
*
* @details
*  The values that are set are not the same as zero-initialization.
*/
    void SetDefault() NN_NOEXCEPT
    {
        this->SetCharCountMax(1024);
        this->SetBufferCount(2);
        this->SetUserMemoryPoolEnabled(false);
    }

/**
* @brief  Sets the maximum number of characters that can be displayed at one time.
*
* @param[in] charCountMax  The maximum number of characters that can be displayed at one time.
*/
    void SetCharCountMax(int charCountMax) NN_NOEXCEPT
    {
        this->m_CharCountMax = charCountMax;
    }

/**
* @brief  Gets the maximum number of characters that can be displayed at one time.
*
* @return  The maximum number of characters that can be displayed at one time.
*/
    int GetCharCountMax() const NN_NOEXCEPT
    {
        return this->m_CharCountMax;
    }

/**
* @brief  Sets the number of buffers for multi-buffering.
*
* @param[in] bufferCount  The number of buffers for multi-buffering.
*/
    void SetBufferCount(int bufferCount) NN_NOEXCEPT
    {
        this->m_BufferCount = bufferCount;
    }

/**
* @brief  Gets the number of buffers for multi-buffering.
*
* @return  Returns the number of buffers for multi-buffering.
*/
    int GetBufferCount() const NN_NOEXCEPT
    {
        return this->m_BufferCount;
    }

/**
* @brief  Sets whether to use a memory pool from the user.
*
* @param[in] value  Boolean value indicating whether to use a memory pool from the user.
*/
    void SetUserMemoryPoolEnabled(bool value) NN_NOEXCEPT
    {
        this->m_Flag.SetBit(Flag_UserMemoryPoolEnable, value);
    }

/**
* @brief  Determines whether to use a memory pool from the user.
*
* @return  Returns the Boolean value indicating whether to use a memory pool from the user.
*/
    bool IsUserMemoryPoolEnabled() const NN_NOEXCEPT
    {
        return this->m_Flag.GetBit(Flag_UserMemoryPoolEnable);
    }

private:
    enum Flag
    {
        Flag_UserMemoryPoolEnable,
    };

    int m_CharCountMax;               //!<  The maximum number of characters that can be displayed at one time.
    int m_BufferCount;                //!<  The number of multi-buffers for the buffer that will be created.
    nn::util::BitPack16 m_Flag;       //!<  The flags.
    NN_PADDING2;
};

//------------------------------------------------------------------------------
//! @brief  The class for rendering the debug font.
//------------------------------------------------------------------------------
class DebugFontTextWriter
{
    NN_DISALLOW_COPY(DebugFontTextWriter);

public:
    // Constructor.
    DebugFontTextWriter() NN_NOEXCEPT;

    // Destructor.
    virtual ~DebugFontTextWriter() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the size of the memory that is required.
    //! @param[in] pDevice  Device.
    //! @param[in] info  Information for initialization purposes.
    //! @return  Returns the size of the memory that is required, in bytes.
    //---------------------------------------------------------------------------
    static size_t GetRequiredMemorySize(
        nn::gfx::Device* pDevice,
        const DebugFontTextWriterInfo &info
    ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the size of the memory pool that is required.
    //! @param[in] pDevice  Device.
    //! @param[in] info  Information for initialization purposes.
    //! @return  Returns the size of the memory pool that is required, in bytes.
    //---------------------------------------------------------------------------
    static size_t GetRequiredMemoryPoolSize(
        nn::gfx::Device* pDevice,
        const DebugFontTextWriterInfo &info
    ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Initializes.
    //! @param[in] pDevice  Device.
    //! @param[in] info  Information for initialization purposes.
    //! @param[in] pMemory  A pointer to the memory that this class will use.
    //! @param[in] memorySize  The size of memory that this class will use.
    //! @param[in] pMemoryPool  Pointer to the memory pool where the buffer will be placed.
    //! @param[in] memoryPoolOffset  Offset, in bytes, to the memory pool where the buffer will be placed.
    //! @param[in] memoryPoolSize  Size of the memory pool the buffer will use, in bytes.
    //---------------------------------------------------------------------------
    void Initialize(
        nn::gfx::Device* pDevice,
        const DebugFontTextWriterInfo& info,
        void* pMemory,
        size_t memorySize,
        nn::gfx::MemoryPool* pMemoryPool,
        ptrdiff_t memoryPoolOffset,
        size_t memoryPoolSize
    ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Finalizes the instance.
    //---------------------------------------------------------------------------
    void Finalize() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this object is initialized.
    //! @return  Returns <tt>true</tt> when initialized. Returns <tt>false</tt> otherwise.
    //! @details
    //!  Becomes initialized, using <tt>Initialize()</tt>.
    //!  Becomes uninitialized, using <tt>Finalize()</tt>.
    //---------------------------------------------------------------------------
    bool IsInitialized() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the maximum number of characters that can be displayed at one time.
    //! @return  The maximum number of characters that can be displayed at one time.
    //---------------------------------------------------------------------------
    int GetCharCountMax() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the number of buffers for multi-buffering.
    //! @return  Returns the number of buffers for multi-buffering.
    //---------------------------------------------------------------------------
    int GetBufferCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets whether to use a memory pool from the user.
    //! @return  Specify <tt>true</tt> if using a memory pool from the user, or <tt>false</tt> otherwise.
    //---------------------------------------------------------------------------
    bool IsUserMemoryPoolEnabled() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the memory used in this class.
    //! @return  Returns the memory used by this class.
    //---------------------------------------------------------------------------
    void* GetMemory() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets a memory pool from the user.
    //! @return  If using a memory pool from the user, returns the memory pool. Otherwise, returns <tt>nullptr</tt>.
    //---------------------------------------------------------------------------
    nn::gfx::MemoryPool* GetMemoryPool() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the offset at the start of the memory pool from the user.
    //! @return  If using a memory pool from the user, returns the offset at the start of the memory pool. Otherwise, returns 0.
    //---------------------------------------------------------------------------
    ptrdiff_t GetMemoryPoolOffset() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the display width.
    //! @param[in] displayWidth  The display width.
    //---------------------------------------------------------------------------
    void SetDisplayWidth(int displayWidth) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the display height.
    //! @param[in] displayHeight  The display height.
    //---------------------------------------------------------------------------
    void SetDisplayHeight(int displayHeight) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the texture descriptor.
    //! @param[in] pTextureDescriptorPool  The texture descriptor pool.
    //! @param[in] textureDescriptorIndexSlot  The texture descriptor slot number.
    //---------------------------------------------------------------------------
    void SetTextureDescriptor(nn::gfx::DescriptorPool* pTextureDescriptorPool, int textureDescriptorIndexSlot) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the texture descriptor slot number.
    //! @return  Returns the texture descriptor slot number.
    //---------------------------------------------------------------------------
    int GetTextureDescriptorIndexSlot() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the sampler descriptor.
    //! @param[in] pSamplerDescriptorPool  The sampler descriptor pool.
    //! @param[in] samplerDescriptorIndexSlot  The sampler descriptor slot number.
    //---------------------------------------------------------------------------
    void SetSamplerDescriptor(nn::gfx::DescriptorPool* pSamplerDescriptorPool, int samplerDescriptorIndexSlot) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the sampler descriptor slot number.
    //! @return  Returns the sampler descriptor slot number.
    //---------------------------------------------------------------------------
    int GetSamplerDescriptorIndexSlot() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the height of a line.
    //! @param[in] height  New line height.
    //---------------------------------------------------------------------------
    void SetLineHeight(float height) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the height of a line.
    //! @return  Returns the height of a line.
    //---------------------------------------------------------------------------
    float GetLineHeight() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the tab width.
    //! @param[in] tabWidth  Tab width in terms of character count.
    //---------------------------------------------------------------------------
    void SetTabWidth(int tabWidth) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the tab width.
    //! @return  Returns the tab width in terms of the character count.
    //---------------------------------------------------------------------------
    int GetTabWidth() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the magnification factor to use for a character.
    //! @param[in] hScale  Horizontal scaling factor.
    //! @param[in] vScale  Vertical scaling factor.
    //---------------------------------------------------------------------------
    void SetScale(float hScale, float vScale) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the magnification factor for the horizontal axis of the character.
    //! @return  Returns the magnification factor for the horizontal axis of the character.
    //---------------------------------------------------------------------------
    float GetScaleX() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the magnification factor for the vertical axis of the character.
    //! @return  Returns the magnification factor for the vertical axis of the character.
    //---------------------------------------------------------------------------
    float GetScaleY() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the character size.
    //! @param[in] width  The width of the cell after magnification.
    //! @param[in] height  The height of the cell after magnification.
    //---------------------------------------------------------------------------
    void SetFontSize(float width, float height) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the character size.
    //! @param[in] height  The height of the cell after magnification.
    //---------------------------------------------------------------------------
    void SetFontSize(float height) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the cell width after applying magnification.
    //! @return  Returns the cell width in pixels after magnification.
    //---------------------------------------------------------------------------
    float GetFontWidth() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the cell height after magnification.
    //! @return  Returns the cell height in pixels after magnification.
    //---------------------------------------------------------------------------
    float GetFontHeight() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the cursor position to the specified coordinate. The screen coordinates are described in a coordinate system where (0,0) defines the upper-left corner, x is positive in the right direction, and y is positive in the down direction.
    //! @param[in] x  The new x-coordinate of the cursor.
    //! @param[in] y  The new y-coordinate of the cursor.
    //---------------------------------------------------------------------------
    void SetCursor(float x, float y) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the cursor's x-coordinate.
    //! @param[in] x  The new x-coordinate of the cursor.
    //---------------------------------------------------------------------------
    void SetCursorX(float x) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the cursor's y-coordinate.
    //! @param[in] y  The new y-coordinate of the cursor.
    //---------------------------------------------------------------------------
    void SetCursorY(float y) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the cursor's x-coordinate.
    //! @return  Returns the x-coordinate of the cursor.
    //---------------------------------------------------------------------------
    float GetCursorX() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the y-coordinate of the cursor.
    //! @return  Returns the y-coordinate of the cursor.
    //---------------------------------------------------------------------------
    float GetCursorY() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the character color.
    //! @param[in] color  Character color.
    //---------------------------------------------------------------------------
    void SetTextColor(const nn::util::Color4u8Type& color) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the text character color.
    //! @return  Returns the text character color.
    //---------------------------------------------------------------------------
    const nn::util::Color4u8Type& GetTextColor() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Draws a string. The length of the string that can be specified is 1,024 characters (including the null terminator), and strings longer than 1,024 characters are discarded for display.
    //! @param[in] format  The format string.
    //! @param[in] ...  The format string parameters.
    //---------------------------------------------------------------------------
    void Print(const char* format, ...) NN_NOEXCEPT
    {
        std::va_list list;
        va_start(list, format);
        VPrintUtf8(NN_GFX_UTIL_DEBUGFONT_USE_DEFAULT_LOCALE_CHARSET_VALUE, format, list);
        va_end(list);
    }

    //---------------------------------------------------------------------------
    //! @brief  Draws.
    //! @param[in] pCommandBuffer  Command buffer.
    //---------------------------------------------------------------------------
    void Draw(nn::gfx::CommandBuffer* pCommandBuffer) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Setting to draw fixed-width characters.
    //! @param[in] isFixed  Specify <tt>true</tt> to draw fixed-width characters.
    //---------------------------------------------------------------------------
    void SetFixedWidthEnabled(bool isFixed) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets whether to draw fixed-width characters.
    //! @return  Returns <tt>true</tt> if characters are to be forcibly drawn at fixed width, or <tt>false</tt> otherwise.
    //---------------------------------------------------------------------------
    bool IsFixedWidthEnabled() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the character width to use when drawing fixed-width characters.
    //! @param[in] width  New drawing width for monospace characters.
    //---------------------------------------------------------------------------
    void SetFixedWidth(float width) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the character width to use when drawing fixed-width characters.
    //! @return  Returns the character width of the forced fixed-width drawing.
    //---------------------------------------------------------------------------
    float GetFixedWidth() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the width of a string.
    //! @param[in] format  The format string.
    //! @param[in] ...  The format string parameters.
    //! @return  Returns the width of the string.
    //---------------------------------------------------------------------------
    float CalculateStringWidth(const char* format, ...) NN_NOEXCEPT
    {
        std::va_list list;
        va_start(list, format);
        float width, height;
        VCalculateFormatStringWidthHeightUtf8(width, height, NN_GFX_UTIL_DEBUGFONT_USE_DEFAULT_LOCALE_CHARSET_VALUE, format, list);
        va_end(list);
        return width;
    }

    //---------------------------------------------------------------------------
    //! @brief  Calculates the height of the string.
    //! @param[in] format  The format string.
    //! @param[in] ...  The format string parameters.
    //! @return  Returns the height of the string.
    //---------------------------------------------------------------------------
    float CalculateStringHeight(const char* format, ...) NN_NOEXCEPT
    {
        std::va_list list;
        va_start(list, format);
        float width, height;
        VCalculateFormatStringWidthHeightUtf8(width, height, NN_GFX_UTIL_DEBUGFONT_USE_DEFAULT_LOCALE_CHARSET_VALUE, format, list);
        va_end(list);
        return height;
    }

private:
    void VPrintUtf8(bool defaultLocaleCharset, const char* format, std::va_list formatArg) NN_NOEXCEPT;
    void VCalculateFormatStringWidthHeightUtf8(float& width, float& height, bool defaultLocaleCharset, const char* format, std::va_list formatArg) NN_NOEXCEPT;

    detail::DebugFontTextWriterImpl* m_pImpl;
    void* m_pMemory;
};


} // namespace util
} // namespace gfx
} // namespace nn
