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
#include "Widgets/Properties/Types/StringProperty.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::StringProperty, OCULAR_TYPE_NAME(std::string));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        StringProperty::StringProperty(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(std::string), parent)
        {
            m_LineValue = new LineEdit(LineType::String);
            m_LayoutRight->addWidget(m_LineValue);
        }

        StringProperty::~StringProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool StringProperty::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                std::string* value = void_cast<std::string*>(m_Variable.data);

                if(m_LineValue->wasEdited())
                {
                    (*value) = m_LineValue->text().toStdString();
                    result = true;
                }
                else
                {
                    m_LineValue->setText((*value).c_str());
                }
            }

            return result;
        }

        void StringProperty::setValue(void* value, uint32_t const size)
        {
            if(value)
            {
                std::string valueCast = void_cast<std::string>(value);

                if(m_Variable.data)
                {
                    std::string* valuePtr = void_cast<std::string*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_LineValue->setText(valueCast.c_str());
            }
        }

        std::string StringProperty::getValue() const
        {
            return m_LineValue->text().toStdString();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}