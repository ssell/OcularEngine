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
#include "Widgets/Properties/Types/BoolProperty.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::BoolProperty, OCULAR_TYPE_NAME(bool));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        BoolProperty::BoolProperty(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(bool), parent)
        {
            m_CheckValue = new CheckBox();
            m_LayoutRight->addWidget(m_CheckValue);
        }

        BoolProperty::~BoolProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool BoolProperty::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                bool* value = void_cast<bool*>(m_Variable.data);

                if(m_CheckValue->wasEdited())
                {
                    (*value) = m_CheckValue->isChecked();
                    result = true;
                }
                else
                {
                    m_CheckValue->setChecked((*value));
                }
            }

            return result;
        }

        void BoolProperty::setValue(void* value, uint32_t const size)
        {
            if(value && (size == sizeof(bool)))
            {
                bool valueCast = void_cast<bool>(value);

                if(m_Variable.data)
                {
                    bool* valuePtr = void_cast<bool*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_CheckValue->setText(OcularString->toString<bool>(valueCast).c_str());
            }
        }

        std::string BoolProperty::getValue() const
        {
            return OcularString->toString<bool>(m_CheckValue->isChecked());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}