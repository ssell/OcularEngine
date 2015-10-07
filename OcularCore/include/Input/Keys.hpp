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

#ifndef __H__OCULAR_INPUT_KEYS__H__
#define __H__OCULAR_INPUT_KEYS__H__

#include <cstdint>

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
         * \enum KeyState
         */
        enum class KeyState : uint8_t
        {
            Released  = 0x00,
            Pressed   = 0x01,
            Undefined = 0x02
        };

        /**
         * \enum  MouseButtons
         * \brief All supported standard mouse buttons.
         * \note  Due to using uint8_t, there is a limit of 255 supported mouse buttons.
         */
        enum class MouseButtons : uint8_t
        {
            Left      = 0x00,
            Right     = 0x01,
            Middle    = 0x02,
            XButton1  = 0x03,
            XButton2  = 0x04,
            Undefined = 0x05
        };

        /**
         * \enum  KeyboardKeys
         * \brief All supported standard keyboard keys.
         * \note  Due to using uint8_t, there is a limit of 255 supported keyboard keys.
         */
        enum class KeyboardKeys : uint8_t
        {
            //------------------------------------------------------------
            // General Keys reserved 0-75

            Backspace         = 0x00,
            Tab               = 0x01,
            Clear             = 0x02,
            Enter             = 0x03,
            ShiftLeft         = 0x04,
            ShiftRight        = 0x05,
            CtrlLeft          = 0x06,
            CtrlRight         = 0x07,
            AltLeft           = 0x08,
            AltRight          = 0x09,
            Pause             = 0x0A,
            CapsLock          = 0x0B,
            Escape            = 0x0C,
            Space             = 0x0D,
            PageUp            = 0x0E,
            PageDown          = 0x0F,
            End               = 0x10,
            Home              = 0x11, 
            LeftArrow         = 0x12,
            RightArrow        = 0x13,
            UpArrow           = 0x14,
            DownArrow         = 0x15,
            Select            = 0x16,
            Execute           = 0x17,
            PrintScreen       = 0x18,
            Insert            = 0x19,
            Delete            = 0x1A,
            Help              = 0x1B,
            OSKey             = 0x1C,
            Subtract          = 0x1D,     /// -
            Underscore        = 0x1E,     /// _
            Plus              = 0x1F,     /// +
            Equals            = 0x20,     /// =
            BracketLeft       = 0x21,     /// [
            BracketRight      = 0x22,     /// ]
            CurlyBracketLeft  = 0x23,     /// {
            CurlyBracketRight = 0x24,     /// }
            Backslash         = 0x25,     /// \ 
            Pipe              = 0x26,     /// |
            Semicolon         = 0x27,     /// ;
            Colon             = 0x28,     /// :
            QuotationSingle   = 0x29,     /// '
            QuotationDouble   = 0x2A,     /// "
            Comma             = 0x2B,     /// ,
            Period            = 0x2C,     /// .
            AngleBracketLeft  = 0x2D,     /// <
            AngleBracketRight = 0x2E,     /// >
            ForwardSlash      = 0x2F,     /// /
            QuestionMark      = 0x30,     /// ?
            Apostrophe        = 0x31,     /// `
            Tilde             = 0x32,     /// ~
            ExclamationMark   = 0x33,     /// !
            Ampersat          = 0x34,     /// @
            Hash              = 0x35,     /// #
            DollarSign        = 0x36,     /// $
            PercentSign       = 0x37,     /// %
            Caret             = 0x38,     /// ^
            Ampersand         = 0x39,     /// &
            Multiply          = 0x3A,     /// *
            ParenthesisLeft   = 0x3B,     /// (
            ParenthesisRight  = 0x3C,     /// )
            
            //------------------------------------------------------------
            // Numpad Keys reserved 76-100
            
            Numpad0           = 0x4C,     /// The '0' key on the numpad. Not to be confused with 'Mainpad0'
            Numpad1           = 0x4D,     /// The '1' key on the numpad. Not to be confused with 'Mainpad1'
            Numpad2           = 0x4E,     /// The '2' key on the numpad. Not to be confused with 'Mainpad2'
            Numpad3           = 0x4F,     /// The '3' key on the numpad. Not to be confused with 'Mainpad3'
            Numpad4           = 0x50,     /// The '4' key on the numpad. Not to be confused with 'Mainpad4'
            Numpad5           = 0x51,     /// The '5' key on the numpad. Not to be confused with 'Mainpad5'
            Numpad6           = 0x52,     /// The '6' key on the numpad. Not to be confused with 'Mainpad6'
            Numpad7           = 0x53,     /// The '7' key on the numpad. Not to be confused with 'Mainpad7'
            Numpad8           = 0x54,     /// The '8' key on the numpad. Not to be confused with 'Mainpad8'
            Numpad9           = 0x55,     /// The '9' key on the numpad. Not to be confused with 'Mainpad9'
            NumpadPlus        = 0x56,     /// The '+' key on the numpad. Not to be confused with 'Plus'
            NumpadSubtract    = 0x57,     /// The '-' key on the numpad. Not to be confused with 'Subtract'
            NumpadMultiply    = 0x58,     /// The '*' key on the numpad. Not to be confused with 'Multiply'
            NumpadDivide      = 0x59,     /// The '/' key on the numpad. Not to be confused with 'ForwardSlash'
            NumpadDecimal     = 0x5A,     /// The '.' key on the numpad. Not to be confused with 'Period'
            NumpadSeparator   = 0x5B,
            NumpadEnter       = 0x5C,

            //------------------------------------------------------------
            // Alphanumeric Keys reserved 101-150

            A                 = 0x65,
            B                 = 0x66,
            C                 = 0x67,
            D                 = 0x68,
            E                 = 0x69,
            F                 = 0x6A,
            G                 = 0x6B,
            H                 = 0x6C,
            I                 = 0x6D,
            J                 = 0x6E,
            K                 = 0x6F,
            L                 = 0x70,
            M                 = 0x71,
            N                 = 0x72,
            O                 = 0x73,
            P                 = 0x74,
            Q                 = 0x75,
            R                 = 0x76,
            S                 = 0x77,
            T                 = 0x78,
            U                 = 0x79,
            V                 = 0x7A,
            W                 = 0x7B,
            X                 = 0x7C,
            Y                 = 0x7D,
            Z                 = 0x7E,
            Mainpad0          = 0x7F,     /// The '0' key on the main keypad. Not to be confused with 'Numpad0'
            Mainpad1          = 0x80,     /// The '1' key on the main keypad. Not to be confused with 'Numpad1'
            Mainpad2          = 0x81,     /// The '2' key on the main keypad. Not to be confused with 'Numpad2'
            Mainpad3          = 0x82,     /// The '3' key on the main keypad. Not to be confused with 'Numpad3'
            Mainpad4          = 0x83,     /// The '4' key on the main keypad. Not to be confused with 'Numpad4'
            Mainpad5          = 0x84,     /// The '5' key on the main keypad. Not to be confused with 'Numpad5'
            Mainpad6          = 0x85,     /// The '6' key on the main keypad. Not to be confused with 'Numpad6'
            Mainpad7          = 0x86,     /// The '7' key on the main keypad. Not to be confused with 'Numpad7'
            Mainpad8          = 0x87,     /// The '8' key on the main keypad. Not to be confused with 'Numpad8'
            Mainpad9          = 0x88,     /// The '9' key on the main keypad. Not to be confused with 'Numpad9'
            MainpadEnter      = 0x89,

            //------------------------------------------------------------
            // Function Keys reserved 151-175
            
            F1                = 0x97,
            F2                = 0x98,
            F3                = 0x99,
            F4                = 0x9A,
            F5                = 0x9B,
            F6                = 0x9C,
            F7                = 0x9D,
            F8                = 0x9E,
            F9                = 0x9F,
            F10               = 0xA0,
            F11               = 0xA1,
            F12               = 0xA2,
            F13               = 0xA3,
            F14               = 0xA4,
            F15               = 0xA5,
            F16               = 0xA6,
            F17               = 0xA7,
            F18               = 0xA8,
            F19               = 0xA9,
            F20               = 0xAA,
            F21               = 0xAB,
            F22               = 0xAC,
            F23               = 0xAD,
            F24               = 0xAE,

            //------------------------------------------------------------
            // Other

            Undefined         = 0xFF
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