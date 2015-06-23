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
#ifndef __H__OCULAR_CORE_SCENE_MANAGER__H__
#define __H__OCULAR_CORE_SCENE_MANAGER__H__

#include "Scene.hpp"
#include "SceneObject.hpp"

#include <map>

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
        public:

            SceneManager();
            ~SceneManager();

            //------------------------------------------------------------------------------
            // SceneObject Methods

            /**
             * Creates and adds a new SceneObject to the active scene.
             * 
             * \param[in] name 
             * \return Pointer to the new object. This object is managed by the manager and should NOT be deallocated by the caller.
             */
            SceneObject* createObject(std::string const& name);

            /**
             * Creates and adds a new SceneObject to the active scene that is an
             * exact duplicate of the provided object.
             *
             * \param[in] object Object instance to duplicate.
             * \return Pointer to the new object. This object is managed by the manager and should NOT be deallocated by the caller.
             */
            SceneObject* duplicateObject(SceneObject* object);

            /**
             * Removes the specified SceneObject from the active scene.
             * \param[in] object SceneObject to remove.
             */
            void removeObject(SceneObject* object);

            /**
             * Removes the SceneObject with the specified name from the active scene.
             * If there are multiple SceneObjects with the given name, only the first
             * object will be removed.
             *
             * \param[in] name Name of the SceneObject to remove.
             */
            void removeObject(std::string const& name);

            /**
             * Removes the SceneObject with the specified UUID from the active scene.
             * \param[in] uuid UUID of the SceneObject to remove.
             */
            void removeObject(UUID const& uuid);

            /**
             * Finds and returns the SceneObject with the specified name.
             * If there are multiple SceneObjects with the given name, only the first
             * object will be removed.
             *
             * \param[in] name Name of the SceneObject to find.
             * \return Pointer to the SceneObject. Returns NULL if the specified object was not found.
             */
            SceneObject* findObject(std::string const& name);
            
            /**
             * Finds and returns the SceneObject with the specified UUID.
             *
             * \param[in] uuid UUID of the SceneObject to find.
             * \return Pointer to the SceneObject. Returns NULL if the specified object was not found.
             */
            SceneObject* findObject(UUID const& uuid);

            //------------------------------------------------------------------------------
            // Scene Methods

            /**
             * Loads the Scene with the specified name. If no matching scene is found,
             * then a new Scene is created. 
             *
             * If a Scene is already in memory, then that Scene is first unloaded.
             *
             * \param[in] name Name of the Scene to load.
             */
            void loadScene(std::string const& name);

        protected:

        private:

            std::map<std::string, SceneObject*> m_Objects;
            Scene* m_Scene;
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