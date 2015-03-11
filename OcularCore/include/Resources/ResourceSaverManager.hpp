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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_SAVER_MANAGER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_SAVER_MANAGER__H__

#include "ResourceSaver.hpp"

#include <memory>
#include <string>
#include <unordered_map>

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
         * \class ResourceSaverManager
         */
        class ResourceSaverManager
        {
        public:

            ResourceSaverManager();
            ~ResourceSaverManager();

            /**
             * Registers a new resource saver with the manager. Note this this method should generally
             * never be directly called, instead a ReasourceSaverRegistrar should be used instead.
             *
             * If the manager already has a ResourceSaver registered with the supported extension,
             * then the specified saver will not be used.
             *
             * \param saver The ResourceSaver to register with the manager.
             */
            void registerResourceSaver(std::shared_ptr<AResourceSaver> saver);

            /**
             *
             * 
             * \param[in] resource Resource object to be saved to disk
             * \param[in] file     A valid resource file
             */
            bool saveResource(Resource* resource, File const& file);

            /**
             * \return The total number of registered ResourceSaver
             */
            unsigned getNumberOfResourceSavers() const;

            /**
             * \return TRUE if the specified extension has an associated ResourceSaver.
             */
            bool isExtensionSupported(std::string const& extension) const;

        protected:

        private:

            std::unordered_map<std::string, std::shared_ptr<AResourceSaver>> m_ResourceSaverMap;
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