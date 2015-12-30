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

#include "Graphics/Material/MaterialResourceSaver.hpp"
#include "Resources/ResourceSaverRegistrar.hpp"
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>
#include <sstream>

OCULAR_REGISTER_RESOURCE_SAVER(Ocular::Graphics::MaterialResourceSaver)

//------------------------------------------------------------------------------------------

bool addShaderData(pugi::xml_node& root, Ocular::Graphics::Material const* material);
bool addShaderNode(pugi::xml_node& parent, const char* name, Ocular::Graphics::Shader const* shader);

bool addTextureData(pugi::xml_node& root, Ocular::Graphics::Material const* material);
bool addTextureNode(pugi::xml_node& parent, uint32_t index, Ocular::Graphics::Material const* material);

bool addUniformData(pugi::xml_node& root, Ocular::Graphics::Material const* material);
bool addUniformNode(pugi::xml_node& parent, uint32_t index, Ocular::Graphics::UniformBuffer const* uniforms);

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MaterialResourceSaver::MaterialResourceSaver()
            : Core::AResourceSaver(".omat")
        {
        
        }

        MaterialResourceSaver::~MaterialResourceSaver()
        {
            
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool MaterialResourceSaver::saveResource(Core::Resource* resource, Core::File const& file)
        {
            bool result = false;

            if(validateResource(resource))
            {
                Material* material = dynamic_cast<Material*>(resource);

                if(material)
                {
                    pugi::xml_document document;
                    pugi::xml_node rootNode = document.append_child("OcularMaterial");

                    if(rootNode)
                    {
                        if(addShaderData(rootNode, material) && addTextureData(rootNode, material) && addUniformData(rootNode, material))
                        {
                            if(document.save_file(file.getFullPath().c_str()))
                            {
                                result = true;
                            }
                            else
                            {
                                OcularLogger->error("Failed to save document to file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "saveResource"));
                            }
                        }
                        else
                        {
                            OcularLogger->error("Failed to build document body", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "saveResource"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Failed to create root OcularMaterial node for document", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "saveResource"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to cast the Resource to Material", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "saveResource"));
                }
            }
            else
            {
                OcularLogger->error("Failed to validate Resource", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "saveResource"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool MaterialResourceSaver::validateResource(Core::Resource const* resource) const
        {
            bool result = true;

            if(resource)
            {
                if(resource->getResourceType() != Core::ResourceType::Material)
                {
                    result = false;
                    OcularLogger->error("Resource must be a Material", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "validateResource"));
                }
            }
            else
            {
                result = false;
                OcularLogger->error("Resource is NULL", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "validateResource"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

//------------------------------------------------------------------------------------------
// OUT-OF-CLASS METHODS
//------------------------------------------------------------------------------------------

bool addShaderData(pugi::xml_node& root, Ocular::Graphics::Material const* material)
{
    bool result = true;

    pugi::xml_node shaderProgramNode = root.append_child("ShaderProgram");

    if(shaderProgramNode)
    {
        if(!addShaderNode(shaderProgramNode, "VertexShader", material->getVertexShader()))
        {
            result = false;
            OcularLogger->error("Failed to add VertexShader node data", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderData"));
        }
        
        if(!addShaderNode(shaderProgramNode, "GeometryShader", material->getGeometryShader()))
        {
            result = false;
            OcularLogger->error("Failed to add GeometryShader node data", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderData"));
        }
        
        if(!addShaderNode(shaderProgramNode, "FragmentShader", material->getFragmentShader()))
        {
            result = false;
            OcularLogger->error("Failed to add FragmentShader node data", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderData"));
        }
        
        if(!addShaderNode(shaderProgramNode, "PreTessellation", material->getPreTessellationShader()))
        {
            result = false;
            OcularLogger->error("Failed to add PreTessellation node data", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderData"));
        }
        
        if(!addShaderNode(shaderProgramNode, "PostTessellation", material->getPostTessellationShader()))
        {
            result = false;
            OcularLogger->error("Failed to add PostTessellation node data", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderData"));
        }
    }
    else
    {
        result = false;
        OcularLogger->error("Failed to add 'ShaderProgram' node to root", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderData"));
    }

    return result;
}

bool addShaderNode(pugi::xml_node& parent, const char* name, Ocular::Graphics::Shader const* shader)
{
    bool result = false;

    pugi::xml_node shaderNode = parent.append_child(name);

    if(shaderNode)
    {
        pugi::xml_node pathNode = shaderNode.append_child("Path");

        if(pathNode)
        {
            pathNode.set_value(shader->getMappingName().c_str());
        }
        else
        {
            OcularLogger->error("Failed to add child 'Path' node", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderNode"));
        }
    }
    else
    {
        OcularLogger->error("Failed to add child '", name, "' node", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addShaderNode"));
    }

    return result;
}

bool addTextureData(pugi::xml_node& root, Ocular::Graphics::Material const* material)
{
    bool result = true;

    pugi::xml_node texturesNode = root.append_child("Textures");

    if(texturesNode)
    {
        const uint32_t maxTextures = OcularGraphics->getMaxBoundTextures();

        for(uint32_t i = 0; i < maxTextures; i++)
        {
            if(!addTextureNode(texturesNode, i, material))
            {
                result = false;
            }
        }
    }
    else
    {
        result = false;
        OcularLogger->error("Failed to add 'Textures' node to root", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addTextureData"));
    }

    return result;
}

bool addTextureNode(pugi::xml_node& parent, uint32_t index, Ocular::Graphics::Material const* material)
{
    bool result = true;
    Ocular::Graphics::Texture const* texture = material->getTexture(index);

    if(texture)
    {
        pugi::xml_node textureNode = parent.append_child("Texture");

        if(textureNode)
        {
            pugi::xml_node pathNode     = textureNode.append_child("Path");
            pugi::xml_node nameNode     = textureNode.append_child("Name");
            pugi::xml_node registerNode = textureNode.append_child("Register");

            if(pathNode && nameNode && registerNode)
            {
                pathNode.set_value(texture->getMappingName().c_str());
                nameNode.set_value(texture->getName().c_str());
                registerNode.set_value(std::to_string(index).c_str());
            }
            else
            {
                result = false;
                OcularLogger->error("Failed to add Texture data nodes", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addTextureNode"));
            }
        }
        else
        {
            result = false;
            OcularLogger->error("Failed to add child 'Texture' node", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addTextureNode"));
        }
    }
    //else
    //{
    //    Not an error as the addTextureData loop simply goes through all potential texture registers
    //}

    return result;
}

bool addUniformData(pugi::xml_node& root, Ocular::Graphics::Material const* material)
{
    bool result = true;

    pugi::xml_node uniformsNode = root.append_child("Uniforms");

    if(uniformsNode)
    {
        Ocular::Graphics::UniformBuffer const* uniforms = material->getUniformBuffer();

        if(uniforms)
        {
            const uint32_t numUniforms = uniforms->getNumUniforms();

            for(uint32_t i = 0; i < numUniforms; i++)
            {
                addUniformNode(uniformsNode, i, uniforms);
            }
        }
    }
    else
    {
        result = false;
        OcularLogger->error("Failed to add 'Uniforms' node to root", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addUniformData"));
    }

    return result;
}

bool addUniformNode(pugi::xml_node& parent, uint32_t index, Ocular::Graphics::UniformBuffer const* uniforms)
{
    bool result = true;
    Ocular::Graphics::Uniform const* uniform = uniforms->getUniform(index);

    if(uniform)
    {
        pugi::xml_node uniformNode = parent.append_child("Uniform");

        if(uniformNode)
        {
            pugi::xml_node typeNode     = uniformNode.append_child("Type");
            pugi::xml_node nameNode     = uniformNode.append_child("Name");
            pugi::xml_node registerNode = uniformNode.append_child("Register");
            pugi::xml_node valueNode    = uniformNode.append_child("Value");

            if(typeNode && nameNode && registerNode && valueNode)
            {
                //--------------------------------------------------------
                // Name and Register

                nameNode.set_value(uniform->getName().c_str());
                registerNode.set_value(std::to_string(index).c_str());

                //--------------------------------------------------------
                // Size

                switch(uniform->getSize())
                {
                case 1:
                    typeNode.set_value("Float");
                    break;

                case 4:
                    typeNode.set_value("Vector4");
                    break;

                case 12:
                    typeNode.set_value("Matrix3x3");
                    break;

                case 16:
                    typeNode.set_value("Matrix4x4");
                    break;

                default:
                    result = false;
                    OcularLogger->error("Invalid uniform data count of ", uniform->getSize(), "; Expected 1, 4, 12, or 16", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addUniformNode"));
                    break;
                }

                //--------------------------------------------------------
                // Value

                std::stringstream sstream;
                float const* values = uniform->getData();

                for(uint32_t i = 0; i < uniform->getSize(); i++)
                {
                    sstream << values[i] << " ";
                }

                valueNode.set_value(sstream.str().c_str());
            }
            else
            {
                result = false;
                OcularLogger->error("Failed to add Uniform data nodes", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addUniformNode"));
            }
        }
        else
        {
            result = false;
            OcularLogger->error("Failed to add child 'Uniform' node", OCULAR_INTERNAL_LOG("MaterialResourceSaver", "addUniformNode"));
        }
    }
    //else
    //{
    //    Not an error as the addUniformData loop simply goes through all potential uniform registers
    //}

    return result;
}