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
#include "Widgets/Properties/Types/Arithmetic/Int8Property.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::Int8Property, OCULAR_TYPE_NAME(int8_t));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        Int8Property::Int8Property(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(int8_t), parent)
        {
            m_EditValue = new LineEdit(LineType::Int8);
            m_LayoutRight->addWidget(m_EditValue);
        }

        Int8Property::~Int8Property()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool Int8Property::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                int8_t* value = void_cast<int8_t*>(m_Variable.data);

                if(m_EditValue->wasEdited())
                {
                    (*value) = m_EditValue->as<int8_t>();
                    result = true;
                }
                else if(!m_EditValue->hasFocus())
                {
                    m_EditValue->setText(OcularString->toString<int8_t>(*value).c_str());
                }
            }

            return result;
        }

        void Int8Property::setValue(void* value, uint32_t const size)
        {
            if(value && (size == sizeof(int8_t)))
            {
                int8_t valueCast = void_cast<int8_t>(value);

                if(m_Variable.data)
                {
                    int8_t* valuePtr = void_cast<int8_t*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_EditValue->setText(OcularString->toString<int8_t>(valueCast).c_str());
            }
        }

        std::string Int8Property::getValue() const
        {
            return m_EditValue->text().toStdString();
        }

        LineEdit* Int8Property::getLineEdit()
        {
            return m_EditValue;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}