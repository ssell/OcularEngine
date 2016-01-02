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

#include "Resources/ResourceDetails.hpp"
#include "Resources/ResourceManager.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceDetails::ResourceDetails(Resource* resource)
        {
            m_Resource = resource;
            m_LastRequest = 0ULL;
            m_NumberOfRequests = 0;
        }

        ResourceDetails::~ResourceDetails()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        Resource* ResourceDetails::getResource()
        {
            m_LastRequest = OcularEngine.Clock()->getElapsedNS();
            m_NumberOfRequests++;

            return m_Resource;
        }

        Resource* ResourceDetails::getResourceUntracked() const 
        {
            return m_Resource;
        }

        uint64_t ResourceDetails::getTimeOfLastRequest() const
        {
            return m_LastRequest;
        }

        unsigned ResourceDetails::getNumberOfRequests() const 
        {
            return m_NumberOfRequests;
        }

        uint64_t ResourceDetails::getSize() const
        {
            uint64_t result = 0ULL;

            if(m_Resource != nullptr)
            {
                result = m_Resource->getSize();
            }

            return result;
        }

        void ResourceDetails::reset() 
        {
            m_LastRequest = 0ULL;
            m_NumberOfRequests = 0;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}