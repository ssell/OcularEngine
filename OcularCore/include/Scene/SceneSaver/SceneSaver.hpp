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
#ifndef __H__OCULAR_CORE_SCENE_SAVER__H__
#define __H__OCULAR_CORE_SCENE_SAVER__H__

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
         * \class SceneSaver
         * \brief Handles the saving of .oscene files (Ocular Scene)
         *
         * Saves SceneObjects as .oscene files.
         *
         * As a Scene is not a Resource, this saver is a standalone class separate from the standard
         * loader/saver pattern found within the Resource subsystem.
         */
        class SceneSaver
        {
        public:

            /**
             * Attempts to save the provided Scene object to the specified .oscene file.
             *
             * \param[in] scene
             * \param[in] file
             *
             * \return TRUE if saved successfully, else FALSE.
             */
            static bool save(Scene const* scene, File const& file);

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