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

#include "Scene/Renderables/MeshRenderable.hpp"
#include "Scene/RenderableRegistrar.hpp"

OCULAR_REGISTER_RENDERABLE(Ocular::Core::MeshRenderable, "Mesh");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MeshRenderable::MeshRenderable(std::string const& name, SceneObject* parent)
            : ARenderable(name, "Mesh", parent)
        {
            m_Mesh = dynamic_cast<Graphics::Mesh*>(OcularResources->getEmptyResource(ResourceType::Mesh));
            m_Material = dynamic_cast<Graphics::Material*>(OcularResources->getEmptyResource(ResourceType::Material));

            exposeVariable("m_Mesh", Utils::TypeName<Resource>::name, true, false, &m_Mesh);
            exposeVariable("m_Material", Utils::TypeName<Resource>::name, true, false, &m_Material);
        }

        MeshRenderable::~MeshRenderable()
        {
            // Do not delete as Mesh and Materials are shared resources
            m_Mesh = nullptr;
            m_Material = nullptr;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool MeshRenderable::initialize()
        {
            bool result = ARenderable::initialize();

            return result;
        }

        bool MeshRenderable::preRender()
        {
            bool result = false;

            if(ARenderable::preRender())
            {
                if(m_Mesh && m_Material)
                {
                    m_Material->bind();
                    result = true;
                }
            }

            return result;
        }

        void MeshRenderable::render()
        {
            if(m_Mesh)
            {
                OcularGraphics->renderMesh(m_Mesh);
            }
        }

        void MeshRenderable::onLoad(BuilderNode const* node)
        {
            Object::onLoad(node);

            if(node)
            {
                const BuilderNode* meshChild = node->getChild("m_Mesh");
                const BuilderNode* materialChild = node->getChild("m_Material");

                if(meshChild)
                {
                    setMesh(meshChild->getValue());
                }

                if(materialChild)
                {
                    setMaterial(materialChild->getValue());
                }
            }
        }

        void MeshRenderable::onSave(BuilderNode* node)
        {
            Object::onSave(node);

            if(node)
            {
                if(m_Mesh)
                {
                    node->addChild("m_Mesh", Utils::TypeName<std::string>::name, m_Mesh->getMappingName());
                }
                
                if(m_Material)
                {
                    node->addChild("m_Material", Utils::TypeName<std::string>::name, m_Material->getMappingName());
                }
            }
        }

        void MeshRenderable::updateBounds()
        {
            if(m_Parent && m_Mesh)
            {
                auto vertexBuffer = m_Mesh->getVertexBuffer();

                if(vertexBuffer)
                {
                    m_Parent->boundsAABB = Math::BoundsAABB(vertexBuffer->getVertices());
                    m_Parent->boundsSphere = Math::BoundsSphere(vertexBuffer->getVertices());
                }
            }
        }

        //----------------------------------------------------------------
        // Getters / Setters
        //----------------------------------------------------------------

        bool MeshRenderable::setMesh(std::string const& name)
        {
            bool result = false;
            m_Mesh = OcularResources->getResource<Graphics::Mesh>(name);

            if(m_Mesh)
            {
                updateBounds();
                result = true;
            }

            return result;
        }

        void MeshRenderable::setMesh(Graphics::Mesh* mesh)
        {
            m_Mesh = mesh;
            updateBounds();
        }

        Graphics::Mesh* MeshRenderable::getMesh() const
        {
            return m_Mesh;
        }

        bool MeshRenderable::setMaterial(std::string const& name)
        {
            bool result = false;
            m_Material = OcularResources->getResource<Graphics::Material>(name);

            if(m_Material)
            {
                result = true;
            }

            return result;
        }

        void MeshRenderable::setMaterial(Graphics::Material* material)
        {
            m_Material = material;
        }

        Graphics::Material* MeshRenderable::getMaterial() const
        {
            return m_Material;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}