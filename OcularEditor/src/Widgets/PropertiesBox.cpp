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

        PropertiesBox::PropertiesBox(QWidget *parent)
            : QGroupBox("Properties", parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            m_PropertiesPanel = new PropertiesPanel();

            m_Layout = new QVBoxLayout();
            m_Layout->setAlignment(Qt::AlignTop);
            m_Layout->addWidget(m_PropertiesPanel);
            m_Layout->setContentsMargins(0, 16, 0, 5);

            setLayout(m_Layout);
        }

        PropertiesBox::~PropertiesBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize PropertiesBox::sizeHint() const
        {
            return QSize(275, 500);
        }

        PropertiesPanel* PropertiesBox::getPropertiesPanel()
        {
            return m_PropertiesPanel;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}