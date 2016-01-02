/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
             *
             * \param[in] xDelta
             * \param[in] yDelta
             */
            void triggerMouseMoveDelta(Math::Vector2i const& delta);

            /**
             * Sets the mouse position.
             *
             * Typically used by the low-level input readers,
             * but can also be used to simulate mouse movement if needed.
             *
             * \param[in] position New mouse position.
             */
            void setMousePosition(Math::Vector2i const& position);

            /**
             * Applies a delta value to the mouse wheel.
             * \param[in] delta
             */
            void triggerMouseScrollDelta(int8_t delta);

            //------------------------------------------------------------
            // Query Methods

            /**
             * Retrieves the current mouse position in window coordinates. 
             */
            Math::Vector2i const& getMousePosition() const;

            /**
             * Checks if the specified keyboard key is down.
             * See Ocular::Core::KeyboardKeys for supported keys to query.
             *
             * \param[in] key         Which key to check the state of.
             * \return TRUE if the key is currently down and has not yet been released.
             */
            bool isKeyboardKeyDown(KeyboardKeys key) const;

            /**
             * Checks if the specified mouse key is down.
             * See Ocular::Core::MouseButtons for supported keys to query.
             *
             * \param[in] button      Which key to check the state of.
             * \return TRUE if the key is currently down and has not yet been released.
             */
            bool isMouseButtonDown(MouseButtons button) const;

            /**
             * Checks if the left shift keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::ShiftLeft);
             *
             * \return TRUE if they left shift key is currently down and has not yet been released.
             */
            bool isLeftShiftDown() const;

            /**
             * Checks if the right shift keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::ShiftRight);
             *
             * \return TRUE if they right shift key is currently down and has not yet been released.
             */
            bool isRightShiftDown() const;

            /**
             * Checks if the left ctrl keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::CtrlLeft);
             *
             * \return TRUE if they left ctrl key is currently down and has not yet been released.
             */
            bool isLeftCtrlDown() const;

            /**
             * Checks if the right ctrl keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::CtrlRight);
             *
             * \return TRUE if they right ctrl key is currently down and has not yet been released.
             */
            bool isRightCtrlDown() const;

            /**
             * Checks if the left alt keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::AltLeft);
             *
             * \return TRUE if they left alt key is currently down and has not yet been released.
             */
            bool isLeftAltDown() const;

            /**
             * Checks if the right alt keyboard key is down. 
             * Convenience method that works identically to:
             *
             *    isKeyboardKeyDown(KeyboardKeys::AltRight);
             *
             * \return TRUE if they right alt key is currently down and has not yet been released.
             */
            bool isRightAltDown() const;

            /**
             * Checks if the left mouse button is down.
             * Convenience method that works identically to:
             *
             *    isMouseButtonDown(MouseButtons::Left);
             *
             * \return TRUE if the left mouse key is currently down and has not yet been released.
             */
            bool isLeftMouseDown() const;

            /**
             * Checks if the right mouse button is down.
             * Convenience method that works identically to:
             *
             *    isMouseButtonDown(MouseButtons::Right);
             *
             * \return TRUE if the right mouse key is currently down and has not yet been released.
             */
            bool isRightMouseDown() const;

            //------------------------------------------------------------
            // Misc.
            
            static std::string ToString(KeyState state);
            static std::string ToString(MouseButtons button);
            static std::string ToString(KeyboardKeys key);

        protected:

        private:

            void toggleKeyState(KeyboardKeys key);
            void toggleButtonState(MouseButtons button);

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

            std::array<bool, 255> m_KeyboardState; 
            std::array<bool, 5> m_MouseState;

            Math::Vector2i m_MousePosition;
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