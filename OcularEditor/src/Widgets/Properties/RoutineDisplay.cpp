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
#include "Widgets/Properties/RoutineDisplay.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        RoutineDisplay::RoutineDisplay(std::string const& routineName, QWidget* parent)
            : PropertiesDisplayBox("Routine", parent),
              m_Routine(nullptr),
              m_RoutineName(routineName)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        }

        RoutineDisplay::~RoutineDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void RoutineDisplay::setObject(Core::SceneObject* object)
        {
            if(m_Object != object)
            {
                m_Object = object;
                removeProperties();

                if(m_Object)
                {
                    m_Routine = m_Object->getRoutine(m_RoutineName);
                    buildProperties();
                }
            }
        }

        void RoutineDisplay::updateProperties()
        {
            if(m_Object)
            {
                // Make sure the Routine is still valid and has not been removed
                m_Routine = m_Object->getRoutine(m_RoutineName);

                if(m_Routine)
                {
                    for(auto prop : m_Properties)
                    {
                        if(prop)
                        {
                            prop->updateProperties();
                        }
                    }
                }
                else
                {
                    removeProperties();
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void RoutineDisplay::buildProperties()
        {
            std::vector<std::string> exposedNames;
            m_Object->getAllExposedNames(exposedNames);

            for(auto name : exposedNames)
            {
                if(!OcularEditor.IsCommonName(name))
                {
                    Core::ExposedVariable exposed;
                    m_Object->getVariable(name, exposed);

                    PropertyWidget* widget = OcularEditor.createPropertyWidget(exposed.name, exposed.type);

                    if(widget)
                    {
                        m_Properties.push_back(widget);
                    }
                }
            }
        }

        void RoutineDisplay::removeProperties()
        {
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
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}