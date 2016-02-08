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

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Mesh::Mesh()
            : Core::Resource(),
              m_VertexBuffer(nullptr),
              m_IndexBuffer(nullptr)
        {
            m_Type = Core::ResourceType::Mesh;
        }

        Mesh::~Mesh()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool Mesh::bind()
        {
            bool result = false;

            if(m_VertexBuffer && m_IndexBuffer)
            {
                m_VertexBuffer->bind();
                m_IndexBuffer->bind();
                result = true;
            }

            return result;
        }

        void Mesh::unbind()
        {
            if(m_VertexBuffer)
            {
                m_VertexBuffer->unbind();
            }

            if(m_IndexBuffer)
            {
                m_IndexBuffer->unbind();
            }
        }

        void Mesh::unload()
        {
            if(m_VertexBuffer)
            {
                delete m_VertexBuffer;
                m_VertexBuffer = nullptr;
            }

            if(m_IndexBuffer)
            {
                delete m_IndexBuffer;
                m_IndexBuffer = nullptr;
            }
        }

        void Mesh::setVertexBuffer(VertexBuffer* buffer)
        {
            if(m_VertexBuffer)
            {
                delete m_VertexBuffer;
            }

            m_VertexBuffer = buffer;
        }

        VertexBuffer* Mesh::getVertexBuffer()
        {
            return m_VertexBuffer;
        }

        void Mesh::setIndexBuffer(IndexBuffer* buffer)
        {
            if(m_IndexBuffer)
            {
                delete m_IndexBuffer;
            }

            m_IndexBuffer = buffer;
        }

        IndexBuffer* Mesh::getIndexBuffer()
        {
            return m_IndexBuffer;
        }

        void Mesh::calculateMinMaxPoints()
        {
            m_MinPoint = Math::Vector3f();
            m_MaxPoint = Math::Vector3f();

            if(m_VertexBuffer)
            {
                auto vb = &m_VertexBuffer->getVertices();

                if(vb)
                {
                    if(vb->size())
                    {
                        m_MinPoint = vb->at(0).position;
                        m_MaxPoint = m_MinPoint;

                        for(auto iter = vb->begin(); iter != vb->end(); ++iter)
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
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}