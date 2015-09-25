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
            OcularScene->addObject(this);
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
            OcularScene->removeObject(m_UUID);  // Remove via UUID as it is faster
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------
        // General Misc Methods
        //----------------------------------------------------------------

        Math::Transform const& SceneObject::getTransform() const
        {
            return m_Transform;
        }

        void SceneObject::setActive(bool active)
        {
            if(m_IsActive != active)
            {
                m_IsActive = active;
                OcularEngine.SceneManager()->objectActiveChanged(this);

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
                OcularEngine.SceneManager()->objectVisibleChanged(this);

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
                OcularEngine.SceneManager()->objectStaticChanged(this);
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
                    OcularEngine.SceneManager()->objectParentChanged(this, oldParent);
                }
            }
        }

        SceneObject* SceneObject::getParent() const
        {
            return m_Parent;
        }

        SceneObject* SceneObject::createChild(std::string const& name)
        {
            return nullptr;
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

                OcularEngine.SceneManager()->objectParentChanged(child, oldParent);
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

        SceneObject* SceneObject::findChild(SceneObject const* object)
        {
            SceneObject* result = nullptr;

            for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
            {
                SceneObject* child = (*iter);

                if(child == object)
                {
                    result = child;
                    break;
                }
            }

            return result;
        }

        bool SceneObject::removeChild(std::string const& name)
        {
            bool result = false;

            // ...

            return result;
        }

        bool SceneObject::removeChild(UUID const& uuid)
        {
            bool result = false;

            // ...

            return result;
        }

        bool SceneObject::removeChild(SceneObject const* object)
        {
            bool result = false;

            // ...

            return result;
        }

        uint32_t SceneObject::getNumChildren() const
        {
            return 0;
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
            ARoutine* routine = nullptr;

            // ...

            if(routine)
            {
                OcularEngine.SceneManager()->objectAddedRoutine(routine);
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

                        OcularEngine.SceneManager()->objectRemovedRoutine(routine);
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

        bool SceneObject::removeRoutine(ARoutine* routine)
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

                        OcularEngine.SceneManager()->objectRemovedRoutine(routine);
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

        void SceneObject::removeAllRoutines()
        {
            while(m_Routines.size() > 0)
            {
                ARoutine* routine = (*m_Routines.begin());
                m_Routines.erase(m_Routines.begin());

                if(routine)
                {
                    OcularEngine.SceneManager()->objectRemovedRoutine(routine);
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

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}