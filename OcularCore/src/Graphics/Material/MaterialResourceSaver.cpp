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

#include "Graphics/Material/MaterialResourceSaver.hpp"
#include "Resources/ResourceSaverRegistrar.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>
#include <sstream>

OCULAR_REGISTER_RESOURCE_SAVER(Ocular::Graphics::MaterialResourceSaver)

//------------------------------------------------------------------------------------------

void ParseBuilderNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode);

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
                        Core::BuilderNode builderNode(nullptr, "", "", "");
                        material->onSave(&builderNode);

                        ParseBuilderNode(&builderNode, rootNode);

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

void ParseBuilderNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode)
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