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

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void MeshRenderableDisplay::buildProperties()
        {
            Core::MeshRenderable* renderable = dynamic_cast<Core::MeshRenderable*>(m_Renderable);

            if(renderable)
            {
                //--------------------------------------------------------
                // Mesh Property
                //--------------------------------------------------------

                m_MeshProperty = new ResourceProperty();

                if(m_MeshProperty)
                {
                    m_Layout->addWidget(m_MeshProperty);

                    Core::ExposedVariable meshVar;

                    if(renderable->getVariable("m_Mesh", meshVar))
                    {
                        m_MeshProperty->setVariable(meshVar);
                    }
                }

                //--------------------------------------------------------
                // Material Properties
                //--------------------------------------------------------

                const uint32_t numMaterials = renderable->getNumMaterials();

                for(uint32_t i = 0; i < numMaterials; i++)
                {
                    MeshRenderableDisplayMaterial* materialProperty = new MeshRenderableDisplayMaterial(i);
                    m_Layout->addWidget(materialProperty);

                    Graphics::Material* material = renderable->getMaterial(i);

                    if(material)
                    {
                        materialProperty->setMaterial(material);
                    }
                }
            }
        }

        void MeshRenderableDisplay::removeProperties()
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}