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

#include "Resources/ResourceManager.hpp"
#include "Resources/ResourceExplorer.hpp"
#include "Resources/MultiResource.hpp"

#include "OcularEngine.hpp"

#include <climits>
#include <algorithm>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceManager::ResourceManager()
            : m_PriorityBehaviour(ResourcePriorityBehaviour::LeastFrequentlyUsed),
              m_MemoryLimit(0)
        {

        }

        ResourceManager::~ResourceManager()
        {
            unloadAllResources();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ResourceManager::initialize()
        {
            std::string sourceDirectory = OcularConfig->get("ResourceDirectory");

            if(sourceDirectory.empty())
            {
                OcularConfig->set("ResourceDirectory", "Resources");
            }
            else
            {
                m_ResourceExplorer.setResourceDirectoryName(sourceDirectory);
            }

            forceSourceRefresh();
            m_ResourceDefaults.initialize();
        }

        void ResourceManager::unloadAllResources()
        {
            for(auto iter = m_ResourceMap.begin(); iter != m_ResourceMap.end(); ++iter)
            {
                auto details = iter->second;

                if(details)
                {
                    auto resource = details->getResourceUntracked();

                    if(resource)
                    {
                        resource->unload();
                        resource = nullptr;
                    }

                    details = nullptr;
                }
            }
        }

        void ResourceManager::forceSourceRefresh()
        {
            //----------------------------------------
            // Populate the file map

            m_FileMap.clear();
            m_ResourceExplorer.populateFileMap(m_FileMap, &m_ResourceLoaderManager);

            //----------------------------------------
            // Populate the resource map

            m_ResourceMap.clear();   // \todo Is this enough to safely remove all Resources?

            for(auto fileIter = m_FileMap.begin(); fileIter != m_FileMap.end(); ++fileIter)
            {
                auto findResource = m_ResourceMap.find(fileIter->first);

                if(findResource == m_ResourceMap.end())
                {
                    // No entry for this resource path. Add an empty one.
                    if(m_ResourceLoaderManager.getResourceType((*fileIter).second.getExtension()) == ResourceType::Multi)
                    {
                        // This file is a MultiResource. Explore it to ensure all sub-resources are added to tracking
                        m_ResourceLoaderManager.exploreResource((*fileIter).second);
                    }

                    m_ResourceMap.insert(std::make_pair(fileIter->first, nullptr));
                }
            }
        }

        bool ResourceManager::forceLoadResource(std::string const& path)
        {
            bool result = false;
            const std::string lowerPath = Utils::String::ToLower(path);

            auto resourceIter = m_ResourceMap.find(lowerPath);

            if(resourceIter != m_ResourceMap.end())
            {
                Resource* resource = resourceIter->second->getResource();

                if((resource == nullptr) || (!resource->isInMemory()))
                {
                    auto findFile = m_FileMap.find(lowerPath);

                    if(findFile != m_FileMap.end())
                    {
                        m_ResourceLoaderManager.loadResource(resource, findFile->second, lowerPath);

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
            const std::string lowerPath = Utils::String::ToLower(path);

            auto resourceIter = m_ResourceMap.find(lowerPath);

            if(resourceIter != m_ResourceMap.end())
            {
                ResourceDetails* details = resourceIter->second.get();

                if(details != nullptr)
                {
                    details->reset();

                    Resource* resource = details->getResourceUntracked();

                    if((resource != nullptr) && (resource->isInMemory()))
                    {
                        resource->unload();
                        m_MemoryDetails.resourceUnloaded(resource);
                    }
                }
            }

            return result;
        }

        bool ResourceManager::addResource(std::string const& name, File const& file, Resource* resource, ResourceType type)
        {
            bool result = false;
            const std::string lowerName = Utils::String::ToLower(name);

            auto findResource = m_ResourceMap.find(lowerName);

            if(findResource == m_ResourceMap.end())
            {
                m_ResourceMap[lowerName] = std::make_shared<ResourceDetails>(resource, type);
                m_FileMap[lowerName] = file;

                result = true;
            }
            else if(!findResource->second)
            {
                findResource->second = std::make_shared<ResourceDetails>(nullptr);

                findResource->second->m_Resource = resource;
                findResource->second->m_Type = type;
            }

            return result;
        }

        ResourceMemoryDetails ResourceManager::getMemoryUsage()
        {
            return m_MemoryDetails;
        }

        Resource* ResourceManager::getResource(std::string const& path)
        {
            Resource* result = nullptr;
            const std::string lowerPath = Utils::String::ToLower(path);
            
            //------------------------------------------------------------
            // First check if the resource exists

            auto findResource = m_ResourceMap.find(lowerPath);

            if(findResource != m_ResourceMap.end())
            {
                // Resource exists (there is an associated file)

                std::shared_ptr<ResourceDetails> details = findResource->second;

                if(details == nullptr)
                {
                    m_ResourceMap[lowerPath] = std::make_shared<ResourceDetails>(nullptr);
                    details = m_ResourceMap[lowerPath];
                }

                result = details->getResource();

                //--------------------------------------------------------
                // Check if the resource has already been created and if its in memory

                if((result == nullptr) || (!result->isInMemory()))
                {
                    // Does not exist or is not in memory; Attempt to create and/or load.
                    auto findFile = m_FileMap.find(lowerPath);

                    if(findFile != m_FileMap.end())
                    {
                        findFile->second.refresh();

                        // Found the file we are to load from
                        Resource* resource = result;

                        if(resource)
                        {
                            //--------------------------------------------
                            // Resource simply needs to be reloaded

                            if((details->getType() == ResourceType::Undefined) ||
                               (details->getType() == m_ResourceLoaderManager.getResourceType(findFile->second.getExtension())))
                            {
                                // The type of the requested Resource matches that of the type associated with the file
                                m_ResourceLoaderManager.loadResource(resource, findFile->second, lowerPath);

                                if((result == nullptr) || (!result->isInMemory()))
                                {
                                    OcularLogger->error("Failed to reload resource at '", findFile->second.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceManager", "getResource"));
                                    result = nullptr; // We return null on failure irregardless
                                }
                                else
                                {
                                    resource->setMappingName(lowerPath);
                                }
                            }
                            else
                            {
                                // The type of the requested Resource does not match that of the type associated with the file.
                                // This is typically due to requesting a subresource in a MultiResource.

                                m_ResourceLoaderManager.loadSubResource(resource, findFile->second, lowerPath);

                                if((result == nullptr) || (!result->isInMemory()))
                                {
                                    OcularLogger->error("Failed to reload sub-resource at '", findFile->second.getFullPath(), "' with mapping name '", path, "'", OCULAR_INTERNAL_LOG("ResourceManager", "getResource"));
                                    result = nullptr; // We return null on failure irregardless
                                }
                                else
                                {
                                    resource->setMappingName(lowerPath);
                                }
                            }
                        }
                        else
                        {
                            //--------------------------------------------
                            // Resource does not exist at all yet

                            if((details->getType() == ResourceType::Undefined) ||
                               (details->getType() == m_ResourceLoaderManager.getResourceType(findFile->second.getExtension())))
                            {
                                // The type of the requested Resource matches that of the type associated with the file

                                if(m_ResourceLoaderManager.loadResource(resource, findFile->second, lowerPath) && resource)
                                {
                                    resource->setMappingName(lowerPath);
                                    details->m_Resource = resource;
                                    result = details->m_Resource;
                                }
                                else
                                {
                                    if(resource)
                                    {
                                        delete resource;
                                        resource = nullptr;
                                    }

                                    OcularLogger->error("Failed to create resource at '", findFile->second.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceManager", "getResource"));
                                }
                            }
                            else
                            {
                                // The type of the requested Resource does not match that of the type associated with the file.
                                // This is typically due to requesting a subresource in a MultiResource.

                                m_ResourceLoaderManager.loadSubResource(resource, findFile->second, lowerPath);

                                if(resource)
                                {
                                    resource->setMappingName(lowerPath);
                                    details->m_Resource = resource;
                                    result = details->m_Resource;
                                }
                                else
                                {
                                    OcularLogger->error("Failed to create sub-resource at '", findFile->second.getFullPath(), "' with mapping name '", path, "'", OCULAR_INTERNAL_LOG("ResourceManager", "getResource"));
                                    result = nullptr; // We return null on failure irregardless
                                }
                            }
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

        Resource* ResourceManager::getEmptyResource(ResourceType const type)
        {
            return m_ResourceDefaults.getEmptyResource(type);
        }

        Resource* ResourceManager::getMissingResource(ResourceType const type)
        {
            return m_ResourceDefaults.getMissingResource(type);
        }

        File ResourceManager::getResourceFile(std::string const& path) const
        {
            File result;
            const std::string lowerPath = Utils::String::ToLower(path);

            auto findFile = m_FileMap.find(lowerPath);

            if(findFile != m_FileMap.end())
            {
                result = findFile->second;
            }

            return result;
        }

        std::string ResourceManager::getResourceMappingName(File const& file) const
        {
            std::string result;
            
            const auto resourceType = m_ResourceLoaderManager.getResourceType(file.getExtension());

            for(auto filePair : m_FileMap)
            {
                const std::string mappingName = filePair.first;

                if(Utils::String::IsEqual(filePair.second.getFullPath(), file.getFullPath()))
                {
                    result = mappingName;

                    // The source files match, but make sure we are not looking at a subresource of a MultiResource
                    auto findResource = m_ResourceMap.find(mappingName);

                    if(findResource != m_ResourceMap.end())
                    {
                        if(findResource->second && (findResource->second->getType() == resourceType))
                        {
                            // Perfect match. Break out.
                            break;
                        }
                    }      
                }
            }

            return result;
        }

        bool ResourceManager::isInMemory(std::string const& path)
        {
            bool result = false;
            const std::string lowerPath = Utils::String::ToLower(path);

            auto resourceIter = m_ResourceMap.find(lowerPath);

            if(resourceIter != m_ResourceMap.end())
            {
                Resource* resource = resourceIter->second->getResource();

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
            const std::string lowerPath = Utils::String::ToLower(path);

            auto resourceIter = m_ResourceMap.find(lowerPath);

            if(resourceIter != m_ResourceMap.end())
            {
                result = true;
            }

            return result;
        }

        Resource* ResourceManager::loadUnmanagedFile(File const& file)
        {
            Resource* result = nullptr;
            
            if((file.exists()) && (file.isFile()))
            {
                m_ResourceLoaderManager.loadResource(result, file, "");
            }
            else 
            {
                OcularLogger->error("Failed to find or open file at '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceManager", "loadUnmanagedFile"));
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

            return result;
        }

        void ResourceManager::setMemoryLimit(uint64_t const maxMemory)
        {
            // Need a way to check max system memory
            m_MemoryLimit = maxMemory;
        }

        void ResourceManager::setPriorityBehaviour(ResourcePriorityBehaviour const behaviour)
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

        std::string const& ResourceManager::getSourceDirectory() const
        {
            return m_ResourceExplorer.getResourceDirectoryName();
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

        void ResourceManager::getResourcesOfType(ResourceType const type, std::vector<std::string>& resources)
        {
            resources.reserve(m_ResourceMap.size());

            for(auto resourceEntry : m_ResourceMap)
            {
                if(resourceEntry.second)
                {
                    Resource* resource = resourceEntry.second->getResource();

                    if(resource)
                    {
                        if(resource->getResourceType() == type)
                        {
                            resources.push_back(resourceEntry.first);
                        }
                    }
                    else if(resourceEntry.second->getType() == type)
                    {
                        resources.push_back(resourceEntry.first);
                    }
                }
                else
                {
                    // Never been created
                    auto findFile = m_FileMap.find(resourceEntry.first);

                    if(findFile != m_FileMap.end())
                    {
                        if(m_ResourceLoaderManager.getResourceType(findFile->second.getExtension()) == type)
                        {
                            resources.push_back(resourceEntry.first);
                        }
                    }
                }
            }
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
                case ResourcePriorityBehaviour::LeastFrequentlyUsed:
                    resourceDetails = findLeastFrequentlyUsed();
                    break;

                case ResourcePriorityBehaviour::SizeAscending:
                    resourceDetails = findSizeAscending();
                    break;

                case ResourcePriorityBehaviour::SizeDescending:
                    resourceDetails = findSizeDescending();
                    break;

                case ResourcePriorityBehaviour::LeastRecentlyUsed:
                default:
                    resourceDetails = findLeastRecentlyUsed();
                    break;
                }

                if(resourceDetails != nullptr)
                {
                    Resource* resource = resourceDetails->getResourceUntracked();

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
                    uint64_t newLimit = m_MemoryLimit;

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

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); ++findResource)
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
            
            uint64_t lastUsed = ULLONG_MAX;

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); ++findResource)
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
            
            uint64_t smallest = ULLONG_MAX;

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); ++findResource)
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
            
            uint64_t largest = 0ULL;

            for(auto findResource = m_ResourceMap.begin(); findResource != m_ResourceMap.end(); ++findResource)
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