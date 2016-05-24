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

#include "Scene/Renderables/MeshRenderable.hpp"
#include "Scene/RenderableRegistrar.hpp"

#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Material/Material.hpp"

#include "Utilities/StringComposer.hpp"

OCULAR_REGISTER_RENDERABLE(Ocular::Core::MeshRenderable, "MeshRenderable");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MeshRenderable::MeshRenderable(std::string const& name, SceneObject* parent)
            : ARenderable(name, "MeshRenderable", parent)
        {
            m_Mesh = dynamic_cast<Graphics::Mesh*>(OcularResources->getEmptyResource(ResourceType::Mesh));
            exposeVariable("m_Mesh", Utils::TypeName<Resource>::name, true, false, &m_Mesh);
        }

        MeshRenderable::~MeshRenderable()
        {
            // Do not delete as Mesh and Materials are shared resources
            m_Mesh = nullptr;
            m_Materials.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // Inherited Methods
        //----------------------------------------------------------------------------------

        bool MeshRenderable::initialize()
        {
            bool result = ARenderable::initialize();

            return result;
        }

        bool MeshRenderable::preRender()
        {
            bool result = ARenderable::preRender();

            return result;
        }

        void MeshRenderable::render()
        {
            if(m_Mesh)
            {
                const uint32_t submeshCount = m_Mesh->getNumSubMeshes();
                const uint32_t materialCount = getNumMaterials();

                for(uint32_t i = 0; i < submeshCount; i++)
                {
                    if(i < materialCount)
                    {
                        auto material = m_Materials[i];

                        if(material)
                        {
                            material->bind();
                        }
                    }

                    OcularGraphics->renderMesh(m_Mesh, i);
                }
            }
        }

        void MeshRenderable::onLoad(BuilderNode const* node)
        {
            Object::onLoad(node);

            if(node)
            {
                const BuilderNode* meshNode = node->getChild("m_Mesh");
                const BuilderNode* materialsNode = node->getChild("Materials");

                if(meshNode)
                {
                    setMesh(meshNode->getValue());
                }

                if(materialsNode)
                {
                    const uint32_t numChildren = materialsNode->getNumChildren();

                    for(uint32_t i = 0; i < numChildren; i++)
                    {
                        auto materialNode = materialsNode->getChild(OCULAR_STRING_COMPOSER("Material_", i));

                        if(materialNode)
                        {
                            const std::string mappingName = materialNode->getValue();
                            m_Materials.push_back(OcularResources->getResource<Graphics::Material>(mappingName));
                        }
                    }
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
                
                auto materialNode = node->addChild("Materials", "", "");
                
                if(materialNode)
                {
                    uint32_t count = 0;

                    for(auto iter = m_Materials.begin(); iter != m_Materials.end(); ++iter)
                    {
                        auto material = (*iter);

                        if(material)
                        {
                            materialNode->addChild(OCULAR_STRING_COMPOSER("Material_", count++), Utils::TypeName<std::string>::name, material->getMappingName());
                        }
                    }
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

        //----------------------------------------------------------------------------------
        // Mesh Methods
        //----------------------------------------------------------------------------------

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

        //----------------------------------------------------------------------------------
        // Material Methods
        //----------------------------------------------------------------------------------

        uint32_t MeshRenderable::addMaterial(std::string const& name)
        {
            const uint32_t result = static_cast<uint32_t>(m_Materials.size());
            m_Materials.push_back(OcularResources->getResource<Graphics::Material>(name));

            return result;
        }

        uint32_t MeshRenderable::addMaterial(Graphics::Material* material)
        {
            const uint32_t result = static_cast<uint32_t>(m_Materials.size());
            m_Materials.push_back(material);

            return result;
        }

        bool MeshRenderable::setMaterial(std::string const& name, uint32_t const index, bool resize)
        {
            bool result = false;

            if(index < static_cast<uint32_t>(m_Materials.size()))
            {
                m_Materials[index] = OcularResources->getResource<Graphics::Material>(name);
                result = true;
            }
            else if(resize)
            {
                m_Materials.resize((index + 1), nullptr);
                m_Materials[index] = OcularResources->getResource<Graphics::Material>(name);
                result = true;
            }

            return result;
        }

        void MeshRenderable::setMaterial(Graphics::Material* material, uint32_t const index, bool resize)
        {
            if(index < static_cast<uint32_t>(m_Materials.size()))
            {
                m_Materials[index] = material;
            }
            else if(resize)
            {
                m_Materials.resize((index + 1), nullptr);
                m_Materials[index] = material;
            }
        }

        void MeshRenderable::removeMaterial(uint32_t const index)
        {
            if(index < static_cast<uint32_t>(m_Materials.size()))
            {
                m_Materials[index] = nullptr;
            }
        }

        Graphics::Material* MeshRenderable::getMaterial(uint32_t const index) const
        {
            Graphics::Material* result = nullptr;

            if(index < static_cast<uint32_t>(m_Materials.size()))
            {
                result = m_Materials[index];
            }

            return result;
        }

        uint32_t MeshRenderable::getNumMaterials() const
        {
            return static_cast<uint32_t>(m_Materials.size());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}