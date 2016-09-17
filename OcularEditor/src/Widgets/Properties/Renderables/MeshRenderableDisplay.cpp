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

#include "Widgets/Properties/Renderables/MeshRenderableDisplay.hpp"
#include "Widgets/Properties/Renderables/MeshRenderableDisplayMaterial.hpp"
#include "Widgets/Properties/Renderables/RenderableDisplayRegistrar.hpp"
#include "Widgets/Properties/Types/ResourceProperty.hpp"
#include "Widgets/Properties/SelectResourceDialog.hpp"

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
              m_MeshProperty(nullptr),
              m_ButtonAddMaterial(nullptr),
              m_ButtonRemoveMaterial(nullptr),
              m_FrameAddRemove(nullptr),
              m_LayoutAddRemove(nullptr)
        {

        }

        MeshRenderableDisplay::~MeshRenderableDisplay()
        {
            removeProperties();

            delete m_ButtonAddMaterial;
            delete m_ButtonRemoveMaterial;
            delete m_LayoutAddRemove;
            delete m_FrameAddRemove;
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
                    m_Object->forceBoundsRebuild();
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
            buildMaterialAddRemove();
        }

        void MeshRenderableDisplay::removeProperties()
        {
            //------------------------------------------------------------
            // Delete the Mesh property

            delete m_MeshProperty;
            m_MeshProperty = nullptr;
            
            //------------------------------------------------------------
            // Delete the Material properties

            for(auto material : m_MaterialProperties)
            {
                delete material;
            }

            m_MaterialProperties.clear();
            
            //------------------------------------------------------------
            // Remove but do not delete the add/remove buttons

            if(m_FrameAddRemove)
            {
                m_Layout->removeWidget(m_FrameAddRemove);
                m_FrameAddRemove->setVisible(false);
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE SLOTS
        //----------------------------------------------------------------------------------

        void MeshRenderableDisplay::onButtonAddMaterialClick()
        {
            SelectResourceDialog dialog(Core::ResourceType::Material);

            if(dialog.exec())
            {
                Core::MeshRenderable* renderable = dynamic_cast<Core::MeshRenderable*>(m_Renderable);

                if(renderable)
                {
                    renderable->addMaterial(OcularResources->getResource<Graphics::Material>(dialog.getSelectedName()));
 
                    removeProperties();
                    buildProperties();
                }
            }
        }

        void MeshRenderableDisplay::onButtonRemoveMaterialClick()
        {
            Core::MeshRenderable* renderable = dynamic_cast<Core::MeshRenderable*>(m_Renderable);

            if(renderable)
            {
                renderable->removeMaterial(renderable->getNumMaterials() - 1);
            }

            auto back = m_MaterialProperties.back();
            delete back;

            m_MaterialProperties.pop_back();

            removeProperties();
            buildProperties();
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
                    const uint32_t numMax = std::max(mesh->getNumSubMeshes(), renderable->getNumMaterials());

                    for(uint32_t i = 0; i < numMax; i++)
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

        void MeshRenderableDisplay::buildMaterialAddRemove()
        {
            if(m_FrameAddRemove == nullptr)
            {
                m_FrameAddRemove = new QFrame();
                m_LayoutAddRemove = new QHBoxLayout();

                m_ButtonRemoveMaterial = new QPushButton("Remove Material");
                m_ButtonRemoveMaterial->setMaximumWidth(150);
                m_ButtonRemoveMaterial->setMinimumHeight(20);
                m_ButtonRemoveMaterial->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

                m_ButtonAddMaterial = new QPushButton("AddMaterial");
                m_ButtonAddMaterial->setMaximumWidth(150);
                m_ButtonAddMaterial->setMinimumHeight(20);
                m_ButtonAddMaterial->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
                
                connect(m_ButtonRemoveMaterial, SIGNAL(clicked()), this, SLOT(onButtonRemoveMaterialClick()));
                connect(m_ButtonAddMaterial, SIGNAL(clicked()), this, SLOT(onButtonAddMaterialClick()));

                m_LayoutAddRemove->addWidget(m_ButtonRemoveMaterial);
                m_LayoutAddRemove->addWidget(m_ButtonAddMaterial);

                m_FrameAddRemove->setLayout(m_LayoutAddRemove);
            }
            
            m_Layout->addWidget(m_FrameAddRemove);
            m_FrameAddRemove->setVisible(true);

            if(m_MaterialProperties.size())
            {
                m_ButtonRemoveMaterial->setVisible(true);
            }
            else
            {
                m_ButtonRemoveMaterial->setVisible(false);
            }
        }
    }
}