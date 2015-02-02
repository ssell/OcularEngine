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

#include <fstream>

#include "FileIO/File.hpp"
#include "boost/filesystem/operations.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        File::File(std::string const path)
        {
            m_FullPath = path;
            m_IsReal = false;
            m_IsReadable = false;
            m_IsWritable = false;
            m_IsFile = false;
            m_IsDirectory = false;
            m_IsSymLink = false;
            m_IsAbsolute = false;
            m_FileSize = 0;

            refresh();
        }

        File::File()
        {
            m_IsReal = false;
            m_IsReadable = false;
            m_IsWritable = false;
            m_IsFile = false;
            m_IsDirectory = false;
            m_IsSymLink = false;
            m_IsAbsolute = false;
            m_FileSize = 0;
        }

        File::~File()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void File::setPath(std::string const path)
        {
            m_FullPath = path;
            refresh();
        }

        void File::refresh()
        {
            boost::filesystem::path file(m_FullPath.c_str());

            m_IsReal = boost::filesystem::exists(file);

            if(m_IsReal)
            {
                m_IsFile = boost::filesystem::is_regular_file(file);
                m_IsDirectory = boost::filesystem::is_directory(file);
                m_IsSymLink = boost::filesystem::is_symlink(file);
                m_IsAbsolute = file.is_absolute();

                if(m_IsFile)
                {
                    m_FileSize = static_cast<unsigned>(boost::filesystem::file_size(file));

                    // Readable?
                    std::ifstream inStream(m_FullPath);
                    m_IsReadable = inStream.good();
                    inStream.close();

                    // Writable?
                    std::ofstream outStream(m_FullPath, std::ios_base::app);
                    m_IsWritable = outStream.good();
                    outStream.close();

                    // Break up path
                    m_Extension = file.extension().string();
                    m_Name = file.filename().string();
                    m_Name = m_Name.substr(0, m_Name.find(m_Extension));  // Remove the extension from the name
                    m_Directory = file.remove_filename().string();
                }
            }
        }

        bool File::exists() const
        {
            return m_IsReal;
        }

        bool File::canRead() const
        {
            return m_IsReadable;
        }

        bool File::canWrite() const
        {
            return m_IsWritable;
        }

        bool File::isFile() const
        {
            return m_IsFile;
        }

        bool File::isDirectory() const
        {
            return m_IsDirectory;
        }

        bool File::isSymLink() const
        {
            return m_IsSymLink;
        }

        bool File::isAbsolute() const
        {
            return m_IsAbsolute;
        }

        unsigned File::getSize() const
        {
            return m_FileSize;
        }

        std::string File::getFullPath() const
        {
            return m_FullPath;
        }

        std::string File::getName() const
        {
            return m_Name;
        }

        std::string File::getExtension() const
        {
            return m_Extension;
        }

        std::string File::getDirectory() const
        {
            return m_Directory;
        }

        time_t File::getLastModifiedTime() const
        {
            time_t result = 0;

            if(m_IsFile)
            {
                boost::filesystem::path file(m_FullPath);
                result = boost::filesystem::last_write_time(file);
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