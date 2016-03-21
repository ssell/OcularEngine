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
#include "Widgets/Properties/Types/FileProperty.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::FileProperty, Ocular::Utils::TypeName<Ocular::Core::File>::name);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        FileProperty::FileProperty(QWidget* parent)
            : PropertyWidget(parent)
        {
            m_LineValue = new LineEdit(LineType::String);
            m_ButtonBrowse = new ButtonFileBrowse();

            m_LayoutRight->addWidget(m_LineValue);
            m_LayoutRight->addWidget(m_ButtonBrowse);
        }

        FileProperty::~FileProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool FileProperty::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                Core::File* value = void_cast<Core::File*>(m_Variable.data);
                
                if(m_ButtonBrowse->wasEdited())
                {
                    (*value).setPath(m_ButtonBrowse->getSelectedFile());
                    m_LineValue->setText(m_ButtonBrowse->getSelectedFile().c_str());

                    result = true;
                }
                else
                {
                    if(m_LineValue->wasEdited())
                    {
                        (*value).setPath(m_LineValue->text().toStdString());
                        result = true;
                    }
                    else if(!m_LineValue->hasFocus())
                    {
                        m_LineValue->setText((*value).getFullPath().c_str());
                    }
                }
            }

            return result;
        }

        void FileProperty::setNameFilter(std::string const& filter)
        {
            m_ButtonBrowse->setNameFilter(filter);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}