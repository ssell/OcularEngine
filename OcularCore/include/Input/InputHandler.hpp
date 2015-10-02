/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __H__OCULAR_INPUT_INPUT_HANDLER__H__
#define __H__OCULAR_INPUT_INPUT_HANDLER__H__

#include "Keys.hpp"
#include "Math/Vector2.hpp"

#include <array>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class InputHandler
         *
         * Receives all low-level system input messages regarding the keyboard 
         * and mouse devices, and generates appropriate input events off of them.
         *
         * Also allows for any-time querying of the state of the input devices.
         *
         * All input is buffered. This means that the input events are only created
         * at specific durations (default once every 20ms) in order to reduce event
         * load and to filter out extraneous input.
         */
        class InputHandler
        {
        public:

            InputHandler();
            ~InputHandler();

            /**
             * If enough time has elapsed, the keyboard and mouse states are checked.
             * Input events are generated if any keys or buttons have been changed.
             */
            void update();

            /**
             * Sets the amount of time, in sec, to wait inbetween input event triggers.
             * The default buffer time is 20ms (0.02f), or at a rate of 50FPS.
             *
             * \param[in] time Time in seconds.
             */
            void setBufferTime(float time);

            //------------------------------------------------------------
            // Trigger Methods

            /**
             * Triggers the specified keyboard key down. 
             * 
             * Typically used by the low-level input readers, 
             * but can also be used to simulate a key press if needed.
             *
             * \param[in] key The keyboard key to trigger. See Ocular::Core::KeyboardKeys
             */
            void triggerKeyboardKeyDown(KeyboardKeys key);

            /**
             * Triggers the specified mouse button down.
             *
             * Typically used by the low-level input readers,
             * but can also be used to simulate a button press if needed.
             *
             * \param[in] button The mouse button to trigger. See Ocular::Core::MouseButtons
             */
            void triggerMouseButtonDown(MouseButtons button);

            /**
             * Triggers the specified keyboard key up.
             *
             * Typically used by the low-level input readers,
             * but can also be used to simulate a key release if needed.
             *
             * \param[in] key The keyboard key to trigger. See Ocular::Core::KeyboardKeys
             */
            void triggerKeyboardKeyUp(KeyboardKeys key);

            /**
             * Triggers the specified mouse button up.
             *
             * Typically used by the low-level input readers,
             * but can also be used to simulate a button release if needed.
             *
             * \param[in] button The mouse button to trigger. See Ocular::Core::MouseButtons
             */
            void triggerMouseButtonUp(MouseButtons button);

            /**
             * Sets the mouse position.
             *
             * Typically used by the low-level input readers,
             * but can also be used to simulate mouse movement if needed.
             *
             * \param[in] position New mouse position.
             */
            void setMousePosition(Math::Vector2f const& position);

            //------------------------------------------------------------
            // Query Methods

            /**
             * Retrieves the current mouse position in window coordinates. 
             * \param[in] queryLatest Queries the absolutest latest mouse position which may be 'unstable'.
             */
            Math::Vector2f const& getMousePosition(bool queryLatest = false) const;

            /**
             * Checks if the specified keyboard key is down.
             * See Ocular::Core::KeyboardKeys for supported keys to query.
             *
             * \param[in] key         Which key to check the state of.
             * \param[in] queryLatest Queries the absolutest latest key state which may be 'unstable'.

             * \return TRUE if the key is currently down and has not yet been released.
             */
            bool isKeyboardKeyDown(KeyboardKeys key, bool queryLatest = false) const;

            /**
             * Checks if the specified mouse key is down.
             * See Ocular::Core::MouseButtons for supported keys to query.
             *
             * \param[in] button      Which key to check the state of.
             * \param[in] queryLatest Queries the absolutest latest button state which may be 'unstable'.

             * \return TRUE if the key is currently down and has not yet been released.
             */
            bool isMouseButtonDown(MouseButtons button, bool queryLatest = false) const;

            /**
             * Checks if the left shift keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::ShiftLeft);
             *
             * \param[in] queryLatest Queries the absolutest latest key state which may be 'unstable'.
             * \return TRUE if they left shift key is currently down and has not yet been released.
             */
            bool isLeftShiftDown(bool queryLatest = false) const;

            /**
             * Checks if the right shift keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::ShiftRight);
             *
             * \param[in] queryLatest Queries the absolutest latest key state which may be 'unstable'.
             * \return TRUE if they right shift key is currently down and has not yet been released.
             */
            bool isRightShiftDown(bool queryLatest = false) const;

            /**
             * Checks if the left ctrl keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::CtrlLeft);
             *
             * \param[in] queryLatest Queries the absolutest latest key state which may be 'unstable'.
             * \return TRUE if they left ctrl key is currently down and has not yet been released.
             */
            bool isLeftCtrlDown(bool queryLatest = false) const;

            /**
             * Checks if the right ctrl keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::CtrlRight);
             *
             * \param[in] queryLatest Queries the absolutest latest key state which may be 'unstable'.
             * \return TRUE if they right ctrl key is currently down and has not yet been released.
             */
            bool isRightCtrlDown(bool queryLatest = false) const;

            /**
             * Checks if the left alt keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::AltLeft);
             *
             * \param[in] queryLatest Queries the absolutest latest key state which may be 'unstable'.
             * \return TRUE if they left alt key is currently down and has not yet been released.
             */
            bool isLeftAltDown(bool queryLatest = false) const;

            /**
             * Checks if the right alt keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::AltRight);
             *
             * \param[in] queryLatest Queries the absolutest latest key state which may be 'unstable'.
             * \return TRUE if they right alt key is currently down and has not yet been released.
             */
            bool isRightAltDown(bool queryLatest = false) const;

            /**
             * Checks if the left mouse button is down.
             * Convenience method that works identically to:
             *
             *    isMouseButtonDown(MouseButtons::Left);
             *
             * \param[in] queryLatest Queries the absolutest latest button state which may be 'unstable'.
             * \return TRUE if the left mouse key is currently down and has not yet been released.
             */
            bool isLeftMouseDown(bool queryLatest = false) const;

            /**
             * Checks if the right mouse button is down.
             * Convenience method that works identically to:
             *
             *    isMouseButtonDown(MouseButtons::Right);
             *
             * \param[in] queryLatest Queries the absolutest latest button state which may be 'unstable'.
             * \return TRUE if the right mouse key is currently down and has not yet been released.
             */
            bool isRightMouseDown(bool queryLatest = false) const;

        protected:

        private:

            void processKeyboardChanges();
            void processMouseChanges();

            /**
             * Handles conversion of keys when a shift key is held down.
             * \param[out] key Key to convert.
             */
            void shiftConvertKey(KeyboardKeys& key);

            /**
             * If a key is held down that requires shift, and shift is released,
             * then that key should be released and the non-shifted version should
             * be pressed down instead.
             *
             * For example, if one holds down shift and '5', then the '%' key will
             * be flagged as pressed down. But if the shift is released prior to the
             * other key, then the '%' should be released and '5' should be pressed.
             */
            void swapShiftSpecialKeys();

            //------------------------------------------------------------

            float m_BufferTime;
            float m_ElapsedTotal;
            
            // The current states are potentially updated multiple times a refresh 
            // period and are thus potentially unstable.

            // The previous states are the 'current official' state and are used when
            // a down query is made or an event is generated.

            std::array<bool, 255> m_KeyboardStateCurrent;     /// Current state of each keyboard key. If TRUE, the key is currently pressed down.
            std::array<bool, 255> m_KeyboardStatePrevious;    /// State of each keyboard key at last refresh. If TRUE, the key is currently pressed down.
            
            std::array<bool, 3>   m_MouseStateCurrent;        /// Current state of each mouse button. If TRUE, the button is currently pressed down.
            std::array<bool, 3>   m_MouseStatePrevious;       /// State of each mouse button at last refresh. If TRUE, the button is currently pressed down.

            Math::Vector2f m_MousePositionCurrent;
            Math::Vector2f m_MousePositionPrevious;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif