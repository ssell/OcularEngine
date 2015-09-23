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

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneObject::SceneObject(std::string const& name)
            : Object(name),
              m_IsStatic(false),
              m_IsActive(true),
              m_IsVisible(false),
              m_ForcedVisible(false),
              m_Persists(false)
        {
            OcularScene->addObject(this);
        }

        SceneObject::SceneObject()
            : Object("SceneObject"),
              m_IsStatic(false),
              m_IsActive(true),
              m_IsVisible(false),
              m_ForcedVisible(false),
              m_Persists(false)
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

        void SceneObject::SetActive(bool active)
        {
            if(m_IsActive != active)
            {
                m_IsActive = active;
                OcularEngine.SceneManager()->objectActiveChanged(this);
            }
        }

        bool SceneObject::IsActive() const
        {
            return m_IsActive;
        }

        void SceneObject::setVisible(bool visible)
        {
            m_IsVisible = visible;
        }

        void SceneObject::setForcedVisible(bool forced)
        {
            if(m_ForcedVisible != forced)
            {
                m_ForcedVisible = forced;
                OcularEngine.SceneManager()->objectVisibleChanged(this);
            }
        }

        bool SceneObject::isVisible() const
        {
            return m_IsVisible;
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
            // Have to ensure the scene tree is updated with all the changes that 
            // could cascade from this action...

            m_Parent = parent;
        }

        SceneObject* SceneObject::getParent() const
        {
            return m_Parent;
        }

        SceneObject* SceneObject::createChild(std::string const& name)
        {
            return nullptr;
        }

        SceneObject* SceneObject::findChild(std::string const& name)
        {
            return nullptr;
        }

        SceneObject* SceneObject::findChild(UUID const& uuid)
        {
            return nullptr;
        }

        SceneObject* SceneObject::findChild(uint32_t const index)
        {
            return nullptr;
        }

        void SceneObject::removeChild(std::string const& name)
        {

        }

        void SceneObject::removeChild(UUID const& uuid)
        {

        }

        void SceneObject::removeChild(uint32_t const index)
        {

        }

        uint32_t SceneObject::getNumChildren() const
        {
            return 0;
        }

        //----------------------------------------------------------------
        // Routine Methods
        //----------------------------------------------------------------

        void SceneObject::addRoutine(std::string const& name)
        {

        }

        ARoutine* SceneObject::getRoutine(std::string const& name)
        {
            return nullptr;
        }

        void getAllRoutines(std::string const& name, std::list<ARoutine*>& routines)
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