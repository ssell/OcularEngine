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

#include "Input/InputHandler.hpp"
#include "OcularEngine.hpp"

#include "Events/Events/KeyboardInputEvent.hpp"
#include "Events/Events/MouseButtonInputEvent.hpp"
#include "Events/Events/MouseMoveInputEvent.hpp"

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
            m_KeyboardStateCurrent.fill(false);
            m_KeyboardStatePrevious.fill(false);

            m_MouseStateCurrent.fill(false);
            m_MouseStatePrevious.fill(false);

            m_BufferTime   = 0.02f;   // 20ms
            m_ElapsedTotal = 0.0f;
        }

        InputHandler::~InputHandler()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void InputHandler::setBufferTime(float const time)
        {
            m_BufferTime = time;
        }

        void InputHandler::triggerKeyboardKeyDown(KeyboardKeys key)
        {
            shiftConvertKey(key);
            m_KeyboardStateCurrent[static_cast<uint8_t>(key)] = true;
        }

        void InputHandler::triggerMouseButtonDown(MouseButtons const button)
        {
            m_MouseStateCurrent[static_cast<uint8_t>(button)] = true;
        }

        void InputHandler::triggerKeyboardKeyUp(KeyboardKeys key)
        {
            if((key == KeyboardKeys::ShiftLeft) || (key == KeyboardKeys::ShiftRight))
            {
                swapShiftSpecialKeys();
            }
            else
            {
                shiftConvertKey(key);
            }

            m_KeyboardStateCurrent[static_cast<uint8_t>(key)] = false;
        }

        void InputHandler::triggerMouseButtonUp(MouseButtons const button)
        {
            m_MouseStateCurrent[static_cast<uint8_t>(button)] = false;
        }

        void InputHandler::setMousePosition(Math::Vector2f const& position)
        {
            m_MousePositionCurrent = position;
        }

        Math::Vector2f const& InputHandler::getMousePosition(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_MousePositionCurrent;
            }
            else
            {
                return m_MousePositionPrevious;
            }
        }

        bool InputHandler::isKeyboardKeyDown(KeyboardKeys const key, bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_KeyboardStateCurrent[static_cast<uint8_t>(key)];
            }
            else
            {
                return m_KeyboardStatePrevious[static_cast<uint8_t>(key)];
            }
        }

        bool InputHandler::isMouseButtonDown(MouseButtons const button, bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_MouseStateCurrent[static_cast<uint8_t>(button)];
            }
            else
            {
                return m_MouseStatePrevious[static_cast<uint8_t>(button)];
            }
        }

        bool InputHandler::isLeftShiftDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_KeyboardStateCurrent[4];
            }
            else
            {
                return m_KeyboardStatePrevious[4];
            }
        }

        bool InputHandler::isRightShiftDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_KeyboardStateCurrent[5];
            }
            else
            {
                return m_KeyboardStatePrevious[5];
            }
        }

        bool InputHandler::isLeftCtrlDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_KeyboardStateCurrent[6];
            }
            else
            {
                return m_KeyboardStatePrevious[6];
            }
        }

        bool InputHandler::isRightCtrlDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_KeyboardStateCurrent[7];
            }
            else
            {
                return m_KeyboardStatePrevious[7];
            }
        }

        bool InputHandler::isLeftAltDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_KeyboardStateCurrent[8];
            }
            else
            {
                return m_KeyboardStatePrevious[8];
            }
        }

        bool InputHandler::isRightAltDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_KeyboardStateCurrent[9];
            }
            else
            {
                return m_KeyboardStatePrevious[9];
            }
        }

        bool InputHandler::isLeftMouseDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_MouseStateCurrent[0];
            }
            else
            {
                return m_MouseStatePrevious[0];
            }
        }

        bool InputHandler::isRightMouseDown(bool const queryLatest) const
        {
            if(queryLatest)
            {
                return m_MouseStateCurrent[1];
            }
            else
            {
                return m_MouseStatePrevious[1];
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void InputHandler::update()
        {
            m_ElapsedTotal += OcularClock->getDelta();

            if(m_ElapsedTotal > m_BufferTime)
            {
                processKeyboardChanges();
                processMouseChanges();

                m_ElapsedTotal = 0.0f;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void InputHandler::processKeyboardChanges()
        {
            for(uint8_t i = 0; i < m_KeyboardStateCurrent.size(); i++)
            {
                if(m_KeyboardStateCurrent[i] != m_KeyboardStatePrevious[i])
                {
                    // Keyboard key state has changed. Generate an event.

                    const KeyboardKeys key = static_cast<KeyboardKeys>(i);
                    const KeyState state = (m_KeyboardStateCurrent[i] ? KeyState::Pressed : KeyState::Released);

                    OcularEvents->queueEvent(std::make_shared<Events::KeyboardInputEvent>(key, state));

                    m_KeyboardStatePrevious[i] = m_KeyboardStateCurrent[i];
                }
            }
        }

        void InputHandler::processMouseChanges()
        {
            for(uint8_t i = 0; i < m_MouseStateCurrent.size(); i++)
            {
                if(m_MouseStateCurrent[i] != m_MouseStatePrevious[i])
                {
                    // Mouse button state has changed. Generate an event.

                    const MouseButtons button = static_cast<MouseButtons>(i);
                    const KeyState state = (m_MouseStateCurrent[i] ? KeyState::Pressed : KeyState::Released);

                    OcularEvents->queueEvent(std::make_shared<Events::MouseButtonInputEvent>(button, state));

                    m_MouseStatePrevious[i] = m_MouseStateCurrent[i];
                }
            }

            if(m_MousePositionCurrent != m_MousePositionPrevious)
            {
                // Mouse position has changed. Generate an event.

                OcularEvents->queueEvent(std::make_shared<Events::MouseMoveInputEvent>(m_MousePositionPrevious, m_MousePositionCurrent));

                m_MousePositionPrevious = m_MousePositionCurrent;
            }
        }

        void InputHandler::shiftConvertKey(KeyboardKeys& key)
        {
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ShiftLeft)] ||
               m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ShiftRight)])
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
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Tilde)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Tilde)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Apostrophe)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ExclamationMark)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ExclamationMark)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad1)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Ampersat)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Ampersat)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad2)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Hash)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Hash)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad3)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::DollarSign)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::DollarSign)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad4)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::PercentSign)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::PercentSign)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad5)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Caret)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Caret)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad6)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Ampersand)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Ampersand)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad7)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Multiply)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Multiply)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad8)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ParenthesisLeft)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ParenthesisLeft)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad9)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ParenthesisRight)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ParenthesisRight)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Mainpad0)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Underscore)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Underscore)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Subtract)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Multiply)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Multiply)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Equals)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::CurlyBracketLeft)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::CurlyBracketLeft)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::BracketLeft)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::CurlyBracketRight)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::CurlyBracketRight)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::BracketRight)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Pipe)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Pipe)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Backslash)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Colon)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Colon)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Semicolon)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::QuotationDouble)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::QuotationDouble)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::QuotationSingle)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::AngleBracketLeft)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::AngleBracketLeft)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Comma)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::AngleBracketRight)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::AngleBracketRight)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::Period)] = true;
            }
            
            if(m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::QuestionMark)])
            {
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::QuestionMark)] = false;
                m_KeyboardStateCurrent[static_cast<uint8_t>(KeyboardKeys::ForwardSlash)] = true;
            }
        }
    }
}