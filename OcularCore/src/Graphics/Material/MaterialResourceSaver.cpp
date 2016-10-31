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

//------------------------------------------------------------------------------------------

#include "Graphics/Material/MaterialResourceSaver.hpp"
#include "Resources/ResourceSaverRegistrar.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>
#include <sstream>

OCULAR_REGISTER_RESOURCE_SAVER(Ocular::Graphics::MaterialResourceSaver)

//------------------------------------------------------------------------------------------
// This source file keeps getting LNK4221 reporting that the constructor is not defined for whatever reason. This is needed to avoid this error.
// Source: http://stackoverflow.com/a/25422179/735425
// May need to move this segment around so it is triggered as a modified file...
// Yea, I know...

__declspec(dllexport) void getRidOfLNK4221(){}  

//------------------------------------------------------------------------------------------

void ParseBuilderNode(Ocular::Core::BuilderNode const* builderNode, pugi::xml_node& xmlNode);

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MaterialResourceSaver::MaterialResourceSaver()
            : Core::AResourceSaver(".omat", Core::ResourceType::Material)
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
                        Core::BuilderNode builderNode(nullptr, "", "", "");
                        material->onSave(&builderNode);

                        auto shaderNode  = builderNode.getChild(Material::ShaderNodeName);
                        auto textureNode = builderNode.getChild(Material::TextureNodeName);
                        auto uniformNode = builderNode.getChild(Material::UniformsNodeName);
                        auto renderNode  = builderNode.getChild(Material::RenderStateNodeName);

                        if(shaderNode && shaderNode->getNumChildren())
                        {
                            auto shaderXMLNode = rootNode.append_child(Material::ShaderNodeName.c_str());
                            ParseBuilderNode(shaderNode, shaderXMLNode);
                        }

                        if(textureNode && textureNode->getNumChildren())
                        {
                            auto textureXMLNode = rootNode.append_child(Material::TextureNodeName.c_str());
                            ParseBuilderNode(textureNode, textureXMLNode);
                        }

                        if(uniformNode && uniformNode->getNumChildren())
                        {
                            auto uniformXMLNode = rootNode.append_child(Material::UniformsNodeName.c_str());
                            ParseBuilderNode(uniformNode, uniformXMLNode);
                        }

                        if(renderNode && renderNode->getNumChildren())
                        {
                            auto renderXMLNode = rootNode.append_child(Material::RenderStateNodeName.c_str());
                            ParseBuilderNode(renderNode, renderXMLNode);
                        }

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

void ParseBuilderNode(Ocular::Core::BuilderNode const* builderNode, pugi::xml_node& xmlNode)
{
    if(builderNode && xmlNode)
    {
        std::vector<Ocular::Core::BuilderNode*> children;
        builderNode->getAllChildren(children);

        for(auto child : children)
        {
            pugi::xml_node xmlChild = xmlNode.append_child("var");

            if(xmlChild)
            {
                pugi::xml_attribute nameAttribute  = xmlChild.append_attribute("name");
                pugi::xml_attribute typeAttribute  = xmlChild.append_attribute("type");
                pugi::xml_attribute valueAttribute = xmlChild.append_attribute("value");

                nameAttribute.set_value(child->getName().c_str());
                typeAttribute.set_value(child->getType().c_str());
                valueAttribute.set_value(child->getValue().c_str());

                if(child->getNumChildren())
                {
                    ParseBuilderNode(child, xmlChild);
                }
            }
        }
    }
}