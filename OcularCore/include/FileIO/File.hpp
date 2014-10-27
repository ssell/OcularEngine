/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

            File(std::string const fullPath);
            ~File();

            void refresh();

            bool exists() const;
            bool canRead() const;
            bool canWrite() const;
            bool isFile() const;
            bool isDirectory() const;
            bool isSymLink() const;

            unsigned getFileSize() const;

            std::string getFullPath() const;
            std::string getName() const;
            std::string getExtension() const;
            std::string getDirectory() const;

            time_t lastModifiedTime() const;

        protected:

        private:

            bool m_IsReal;
            bool m_IsReadable;
            bool m_IsWritable;
            bool m_IsFile;
            bool m_IsDirectory;
            bool m_IsSymLink;

            unsigned m_FileSize;

            std::string m_FullPath;
            std::string m_Name;         // todo
            std::string m_Extension;    // todo
            std::string m_Directory;    // todo
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