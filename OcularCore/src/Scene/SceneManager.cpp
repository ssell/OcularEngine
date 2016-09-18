/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Scene/SceneManager.hpp"
#include "Scene/Camera/Camera.hpp"
#include "Scene/SceneLoader/SceneLoader.hpp"
#include "Scene/SceneSaver/SceneSaver.hpp"

#include "Events/Events/SceneObjectAddedEvent.hpp"
#include "Events/Events/SceneObjectRemovedEvent.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneManager::SceneManager()
        {
            m_Scene = nullptr;
        }

        SceneManager::~SceneManager()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        SceneObject* SceneManager::createObject(std::string const& name, SceneObject* parent)
        {
            return new SceneObject(name, parent);
        }

        SceneObject* SceneManager::createObjectOfType(std::string const& type, std::string const& name, SceneObject* parent)
        {
            SceneObject* result = m_SceneObjectFactory.createComponent(type);

            if(result)
            {
                result->setName(name);
                result->setParent(parent);
            }

            return result;
        }

        SceneObject* SceneManager::duplicateObject(SceneObject const* object)
        {
            // Simply use BuilderNodes: mock save to a builder chain and then
            // create a new object and 'load' that object from the chain.

            SceneObject* result = nullptr;

            if(object)
            {
                //--------------------------------------------------------
                // Copy the target object to a BuilderNode chain
                //--------------------------------------------------------

                BuilderNode builderNode(nullptr, "", "", "");
                object->onSave(&builderNode);
                
                //--------------------------------------------------------
                // Build the new object from the BuilderNode chain
                //--------------------------------------------------------

                result = new SceneObject();

                const UUID oldUUID = result->getUUID();    // Preserve the current UUID as onLoad will overwrite it with the target object's

                result->onLoad(&builderNode);              // Build the object
                result->setUUID(oldUUID.toString());       // Restore the UUID
                result->setParent(object->getParent());    // Set to same parent
            }

            return result;
        }

        void SceneManager::destroyObject(SceneObject* object)
        {
            for(auto iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
            {
                if(iter->second)
                {
                    if(iter->second == object)
                    {
                        deleteObject(object);
                        m_Objects.erase(iter);

                        break;
                    }
                }
            }
        }

        void SceneManager::destroyObject(std::string const& name, bool removeAll)
        {
            auto iter = m_Objects.begin();

            while(iter != m_Objects.end())
            {
                SceneObject* object = iter->second;

                if(object)
                {
                    if(object->getName().compare(name) == 0)
                    {
                        deleteObject(object);
                        iter = m_Objects.erase(iter);

                        if(removeAll)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                ++iter;
            }
        }

        void SceneManager::destroyObject(UUID const& uuid)
        {
            SceneObject* result = nullptr;
            const auto findObject = m_Objects.find(uuid.toString());

            if(findObject != m_Objects.end())
            {
                SceneObject* object = findObject->second;

                deleteObject(object);

                m_Objects.erase(findObject);
            }
        }

        SceneObject* SceneManager::findObject(std::string const& name) const
        {
            SceneObject* result = nullptr;
            auto iter = m_Objects.begin();

            while(iter != m_Objects.end())
            {
                if(iter->second)
                {
                    if(iter->second->getName().compare(name) == 0)
                    {
                        result = iter->second;
                        break;
                    }
                }

                ++iter;
            }

            return result;
        }

        void SceneManager::findObjects(std::string const& name, std::vector<SceneObject*>& objects) const
        {
            for(auto iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
            {
                if(iter->second)
                {
                    if(iter->second->getName().compare(name) == 0)
                    {
                        objects.emplace_back(iter->second);
                    }
                }
            }
        }

        SceneObject* SceneManager::findObject(UUID const& uuid) const
        {
            SceneObject* result = nullptr;
            const auto findObject = m_Objects.find(uuid.toString());

            if(findObject != m_Objects.end())
            {
                result = findObject->second;
            }

            return result;
        }

        void SceneManager::findTopObjects(std::vector<SceneObject*>& objects) const
        {
            for(auto iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
            {
                SceneObject* object = (*iter).second;

                if(object)
                {
                    if(object->getParent() == nullptr)
                    {
                        objects.push_back(object);
                    }
                }
            }
        }

        void SceneManager::updateUUID(UUID const& oldUUID)
        {
            // Check if the SceneObject tracked with the old UUID 
            // has had it's UUID changed (typically due to SceneObject::onLoad).

            // If it has, remove the old entry and add a new one
            // with the updated UUID.

            auto findObject = m_Objects.find(oldUUID.toString());

            if(findObject != m_Objects.end())
            {
                const UUID currentUUID = (*findObject).second->getUUID();

                if(oldUUID != currentUUID)
                {
                    if(m_Objects.find(currentUUID.toString()) == m_Objects.end())
                    {
                        m_Objects.insert(std::make_pair(currentUUID.toString(), (*findObject).second));
                        m_Objects.erase(findObject);
                    }
                    else
                    {
                        // The new UUID is already in use (potentially caused by a duplicate call or malformed setUUID).
                        // To avoid any complications, generate a new UUID for the object.

                        UUID newUUID;
                        findObject->second->setUUID(newUUID.toString());
                    }
                }
            }
        }

        void SceneManager::getVisibleSceneObjects(std::vector<SceneObject*>& objects, Math::Frustum const& frustum)
        {
            if(m_Scene)
            {
                m_Scene->getVisibleSceneObjects(objects, frustum);
            }
        }

        void SceneManager::triggerObjectDirty(UUID const& uuid, bool const staticObject)
        {
            if(m_Scene)
            {
                m_Scene->triggerObjectDirty(uuid, staticObject);
            }
        }

        void SceneManager::createScene(std::string const& name, SceneTreeType const staticType, SceneTreeType const dynamicType)
        {
            /**
             * Loading a scene requires the following steps:
             *
             *     1. Ensure the old scene (if valid) is completely unloaded.
             *     2. Load or create a new scene.
             *     3. Add all persistent objects to the scene.
             */

            if(m_Scene)
            {
                unloadScene();
            }

            m_Scene = new Scene();
            m_Scene->setStaticTreeType(staticType);
            m_Scene->setDynamicTreeType(dynamicType);
            m_Scene->setRendererType("EditorForwardRenderer");
            m_Scene->initialize();

            loadPersistentObjects();
        }

        bool SceneManager::loadScene(File const& file)
        {
            bool result = false;

            if(m_Scene)
            {
                unloadScene();
            }

            m_Scene = new Scene();

            if(SceneLoader::Load(m_Scene, file))
            {
                result = true;
                m_Scene->setRendererType("EditorForwardRenderer");
            }
            else
            {
                m_Scene->initialize();
            }

            loadPersistentObjects();

            return result;
        }

        bool SceneManager::saveScene(File const& file)
        {
            bool result = false;

            if(m_Scene)
            {
                result = SceneSaver::Save(m_Scene, file);
            }

            return result;
        }

        bool SceneManager::isSceneActive() const
        {
            return (m_Scene != nullptr);
        }

        ComponentFactory<ARoutine>& SceneManager::getRoutineFactory()
        {
            return m_RoutineFactory;
        }

        ComponentFactory<ARenderable>& SceneManager::getRenderableFactory()
        {
            return m_RenderableFactory;
        }

        ComponentFactory<SceneObject>& SceneManager::getSceneObjectFactory()
        {
            return m_SceneObjectFactory;
        }

        ComponentFactory<Renderer>& SceneManager::getRendererFactory()
        {
            return m_RendererFactory;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void SceneManager::loadPersistentObjects()
        {
            std::vector<SceneObject*> persistentObjects;
            persistentObjects.reserve(m_Objects.size());

            for(auto iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
            {
                SceneObject* object = iter->second;

                if(object && object->isPersistent())
                {
                    persistentObjects.emplace_back(object);
                }
            }

            m_Scene->addObjects(persistentObjects);
        }

        void SceneManager::addObject(SceneObject* object, SceneObject* parent)
        {
            // Ensure that the object isn't already managed by the SceneManager...
            
            if(object)
            {
                SceneObject* obj = findObject(object->getUUID());

                if(obj == nullptr)
                {
                    // Not already tracked. Add it.

                    const std::pair<std::string, SceneObject*> pair(object->getUUID().toString(), object);
                    m_Objects.insert(pair);

                    if(m_Scene)
                    {
                        m_Scene->addObject(object);
                        OcularEvents->queueEvent(std::make_shared<SceneObjectAddedEvent>(object));
                    }

                    if(parent)
                    {
                        parent->addChild(object);
                    }
                }
            }
        }

        void SceneManager::unloadScene()
        {
            //------------------------------------------------------------
            // Delete the Scene

            if(m_Scene)
            {
                delete m_Scene;
                m_Scene = nullptr;
            }

            //------------------------------------------------------------
            // Destroy all objects that are not marked as persistent

            auto objectIter = m_Objects.begin();

            while(objectIter != m_Objects.end())
            {
                SceneObject* object = objectIter->second;

                if(object)
                {
                    if(!object->isPersistent())
                    {
                        deleteObject(object);
                        objectIter = m_Objects.erase(objectIter);
                    }
                    else
                    {
                        ++objectIter;
                    }
                }
                else
                {
                    objectIter = m_Objects.erase(objectIter);
                }
            }
        }

        void SceneManager::update()
        {
            if(m_Scene)
            {
                m_Scene->update();
            }
        }

        void SceneManager::render()
        {
            if(m_Scene)
            {
                m_Scene->render();
            }
        }

        void SceneManager::objectActiveChanged(SceneObject* object)
        {
            if(object)
            {

            }
        }

        void SceneManager::objectVisibleChanged(SceneObject* object)
        {
            if(object)
            {

            }
        }

        void SceneManager::objectStaticChanged(SceneObject* object)
        {
            if(object)
            {
                if(m_Scene)
                {
                    m_Scene->objectTreeChanged(object);
                }
            }
        }

        void SceneManager::objectAddedRoutine(ARoutine* routine)
        {
            if(routine)
            {
                if(m_Scene)
                {
                    m_Scene->routineAdded(routine);
                }
            }
        }

        void SceneManager::objectRemovedRoutine(ARoutine* routine)
        {
            if(routine)
            {
                if(m_Scene)
                {
                    m_Scene->routineRemoved(routine);
                }
            }
        }

        void SceneManager::objectParentChanged(SceneObject* object, SceneObject* oldParent)
        {
            if(m_Scene && object && oldParent)
            {
                m_Scene->objectParentChanged(object, oldParent);
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void SceneManager::deleteObject(SceneObject* object)
        {
            if(object)
            {
                //--------------------------------------------------------
                // 1. Destroy any child objects
                //--------------------------------------------------------

                auto children = object->getAllChildren();

                for(auto child = children.begin(); child != children.end(); ++child)
                {
                    destroyObject((*child)->getUUID());
                }

                //--------------------------------------------------------
                // 2. Remove the object from the Scene
                //--------------------------------------------------------

                if(m_Scene)
                {
                    // Also removes it from it's parent
                    m_Scene->removeObject(object);
                }
                else
                {
                    object->setParent(nullptr);
                }

                //--------------------------------------------------------
                // 3. Inform about the removal
                //--------------------------------------------------------

                // We do this now so that our children generate removal events
                // before we do to preserve the bottom up flow.

                OcularEvents->queueEvent(std::make_shared<SceneObjectRemovedEvent>(object->getUUID()));

                //--------------------------------------------------------
                // 4. Delete the object
                //--------------------------------------------------------

                delete object;
                object = nullptr;
            }
        }
    }
}