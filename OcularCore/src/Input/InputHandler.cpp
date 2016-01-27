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

#include "Input/InputHandler.hpp"
#include "OcularEngine.hpp"

#include "Events/Events/KeyboardInputEvent.hpp"
#include "Events/Events/MouseButtonInputEvent.hpp"
#include "Events/Events/MouseMoveInputEvent.hpp"
#include "Events/Events/MouseScrollInputEvent.hpp"

#include <algorithm>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        InputHandler::InputHandler()
        {
            m_KeyboardState.fill(false);
            m_MouseState.fill(false);
        }

        InputHandler::~InputHandler()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void InputHandler::triggerKeyboardKeyDown(KeyboardKeys key)
        {
            shiftConvertKey(key);

            if(!m_KeyboardState[static_cast<uint8_t>(key)])
            {
                toggleKeyState(key);
            }
        }

        void InputHandler::triggerMouseButtonDown(MouseButtons const button)
        {
            if(!m_MouseState[static_cast<uint8_t>(button)])
            {
                toggleButtonState(button);
            }
        }

        void InputHandler::triggerKeyboardKeyUp(KeyboardKeys key)
        {
            if((key == KeyboardKeys::ShiftLeft) || (key == KeyboardKeys::ShiftRight))
            {
                swapShiftSpecialKeys();
            }
            else
            {
                if(m_KeyboardState[static_cast<uint8_t>(key)])
                {
                    toggleKeyState(key);
                    return;
                }
                else
                {
                    shiftConvertKey(key);
                }
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(key)])
            {
                toggleKeyState(key);
            }
        }

        void InputHandler::triggerMouseButtonUp(MouseButtons const button)
        {
            if(m_MouseState[static_cast<uint8_t>(button)])
            {
                toggleButtonState(button);
            }
        }

        void InputHandler::triggerMouseScrollDelta(int8_t const delta)
        {
            if(delta != 0)
            {
                OcularEvents->queueEvent(std::make_shared<MouseScrollInputEvent>(delta));
            }
        }

        void InputHandler::triggerMouseMoveDelta(Math::Vector2i const& delta)
        {
            if(delta.x != 0 || delta.y != 0)
            {
                const Math::Vector2i newPosition = m_MousePosition + delta;
                OcularEvents->queueEvent(std::make_shared<MouseMoveInputEvent>(m_MousePosition, newPosition));

                m_MousePosition = newPosition;
            }
        }

        void InputHandler::setMousePosition(Math::Vector2i const& position)
        {
            if(m_MousePosition != position)
            {
                OcularEvents->queueEvent(std::make_shared<MouseMoveInputEvent>(m_MousePosition, position));
                m_MousePosition = position;
            }
        }

        Math::Vector2i const& InputHandler::getMousePosition() const
        {
            return m_MousePosition;
        }

        bool InputHandler::isKeyboardKeyDown(KeyboardKeys const key) const
        {
            return m_KeyboardState[static_cast<uint8_t>(key)];
        }

        bool InputHandler::isMouseButtonDown(MouseButtons const button) const
        {
            return m_KeyboardState[static_cast<uint8_t>(button)];
        }

        bool InputHandler::isLeftShiftDown() const
        {
            return m_KeyboardState[4];
        }

        bool InputHandler::isRightShiftDown() const
        {
            return m_KeyboardState[5];
        }

        bool InputHandler::isLeftCtrlDown() const
        {
            return m_KeyboardState[6];
        }

        bool InputHandler::isRightCtrlDown() const
        {
            return m_KeyboardState[7];
        }

        bool InputHandler::isLeftAltDown() const
        {
            return m_KeyboardState[8];
        }

        bool InputHandler::isRightAltDown() const
        {
            return m_KeyboardState[9];
        }

        bool InputHandler::isLeftMouseDown() const
        {
            return m_MouseState[0];
        }

        bool InputHandler::isRightMouseDown() const
        {
            return m_MouseState[1];
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void InputHandler::update()
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void InputHandler::toggleKeyState(KeyboardKeys const key)
        {
            // Toggle the state and generate an event

            const uint8_t index = static_cast<uint8_t>(key);
            const KeyState state = (!m_KeyboardState[index] ? KeyState::Pressed : KeyState::Released);

            OcularEvents->queueEvent(std::make_shared<KeyboardInputEvent>(key, state));

            m_KeyboardState[index] = !m_KeyboardState[index];
        }

        void InputHandler::toggleButtonState(MouseButtons const button)
        {
            // Toggle the state and generate an event

            const uint8_t index = static_cast<uint8_t>(button);
            const KeyState state = (!m_MouseState[index] ? KeyState::Pressed : KeyState::Released);

            OcularEvents->queueEvent(std::make_shared<MouseButtonInputEvent>(button, state));

            m_MouseState[index] = !m_MouseState[index];
        }

        void InputHandler::shiftConvertKey(KeyboardKeys& key)
        {
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::ShiftLeft)] ||
               m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::ShiftRight)])
            {
                switch(key)
                {
                case KeyboardKeys::Apostrophe:
                    key = KeyboardKeys::Tilde;
                    break;

                case KeyboardKeys::Mainpad1:
                    key = KeyboardKeys::ExclamationMark;
                    break;

                case KeyboardKeys::Mainpad2:
                    key = KeyboardKeys::Ampersat;
                    break;

                case KeyboardKeys::Mainpad3:
                    key = KeyboardKeys::Hash;
                    break;

                case KeyboardKeys::Mainpad4:
                    key = KeyboardKeys::DollarSign;
                    break;

                case KeyboardKeys::Mainpad5:
                    key = KeyboardKeys::PercentSign;
                    break;

                case KeyboardKeys::Mainpad6:
                    key = KeyboardKeys::Caret;
                    break;

                case KeyboardKeys::Mainpad7:
                    key = KeyboardKeys::Ampersand;
                    break;

                case KeyboardKeys::Mainpad8:
                    key = KeyboardKeys::Multiply;
                    break;

                case KeyboardKeys::Mainpad9:
                    key = KeyboardKeys::ParenthesisLeft;
                    break;

                case KeyboardKeys::Mainpad0:
                    key = KeyboardKeys::ParenthesisRight;
                    break;

                case KeyboardKeys::Subtract:
                    key = KeyboardKeys::Underscore;
                    break;

                case KeyboardKeys::Equals:
                    key = KeyboardKeys::Plus;
                    break;

                case KeyboardKeys::BracketLeft:
                    key = KeyboardKeys::CurlyBracketLeft;
                    break;

                case KeyboardKeys::BracketRight:
                    key = KeyboardKeys::CurlyBracketRight;
                    break;

                case KeyboardKeys::Backslash:
                    key = KeyboardKeys::Pipe;
                    break;

                case KeyboardKeys::Semicolon:
                    key = KeyboardKeys::Colon;
                    break;

                case KeyboardKeys::QuotationSingle:
                    key = KeyboardKeys::QuotationDouble;
                    break; 

                case KeyboardKeys::Comma:
                    key = KeyboardKeys::AngleBracketLeft;
                    break;

                case KeyboardKeys::Period:
                    key = KeyboardKeys::AngleBracketRight;
                    break;

                case KeyboardKeys::ForwardSlash:
                    key = KeyboardKeys::QuestionMark;
                    break;

                default:
                    break;
                }
            }
        }

        void InputHandler::swapShiftSpecialKeys()
        {
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Tilde)])
            {
                toggleKeyState(KeyboardKeys::Tilde);
                toggleKeyState(KeyboardKeys::Apostrophe);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::ExclamationMark)])
            {
                toggleKeyState(KeyboardKeys::ExclamationMark);
                toggleKeyState(KeyboardKeys::Mainpad1);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Ampersat)])
            {
                toggleKeyState(KeyboardKeys::Ampersat);
                toggleKeyState(KeyboardKeys::Mainpad2);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Hash)])
            {
                toggleKeyState(KeyboardKeys::Hash);
                toggleKeyState(KeyboardKeys::Mainpad3);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::DollarSign)])
            {
                toggleKeyState(KeyboardKeys::DollarSign);
                toggleKeyState(KeyboardKeys::Mainpad4);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::PercentSign)])
            {
                toggleKeyState(KeyboardKeys::PercentSign);
                toggleKeyState(KeyboardKeys::Mainpad5);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Caret)])
            {
                toggleKeyState(KeyboardKeys::Caret);
                toggleKeyState(KeyboardKeys::Mainpad6);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Ampersand)])
            {
                toggleKeyState(KeyboardKeys::Ampersand);
                toggleKeyState(KeyboardKeys::Mainpad7);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Multiply)])
            {
                toggleKeyState(KeyboardKeys::Multiply);
                toggleKeyState(KeyboardKeys::Mainpad8);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::ParenthesisLeft)])
            {
                toggleKeyState(KeyboardKeys::ParenthesisLeft);
                toggleKeyState(KeyboardKeys::Mainpad9);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::ParenthesisRight)])
            {
                toggleKeyState(KeyboardKeys::ParenthesisRight);
                toggleKeyState(KeyboardKeys::Mainpad0);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Underscore)])
            {
                toggleKeyState(KeyboardKeys::Underscore);
                toggleKeyState(KeyboardKeys::Subtract);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Multiply)])
            {
                toggleKeyState(KeyboardKeys::Multiply);
                toggleKeyState(KeyboardKeys::Equals);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::CurlyBracketLeft)])
            {
                toggleKeyState(KeyboardKeys::CurlyBracketLeft);
                toggleKeyState(KeyboardKeys::BracketLeft);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::CurlyBracketRight)])
            {
                toggleKeyState(KeyboardKeys::CurlyBracketRight);
                toggleKeyState(KeyboardKeys::BracketRight);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Pipe)])
            {
                toggleKeyState(KeyboardKeys::Pipe);
                toggleKeyState(KeyboardKeys::Backslash);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::Colon)])
            {
                toggleKeyState(KeyboardKeys::Colon);
                toggleKeyState(KeyboardKeys::Semicolon);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::QuotationDouble)])
            {
                toggleKeyState(KeyboardKeys::QuotationDouble);
                toggleKeyState(KeyboardKeys::QuotationSingle);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::AngleBracketLeft)])
            {
                toggleKeyState(KeyboardKeys::AngleBracketLeft);
                toggleKeyState(KeyboardKeys::Comma);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::AngleBracketRight)])
            {
                toggleKeyState(KeyboardKeys::AngleBracketRight);
                toggleKeyState(KeyboardKeys::Period);
            }
            
            if(m_KeyboardState[static_cast<uint8_t>(KeyboardKeys::QuestionMark)])
            {
                toggleKeyState(KeyboardKeys::QuestionMark);
                toggleKeyState(KeyboardKeys::ForwardSlash);
            }
        }

        //----------------------------------------------------------------------------------
        // STATIC METHODS
        //----------------------------------------------------------------------------------

        std::string InputHandler::ToString(KeyState const state)
        {
            static const std::string stringArray[3] =
            {
                "Released",
                "Pressed",
                "Undefined"
            };

            std::string result = "Undefined";
            const uint8_t index = static_cast<uint8_t>(state);

            if(index < 3)
            {
                result = stringArray[index];
            }

            return result;
        }

        std::string InputHandler::ToString(MouseButtons const button)
        {
            static std::string stringArray[6] =
            {
                "Left",
                "Right",
                "Middle",
                "XButton1",
                "XButton2",
                "Undefined"
            };

            std::string result = "Undefined";
            const uint8_t index = static_cast<uint8_t>(button);

            if(index < 6)
            {
                result = stringArray[index];
            }

            return result;
        }

        std::string InputHandler::ToString(KeyboardKeys const key)
        {
            static std::string stringArray[255] =
            {
                "Backspace",
                "Tab",
                "Clear",
                "Enter",
                "Left Shift",
                "Right Shift",
                "Left Ctrl",
                "Right Ctrl",
                "Left Alt",
                "Right Alt",
                "Pause",
                "Caps Lock",
                "Escape",
                "Space",
                "Page Up",
                "Page Down",
                "End",
                "Home",
                "Left Arrow",
                "Right Arrow",
                "Up Arrow",
                "Down Arrow",
                "Select",
                "Execute",
                "Print Screen",
                "Insert",
                "Delete",
                "Help",
                "OS Key",
                "-",
                "_",
                "+",
                "=",
                "[",
                "]",
                "{",
                "}",
                "\\",
                "|",
                ";",
                ":",
                "'",
                "\"",
                ",",
                ".",
                "<",
                ">",
                "/",
                "?",
                "`",
                "~",
                "!",
                "@",
                "#",
                "$",
                "%",
                "^",
                "&",
                "*",
                "(",
                ")",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "0",
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "+",
                "-",
                "*",
                "/",
                ".",
                "Separator",
                "Enter",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "A",
                "B",
                "C",
                "D",
                "E",
                "F",
                "G",
                "H",
                "I",
                "J",
                "K",
                "L",
                "M",
                "N",
                "O",
                "P",
                "Q",
                "R",
                "S",
                "T",
                "U",
                "V",
                "W",
                "X",
                "Y",
                "Z",
                "0",
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                "7",
                "8",
                "9",
                "Enter",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "F1",
                "F2",
                "F3",
                "F4",
                "F5",
                "F6",
                "F7",
                "F8",
                "F9",
                "F10",
                "F11",
                "F12",
                "F13",
                "F14",
                "F15",
                "F16",
                "F17",
                "F18",
                "F19",
                "F20",
                "F21",
                "F22",
                "F23",
                "F24",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined",
                "Undefined"
            };

            std::string result = "Undefined";
            const uint8_t index = static_cast<uint8_t>(key);

            if(index < 255)
            {
                result = stringArray[index];
            }

            return result;
        }
    }
}