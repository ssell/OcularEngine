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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_LOADER_MANAGER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_LOADER_MANAGER__H__

#include "ResourceLoader.hpp"

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
         * \class ResourceLoaderManager
         */
        class ResourceLoaderManager
        {
        public:

            ResourceLoaderManager();
            ~ResourceLoaderManager();

            /**
             *
             */
            void registerResourceLoader(std::shared_ptr<AResourceLoader> loader);
            
            /**
             * 
             */
            void loadResource(Resource* resource, File const& file);

            /**
             *
             */
            unsigned getNumberOfResourceLoaders() const;

            /**
             *
             */
            bool isExtensionSupported(std::string const& extension) const;

        protected:

        private:

            std::unordered_map<std::string, std::shared_ptr<AResourceLoader>> m_ResourceLoaderMap;
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