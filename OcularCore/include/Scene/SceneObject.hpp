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

#include "Graphics/Shader/Uniform/UniformPerObject.hpp"

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
             * \param[in] name   Identifier name of the object. Note that the name does not need to be unique as
             *                   all objects are already uniquely identified via a UUID (see getUUID()).
             * \param[in] parent 
             */
            SceneObject(std::string const& name, SceneObject* parent = nullptr);

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
            Math::Transform& getTransform();

            /**
             * Sets whether this object is active or not. An inactive object 
             * will not have it's render or update methods called.
             *
             * \note The active state propagates to child SceneObjects.
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
             * \return If TRUE, then the object is being rendered.
             */
            bool isVisible() const;

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
             * \return TRUE if the object is being forced visible and being rendered irregardless of culling tests.
             */
            bool isForcedVisible() const;

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

            /**
             *
             */
            Graphics::UniformPerObject const& getUniformData();

            //------------------------------------------------------------
            // Movement and Rotation Methods
            //------------------------------------------------------------

            /**
             * Sets the position of the SceneObject.
             *
             * \param[in] x
             * \param[in] y
             * \param[in] z
             */
            void setPosition(float x, float y, float z);

            /**
             * Sets the position of the SceneObject.
             * \param[in]position
             */
            void setPosition(Math::Vector3f const& position);

            /**
             * \return The SceneObject's position
             */
            Math::Vector3f const& getPosition() const;

            /**
             * Translates the SceneObject along the given vector
             * \param[in] translation
             */
            void translate(Math::Vector3f const& translation, bool local = true);

            /**
             * Rotates the SceneObject along the given axis by the given angle
             *
             * \param[in] angle Angle to rotate in degrees
             * \param[in] axis  Axis to rotate around
             */
            void rotate(float angle, Math::Vector3f const& axis);

            /**
             * Sets the SceneObject's rotation
             * \param[in] rotation
             */
            void setRotation(Math::Quaternion const& rotation);

            /**
             * Resets the orientation of the object
             */
            void resetRotation();

            /**
             *
             */
            Math::Quaternion const& getRotation() const;

            /**
             *
             */
            void setTransform(Math::Transform const& transform);

            /**
             *
             */
            Math::Transform const& getTransform() const;

            //------------------------------------------------------------
            // Child Object Methods
            //------------------------------------------------------------

            /**
             * Sets the specified SceneOject as the parent of this SceneObject.
             * 
             * If the new parent is not null, then the cascading states of the parent
             * (active, forced visible, static/dynamic, etc.) are applied to this object.
             *
             * \param[in] parent New parent of this object. Pass NULL if no parent is desired.
             */
            void setParent(SceneObject* parent);

            /**
             * \return Parent of this SceneObject (NULL if no parent)
             */
            SceneObject* getParent() const;

            /**
             * Creates a new SceneObject with the specified name and adds it 
             * as a child of this SceneObject.
             *
             * Calling this method is functionally identical to:
             *
             *     OcularEngine.SceneManager()->createObject(name, thisObject);
             *
             * \param[in] name Name for the new object (does not have to be unique).
             * \return Pointer to the new object.
             */
            SceneObject* createChild(std::string const& name);

            /**
             * Adds the specified object as a child of this SceneObject and removes
             * it from it's previous parent.
             *
             * The object's parent will change, and it's state will be modified
             * to reflect it's new parent (active, forced visible, static/dynamic, etc.).
             *
             * \param[in] child
             */
            void addChild(SceneObject* child);

            /**
             * \param[in] name Name to search for.
             * \return Pointer to first discovered child with specified name (NULL if not found).
             */
            SceneObject* findChild(std::string const& name);

            /**
             * \param[in] uuid UUID to search for.
             * \return Pointer to child with matching UUID (NULL if not found).
             */
            SceneObject* findChild(UUID const& uuid);

            /**
             * Removes the first discovered child with the specified name.
             *
             * This does not delete the child object, but simply removes it
             * from this SceneObject. The removed object will continue to exist,
             * along with all of it's routines, renderables, and children.
             *
             * A pointer to the removed object is returned. If you desired to
             * fully destroy the object, then you must call:
             *
             *     OcularEngine.SceneManager()->removeObject(object);
             *
             * Note that the removed object will retain the state of it's old
             * parent (active, forced visible, static/dynamic, etc.). It's transform
             * will also be unmodified, but may appear to move as it is no longer
             * being based on the parent but now on the world.
             *
             * \param[in] name
             * \return Pointer to the removed object (NULL if no matching child was found).
             */
            SceneObject* removeChild(std::string const& name);

            /**
             * Removes the first discovered child with the specified UUID.
             *
             * This does not delete the child object, but simply removes it
             * from this SceneObject. The removed object will continue to exist,
             * along with all of it's routines, renderables, and children.
             *
             * A pointer to the removed object is returned. If you desired to
             * fully destroy the object, then you must call:
             *
             *    OcularScene->removeObject(object);
             *
             * Note that the removed object will retain the state of it's old
             * parent (active, forced visible, static/dynamic, etc.). It's transform
             * will also be unmodified, but may appear to move as it is no longer
             * being based on the parent but now on the world.
             *
             * \param[in] uuid
             * \return Pointer to the removed object (NULL if no matching child was found).
             */
            SceneObject* removeChild(UUID const& uuid);

            /**
             * Removes the first discovered child with the specified name.
             *
             * This does not delete the child object, but simply removes it
             * from this SceneObject. The removed object will continue to exist,
             * along with all of it's routines, renderables, and children.
             *
             * A pointer to the removed object is returned. If you desired to
             * fully destroy the object, then you must call:
             *
             *     OcularScene->removeObject(object);
             *
             * Note that the removed object will retain the state of it's old
             * parent (active, forced visible, static/dynamic, etc.). It's transform
             * will also be unmodified, but may appear to move as it is no longer
             * being based on the parent but now on the world.
             *
             * \param[in] object
             * \return Pointer to the removed object (NULL if no matching child was found).
             */
            SceneObject* removeChild(SceneObject const* object);

            /**
             * \return The number of child objects owned by this SceneObject.
             */
            uint32_t getNumChildren() const;

            /**
             * \return A vector containing pointers to all children owned by this SceneObject.
             */
            std::vector<SceneObject*> const& getAllChildren() const;

            //------------------------------------------------------------
            // Routine Methods
            //------------------------------------------------------------

            /**
             * Adds a new instance of the specified routine to the SceneObject.
             *
             * \param[in] name Name of the ARoutine implementation to add.
             * \return TRUE if the ARoutine implementation was successfully added. If it fails,
             *         then no matching implementation with that name was discovered.
             */
            bool addRoutine(std::string const& name);

            /**
             * Adds a new instance of a routine to the SceneObject.
             *
             * The object takes full ownership of the routine and frees it when
             * no longer in use.
             */
            template<class T> T* addRoutine() 
            { 
                T* t = new T();
                ARoutine* routine = dynamic_cast<ARoutine*>(t);

                if(routine)
                {
                    routine->setParent(this);
                    m_Routines.push_back(routine);
                    routine->onCreation();
                }
                else
                {
                    // T is not a routine
                    delete t;
                    t = nullptr;
                }

                return t;
            }

            /**
             * Removes an instance of the specified routine implementation from the SceneObject.
             * Will only remove the first instance of the implementation that it finds.
             *
             * \param[in] name Name of the ARoutine implementation to remove.
             * \return TRUE if the routine implementation was successfully removed. If it fails,
             *         then no matching implementation instance with that name was discovered.
             */
            bool removeRoutine(std::string const& name);

            /**
             * Removes the specified ARoutine instance from the SceneObject.
             *
             * \param[in] routine Routine instance to remove from the SceneObject.
             * \param[in] transferring If true, then this Routine is being transferred to another
             *                         SceneObject and should not be deleted.
             *
             * \return TRUE if the routine instance was successfully discovered and removed.
             *         If it fails, then no matching instance was discovered.
             */
            bool removeRoutine(ARoutine* routine, bool transferring = false);

            /**
             * Removes all routine instances that belong to this SceneObject.
             */
            void removeAllRoutines();

            /**
             * Retrieves the first discovered instance of the specified ARoutine implementation.
             *
             * \param[in] name 
             * \return The ARoutine instance or NULL if no matching routines were discovered.
             */
            ARoutine* getRoutine(std::string const& name);

            /**
             * Returns a collection of all routines that are owned by this SceneObject.
             */
            std::vector<ARoutine*> const& getAllRoutines() const;

            /**
             *
             */
            uint32_t getNumRoutines() const;

            //------------------------------------------------------------
            // Renderable Methods
            //------------------------------------------------------------

            /**
             *
             */
            void addRenderable(ARenderable* renderable);

            /**
             *
             */
            bool removeRenderable(ARenderable* renderable, bool transferring = false);

            /**
             *
             */
            bool removeRenderable(std::string const& name);

            /**
             *
             */
            void removeAllRenderables();

            /**
             *
             */
            ARenderable* getRenderable(std::string const& name);

            /**
             *
             */
            std::vector<ARenderable*> const& getAllRenderables() const;

            /**
             *
             */
            uint32_t getNumRenderables() const;

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

            Graphics::UniformPerObject m_UniformData;
            Math::Transform m_Transform;

        private:

            void removeChild(std::vector<SceneObject*>::iterator& child);

            //------------------------------------------------------------
            
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