/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
        // Window Style
        //----------------------------------------------------------------------------------

        // (211, 211, 211) : Default Text
        // (255, 255, 255) : Highlighted / Special Text

        // (45, 45, 48) : Normal Background
        // (51, 51, 51) : Grouping Background
        // (56, 56, 60) : Grouping Highlight
        // (27, 27, 28) : Dark Selected
        // (62, 62, 64) : Light Hover

        // (37, 194, 62) : Green Selection
        // (196, 56, 60) : Error Red

        const QString GeneralStyles::windowStyle =

            //------------------------------------------------------------
            // QWidget
            //------------------------------------------------------------

            "QWidget"
            "{"
            "    color: rgb(211, 221, 211);"
            "    background-color: rgb(45, 45, 48);"
            "    border-color: rgb(63, 63, 70);"
            "    outline: 0;"
            "}"

            //------------------------------------------------------------
            // QFrame
            //------------------------------------------------------------

            "QFrame"
            "{"
            "    color: rgb(211, 211, 211);"
            "}"

            //------------------------------------------------------------
            // QLabel
            //------------------------------------------------------------

            "QLabel"
            "{"
            "    color: rgb(211, 211, 211);"
            "    background-color: rgb(56, 56, 60);"
            "}"

            //------------------------------------------------------------
            // QToolButton
            //------------------------------------------------------------

            "QToolButton"
            "{"
            "    border: 0px solid rgb(27, 27, 28);"
            "    padding: 5px;"
            "}"
            "QToolButton:pressed"
            "{"
            "    background-color: rgb(37, 194, 62);"
            "}"
            "QToolButton:hover"
            "{"
            "    border: 0px solid rgb(27, 27, 28);"
            "    background-color: rgb(62, 62, 64);"
            "}"

            //------------------------------------------------------------
            // QPushButton
            //------------------------------------------------------------

            "QPushButton"
            "{"
            "    border: 0px solid rgb(27, 27, 28);"
            "    border-radius: 2px;"
            "}"
            "QPushButton:hover"
            "{"
            "    background-color: rgb(62, 62, 64);"
            "}"
            "QPushButton:pressed"
            "{"
            "    background-color: rgb(37, 194, 62);"
            "}"
            "QPushButton:disabled"
            "{"
            "    color: rgb(125, 125, 125);"
            "}"

            //------------------------------------------------------------
            // QGroupBox
            //------------------------------------------------------------

            "QGroupBox"
            "{"
            "    border: 1px solid rgb(27, 27, 28);"
            "    background-color: rgb(56, 56, 60);"
            "    padding-left: 0px;"
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

            //------------------------------------------------------------
            // QTextEdit
            //------------------------------------------------------------

            "QTextEdit"
            "{"
            "    color: rgb(255, 255, 255);"
            "    selection-background-color: rgb(37, 194, 62);"
            "    border: 0px solid black;"
            "}"

            //------------------------------------------------------------
            // QLineEdit
            //------------------------------------------------------------

            "QLineEdit"
            "{"
            "    selection-background-color: rgb(37, 194, 62);"
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

            //------------------------------------------------------------
            // QTreeWidget
            //------------------------------------------------------------

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
            "    color: rgb(255, 255, 255);"
            "    background-color: rgb(37, 194, 62);"
            "    border: 0px solid black;"
            "}"
            "QTreeWidget::item::selected"
            "{"
            "    color: rgb(255, 255, 255);"
            "    background-color: rgb(37, 194, 62);"
            "    border: 0px solid black;"
            "}"
            "QTreeWidget::branch:selected"
            "{"
            "    background-color: rgb(37, 194, 62);"
            "}"

            //------------------------------------------------------------
            // QMenuBar
            //------------------------------------------------------------

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

            //------------------------------------------------------------
            // QMenu
            //------------------------------------------------------------

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
            "    height: 1px;"
            "    border-color: rgb(197, 197, 197);" 
            "}"
            
            //------------------------------------------------------------
            // QComboBox
            //------------------------------------------------------------
            
            "QComboBox"
            "{"
            "    border: 0px solid rgb(27, 27, 28);"
            "}"
            "QComboBox QAbstractItemView"
            "{"
            "    border: 0px solid rgb(27, 27, 28);"
            "    selection-background-color: rgb(37, 194, 62);"
            "}"
            "QComboBox::drop-down"
            "{"
            "    border: 0px solid rgb(27, 27, 28);"
            "}"

            //------------------------------------------------------------
            // QCheckBox
            //------------------------------------------------------------

            "QCheckBox"
            "{"
            "    background-color: rgba(0, 0, 0, 0);"
            "}"
            "QCheckBox::indicator"
            "{"
            "    selection-color: rgb(66,166,66);"
            "    selection-background-color: (45, 45, 48);"
            "}";


        //----------------------------------------------------------------------------------
        // Frame Styles
        //----------------------------------------------------------------------------------

        const QString GeneralStyles::frameStyle =
            ""
            "";

        //----------------------------------------------------------------------------------
        // Line Edit Valid Styles
        //----------------------------------------------------------------------------------

        const QString GeneralStyles::lineEditValidStyle =
            "QLineEdit"
            "{"
            "    selection-background-color: rgb(37, 194, 62);"
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
            "}";

        //----------------------------------------------------------------------------------
        // Line Edit Invalid Styles
        //----------------------------------------------------------------------------------

        const QString GeneralStyles::lineEditInvalidStyle =
            "QLineEdit"
            "{"
            "    selection-background-color: rgb(37, 194, 62);"
            "    background-color: rgb(45, 45, 48);"
            "    border: 1px solid rgb(196, 56, 60);"
            "    border-radius: 2px;"
            "    padding: 1px;"
            "}"
            "QLineEdit:focus"
            "{"
            "    background-color: rgb(45, 45, 48);"
            "    border: 1px solid rgb(196, 56, 60);"
            "    border-radius: 2px;"
            "    padding: 1px;"
            "}";
    }
}