/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
            SceneObject* newObject = new SceneObject(name);  // The constructor calls addObject which will do the rest...

            if(m_Scene)
            {
                /**
                 * Do we need to add it to the scene?
                 *
                 * As a brand-new object it will not have any renderables or routines.
                 * So our only concern is if it does not have a parent. 
                 * 
                 * If there is no parent, then it is a 'top-level' object and will
                 * need to be known to the SceneTrees.
                 */

                if(parent)
                {
                    parent->addChild(newObject);
                }
                else
                {
                    m_Scene->addObject(newObject);
                }
            }

            return newObject;
        }

        SceneObject* SceneManager::duplicateObject(SceneObject const* object)
        {
            return nullptr;
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

        void SceneManager::loadScene(std::string const& name, SceneTreeType treeType)
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

            /// \todo Search for a scene file and load it. But for now, always create a new scene.
            m_Scene = new Scene(treeType);
            
            std::vector<SceneObject*> persistentObjects(m_Objects.size());

            for(auto iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
            {
                persistentObjects.emplace_back(iter->second);
            }

            m_Scene->addObjects(persistentObjects);
        }

        RoutineFactory& SceneManager::getRoutineFactory()
        {
            return m_RoutineFactory;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

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
                        if(parent)
                        {
                            parent->addChild(object);
                        }
                        else
                        {
                            m_Scene->addObject(object);
                        }
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
            if(m_Scene)
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
                // 1. Remove the object from the Scene

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
                // 3. Destroy any child objects

                auto children = object->getAllChildren();

                for(auto child = children.begin(); child != children.end(); ++child)
                {
                    destroyObject((*child)->getUUID());
                }
                
                //--------------------------------------------------------
                // 4. Delete the object

                delete object;
                object = nullptr;
            }
        }
    }
}