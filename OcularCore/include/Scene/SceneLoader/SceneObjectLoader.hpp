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
#ifndef __H__OCULAR_CORE_SCENE_OBJECT_LOADER__H__
#define __H__OCULAR_CORE_SCENE_OBJECT_LOADER__H__

#include "FileIO/File.hpp"

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
        class SceneObject;
        struct Node_Internal;

        /**
         * \class SceneObjectLoader
         * \brief Handles the loading of .opre files (Ocular Predefined Scene Object)
         *
         * Loads .opre files as instances of SceneObjects.
         *
         * As a SceneObject is not a Resource, this loader is a standalone class separate from the standard
         * loader/saver pattern found within the Resource subsystem.
         */
        class SceneObjectLoader
        {
        public:

            /**
             * Attempts to the load the SceneObject from the specified .opre file.
             *
             * \param[in] file
             *
             * \return The new SceneObject. The object is already owned by the primary SceneManager (OcularScene),
             *         and as such should not be manually destroyed. Returns NULL if failed to load.
             */
            static SceneObject* Load(File const& file);

            /**
             * Attempts to the load the SceneObject from the provided node.
             * \note This is generally for internal use only by other loaders (ie SceneLoader)
             *
             * \param[in] node
             *
             * \return The new SceneObject. The object is already owned by the primary SceneManager (OcularScene),
             *         and as such should not be manually destroyed. Returns NULL if failed to load.
             */
            static SceneObject* Load(Node_Internal* node);

        protected:

            static bool IsValidFile(File const& file);

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