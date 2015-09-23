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

        SceneObject* SceneManager::createObject(std::string const& name)
        {
            SceneObject* newObject = new SceneObject(name);  // The constructor calls addObject which will do the rest...
            return newObject;
        }

        void SceneManager::addObject(SceneObject* object)
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
                    }
                }
            }
        }

        SceneObject* SceneManager::duplicateObject(SceneObject const* object)
        {
            return nullptr;
        }

        void SceneManager::removeObject(SceneObject* object)
        {
            for(auto iter = m_Objects.begin(); iter != m_Objects.end(); ++iter)
            {
                if(iter->second)
                {
                    if(iter->second == object)
                    {
                        if(m_Scene)
                        {
                            m_Scene->removeObject(object);
                        }

                        m_Objects.erase(iter);
                        break;
                    }
                }
            }
        }

        void SceneManager::removeObject(std::string const& name, std::vector<SceneObject*>& objects, bool removeAll)
        {
            auto iter = m_Objects.begin();

            while(iter != m_Objects.end())
            {
                if(iter->second)
                {
                    if(iter->second->getName().compare(name) == 0)
                    {
                        if(m_Scene)
                        {
                            m_Scene->removeObject(iter->second);
                        }

                        objects.emplace_back(iter->second);
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

        SceneObject* SceneManager::removeObject(UUID const& uuid)
        {
            SceneObject* result = nullptr;
            const auto findObject = m_Objects.find(uuid.toString());

            if(findObject != m_Objects.end())
            {
                if(m_Scene)
                {
                    m_Scene->removeObject(findObject->second);
                }

                result = findObject->second;
                m_Objects.erase(findObject);
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
                        if(m_Scene)
                        {
                            m_Scene->removeObject(object);
                        }

                        m_Objects.erase(iter);

                        delete object;
                        object = nullptr;

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
                if(iter->second)
                {
                    if(iter->second->getName().compare(name) == 0)
                    {
                        if(m_Scene)
                        {
                            m_Scene->removeObject(iter->second);
                        }

                        delete iter->second;
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
                if(m_Scene)
                {
                    m_Scene->removeObject(findObject->second);
                }

                delete findObject->second;
                m_Objects.erase(uuid.toString());
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

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void SceneManager::unloadScene()
        {
            /**
             * Unloading a scene requires the following steps:
             *
             *    1. Remove all objects from that scene's tree
             *    2. Delete all objects that are not marked as persistant.
             *    3. Delete the scene itself.
             */

            m_Scene->removeAllObjects();

            auto objectIter = m_Objects.begin();

            while(objectIter != m_Objects.end())
            {
                if(objectIter->second)
                {
                    if(!objectIter->second->isPersistent())
                    {
                        delete objectIter->second;
                        objectIter = m_Objects.erase(objectIter);

                        continue;
                    }
                }

                ++objectIter;
            }

            delete m_Scene;
            m_Scene = nullptr;
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

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}