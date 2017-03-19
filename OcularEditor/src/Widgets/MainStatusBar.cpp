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
#include "Widgets/MainStatusBar.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MainStatusBar::MainStatusBar(QWidget *parent)
            : QStatusBar(parent),
              m_PermanentMessageLabel(new QLabel())
        {
            m_PermanentMessageLabel->setStyleSheet("QLabel { color: rgb(91, 91, 91); background-color: rgba(0, 0, 0, 0); }");
            addPermanentWidget(m_PermanentMessageLabel);
        }

        MainStatusBar::~MainStatusBar()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void MainStatusBar::setPermanentMessage(std::string const& message)
        {
            m_PermanentMessageLabel->setText(message.c_str());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}