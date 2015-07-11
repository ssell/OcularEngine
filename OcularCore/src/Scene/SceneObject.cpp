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

#include "Scene/SceneObject.hpp"
#include "Math/Transform.hpp"
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneObject::SceneObject()
            : Object("SceneObject")
        {
        
        }

        SceneObject::~SceneObject()
        {
        
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

        Math::BoundsSphere const& SceneObject::getBoundsSphere() const
        {
            return m_BoundsSphere;
        }

        Math::BoundsAABB const& SceneObject::getBoundsAABB() const
        {
            return m_BoundsAABB;
        }

        Math::BoundsOBB const& SceneObject::getBoundsOBB() const
        {
            return m_BoundsOBB;
        }

        void SceneObject::setVisible(bool visible)
        {
            m_IsVisible = visible;
        }

        void SceneObject::setForcedVisible(bool forced)
        {
            m_ForcedVisible = forced;
        }

        bool SceneObject::isVisible() const
        {
            return m_IsVisible;
        }

        void SceneObject::setStatic(bool isStatic)
        {
            m_IsStatic = isStatic;
        }

        bool SceneObject::isStatic() const
        {
            return m_IsStatic;
        }

        void SceneObject::setPersists(bool persists)
        {
            m_Persists = persists;
        }

        bool SceneObject::doesPersist() const
        {
            return m_Persists;
        }

        //----------------------------------------------------------------
        // Child Object Methods
        //----------------------------------------------------------------

        SceneObject* SceneObject::createChild(std::string const& name)
        {

        }

        SceneObject* SceneObject::findChild(std::string const& name)
        {

        }

        SceneObject* SceneObject::findChild(UUID const& uuid)
        {

        }

        SceneObject* SceneObject::findChild(uint32_t const index)
        {

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

        }

        //----------------------------------------------------------------
        // Routine Methods
        //----------------------------------------------------------------

        void SceneObject::addRoutine(std::string const& name)
        {

        }

        ARoutine* SceneObject::getRoutine(std::string const& name)
        {

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