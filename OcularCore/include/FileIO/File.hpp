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

namespace Ocular
{
    namespace Core
    {
        /**
         * \class File
         */
        class File
        {
        public:

            File(std::string fullPath);
            ~File();

            bool exists();
            bool canRead();
            bool canWrite();
            bool isFile();
            bool isDirectory();
            bool create(bool createDirs = false);

            std::string getFullPath();
            std::string getName();
            std::string getExtension();
            std::string getDirectory();

        protected:

        private:

            std::string m_FullPath;
            std::string m_Name;
            std::string m_Extension;
            std::string m_Directory;
        };
    }
}

//------------------------------------------------------------------------------------------

#endif