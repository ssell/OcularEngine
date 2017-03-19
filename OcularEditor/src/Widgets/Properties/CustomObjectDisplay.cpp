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
                        if(!OcularEditor.IsCommonName(name))
                        {
                            Core::ExposedVariable variable;

                            if(object->getVariable(name, variable))
                            {
                                PropertyWidget* widget = OcularEditor.createPropertyWidget(OcularEditor.FormatName(variable.name), variable.type);

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
                        if(prop->updateProperties())
                        {
                            m_Object->onVariableModified(prop->getVariableName());
                        }
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}