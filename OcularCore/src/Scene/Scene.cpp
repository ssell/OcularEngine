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

#include "OcularEngine.hpp"

#include "Scene/Scene.hpp"
#include "Scene/ISceneTree.hpp"
#include "Scene/SceneObject.hpp"

// SceneTree implementations

#include "Scene/BVHSceneTree.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Scene::Scene(SceneTreeType treeType)
        {
            switch(treeType)
            {
            case SceneTreeType::BoundingVolumeHierarchyCPU:
                m_SceneTree = new BVHSceneTree();
                break;

            default:
                m_SceneTree = nullptr;
                OcularLogger->error("Unsupported SceneTree Type specified for new SceneTree", OCULAR_INTERNAL_LOG("Scene", "Scene"));
                break;
            }
        }

        Scene::~Scene()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Scene::addObject(SceneObject* object)
        {
            if(object)
            {
                if(object->isStatic())
                {
                    if(m_StaticSceneTree)
                    {
                        m_StaticSceneTree->addObject(object);
                    }
                }
                else
                {
                    if(m_DynamicSceneTree)
                    {
                        m_DynamicSceneTree->addObject(object);
                    }
                }
            }
        }

        void Scene::addObjects(std::vector<SceneObject*> const& objects)
        {
            for(auto iter = objects.begin(); iter != objects.end(); ++iter)
            {
                addObject((*iter));
            }
        }

        void Scene::removeObject(SceneObject* object)
        {
            bool result = true;

            if(object)
            {
                if(object->isStatic())
                {
                    if(m_StaticSceneTree)
                    {
                        result = m_StaticSceneTree->removeObject(object);
                    }
                }

                if(!object->isStatic() || !result)
                {
                    // Object is dynamic or was not found in the static tree to remove...

                    if(m_DynamicSceneTree)
                    {
                        m_DynamicSceneTree->removeObject(object);
                    }
                }
            }
        }

        void Scene::removeObjects(std::vector<SceneObject*> const& objects)
        {
            for(auto iter = objects.begin(); iter != objects.end(); ++iter)
            {
                removeObject((*iter));
            }
        }

        void Scene::removeAllObjects()
        {
            if(m_StaticSceneTree)
            {
                m_StaticSceneTree->destroy();
            }

            if(m_DynamicSceneTree)
            {
                m_DynamicSceneTree->destroy();
            }
        }

        void Scene::update()
        {
            if(m_StaticSceneTree)
            {
                m_StaticSceneTree->restructure();
            }

            if(m_DynamicSceneTree)
            {
                m_DynamicSceneTree->restructure();
            }
        }

        void Scene::render()
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