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

#include "Resources/ResourceMemoryDetails.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceMemoryDetails::ResourceMemoryDetails()
        {
            m_TotalUsage = 0ULL;

            // Set up the map
            const unsigned stop = static_cast<unsigned>(ResourceType::Undefined);

            for(unsigned i = 0; i <= stop; i++)
            {
                m_MemoryMap.insert(std::make_pair(static_cast<ResourceType>(i), 0ULL));
            }
        }

        ResourceMemoryDetails::~ResourceMemoryDetails()
        {
            
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ResourceMemoryDetails::resourceLoaded(Resource const* resource)
        {
            if((resource != nullptr) && (resource->isInMemory()))
            {
                ResourceType resourceType = resource->getResourceType();
                uint64_t memoryUsed = resource->getSize();

                m_TotalUsage += memoryUsed;
                m_MemoryMap[resourceType] += memoryUsed;
            }
        }

        void ResourceMemoryDetails::resourceUnloaded(Resource const* resource)
        {
            if((resource != nullptr) && (!resource->isInMemory()))
            {
                ResourceType resourceType = resource->getResourceType();
                uint64_t memoryFreed = resource->getSize();

                m_TotalUsage -= memoryFreed;
                m_MemoryMap[resourceType] -= memoryFreed;
            }
        }

        uint64_t ResourceMemoryDetails::getTotalMemoryUsage() const
        {
            return m_TotalUsage;
        }

        uint64_t ResourceMemoryDetails::getMemoryUsage(ResourceType const type) const
        {
            return m_MemoryMap.find(type)->second;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}