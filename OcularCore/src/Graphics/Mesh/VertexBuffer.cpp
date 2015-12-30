/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Graphics/Mesh/VertexBuffer.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        VertexBuffer::VertexBuffer()
        {

        }

        VertexBuffer::~VertexBuffer()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool VertexBuffer::build()
        {
            return false;
        }

        void VertexBuffer::bind()
        {

        }

        void VertexBuffer::unbind()
        {

        }

        void VertexBuffer::addVertex(Vertex const& vertex)
        {
            m_Vertices.push_back(vertex);
        }

        void VertexBuffer::addVertices(std::vector<Vertex> const& vertices)
        {
            m_Vertices.reserve(m_Vertices.size() + vertices.size());
            m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
        }

        void VertexBuffer::addVertices(std::vector<Vertex> const& vertices, uint32_t const count)
        {
            m_Vertices.reserve(m_Vertices.size() + count);
            m_Vertices.insert(m_Vertices.end(), vertices.begin(), (vertices.begin() + count));
        }

        void VertexBuffer::addVertices(Vertex const* vertices, uint32_t count)
        {
            m_Vertices.reserve(m_Vertices.size() + count);

            for(uint32_t i = 0; i < count; i++)
            {
                m_Vertices.emplace_back(vertices[i]);
            }
        }

        Vertex const* VertexBuffer::getVertex(uint32_t index) const
        {
            Vertex const* result = nullptr;

            if(index < m_Vertices.size())
            {
                result = &m_Vertices[index];
            }
            else
            {
                OcularLogger->warning("Requesting out-of-bounds index", OCULAR_INTERNAL_LOG("VertexBuffer", "getVertex"));
            }

            return result;
        }

        std::vector<Vertex> const& VertexBuffer::getVertices() const
        {
            return m_Vertices;
        }

        uint32_t VertexBuffer::getNumVertices() const
        {
            return m_Vertices.size();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}