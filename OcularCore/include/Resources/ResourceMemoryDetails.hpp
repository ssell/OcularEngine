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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_MEMORY_DETAILS__H__
#define __H__OCULAR_RESOURCES_RESOURCE_MEMORY_DETAILS__H__

#include "Resource.hpp"
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
         * \class ResourceMemoryDetails
         */
        class ResourceMemoryDetails
        {
        public:

            ResourceMemoryDetails();
            ~ResourceMemoryDetails();

            /**
             * Notifies that the specified resource has been loaded into memory.
             *
             * \param[in] resource
             */
            void resourceLoaded(Resource const* resource);

            /**
             * Notifies that the specified resource has be unloaded from memory.
             *
             * \param[in] resource
             */
            void resourceUnloaded(Resource const* resource);

            /** 
             * \return The total amount of memory, in bytes, in use by tracked Resources.
             */
            uint64_t getTotalMemoryUsage() const;

            /**
             * \param[in] type Type of Resource to query about
             * \return The total amount of memory, in bytes, used by all Resources of the specified type.
             */
            uint64_t getMemoryUsage(ResourceType type) const;

        protected:

        private:

            uint64_t m_TotalUsage;

            std::unordered_map<ResourceType, uint64_t> m_MemoryMap;
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