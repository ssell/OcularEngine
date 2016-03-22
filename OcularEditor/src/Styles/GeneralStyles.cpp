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

        // (211, 211, 211) : Default Text
        // (255, 255, 255) : Highlighted / Special Text

        // (45, 45, 48) : Normal Background
        // (51, 51, 51) : Grouping Background
        // (56, 56, 60) : Grouping Highlight
        // (27, 27, 28) : Dark Selected
        // (62, 62, 64) : Light Hover

        const QString GeneralStyles::windowStyle =
            "QWidget"
            "{"
            "    color: rgb(211, 221, 211);"
            "    background-color: rgb(45, 45, 48);"
            "    border-color: rgb(63, 63, 70);"
            "}"
            "QFrame"
            "{"
            "    color: rgb(211, 211, 211);"
            "}"
            "QLabel"
            "{"
            "    color: rgb(211, 211, 211);"
            "    background-color: rgb(56, 56, 60);"
            "}"
            "QGroupBox"
            "{"
            "    border: 1px solid rgb(27, 27, 28);"
            "    background-color: rgb(56, 56, 60);"
            "}"
            "QGroupBox::title"
            "{"
            "    color: rgb(255, 255, 255);"
            "    background-color: rgb(27, 27, 28);"
            "    padding-left: 10px;"
            "    padding-right: 2000px;"
            "    padding-top: 3px;"
            "    padding-bottom: 3px;"
            "}"
            "QGroupBox::title::focus"
            "{"
            "    background-color: rgb(0, 255, 0);"
            "}"
            "QTextEdit"
            "{"
            "    color: rgb(255, 255, 255);"
            "    border: 0px solid black;"
            "}"
            "QLineEdit"
            "{"
            "    background-color: rgb(45, 45, 48);"
            "    border: 1px solid rgb(52, 52, 54);"
            "    border-radius: 2px;"
            "    padding: 1px;"
            "}"
            "QLineEdit:focus"
            "{"
            "    background-color: rgb(45, 45, 48);"
            "    border: 1px solid rgb(37, 194, 62);"
            "    border-radius: 2px;"
            "    padding: 1px;"
            "}"
            "QTreeWidget"
            "{"
            "    border: 0px solid black;"
            "    background-color: rgb(56, 56, 60);"
            "}"
            "QTreeWidget::item"
            "{"
            "    color: rgb(211, 221, 211);"
            "    background-color: rgb(56, 56, 60);"
            "}"
            "QTreeWidget::item::focus"
            "{"
            "    border: 0px solid black;"
            "}"
            "QTreeWidget::item::selected"
            "{"
            "    color: rgb(255, 255, 255);"
            "    background-color: rgb(56, 56, 60);"
            "    border: 0px solid black;"
            "}"
            "QTreeWidget::item::hover"
            "{"
            "    color: rgb(255, 255, 255);"
            "    background-color: rgb(62, 62, 64);"
            "    border: 0px solid black;"
            "}"
            "QMenuBar::item"
            "{"
            "    background-color: transparent;"
            "}"
            "QMenuBar::item::selected"
            "{"
            "    background-color: rgb(62, 62, 64);"
            "}"
            "QMenuBar::item::pressed"
            "{"
            "    background-color: rgb(27, 27, 28);"
            "}"
            "QMenu::item"
            "{"
            "    background-color: rgb(27, 27, 28);"
            "}"
            "QMenu::item::selected"
            "{"
            "    background-color: rgb(45, 45, 48);"
            "}"
            "QMenu::item::pressed"
            "{"
            "    background-color: rgb(45, 45, 48);"
            "}"
            "QMenu::separator"
            "{" 
            "    border-color: rgb(197, 197, 197);" 
            "}";

        const QString GeneralStyles::frameStyle =
            ""
            "";

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