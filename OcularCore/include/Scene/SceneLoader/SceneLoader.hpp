/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_CORE_SCENE_LOADER__H__
#define __H__OCULAR_CORE_SCENE_LOADER__H__

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
        class Scene;

        /**
         * \class SceneLoader
         * \brief Handles the loading of .oscene files (Ocular Scene)
         *
         * Loads .oscene files as instances of Scene objects (not to be confused with SceneObject!).
         *
         * As a Scene is not a Resource, this loader is a standalone class separate from the standard
         * loader/saver pattern found within the Resource subsystem.
         *
         * Example Scene file:
         *
         *     <OcularScene>
         *         <SceneHeader>
         *             <SceneTreeType>
         *                 <Static>0</Static>
         *                 <Dynamic>0</Dynamic>
         *             </SceneTreeType>
         *         </SceneHeader>
         *         <SceneTree>
         *             <SceneObject>
         *             </SceneObject>
         *         </SceneTree>
         *     </OcularScene>
         *
         * SceneTreeType values for <Static> and <Dynamic> correspond to the enum values defined
         * in the SceneTreeType enum (Core/Scene/SceneTreeType.hpp)
         *
         * SceneObject parameters are detailed in the SceneObjectLoader class description.
         *
         * Even if they are empty, the <SceneHeader> and <SceneTree> nodes are required.
         */
        class SceneLoader
        {
        public:

            /**
             * Attempts to the load the Scene from the specified .oscene file.
             *
             * \param[in] file
             *
             * \return The new Scene object. Ownership of (and responsibility to destroy) this object is
             *         transferred to the method caller. May return NULL if failed to load.
             */
            static bool Load(Scene* scene, File const& file);

        protected:

            static bool ValidateFile(File const& file);

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