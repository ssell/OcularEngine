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
#include "Widgets/MaterialEditor/TexturesDisplayBox.hpp"
#include "Widgets/Properties/Types/ResourceProperty.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TexturesDisplayBox::TexturesDisplayBox(QWidget* parent)
            : MaterialPropertiesDisplayBox("Textures", parent)
        {

        }

        TexturesDisplayBox::~TexturesDisplayBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void TexturesDisplayBox::setMaterial(Graphics::Material* material)
        {
            MaterialPropertiesDisplayBox::setMaterial(material);

            if(material)
            {
                auto textures = material->getTextures();

                if(textures)
                {
                    m_Properties.resize(textures->size(), nullptr);

                    for(uint32_t i = 0; i < m_Properties.size(); ++i)
                    {
                        auto textureInfo = textures->at(i);

                        m_Properties[i] = OcularEditor.createPropertyWidget(textureInfo.samplerName, OCULAR_TYPE_NAME(Core::Resource));
                        ResourceProperty* resourceProp = dynamic_cast<ResourceProperty*>(m_Properties[i]);

                        if(resourceProp)
                        {
                            resourceProp->setResourceType(Core::ResourceType::Texture);

                            if(textureInfo.texture)
                            {
                                resourceProp->setValue(void_cast<std::string>(textureInfo.texture->getMappingName()), 0);
                            }
                        }

                        m_Layout->addWidget(m_Properties[i]);
                    }
                }
            }
        }

        void TexturesDisplayBox::updateProperties()
        {

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}