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
#include "Widgets/DetailsFrame.hpp"
#include "Widgets/PropertiesBox.hpp"
#include "Widgets/PropertiesPanel.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        DetailsFrame::DetailsFrame(QWidget *parent)
            : QFrame(parent)
        {
            setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
            setFrameStyle(QFrame::Panel | QFrame::Plain);
            setStyleSheet(GeneralStyles::frameStyle);
            setLineWidth(0);

            m_PropertiesBox = new PropertiesBox();

            m_Layout = new QVBoxLayout();
            m_Layout->addWidget(m_PropertiesBox);
            m_Layout->setContentsMargins(0, 0, 0, 0);
            
            setLayout(m_Layout);
        }

        DetailsFrame::~DetailsFrame()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize DetailsFrame::sizeHint() const
        {
            return QSize(275, 700);
        }

        PropertiesPanel* DetailsFrame::getPropertiesPanel()
        {
            return m_PropertiesBox->getPropertiesPanel();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}