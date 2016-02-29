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

#include "Scene/SceneLoader/SceneObjectLoader.hpp"
#include "Scene/SceneLoader/SceneLoader.hpp"
#include "Scene/SceneLoader/SceneLoadInternal.hpp"
#include "Scene/ARenderable.hpp"
#include "Scene/ARoutine.hpp"
#include "Utilities/StringUtils.hpp"
#include "OcularEngine.hpp"

#include <pugixml/pugixml.hpp>

using namespace Ocular::Utils;

//------------------------------------------------------------------------------------------

Ocular::Core::SceneObject* ParseGeneral(pugi::xml_node& root);
Ocular::Core::SceneObject* CreateObject(std::string const& name, std::string const& uuid, std::string const& parentUUID, std::string const& type);

void ParseBounds(pugi::xml_node& root, Ocular::Core::SceneObject* object);
void ParseTransform(pugi::xml_node& root, Ocular::Core::SceneObject* object);
void ParseRenderable(pugi::xml_node& root, Ocular::Core::SceneObject* object);
void ParseRoutines(pugi::xml_node& root, Ocular::Core::SceneObject* object);
//void SetExposedValue(std::string const& value, ExposedVariable& exposed);

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
                    result = ParseGeneral(*root);

                    if(result)
                    {
                        ParseBounds(*root, result);
                        ParseTransform(*root, result);
                        ParseRenderable(*root, result);
                        ParseRoutines(*root, result);
                    }
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

//------------------------------------------------------------------------------------------
// OUT-OF-CLASS METHODS
//------------------------------------------------------------------------------------------

Ocular::Core::SceneObject* ParseGeneral(pugi::xml_node& root)
{
    Ocular::Core::SceneObject* result = nullptr;

    // Attempt to parse out the following components:
    //
    //     - Name
    //     - UUID
    //     - Parent UUID

    //--------------------------------------------------------------------
    // Parse Name, Type, UUID, and Parent UUID prior to SceneObject creation
    //--------------------------------------------------------------------

    pugi::xml_node nameNode   = root.child("Name");
    pugi::xml_node typeNode   = root.child("Type");
    pugi::xml_node uuidNode   = root.child("UUID");
    pugi::xml_node parentNode = root.child("Parent");

    std::string name;
    std::string type;
    std::string uuid;
    std::string parent;

    if(nameNode)
    {
        name = nameNode.text().as_string();
    }

    if(typeNode)
    {
        type = typeNode.text().as_string();
    }

    if(uuidNode)
    {
        uuid = uuidNode.text().as_string();
    }

    if(parentNode)
    {
        parent = parentNode.text().as_string();
    }

    result = CreateObject(name, type, uuid, parent);

    return result;
}

Ocular::Core::SceneObject* CreateObject(std::string const& name, std::string const& type, std::string const& uuid, std::string const& parentUUID)
{
    Ocular::Core::SceneObject* result = nullptr;
    Ocular::Core::SceneObject* parent = nullptr;

    if(parentUUID.size())
    {
        parent = OcularScene->findObject(Ocular::Core::UUID(parentUUID));
    }

    // Handle different types..

    result = OcularScene->createObject(name, parent);
    
    if(uuid.size())
    {
        result->setUUID(uuid);
    }

    return result;
}

void ParseBounds(pugi::xml_node& root, Ocular::Core::SceneObject* object)
{
    pugi::xml_node aabbNode   = root.child("BoundsAABB");
    pugi::xml_node obbNode    = root.child("BoundsOBB");
    pugi::xml_node sphereNode = root.child("BoundsSphere");

    if(aabbNode)
    {
        // <BoundsAABB>
        //     <Center>0.0 0.0 0.0</Center>
        //     <Extents>0.0 0.0 0.0</Extents>
        // </BoundsAABB>

        pugi::xml_node centerNode  = aabbNode.child("Center");
        pugi::xml_node extentsNode = aabbNode.child("Extents");

        if(centerNode)
        {
            Ocular::Math::Vector3f center = OcularString->fromString<Ocular::Math::Vector3f>(centerNode.text().as_string());
            object->boundsAABB.setCenter(center);
        }

        if(extentsNode)
        {
            Ocular::Math::Vector3f extents = OcularString->fromString<Ocular::Math::Vector3f>(extentsNode.text().as_string());
            object->boundsAABB.setExtents(extents);
        }
    }
    // else
    // {
    //     No AABB set which is OK
    // }

    if(obbNode)
    {
        // <BoundsOBB>
        //     <Center>0.0 0.0 0.0</Center>
        //     <Extents>0.0 0.0 0.0</Extents>
        //     <XDirection>0.0 0.0 0.0</XDirection>
        //     <YDirection>0.0 0.0 0.0</YDirection>
        //     <ZDirection>0.0 0.0 0.0</ZDirection>
        // </BoundsOBB>
            
        pugi::xml_node centerNode  = obbNode.child("Center");
        pugi::xml_node extentsNode = obbNode.child("Extents");
        pugi::xml_node xDirNode    = obbNode.child("XDirection");
        pugi::xml_node yDirNode    = obbNode.child("YDirection");
        pugi::xml_node zDirNode    = obbNode.child("ZDirection");

        if(centerNode)
        {
            Ocular::Math::Vector3f center = OcularString->fromString<Ocular::Math::Vector3f>(centerNode.text().as_string());
            object->boundsOBB.setCenter(center);
        }

        if(extentsNode)
        {
            Ocular::Math::Vector3f extents = OcularString->fromString<Ocular::Math::Vector3f>(extentsNode.text().as_string());
            object->boundsOBB.setCenter(extents);
        }

        if(xDirNode)
        {
            Ocular::Math::Vector3f xDir = OcularString->fromString<Ocular::Math::Vector3f>(xDirNode.text().as_string());
            object->boundsOBB.setCenter(xDir);
        }

        if(yDirNode)
        {
            Ocular::Math::Vector3f yDir = OcularString->fromString<Ocular::Math::Vector3f>(yDirNode.text().as_string());
            object->boundsOBB.setCenter(yDir);
        }

        if(zDirNode)
        {
            Ocular::Math::Vector3f zDir = OcularString->fromString<Ocular::Math::Vector3f>(zDirNode.text().as_string());
            object->boundsOBB.setCenter(zDir);
        }
    }
    // else
    // {
    //     No OBB set which is OK
    // }

    if(sphereNode)
    {
        // <BoundsSphere>
        //     <Center>0.0 0.0 0.0</Center>
        //     <Radius>0.0</Radius>
        // </BoundsSphere>

        pugi::xml_node centerNode = sphereNode.child("Center");
        pugi::xml_node radiusNode = sphereNode.child("Radius");

        if(centerNode)
        {
            Ocular::Math::Vector3f center = OcularString->fromString<Ocular::Math::Vector3f>(centerNode.text().as_string());
            object->boundsSphere.setCenter(center);
        }

        if(radiusNode)
        {
            object->boundsSphere.setRadius(radiusNode.text().as_float());
        }
    }
    // else
    // {
    //     No bounding sphere set which is OK
    // }
}

void ParseTransform(pugi::xml_node& root, Ocular::Core::SceneObject* object)
{
    // <Transform>
    //     <Position>0.0 0.0 0.0</Position>
    //     <Scaling>0.0 0.0 0.0</Scaling>
    //     <Rotation>0.0 0.0 0.0 0.0</Rotation>
    // </Transform>

    pugi::xml_node transformNode = root.child("Transform");

    if(transformNode)
    {
        pugi::xml_node positionNode = transformNode.child("Position");
        pugi::xml_node scalingNode  = transformNode.child("Scaling");
        pugi::xml_node rotationNode = transformNode.child("Rotation");

        if(positionNode)
        {
            Ocular::Math::Vector3f position = OcularString->fromString<Ocular::Math::Vector3f>(positionNode.text().as_string());
            object->getTransform().setPosition(position);
        }

        if(scalingNode)
        {
            Ocular::Math::Vector3f scaling = OcularString->fromString<Ocular::Math::Vector3f>(scalingNode.text().as_string());
            object->getTransform().setScale(scaling);
        }

        if(rotationNode)
        {
            Ocular::Math::Vector3f rotation = OcularString->fromString<Ocular::Math::Vector3f>(rotationNode.text().as_string());
            object->getTransform().setRotation(rotation);
        }
    }
    // else
    // {
    //     No transform set which is OK
    // }
}

void ParseRenderable(pugi::xml_node& root, Ocular::Core::SceneObject* object)
{
    // <Renderable>
    //     <Name>Some Name</Name>
    // </Renderable>

    // The above is the only required data for a Renderable. 
    // But there is expected to be numerous exposed custom variables.

    pugi::xml_node renderableNode = root.child("Renderable");

    if(renderableNode)
    {
        pugi::xml_node nameNode = renderableNode.child("Name");

        if(nameNode)
        {
            const std::string name = nameNode.text().as_string();
            Ocular::Core::ARenderable* renderable = object->setRenderable(name);

            if(renderable)
            {
                // Successfully added renderable. Now check for and parse any exposed variables

                /*std::vector<std::string> exposedNames;
                renderable->getAllExposedNames(exposedNames);

                for(auto exposedName : exposedNames)
                {
                    pugi::xml_node exposedNode = renderableNode.child(exposedName.c_str());
                    ExposedVariable exposed; 

                    if((exposedNode) && (renderable->getVariable(exposedName, exposed)))
                    {
                        SetExposedValue(exposedNode.text().as_string(), exposed);
                    }
                }*/
            }
            else
            {
                OcularLogger->warning("Failed to set Renderable for object '", object->getName(), "' of type '", name, "'", OCULAR_INTERNAL_LOG("SceneObjectLoader", "ParseRenderable"));
            }
        }
        // else
        // {
        //     No renderable set which is OK
        // }
    }
    // else
    // {
    //     No renderable set which is OK
    // }
}

void ParseRoutines(pugi::xml_node& root, Ocular::Core::SceneObject* object)
{

}

/*void SetExposedValue(std::string const& value, ExposedVariable& exposed)
{
    const std::string type = exposed.type;

    if(String::IsEqual(type, OCULAR_TYPE_NAME(float)))
    {
        StringUtils::StringToFloat(value, *(float*)exposed.ptr);
    }
    else if(String::IsEqual(type, OCULAR_TYPE_NAME(Ocular::Core::Resource)))
    {
        *(&exposed.ptr) = OcularResources->getResource(value);
    }
}*/
