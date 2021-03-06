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
#ifndef __H__OCULAR_CORE_FILEIO_DIRECTORY__H__
#define __H__OCULAR_CORE_FILEIO_DIRECTORY__H__

#include <string>
#include <vector>

#include "File.hpp"

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
         * \class Directory
         */
        class Directory : public File
        {
        public:

            /**
             * \param[in] path Directory path
             * \note If an empty path is provided, the current working directory will be used.
             */
            Directory(std::string const path = "");
            ~Directory();

            /**
             * \note explore must be called first or else the container will be empty.
             * \param[in] recursive If true, returned list also contains all files belonging to child directories.
             * \return A collection of all immediate child directories.
             */
            std::vector<Directory> getChildDirectories(bool recursive = false) const;

            /**
             * \note explore must be called first or else the container will be empty.
             * \param[in] recursive If true, returned list also contains all files belonging to child directories.
             * \return A collection of all immediate child files.
             */
            std::vector<File> getChildFiles(bool recursive = false) const;

            /**
             * Populates the list of child directories and files. <br/>
             *
             * If recursive is true, then this Directory's child directories and files will
             * be filled with ALL child directories and files, no matter how deeply nested.
             *
             * \param[in] recursive If TRUE, child directories are automatically explored.
             */
            void explore(bool const recursive = false);

            /**
             * Attempts to create the directory if it does not already exist.
             *
             * \param[in] createDirectories If TRUE, creates all necessary parent directories that do not already exist.
             * \return bool TRUE if successful
             */
            virtual bool create(bool createDirectories = false);

        protected:

        private:

            std::vector<Directory> m_ChildDirectories;
            std::vector<File> m_ChildFiles;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

OCULAR_REGISTER_TYPE_CUSTOM(Ocular::Core::Directory, "Directory");

//------------------------------------------------------------------------------------------

#endif