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

#include "Graphics/Material/Material.hpp"
#include "Graphics/Texture/Texture.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"

#include "Math/Matrix3x3.hpp"

#include "OcularEngine.hpp"

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
              m_PostTessellationShader(nullptr),
              m_PrimitiveStyle(PrimitiveStyle::TriangleList),
              m_RenderPriority(static_cast<uint32_t>(Core::RenderPriority::Opaque))
        {
            m_Type = Core::ResourceType::Material;
            m_UniformBuffer = OcularGraphics->createUniformBuffer(UniformBufferType::PerMaterial);
            m_Textures.reserve(OcularGraphics->getMaxBoundTextures());

            RenderState* renderState = OcularGraphics->getRenderState();

            if(renderState)
            {
                m_StoredRasterState = renderState->getRasterState();
            }

            exposeProperties();
            setDefaults();
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
            bindStateChanges();
            bindShaders();
            //bindTextures

            m_UniformBuffer->bind();
        }

        void Material::unbind()
        {
            unbindStateChanges();
            unbindShaders();
        }

        void Material::unload()
        {
            // Intentionally left empty
        }

        void Material::onLoad(Core::BuilderNode const* node)
        {
            ObjectIO::onLoad(node);

            if(node)
            {
                //--------------------------------------------------------
                // Shaders
                //--------------------------------------------------------

                const Core::BuilderNode* shaderProgramNode = node->getChild("ShaderProgram");

                if(shaderProgramNode)
                {
                    const Core::BuilderNode* vertexNode = shaderProgramNode->getChild("Vertex");

                    if(vertexNode)
                    {
                        ShaderProgram* program = OcularResources->getResource<ShaderProgram>(vertexNode->getValue());

                        if(program)
                        {
                            m_VertexShader = program->getVertexShader();
                        }
                    }

                    const Core::BuilderNode* geometryNode = shaderProgramNode->getChild("Geometry");

                    if(geometryNode)
                    {
                        ShaderProgram* program = OcularResources->getResource<ShaderProgram>(geometryNode->getValue());

                        if(program)
                        {
                            m_GeometryShader = program->getGeometryShader();
                        }
                    }

                    const Core::BuilderNode* fragmentNode = shaderProgramNode->getChild("Fragment");

                    if(fragmentNode)
                    {
                        ShaderProgram* program = OcularResources->getResource<ShaderProgram>(fragmentNode->getValue());

                        if(program)
                        {
                            m_FragmentShader = program->getFragmentShader();
                        }
                    }

                    const Core::BuilderNode* preTessellationNode = shaderProgramNode->getChild("PreTessellation");

                    if(preTessellationNode)
                    {
                        ShaderProgram* program = OcularResources->getResource<ShaderProgram>(preTessellationNode->getValue());

                        if(program)
                        {
                            m_PreTessellationShader = program->getPreTessellationShader();
                        }
                    }

                    const Core::BuilderNode* postTessellationNode = shaderProgramNode->getChild("PostTessellation");

                    if(postTessellationNode)
                    {
                        ShaderProgram* program = OcularResources->getResource<ShaderProgram>(postTessellationNode->getValue());

                        if(program)
                        {
                            m_PostTessellationShader = program->getPostTessellationShader();
                        }
                    }
                }

                //--------------------------------------------------------
                // Textures
                //--------------------------------------------------------

                const Core::BuilderNode* texturesNode = node->getChild("Textures");

                if(texturesNode)
                {
                    std::vector<Core::BuilderNode*> textureNodes;
                    texturesNode->findChildrenByType(textureNodes, "Texture");

                    m_Textures.clear();
                    m_Textures.reserve(textureNodes.size());

                    for(auto textureNode : textureNodes)
                    {
                        // Call setTexture instead of adding directly to the m_Textures container so
                        // that any API-specific implementations (aka D3D11Material) may work properly.

                        setTexture(
                            static_cast<uint32_t>(m_Textures.size()), 
                            textureNode->getName(), 
                            OcularResources->getResource<Texture>(textureNode->getValue()));
                    }
                }

                //--------------------------------------------------------
                // Uniforms
                //--------------------------------------------------------

                const Core::BuilderNode* uniformsNode = node->getChild("Uniforms");

                if(uniformsNode)
                {
                    std::vector<Core::BuilderNode*> uniformNodes;
                    uniformsNode->findChildrenByName(uniformNodes, "Uniform");

                    uint32_t index = 0;

                    for(auto uniformNode : uniformNodes)
                    {
                        Uniform uniform;

                        if(Utils::String::IsEqual(uniformNode->getType(), Utils::TypeName<float>::name))
                        {
                            float data = OcularString->fromString<float>(uniformNode->getValue());
                            uniform.setData(data);
                        }
                        else if(Utils::String::IsEqual(uniformNode->getType(), Utils::TypeName<Math::Vector4f>::name))
                        {
                            Math::Vector4f data = OcularString->fromString<Math::Vector4f>(uniformNode->getValue());
                            uniform.setData(data);
                        }
                        else if(Utils::String::IsEqual(uniformNode->getType(), Utils::TypeName<Math::Matrix3x3>::name))
                        {
                            Math::Matrix3x3 data = OcularString->fromString<Math::Matrix3x3>(uniformNode->getValue());
                            uniform.setData(data);
                        }
                        else if(Utils::String::IsEqual(uniformNode->getType(), Utils::TypeName<Math::Matrix4x4>::name))
                        {
                            Math::Matrix4x4 data = OcularString->fromString<Math::Matrix4x4>(uniformNode->getValue());
                            uniform.setData(data);
                        }
                        else
                        {
                            continue;
                        }

                        uniform.setName(uniformNode->getName());
                        uniform.setRegister(index);

                        m_UniformBuffer->setUniform(uniform);

                        index++;
                    }
                }

            }
        }

        void Material::onSave(Core::BuilderNode* node) const
        {
            ObjectIO::onSave(node);

            if(node)
            {
                //--------------------------------------------------------
                // Shaders
                //--------------------------------------------------------

                Core::BuilderNode* shaderProgramNode = node->addChild("ShaderProgram", "", "");

                if(shaderProgramNode)
                {
                    if(m_VertexShader)
                    {
                        shaderProgramNode->addChild("Vertex", "Shader", m_VertexShader->getMappingName());
                    }
                    
                    if(m_GeometryShader)
                    {
                        shaderProgramNode->addChild("Geometry", "Shader", m_GeometryShader->getMappingName());
                    }
                    
                    if(m_FragmentShader)
                    {
                        shaderProgramNode->addChild("Fragment", "Shader", m_FragmentShader->getMappingName());
                    }
                    
                    if(m_PreTessellationShader)
                    {
                        shaderProgramNode->addChild("PreTessellation", "Shader", m_PreTessellationShader->getMappingName());
                    }
                    
                    if(m_PostTessellationShader)
                    {
                        shaderProgramNode->addChild("PostTessellation", "Shader", m_PostTessellationShader->getMappingName());
                    }
                }
                
                //--------------------------------------------------------
                // Textures
                //--------------------------------------------------------

                Core::BuilderNode* texturesNode = node->addChild("Textures", "", "");

                if(texturesNode)
                {
                    for(auto texture : m_Textures)
                    {
                        // Store in node as: 
                        // name:  sampler name
                        // type:  sampler register
                        // value: resource relative path

                        texturesNode->addChild(texture.samplerName, OcularString->toString<uint32_t>(texture.samplerRegister), texture.texture->getMappingName());
                    }
                }
                
                //--------------------------------------------------------
                // Uniforms
                //--------------------------------------------------------

                Core::BuilderNode* uniformsNode = node->addChild("Uniforms", "", "");

                if(uniformsNode)
                {
                    if(m_UniformBuffer)
                    {
                        for(uint32_t i = 0; i < m_UniformBuffer->getNumUniforms(); i++)
                        {
                            const Uniform* uniform = m_UniformBuffer->getUniform(i);
                            
                            if(uniform)
                            {
                                // Store in node as: 
                                // name:  uniform name
                                // type:  uniform size
                                // value: uniform value as string

                                switch(uniform->getSize())
                                {
                                case 1:
                                {
                                    float value = uniform->getData()[0];
                                    uniformsNode->addChild(uniform->getName(), Utils::TypeName<float>::name, OcularString->toString<float>(value));
                                    break;
                                }

                                case 4:
                                {
                                    Math::Vector4f value = Math::Vector4f(uniform->getData());
                                    uniformsNode->addChild(uniform->getName(), Utils::TypeName<Math::Vector4f>::name, OcularString->toString<Math::Vector4f>(value));
                                    break;
                                }

                                case 9:
                                {
                                    Math::Matrix3x3 value = Math::Matrix3x3(uniform->getData());
                                    uniformsNode->addChild(uniform->getName(), Utils::TypeName<Math::Matrix3x3>::name, OcularString->toString<Math::Matrix3x3>(value));
                                    break;
                                }

                                case 16:
                                {
                                    Math::Matrix4x4 value = Math::Matrix4x4(uniform->getData());
                                    uniformsNode->addChild(uniform->getName(), Utils::TypeName<Math::Matrix4x4>::name, OcularString->toString<Math::Matrix4x4>(value));
                                    break;
                                }

                                default:
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // Texture Methods
        //----------------------------------------------------------------------------------

        bool Material::setTexture(uint32_t const index, std::string const& name, Texture* texture)
        {
            bool result = false;

            if(index < OcularGraphics->getMaxBoundTextures())
            {
                bool registerInUse = false;

                for(auto iter = m_Textures.begin(); iter != m_Textures.end(); ++iter)
                {
                    if((*iter).samplerRegister == index)
                    {
                        (*iter).samplerName = name;
                        (*iter).texture = texture;

                        registerInUse = true;
                    }
                }

                if(!registerInUse)
                {
                    TextureSamplerInfo sampler;
                    sampler.texture = texture;
                    sampler.samplerName = name;
                    sampler.samplerRegister = index;

                    m_Textures.emplace_back(sampler);
                }

                result = true;
            }
            else
            {
                OcularLogger->warning("Specified Texture register index of ", index, " exceeds maximum register index of ", (OcularGraphics->getMaxBoundTextures() - 1), OCULAR_INTERNAL_LOG("Material", "setTexture"));
            }

            return result;
        }

        Texture* Material::getTexture(uint32_t const index) const
        {
            Texture* result = nullptr;

            if(index < OcularGraphics->getMaxBoundTextures())
            {
                for(auto iter = m_Textures.begin(); iter != m_Textures.end(); ++iter)
                {
                    if((*iter).samplerRegister == index)
                    {
                        result = (*iter).texture;
                    }
                }
            }
            else
            {
                OcularLogger->warning("Specified Texture register index of ", index, " exceeds maximum register index of ", (OcularGraphics->getMaxBoundTextures() - 1), OCULAR_INTERNAL_LOG("Material", "getTexture"));
            }

            return result;
        }

        void Material::removeTexture(uint32_t const index)
        {
            if(index < OcularGraphics->getMaxBoundTextures())
            {
                for(auto iter = m_Textures.begin(); iter != m_Textures.end(); ++iter)
                {
                    if((*iter).samplerRegister == index)
                    {
                        m_Textures.erase(iter);
                    }
                }
            }
            else
            {
                OcularLogger->warning("Specified Texture register index of ", index, " exceeds maximum register index of ", (OcularGraphics->getMaxBoundTextures() - 1), OCULAR_INTERNAL_LOG("Material", "removeTexture"));
            }
        }

        //----------------------------------------------------------------------------------
        // Shader Methods
        //----------------------------------------------------------------------------------

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

        //----------------------------------------------------------------------------------
        // Uniform Methods
        //----------------------------------------------------------------------------------

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
                    float const* data = uniform->getData();

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

        void Material::setUniform(std::string const& name, uint32_t registerIndex, Math::Matrix3x3 const& value)
        {
            Uniform uniform;
            uniform.setName(name);
            uniform.setRegister(registerIndex);
            uniform.setData(value);

            m_UniformBuffer->setUniform(uniform);
        }

        bool Material::getUniform(std::string const& name, Math::Matrix3x3& value)
        {
            bool result = false;
            Uniform const* uniform = m_UniformBuffer->getUniform(name);

            if(uniform)
            {
                if(uniform->getSize() == 12)
                {
                    float const* data = uniform->getData();

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

        void Material::setUniform(std::string const& name, uint32_t registerIndex, Math::Matrix4x4 const& value)
        {
            Uniform uniform;
            uniform.setName(name);
            uniform.setRegister(registerIndex);
            uniform.setData(value);

            m_UniformBuffer->setUniform(uniform);
        }

        bool Material::getUniform(std::string const& name, Math::Matrix4x4& value)
        {
            bool result = false;
            Uniform const* uniform = m_UniformBuffer->getUniform(name);

            if(uniform)
            {
                if(uniform->getSize() == 16)
                {
                    float const* data = uniform->getData();

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

        UniformBuffer const* Material::getUniformBuffer() const
        {
            return m_UniformBuffer;
        }

        //----------------------------------------------------------------------------------
        // Render State Changes
        //----------------------------------------------------------------------------------

        void Material::setPrimitiveStyle(PrimitiveStyle const style)
        {
            m_PrimitiveStyle = style;
        }

        PrimitiveStyle Material::getPrimitiveStyle() const
        {
            return m_PrimitiveStyle;
        }

        void Material::setRenderPriority(uint32_t const priority)
        {
            m_RenderPriority = priority;
        }

        uint32_t Material::getRenderPriority() const
        {
            return m_RenderPriority;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Material::exposeProperties()
        {
            OCULAR_EXPOSE(m_PrimitiveStyle);
            OCULAR_EXPOSE(m_RenderPriority);
        }

        void Material::setDefaults()
        {
            ShaderProgram* shaders = OcularResources->getResource<Graphics::ShaderProgram>("OcularCore/Shaders/Default");

            if(shaders)
            {
                m_VertexShader           = shaders->getVertexShader();
                m_GeometryShader         = shaders->getGeometryShader();
                m_FragmentShader         = shaders->getFragmentShader();
                m_PreTessellationShader  = shaders->getPreTessellationShader();
                m_PostTessellationShader = shaders->getPostTessellationShader();
            }
        }

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

        void Material::bindStateChanges()
        {
            RenderState* renderState = OcularGraphics->getRenderState();

            if(renderState)
            {
                RasterState currState = renderState->getRasterState();

                if(currState.primitiveStyle != m_PrimitiveStyle)
                {
                    m_StoredRasterState = currState;
                    currState.primitiveStyle = m_PrimitiveStyle;

                    renderState->setRasterState(currState);
                    renderState->bind();
                }
            }
        }

        void Material::unbindStateChanges()
        {
            RenderState* renderState = OcularGraphics->getRenderState();

            if(renderState)
            {
                if(m_StoredRasterState.primitiveStyle != m_PrimitiveStyle)
                {
                    renderState->setRasterState(m_StoredRasterState);
                    renderState->bind();
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}