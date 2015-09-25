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
#include "Scene/ARoutine.hpp"

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
            m_RoutinesAreDirty = false;

            switch(treeType)
            {
            case SceneTreeType::BoundingVolumeHierarchyCPU:
            {
                m_StaticSceneTree = new BVHSceneTree();
                m_DynamicSceneTree = new BVHSceneTree();
                break;
            }

            default:
            {
                m_StaticSceneTree = nullptr;
                m_DynamicSceneTree = nullptr;
                OcularLogger->error("Unsupported SceneTree Type specified for new SceneTree", OCULAR_INTERNAL_LOG("Scene", "Scene"));
                break;
            }
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
            updateTrees();
            updateRoutines();
        }

        void Scene::render()
        {

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Scene::updateTrees()
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

        void Scene::updateRoutines()
        {
            sortRoutines();
            
            const float delta = OcularEngine.Clock()->getDelta();

            for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
            {
                ARoutine* routine = (*iter);

                if(routine)
                {
                    SceneObject* parent = routine->getParent();

                    if(parent && parent->isActive())
                    {
                        routine->onUpdate(delta);
                    }
                }
            }
        }

        void Scene::sortRoutines()
        {
            if(m_RoutinesAreDirty)
            {
                std::sort(m_Routines.begin(), m_Routines.end(), [](ARoutine const* lhs, ARoutine const* rhs)->bool
                {
                    return (lhs->getPriorityLevel() > rhs->getPriorityLevel());
                });

                m_RoutinesAreDirty = false;
            }
        }

        void Scene::objectTreeChanged(SceneObject* object)
        {
            if(object)
            {
                if(object->isStatic())
                {
                    // Was dynamic, is now static.

                    if(m_DynamicSceneTree)
                    {
                        m_DynamicSceneTree->removeObject(object);
                    }

                    if(m_StaticSceneTree)
                    {
                        m_StaticSceneTree->addObject(object);
                    }
                }
                else
                {
                    // Was static, is now dynamic.

                    if(m_StaticSceneTree)
                    {
                        m_StaticSceneTree->removeObject(object);
                    }
                    
                    if(m_DynamicSceneTree)
                    {
                        m_DynamicSceneTree->addObject(object);
                    }
                }
            }
        }

        void Scene::routineAdded(ARoutine* routine)
        {
            if(routine)
            {
                m_Routines.insert(m_Routines.begin(), routine);
                m_RoutinesAreDirty = true;
            }
        }

        void Scene::routineRemoved(ARoutine* routine)
        {
            if(routine)
            {
                for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
                {
                    if((*iter) == routine)
                    {
                        m_Routines.erase(iter);
                        break;
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}