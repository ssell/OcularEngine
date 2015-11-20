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

#include "Graphics/Material/Material.hpp"

#include "OcularEngine.hpp"
#include "Graphics/Texture/Texture.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Material::Material()
            : Core::Resource(),
              m_VertexShader(nullptr),
              m_GeometryShader(nullptr),
              m_FragmentShader(nullptr),
              m_PreTessellationShader(nullptr),
              m_PostTessellationShader(nullptr)
        {
            m_UniformBuffer = OcularGraphics->createUniformBuffer(UniformBufferType::PerMaterial);

            m_Textures.reserve(OcularGraphics->getMaxBoundTextures());
            std::fill(m_Textures.begin(), m_Textures.end(), std::make_pair("", nullptr));
        }

        Material::~Material()
        {
            unbind();

            if(m_UniformBuffer)
            {
                delete m_UniformBuffer;
                m_UniformBuffer = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Material::bind()
        {
            bindShaders();
        }

        void Material::unbind()
        {
            unbindShaders();
        }

        void Material::unload()
        {
            // Intentionally left empty
        }

        //--------------------------------------------
        // Texture Methods
        //--------------------------------------------

        bool Material::setTexture(uint32_t const index, std::string const& name, Texture* texture)
        {
            bool result = false;

            if(index < m_Textures.size())
            {
                m_Textures[index].first = name;
                m_Textures[index].second = texture;
                result = true;
            }

            return result;
        }

        Texture* Material::getTexture(uint32_t const index) const
        {
            return m_Textures[index].second;
        }

        void Material::removeTexture(uint32_t const index)
        {
            if(index < m_Textures.size())
            {
                if(m_Textures[index].second)
                {
                    m_Textures[index].second = nullptr;
                }
            }
        }

        //--------------------------------------------
        // Shader Methods
        //--------------------------------------------

        bool Material::setVertexShader(std::string const& name)
        {
            bool result = false;
            ShaderProgram* program = OcularResources->getResource<ShaderProgram>(name);

            if(program)
            {
                m_VertexShader = program->getVertexShader();

                if(m_VertexShader)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->warning("Found matching ShaderProgram '", name, "' but it did not contain a vertex shader", OCULAR_INTERNAL_LOG("Material", "setVertexShader"));
                }
            }
            else
            {
                OcularLogger->warning("No ShaderProgram was found with the name '", name, "'", OCULAR_INTERNAL_LOG("Material", "setVertexShader"));
            }

            return result;
        }

        void Material::setVertexShader(VertexShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_VertexShader = shader;
        }

        bool Material::setGeometryShader(std::string const& name)
        {
            bool result = false;
            ShaderProgram* program = OcularResources->getResource<ShaderProgram>(name);

            if(program)
            {
                m_GeometryShader = program->getGeometryShader();

                if(m_GeometryShader)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->warning("Found matching ShaderProgram '", name, "' but it did not contain a geometry shader", OCULAR_INTERNAL_LOG("Material", "setGeometryShader"));
                }
            }
            else
            {
                OcularLogger->warning("No ShaderProgram was found with the name '", name, "'", OCULAR_INTERNAL_LOG("Material", "setGeometryShader"));
            }

            return result;
        }

        void Material::setGeometryShader(GeometryShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_GeometryShader = shader;
        }

        bool Material::setFragmentShader(std::string const& name)
        {
            bool result = false;
            ShaderProgram* program = OcularResources->getResource<ShaderProgram>(name);

            if(program)
            {
                m_FragmentShader = program->getFragmentShader();

                if(m_FragmentShader)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->warning("Found matching ShaderProgram '", name, "' but it did not contain a fragment shader", OCULAR_INTERNAL_LOG("Material", "setFragmentShader"));
                }
            }
            else
            {
                OcularLogger->warning("No ShaderProgram was found with the name '", name, "'", OCULAR_INTERNAL_LOG("Material", "setFragmentShader"));
            }

            return result;
        }

        void Material::setFragmentShader(FragmentShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_FragmentShader = shader;
        }

        bool Material::setPreTessellationShader(std::string const& name)
        {
            bool result = false;
            ShaderProgram* program = OcularResources->getResource<ShaderProgram>(name);

            if(program)
            {
                m_PreTessellationShader = program->getPreTessellationShader();

                if(m_PreTessellationShader)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->warning("Found matching ShaderProgram '", name, "' but it did not contain a pre-tessellation shader", OCULAR_INTERNAL_LOG("Material", "setPreTessellationShader"));
                }
            }
            else
            {
                OcularLogger->warning("No ShaderProgram was found with the name '", name, "'", OCULAR_INTERNAL_LOG("Material", "setPreTessellationShader"));
            }

            return result;
        }

        void Material::setPreTessellationShader(PreTessellationShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_PreTessellationShader = shader;
        }

        bool Material::setPostTessellationShader(std::string const& name)
        {
            bool result = false;
            ShaderProgram* program = OcularResources->getResource<ShaderProgram>(name);

            if(program)
            {
                m_PostTessellationShader = program->getPostTessellationShader();

                if(m_PostTessellationShader)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->warning("Found matching ShaderProgram '", name, "' but it did not contain a post-tessellation shader", OCULAR_INTERNAL_LOG("Material", "setPostTessellationShader"));
                }
            }
            else
            {
                OcularLogger->warning("No ShaderProgram was found with the name '", name, "'", OCULAR_INTERNAL_LOG("Material", "setPostTessellationShader"));
            }

            return result;
        }

        void Material::setPostTessellationShader(PostTessellationShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_PostTessellationShader = shader;
        }

        VertexShader* Material::getVertexShader() const
        {
            return m_VertexShader;
        }

        GeometryShader* Material::getGeometryShader() const
        {
            return m_GeometryShader;
        }

        FragmentShader* Material::getFragmentShader() const
        {
            return m_FragmentShader;
        }

        PreTessellationShader* Material::getPreTessellationShader() const
        {
            return m_PreTessellationShader;
        }

        PostTessellationShader* Material::getPostTessellationShader() const
        {
            return m_PostTessellationShader;
        }

        //------------------------------------------------------------
        // Uniform Methods
        //------------------------------------------------------------

        void Material::setUniform(std::string const& name, uint32_t registerIndex, float const value)
        {
            Uniform uniform;
            uniform.setName(name);
            uniform.setRegister(registerIndex);
            uniform.setData(value);

            m_UniformBuffer->setUniform(uniform);
        }

        bool Material::getUniform(std::string const& name, float& value)
        {
            bool result = false;
            Uniform const* uniform = m_UniformBuffer->getUniform(name);

            if(uniform)
            {
                if(uniform->getSize() == 1)
                {
                    value = uniform->getElement(0);
                    result = true;
                }
                else
                {
                    OcularLogger->error("Improper uniform request (requesting single float for non-single float uniform)", OCULAR_INTERNAL_LOG("Material", "getUniform"));
                }
            }

            return result;
        }

        void Material::setUniform(std::string const& name, uint32_t registerIndex, Math::Vector4f const& value)
        {
            Uniform uniform;
            uniform.setName(name);
            uniform.setRegister(registerIndex);
            uniform.setData(value);

            m_UniformBuffer->setUniform(uniform);
        }

        bool Material::getUniform(std::string const& name, Math::Vector4f& value)
        {
            bool result = false;
            Uniform const* uniform = m_UniformBuffer->getUniform(name);

            if(uniform)
            {
                if(uniform->getSize() == 4)
                {
                    float* data = uniform->getData();

                    if(data)
                    {
                        value.x = data[0];
                        value.y = data[1];
                        value.z = data[2];
                        value.w = data[3];

                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Uniform data is NULL", OCULAR_INTERNAL_LOG("Material", "getUniform"));
                    }
                }
                else
                {
                    OcularLogger->error("Improper uniform request (requesting vector for non-vector uniform)", OCULAR_INTERNAL_LOG("Material", "getUniform"));
                }
            }

            return result;
        }

        void Material::setUniform(std::string const& name, uint32_t registerIndex, Math::Matrix3x3f const& value)
        {
            Uniform uniform;
            uniform.setName(name);
            uniform.setRegister(registerIndex);
            uniform.setData(value);

            m_UniformBuffer->setUniform(uniform);
        }

        bool Material::getUniform(std::string const& name, Math::Matrix3x3f& value)
        {
            bool result = false;
            Uniform const* uniform = m_UniformBuffer->getUniform(name);

            if(uniform)
            {
                if(uniform->getSize() == 12)
                {
                    float* data = uniform->getData();

                    if(data)
                    {
                        value.setData(uniform->getData());
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Uniform data is NULL", OCULAR_INTERNAL_LOG("Material", "getUniform"));
                    }
                }
                else
                {
                    OcularLogger->error("Improper uniform request (requesting 3x3 matrix for non-3x3 matrix uniform)", OCULAR_INTERNAL_LOG("Material", "getUniform"));
                }
            }

            return result;
        }

        void Material::setUniform(std::string const& name, uint32_t registerIndex, Math::Matrix4x4f const& value)
        {
            Uniform uniform;
            uniform.setName(name);
            uniform.setRegister(registerIndex);
            uniform.setData(value);

            m_UniformBuffer->setUniform(uniform);
        }

        bool Material::getUniform(std::string const& name, Math::Matrix4x4f& value)
        {
            bool result = false;
            Uniform const* uniform = m_UniformBuffer->getUniform(name);

            if(uniform)
            {
                if(uniform->getSize() == 16)
                {
                    float* data = uniform->getData();

                    if(data)
                    {
                        value.setData(uniform->getData());
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Uniform data is NULL", OCULAR_INTERNAL_LOG("Material", "getUniform"));
                    }
                }
                else
                {
                    OcularLogger->error("Improper uniform request (requesting 3x3 matrix for non-4x4 matrix uniform)", OCULAR_INTERNAL_LOG("Material", "getUniform"));
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Material::bindShaders()
        {
            if(m_VertexShader)
            {
                m_VertexShader->bind();
            }

            if(m_GeometryShader)
            {
                m_GeometryShader->bind();
            }

            if(m_FragmentShader)
            {
                m_FragmentShader->bind();
            }

            if(m_PreTessellationShader)
            {
                m_PreTessellationShader->bind();
            }

            if(m_PostTessellationShader)
            {
                m_PostTessellationShader->bind();
            }
        }

        void Material::unbindShaders()
        {
            if(m_VertexShader)
            {
                m_VertexShader->unbind();
            }

            if(m_GeometryShader)
            {
                m_GeometryShader->unbind();
            }

            if(m_FragmentShader)
            {
                m_FragmentShader->unbind();
            }

            if(m_PreTessellationShader)
            {
                m_PreTessellationShader->unbind();
            }

            if(m_PostTessellationShader)
            {
                m_PostTessellationShader->unbind();
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}