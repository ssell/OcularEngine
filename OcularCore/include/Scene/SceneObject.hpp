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

#pragma once
#ifndef __H__OCULAR_CORE_SCENE_OBJECT__H__
#define __H__OCULAR_CORE_SCENE_OBJECT__H__

#include "Object.hpp"
#include "Math/Transform.hpp"
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"

#include <string>
#include <map>
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
        class SceneManager;
        class ARoutine;

        /**
         * \class SceneObject
         *
         * A SceneObject represents the instance of an arbitrary object in a Scene.
         * This can range from a static scenery object, such as a rock, to a particle effect,
         * to a physics volume, to a multifaceted actor.
         *
         * A single SceneObject can have multiple child objects attached to it. This can be 
         * thought of as similar to a car. A parent chassis object could have child axle objects
         * which in turn have child wheel objects. Each level down inherits the parent's transform
         * and active/visible status (unless otherwise overridden).
         *
         * Additionally, there are Routine and Renderable instances that may be attached to
         * a SceneObject. A Routine represents the logic behind an object while the Renderable
         * is any part of the object that is to be rendered onto the screen.
         *
         *
         */
        class SceneObject : public Object
        {
            friend class SceneManager;

        public:
            
            SceneObject();
            ~SceneObject();

            //------------------------------------------------------------
            // General Misc. Methods
            //------------------------------------------------------------

            /**
             * Sets whether this object is visible or not. Note that this method
             * is called every frame by the scene, and thus manually calling it
             * will have little or no effect.
             *
             * If you wish to force an object to always be rendered, then you
             * should instead call setForcedVisible.
             *
             * \param[in] visible
             */
            void setVisible(bool visible);

            /**
             * Sets whether this object is forced visible. If an object is forced
             * visible, then it's renderables will always be rendered irregardless
             * of whether or not it is in view or passes any culling tests.
             *
             * \note This flag has a cascading effect. Any children of a forced visible
             *       object will automatically be forced visible themselves.
             *
             * \param[in] forced
             */
            void setForcedVisible(bool forced);

            /**
             * \return If TRUE, then the object is being rendered.
             */
            bool isVisible() const;

            /**
             * Sets whether this object is static or not. If an object is static,
             * then no transformations (translation, rotation, scaling) will have
             * any effect on it.
             *
             * This is useful for objects such as terrain pieces that once created,
             * will never move. By setting to static, it allows for numerous rendering
             * optimizations to take place.
             *
             * \note This flag has a cascading effect. Any children of a static object
             *       will automatically be static themselves.
             *
             * \param[in] isStatic
             */
            void setStatic(bool isStatic);

            /**
             * \return TRUE if the object (or a parent) is marked as static.
             */
            bool isStatic() const;

            /**
             * Sets whether this object should persist inbetween scenes.
             *
             * Typically, all active objects are unloaded along with the currently
             * active scene. However, if an object is marked as persistent, then
             * it will not be unloaded with the scene and will automatically added
             * to the new scene.
             *
             * \param[in] persists
             */
            void setPersists(bool persists);

            /**
             * \return TRUE if this object persists between scenes.
             */
            bool doesPersist() const;

            //------------------------------------------------------------
            // Child Object Methods
            //------------------------------------------------------------

            SceneObject* createChild(std::string const& name);
            
            SceneObject* findChild(std::string const& name);
            SceneObject* findChild(UUID const& uuid);
            SceneObject* findChild(uint32_t const index);

            void removeChild(std::string const& name);
            void removeChild(UUID const& uuid);
            void removeChild(uint32_t const index);

            uint32_t getNumChildren() const;

            //------------------------------------------------------------
            // Routine Methods
            //------------------------------------------------------------

            void addRoutine(std::string const& name);

            ARoutine* getRoutine(std::string const& name);
            void getAllRoutines(std::string const& name, std::list<ARoutine*>& routines);

            //------------------------------------------------------------
            // Public Members
            //------------------------------------------------------------

            Math::Transform transform;

			Math::BoundsSphere boundsSphere;
			Math::BoundsAABB   boundsAABB;
			Math::BoundsOBB    boundsOBB;

        protected::

        private:

            std::string m_Name;        ///< Unique name for this SceneObject instance.
            
            bool m_IsStatic;           ///< Boolean if this object is static. If static, no movement or rotation calls will have any affect. Default: false.
            bool m_IsActive;           ///< If active, an object's Routines will be invoked.
            bool m_IsVisible;          ///< If visible, an object's Renderables will be invoked.
            bool m_ForcedVisible;      ///< If true, the object will be forced visible and the Renderable will always be invoked irregardless of any frustum, cull, etc. tests. Default: false.
            bool m_InheritsPosition;   ///< If true, the object's local position will inherit and be based off of any parent object. Default: true.
            bool m_InheritsRotation;   ///< If true, the object's local rotation will inherit and be based off of any parent object. Default: true.
            bool m_InheritsScale;      ///< If true, the objects' local scale will inherit and be based off of any parent object. Default: true.
            bool m_Persists;           ///< If true, this object (and children) will persist inbetween scenes. When a new scene is created, it will automatically be added to it.

            uint32_t m_Layer;          ///< The render layer this object is part of.
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