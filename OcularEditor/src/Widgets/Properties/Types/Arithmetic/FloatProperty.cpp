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
#include "Widgets/Properties/Types/Arithmetic/FloatProperty.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::FloatProperty, Ocular::Utils::TypeName<float>::name);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        FloatProperty::FloatProperty(QWidget* parent)
            : PropertyWidget(parent)
        {
            m_EditValue = new LineEdit(LineType::Float);
            m_LayoutRight->addWidget(m_EditValue);
        }

        FloatProperty::~FloatProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool FloatProperty::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                float* value = void_cast<float*>(m_Variable.data);

                if(m_EditValue->wasEdited())
                {
                    (*value) = m_EditValue->asFloat();
                    result = true;
                }
                else if(!m_EditValue->hasFocus())
                {
                    m_EditValue->setText(OcularString->toString<float>(*value).c_str());
                }
            }

            return result;
        }

        bool FloatProperty::wasEdited(bool reset)
        {
            return m_EditValue->wasEdited(reset);
        }

        void FloatProperty::setValue(float value)
        {
            m_EditValue->setText(OcularString->toString<float>(value).c_str());
        }

        float FloatProperty::getValue() const
        {
            return OcularString->fromString<float>(m_EditValue->text().toStdString());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}