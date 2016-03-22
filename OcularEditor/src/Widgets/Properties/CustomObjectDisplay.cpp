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
#include "Widgets/Properties/CustomObjectDisplay.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CustomObjectDisplay::CustomObjectDisplay(QWidget* parent)
            : PropertiesDisplayBox("Custom", parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        }

        CustomObjectDisplay::~CustomObjectDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void CustomObjectDisplay::setObject(Core::SceneObject* object)
        {
            if(m_Object != object)
            {
                m_Object = object;

                for(auto prop : m_Properties)
                {
                    if(prop)
                    {
                        m_Layout->removeWidget(prop);
                        delete prop;
                        prop = nullptr;
                    }
                }

                m_Properties.clear();

                //--------------------------------------------------------

                if(m_Object)
                {
                    std::vector<std::string> exposedNames;
                    object->getAllExposedNames(exposedNames);

                    for(auto name : exposedNames)
                    {
                        if(!isCommonName(name))
                        {
                            Core::ExposedVariable variable;

                            if(object->getVariable(name, variable))
                            {
                                PropertyWidget* widget = OcularEditor.createPropertyWidget(variable.name, variable.type);

                                if(widget)
                                {
                                    m_Properties.push_back(widget);
                                    m_Layout->addWidget(widget);
                                    widget->setVariable(variable);
                                }
                            }
                        }
                    }
                }
            }
        }

        void CustomObjectDisplay::updateProperties()
        {
            if(m_Object)
            {
                for(auto prop : m_Properties)
                {
                    if(prop)
                    {
                        prop->updateProperties();
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool CustomObjectDisplay::isCommonName(std::string const& name)
        {
            bool result = false;

            static std::string CommonNames[7] =
            {
                "m_Name",
                "m_Position",
                "m_Rotation",
                "m_Scale",
                "m_Class",
                "m_IsStatic",
                "m_ForcedVisible"
            };

            for(auto commonName : CommonNames)
            {
                if(Utils::String::IsEqual(name, commonName))
                {
                    result = true;
                    break;
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}