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
            
            m_Materials.push_back(dynamic_cast<Graphics::Material*>(OcularResources->getEmptyResource(ResourceType::Material)));
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
                            OcularGraphics->renderMesh(m_Mesh, i);
                        }
                    }
                }
            }
        }

        void MeshRenderable::render(Graphics::Material* material)
        {
            if(m_Mesh && material)
            {
                material->bind();

                const uint32_t submeshCount = m_Mesh->getNumSubMeshes();

                for(uint32_t i = 0; i < submeshCount; i++)
                {
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
                            setMaterial(mappingName, i, true);
                        }
                    }
                }
            }
        }

        void MeshRenderable::onSave(BuilderNode* node) const
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

        void MeshRenderable::buildBounds(Math::BoundsSphere* sphere, Math::BoundsAABB* aabb, Math::BoundsOBB* obb, Math::Matrix4x4 const& matrix)
        {
            if(m_Mesh)
            {
                //--------------------------------------------------------
                // Get all vertex buffers

                const uint32_t numVBs = m_Mesh->getNumSubMeshes();

                if(numVBs)
                {
                    std::vector<Graphics::VertexBuffer*> vbs(numVBs, nullptr);

                    for(uint32_t i = 0; i < numVBs; ++i)
                    {
                        vbs[i] = m_Mesh->getVertexBuffer(i);
                    }

                    //----------------------------------------------------
                    // Build sphere bounds

                    if(sphere)
                    {
                        // Build individual bound for each vb

                        std::vector<Math::BoundsSphere> bounds(numVBs);

                        for(uint32_t i = 0; i < numVBs; ++i)
                        {
                            bounds[i].construct(vbs[i]->getVertices(), matrix);
                        }

                        // Combine bounds

                        sphere->setCenter(bounds[0].getCenter());
                        sphere->setRadius(bounds[0].getRadius());

                        for(uint32_t i = 1; i < numVBs; ++i)
                        {
                            sphere->expandToContain(bounds[i]);
                        }
                    }

                    //----------------------------------------------------
                    // Build aabb

                    if(aabb)
                    {
                        // Build individaul bound for each vb

                        std::vector<Math::BoundsAABB> bounds(numVBs);

                        for(uint32_t i = 0; i < numVBs; ++i)
                        {
                            bounds[i].construct(vbs[i]->getVertices(), matrix);
                        }

                        // Combine bounds

                        aabb->setCenter(bounds[0].getCenter());
                        aabb->setExtents(bounds[0].getExtents());

                        for(uint32_t i = 1; i < numVBs; ++i)
                        {
                            aabb->expandToContain(bounds[i]);
                        }
                    }

                    //----------------------------------------------------
                    // Build obb

                    // not yet available ...
                }
            }
        }

        uint32_t MeshRenderable::getRenderPriority() const
        {
            uint32_t result = 0;

            for(auto material : m_Materials)
            {
                result = std::max(result, material->getRenderPriority());
            }

            return result;
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
                if(m_Parent)
                {
                    m_Parent->forceBoundsRebuild();
                }

                result = true;
            }

            return result;
        }

        void MeshRenderable::setMesh(Graphics::Mesh* mesh)
        {
            m_Mesh = mesh;

            if(m_Parent)
            {
                m_Parent->forceBoundsRebuild();
            }
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

        bool MeshRenderable::setMaterial(std::string const& name, uint32_t const index, bool const resize)
        {
            bool result = false;

            if(validateMaterialIndex(index, resize))
            {
                m_Materials[index] = findMaterial(name);
                result = true;
            }

            return result;
        }

        void MeshRenderable::setMaterial(Graphics::Material* material, uint32_t const index, bool const resize)
        {
            if(validateMaterialIndex(index, resize))
            {
                m_Materials[index] = material;
            }
        }

        void MeshRenderable::removeMaterial(uint32_t const index)
        {
            if(index < static_cast<uint32_t>(m_Materials.size()))
            {
                m_Materials.erase(m_Materials.begin() + index);
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

        bool MeshRenderable::validateMaterialIndex(uint32_t const index, bool const resize)
        {
            bool result = false;

            if(index < static_cast<uint32_t>(m_Materials.size()))
            {
                result = true;
            }
            else if(resize)
            {
                m_Materials.resize((index + 1), nullptr);
                result = true;
            }

            return result;
        }

        Graphics::Material* MeshRenderable::findMaterial(std::string const& name)
        {
            auto result = OcularResources->getResource<Graphics::Material>(name);

            if(result == nullptr)
            {
                // Material was not found. Use the default missing material instead
                result = dynamic_cast<Graphics::Material*>(OcularResources->getMissingResource(ResourceType::Material));
                OcularLogger->warning("Unable to find Material '", name, "'; Using default 'Missing' Material", OCULAR_INTERNAL_LOG("MeshRenderable", "findMaterial"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}