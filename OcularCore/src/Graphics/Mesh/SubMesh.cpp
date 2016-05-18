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

#include "Graphics/Mesh/SubMesh.hpp"
#include "Graphics/Mesh/VertexBuffer.hpp"
#include "Graphics/Mesh/IndexBuffer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SubMesh::SubMesh()
            : m_VertexBuffer(nullptr),
              m_IndexBuffer(nullptr)
        {

        }

        SubMesh::~SubMesh()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool SubMesh::bind()
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

        void SubMesh::unbind()
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

        void SubMesh::unload()
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

        void SubMesh::setVertexBuffer(VertexBuffer* buffer)
        {
            if(m_VertexBuffer)
            {
                delete m_VertexBuffer;
            }

            m_VertexBuffer = buffer;
        }

        VertexBuffer* SubMesh::getVertexBuffer()
        {
            return m_VertexBuffer;
        }

        void SubMesh::setIndexBuffer(IndexBuffer* buffer)
        {
            if(m_IndexBuffer)
            {
                delete m_IndexBuffer;
            }

            m_IndexBuffer = buffer;
        }

        IndexBuffer* SubMesh::getIndexBuffer()
        {
            return m_IndexBuffer;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}