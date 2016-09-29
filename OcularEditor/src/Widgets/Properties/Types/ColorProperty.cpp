/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Widgets/Properties/Types/ColorProperty.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::ColorProperty, Ocular::Utils::TypeName<Ocular::Core::Color>::name);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        ColorProperty::ColorProperty(QWidget* parent)
            : PropertyWidget(Ocular::Utils::TypeName<Ocular::Core::Color>::name, parent)
        {
            m_ColorPreview = new ColorPreview();
            m_ButtonColor = new ButtonColorPicker();
            
            m_LayoutRight->addWidget(m_ColorPreview);
            m_LayoutRight->addWidget(m_ButtonColor);

            connect(m_ButtonColor, SIGNAL(clicked()), this, SLOT(onColorPicked()));
        }

        ColorProperty::~ColorProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool ColorProperty::updateProperties()
        {
            bool result = false;

            auto color = m_ButtonColor->getSelectedColor();

            if(m_Variable.data)
            {
                Core::Color* value = void_cast<Core::Color*>(m_Variable.data);
                
                if(m_ButtonColor->wasEdited())
                {
                    (*value) = color;
                    m_ColorPreview->setColor(color);

                    result = true;
                }
                else
                {
                    m_ColorPreview->setColor(color);
                }
            }
            else
            {
                m_ColorPreview->setColor(color);
            }

            return result;
        }

        void ColorProperty::setValue(void* value, uint32_t const size)
        {
            if(value && (size == sizeof(Core::Color)))
            {
                Core::Color valueCast = void_cast<Core::Color>(value);

                if(m_Variable.data)
                {
                    Core::Color* valuePtr = void_cast<Core::Color*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_ColorPreview->setColor(valueCast);
            }
        }

        std::string ColorProperty::getValue() const
        {
            auto color = m_ColorPreview->getColor();
            return OcularString->toString<Core::Color>(color);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void ColorProperty::onColorPicked()
        {
            updateProperties();
        }
    }
}