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
#include "Widgets/Properties/Types/MultiProperty.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MultiProperty::MultiProperty(QWidget* parent)
            : PropertyWidget("MultiProperty", parent)
        {

        }

        MultiProperty::~MultiProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool MultiProperty::updateProperties()
        {
            return false;
        }

        uint32_t MultiProperty::addProperty(std::string const& name, LineType type)
        {
            uint32_t index = static_cast<uint32_t>(m_Properties.size());

            QLabel* label = new QLabel(name.c_str());
            LineEdit* edit = new LineEdit(type);

            m_LayoutRight->addWidget(label);
            m_LayoutRight->addWidget(edit);

            m_Properties.push_back(std::make_pair(label, edit));

            return 0;
        }

        QLabel* MultiProperty::getLabel(uint32_t const index)
        {
            QLabel* result = nullptr;

            if(index < static_cast<uint32_t>(m_Properties.size()))
            {
                result = m_Properties[index].first;
            }

            return result;
        }

        LineEdit* MultiProperty::getLineEdit(uint32_t const index)
        {
            LineEdit* result = nullptr;

            if(index < static_cast<uint32_t>(m_Properties.size()))
            {
                result = m_Properties[index].second;
            }

            return result;
        }

        uint32_t MultiProperty::getNumProperties() const
        {
            return static_cast<uint32_t>(m_Properties.size());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}