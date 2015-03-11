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

#include <climits>

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
                Resource* resource = resourceIter->second->getResource().get();

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
                ResourceDetails* details = resourceIter->second.get();

                if(details != nullptr)
                {
                    details->reset();

                    Resource* resource = details->getResourceUntracked().get();

                    if((resource != nullptr) && (resource->isInMemory()))
                    {
                        resource->unload();
                        m_MemoryDetails.resourceUnloaded(resource);
                    }
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
                result = findExists->second->getResource();

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
                Resource* resource = resourceIter->second->getResource().get();

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

        bool ResourceManager::saveResource(Resource* resource, File const& file)
        {
            bool result = false;

            // Validate the Resource
            if(resource != nullptr)
            {
                if(resource->isInMemory())
                {
                    // The ResourceSaverManager will validate the file extension,
                    // and the ResourceSaver itself will validate the file.
                    result = m_ResourceSaverManager.saveResource(resource, file);
                }
                else 
                {
                    OcularLogger->error("Provided resource is not loaded in memory", OCULAR_INTERNAL_LOG("ResourceManager", "saveResource"));
                }
            }
            else 
            {
                OcularLogger->error("Provided resource is NULL", OCULAR_INTERNAL_LOG("ResourceManager", "saveResource"));
            }

            return false;
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

        void ResourceManager::registerResourceSaver(std::shared_ptr<AResourceSaver> saver)
        {
            m_ResourceSaverManager.registerResourceSaver(saver);
        }

        unsigned ResourceManager::getNumberOfResources() const
        {
            return static_cast<unsigned>(m_ResourceMap.size());
        }

        unsigned ResourceManager::getNumberOfResourceLoaders() const
        {
            return m_ResourceLoaderManager.getNumberOfResourceLoaders();
        }

        unsigned ResourceManager::getNumberOfResourceSavers() const
        {
            return m_ResourceSaverManager.getNumberOfResourceSavers();
        }

        void ResourceManager::isFileTypeSupported(std::string const& extension, bool& canLoad, bool& canSave) const
        {
            canLoad = m_ResourceLoaderManager.isExtensionSupported(extension);
            canSave = m_ResourceSaverManager.isExtensionSupported(extension);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void ResourceManager::freeMemorySpace()
        {
            if(m_MemoryDetails.getTotalMemoryUsage() > m_MemoryLimit)
            {
                ResourceDetails* resourceDetails = nullptr;

                // Out of space, need to free up memory
                switch(m_PriorityBehaviour)
                {
                case RESOURCE_PRIORITY_BEHAVIOUR::LEAST_FREQUENTLY_USED:
                    resourceDetails = findLeastFrequentlyUsed();
                    break;

                case RESOURCE_PRIORITY_BEHAVIOUR::SIZE_ASCENDING:
                    resourceDetails = findSizeAscending();
                    break;

                case RESOURCE_PRIORITY_BEHAVIOUR::SIZE_DESCENDING:
                    resourceDetails = findSizeDescending();
                    break;

                case RESOURCE_PRIORITY_BEHAVIOUR::LEAST_RECENTLY_USED:
                default:
                    resourceDetails = findLeastRecentlyUsed();
                    break;
                }

                if(resourceDetails != nullptr)
                {
                    Resource* resource = resourceDetails->getResourceUntracked().get();

                    if(resource != nullptr)
                    {
                        resource->unload();
                        m_MemoryDetails.resourceUnloaded(resource);
                    }

                    resourceDetails->reset();

                    // Call this method again as freeing just a single resource may not have been enough
                    freeMemorySpace();
                }
                else 
                {
                    unsigned long long newLimit = m_MemoryLimit;

                    if(newLimit == 0ULL)
                    {
                        newLimit = 1000000UL;
                    }
                    else
                    {
                        newLimit *= 2;
                    }

                    OcularLogger->warning("Unexpected behaviour: Resource memory limit exceeded but no Resources discovered. Increasing limit from ", m_MemoryLimit, " to ", newLimit, OCULAR_INTERNAL_LOG("ResourceManager", "freeMemorySpace"));

                    m_MemoryLimit = newLimit;
                }
            }
        }

        ResourceDetails* ResourceManager::findLeastFrequentlyUsed()
        {
            ResourceDetails* result = nullptr;

            unsigned leastUsed = UINT_MAX;

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); findResource++)
            {
                ResourceDetails* current = findResource->second.get();

                if(current != nullptr)
                {
                    if(current->getNumberOfRequests() < leastUsed)
                    {
                        result = current;
                    }
                }
            }

            return result;
        }

        ResourceDetails* ResourceManager::findLeastRecentlyUsed()
        {
            ResourceDetails* result = nullptr;
            
            unsigned long long lastUsed = ULLONG_MAX;

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); findResource++)
            {
                ResourceDetails* current = findResource->second.get();

                if(current != nullptr)
                {
                    if(current->getTimeOfLastRequest() < lastUsed)
                    {
                        result = current;
                    }
                }
            }

            return result;
        }

        ResourceDetails* ResourceManager::findSizeAscending()
        {
            ResourceDetails* result = nullptr;
            
            unsigned long long smallest = ULLONG_MAX;

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); findResource++)
            {
                ResourceDetails* current = findResource->second.get();

                if(current != nullptr)
                {
                    if(current->getSize() < smallest)
                    {
                        result = current;
                    }
                }
            }

            return result;
        }

        ResourceDetails* ResourceManager::findSizeDescending()
        {
            ResourceDetails* result = nullptr;
            
            unsigned long long largest = 0ULL;

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); findResource++)
            {
                ResourceDetails* current = findResource->second.get();

                if(current != nullptr)
                {
                    if(current->getSize() > largest)
                    {
                        result = current;
                    }
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}