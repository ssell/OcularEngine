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

#include "Graphics/Shader/UniformBuffer.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        UniformBuffer::UniformBuffer(UniformBufferType const type)
            : m_IsDirty(true),
              m_UniformData(nullptr),
              m_UniformDataSize(0),
              m_Type(static_cast<uint32_t>(type))
        {
        
        }

        UniformBuffer::~UniformBuffer()
        {
            if(m_UniformData)
            {
                delete[] m_UniformData;
                m_UniformData = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void UniformBuffer::bind()
        {
            // Intentionally left empty
        }

        void UniformBuffer::unbind()
        {
            // Intentionally left empty
        }

        void UniformBuffer::setUniform(Uniform const& uniform)
        {
            const uint32_t index = uniform.getRegister();

            if(index < m_Uniforms.size())
            {
                m_Uniforms.resize(index);
            }

            m_Uniforms[index] = uniform;
        }

        Uniform const* UniformBuffer::getUniform(std::string const& name) const
        {
            Uniform const* result = nullptr;

            for(uint32_t i = 0; i < m_Uniforms.size(); i++)
            {
                if(m_Uniforms[i].getName().compare(name) == 0)
                {
                    result = &m_Uniforms[i];
                    break;
                }
            }

            if(result == nullptr)
            {
                OcularLogger->error("No uniform with matching name of '", name, "'", OCULAR_INTERNAL_LOG("UniformBuffer", "getUniform"));
            }

            return result;
        }

        Uniform const* UniformBuffer::getUniform(uint32_t const registerIndex) const
        {
            Uniform const* result = nullptr;

            if(registerIndex < m_Uniforms.size())
            {
                result = &m_Uniforms[registerIndex];
            }
            else
            {
                OcularLogger->error("No uniform with matching register index of ", registerIndex, OCULAR_INTERNAL_LOG("UniformBuffer", "getUniform"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}