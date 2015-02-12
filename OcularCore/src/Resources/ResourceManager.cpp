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

        void ResourceManager::forceSourceRefresh()
        {
        
        }

        bool ResourceManager::forceLoadResource(std::string const& path)
        {
            bool result = false;

            // ...

            return result;
        }

        bool ResourceManager::forceUnloadResource(std::string const& path)
        {
            bool result = false;

            // ...

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

            // ...

            return result;
        }

        bool ResourceManager::isInMemory(std::string const& path)
        {
            bool result = false;

            // ...

            return result;
        }

        bool ResourceManager::doesExist(std::string const& path)
        {
            bool result = false;

            // ...

            return result;
        }

        Resource* ResourceManager::loadUnmanagedFile(std::string const& path)
        {
            Resource* result = nullptr;

            // ...

            return result;
        }

        void ResourceManager::setMemoryLimit(unsigned long long const maxMemory)
        {
        
        }

        void ResourceManager::setPriorityBehaviour(RESOURCE_PRIORITY_BEHAVIOUR const behaviour)
        {
        
        }

        void ResourceManager::setSourceBlacklist(std::list<std::string> const& blacklist)
        {
        
        }

        void ResourceManager::setSourceDirectory(std::string const& directory)
        {
        
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}