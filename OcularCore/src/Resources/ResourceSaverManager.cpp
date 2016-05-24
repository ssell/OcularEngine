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

#include "Resources/ResourceSaverManager.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceSaverManager::ResourceSaverManager()
        {
        
        }

        ResourceSaverManager::~ResourceSaverManager()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ResourceSaverManager::registerResourceSaver(std::shared_ptr<AResourceSaver> saver)
        {
            if(saver != nullptr)
            {
                std::string extension = saver->getSupportedFileType();
                auto findSaver = m_ResourceSaverMap.find(extension);

                if(findSaver == m_ResourceSaverMap.end())
                {
                    m_ResourceSaverMap.insert(std::make_pair(extension, saver));
                }
            }
        }

        bool ResourceSaverManager::saveResource(Resource* resource, File const& file)
        {
            bool result = false;

            std::string extension = file.getExtension();
            auto findSaver = m_ResourceSaverMap.find(extension);

            if(findSaver != m_ResourceSaverMap.end())
            {
                std::shared_ptr<AResourceSaver> saver = findSaver->second;

                if(saver != nullptr)
                {
                    result = saver->saveResource(resource, file);
                }
                else
                {
                    // This *should* never happen
                    OcularLogger->error("ResourceSaver for '", extension, "' is invalid", OCULAR_INTERNAL_LOG("ResourceSaverManager", "saveResource"));
                }
            }
            else
            {
                OcularLogger->error("No ResourceSaver associated with '", extension, "' files", OCULAR_INTERNAL_LOG("ResourceSaverManager", "saveResource"));
            }

            return result;
        }

        unsigned ResourceSaverManager::getNumberOfResourceSavers() const
        {
            return static_cast<unsigned>(m_ResourceSaverMap.size());
        }

        bool ResourceSaverManager::isExtensionSupported(std::string const& extension) const
        {
            bool result = false;
            auto findExtension = m_ResourceSaverMap.find(extension);

            if(findExtension != m_ResourceSaverMap.end())
            {
                result = true;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}