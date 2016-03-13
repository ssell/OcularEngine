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
#include "Widgets/Properties/QuatAsEulerProperty.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Euler.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        QuatAsEulerProperty::QuatAsEulerProperty(QString const& displayName, QWidget* parent)
            : PropertyWidget(displayName, parent)
        {
            m_LabelX = new QLabel("X");
            m_LabelY = new QLabel("Y");
            m_LabelZ = new QLabel("Z");
            
            m_EditX = new QLineEdit();
            m_EditY = new QLineEdit();
            m_EditZ = new QLineEdit();
            
            m_LayoutRight->addWidget(m_LabelX);
            m_LayoutRight->addWidget(m_EditX);
            m_LayoutRight->addWidget(m_LabelY);
            m_LayoutRight->addWidget(m_EditY);
            m_LayoutRight->addWidget(m_LabelZ);
            m_LayoutRight->addWidget(m_EditZ);
        }

        QuatAsEulerProperty::~QuatAsEulerProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void QuatAsEulerProperty::updateProperties()
        {
            if(m_Variable.data)
            {
                Math::Quaternion quaternion = void_cast<Math::Quaternion>(m_Variable.data);
                Math::Euler euler(quaternion);

                if(!m_EditX->hasFocus())
                {
                    m_EditX->setText(OcularString->toString<float>(euler.getPitch()).c_str());
                    m_EditX->setCursorPosition(0);
                }

                if(!m_EditY->hasFocus())
                {
                    m_EditY->setText(OcularString->toString<float>(euler.getYaw()).c_str());
                    m_EditY->setCursorPosition(0);
                }

                if(!m_EditZ->hasFocus())
                {
                    m_EditZ->setText(OcularString->toString<float>(euler.getRoll()).c_str());
                    m_EditZ->setCursorPosition(0);
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}