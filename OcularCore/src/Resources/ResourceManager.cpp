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

#include "OcularEngine.hpp"

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
            //----------------------------------------
            // Populate the file map

            m_ResourceExplorer.populateFileMap(m_FileMap);

            //----------------------------------------
            // Populate the resource map

            for(auto fileIter = m_FileMap.begin(); fileIter != m_FileMap.end(); fileIter++)
            {
                auto findResource = m_ResourceMap.find(fileIter->first);

                if(findResource == m_ResourceMap.end())
                {
                    // No entry for this resource path. Add an empty one.
                    m_ResourceMap.insert(std::make_pair(fileIter->first, nullptr));
                }
            }
        }

        bool ResourceManager::forceLoadResource(std::string const& path)
        {
            bool result = false;
            auto resourceIter = m_ResourceMap.find(path);

            if(resourceIter != m_ResourceMap.end())
            {
                Resource* resource = resourceIter->second.get();

                if((resource == nullptr) || (!resource->isInMemory()))
                {
                    auto findFile = m_FileMap.find(path);

                    if(findFile != m_FileMap.end())
                    {
                        m_ResourceLoaderManager.loadResource(resource, findFile->second);

                        if((resource != nullptr) && (resource->isInMemory()))
                        {
                            m_MemoryDetails.resourceLoaded(resource);
                            result = true;
                        }
                        else
                        {
                            OcularLogger->error("Failed to load resource at '", findFile->second.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceManager", "forceLoadResource"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("No associated full path with '", path, "'", OCULAR_INTERNAL_LOG("ResourceManager", "forceLoadResource"));
                    }
                }
                else
                {
                    // Already exists and in memory
                    result = true;
                }
            }
            else
            {
                OcularLogger->error("No tracked resource at '", path, "'", OCULAR_INTERNAL_LOG("ResourceManager", "forceLoadResource"));
            }

            freeMemorySpace();

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
                    resource->release();
                    m_MemoryDetails.resourceUnloaded(resource);
                }
            }

            return result;
        }

        ResourceMemoryDetails ResourceManager::getMemoryUsage()
        {
            return m_MemoryDetails;
        }

        std::shared_ptr<Resource> ResourceManager::getResource(std::string const& path)
        {
            std::shared_ptr<Resource> result = nullptr;
            
            // First check if the resource exists
            auto findExists = m_ResourceMap.find(path);

            if(findExists != m_ResourceMap.end())
            {
                result = findExists->second;

                if((result == nullptr) || (!result->isInMemory()))
                {
                    // Does not exist or is not in memory; Attempt to create and/or load.
                    auto findFile = m_FileMap.find(path);

                    if(findFile != m_FileMap.end())
                    {
                        m_ResourceLoaderManager.loadResource(result.get(), findFile->second);

                        if((result == nullptr) || (!result->isInMemory()))
                        {
                            OcularLogger->error("Failed to load resource at '", findFile->second.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceManager", "getResource"));
                            result = nullptr; // We return null on failure irregardless
                        }
                    }
                    else
                    {
                        OcularLogger->error("No matching resouce file found for '", path, "'", OCULAR_INTERNAL_LOG("ResourceManager", "getResource"));
                        result = nullptr; // We return null on failure irregardless
                    }
                }
            }
            else
            {
                OcularLogger->error("No matching resource for '", path, "'", OCULAR_INTERNAL_LOG("ResourceManager", "getResource"));
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
                    m_ResourceLoaderManager.loadResource(result, path);
                }
                else 
                {
                    OcularLogger->error("Failed to find or open file at '", path, "'", OCULAR_INTERNAL_LOG("ResourceManager", "loadUnmanagedFile"));
                }
            }
            else 
            {
                OcularLogger->error("Specified file path is empty", OCULAR_INTERNAL_LOG("ResourceManager", "loadUnmanagedFile"));
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
            m_ResourceLoaderManager.registerResourceLoader(loader);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void ResourceManager::freeMemorySpace()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}