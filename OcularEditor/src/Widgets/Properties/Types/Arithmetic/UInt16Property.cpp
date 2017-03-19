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
#include "Widgets/Properties/Types/Arithmetic/UInt16Property.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::UInt16Property, OCULAR_TYPE_NAME(uint16_t));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        UInt16Property::UInt16Property(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(uint16_t), parent)
        {
            m_EditValue = new LineEdit(LineType::UInt16);
            m_LayoutRight->addWidget(m_EditValue);
        }

        UInt16Property::~UInt16Property()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool UInt16Property::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                uint16_t* value = void_cast<uint16_t*>(m_Variable.data);

                if(m_EditValue->wasEdited())
                {
                    (*value) = m_EditValue->as<uint16_t>();
                    result = true;
                }
                else if(!m_EditValue->hasFocus())
                {
                    m_EditValue->setText(OcularString->toString<uint16_t>(*value).c_str());
                }
            }

            return result;
        }

        void UInt16Property::setValue(void* value, uint32_t const size)
        {
            if(value && (size == sizeof(uint16_t)))
            {
                uint16_t valueCast = void_cast<uint16_t>(value);

                if(m_Variable.data)
                {
                    uint16_t* valuePtr = void_cast<uint16_t*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_EditValue->setText(OcularString->toString<uint16_t>(valueCast).c_str());
            }
        }

        std::string UInt16Property::getValue() const
        {
            return m_EditValue->text().toStdString();
        }

        LineEdit* UInt16Property::getLineEdit()
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