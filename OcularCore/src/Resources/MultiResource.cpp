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

#include "Resources/MultiResource.hpp"
#include "OcularEngine.hpp"
#include "Utilities/StringComposer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MultiResource::MultiResource()
            : Resource()
        {

        }

        MultiResource::~MultiResource()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void MultiResource::addSubResource(Resource* resource, std::string const& name)
        {
            if(resource)
            {
                auto find = m_SubResources.find(name);

                if(find != m_SubResources.end())
                {
                    OcularLogger->warning("Duplicate Resource Added", OCULAR_INTERNAL_LOG("MultiResource", "addSubResource"));
                    
                    delete (*find).second;
                    m_SubResources.erase(find);
                }

                resource->setName(name);
                resource->setMappingName(m_MappingName + "/" + name);
                resource->setIsInMemory(true);
                resource->setSourceFile(m_SourceFile);

                m_SubResources[name] = resource;
            }
            else
            {
                OcularLogger->warning("Attempted to add NULL Resource to MultiResource", OCULAR_INTERNAL_LOG("MultiResource", "addSubResource"));
            }
        }

        Resource* MultiResource::getSubResource(std::string const& name)
        {
            Resource* result = nullptr;
            auto find = m_SubResources.find(name);

            if(find != m_SubResources.end())
            {
                result = (*find).second;
            }

            return result;
        }

        void MultiResource::getSubResourceNames(std::vector<std::string>& names)
        {
            names.clear();
            names.reserve(m_SubResources.size());

            for(auto iter = m_SubResources.begin(); iter != m_SubResources.end(); ++iter)
            {
                names.push_back((*iter).first);
            }
        }

        void MultiResource::getSubResources(std::vector<Resource*>& resources)
        {
            resources.clear();
            resources.reserve(m_SubResources.size());

            for(auto iter = m_SubResources.begin(); iter != m_SubResources.end(); ++iter)
            {
                resources.push_back((*iter).second);
            }
        }

        uint32_t MultiResource::getNumSubResources() const
        {
            return static_cast<uint32_t>(m_SubResources.size());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}