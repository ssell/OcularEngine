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
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::MaterialResourceLoader)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        void parseShaderProgram(Material* material, pugi::xml_document& document, Core::File const& source);
        void parseTextureList(Material* material, pugi::xml_document& document, Core::File const& source);
        void parseUniformList(Material* material, pugi::xml_document& document, Core::File const& source);

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

                if(result)
                {
                    Material* material = new Material();
                    material->setSourceFile(file);

                    parseShaderProgram(material, document, file);
                    parseTextureList(material, document, file);
                    parseUniformList(material, document, file);

                    resource = material;
                    result = true;
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

        void parseShaderProgram(Material* material, pugi::xml_document& document, Core::File const& source)
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

            pugi::xml_node shaderNode = document.child("ShaderProgram");

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
                        OcularLogger->warning("Failed to retrieve ShaderProgram '", path, "' in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    }
                }
                else
                {
                    OcularLogger->warning("Material at '", source.getFullPath(), "' is missing required Vertex program", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
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
                        OcularLogger->warning("Failed to retrieve ShaderProgram '", path, "' in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    }
                }
                else
                {
                    OcularLogger->warning("Material at '", source.getFullPath(), "' is missing required Fragment program", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
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
        }

        void parseTextureList(Material* material, pugi::xml_document& document, Core::File const& source)
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

            pugi::xml_node texturesNode = document.child("Textures");

            if(texturesNode)
            {
                // Loop through all texture children
                for(pugi::xml_node textureNode = texturesNode.child("Texture"); textureNode; textureNode = textureNode.next_sibling("Texture"))
                {
                    bool result = true;

                    const std::string path  = textureNode.child_value("Path");
                    const std::string name  = textureNode.child_value("Name");
                    const std::string index = textureNode.child_value("Register");

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

                    if(result)
                    {
                        Texture* texture = OcularResources->getResource<Texture>(path);

                        if(texture)
                        {
                            material->setTexture(registerIndex, name, texture);
                        }
                        else
                        {
                            OcularLogger->warning("Failed to retrieve Texture '", path, "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                            result = false;
                        }
                    }

                    if(!result)
                    {
                        OcularLogger->warning("Failed to parse Texture in Material '", source.getFullPath(), "'", OCULAR_INTERNAL_LOG("MaterialResourceLoader", "parseShaderProgram"));
                    }
                }
            }
        }

        void parseUniformList(Material* material, pugi::xml_document& document, Core::File const& source)
        {
            /**
             * <Uniforms>
             *     <Uniform>
             *         <Type>Vector4</Type>
             *         <Name>Offset</Name>
             *         <Value>1.0 0.5 3.0 0.0</Value>
             *     </Uniform>
             *     <Uniform>
             *         <Type>Float</Type>
             *         <Name>Fade</Name>
             *         <Value>0.5</Value>
             *     </Uniform>
             *     <Uniform>
             *         <Type>Matrix3x3</Type>
             *         <Name>Identity3x3</Name>
             *         <Value>1.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 1.0</Value>
             *     </Uniform>
             *     <Uniform>
             *         <Type>Matrix3x3</Type>
             *         <Name>Rot3x3</Name>
             *         <Value>
             *             0.38 1.0 0.0
             *             1.97 3.0 0.5
             *             0.01 0.9 1.0
             *         </Value>
             *     </Uniform>
             * </Uniforms>
             */
        }
    }
}


