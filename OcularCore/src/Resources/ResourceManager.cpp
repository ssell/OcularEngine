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

#include "Resources/ResourceManager.hpp"
#include "Resources/ResourceExplorer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceManager::ResourceManager()
        {
        
        }

        ResourceManager::~ResourceManager()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ResourceManager::initialize()
        {
            forceSourceRefresh();
        }

        void ResourceManager::forceSourceRefresh()
        {
            m_ResourceExplorer.populateResourceMap(m_ResourceMap);
        }

        bool ResourceManager::forceLoadResource(std::string const& path)
        {
            bool result = false;
            auto resourceIter = m_ResourceMap.find(path);

            if(resourceIter != m_ResourceMap.end())
            {
                Resource* resource = resourceIter->second.get();

                if((resource != nullptr) && (!resource->isInMemory()))
                {
                    // ...
                }
            }

            return result;
        }

        bool ResourceManager::forceUnloadResource(std::string const& path)
        {
            bool result = false;
            auto resourceIter = m_ResourceMap.find(path);

            if(resourceIter != m_ResourceMap.end())
            {
                Resource* resource = resourceIter->second.get();

                if((resource != nullptr) && (resource->isInMemory()))
                {
                    // ...
                }
            }

            return result;
        }

        ResourceMemoryDetails ResourceManager::getMemoryUsage()
        {
            ResourceMemoryDetails result;

            // ...

            return result;
        }

        std::shared_ptr<Resource> ResourceManager::getResource(std::string const& path)
        {
            std::shared_ptr<Resource> result = nullptr;
            auto resourceIter = m_ResourceMap.find(path);

            if(resourceIter != m_ResourceMap.end())
            {
                result = resourceIter->second;
            }

            return result;
        }

        bool ResourceManager::isInMemory(std::string const& path)
        {
            bool result = false;
            auto resourceIter = m_ResourceMap.find(path);

            if(resourceIter != m_ResourceMap.end())
            {
                Resource* resource = resourceIter->second.get();

                if(resource != nullptr)
                {
                    result = resource->isInMemory();
                }
            }

            return result;
        }

        bool ResourceManager::doesExist(std::string const& path)
        {
            bool result = false;
            auto resourceIter = m_ResourceMap.find(path);

            if(resourceIter != m_ResourceMap.end())
            {
                result = true;
            }

            return result;
        }

        Resource* ResourceManager::loadUnmanagedFile(std::string const& path)
        {
            Resource* result = nullptr;
            
            if(!path.empty())
            {
                File file(path);

                if((file.exists()) && (file.isFile()))
                {
                    // ...
                }
            }

            return result;
        }

        void ResourceManager::setMemoryLimit(unsigned long long const maxMemory)
        {
            // Need a way to check max system memory
            m_MemoryLimit = maxMemory;
        }

        void ResourceManager::setPriorityBehaviour(RESOURCE_PRIORITY_BEHAVIOUR const behaviour)
        {
            m_PriorityBehaviour = behaviour;
        }

        void ResourceManager::setSourceBlacklist(std::list<std::string> const& blacklist)
        {
            m_ResourceExplorer.setBlacklist(blacklist);
        }

        void ResourceManager::setSourceDirectory(std::string const& directory)
        {
            m_ResourceExplorer.setResourceDirectoryName(directory);
        }

        void ResourceManager::registerResourceLoader(std::shared_ptr<AResourceLoader> loader)
        {
            if(loader != nullptr)
            {
                std::string fileType = loader->getSupportedFileType();
                auto findLoader = m_ResourceLoaderMap.find(fileType);

                if(findLoader != m_ResourceLoaderMap.end())
                {
                    m_ResourceLoaderMap.insert(std::make_pair(fileType, loader));
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}