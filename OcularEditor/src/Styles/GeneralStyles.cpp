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

#include "stdafx.h"
#include "Styles/GeneralStyles.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        const QString GeneralStyles::windowStyle =
            "QWidget"
            "{"
            "    color: rgb(255, 255, 255);"
            "    background-color: rgb(45, 45, 48);"
            "    border-color: rgb(63, 63, 70);"
            "}"
            "QGroupBox"
            "{"
            "    border: 1px solid rgb(51, 51, 55);"
            "    background-color: rgb(51, 51, 55);"
            "}"
            "QGroupBox::title"
            "{"
            "    color: rgb(255, 255, 255);"
            "    background-color: rgb(63, 63, 70);"
            "    padding-left: 10px;"
            "    padding-right: 2000px;"
            "    padding-top: 3px;"
            "    padding-bottom: 3px;"
            "}"
            "QTextEdit"
            "{"
            "    color: rgb(255, 255, 255);"
            "    border: 0px solid black;"
            "}"
            "QTreeWidget"
            "{"
            "    color: rgb(255, 255, 255);"
            "    border: 0px solid black;"
            "}";

        const QString GeneralStyles::frameStyle =
            "color: rgb(63, 63, 70);";

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}