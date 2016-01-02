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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_SAVER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_SAVER__H__

#include "Resource.hpp"
#include "Common.hpp"

#include <string>
#include <vector>

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
         * \class AResourceSaver
         *
         * Base interface for all resource savers.
         *
         * A resource saver is responsible for saving a specific
         * type of resource to a specified file.
         */
        class AResourceSaver
        {
        public:

            AResourceSaver(std::string const& extension);
            virtual ~AResourceSaver();

            virtual std::string getSupportedFileType() const;

            /**
             * \param[in] resource
             * \param[in] file
             */
            virtual bool saveResource(Resource* resource, File const& file);

        protected:

            /**
             * Writes the full contents of the provided buffer to the specified file in the requisite endianness.
             *
             * It is assumed that the incoming buffer has native endian ordering.
             *
             * \param[in] file File to write the buffer to
             * \param[in] buffer Buffer container containing the entire file to write.
             * \param[in] fileEndianness The endianness in which to write the data.
             *
             * \return TRUE if successful.
             */
            virtual bool writeFile(Core::File const& file, std::vector<unsigned char> buffer, Endianness fileEndianness);

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