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

#include "Widgets/Properties/Renderables/MeshRenderableDisplay.hpp"
#include "Widgets/Properties/Renderables/MeshRenderableDisplayMaterial.hpp"
#include "Widgets/Properties/Renderables/RenderableDisplayRegistrar.hpp"
#include "Widgets/Properties/Types/ResourceProperty.hpp"

#include "Scene/Renderables/MeshRenderable.hpp"

OCULAR_REGISTER_RENDERABLE_DISPLAY(Ocular::Editor::MeshRenderableDisplay, "MeshRenderable");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MeshRenderableDisplay::MeshRenderableDisplay(QWidget* parent)
            : RenderableDisplay("MeshRenderable", parent),
              m_MeshProperty(nullptr)
        {

        }

        MeshRenderableDisplay::~MeshRenderableDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void MeshRenderableDisplay::updateProperties()
        {
            if(m_Object)
            {
                bool updated = false;

                // Make sure the Renderable is still valid and has not been removed
                m_Renderable = m_Object->getRenderable();

                if(m_Renderable)
                {
                    //----------------------------------------------------
                    // Update Mesh
                    //----------------------------------------------------

                    if(m_MeshProperty)
                    {
                        // If the Mesh was changed
                        if(m_MeshProperty->updateProperties())
                        {
                            updated = true;

                            // Rebuild this display

                            removeProperties();
                            buildProperties();
                        }
                    }
                    
                    //----------------------------------------------------
                    // Update Materials
                    //----------------------------------------------------

                    for(auto materialProp : m_MaterialProperties)
                    {
                        if(materialProp)
                        {
                            if(materialProp->wasEdited())
                            {
                                updated = true;

                                Core::MeshRenderable* renderable = dynamic_cast<Core::MeshRenderable*>(m_Renderable);
                                
                                if(renderable)
                                {
                                    renderable->setMaterial(materialProp->getMaterialMapping(), materialProp->getMaterialIndex(), true);
                                }
                            }
                        }
                    }
                }
                else
                {
                    removeProperties();
                }

                if(updated)
                {
                    m_Renderable->updateBounds();
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void MeshRenderableDisplay::buildProperties()
        {
            buildMeshProperty();
            buildMaterialProperties();
        }

        void MeshRenderableDisplay::removeProperties()
        {
            if(m_MeshProperty)
            {
                m_Layout->removeWidget(m_MeshProperty);
                delete m_MeshProperty;
                m_MeshProperty = nullptr;
            }

            for(auto material : m_MaterialProperties)
            {
                if(material)
                {
                    m_Layout->removeWidget(material);
                    delete material;
                    material = nullptr;
                }
            }

            m_MaterialProperties.clear();
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void MeshRenderableDisplay::buildMeshProperty()
        {
            const std::string name = "m_Mesh";

            Core::ExposedVariable exposed;
            m_Renderable->getVariable(name, exposed);

            m_MeshProperty = dynamic_cast<ResourceProperty*>(OcularEditor.createPropertyWidget(OcularEditor.FormatName(name), exposed.type));

            if(m_MeshProperty)
            {
                m_Layout->addWidget(m_MeshProperty);
                        
                m_MeshProperty->setVariable(exposed);

                if(OcularString->IsEqual(exposed.type, Utils::TypeName<Core::Resource>::name))
                {
                    ResourceProperty* prop = dynamic_cast<ResourceProperty*>(m_MeshProperty);

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

        void MeshRenderableDisplay::buildMaterialProperties()
        {
            Core::MeshRenderable* renderable = dynamic_cast<Core::MeshRenderable*>(m_Renderable);

            if(renderable)
            {
                auto mesh = renderable->getMesh();

                if(mesh)
                {
                    const uint32_t numSubmeshes = mesh->getNumSubMeshes();

                    for(uint32_t i = 0; i < numSubmeshes; i++)
                    {
                        MeshRenderableDisplayMaterial* materialProperty = new MeshRenderableDisplayMaterial(i);
                        m_Layout->addWidget(materialProperty);

                        Graphics::Material* material = renderable->getMaterial(i);

                        if(material)
                        {
                            materialProperty->setMaterialMapping(material->getMappingName());
                        }

                        m_MaterialProperties.push_back(materialProperty);
                    }
                }
            }
        }
    }
}