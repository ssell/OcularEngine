/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
         * \brief Handles the saving of .opre files (Ocular Predefined Scene Object)
         *
         * Saves SceneObjects as .opre files.
         *
         * As a SceneObject is not a Resource, this saver is a standalone class separate from the standard
         * loader/saver pattern found within the Resource subsystem.
         */
        class SceneObjectSaver
        {
        public:

            /**
             * Attempts to the load the SceneObject from the specified .opre file.
             *
             * \param[in] object
             * \param[in] file 
             *
             * \return TRUE if saved successfully, else FALSE.
             */
            static bool Save(SceneObject* object, File const& file);

            /**
             * Attempts to the save the SceneObject to the provided node.
             * \note This is generally for internal use only by other savers (ie SceneSaver)
             *
             * \param[in] object
             * \param[in] node
             *
             * \return TRUE if saved successfully, else FALSE.
             */
            static bool Save(SceneObject* object, Node_Internal* node);

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