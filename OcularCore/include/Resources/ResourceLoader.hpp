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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_LOADER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_LOADER__H__

#include "Resource.hpp"
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

            AResourceLoader(std::string const& extension, ResourceType type);
            virtual ~AResourceLoader();

            /**
             * \return The file type (as an extension) that this loader can operate on.
             */
            virtual std::string getSupportedFileType() const;
            
            /**
             * \param[out] resource
             * \param[in]  file
             */
            virtual bool loadResource(Resource* &resource, File const& file);

            /**
             * \param[out] resource
             * \param[in]  file
             * \param[in]  mappingName
             */
            virtual bool loadSubResource(Resource* &resource, File const& file, std::string const& mappingName);

            /** 
             * For use with MultiResources. When called, the Resource will be explored
             * and all sub-resources should be added to the global resource manager via
             *
             *    ResourceManager::addResource
             *
             * \param[in] file 
             */
            virtual bool exploreResource(File const& file);

            /**
             * Returns the type of resource created by this loader.
             */
            ResourceType getResourceType() const;

        protected:
          
            /**
             * Verifies the file on the following conditions:
             *
             *     - File exists
             *     - File is readable
             *     - File extension matches the supported extension of the loader
             *
             * \param[in] File The file to validate.
             * \return TRUE if valid; Else FALSE.
             */
            bool isFileValid(Core::File const& file) const;

            //------------------------------------------------------------

            std::string m_SupportedExtension;
            
            ResourceType m_Type;

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