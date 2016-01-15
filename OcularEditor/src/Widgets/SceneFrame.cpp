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

#include "Widgets/SceneFrame.hpp"
#include "Widgets/SceneBox.hpp"
#include "Widgets/ConsoleBox.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneFrame::SceneFrame(QWidget *parent)
            : QFrame(parent)
        {
            setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);setFrameStyle(QFrame::Panel | QFrame::Plain);
            setLineWidth(0);
            setStyleSheet(GeneralStyles::frameStyle);

            m_SceneBox = new SceneBox();
            m_ConsoleBox = new ConsoleBox();
            
            m_pSplitter = new QSplitter();
            m_pSplitter->setOrientation(Qt::Vertical);
            m_pSplitter->addWidget(m_SceneBox);
            m_pSplitter->addWidget(m_ConsoleBox);
            m_pSplitter->setStretchFactor(0, 1);     // When window is resized, the scene tree will take the majority of the stretch difference
                                                     // leaving the console box relatively the same size
            m_Layout = new QVBoxLayout();
            m_Layout->addWidget(m_pSplitter);
            m_Layout->setContentsMargins(0, 0, 0, 0);

            setLayout(m_Layout);
        }

        SceneFrame::~SceneFrame()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize SceneFrame::sizeHint() const
        {
            return QSize(275, 700);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}