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

#ifndef __H__OCULAR_CORE_SCENE_NODE__H__
#define __H__OCULAR_CORE_SCENE_NODE__H__

#include "Object.hpp"
#include "Math/Transform.hpp"

#include <memory>
#include <list>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        class SceneTree;

        /**
         * \class SceneNode
         */
        class SceneNode : public Object
        {
            friend class SceneTree;
            friend class SceneNode;

        public:

            /**
             * \param[in] name     Name of the scene node. This should be descriptive and unique.
             * \param[in] position Initial local position of the scene node.
             * \param[in] rotation Initial local rotation of the scene node.
             * \param[in] scale    Initial local scale of the scene node.
             * \param[in] parent   Parent node of this scene node.
             */
            SceneNode(std::string const& name, Math::Vector3f const& position = Math::Vector3f(), Math::Quaternion const& rotation = Math::Quaternion(), Math::Vector3f const& scale = Math::Vector3f(1.0f, 1.0f, 1.0f), SceneNode* parent = nullptr);
            ~SceneNode();

            //------------------------------------------------------------
            // Node Get/Setters

            SceneNode* getParent() const;
            
            uint32_t   addChild(std::shared_ptr<SceneNode> const& child);
            SceneNode* addChild(std::string const& name, Math::Vector3f const& position = Math::Vector3f(), Math::Quaternion const& rotation = Math::Quaternion(), Math::Vector3f const& scale = Math::Vector3f(1.0f, 1.0f, 1.0f));

            SceneNode* getChild(UUID const& uuid) const;
            SceneNode* getChild(std::string const& name) const;
            SceneNode* getChild(uint32_t const index) const;

            void getChildren(std::list<SceneNode*>& children) const;

            uint32_t getNumChildren() const;

            //------------------------------------------------------------
            // Active and Visibility

            /**
             * Returns whether this node is active or not. 
             * A node that is active will have it's update methods called.
             *
             * Whether a node is active or not is determined by the scene tree it belongs to.
             */
            bool getIsActive() const;

            /**
             * Returns whether this node is visible or not.
             * A node that is visible will have it's render methods called.
             *
             * Whether a node is active or not is determined by the scene tree it belongs to.
             */
            bool getIsVisible() const;

            /**
             * Set whether this node should always be forced active.
             *
             * If forced active, this node's update methods will always be called irregardless 
             * of if the scene tree determined it active or not.
             *
             * \param[in] force
             */
            void setForcedActive(bool force);

            /**
             * Set whether this node should always be forced visible.
             *
             * If forced visible, this node's render methods will always be called irregardless 
             * of if the scene tree determined it visbile or not.
             *
             * \param[in] force
             */
            void setForcedVisible(bool force);

            /**
             * Set whether this node should always be forced inactive.
             *
             * If forced inactive, this node's update methods will never be called irregardless 
             * of if the scene tree determined it active or not.
             *
             * \param[in] force
             */
            void setForcedInactive(bool force);

            /**
             * Set whether this node should always be forced invisible.
             *
             * If forced invisible, this node's render methods will never be called irregardless 
             * of if the scene tree determined it visbile or not.
             *
             * \param[in] force
             */
            void setForcedInvisible(bool force);

            //------------------------------------------------------------
            // Misc. Options

            void setInheritsPosition(bool inherit);
            void setInheritsRotation(bool inherit);
            void setInheritsScale(bool inherit);

            bool getInheritsPosition() const;
            bool getInheritsRotation() const;
            bool getInheritsScale() const;

            //------------------------------------------------------------

            Math::Transform transform;

        protected:

            bool setIsActive(bool active);
            bool setIsVisible(bool visible);

            void setParent(SceneNode* parent);

            SceneNode* previous;
            SceneNode* next;

        private:

            bool m_IsActive;
            bool m_IsVisible;
            bool m_ForcedActive;
            bool m_ForcedVisible;
            bool m_ForcedInactive;
            bool m_ForcedInvisible;

            bool m_InheritsPosition;
            bool m_InheritsRotation;
            bool m_InheritsScale;

            SceneNode* m_Parent;
            std::list<std::shared_ptr<SceneNode>> m_Children;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif