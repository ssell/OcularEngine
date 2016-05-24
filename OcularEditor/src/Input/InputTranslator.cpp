/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "stdafx.h"

#include "Input/InputTranslator.hpp"
#include <qevent.h>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        InputTranslator::InputTranslator(QObject* parent)
            : QObject(parent)
        {

        }

        InputTranslator::~InputTranslator()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool InputTranslator::eventFilter(QObject* obj, QEvent* event)
        {
            bool result = false;

            if(event)
            {
                if(event->type() == QEvent::KeyPress)
                {
                    result = processKeyPress(event);
                }
                else if(event->type() == QEvent::KeyRelease)
                {
                    result = processKeyRelease(event);
                }
                else if(event->type() == QEvent::MouseButtonPress)
                {
                    result = processMousePress(event);
                }
                else if(event->type() == QEvent::MouseButtonRelease)
                {
                    result = processMouseRelease(event);
                }
                else if(event->type() == QEvent::MouseMove)
                {
                    result = processMouseMove(event);
                }
                else
                {
                    result = QObject::eventFilter(obj, event);
                }
            }

            // Return TRUE to consume the event (filter it)
            return result;
        }

        bool InputTranslator::processKeyPress(QEvent* event)
        {
            bool result = false;
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            if(keyEvent)
            {
                const int32_t key = keyEvent->key();
                const Core::KeyboardKeys okey = convertKey(key);

                if(okey != Core::KeyboardKeys::Undefined)
                {
                    OcularInput->triggerKeyboardKeyDown(okey);
                }
            }

            return result;
        }

        bool InputTranslator::processKeyRelease(QEvent* event)
        {
            bool result = false;
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

            if(keyEvent)
            {
                const int32_t key = keyEvent->key();
                const Core::KeyboardKeys okey = convertKey(key);

                if(okey != Core::KeyboardKeys::Undefined)
                {
                    OcularInput->triggerKeyboardKeyUp(okey);
                }
            }

            return result;
        }

        bool InputTranslator::processMousePress(QEvent* event)
        {
            bool result = false;
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            if(mouseEvent)
            {
                const int32_t button = static_cast<int32_t>(mouseEvent->button());
                Core::MouseButtons obutton = convertButton(button);

                if(obutton != Core::MouseButtons::Undefined)
                {
                    OcularInput->triggerMouseButtonDown(obutton);
                }
            }

            return result;
        }

        bool InputTranslator::processMouseRelease(QEvent* event)
        {
            bool result = false;
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            if(mouseEvent)
            {
                const int32_t button = static_cast<int32_t>(mouseEvent->button());
                Core::MouseButtons obutton = convertButton(button);

                if(obutton != Core::MouseButtons::Undefined)
                {
                    OcularInput->triggerMouseButtonUp(obutton);
                }
            }

            return result;
        }

        bool InputTranslator::processMouseMove(QEvent* event)
        {
            bool result = false;
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            if(mouseEvent)
            {
                OcularInput->setMousePosition(Math::Vector2i(static_cast<int32_t>(mouseEvent->x()), static_cast<int32_t>(mouseEvent->y())));
            }

            return result;
        }

        Core::KeyboardKeys InputTranslator::convertKey(int32_t const key)
        {
            // http://doc.qt.io/qt-5/qt.html#Key-enum

            Core::KeyboardKeys result = Core::KeyboardKeys::Undefined;

            switch(key)
            {
                //--------------------------------------------------------
                // General Keys

            case Qt::Key_Backspace:
                result = Core::KeyboardKeys::Backspace;
                break;

            case Qt::Key_Tab:
                result = Core::KeyboardKeys::Tab;
                break;

            case Qt::Key_Clear:
                result = Core::KeyboardKeys::Clear;
                break;

            case Qt::Key_Enter:
                result = Core::KeyboardKeys::Enter;
                break;

            case Qt::Key_Shift:
                result = Core::KeyboardKeys::ShiftLeft;    // Qt does not distinguish between left and right. Default to left.
                break;

            case Qt::Key_Control:
                result = Core::KeyboardKeys::CtrlLeft;     // Qt does not distinguish between left and right. Default to left.
                break;

            case Qt::Key_Alt: 
                result = Core::KeyboardKeys::AltLeft;      // Qt does not distinguish between left and right. Default to left.
                break;

            case Qt::Key_Pause:
                result = Core::KeyboardKeys::Pause;
                break;

            case Qt::Key_CapsLock:
                result = Core::KeyboardKeys::CapsLock;
                break;

            case Qt::Key_Escape:
                result = Core::KeyboardKeys::Escape;
                break;

            case Qt::Key_Space:
                result = Core::KeyboardKeys::Space;
                break;

            case Qt::Key_PageUp:
                result = Core::KeyboardKeys::PageUp;
                break;

            case Qt::Key_PageDown:
                result = Core::KeyboardKeys::PageDown;
                break;

            case Qt::Key_End:
                result = Core::KeyboardKeys::End;
                break;

            case Qt::Key_Home:
                result = Core::KeyboardKeys::Home;
                break;

            case Qt::Key_Left:
                result = Core::KeyboardKeys::LeftArrow;
                break;

            case Qt::Key_Right:
                result = Core::KeyboardKeys::RightArrow;
                break;

            case Qt::Key_Up:
                result = Core::KeyboardKeys::UpArrow;
                break;

            case Qt::Key_Down:
                result = Core::KeyboardKeys::DownArrow;
                break;

            case Qt::Key_Select:
                result = Core::KeyboardKeys::Select;
                break;

            case Qt::Key_Execute:
                result = Core::KeyboardKeys::Execute;
                break;

            case Qt::Key_Print:
                result = Core::KeyboardKeys::PrintScreen;
                break;

            case Qt::Key_Insert:
                result = Core::KeyboardKeys::Insert;
                break;

            case Qt::Key_Delete:
                result = Core::KeyboardKeys::Delete;
                break;

            case Qt::Key_Help:
                result = Core::KeyboardKeys::Help;
                break;

            case Qt::Key_Meta:
                result = Core::KeyboardKeys::OSKey;
                break;

            case Qt::Key_Minus:
                result = Core::KeyboardKeys::Subtract;
                break;

            case Qt::Key_Underscore:
                result = Core::KeyboardKeys::Underscore;
                break;

            case Qt::Key_Plus:
                result = Core::KeyboardKeys::Plus;
                break;

            case Qt::Key_Equal:
                result = Core::KeyboardKeys::Equals;
                break;

            case Qt::Key_BracketLeft:
                result = Core::KeyboardKeys::BracketLeft;
                break;

            case Qt::Key_BracketRight:
                result = Core::KeyboardKeys::BracketRight;
                break;

            case Qt::Key_BraceLeft:
                result = Core::KeyboardKeys::CurlyBracketLeft;
                break;

            case Qt::Key_BraceRight:
                result = Core::KeyboardKeys::CurlyBracketRight;
                break;

            case Qt::Key_Backslash:
                result = Core::KeyboardKeys::Backslash;
                break;

            case Qt::Key_Bar:
                result = Core::KeyboardKeys::Pipe;
                break;

            case Qt::Key_Semicolon:
                result = Core::KeyboardKeys::Semicolon;
                break;

            case Qt::Key_Colon:
                result = Core::KeyboardKeys::Colon;
                break;

            case Qt::Key_QuoteLeft:
                result = Core::KeyboardKeys::QuotationSingle;
                break;

            case Qt::Key_QuoteDbl:
                result = Core::KeyboardKeys::QuotationDouble;
                break;

            case Qt::Key_Comma:
                result = Core::KeyboardKeys::Comma;
                break;

            case Qt::Key_Period:
                result = Core::KeyboardKeys::Period;
                break;

            case Qt::Key_Less:
                result = Core::KeyboardKeys::AngleBracketLeft;
                break;

            case Qt::Key_Greater:
                result = Core::KeyboardKeys::AngleBracketRight;
                break;

            case Qt::Key_Slash:
                result = Core::KeyboardKeys::ForwardSlash;
                break;

            case Qt::Key_Question:
                result = Core::KeyboardKeys::QuestionMark;
                break;

            case Qt::Key_Apostrophe:
                result = Core::KeyboardKeys::Apostrophe;
                break;

            case Qt::Key_AsciiTilde:
                result = Core::KeyboardKeys::Tilde;
                break;

            case Qt::Key_Exclam:
                result = Core::KeyboardKeys::ExclamationMark;
                break;

            case Qt::Key_At:
                result = Core::KeyboardKeys::Ampersat;
                break;

            case Qt::Key_NumberSign:
                result = Core::KeyboardKeys::Hash;
                break;

            case Qt::Key_Dollar:
                result = Core::KeyboardKeys::DollarSign;
                break;

            case Qt::Key_Percent:
                result = Core::KeyboardKeys::PercentSign;
                break;

            case Qt::Key_Ampersand:
                result = Core::KeyboardKeys::Ampersand;
                break;

            case Qt::Key_Asterisk:
                result = Core::KeyboardKeys::Multiply;
                break;

            case Qt::Key_ParenLeft:
                result = Core::KeyboardKeys::ParenthesisLeft;
                break;

            case Qt::Key_ParenRight:
                result = Core::KeyboardKeys::ParenthesisRight;
                break;

                //--------------------------------------------------------
                // Numpad Keys

                //--------------------------------------------------------
                // Alphanumeric Keys

            case Qt::Key_A:
                result = Core::KeyboardKeys::A;
                break;

            case Qt::Key_B:
                result = Core::KeyboardKeys::B;
                break;

            case Qt::Key_C:
                result = Core::KeyboardKeys::C;
                break;

            case Qt::Key_D:
                result = Core::KeyboardKeys::D;
                break;

            case Qt::Key_E:
                result = Core::KeyboardKeys::E;
                break;

            case Qt::Key_F:
                result = Core::KeyboardKeys::F;
                break;

            case Qt::Key_G:
                result = Core::KeyboardKeys::G;
                break;

            case Qt::Key_H:
                result = Core::KeyboardKeys::H;
                break;

            case Qt::Key_I:
                result = Core::KeyboardKeys::I;
                break;

            case Qt::Key_J:
                result = Core::KeyboardKeys::J;
                break;

            case Qt::Key_K:
                result = Core::KeyboardKeys::K;
                break;

            case Qt::Key_L:
                result = Core::KeyboardKeys::L;
                break;

            case Qt::Key_M:
                result = Core::KeyboardKeys::M;
                break;

            case Qt::Key_N:
                result = Core::KeyboardKeys::N;
                break;

            case Qt::Key_O:
                result = Core::KeyboardKeys::O;
                break;

            case Qt::Key_P:
                result = Core::KeyboardKeys::P;
                break;

            case Qt::Key_Q:
                result = Core::KeyboardKeys::Q;
                break;

            case Qt::Key_R:
                result = Core::KeyboardKeys::R;
                break;

            case Qt::Key_S:
                result = Core::KeyboardKeys::S;
                break;

            case Qt::Key_T:
                result = Core::KeyboardKeys::T;
                break;

            case Qt::Key_U:
                result = Core::KeyboardKeys::U;
                break;

            case Qt::Key_V:
                result = Core::KeyboardKeys::V;
                break;

            case Qt::Key_W:
                result = Core::KeyboardKeys::W;
                break;

            case Qt::Key_X:
                result = Core::KeyboardKeys::X;
                break;

            case Qt::Key_Y:
                result = Core::KeyboardKeys::Y;
                break;

            case Qt::Key_Z:
                result = Core::KeyboardKeys::Z;
                break;

            case Qt::Key_0:
                result = Core::KeyboardKeys::Mainpad0;
                break;

            case Qt::Key_1:
                result = Core::KeyboardKeys::Mainpad1;
                break;

            case Qt::Key_2:
                result = Core::KeyboardKeys::Mainpad2;
                break;

            case Qt::Key_3:
                result = Core::KeyboardKeys::Mainpad3;
                break;

            case Qt::Key_4:
                result = Core::KeyboardKeys::Mainpad4;
                break;

            case Qt::Key_5:
                result = Core::KeyboardKeys::Mainpad5;
                break;

            case Qt::Key_6:
                result = Core::KeyboardKeys::Mainpad6;
                break;

            case Qt::Key_7:
                result = Core::KeyboardKeys::Mainpad7;
                break;

            case Qt::Key_8:
                result = Core::KeyboardKeys::Mainpad8;
                break;

            case Qt::Key_9:
                result = Core::KeyboardKeys::Mainpad9;
                break;

                //--------------------------------------------------------
                // Function Keys

            case Qt::Key_F1:
                result = Core::KeyboardKeys::F1;
                break;

            case Qt::Key_F2:
                result = Core::KeyboardKeys::F2;
                break;

            case Qt::Key_F3:
                result = Core::KeyboardKeys::F3;
                break;

            case Qt::Key_F4:
                result = Core::KeyboardKeys::F4;
                break;

            case Qt::Key_F5:
                result = Core::KeyboardKeys::F5;
                break;

            case Qt::Key_F6:
                result = Core::KeyboardKeys::F6;
                break;

            case Qt::Key_F7:
                result = Core::KeyboardKeys::F7;
                break;

            case Qt::Key_F8:
                result = Core::KeyboardKeys::F8;
                break;

            case Qt::Key_F9:
                result = Core::KeyboardKeys::F9;
                break;

            case Qt::Key_F10:
                result = Core::KeyboardKeys::F10;
                break;

            case Qt::Key_F11:
                result = Core::KeyboardKeys::F11;
                break;

            case Qt::Key_F12:
                result = Core::KeyboardKeys::F12;
                break;

            case Qt::Key_F13:
                result = Core::KeyboardKeys::F13;
                break;

            case Qt::Key_F14:
                result = Core::KeyboardKeys::F14;
                break;

            case Qt::Key_F15:
                result = Core::KeyboardKeys::F15;
                break;

            case Qt::Key_F16:
                result = Core::KeyboardKeys::F16;
                break;

            case Qt::Key_F17:
                result = Core::KeyboardKeys::F17;
                break;

            case Qt::Key_F18:
                result = Core::KeyboardKeys::F18;
                break;

            case Qt::Key_F19:
                result = Core::KeyboardKeys::F19;
                break;

            case Qt::Key_F20:
                result = Core::KeyboardKeys::F20;
                break;

            case Qt::Key_F21:
                result = Core::KeyboardKeys::F21;
                break;

            case Qt::Key_F22:
                result = Core::KeyboardKeys::F22;
                break;

            case Qt::Key_F23:
                result = Core::KeyboardKeys::F23;
                break;

            case Qt::Key_F24:
                result = Core::KeyboardKeys::F24;
                break;

                //--------------------------------------------------------

            default:
                break;
            }

            return result;
        }

        Core::MouseButtons InputTranslator::convertButton(int32_t const button)
        {
            Core::MouseButtons result = Core::MouseButtons::Undefined;

            switch(button) 
            {
            case Qt::LeftButton:
                result = Core::MouseButtons::Left;
                break;

            case Qt::RightButton:
                result = Core::MouseButtons::Right;
                break;

            case Qt::MiddleButton:
                result = Core::MouseButtons::Middle;
                break;

            case Qt::XButton1:
                result = Core::MouseButtons::XButton1;
                break;

            case Qt::XButton2:
                result = Core::MouseButtons::XButton2;
                break;

            default:
                break;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}