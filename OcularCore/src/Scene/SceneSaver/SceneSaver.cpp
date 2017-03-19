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

#include "Scene/SceneSaver/SceneSaver.hpp"
#include "Scene/SceneSaver/SceneObjectSaver.hpp"
#include "Scene/SceneLoader/SceneLoadInternal.hpp"

#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

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
        
        bool SceneSaver::Save(Scene const* scene, File const& file)
        {
            bool result = false;

            if(scene)
            {
                if(IsValidFile(file))
                {
                    pugi::xml_document document;
                    pugi::xml_node root = document.append_child("OcularScene");

                    if(root)
                    {
                        //------------------------------------------------
                        // Header
                        //------------------------------------------------

                        pugi::xml_node headerRoot   = root.append_child("SceneHeader");

                        // SceneTree Type

                        pugi::xml_node sceneTreeTypeRoot    = headerRoot.append_child("SceneTreeType");
                        pugi::xml_node staticSceneTreeNode  = sceneTreeTypeRoot.append_child("Static");
                        pugi::xml_node dynamicSceneTreeNode = sceneTreeTypeRoot.append_child("Dynamic");

                        staticSceneTreeNode.append_child(pugi::xml_node_type::node_pcdata).set_value(OcularString->toString<uint32_t>(static_cast<uint32_t>(scene->getStaticTreeType())).c_str());
                        dynamicSceneTreeNode.append_child(pugi::xml_node_type::node_pcdata).set_value(OcularString->toString<uint32_t>(static_cast<uint32_t>(scene->getDynamicTreeType())).c_str());
                        
                        // Renderer Type

                        pugi::xml_node rendererTypeNode = headerRoot.append_child("RendererType");
                        rendererTypeNode.append_child(pugi::xml_node_type::node_pcdata).set_value(scene->getRendererType().c_str());

                        // Lighting

                        pugi::xml_node lightingRoot = headerRoot.append_child("Lighting");
                        pugi::xml_node ambientIntensityNode = lightingRoot.append_child("AmbientIntensity");
                        pugi::xml_node ambientColorNode = lightingRoot.append_child("AmbientColor");

                        ambientIntensityNode.append_child(pugi::xml_node_type::node_pcdata).set_value(OcularString->toString<float>(OcularLights->getAmbientLightIntensity()).c_str());
                        ambientColorNode.append_child(pugi::xml_node_type::node_pcdata).set_value(OcularString->toString<Color>(OcularLights->getAmbientLightColor()).c_str());

                        //------------------------------------------------
                        // SceneTree
                        //------------------------------------------------

                        pugi::xml_node treeRoot = root.append_child("SceneTree");
                        std::vector<SceneObject*> topObjects;
                        OcularScene->findTopObjects(topObjects);

                        for(auto object : topObjects)
                        {
                            if(!object->isPersistent())
                            {
                                pugi::xml_node childNode = treeRoot.append_child("SceneObject");

                                Ocular::Core::Node_Internal internal;
                                internal.node = &childNode;

                                SceneObjectSaver::Save(object, &internal);
                            }
                        }

                        //------------------------------------------------
                        // Write
                        //------------------------------------------------

                        if(document.save_file(file.getFullPath().c_str(), "    "))
                        {
                            result = true;
                        }
                        else
                        {
                            OcularLogger->error("Failed to write XML document", OCULAR_INTERNAL_LOG("SceneSaver", "Save"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Failed to create root node", OCULAR_INTERNAL_LOG("SceneSaver", "Save"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to validate output file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("SceneSaver", "Save"));
                }
            }
            else
            {
                OcularLogger->error("Invalid (NULL) Scene parameter", OCULAR_INTERNAL_LOG("SceneSaver", "Save"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool SceneSaver::IsValidFile(File const& file)
        {
            bool result = true;

            if(!Utils::String::IsEqual(file.getExtension(), ".oscene"))
            {
                OcularLogger->error("Invalid file extension '", file.getExtension(), "' provided. Expected '.oscene'", OCULAR_INTERNAL_LOG("SceneSaver", "IsValidFile"));
                result = false;
            }

            return result;
        }
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}