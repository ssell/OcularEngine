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

#include "Resources/ResourceLoaderManager.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceLoaderManager::ResourceLoaderManager()
        {
        
        }

        ResourceLoaderManager::~ResourceLoaderManager()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ResourceLoaderManager::registerResourceLoader(std::shared_ptr<AResourceLoader> loader)
        {
            if(loader != nullptr)
            {
                std::string extension = loader->getSupportedFileType();
                auto findLoader = m_ResourceLoaderMap.find(extension);

                if(findLoader == m_ResourceLoaderMap.end())
                {
                    m_ResourceLoaderMap.insert(std::make_pair(extension, loader));
                }
            }
        }

        void ResourceLoaderManager::loadResource(Resource* resource, std::string path)
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