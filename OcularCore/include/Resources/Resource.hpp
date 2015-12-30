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
#ifndef __H__OCULAR_RESOURCES_RESOURCE__H__
#define __H__OCULAR_RESOURCES_RESOURCE__H__

#include "ResourceType.hpp"
#include "FileIO/File.hpp"
#include <cstdint>

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
         * \class Resource
         */
        class Resource 
        {
            friend class ResourceManager;

        public:

            /**
             * \param[in] file The source file for the resource.
             */
            Resource(File const& source);
            Resource();

            ~Resource();

            //----------------------------------------
            // Virtual Methods

            /**
             * Frees all memory used by this Resource.
             */
            virtual void unload() = 0;

            //----------------------------------------
            // Non-Virtual Methods

            /**
             * \return The source file for the resource.
             */
            File getSourceFile() const;

            /**
             * \param[in] file
             * \note This method should generally not be used unless by internal mechanisms.
             */
            void setSourceFile(File const& file);

            /**
             * \param[in] inMemory
             * \note This method should generally not be used unless by internal mechanisms.
             */
            void setIsInMemory(bool inMemory);

            /**
             * \return TRUE if the Resource is loaded in memory.
             */
            bool isInMemory() const;

            /**
             * \return The size, in bytes, of the Resource
             */
            uint64_t getSize() const;

            /**
             * \return The type of resource.
             */
            ResourceType getResourceType() const;

            /**
             * Forces this Resource to be loaded into memory.
             */
            virtual void forceLoad();

            /**
             *
             */
            void setName(std::string const& name);

            /**
             *
             */
            std::string const& getName() const;

            /**
             *
             */
            std::string const& getMappingName() const;

        protected:

            ResourceType m_Type;

            File m_SourceFile;
            bool m_IsInMemory;

            uint64_t m_SizeInMemory;

            std::string m_Name;
            std::string m_MappingName;

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