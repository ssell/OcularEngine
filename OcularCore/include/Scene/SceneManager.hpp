/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_CORE_SCENE_MANAGER__H__
#define __H__OCULAR_CORE_SCENE_MANAGER__H__

#include "Scene.hpp"
#include "SceneObject.hpp"
#include "SceneTreeType.hpp"
#include "Renderer/Renderer.hpp"
#include "ComponentFactory.hpp"
#include "FileIO/File.hpp"
#include "Math/Geometry/Frustum.hpp"

#include <unordered_map>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    // Forward Declaration

    class Engine;

    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class SceneManager
         * 
         * The SceneManager is the owner of all Scenes and SceneObjects. It responsible
         * for properly loading and unloading of the objects and providing access to them.
         *
         * Only a single Scene may be active at a time, and any SceneObjects that are associated
         * with it will be unloaded with it. Any SceneObjects that are created dynamically will
         * be automatically added and associated with the current Scene.
         *
         * In special circumstances, a SceneObject may be allowed to persist inbetween scenes.
         * It is not recommended to apply this modifier often, but it may be useful in special
         * circumstances. Any SceneObject that persists will be automatically added to a newly
         * loaded scene.
         */
        class SceneManager
        {
            friend class Engine;
            friend class SceneObject;
            friend class ARoutine;

        public:

            SceneManager();
            ~SceneManager();

            //------------------------------------------------------------------------------
            // SceneObject Methods

            /**
             * Creates and adds a new empty SceneObject to the active scene.
             * 
             * \param[in] name   Non-unique display name for the object
             * \param[in] parent Optional parent SceneObject. NULL if no parent.
             *
             * \return Pointer to the new object. This object is managed by the manager and should NOT be deallocated by the caller.
             */
            SceneObject* createObject(std::string const& name = "Unnamed", SceneObject* parent = nullptr);

            /**
             *
             */
            template<class T>
            T* createObject(std::string const& name = "Unnamed", SceneObject* parent = nullptr)
            {
                T* result = new T(name, parent);
                addObject(result);

                return result;
            }

            /**
             * Attempts to create an object of the given type.
             * 
             * This is an alternative to createObject<T> when the explicit type T is not directly available.
             *
             * \param[in] type   A valid SceneObject type name (ie "SceneObject", "Camera", etc.)
             * \param[in] name   Non-unique display name for the object
             * \param[in] parent Optional parent SceneObject. NULL if no parent.
             *
             * \return The newly created SceneObject. May return false if the provided type is invalid (not found registered with 
             *         the SceneObject factory (SceneManager::getSceneObjectFactory))
             */
            SceneObject* createObjectOfType(std::string const& type, std::string const& name = "Unnamed", SceneObject* parent = nullptr);

            /**
             * Creates and adds a new SceneObject to the active scene that is an exact duplicate of the provided object.
             * The new SceneObject is added as a child to the parent of the specified SceneObject (they are siblings).
             *
             * \param[in] object Object instance to duplicate.
             * \return Pointer to the new object. This object is managed by the manager and should NOT be deallocated by the caller.
             */
            SceneObject* duplicateObject(SceneObject const* object);

            /**
             * Destroys the specified SceneObject and removes it completely from the SceneManager/Scene/etc.
             *
             * This will remove the object from the scene and parent. Will also destroy (delete) the object
             * and any children.
             *
             * \note Removing by pointer is less efficient than by UUID.
             * \param[in] object SceneObject to remove.
             */
            void destroyObject(SceneObject* object);

            /**
             * Destroys the specified SceneObject and removes it completely from the SceneManager/Scene/etc.
             *
             * This will remove the object from the scene and parent. Will also destroy (delete) the object
             * and any children.
             *
             * By default, if there are multiple SceneObjects with the given name, only the first
             * object will be removed.
             *
             * \param[in] name Name of the SceneObject to remove.
             * \param[in] bool If there are multiple SceneObjects with the given name, and this parameter is set TRUE, then
             *                 all objects with the matching name will be removed.
             */
            void destroyObject(std::string const& name, bool removeAll = false);

            /**
             * Destroys the specified SceneObject and removes it completely from the SceneManager/Scene/etc.
             *
             * This will remove the object from the scene and parent. Will also destroy (delete) the object
             * and any children.
             *
             * \note Removing by name is less efficient than by UUID.
             * \param[in] uuid UUID of the SceneObject to remove.
             */
            void destroyObject(UUID const& uuid);

            /**
             * Finds and returns the SceneObject with the specified name.
             *
             * If there are multiple SceneObjects with the given name, only the first
             * object will be removed. If you need all objects with a given name, then
             * use the findObjects() method.
             *
             * \note Searching by name is less efficient than by UUID.
             *
             * \param[in] name Name of the SceneObject to find.
             * \return Pointer to the SceneObject. Returns NULL if the specified object was not found.
             */
            SceneObject* findObject(std::string const& name) const;

            /**
             * Finds and returns all SceneObjects with names that match the specified one.
             *
             * \param[in]  name    Name of the SceneObject(s) to find.
             * \param[out] objects Collection of all SceneObjects whose names match the provided.
             */
            void findObjects(std::string const& name, std::vector<SceneObject*>& objects) const;
            
            /**
             * Finds and returns the SceneObject with the specified UUID.
             *
             * \param[in] uuid UUID of the SceneObject to find.
             * \return Pointer to the SceneObject. Returns NULL if the specified object was not found.
             */
            SceneObject* findObject(UUID const& uuid) const;

            /**
             * Finds and returns a container of all top-level SceneObjects (object with no parents).
             */
            void findTopObjects(std::vector<SceneObject*>& object) const;

            /**
             * Updates the UUID of a SceneObject.
             * \note Typically for internal engine use only
             */
            void updateUUID(UUID const& uuid);

            /**
             * Returns a collection of all SceneObjects visible to the specified view frustum (see Camera::getFrustum).
             *
             * The returned collection is a flat list meaning all visible SceneObjects are returned, not just
             * top-level parents. Thus there is no need to check child visibility, as visible children will also be
             * stored in the returned collection.
             *
             * \param[out] objects All visible SceneObjects
             * \param[in]  frustum View frustum to perform frustum-culling against
             */
            void getVisibleSceneObjects(std::vector<SceneObject*>& objects, Math::Frustum const& frustum);

            //------------------------------------------------------------------------------
            // Scene Methods

            /**
             * Creates a new Scene with the specified name.
             *
             * Note that if a Scene is already active, that Scene will be first unloaded.
             * If any changes to that Scene need to be saved prior to unloading, then the
             * saveScene method should be called prior to createScene.
             *
             * \param[in] name
             * \param[in] staticType  Type of SceneTree to use for static objects (default CPU BVH)
             * \param[in] dynamicType Type of SceneTree to use for dynamic objects (default CPU BVH)
             */
            void createScene(std::string const& name, SceneTreeType staticType = SceneTreeType::BoundingVolumeHierarchyCPU, SceneTreeType dynamicType = SceneTreeType::BoundingVolumeHierarchyCPU);

            /**
             * Attempts to load the Scene from the specified .oscene file.
             *
             * If the specified Scene can not be loaded, then an empty default Scene
             * will be created instead.
             *
             * Note that if a Scene is already active, that Scene will be first unloaded.
             * If any changes to that Scene need to be saved prior to unloading, then the
             * saveScene method should be called prior to loadScene.
             *
             * \param[in] file
             * \return TRUE if loaded successfully
             */
            bool loadScene(File const& file);

            /**
             * Attempts to save the Scene to the specified .oscene file.
             *
             * \param[in] file
             * \return TRUE if saved successfully
             */
            bool saveScene(File const& file);

            /**
             * \return TRUE if there is an active Scene running.
             */
            bool isSceneActive() const;

            /**
             *
             */
            ComponentFactory<ARoutine>& getRoutineFactory();

            /**
             *
             */
            ComponentFactory<ARenderable>& getRenderableFactory();

            /**
             *
             */
            ComponentFactory<SceneObject>& getSceneObjectFactory();

            /**
             *
             */
            ComponentFactory<Renderer>& getRendererFactory();

        protected:

            void loadPersistentObjects();

            /**
             * Adds the provided SceneObject to the current Scene.
             * \param[in] object
             */
            void addObject(SceneObject* object, SceneObject* parent = nullptr);

            /**
             *
             */
            void unloadScene();

            /**
             * Tells the current Scene to update and restructure it's SceneTrees. Also calls the various update methods
             * for all active SceneObjects.
             */
            void update();

            /**
             * Tells the current Scene to retrieve all visible SceneObjects and perform envoke their render methods.
             */
            void render();

            /**
             * Called when a SceneObject's SetActive method is envoked.
             * \param[in] object
             */
            void objectActiveChanged(SceneObject* object);

            /**
             * Called when a SceneObject's SetForcedVisible method is envoked.
             * \param[in] object
             */
            void objectVisibleChanged(SceneObject* object);

            /**
             * Called when a SceneObject's SetStatic method is envoked.
             * \param[in] object
             */
            void objectStaticChanged(SceneObject* object);

            /**
             * Called when a SceneObject adds a new ARoutine instance.
             * \param[in] routine
             */
            void objectAddedRoutine(ARoutine* routine);

            /**
             * Called when a SceneObject removes a ARoutine instance.
             * \param[in] routine
             */
            void objectRemovedRoutine(ARoutine* routine);

            /**
             * Called when an object's parent is changed.
             * 
             * \param[in] object    The object that has a new parent.
             * \param[in] oldParent The old parent of the object.
             */
            void objectParentChanged(SceneObject* object, SceneObject* oldParent);

        private:

            void deleteObject(SceneObject* object);

            std::unordered_map<std::string, SceneObject*> m_Objects;    ///< Key is the string representation of the object UUID
            Scene* m_Scene;

            ComponentFactory<ARoutine>    m_RoutineFactory;
            ComponentFactory<ARenderable> m_RenderableFactory;
            ComponentFactory<SceneObject> m_SceneObjectFactory;
            ComponentFactory<Renderer>    m_RendererFactory;
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