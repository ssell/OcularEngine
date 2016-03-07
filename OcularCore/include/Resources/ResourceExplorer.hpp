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

#pragma once
#ifndef __H__OCULAR_RESOURCES_RESOURCE_EXPLORER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_EXPLORER__H__

#include "FileIO/Directory.hpp"
#include "Resource.hpp"

#include <memory>
#include <list>
#include <unordered_map>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class ResourceExplorer
         *
         * Searches for resource folders and explores them for valid resource files.
         */
        class ResourceExplorer
        {
        public:

            ResourceExplorer();
            ~ResourceExplorer();

            /**
             * Sets the blacklist for the explorer.
             * 
             * \param[in] blacklist Container with all of the file extensions (including the '.') to add to the blacklist.
             * \note populateResourceMap will need to be called to update entries with new blacklist
             */
            void setBlacklist(std::list<std::string> const& blacklist);

            /**
             * \param[in] name Name of root directories that contain resource files.
             * \note populateResourceMap will need to be called to update entries with new directories
             */
            void setResourceDirectoryName(std::string const& name);

            /**
             *
             */
            std::string const& getResourceDirectoryName() const;

            /**
             * If extension-sensitive, then map keys will include the file extension. <br/>
             *
             * Example: <br/>
             *
             *     /path/to/Resources/Textures/Grass.png
             *     
             *     Sensitive Key:   Textures/Grass.png
             *     Insensitive Key: Textures/Grass
             *
             * Default behaviour is insensitive keys.
             *
             * \param[in] sensitive
             * \note populateResourceMap will need to be called to update keys for new sensitivity.
             */
            void setIsExtensionSensitive(bool sensitive);

            /**
             * \param[out] resourceMap Map of all resource files.
             */
            void populateFileMap(std::unordered_map<std::string, File>& fileMap);

        protected:

            /**
             * \return TRUE if the extension is blacklisted.
             */
            bool isBlacklisted(std::string extension);
            
            /**
             * Finds all root directories to explore for resource files.
             *
             * \param[out] rootDirectories
             */
            void findRootDirectories(std::list<Directory>& rootDirectories);

            /**
             * Composes the relative path from the root directory to the file. <br/>
             * 
             * Example: <br/>
             *
             *     Dir:  /path/to/Resources
             *     File: /path/to/Resources/Textures/Grass.png
             *     Rel:  Textures/Grass
             *
             * The returned path is formatted to be used as a resource map key.
             *
             * \param[in] root The root resource directory that contains the file
             * \param[in] file The resource file
             * \return The relative path from the root to the file
             */
            std::string getRelativePathFromResourceRoot(Directory root, File file);

        private:

            std::unordered_map<std::string, bool> m_Blacklist;
            std::string m_DirectoryName;

            bool m_ExtensionSensitive;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif