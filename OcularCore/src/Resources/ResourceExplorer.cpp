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

#include "Resources/ResourceExplorer.hpp"
#include "Resources/ResourceLoaderManager.hpp"

#include "Utilities/StringUtils.hpp"

#include <algorithm>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceExplorer::ResourceExplorer()
        {
            m_DirectoryName = "Resources";
            m_ExtensionSensitive = false;
        }

        ResourceExplorer::~ResourceExplorer()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ResourceExplorer::setBlacklist(std::list<std::string> const& blacklist)
        {
            m_Blacklist.clear();

            for(auto iter = blacklist.begin(); iter != blacklist.end(); ++iter)
            {
                if(m_Blacklist.find((*iter)) == m_Blacklist.end()) 
                {
                    m_Blacklist.insert(std::make_pair((*iter), true));
                }
            }
        }

        void ResourceExplorer::setResourceDirectoryName(std::string const& name)
        {
            m_DirectoryName = name;
        }

        std::string const& ResourceExplorer::getResourceDirectoryName() const
        {
            return m_DirectoryName;
        }

        void ResourceExplorer::setIsExtensionSensitive(bool const sensitive)
        {
            m_ExtensionSensitive = sensitive;
        }

        void ResourceExplorer::populateFileMap(std::unordered_map<std::string, File>& fileMap, ResourceLoaderManager* loader)
        {
            std::list<Directory> rootDirectories;

            Directory specifiedDir = Directory(m_DirectoryName);

            if(specifiedDir.exists())
            {
                rootDirectories.push_back(specifiedDir);
            }
            else
            {
                findRootDirectories(rootDirectories);
            }

            if(rootDirectories.empty())
            {
                return;
            }

            //------------------------------------------------------------------------------
            // Iterate through each discovered root directory and catalog all resource files found within them.

            for(auto rootIter = rootDirectories.begin(); rootIter != rootDirectories.end(); ++rootIter)
            {
                (*rootIter).explore(true);
                std::vector<File> resourceFiles = (*rootIter).getChildFiles(true);

                for(auto fileIter = resourceFiles.begin(); fileIter != resourceFiles.end(); ++fileIter)
                {
                    const std::string extension = (*fileIter).getExtension();

                    if(!isBlacklisted(extension) && loader->isExtensionSupported(extension))
                    {
                        std::string relative = getRelativePathFromResourceRoot((*rootIter), (*fileIter));
                        std::replace(relative.begin(), relative.end(), '\\', '/');

                        const std::string relativeLower = Utils::String::ToLower(relative);

                        // If the key is not already in-use, then add a new entry to the map
                        if(fileMap.find(relativeLower) == fileMap.end())
                        {
                            fileMap.insert(std::make_pair(relativeLower, (*fileIter)));
                        }
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool ResourceExplorer::isBlacklisted(std::string const& extension)
        {
            bool result = false;

            if(m_Blacklist.find(extension) != m_Blacklist.end()) 
            {
                result = true;
            }

            return result;
        }

        void ResourceExplorer::findRootDirectories(std::list<Directory>& rootDirectories)
        {
            Directory workingDir("");

            workingDir.explore(true);
            std::vector<Directory> children = workingDir.getChildDirectories();

            for(auto iter = children.begin(); iter != children.end(); ++iter)
            {
                if((*iter).getName().compare(m_DirectoryName) == 0)
                {
                    rootDirectories.push_back(Directory((*iter).getFullPath()));
                }
            }
        }

        std::string ResourceExplorer::getRelativePathFromResourceRoot(Directory const root, File const file)
        {
            // 1. relative = /path/to/Resources/path/to/Resource.png
            // 2. relative = path/to/Resource.png
            // 3. relative = path/to/Resource      (optional if m_ExtensionSensitive == true)

            std::string relative = file.getFullPath();
            relative.erase(0, root.getFullPath().length() + 1);  // +1 because directory full path excludes trailing slash

            if(!m_ExtensionSensitive)
            {
                relative.erase((relative.length() - file.getExtension().length()));
            }

            return relative;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}