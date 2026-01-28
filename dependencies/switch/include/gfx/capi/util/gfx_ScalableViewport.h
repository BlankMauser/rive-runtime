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

namespace nn { namespace gfx { namespace util {

/**
* @brief  The class that converts between two viewports.
*
* @details
*  This class may be used for dynamically changing the rendering resolution.
*/
    class ScalableViewport
    {
    public:

/**
* @brief  The enumerator that defines the origin of the window coordinates.
*/
        enum OriginMode
        {
            OriginMode_LowerLeft,
            OriginMode_UpperLeft,
            OriginMode_Count
        };

/**
* @brief  The class that defines the window coordinates.
*
* @details
*  <tt>nn::gfx::util::ScalableViewport</tt> manages virtual windows and physical windows, and performs conversion between viewports.
*/
        class WindowCoordinate
        {
        public:

/**
* @brief  Constructor.
*/
            WindowCoordinate() NN_NOEXCEPT
                : m_OriginMode(OriginMode_LowerLeft)
                , m_Width(0)
                , m_Height(0)
            {
            }

/**
* @brief  Sets the position of the origin.
* @param[in] originMode  The position of the origin.
*/
            void SetOriginMode(OriginMode originMode) NN_NOEXCEPT
            {
                m_OriginMode = originMode;
            }

/**
* @brief  Gets the position of the origin.
* @return  Returns the position of the origin.
*/
            OriginMode GetOriginMode() const NN_NOEXCEPT
            {
                return m_OriginMode;
            }

/**
* @brief  Sets the width of the window.
* @param[in] width  The width of the window.
*/
            void SetWidth(float width) NN_NOEXCEPT
            {
                m_Width = width;
            }

/**
* @brief  Gets the width of the window.
* @return  Returns the width of the window.
*/
            float GetWidth() const NN_NOEXCEPT
            {
                return m_Width;
            }

/**
* @brief  Sets the height of the window.
* @param[in] height  The height of the window.
*/
            void SetHeight(float height) NN_NOEXCEPT
            {
                m_Height = height;
            }

/**
* @brief  Gets the height of the window.
* @return  Returns the height of the window.
*/
            float GetHeight() const NN_NOEXCEPT
            {
                return m_Height;
            }

/**
* @brief  Sets the width and height of the window.
*
* @param[in] width  The width of the window.
* @param[in] height  The height of the window.
*
* @details
*  This function does the same thing as calling the following functions.
*  <tt>SetWidth(width);</tt>
*  <tt>SetHeight(height);</tt>
*/
            void SetSize(float width, float height) NN_NOEXCEPT
            {
                SetWidth(width);
                SetHeight(height);
            }

/**
* @brief  Determines whether valid values are set.
*
* @return  Returns <tt>true</tt> if valid values are set.
*
* @details
*  If <tt><var>m_Width</var></tt> > <tt>0</tt>, <tt><var>m_Height</var></tt> > <tt>0</tt>, and <tt><var>m_OriginMode</var></tt> is a value value, returns <tt>true</tt>.
*/
            bool IsValid() const NN_NOEXCEPT;

        private:
            OriginMode  m_OriginMode;
            float       m_Width;
            float       m_Height;
        };

/**
* @brief  The structure for specifying the viewport and scissor range.
*/
        struct Rect
        {
            float originX;  //! @brief  The x-coordinate of the origin.
            float originY;  //! @brief  The y-coordinate of the origin.
            float width;    //! @brief  The width.
            float height;   //! @brief  The length.
        };

/**
* @brief  Constructor.
*/
        ScalableViewport() NN_NOEXCEPT
            : m_IsInitialized(false)
        {
        }

/**
* @brief  Initializes.
*
* @param[in] virtualWindowCoordinate  The virtual window coordinates to set.
* @param[in] physicalWindowCoordinate  The physical window coordinates to set.
*
* @pre
*  - ! <tt>IsInitialized()</tt>
*  - <tt><var>virtualWindowCoordinate</var>.IsValid()</tt>
*  - <tt><var>physicalWindowCoordinate</var>.IsValid()</tt>
*
* @post
*  - <tt>IsInitialized()</tt>
*/
        void Initialize(const WindowCoordinate& virtualWindowCoordinate, const WindowCoordinate& physicalWindowCoordinate) NN_NOEXCEPT;

/**
* @brief  Finalizes.
*
* @pre  <tt>IsInitialized()</tt>
* @post  ! <tt>IsInitialized()</tt>
*
*/
        void Finalize() NN_NOEXCEPT;

/**
* @brief  Sets the virtual window coordinates.
*
* @param[in] virtualWindow  The virtual window coordinates to set.
*
* @pre
*  - <tt>IsInitialized()</tt>
*  - <tt><var>virtualWindow</var>.IsValid()</tt>
*/
        void SetVirtualWindowCoordinate(const WindowCoordinate& virtualWindow) NN_NOEXCEPT;

/**
* @brief  Gets the virtual window coordinate settings.
* @return  Returns a pointer to the address for the physical window coordinate settings.
*/
        const WindowCoordinate* GetVirtualWindowCoordinate() const NN_NOEXCEPT
        {
            return &m_VirtualWindow;
        }

/**
* @brief  Gets the physical window coordinate settings.
*
* @param[in] physicalWindow  The physical window coordinates to set.
*
* @pre
*  - <tt>IsInitialized()</tt>
*  - <tt><var>virtualWindow</var>.IsValid()</tt>
*/
        void SetPhysicalWindowCoordinate(const WindowCoordinate& physicalWindow) NN_NOEXCEPT;

/**
* @brief  Gets the physical window coordinate settings.
* @return  Returns a pointer to the address for the physical window coordinate settings.
*/
        const WindowCoordinate* GetPhysicalWindowCoordinate() const NN_NOEXCEPT
        {
            return &m_PhysicalWindow;
        }

/**
* @brief  Converts a point in the virtual window to a value in the physical window.
*
* @param[out] pOutPhysicalX  X-coordinate in the physical window.
* @param[out] pOutPhysicalY  Y-coordinate in the physical window.
* @param[in] virtualX  X-coordinate in the virtual window.
* @param[in] virtualY  Y-coordinate in the virtual window.
*
* @pre
*  - <tt>IsInitialized()</tt>
*/
        void ConvertPointVirtualToPhysical(float* pOutPhysicalX, float* pOutPhysicalY, float virtualX, float virtualY) const NN_NOEXCEPT;

/**
* @brief  Converts a point in the physical window to a value in the virtual window.
*
* @param[out] pOutVirtualX  X-coordinate in the virtual window.
* @param[out] pOutVirtualY  Y-coordinate in the virtual window.
* @param[in] physicalX  X-coordinate in the physical window.
* @param[in] physicalY  Y-coordinate in the physical window.
*
* @pre
*  - <tt>IsInitialized()</tt>
*/
        void ConvertPointPhysicalToVirtual(float* pOutVirtualX, float* pOutVirtualY, float physicalX, float physicalY) const NN_NOEXCEPT;

/**
* @brief  Converts the width and height in the virtual window to values in the physical window.
*
* @param[out] pOutPhysicalWidth  Width of the physical window.
* @param[out] pOutPhysicalHeight  Height of the physical window.
* @param[in] virtualWidth  Width of the virtual window.
* @param[in] virtualHeight  Height of the virtual window.
*
* @pre
*  - <tt>IsInitialized()</tt>
*/
        void ConvertLengthVirtualToPhysical(float* pOutPhysicalWidth, float* pOutPhysicalHeight, float virtualWidth, float virtualHeight) const NN_NOEXCEPT;

/**
* @brief  Converts the width and height in the physical window to values in the virtual window.
*
* @param[out] pOutVirtualWidth  Width of the virtual window.
* @param[out] pOutVirtualHeight  Height of the virtual window.
* @param[in] physicalWidth  Width of the physical window.
* @param[in] physicalHeight  Height of the physical window.
*
* @pre
*  - <tt>IsInitialized()</tt>
*/
        void ConvertLengthPhysicalToVirtual(float* pOutVirtualWidth, float* pOutVirtualHeight, float physicalWidth, float physicalHeight) const NN_NOEXCEPT;

/**
* @brief  Converts a rectangle in the virtual window to values in the physical window.
*
* @param[out] pOutPhysicalRect  Rectangle in the physical window.
* @param[in] virtualRect  Rectangle in the virtual window.
*
* @pre
*  - <tt>IsInitialized()</tt>
*  - <tt><var>pOutPhysicalRect</var></tt> != <tt>NULL</tt>.
*/
        void ConvertRectVirtualToPhysical(Rect* pOutPhysicalRect, const Rect& virtualRect) const NN_NOEXCEPT;

/**
* @brief  Converts a rectangle in the physical window to values in the virtual window.
*
* @param[out] pOutVirtualRect  Rectangle in the virtual window.
* @param[in] physicalRect  Rectangle in the physical window.
*
* @pre
*  - <tt>IsInitialized()</tt>
*  - <tt><var>pOutVirtualRect</var></tt> != <tt>NULL</tt>.
*/
        void ConvertRectPhysicalToVirtual(Rect* pOutVirtualRect, const Rect& physicalRect) const NN_NOEXCEPT;

/**
* @brief  Configures viewport settings based on the rectangle values.
*
* @param[out] pOutViewportStateInfo  Pointer to the viewport state for setting the values.
* @param[in] physicalRect  Rectangle on which the viewport state values are based.
*
* @details
*  - This function sets the coordinates of the origin and the width and height of the viewport.
*  - Note that depth settings are not configured.
*/
        void SetupViewportStateInfo(nn::gfx::ViewportStateInfo* pOutViewportStateInfo, const Rect& physicalRect) const NN_NOEXCEPT;

/**
* @brief  Sets the scissor state based on the rectangle values.
*
* @param[out] pOutScissorStateInfo  Pointer to the scissor state for which to set values.
* @param[in] physicalRect  Rectangle on which the scissor state values are based.
*
* @pre
*  - <tt><var>physicalRect</var>.originX</tt> >= <tt>0</tt>.
*  - <tt><var>physicalRect</var>.originY</tt> >= <tt>0</tt>.
*  - <tt><var>physicalRect</var>.width</tt> >= <tt>0</tt>.
*  - <tt><var>physicalRect</var>.height</tt> >= <tt>0</tt>.
*/
        void SetupScissorStateInfo(nn::gfx::ScissorStateInfo* pOutScissorStateInfo, const Rect& physicalRect) const NN_NOEXCEPT;

/**
* @brief  Sets values to the rectangle based on the viewport state values.
*
* @param[out] pOutRect  Pointer to the rectangle for which to set values.
* @param[in] viewportStateInfo  Viewport state on which the rectangle values are based.
*
* @pre
*  - <tt><var>pOutRect</var></tt> != <tt>NULL</tt>.
*/
        void SetupRectFromViewportStateInfo(Rect* pOutRect, const nn::gfx::ViewportStateInfo& viewportStateInfo) const NN_NOEXCEPT;

/**
* @brief  Sets values to the rectangle based on the scissor state values.
*
* @param[out] pOutRect  Pointer to the rectangle for which to set values.
* @param[in] scissorStateInfo  Scissor state on which the rectangle values are based.
*
* @pre
*  - <tt><var>pOutRect</var></tt> != <tt>NULL</tt>.
*/
        void SetupRectFromScissorStateInfo(Rect* pOutRect, const nn::gfx::ScissorStateInfo& scissorStateInfo) const NN_NOEXCEPT;

/**
* @brief  Determines whether initialized.
* @return  Returns whether initialized.
*/
        bool IsInitialized() const NN_NOEXCEPT
        {
            return m_IsInitialized;
        }

/**
* @brief  Gets the position of the origin of the physical window.
*
* @tparam TTarget  The target low-level API.
*
* @param[in] pDevice  Pointer for the device.
*
* @return  Returns the position of the origin of the physical window.
*
* @details
* - <tt><var>pDevice</var></tt> != <tt>NULL</tt>.
* - <tt>nn::gfx::IsInitialized(<var>*pDevice</var>)</tt>
*/
        template<typename TTarget>
        static OriginMode GetPhysicalWindowOriginMode(nn::gfx::TDevice<TTarget>* pDevice) NN_NOEXCEPT;

    private:
        WindowCoordinate    m_VirtualWindow;
        WindowCoordinate    m_PhysicalWindow;
        bool                m_IsInitialized;
    };

} } }
