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
#include "Widgets/Properties/Types/Arithmetic/DoubleProperty.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::DoubleProperty, OCULAR_TYPE_NAME(double));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        DoubleProperty::DoubleProperty(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(double), parent)
        {
            m_EditValue = new LineEdit(LineType::Double);
            m_LayoutRight->addWidget(m_EditValue);
        }

        DoubleProperty::~DoubleProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool DoubleProperty::updateProperties()
        {
            bool result = false;

            /*if(m_Variable.data)
            {
                double* value = void_cast<double*>(m_Variable.data);

                if(m_EditValue->wasEdited())
                {
                    (*value) = m_EditValue->as<double>();
                    result = true;
                }
                else if(!m_EditValue->hasFocus())
                {
                    m_EditValue->setText(OcularString->toString<double>(*value).c_str());
                }
            }*/

            return result;
        }

        void DoubleProperty::setValue(void* value, uint32_t const size)
        {
            /*if(value && (size == sizeof(double)))
            {
                double valueCast = void_cast<double>(value);

                if(m_Variable.data)
                {
                    double* valuePtr = void_cast<double*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_EditValue->setText(OcularString->toString<double>(valueCast).c_str());
            }*/
        }

        std::string DoubleProperty::getValue() const
        {
            return m_EditValue->text().toStdString();
        }

        LineEdit* DoubleProperty::getLineEdit()
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