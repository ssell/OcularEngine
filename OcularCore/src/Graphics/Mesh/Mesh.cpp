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

#include "Graphics/Mesh/Mesh.hpp"

#include "Graphics/Mesh/SubMesh.hpp"
#include "Graphics/Mesh/VertexBuffer.hpp"
#include "Graphics/Mesh/SubMesh.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Mesh::Mesh()
            : Core::Resource()
        {
            m_Type = Core::ResourceType::Mesh;
        }

        Mesh::~Mesh()
        {
            unload();

            while(m_SubMeshes.size())
            {
                delete (*m_SubMeshes.begin());
                m_SubMeshes.erase(m_SubMeshes.begin());
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // Virtual Methods
        //----------------------------------------------------------------------------------

        bool Mesh::bind()
        {
            bool result = true;

            for(auto submesh : m_SubMeshes)
            {
                if(submesh)
                {
                    result = result && submesh->bind();
                }
            }

            return result;
        }

        void Mesh::unbind()
        {
            for(auto submesh : m_SubMeshes)
            {
                if(submesh)
                {
                    submesh->unbind();
                }
            }
        }

        void Mesh::unload()
        {
            for(auto submesh : m_SubMeshes)
            {
                if(submesh)
                {
                    submesh->unload();
                }
            }
        }
        
        //----------------------------------------------------------------------------------
        // Buffer Methods
        //----------------------------------------------------------------------------------

        void Mesh::setVertexBuffer(VertexBuffer* buffer, uint32_t const index)
        {
            if(index < m_SubMeshes.size())
            {
                auto submesh = m_SubMeshes[index];

                if(submesh)
                {
                    submesh->setVertexBuffer(buffer);
                }
            }
        }

        VertexBuffer* Mesh::getVertexBuffer(uint32_t const index)
        {
            VertexBuffer* result = nullptr;

            if(index < m_SubMeshes.size())
            {
                auto submesh = m_SubMeshes[index];

                if(submesh)
                {
                    result = submesh->getVertexBuffer();
                }
            }

            return result;
        }

        void Mesh::setIndexBuffer(IndexBuffer* buffer, uint32_t const index)
        {
            if(index < m_SubMeshes.size())
            {
                auto submesh = m_SubMeshes[index];

                if(submesh)
                {
                    submesh->setIndexBuffer(buffer);
                }
            }
        }

        IndexBuffer* Mesh::getIndexBuffer(uint32_t const index)
        {
            IndexBuffer* result = nullptr;

            if(index < m_SubMeshes.size())
            {
                auto submesh = m_SubMeshes[index];

                if(submesh)
                {
                    result = submesh->getIndexBuffer();
                }
            }

            return result;
        }
        
        //----------------------------------------------------------------------------------
        // Min/Max Point Methods
        //----------------------------------------------------------------------------------

        void Mesh::calculateMinMaxPoints()
        {
            m_MinPoint = Math::Vector3f();
            m_MaxPoint = Math::Vector3f();

            for(auto submesh : m_SubMeshes)
            {
                VertexBuffer* vb = nullptr;  
                
                if(submesh)
                {
                    vb = submesh->getVertexBuffer();
                }

                if(vb)
                {
                    auto vertices = &vb->getVertices();

                    if(vertices)
                    {
                        if(vertices->size())
                        {
                            m_MinPoint = vertices->at(0).position;
                            m_MaxPoint = m_MinPoint;

                            for(auto iter = vertices->begin(); iter != vertices->end(); ++iter)
                            {
                                m_MinPoint.x = std::min(m_MinPoint.x, (*iter).position.x);
                                m_MinPoint.y = std::min(m_MinPoint.y, (*iter).position.y);
                                m_MinPoint.z = std::min(m_MinPoint.z, (*iter).position.z);

                                m_MaxPoint.x = std::max(m_MaxPoint.x, (*iter).position.x);
                                m_MaxPoint.y = std::max(m_MaxPoint.y, (*iter).position.y);
                                m_MaxPoint.z = std::max(m_MaxPoint.z, (*iter).position.z);
                            }
                        }
                    }
                }
            }
        }

        void Mesh::setMinMaxPoints(Math::Vector3f const& min, Math::Vector3f const& max)
        {
            m_MinPoint = min;
            m_MaxPoint = max;
        }

        Math::Vector3f const& Mesh::getMinPoint() const
        {
            return m_MinPoint;
        }

        Math::Vector3f const& Mesh::getMaxPoint() const
        {
            return m_MaxPoint;
        }

        //----------------------------------------------------------------------------------
        // Sub-Mesh Methods
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}