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

#include "Scene/SceneSaver/SceneObjectSaver.hpp"
#include "Scene/SceneSaver/SceneSaver.hpp"
#include "Scene/SceneLoader/SceneLoadInternal.hpp"

#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

//------------------------------------------------------------------------------------------

void ParseNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node* xmlNode);

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
        
        bool SceneObjectSaver::Save(SceneObject const* scene, File const& file)
        {
            bool result = false;
            return result;
        }

        bool SceneObjectSaver::Save(SceneObject* object, Node_Internal* node)
        {
            bool result = false;

            if(object)
            {
                BuilderNode builderNode(nullptr, "", "", "");
                object->onSave(&builderNode);

                ParseNode(&builderNode, node->node);

                result = true;
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

void ParseNode(Ocular::Core::BuilderNode* builderNode, pugi::xml_node* xmlNode)
{
    if(builderNode && xmlNode)
    {
        std::vector<Ocular::Core::BuilderNode*> children;
        builderNode->getAllChildren(children);

        for(auto child : children)
        {
            pugi::xml_node xmlChild = xmlNode->append_child("var");

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
                    ParseNode(child, &xmlChild);
                }
            }
        }
    }
}