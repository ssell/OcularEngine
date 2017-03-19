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
#include "Widgets/MaterialEditor/MaterialPropertiesDisplayBox.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MaterialPropertiesDisplayBox::MaterialPropertiesDisplayBox(std::string const& displayName, QWidget* parent)
            : PropertiesDisplayBox(displayName, true, false, parent)
        {
            hide();
        }

        MaterialPropertiesDisplayBox::~MaterialPropertiesDisplayBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void MaterialPropertiesDisplayBox::setObject(Core::SceneObject* object)
        {
            // Do nothing as we are only interested in materials.
            // This is probably a design flaw in PropertiesDisplayBox...
        }

        void MaterialPropertiesDisplayBox::setMaterial(Graphics::Material* material)
        {
            releaseProperties();
            m_Material = material;

            if(m_Material)
            {
                show();
            }
            else
            {
                hide();
            }
        }

        void MaterialPropertiesDisplayBox::updateProperties()
        {

        }

        void MaterialPropertiesDisplayBox::onApply()
        {

        }
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void MaterialPropertiesDisplayBox::releaseProperties()
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