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
#include "Widgets/Properties/Types/Vector3Property.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"
#include "Math/Vector3.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::Vector3Property, Ocular::Utils::TypeName<Ocular::Math::Vector3f>::name);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        Vector3Property::Vector3Property(QWidget* parent)
            : PropertyWidget(parent)
        {
            m_LabelX = new QLabel("X");
            m_LabelY = new QLabel("Y");
            m_LabelZ = new QLabel("Z");
            
            m_EditX = new LineEdit(LineType::Float);
            m_EditY = new LineEdit(LineType::Float);
            m_EditZ = new LineEdit(LineType::Float);
            
            m_LayoutRight->addWidget(m_LabelX);
            m_LayoutRight->addWidget(m_EditX);
            m_LayoutRight->addWidget(m_LabelY);
            m_LayoutRight->addWidget(m_EditY);
            m_LayoutRight->addWidget(m_LabelZ);
            m_LayoutRight->addWidget(m_EditZ);
        }

        Vector3Property::~Vector3Property()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool Vector3Property::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                Math::Vector3f* vector = void_cast<Math::Vector3f*>(m_Variable.data);

                if(m_EditX->wasEdited())
                {
                    (*vector).x = m_EditX->asFloat();
                    result = true;
                }
                else if(!m_EditX->hasFocus())
                {
                    m_EditX->setText(OcularString->toString<float>(vector->x).c_str());
                }

                if(m_EditY->wasEdited())
                {
                    (*vector).y = m_EditY->asFloat();
                    result = true;
                }
                else if(!m_EditY->hasFocus())
                {
                    m_EditY->setText(OcularString->toString<float>(vector->y).c_str());
                }

                if(m_EditZ->wasEdited())
                {
                    (*vector).z = m_EditZ->asFloat();
                    result = true;
                }
                else if(!m_EditZ->hasFocus())
                {
                    m_EditZ->setText(OcularString->toString<float>(vector->z).c_str());
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}