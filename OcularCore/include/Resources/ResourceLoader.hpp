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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_LOADER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_LOADER__H__

#include "Resource.hpp"

#include <memory>
#include <string>

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
         * \class AResourceLoader
         *
         * Base interface for all resource loaders.
         *
         * A resource loader is responsible for reading and loading a 
         * specific type of resource file (based on extension) and then
         * creating a Resource implementation from it.
         *
         * For example, one loader may handle the '.png' extension and
         * create a 2D texture from it.
         *
         * Another may handle the '.ply' extension and create a model
         * from the data read in.
         *
         * There may only be one loader per file extension.
         */
        class AResourceLoader
        {
        public:

            AResourceLoader(std::string const& extension);
            virtual ~AResourceLoader();

            /**
             * \return The file type (as an extension) that this loader can operate on.
             */
            virtual std::string getSupportedFileType() const;
            
            /**
             * 
             */
            virtual bool loadResource(Resource* resource, File const& file);

        protected:

            std::string m_SupportedExtension;
            
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