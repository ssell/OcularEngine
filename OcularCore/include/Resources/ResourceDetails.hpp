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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_DETAILS__H__
#define __H__OCULAR_RESOURCES_RESOURCE_DETAILS__H__

#include "Resource.hpp"
#include <memory>

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
        class ResourceManager;

        /**
         * \class ResourceDetails
         * \brief Maintains a resource and usage details.
         */
        class ResourceDetails
        {
            friend class ResourceManager;

        public:

            ResourceDetails(Resource* resource, ResourceType type = ResourceType::Undefined);
            ~ResourceDetails();

            /**
             *
             */
            Resource* getResource();

            /**
             *
             */
            Resource* getResourceUntracked() const;

            /**
             *
             */
            uint64_t getTimeOfLastRequest() const;

            /**
             *
             */
            unsigned getNumberOfRequests() const;

            /**
             *
             */
            uint64_t getSize() const;

            /**
             *
             */
            ResourceType getType() const;

            /**
             *
             */
            void reset();
        
        protected:

            Resource* m_Resource;
            ResourceType m_Type;     /// Secondary copy of ResourceType. Mainly used when identifying subresources of MultiResource instances.

            uint64_t m_LastRequest;  /// In NS
            unsigned m_NumberOfRequests;
        
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