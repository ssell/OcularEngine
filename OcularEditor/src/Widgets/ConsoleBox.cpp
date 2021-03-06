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
#include "Widgets/ConsoleBox.hpp"
#include "Widgets/ConsoleText.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ConsoleBox::ConsoleBox(QWidget *parent)
            : QGroupBox("Console", parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            m_ConsoleText = new ConsoleText();

            m_Layout = new QVBoxLayout();
            m_Layout->addWidget(m_ConsoleText);
            m_Layout->setContentsMargins(5, 25, 5, 5);

            setLayout(m_Layout);
        }

        ConsoleBox::~ConsoleBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ConsoleBox::sizeHint() const
        {
            return QSize(275, 175);
        }

        ConsoleText* ConsoleBox::getConsoleText() const
        {
            return m_ConsoleText;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}