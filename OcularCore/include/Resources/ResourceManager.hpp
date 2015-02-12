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

#pragma once
#ifndef __H__OCULAR_RESOURCES_RESOURCE_MANAGER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_MANAGER__H__

#include <memory>
#include <list>
#include <string>

#include "Resource.hpp"
#include "ResourceMemoryDetails.hpp"
#include "ResourcePriorityBehaviour.hpp"

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
         * \class ResourceManager
         *
         * The resource subsystem manages the loading, unloading, and tracking of 
         * all file-based resources used by the engine. This includes any textures, 
         * models, shaders, or any other form of data that is stored on-disk.
         *
         * When requesting a resource, you simply provide the local path and filename 
         * of the resource from the root 'Resources/' directory (or directories), minus 
         * the extension. For example, if you have a resource structure as follows:
         *
         *     OcularProject/
         *         Binaries/
         *         Intermediate/
         *         Resources/
         *             Models/
         *             Textures/
         *                 Buildings/
         *                 Terrain/
         *                     GrassDead.png
         *                     GrassGreen.tga
         *         Source/
         *
         * You would retrieve the `GrassGreen.tga` texture as follows:
         *
         *     ResourceManager->getResource("Textures/Terrain/GrassGreen");
         */
        class ResourceManager 
        {
        public:

            ResourceManager();
            ~ResourceManager();

            //----------------------------------------

            /**
             * Forces a refresh of all source folder contents.
             */
            void forceSourceRefresh();
            
            /**
             * Forces the resource to be loaded into memory.
             *
             * \param[in] path Resource path and name
             * \return TRUE if load was successful.
             */
            bool forceLoadResource(std::string const& path);

            /**
             * Forces the resource to be unloaded from memory.
             *
             * \param[in] path Resource path and name
             * \return TRUE if unload was successful.
             */
            bool forceUnloadResource(std::string const& path);

            /**
             * Retrieves the total amount of memory currently 
             * in use by the Resource Manager.
             *
             * \return
             */
            ResourceMemoryDetails getMemoryUsage();

            /**
             * Returns the resource at the specified path if it exists. 
             * The resource is loaded in memory if it is not already.
             *
             * \param[in] path Resource path and name
             * \return Pointer to the resource; Returns nullptr if failed to fetch resource.
             */
            std::shared_ptr<Resource> getResource(std::string const& path);

            /**
             * \param[in] path Resource path and name
             * \return TRUE if the specified resource is currently in-memory.
             */
            bool isInMemory(std::string const& path);

            /**
             * \param[in] path Resource path and name
             * \return TRUE if the specified resource exists on the system and is tracked.
             */
            bool doesExist(std::string const& path);

            /**
             * Attempts to load the file at the specified path as a Resource.
             *
             * Unlike other path parameters, this method requires the full path to the file.
             * This is because the resource is untracked, and does not exist in a designated Resource folder.
             *
             * It is up to the caller to properly clean up the returned resource (if not NULL)
             * when they are done using it.
             *
             * \param[in] path Full path to the file
             * \return A new Resource object; Returns NULL if the file does not exist or unable to load it.
             */
            Resource* loadUnmanagedFile(std::string const& path);

            /**
             * Sets the maximum amount of memory (in bytes) allocated for Resources.
             * This value is clamped if it exceeds the amount of memory available to the system.
             *
             * \param[in] maxMemory Amount of memory to allocate to Resources
             */
            void setMemoryLimit(unsigned long long maxMemory);

            /**
             * Sets the priority behaviour when determining which Resource to unload when 
             * the memory limit has been reached.
             *
             * Default is LEAST_RECENTLY_USED.
             *
             * \param behaviour Priority behaviour to use.
             */
            void setPriorityBehaviour(RESOURCE_PRIORITY_BEHAVIOUR behaviour);

            /**
             * Sets the blacklist for files to exclude as Resources.
             * Each string is expected to be a file extension including the '.'.
             *
             * \param[in] blacklist Container of file extensions to exclude.
             */
            void setSourceBlacklist(std::list<std::string> const& blacklist);

            /**
             * Sets the expected name of the source directories to explore for resource files.
             *
             * All directories underneath the application are explored, and those
             * whose name matches the specified directory name will be cataloged.
             *
             * Default is "Resources"
             *
             * \param[in] directory Name of resource directories
             */
            void setSourceDirectory(std::string const& directory);

        protected:

        private:
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