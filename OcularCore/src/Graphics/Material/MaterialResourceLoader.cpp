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

#include "Graphics/Material/MaterialResourceLoader.hpp"
#include "Graphics/Material/Material.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"

#include "Resources/ResourceLoaderRegistrar.hpp"
#include "Utilities/StringUtils.hpp"
#include "Math/Matrix3x3.hpp"
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::MaterialResourceLoader)

//------------------------------------------------------------------------------------------

void ParseMaterialTree(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode);
void ParseVarNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode);

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MaterialResourceLoader::MaterialResourceLoader()
            : Core::AResourceLoader(".omat", Core::ResourceType::Material)
        {
        
        }

        MaterialResourceLoader::~MaterialResourceLoader()
        {
            
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool MaterialResourceLoader::loadResource(Core::Resource* &resource, Core::File const& file, std::string const& mappingName)
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
                        Ocular::Core::BuilderNode builderNode(nullptr, "OcularMaterial", "", "");

                        //------------------------------------------------
                        // Parse generic variable nodes
                        //------------------------------------------------

                        for(auto child : rootNode.children())
                        {
                            if(Ocular::Utils::String::IsEqual(child.name(), "var"))
                            {
                                ParseVarNode(&builderNode, child);
                            }
                        }

                        //------------------------------------------------
                        // Parse Material specific nodes
                        //------------------------------------------------

                        ParseMaterialTree(&builderNode, rootNode);
                        
                        //------------------------------------------------
                        // Create and load the Material
                        //------------------------------------------------

                        Material* material = OcularGraphics->createMaterial();
                        material->setSourceFile(file);
                        material->onLoad(&builderNode);

                        resource = material;
                        result = true;
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
    }
}

//------------------------------------------------------------------------------------------
// OUT-OF-CLASS METHODS
//------------------------------------------------------------------------------------------

void ParseMaterialTree(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode)
{
    if(builderNode)
    {
        pugi::xml_node shadersXMLNode     = xmlNode.child(Ocular::Graphics::Material::ShaderNodeName.c_str());
        pugi::xml_node texturesXMLNode    = xmlNode.child(Ocular::Graphics::Material::TextureNodeName.c_str());
        pugi::xml_node uniformsXMLNode    = xmlNode.child(Ocular::Graphics::Material::UniformNodeName.c_str());
        pugi::xml_node renderStateXMLNode = xmlNode.child(Ocular::Graphics::Material::RenderStateNodeName.c_str());

        if(shadersXMLNode)
        {
            Ocular::Core::BuilderNode* shadersBuilderNode = builderNode->addChild(Ocular::Graphics::Material::ShaderNodeName, "", "");

            for(auto child : shadersXMLNode.children())
            {
                if(Ocular::Utils::String::IsEqual(child.name(), "var"))
                {
                    ParseVarNode(shadersBuilderNode, child);
                }
            }
        }

        if(texturesXMLNode)
        {
            Ocular::Core::BuilderNode* texturesBuilderNode = builderNode->addChild(Ocular::Graphics::Material::TextureNodeName, "", "");

            for(auto child : texturesXMLNode.children())
            {
                if(Ocular::Utils::String::IsEqual(child.name(), "var"))
                {
                    ParseVarNode(texturesBuilderNode, child);
                }
            }
        }

        if(uniformsXMLNode)
        {
            Ocular::Core::BuilderNode* uniformsBuilderNode = builderNode->addChild(Ocular::Graphics::Material::UniformNodeName, "", "");

            for(auto child : uniformsXMLNode.children())
            {
                if(Ocular::Utils::String::IsEqual(child.name(), "var"))
                {
                    ParseVarNode(uniformsBuilderNode, child);
                }
            }
        }

        if(renderStateXMLNode)
        {
            Ocular::Core::BuilderNode* renderStateBuilderNode = builderNode->addChild(Ocular::Graphics::Material::RenderStateNodeName, "", "");

            for(auto child : renderStateXMLNode.children())
            {
                if(Ocular::Utils::String::IsEqual(child.name(), "var"))
                {
                    ParseVarNode(renderStateBuilderNode, child);
                }
            }
        }
    }
}

void ParseVarNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode)
{
    if(builderNode && xmlNode)
    {
        const std::string name  = xmlNode.attribute("name").as_string();
        const std::string type  = xmlNode.attribute("type").as_string();
        const std::string value = xmlNode.attribute("value").as_string();

        builderNode->addChild(name, type, value);
    }
}