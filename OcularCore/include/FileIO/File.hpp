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
#ifndef __H__OCULAR_CORE_FILEIO_FILE__H__
#define __H__OCULAR_CORE_FILEIO_FILE__H__

#include <string>

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
         * \class File
         */
        class File
        {
        public:

            /**
             * Providing an empty string sets the current path to that of the current working directory.
             */
            File(std::string const fullPath = "");
            ~File();

            /**
            * Sets the path to the file object.
            */
            void setPath(std::string const fullPath);

            /**
             * Refreshes all information about the file.
             */
            void refresh();

            /**
             * Returns whether the object (file, directory, or symlink) at the specified path exists.
             */
            bool exists() const;

            /**
             * Returns whether the file at the specified path can be read from.
             */
            bool canRead() const;

            /**
             * Returns whether the file at the specified path can be written to.
             */
            bool canWrite() const;

            /**
             * Returns whether the object at the specified path is a file.
             */
            bool isFile() const;

            /**
            * Returns whether the object at the specified path is a directory.
            */
            bool isDirectory() const;

            /**
             * Returns whether the object at the specified path is a symbolic link.
             */
            bool isSymLink() const;

            /**
             * Returns whether the specified path is an absolute path.
             */
            bool isAbsolute() const;

            /** 
             * Returns the size of the file in bytes.
             */
            unsigned getSize() const;

            /**
             * Returns the full specified path of the file. Example:<br/><br/>
             *
             * <pre>
             *    /path/to/file/AFile.txt
             * </pre><br/>
             *
             * Returns "/path/to/file/AFile.txt"
             */
            std::string getFullPath() const;

            /**
             * Returns the name of the file. Example:<br/><br/>
             *
             * <pre>
             *    /path/to/file/AFile.txt
             * </pre><br/>
             *
             * Returns "AFile"
             */
            std::string getName() const;

            /**
            * Returns the extension of the file. Example:<br/><br/>
            *
            * <pre>
            *    /path/to/file/AFile.txt
            * </pre><br/>
            *
            * Returns ".txt"
            */
            std::string getExtension() const;

            /**
            * Returns the directory path of the file. Example:<br/><br/>
            *
            * <pre>
            *    /path/to/file/AFile.txt
            * </pre><br/>
            *
            * Returns "/path/to/file"
            */
            std::string getDirectory() const;

            /**
             * Returns the epoch time (in seconds) of the last write action to the file.
             */
            time_t getLastModifiedTime() const;

            /**
             * Ensures that all path-separators are the same. <br/>
             *
             * On Windows, the '\' separator is used. <br/>
             * On Linux-based systems, the '/' separator is used. 
             */
            void formatForSystem();

            /**
             * Attempts to create the file if it does not already exist.
             *
             * \param[in] createDirectories If TRUE, creates all necessary parent directories that do not already exist.
             * \return bool TRUE if successful
             */
            virtual bool create(bool createDirectories = false);

        protected:

            bool m_IsReal;
            bool m_IsReadable;
            bool m_IsWritable;
            bool m_IsFile;
            bool m_IsDirectory;
            bool m_IsSymLink;
            bool m_IsAbsolute;

            unsigned m_FileSize;

            std::string m_FullPath;
            std::string m_Name;
            std::string m_Extension;
            std::string m_Directory;

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