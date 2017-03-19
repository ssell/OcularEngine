/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Scene/SceneLoader/SceneObjectLoader.hpp"
#include "Scene/SceneLoader/SceneLoader.hpp"
#include "Scene/SceneLoader/SceneLoadInternal.hpp"
#include "Scene/ARenderable.hpp"
#include "Scene/ARoutine.hpp"
#include "Utilities/StringUtils.hpp"
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

void ParseNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        SceneObject* SceneObjectLoader::Load(File const& file)
        {
            SceneObject* result = nullptr;

            if(IsValidFile(file))
            {
                pugi::xml_document document;
                pugi::xml_parse_result parseResult = document.load_file(file.getFullPath().c_str());

                if(parseResult)
                {
                    pugi::xml_node root = document.child("SceneObject");

                    if(root)
                    {
                        Node_Internal node;
                        node.node = &root;

                        result = Load(&node);
                    }
                    else
                    {
                        OcularLogger->error("Failed to locate root node <SceneObject>", OCULAR_INTERNAL_LOG("SceneObjectLoader", "Load"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to parse XML document", OCULAR_INTERNAL_LOG("SceneObjectLoader", "Load"));
                }
            }
            else
            {
                OcularLogger->error("Failed to validate file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("SceneObjectLoader", "Load"));
            }

            return result;
        }

        SceneObject* SceneObjectLoader::Load(Node_Internal* node)
        {
            SceneObject* result = nullptr;

            if(node)
            {
                pugi::xml_node* root = node->node;

                if(root)
                {
                    BuilderNode builderNode(nullptr, "", "", "");

                    for(auto child : root->children())
                    {
                        if(Utils::String::IsEqual(child.name(), "var"))
                        {
                            ParseNode(&builderNode, child);
                        }
                    }

                    result = new SceneObject();
                    result->onLoad(&builderNode);
                }
            } 
            else
            {
                OcularLogger->error("Provided node is NULL", OCULAR_INTERNAL_LOG("SceneObjectLoader", "Load"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool SceneObjectLoader::IsValidFile(File const& file)
        {
            bool result = true;

            if(!file.exists())
            {
                OcularLogger->error("File does not exist", OCULAR_INTERNAL_LOG("SceneObjectLoader", "IsValidFile"));
                result = false;
            }

            if(!file.canRead())
            {
                OcularLogger->error("File can not be read", OCULAR_INTERNAL_LOG("SceneObjectLoader", "IsValidFile"));
                result = false;
            }

            if(!Utils::String::IsEqual(file.getExtension(), ".opre"))
            {
                OcularLogger->error("File is invalid type. Expecting '.opre'", OCULAR_INTERNAL_LOG("SceneObjectLoader", "IsValidFile"));
                result = false;
            }

            return result;
        }
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

void ParseNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node& xmlNode)
{
    const std::string name  = xmlNode.attribute("name").as_string();
    const std::string type  = xmlNode.attribute("type").as_string();
    const std::string value = xmlNode.attribute("value").as_string();

    if(name.size())
    {
        // May have no type or value which is OK
        Ocular::Core::BuilderNode* newNode = builderNode->addChild(name, type, value);

        for(auto child : xmlNode.children())
        {
            ParseNode(newNode, child);
        }
    }
    else
    {
        OcularLogger->warning("Failed to parse name attribute from node", OCULAR_INTERNAL_LOG("SceneObjectLoader", "ParseNode"));
    }
}