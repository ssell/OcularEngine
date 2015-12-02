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

#include "Graphics/Material/MaterialResourceLoader.hpp"
#include "Graphics/Material/Material.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"

#include "Resources/ResourceLoaderRegistrar.hpp"
#include "Utilities/StringUtils.hpp"
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::MaterialResourceLoader)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        bool parseShaderProgram(Material* material, pugi::xml_node& root, Core::File const& source);
        void parseTextureList(Material* material, pugi::xml_node& root, Core::File const& source);
        void parseUniformList(Material* material, pugi::xml_node& root, Core::File const& source);

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MaterialResourceLoader::MaterialResourceLoader()
            : Core::AResourceLoader(".omat")
        {
        
        }

        MaterialResourceLoader::~MaterialResourceLoader()
        {
            
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool MaterialResourceLoader::loadResource(Core::Resource* &resource, Core::File const& file)
        {
            bool result = false;

            if(isFileValid(file))
            {
                pugi::xml_document document;
                pugi::xml_parse_result parseResult = document.load_file(file.getFullPath().c_str());

                if(parseResult)
                {
                    pugi::xml_node rootNode = document.child("OcularMaterial");

                    if(rootNode)
                    {
                        Material* material = new Material();
                        material->setSourceFile(file);

                        if(parseShaderProgram(material, rootNode, file))
                        {
                            parseTextureList(material, rootNode, file);
                            parseUniformList(material, rootNode, file);

                            resource = material;
                            result = true;
                        }
                        else
                        {
                            delete material;
                            material = nullptr;

                            OcularLogger->error("Failed to parse required Shader data in Material '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "loadResource"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Failed to find root node 'OcularMaterial' in Material '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "loadResource"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to parse Material file at '", file.getFullPath(), "' with error: ", parseResult.description(), OCULAR_INTERNAL_LOG("MaterialResourceLoader", "loadResource"));
                }
            }
            else
            {
                OcularLogger->error("Resource file at '", file.getFullPath(), "' is invalid", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "loadResource"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // OUT-OF-CLASS FUNCTIONS
        //----------------------------------------------------------------------------------

        bool parseShaderProgram(Material* material, pugi::xml_node& rootNode, Core::File const& source)
        {
            /**
             * <ShaderProgram>
             *     <Vertex>
             *         <Path>Shaders/Flat</Path>
             *     </Vertex>
             *     <Fragment>
             *         <Path>Shaders/Flat</Path>
             *     </Fragment>
             * </ShaderProgram>
             */

            // This method can only outright fail if the ShaderProgram, Vertex, or Fragment children are missing.
            // Everything else is optional and merits either no response or a warning.

            bool success = true;
            pugi::xml_node shaderNode = rootNode.child("ShaderProgram");

            if(shaderNode)
            {
                //----------------------------------------------------------------
                // Fetch the individual Shader nodes

                pugi::xml_node vertexNode   = shaderNode.child("Vertex");
                pugi::xml_node geometryNode = shaderNode.child("Geometry");
                pugi::xml_node fragmentNode = shaderNode.child("Fragment");
                pugi::xml_node preTessNode  = shaderNode.child("PreTessellation");
                pugi::xml_node postTessNode = shaderNode.child("PostTessellation");

                //----------------------------------------------------------------
                // Check for alternate names

                if(!fragmentNode)
                {
                    fragmentNode = shaderNode.child("Pixel");
                }

                if(!preTessNode)
                {
                    preTessNode = shaderNode.child("Hull");
                }

                if(!postTessNode)
                {
                    postTessNode = shaderNode.child("Domain");
                }

                //----------------------------------------------------------------
                // Fetch the data

                if(vertexNode)
                {
                    const std::string path = vertexNode.child_value("Path");
                    ShaderProgram* program = OcularResources->getResource<ShaderProgram>(path);

                    if(program)
                    {
                        material->setVertexShader(program->getVertexShader());
                    }
                    else
                    {
                        OcularLogger->error("Failed to retrieve ShaderProgram '", path, "' in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                        success = false;    // Vertex Shader is required
                    }
                }
                else
                {
                    OcularLogger->error("Material at '", source.getFullPath(), "' is missing required Vertex program", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    success = false;        // Vertex Shader is required
                }

                if(geometryNode)
                {
                    const std::string path = geometryNode.child_value("Path");
                    ShaderProgram* program = OcularResources->getResource<ShaderProgram>(path);

                    if(program)
                    {
                        material->setGeometryShader(program->getGeometryShader());
                    }
                    else
                    {
                        OcularLogger->warning("Failed to retrieve ShaderProgram '", path, "' in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    }
                }

                if(fragmentNode)
                {
                    const std::string path = fragmentNode.child_value("Path");
                    ShaderProgram* program = OcularResources->getResource<ShaderProgram>(path);

                    if(program)
                    {
                        material->setFragmentShader(program->getFragmentShader());
                    }
                    else
                    {
                        OcularLogger->error("Failed to retrieve ShaderProgram '", path, "' in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                        success = false;    // Fragment Shader is required
                    }
                }
                else
                {
                    OcularLogger->error("Material at '", source.getFullPath(), "' is missing required Fragment program", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    success = false;        // Fragment Shader is required
                }

                if(preTessNode)
                {
                    const std::string path = preTessNode.child_value("Path");
                    ShaderProgram* program = OcularResources->getResource<ShaderProgram>(path);

                    if(program)
                    {
                        material->setPreTessellationShader(program->getPreTessellationShader());
                    }
                    else
                    {
                        OcularLogger->warning("Failed to retrieve ShaderProgram '", path, "' in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    }
                }

                if(postTessNode)
                {
                    const std::string path = postTessNode.child_value("Path");
                    ShaderProgram* program = OcularResources->getResource<ShaderProgram>(path);

                    if(program)
                    {
                        material->setPostTessellationShader(program->getPostTessellationShader());
                    }
                    else
                    {
                        OcularLogger->warning("Failed to retrieve ShaderProgram '", path, "' in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    }
                }
            }
            else
            {
                OcularLogger->error("Failed to find required 'ShaderProgram' child in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                success = false;
            }

            return success;
        }

        void parseTextureList(Material* material, pugi::xml_node& rootNode, Core::File const& source)
        {
            /**
             * <Textures>
             *     <Texture>
             *         <Path>Textures/Grass</Path>
             *         <Name>GrassDiffuse</Name>
             *         <Register>0</Register>
             *     </Texture>
             *     <Texture>
             *         <Path>Textures/GrassBump</Path>
             *         <Name>GrassBumpMap</Name>
             *         <Register>1</Register>
             *     </Texture>
             * </Textures>
             */

            // Textures are not required, so at most only warnings are generated. 

            pugi::xml_node texturesNode = rootNode.child("Textures");

            if(texturesNode)
            {
                // Loop through all texture children
                for(pugi::xml_node textureNode = texturesNode.child("Texture"); textureNode; textureNode = textureNode.next_sibling("Texture"))
                {
                    bool result = true;

                    //--------------------------------------------------------------
                    // Ensure each required child node is present

                    if(!textureNode.child("Path"))
                    {
                        OcularLogger->warning("Uniform is missing required child node 'Path'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseTextureList"));
                        result = false;
                    }

                    if(!textureNode.child("Name"))
                    {
                        OcularLogger->warning("Uniform is missing required child node 'Path'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseTextureList"));
                        result = false;
                    }

                    if(!textureNode.child("Register"))
                    {
                        OcularLogger->warning("Uniform is missing required child node 'Path'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseTextureList"));
                        result = false;
                    }

                    if(result)
                    {
                        //--------------------------------------------------------------
                        // Get the value of each required child node

                        const std::string path  = textureNode.child_value("Path");
                        const std::string name  = textureNode.child_value("Name");
                        const std::string index = textureNode.child_value("Register");

                        //--------------------------------------------------------------
                        // Attempt to convert the index string value to an uint

                        uint32_t registerIndex = 0;

                        try
                        {
                            registerIndex = std::stoul(index);
                        }
                        catch(std::invalid_argument const& error)
                        {
                            OcularLogger->warning("Failed to convert Texture register value of '", index, "' to integer with error: ", error.what(), OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseTextureList"));
                            result = false;
                        }
                        catch(std::out_of_range const& error)
                        {
                            OcularLogger->warning("Failed to convert Texture register value of '", index, "' to integer with error: ", error.what(), OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseTextureList"));
                            result = false;
                        }

                        //--------------------------------------------------------------
                        // Attempt to fetch the Texture resource and set the material values

                        if(result)
                        {
                            Texture* texture = OcularResources->getResource<Texture>(path);

                            if(texture)
                            {
                                material->setTexture(registerIndex, name, texture);
                            }
                            else
                            {
                                OcularLogger->warning("Failed to retrieve Texture '", path, "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseTextureList"));
                                result = false;
                            }
                        }
                    }

                    //----------------------------------------------------
                    // Report any failure

                    if(!result)
                    {
                        OcularLogger->warning("Failed to parse Texture in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseTextureList"));
                    }
                }
            }
        }

        void parseUniformList(Material* material, pugi::xml_node& rootNode, Core::File const& source)
        {
            /**
             * <Uniforms>
             *     <Uniform>
             *         <Type>Vector4</Type>
             *         <Name>Offset</Name>
             *         <Register>0</Register>
             *         <Value>1.0 0.5 3.0 0.0</Value>
             *     </Uniform>
             *     <Uniform>
             *         <Type>Float</Type>
             *         <Name>Fade</Name>
             *         <Register>1</Register>
             *         <Value>0.5</Value>
             *     </Uniform>
             *     <Uniform>
             *         <Type>Matrix3x3</Type>
             *         <Name>Identity3x3</Name>
             *         <Register>2</Register>
             *         <Value>1.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 1.0</Value>
             *     </Uniform>
             *     <Uniform>
             *         <Type>Matrix3x3</Type>
             *         <Name>Rot3x3</Name>
             *         <Register>3</Register>
             *         <Value>
             *             0.38 1.0 0.0
             *             1.97 3.0 0.5
             *             0.01 0.9 1.0
             *         </Value>
             *     </Uniform>
             * </Uniforms>
             */

            // Uniforms are not required, so at most only warnings are generated.

            pugi::xml_node uniformsNode = rootNode.child("Uniforms");

            if(uniformsNode)
            {
                for(pugi::xml_node uniformNode = uniformsNode.child("Uniform"); uniformNode; uniformNode = uniformNode.next_sibling())
                {
                    bool result = true;

                    //--------------------------------------------------------------
                    // Ensure each required child node is present

                    if(!uniformNode.child("Type"))
                    {
                        OcularLogger->warning("Uniform is missing required child node 'Type'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                        result = false;
                    }

                    if(!uniformNode.child("Name"))
                    {
                        OcularLogger->warning("Uniform is missing required child node 'Name'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                        result = false;
                    }

                    if(!uniformNode.child("Register"))
                    {
                        OcularLogger->warning("Uniform is missing required child node 'Register'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                        result = false;
                    }

                    if(!uniformNode.child("Value"))
                    {
                        OcularLogger->warning("Uniform is missing required child node 'Value'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                        result = false;
                    }

                    if(result)
                    {
                        //--------------------------------------------------------------
                        // Get the value of each required child node

                        const std::string type  = uniformNode.child_value("Type");
                        const std::string name  = uniformNode.child_value("Name");
                        const std::string index = uniformNode.child_value("Register");
                        const std::string value = uniformNode.child_value("Value");

                        uint32_t registerIndex = 0;

                        //--------------------------------------------------------------
                        // Attempt to convert the index string value to an uint

                        try
                        {
                            registerIndex = std::stoul(index);
                        }
                        catch(std::invalid_argument const& error)
                        {
                            OcularLogger->warning("Failed to convert Uniform '", name, "' register value of '", index, "' to integer with error: ", error.what(), OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                            result = false;
                        }
                        catch(std::out_of_range const& error)
                        {
                            OcularLogger->warning("Failed to convert Uniform '", name, "' register value of '", index, "' to integer with error: ", error.what(), OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                            result = false;
                        }

                        //--------------------------------------------------------------
                        // Attempt to convert the uniform value string to the appropriate data structure

                        if(result)
                        {
                            if(Utils::StringUtils::isEqual(type, "Float", true))
                            {
                                float uniformValue = 0.0f;
                        
                                if(Utils::StringUtils::stringToFloat(value, uniformValue))
                                {
                                    material->setUniform(name, registerIndex, uniformValue);
                                }
                                else
                                {
                                    OcularLogger->warning("Failed to convert Uniform '", name, "' value of '", value, "' to Float", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                                    result = false;
                                }
                            }
                            else if(Utils::StringUtils::isEqual(type, "Vector4", true))
                            {
                                Math::Vector4f uniformValue;

                                if(Utils::StringUtils::stringToVector(value, uniformValue))
                                {
                                    material->setUniform(name, registerIndex, uniformValue);
                                }
                                else
                                {
                                    OcularLogger->warning("Failed to convert Uniform '", name, "' value of '", value, "' to Vector4", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                                    result = false;
                                }
                            }
                            else if(Utils::StringUtils::isEqual(type, "Matrix3x3", true))
                            {
                                Math::Matrix3x3f uniformValue;
                        
                                if(Utils::StringUtils::stringToMatrix(value, uniformValue))
                                {
                                    material->setUniform(name, registerIndex, uniformValue);
                                }
                                else
                                {
                                    OcularLogger->warning("Failed to convert Uniform '", name, "' value of '", value, "' to Matrix3x3", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                                    result = false;
                                }
                            }
                            else if(Utils::StringUtils::isEqual(type, "Matrix4x4", true))
                            {
                                Math::Matrix4x4f uniformValue;
                        
                                if(Utils::StringUtils::stringToMatrix(value, uniformValue))
                                {
                                    material->setUniform(name, registerIndex, uniformValue);
                                }
                                else
                                {
                                    OcularLogger->warning("Failed to convert Uniform '", name, "' value of '", value, "' to Matrix4x4", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                                    result = false;
                                }
                            }
                            else
                            {
                                OcularLogger->warning("Invalid Uniform '", name, "' Type of '", type, "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                                result = false;
                            }
                        }
                    }

                    //----------------------------------------------------
                    // Report any failure

                    if(!result)
                    {
                        OcularLogger->warning("Failed to parse Uniform in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseUniformList"));
                    }
                }
            }
        }
    }
}


