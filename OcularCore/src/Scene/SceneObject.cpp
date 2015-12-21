/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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

#include "OcularEngine.hpp"
#include "Scene/SceneObject.hpp"
#include "Scene/ARoutine.hpp"
#include "Scene/ARenderable.hpp"
#include "Scene/RoutineFactory.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneObject::SceneObject(std::string const& name, SceneObject* parent)
            : Object(name),
              m_IsStatic(false),
              m_IsActive(true),
              m_IsVisible(false),
              m_ForcedVisible(false),
              m_Persists(false),
              m_Parent(parent)
        {
            OcularScene->addObject(this, parent);
        }

        SceneObject::SceneObject()
            : Object("SceneObject"),
              m_IsStatic(false),
              m_IsActive(true),
              m_IsVisible(false),
              m_ForcedVisible(false),
              m_Persists(false),
              m_Parent(nullptr)
        {
            OcularScene->addObject(this);
        }

        SceneObject::~SceneObject()
        {
            /** 
             * At this point the SceneManager/Scene have done the following:
             *
             *     - Removed this object from it's parent
             *     - Removed this object from the SceneTrees
             *     - Removed this object's routines from the Scene
             *     - Removed this object from the SceneManager
             *
             * What is left is to:
             *
             *     - Verify the above as much as possible
             *     - Destroy the routines
             *     - Destroy the renderables
             */

            //------------------------------------------------------------
            // Verify parent and children were removed

            if(m_Parent)
            {
                // Parent was not properly undone
                setParent(nullptr);
            }

            if(m_Children.size() > 0)
            {
                // Children were not properly destroyed
                while(m_Children.size() > 0)
                {
                    // This also calls child->setParent(nullptr) so removes it from our child list
                    OcularScene->destroyObject(m_Children[0]);
                }
            }

            //------------------------------------------------------------
            // Delete the routines

            while(m_Routines.size() > 0)
            {
                ARoutine* routine = m_Routines[0];

                if(routine)
                {
                    routine->onDestruction();
                    
                    delete routine;
                    routine = nullptr;
                }

                m_Routines.erase(m_Routines.begin());
            }

            //------------------------------------------------------------
            // Delete the renderable

            if(m_Renderable)
            {
                delete m_Renderable;
                m_Renderable = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------
        // General Misc Methods
        //----------------------------------------------------------------

        Math::Transform& SceneObject::getTransform()
        {
            return m_Transform;
        }

        void SceneObject::setActive(bool active)
        {
            if(m_IsActive != active)
            {
                m_IsActive = active;
                OcularScene->objectActiveChanged(this);

                //--------------------------------------------------------
                // Propagate the state change to the child objects

                for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
                {
                    SceneObject* object = (*iter);

                    if(object)
                    {
                        object->setActive(active);
                    }
                }
            }
        }

        bool SceneObject::isActive() const
        {
            return m_IsActive;
        }

        void SceneObject::setVisible(bool visible)
        {
            m_IsVisible = visible;
        }

        bool SceneObject::isVisible() const
        {
            return m_IsVisible;
        }

        void SceneObject::setForcedVisible(bool forced)
        {
            if(m_ForcedVisible != forced)
            {
                m_ForcedVisible = forced;
                OcularScene->objectVisibleChanged(this);

                //--------------------------------------------------------
                // Propagate the state change to the child objects

                for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
                {
                    SceneObject* object = (*iter);

                    if(object)
                    {
                        object->setForcedVisible(forced);
                    }
                }
            }
        }

        bool SceneObject::isForcedVisible() const
        {
            return m_ForcedVisible;
        }

        void SceneObject::setStatic(bool isStatic)
        {
            if(m_IsStatic != isStatic)
            {
                m_IsStatic = isStatic;
                OcularScene->objectStaticChanged(this);
            }
        }

        bool SceneObject::isStatic() const
        {
            return m_IsStatic;
        }

        void SceneObject::setPersistent(bool persists)
        {
            m_Persists = persists;
        }

        bool SceneObject::isPersistent() const
        {
            return m_Persists;
        }

        Graphics::UniformPerObject const& SceneObject::getUniformData()
        {
            m_Transform.getModelMatrix(m_UniformData.modelMatrix);
            return m_UniformData;
        }

        //----------------------------------------------------------------
        // Movement and Rotation Methods
        //----------------------------------------------------------------

        void SceneObject::setPosition(float const x, float const y, float const z)
        {
            m_Transform.setPosition(x, y, z);
        }

        void SceneObject::setPosition(Math::Vector3f const& position)
        {
            m_Transform.setPosition(position);
        }

        Math::Vector3f const& SceneObject::getPosition() const
        {
            return m_Transform.getPosition();
        }

        void SceneObject::translate(Math::Vector3f const& translation, bool local)
        {
            m_Transform.translate(translation, local);
        }

        void SceneObject::rotate(float const angle, Math::Vector3f const& axis)
        {
            m_Transform.rotate(angle, axis);
        }

        void SceneObject::rotate(Math::Quaternion const& rotation)
        {
            m_Transform.rotate(rotation);
        }

        void SceneObject::resetRotation()
        {
            m_Transform.setRotation(Math::Quaternion());
        }

        void SceneObject::setRotation(Math::Quaternion const& rotation)
        {
            m_Transform.setRotation(rotation);
        }

        Math::Quaternion const& SceneObject::getRotation() const
        {
            return m_Transform.getRotation();
        }

        void SceneObject::setTransform(Math::Transform const& transform)
        {
            m_Transform = transform;
        }

        Math::Transform const& SceneObject::getTransform() const
        {
            return m_Transform;
        }

        //----------------------------------------------------------------
        // Child Object Methods
        //----------------------------------------------------------------

        void SceneObject::setParent(SceneObject* parent)
        {
            if(parent != m_Parent)
            {
                if(parent)
                {
                    parent->addChild(this);
                }
                else
                {
                    SceneObject* oldParent = m_Parent;

                    if(oldParent)
                    {
                        oldParent->removeChild(this);
                    }

                    m_Parent = parent;
                    OcularScene->objectParentChanged(this, oldParent);
                }
            }
        }

        SceneObject* SceneObject::getParent() const
        {
            return m_Parent;
        }

        SceneObject* SceneObject::createChild(std::string const& name)
        {
            SceneObject* child = OcularScene->createObject(name, this);
            return child;
        }

        void SceneObject::addChild(SceneObject* child)
        {
            if(child)
            {
                SceneObject* oldParent = child->getParent();
                oldParent->removeChild(child);

                child->m_Parent = this;
                child->setActive(isActive());
                child->setForcedVisible(isForcedVisible());
                child->setStatic(isStatic());

                m_Children.emplace_back(child);

                OcularScene->objectParentChanged(child, oldParent);
            }
        }

        SceneObject* SceneObject::findChild(std::string const& name)
        {
            SceneObject* result = nullptr;

            for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
            {
                SceneObject* child = (*iter);

                if(child)
                {
                    if(child->getName().compare(name) == 0)
                    {
                        result = child;
                        break;
                    }
                }
            }

            return result;
        }

        SceneObject* SceneObject::findChild(UUID const& uuid)
        {
            SceneObject* result = nullptr;

            for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
            {
                SceneObject* child = (*iter);

                if(child)
                {
                    if(child->getUUID() == uuid)
                    {
                        result = child;
                        break;
                    }
                }
            }

            return result;
        }

        SceneObject* SceneObject::removeChild(std::string const& name)
        {
            SceneObject* result = nullptr;

            for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
            {
                SceneObject* child = (*iter);

                if(child)
                {
                    if(child->getName().compare(name) == 0)
                    {
                        result = child;
                        m_Children.erase(iter);

                        child->m_Parent = nullptr;
                        OcularScene->objectParentChanged(child, this);

                        break;
                    }
                }
            }

            return result;
        }

        SceneObject* SceneObject::removeChild(UUID const& uuid)
        {
            SceneObject* result = nullptr;

            for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
            {
                SceneObject* child = (*iter);

                if(child)
                {
                    if(child->getUUID() == uuid)
                    {
                        result = child;
                        m_Children.erase(iter);

                        child->m_Parent = nullptr;
                        OcularScene->objectParentChanged(child, this);

                        break;
                    }
                }
            }

            return result;
        }

        SceneObject* SceneObject::removeChild(SceneObject const* object)
        {
            SceneObject* result = nullptr;

            for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
            {
                SceneObject* child = (*iter);

                if(child == object)
                {
                    result = child;
                    m_Children.erase(iter);

                    child->m_Parent = nullptr;
                    OcularScene->objectParentChanged(child, this);

                    break;
                }
            }

            return result;
        }

        uint32_t SceneObject::getNumChildren() const
        {
            return m_Children.size();
        }

        std::vector<SceneObject*> const& SceneObject::getAllChildren() const
        {
            return m_Children;
        }

        //----------------------------------------------------------------
        // Routine Methods
        //----------------------------------------------------------------

        bool SceneObject::addRoutine(std::string const& name)
        {
            bool result = false;
            ARoutine* routine = OcularScene->getRoutineFactory().createRoutine(name);

            if(routine)
            {
                routine->setParent(this);
                routine->setName(name);
                routine->onCreation();

                result = true;
            }

            return result;
        }

        bool SceneObject::removeRoutine(std::string const& name)
        {
            bool result = false;

            for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
            {
                ARoutine* routine = (*iter);

                if(routine)
                {
                    if(routine->getName().compare(name) == 0)
                    {
                        m_Routines.erase(iter);

                        OcularScene->objectRemovedRoutine(routine);
                        routine->onDestruction();

                        delete routine;
                        routine = nullptr;

                        result = true;
                        break;
                    }
                }
            }

            return result;
        }

        bool SceneObject::removeRoutine(ARoutine* routine, bool transferring)
        {
            bool result = false;

            if(routine)
            {
                for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
                {
                    ARoutine* iterRoutine = (*iter);

                    if(iterRoutine == routine)
                    {
                        m_Routines.erase(iter);

                        if(!transferring)
                        {
                            OcularScene->objectRemovedRoutine(routine);
                            routine->onDestruction();

                            delete routine;
                            routine = nullptr;
                        }

                        result = true;
                        break;
                    }
                }
            }

            return result;
        }

        void SceneObject::removeAllRoutines()
        {
            while(m_Routines.size() > 0)
            {
                ARoutine* routine = (*m_Routines.begin());
                m_Routines.erase(m_Routines.begin());

                if(routine)
                {
                    OcularScene->objectRemovedRoutine(routine);
                    routine->onDestruction();

                    delete routine;
                    routine = nullptr;
                }
            }
        }

        ARoutine* SceneObject::getRoutine(std::string const& name)
        {
            ARoutine* result = nullptr;

            for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
            {
                ARoutine* routine = (*iter);

                if(routine)
                {
                    if(routine->getName().compare(name) == 0)
                    {
                        result = routine;
                        break;
                    }
                }
            }

            return result;
        }

        std::vector<ARoutine*> const& SceneObject::getAllRoutines() const
        {
            return m_Routines;
        }

        uint32_t SceneObject::getNumRoutines() const
        {
            return m_Routines.size();
        }

        //----------------------------------------------------------------
        // Renderable Methods
        //----------------------------------------------------------------

        void SceneObject::setRenderable(ARenderable* renderable)
        {
            removeRenderable();
            m_Renderable = renderable;
        }

        void SceneObject::removeRenderable()
        {
            if(m_Renderable)
            {
                delete m_Renderable;
                m_Renderable = nullptr;
            }
        }

        ARenderable* SceneObject::getRenderable() const
        {
            return m_Renderable;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}