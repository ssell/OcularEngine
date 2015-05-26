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

#ifndef __H__OCULAR_CORE_SCENE_MANAGER__H__
#define __H__OCULAR_CORE_SCENE_MANAGER__H__

#include "Scene.hpp"
#include "SceneObject.hpp"

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
             * \return Pointer to the new object. This object is managed by the manager and should NOT be deallocated by the user.
             */
            SceneObject* AddObject(std::string const& name);

            void RemoveObject(SceneObject* object);
            void RemoveObject(std::string const& name);
            void RemoveObject(UUID const& uuid);

            SceneObject* FindObject(std::string const& name);
            SceneObject* FindObject(UUID const& uuid);

        protected:

        private:

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