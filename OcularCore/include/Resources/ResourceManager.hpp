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

#pragma once
#ifndef __H__OCULAR_RESOURCES_RESOURCE_MANAGER__H__
#define __H__OCULAR_RESOURCES_RESOURCE_MANAGER__H__

#include <memory>
#include <list>
#include <string>
#include <unordered_map>

#include "ResourceDetails.hpp"
#include "ResourceMemoryDetails.hpp"
#include "ResourcePriorityBehaviour.hpp"
#include "ResourceExplorer.hpp"
#include "ResourceLoader.hpp"
#include "ResourceLoaderManager.hpp"
#include "ResourceSaver.hpp"
#include "ResourceSaverManager.hpp"
#include "ResourceDefaults.hpp"

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
         *     Texture* texture = nullptr;
         *     Resource* resource = OcularResources->getResource("Textures/Terrain/GrassGreen");
         *
         *     if(resource->getResourceType() == ResourceType::Texture)
         *     {
         *         texture = dynamic_cast<Texture*>(resource);
         *
         *         if(texture)
         *         {
         *             // ...
         *         }
         *     }
         *
         * or:
         *
         *     Texture* texture = OcularResources->getResource<Texture>("Textures/Terrain/GrassGreen");
         *
         *     if(texture)
         *     {
         *         // ...
         *     }
         *
         * The returned Resource pointer will always be valid as long as the ResourceManager
         * instance exists (so the life of the Engine). But, the internal data of the
         * resource itself may not be valid. So before use of the Resource itself, one 
         * should verify that the Resource is loaded. Example:
         *
         *     if(!texture->isInMemory())
         *     {
         *         texture->forceLoad();
         *     }
         *
         * Note that a retrieved texture (getResource) is guaranteed to be fully loaded into
         * memory (at least until the next getResource request).
         */
        class ResourceManager 
        {
        public:

            ResourceManager();
            ~ResourceManager();

            //----------------------------------------

            /**
             *
             */
            void initialize();

            /**
             *
             */
            void initializeDefaultResources();

            /**
             *
             */
            void unloadAllResources();

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
             * Adds the Resource to the ResourceManager. The manager will assume ownership
             * of the Resource and handle loading/unloading/destruction of it.
             *
             * \param[in] name       Mapping name to associate with the Resource. Must be 
             *                       unique and not already in use by a pre-existing Resource.
             * \param[in] sourceFile File to load the Resource from. File may be in use by
             *                       multiple resources, such as with a MultiResource.
             * \param[in] resource   The Resource to transfer ownership of.
             * \param[in] type
             *
             * \return Returns FALSE if the specified path is already occupied.
             */
            bool addResource(std::string const& name, File const& sourceFile, Resource* resource, ResourceType type);

            /**
             * Retrieves the total amount of memory currently 
             * in use by the Resource Manager.
             *
             * \return
             */
            ResourceMemoryDetails getMemoryUsage();

            /**
             * Returns the resource with the specified mapping name.
             * The resource is loaded in memory if it is not already.
             *
             * \param[in] path Mapping name of the Resource. Relative path from Resources folder, sans extension.
             * \return Pointer to the resource; Returns nullptr if failed to fetch resource.
             */
            Resource* getResource(std::string const& path);

            /**
             * Returns the resource at the specified path if it exists. 
             * The resource is loaded in memory if it is not already.
             *
             * \param[in] path Resource path and name
             * \return Pointer to the resource; Returns nullptr if failed to fetch resource.
             */
            template<class T> T* getResource(std::string const& path) { return dynamic_cast<T*>(getResource(path)); };

            /**
             * Returns the pre-built 'empty' Resource for the specified type.
             * \param[in] type
             */
            Resource* getEmptyResource(ResourceType type);

            /**
             * Returns the pre-built 'missing' Resource for the specified type.
             * \param[in] type
             */
            Resource* getMissingResource(ResourceType type);

            /**
             * Returns the file associated with the specified resource mapping name.
             *
             * For example, the mapping name
             *
             *     Textures/Grass
             *
             * May return the file located at
             *
             *     /path/to/project/Resources/Textures/Grass.png
             *
             * \param[in] path
             * \return If there is no tracked Resource with the specified mapping name,
             *         then the current directory (default File value) will be returned.
             */
            File getResourceFile(std::string const& path) const;

            /**
             * Returns the mapping name associated with the specified file.
             *
             * For example, the file located at 
             *
             *     /path/to/project/Resources/Textures/Grass.png
             *
             * Would return
             *
             *     Textures/Grass
             *
             * \param[in] file
             * \return If there is no tracked Resource at the specified file, then
             *         an empty string will be returned.
             */
            std::string getResourceMappingName(File const& file) const;

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
             * \param[in] file Resource file to load
             * \return A new Resource object; Returns NULL if the file does not exist or unable to load it.
             */
            Resource* loadUnmanagedFile(File const& file);

            /**
             * Attempts to save the provided Resource to the specified file on disk.
             * 
             * In order for the Resource to be saved, all of the following must be true:
             *
             *   - The provided Resource must not be NULL
             *   - The provided Resource must be currently loaded in memory 
             *   - A AResourceSaver must be registered to the manager that supports the same
             *     file type as the specified output file. This may be verified using isFileTypeSupported()
             *   - The file and it's parent directories do not have to exist at the time of the method call, 
             *     but they must be valid and the engine must have proper write access to create them.
             * 
             * \param[in] resource Resource object to be saved to disk
             * \param[in] file     A valid resource file
             *
             * \return TRUE if the Resource was successfully saved to disk.
             */
            bool saveResource(Resource* resource, File const& file);

            /**
             * Sets the maximum amount of memory (in bytes) allocated for Resources.
             * This value is clamped if it exceeds the amount of memory available to the system.
             *
             * \param[in] maxMemory Amount of memory to allocate to Resources
             */
            void setMemoryLimit(uint64_t maxMemory);

            /**
             * Sets the priority behaviour when determining which Resource to unload when 
             * the memory limit has been reached.
             *
             * Default is LeastRecentlyUsed.
             *
             * \param behaviour Priority behaviour to use.
             */
            void setPriorityBehaviour(ResourcePriorityBehaviour behaviour);

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
             * \note To update the resource mappings, forceSourceRefresh must be called.
             * \param[in] directory Name of resource directories
             */
            void setSourceDirectory(std::string const& directory);

            /**
             * Returns the directory path in which resources are expected.
             */
            std::string const& getSourceDirectory() const;
            
            /**
             * Registers the ResourceLoader
             *
             * \param[in] loader
             */
            void registerResourceLoader(std::shared_ptr<AResourceLoader> loader);
            
            /**
             * Registers the ResourceSaver
             *
             * \param[in] saver
             */
            void registerResourceSaver(std::shared_ptr<AResourceSaver> loader);

            /**
             * \return Total number of tracked resources. This value does not represent the number of Resources in memory.
             */
            unsigned getNumberOfResources() const;

            /**
             * \return Total number of registered Resource Loaders.
             */
            unsigned getNumberOfResourceLoaders() const;

            /**
             * \return Total number of registered Resource Savers.
             */
            unsigned getNumberOfResourceSavers() const;

            /**
             * Checks if the specified resource extension is supported.
             *
             * \param[in]  extension File extension to check for support
             * \param[out] canLoad   Is set to TRUE if the specified file extension has an associated AResourceLoader and can be loaded.
             * \param[out] canSave   Is set to TRUE if the specified file extension has an associated AResourceSaver and can be saved.
             */
            void isFileTypeSupported(std::string const& extension, bool& canLoad, bool& canSave) const;

            /**
             * Finds all resources of the specified type, and returns a vector containing their mapping names.
             *
             * \param[in]  type
             * \param[out] resources
             */
            void getResourcesOfType(ResourceType type, std::vector<std::string>& resources);

        protected:

            /**
             * Checks to ensure that the amount of memory currently in use does not
             * exceed the maximum memory limit. If limit is surpassed, then it frees
             * up space until back below the limit.
             */
            void freeMemorySpace();

            /**
             * Frees memory based on usage frequency.
             */
            ResourceDetails* findLeastFrequentlyUsed();

            /**
             * Frees memory based on when the resource was last used.
             */
            ResourceDetails* findLeastRecentlyUsed();

            /**
             * Frees memory based on size.
             */
            ResourceDetails* findSizeAscending();

            /**
             * Frees memory based on size.
             */
            ResourceDetails* findSizeDescending();

        private:
            
            std::unordered_map<std::string, std::shared_ptr<ResourceDetails>> m_ResourceMap;
            std::unordered_map<std::string, File> m_FileMap;

            ResourceExplorer      m_ResourceExplorer;
            ResourceLoaderManager m_ResourceLoaderManager;
            ResourceSaverManager  m_ResourceSaverManager;
            ResourceMemoryDetails m_MemoryDetails;
            ResourceDefaults      m_ResourceDefaults;

            ResourcePriorityBehaviour m_PriorityBehaviour;

            uint64_t m_MemoryLimit;

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