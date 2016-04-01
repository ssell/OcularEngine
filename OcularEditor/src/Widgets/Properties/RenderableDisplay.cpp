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
#include "Widgets/Properties/RenderableDisplay.hpp"
#include "Widgets/Properties/Types/ResourceProperty.hpp"
#include "Scene/ARenderable.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        RenderableDisplay::RenderableDisplay(QWidget* parent)
            : PropertiesDisplayBox("Renderable", true, true, parent),
              m_Renderable(nullptr)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        }

        RenderableDisplay::~RenderableDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void RenderableDisplay::setObject(Core::SceneObject* object)
        {
            if(m_Object != object)
            {
                m_Object = object;
                removeProperties();

                if(m_Object)
                {
                    m_Renderable = m_Object->getRenderable();
                    buildProperties();
                }
            }
        }

        void RenderableDisplay::updateProperties()
        {
            if(m_Object)
            {
                // Make sure the Renderable is still valid and has not been removed
                m_Renderable = m_Object->getRenderable();

                if(m_Renderable)
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

        void RenderableDisplay::buildProperties()
        {
            std::vector<std::string> exposedNames;
            m_Renderable->getAllExposedNames(exposedNames);

            for(auto name : exposedNames)
            {
                if(!OcularEditor.IsCommonName(name))
                {
                    Core::ExposedVariable exposed;
                    m_Renderable->getVariable(name, exposed);

                    PropertyWidget* widget = OcularEditor.createPropertyWidget(OcularEditor.FormatName(name), exposed.type);

                    if(widget)
                    {
                        m_Properties.push_back(widget);
                        m_Layout->addWidget(widget);
                        
                        widget->setVariable(exposed);

                        if(OcularString->IsEqual(exposed.type, Utils::TypeName<Core::Resource>::name))
                        {
                            ResourceProperty* prop = dynamic_cast<ResourceProperty*>(widget);

                            if(prop)
                            {
                                Core::Resource** resource = (Core::Resource**)(exposed.data);

                                if((resource != nullptr) && ((*resource) != nullptr))
                                {
                                    prop->setResourceType((*resource)->getResourceType());
                                }
                            }
                        }
                    }
                }
            }
        }

        void RenderableDisplay::removeProperties()
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