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
#include <vector>

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
        class ARenderable;

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
         * When a SceneObject is created, it is automatically added to the current SceneManager which
         * then takes ownership of the object. This means it will be automatically destroyed when
         * the current Scene is unloaded or when the SceneManager is destroyed in the case of an
         * object marked as persistent.
         *
         * There are two options when creating/destroying a standalone object:
         *
         *     SceneObject* object = new SceneObject();
         *     delete object;
         *
         *     SceneObject* object = OcularScene->createObject();
         *     OcularScene->destroyObject();
         *
         * In either case, the SceneManager owns the object and handles adding it to the Scene,
         * invoking the Routines and Renderables, intersection testing, etc.
         */
        class SceneObject : public Object
        {
            friend class SceneManager;

        public:
            
            /**
             * Creates a new SceneObject with the specified name.
             *
             * \note The object is automatically added to the Ocular SceneManager, and the SceneManager
             *       takes ownership of it. If a completely unmanaged object is required see ... (not yet available)
             *
             * \param[in] name Identifier name of the object. Note that the name does not need to be unique as
             *                 all objects are already uniquely identified via a UUID (see getUUID()).
             */
            SceneObject(std::string const& name);

            /**
             * Creates a new SceneObject with the default name of "SceneObject".
             *
             * \note The object is automatically added to the Ocular SceneManager, and the SceneManager
             *       takes ownership of it. If a completely unmanaged object is required see ... (not yet available)
             */
            SceneObject();

            ~SceneObject();

            //------------------------------------------------------------
            // General Misc. Methods
            //------------------------------------------------------------

            /**
             * Returns the current transform of this object.
             */
            Math::Transform const& getTransform() const;

            /**
             * Sets whether this object is active or not. An inactive object 
             * will not have it's render or update methods called.
             *
             * \param[in] active (default TRUE)
             */
            void setActive(bool active);

            /**
             * Returns if the object is active.
             */
            bool isActive() const;

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
            void setPersistent(bool persists);

            /**
             * \return TRUE if this object persists between scenes.
             */
            bool isPersistent() const;

            //------------------------------------------------------------
            // Child Object Methods
            //------------------------------------------------------------

            void setParent(SceneObject* parent);
            SceneObject* getParent() const;

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

            void removeRoutine(std::string const& name);
            void removeRoutine(ARoutine* routine);
            void removeAllRoutines();

            ARoutine* getRoutine(std::string const& name);
            std::vector<ARoutine*> const& getAllRoutines() const;

            //------------------------------------------------------------
            // Public Members
            //------------------------------------------------------------

			Math::BoundsSphere boundsSphere;
			Math::BoundsAABB   boundsAABB;
			Math::BoundsOBB    boundsOBB;

        protected:

            SceneObject* m_Parent;

            //------------------------------------------------------------
            // General Characteristics

            std::string m_Name;        ///< Unique name for this SceneObject instance.
            uint32_t m_Layer;          ///< The render layer this object is part of.

            //------------------------------------------------------------
            // Physical Characteristics

            Math::Transform m_Transform;

        private:
            
            bool m_IsStatic;           ///< Boolean if this object is static. If static, no movement or rotation calls will have any affect. Determines which SceneTree it will reside in. Default: false.
            bool m_IsActive;           ///< If active, an object's Routines will be invoked. Default: true.
            bool m_IsVisible;          ///< If visible, an object's Renderables will be invoked. Default: false.
            bool m_ForcedVisible;      ///< If true, the object will be forced visible and the Renderable will always be invoked irregardless of any frustum, cull, etc. tests. Default: false.
            bool m_Persists;           ///< If true, this object (and children) will persist inbetween scenes. When a new scene is created, it will automatically be added to it.

            std::vector<ARoutine*> m_Routines;
            std::vector<ARenderable*> m_Renderables;
            std::vector<SceneObject*> m_Children;
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