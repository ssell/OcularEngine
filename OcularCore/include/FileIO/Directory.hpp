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
        class Directory
        {
        public:

            /**
             * \param[in] path Directory path
             * \note If an empty path is provided, the current working directory will be used.
             */
            Directory(std::string const path);
            Directory();

            ~Directory();

            /**
             * Sets the path to the file object.
             */
            void setPath(std::string const path);

            /**
            * \return Whether the object (file, directory, or symlink) at the specified path exists.
            */
            bool exists() const;

            /**
            * Returns whether the object at the specified path is a directory.
            */
            bool isDirectory() const;

            /**
            * \return Whether the specified path is an absolute path.
            */
            bool isAbsolute() const;

            /**
            * \return The full path of the directory (with no trailing slash).
            */
            std::string getFullPath() const;

            /**
             * \return The name of the directory.
             */
            std::string getName() const;

            /**
            * \return A collection of all immediate child directories.
            * \note delve must be called first or else the container will be empty.
            */
            std::vector<Directory> getChildDirectories() const;

            /**
            * \return A collection of all immediate child files.
            * \note delve must be called first or else the container will be empty.
            */
            std::vector<File> getChildFiles() const;

            /**
             * Populates the list of child directories and files.
             *
             * \param[in] recursive If TRUE, child directories are automatically explored.
             */
            void delve(bool const recursive = false);

        protected:

        private:

            File m_This;

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

//------------------------------------------------------------------------------------------

#endif