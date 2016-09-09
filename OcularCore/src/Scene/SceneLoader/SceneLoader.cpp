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

#include "Scene/SceneLoader/SceneLoader.hpp"
#include "Scene/SceneLoader/SceneObjectLoader.hpp"
#include "Scene/SceneLoader/SceneLoadInternal.hpp"
#include "Utilities/StringUtils.hpp"
#include "Math/Color.hpp"

#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

//------------------------------------------------------------------------------------------

namespace
{
    const std::string DefaultRendererType = "ForwardRenderer";
}

bool ParseSceneHeader(pugi::xml_node& root, Ocular::Core::Scene* scene);
void ParseSceneTreeType(pugi::xml_node& root, Ocular::Core::SceneTreeType& staticType, Ocular::Core::SceneTreeType& dynamicType);
bool ParseSceneTree(pugi::xml_node& root);

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
        
        bool SceneLoader::Load(Scene* scene, File const& file)
        {
            bool result = false;

            if(scene)
            {
                if(IsValidFile(file))
                {
                    pugi::xml_document document;
                    pugi::xml_parse_result parseResult = document.load_file(file.getFullPath().c_str());

                    if(parseResult)
                    {
                        pugi::xml_node root = document.child("OcularScene");

                        if(root)
                        {
                            if(ParseSceneHeader(root, scene))
                            {
                                scene->initialize();
                                
                                if(ParseSceneTree(root))
                                {
                                    result = true;
                                }
                                else
                                {
                                    OcularLogger->error("Failed to parse scene tree", OCULAR_INTERNAL_LOG("SceneLoader", "Load"));
                                }
                            }
                            else
                            {
                                OcularLogger->error("Failed to parse header", OCULAR_INTERNAL_LOG("SceneLoader", "Load"));
                            }
                        }
                        else
                        {
                            OcularLogger->error("Failed to locate root node <OcularScene>", OCULAR_INTERNAL_LOG("SceneLoader", "Load"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Failed to parse XML document", OCULAR_INTERNAL_LOG("SceneLoader", "Load"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to validate file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("SceneLoader", "Load"));
                }
            }
            else
            {
                OcularLogger->error("Invalid (NULL) Scene parameter", OCULAR_INTERNAL_LOG("SceneLoader", "Load"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        bool SceneLoader::IsValidFile(File const& file)
        {
            bool result = true;

            if(!file.exists())
            {
                OcularLogger->error("File does not exist", OCULAR_INTERNAL_LOG("SceneLoader", "IsValidFile"));
                result = false;
            }

            if(!file.canRead())
            {
                OcularLogger->error("File can not be read", OCULAR_INTERNAL_LOG("SceneLoader", "IsValidFile"));
                result = false;
            }

            if(!Utils::String::IsEqual(file.getExtension(), ".oscene"))
            {
                OcularLogger->error("File is invalid type. Expecting '.oscene'", OCULAR_INTERNAL_LOG("SceneLoader", "IsValidFile"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

//------------------------------------------------------------------------------------------
// OUT-OF-CLASS FUNCTIONS
//------------------------------------------------------------------------------------------

bool ParseSceneHeader(pugi::xml_node& root, Ocular::Core::Scene* scene)
{
    bool result = false;
    pugi::xml_node headerNode = root.child("SceneHeader");

    if(headerNode)
    {
        //----------------------------------------------------------------
        // SceneTree Type
        //----------------------------------------------------------------

        pugi::xml_node sceneTreeTypeNode = headerNode.child("SceneTreeType");

        if(sceneTreeTypeNode)
        {
            Ocular::Core::SceneTreeType staticType;
            Ocular::Core::SceneTreeType dynamicType;

            ParseSceneTreeType(sceneTreeTypeNode, staticType, dynamicType);

            scene->setStaticTreeType(staticType);
            scene->setDynamicTreeType(dynamicType);
        }
        // else
        // {
        //     The <SceneTreeType> node is optional, so it's absence 
        //     does not necessarily indicate an error 
        // }
        
        //----------------------------------------------------------------
        // Renderer Type
        //----------------------------------------------------------------

        pugi::xml_node rendererTypeNode = headerNode.child("RendererType");

        if(rendererTypeNode)
        {
            scene->setRendererType(rendererTypeNode.text().as_string());
        }
        else
        {
            scene->setRendererType(DefaultRendererType);
        }

        //----------------------------------------------------------------
        // Lighting
        //----------------------------------------------------------------

        pugi::xml_node lightingRootNode = headerNode.child("Lighting");

        if(lightingRootNode)
        {
            pugi::xml_node ambientIntensityNode = lightingRootNode.child("AmbientIntensity");
            pugi::xml_node ambientColorNode = lightingRootNode.child("AmbientColor");

            if(ambientIntensityNode)
            {
                OcularLights->setAmbientLightIntensity(OcularString->fromString<float>(ambientIntensityNode.text().as_string()));
            }
            
            if(ambientColorNode)
            {
                OcularLights->setAmbientLightColor(OcularString->fromString<Ocular::Core::Color>(ambientColorNode.text().as_string()));
            }
        }

        result = true;
    }
    else
    {
        OcularLogger->error("Failed to locate header node <SceneHeader>", OCULAR_INTERNAL_LOG("SceneLoader", "ParseSceneHeader"));
    }

    return result;
}

void ParseSceneTreeType(pugi::xml_node& typeNode, Ocular::Core::SceneTreeType& staticType, Ocular::Core::SceneTreeType& dynamicType)
{
    staticType  = Ocular::Core::SceneTreeType::BoundingVolumeHierarchyCPU;      // CPU BVH by default
    dynamicType = Ocular::Core::SceneTreeType::BoundingVolumeHierarchyCPU;

    pugi::xml_node staticNode  = typeNode.child("Static");
    pugi::xml_node dynamicNode = typeNode.child("Dynamic");

    uint32_t value;

    if(staticNode)
    {
        value = staticNode.text().as_uint();
        staticType = static_cast<Ocular::Core::SceneTreeType>(value);
    }

    if(dynamicNode)
    {
        value = dynamicNode.text().as_uint();
        dynamicType = static_cast<Ocular::Core::SceneTreeType>(value);
    }
}

bool ParseSceneTree(pugi::xml_node& root)
{
    // At this point, the Scene will have been created and set as the 
    // active Scene. So any new objects will be automatically added
    // to it via the SceneManager. So all we have to do is create
    // the objects, and the rest is handled automatically.

    bool result = false;
    pugi::xml_node treeRoot = root.child("SceneTree");

    if(treeRoot)
    {
        auto sceneObjects = treeRoot.children();
        Ocular::Core::Node_Internal node;
        
        for(auto iter = sceneObjects.begin(); iter != sceneObjects.end(); ++iter)
        {
            node.node = &(*iter);
            Ocular::Core::SceneObjectLoader::Load(&node);
        }

        result = true;
    }
    else
    {
        OcularLogger->error("Failed to locate tree node <SceneTree>", OCULAR_INTERNAL_LOG("SceneLoader", "ParseSceneTree"));
    }

    return result;
}