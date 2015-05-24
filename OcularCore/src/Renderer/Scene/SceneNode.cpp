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

#include "Renderer/Scene/SceneNode.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneNode::SceneNode(std::string const& name, Math::Vector3f const& position, Math::Quaternion const& rotation, Math::Vector3f const& scale, SceneNode* parent)
        {
            transform.setPosition(position);
            transform.setRotation(rotation);
            transform.setScale(scale);

            m_Parent = parent;

            m_IsActive        = false;
            m_IsVisible       = false;
            m_ForcedActive    = false;
            m_ForcedVisible   = false;
            m_ForcedInactive  = false;
            m_ForcedInvisible = false;

            m_InheritsPosition = true;
            m_InheritsRotation = true;
            m_InheritsScale    = true;

            previous = nullptr;
            next = nullptr;
        }

        SceneNode::~SceneNode()
        {
            m_Parent = nullptr;

            for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
            {
                (*iter) = nullptr;
            }

            m_Children.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        SceneNode* SceneNode::getParent() const
        {
            return m_Parent;
        }

        uint32_t SceneNode::addChild(std::shared_ptr<SceneNode> const& child)
        {
            return 0;
        }

        SceneNode* SceneNode::addChild(std::string const& name, Math::Vector3f const& position, Math::Quaternion const& rotation, Math::Vector3f const& scale)
        {
            return nullptr;
        }

        SceneNode* SceneNode::getChild(UUID const& uuid) const
        {
            return nullptr;
        }

        SceneNode* SceneNode::getChild(std::string const& name) const
        {
            return nullptr;
        }

        SceneNode* SceneNode::getChild(uint32_t const index) const
        {
            return nullptr;
        }

        void SceneNode::getChildren(std::list<SceneNode*>& children) const
        {
        
        }

        uint32_t SceneNode::getNumChildren() const
        {
            return static_cast<uint32_t>(m_Children.size());
        }

        bool SceneNode::getIsActive() const
        {
            return m_IsActive;
        }

        bool SceneNode::getIsVisible() const
        {
            return m_IsVisible;
        }

        void SceneNode::setForcedActive(bool const force)
        {
            m_ForcedActive   = force;
            m_ForcedInactive = !force;
        }

        void SceneNode::setForcedVisible(bool const force)
        {
            m_ForcedVisible   = force;
            m_ForcedInvisible = !force;
        }

        void SceneNode::setForcedInactive(bool const force)
        {
            m_ForcedInactive = force;
            m_ForcedActive   = !force;
        }

        void SceneNode::setForcedInvisible(bool const force)
        {
            m_ForcedInvisible = force;
            m_ForcedVisible   = !force;
        }

        void SceneNode::setInheritsPosition(bool inherit)
        {
            m_InheritsPosition = inherit;
        }

        void SceneNode::setInheritsRotation(bool inherit)
        {
            m_InheritsRotation = inherit;
        }

        void SceneNode::setInheritsScale(bool inherit)
        {
            m_InheritsScale = inherit;
        }

        bool SceneNode::getInheritsPosition() const
        {
            return m_InheritsPosition;
        }

        bool SceneNode::getInheritsRotation() const
        {
            return m_InheritsRotation;
        }

        bool SceneNode::getInheritsScale() const
        {
            return m_InheritsScale;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}