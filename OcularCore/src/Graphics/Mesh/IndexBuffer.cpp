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

#include "Graphics/Mesh/IndexBuffer.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        IndexBuffer::IndexBuffer()
        {

        }

        IndexBuffer::~IndexBuffer()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool IndexBuffer::build()
        {
            return false;
        }

        void IndexBuffer::bind()
        {

        }

        void IndexBuffer::unbind()
        {

        }

        void IndexBuffer::addIndex(uint32_t const index)
        {
            m_Indices.push_back(index);
        }

        void IndexBuffer::addIndices(std::vector<uint32_t> const& indices)
        {
            m_Indices.reserve(m_Indices.size() + indices.size());
            m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
        }

        void IndexBuffer::addIndices(std::vector<uint32_t> const& indices, uint32_t const count)
        {
            m_Indices.reserve(m_Indices.size() + count);
            m_Indices.insert(m_Indices.end(), indices.begin(), (indices.begin() + count));
        }

        void IndexBuffer::addIndices(uint32_t const* indices, uint32_t count)
        {
            m_Indices.reserve(m_Indices.size() + count);

            for(uint32_t i = 0; i < count; i++)
            {
                m_Indices.emplace_back(indices[i]);
            }
        }

        uint32_t IndexBuffer::getIndex(uint32_t const index)
        {
            uint32_t result = 0;

            if(index < m_Indices.size())
            {
                result = m_Indices[index];
            }
            else
            {
                OcularLogger->warning("Requesting out-of-bounds index", OCULAR_INTERNAL_LOG("IndexBuffer", "getIndex"));
            }

            return result;
        }

        std::vector<uint32_t> const& IndexBuffer::getIndices() const
        {
            return m_Indices;
        }

        uint32_t IndexBuffer::getNumIndices() const
        {
            return m_Indices.size();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}