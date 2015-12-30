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

#include "Graphics/Shader/Uniform/UniformBuffer.hpp"
#include "Graphics/Shader/Uniform/UniformsPerFrame.hpp"
#include "Graphics/Shader/Uniform/UniformPerCamera.hpp"
#include "Graphics/Shader/Uniform/UniformPerObject.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        UniformBuffer::UniformBuffer(UniformBufferType type)
            : m_IsDirty(true),
              m_UniformData(nullptr),
              m_UniformDataSize(0),
              m_Type(static_cast<uint32_t>(type))
        {
            m_Uniforms.reserve(100);
        }

        UniformBuffer::~UniformBuffer()
        {
            if(m_UniformData)
            {
                delete[] m_UniformData;
                m_UniformData = nullptr;
            }

            // m_FixedUniformData is not owned by this object
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

        void UniformBuffer::setFixedData(UniformPerFrame const& data)
        {
            m_Uniforms.clear();

            
        }

        void UniformBuffer::setFixedData(UniformPerCamera const& data)
        {
            Uniform viewMatrixUniform;
            Uniform projMatrixUniform;
            Uniform viewProjMatrixUniform;
            Uniform eyePosUniform;

            viewMatrixUniform.setData(data.viewMatrix);
            viewMatrixUniform.setName("ViewMatrix");
            viewMatrixUniform.setRegister(0);

            projMatrixUniform.setData(data.projMatrix);
            projMatrixUniform.setName("ProjMatrix");
            projMatrixUniform.setRegister(4);

            viewProjMatrixUniform.setData(data.viewProjMatrix);
            viewProjMatrixUniform.setName("ViewProjMatrix");
            viewProjMatrixUniform.setRegister(8);

            eyePosUniform.setData(data.eyePosition);
            eyePosUniform.setName("EyePosition");
            eyePosUniform.setRegister(12);

            setUniform(viewMatrixUniform);
            setUniform(projMatrixUniform);
            setUniform(viewProjMatrixUniform);
            setUniform(eyePosUniform);
        }

        void UniformBuffer::setFixedData(UniformPerObject const& data)
        {
            Uniform modelMatrixUniform;

            modelMatrixUniform.setData(data.modelMatrix);
            modelMatrixUniform.setName("ModelMatrix");
            modelMatrixUniform.setRegister(0);

            setUniform(modelMatrixUniform);
        }

        void UniformBuffer::setUniform(Uniform const& uniform)
        {
            const uint32_t index = uniform.getRegister();
            bool foundUniform = false;

            for(auto iter = m_Uniforms.begin(); iter != m_Uniforms.end(); ++iter)
            {
                if((*iter).getRegister() == index)
                {
                    (*iter) = uniform;
                    foundUniform = true;
                    m_IsDirty = true;

                    break;
                }
            }

            if(!foundUniform)
            {
                m_Uniforms.emplace_back(uniform);
            }
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

            return result;
        }

        Uniform const* UniformBuffer::getUniform(uint32_t const registerIndex) const
        {
            Uniform const* result = nullptr;

            if(registerIndex < m_Uniforms.size())
            {
                result = &m_Uniforms[registerIndex];
            }

            return result;
        }

        uint32_t UniformBuffer::getNumUniforms() const
        {
            return m_Uniforms.size();
        }

        uint32_t UniformBuffer::getUniformsSize() const
        {
            return m_UniformDataSize;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}