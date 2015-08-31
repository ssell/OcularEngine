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
            SceneObject* newObject = new SceneObject(name);

            const std::pair<std::string, SceneObject*> pair(newObject->getUUID().toString(), newObject);
            m_Objects.insert(pair);  // std::make_pair did not want to work here...

            if(m_Scene)
            {
                m_Scene->addObject(newObject);
            }

            return newObject;
        }

        SceneObject* SceneManager::duplicateObject(SceneObject const* object)
        {
            return nullptr;
        }

        void SceneManager::removeObject(SceneObject* object)
        {
            auto iter = m_Objects.begin();

            while(iter != m_Objects.end())
            {
                if(iter->second)
                {
                    if(iter->second == object)
                    {
                        if(m_Scene)
                        {
                            m_Scene->removeObject(iter->second);
                        }

                        delete iter->second;
                        iter = m_Objects.erase(iter);

                        break;
                    }
                    else
                    {
                        ++iter;
                    }
                }
            }
        }

        void SceneManager::removeObject(std::string const& name, bool removeAll)
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

                        if(!removeAll)
                        {
                            break;
                        }
                    }
                    else
                    {
                        ++iter;
                    }
                }
            }
        }

        void SceneManager::removeObject(UUID const& uuid)
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
                    else
                    {
                        ++iter;
                    }
                }
            }

            return result;
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

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}