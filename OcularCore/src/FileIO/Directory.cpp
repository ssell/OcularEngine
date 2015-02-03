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

#include "FileIO/Directory.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/foreach.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------

        Directory::Directory(std::string const path)
            : File(path)
        {
            
        }

        Directory::Directory()
        {

        }

        Directory::~Directory()
        {

        }

        //----------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------

        std::vector<Directory> Directory::getChildDirectories() const
        {
            return m_ChildDirectories;
        }

        std::vector<File> Directory::getChildFiles() const
        {
            return m_ChildFiles;
        }

        void Directory::delve(bool const recursive)
        {
            if((m_IsDirectory) && (!m_IsSymLink))
            {
                boost::filesystem::path directory(m_FullPath);
                boost::filesystem::directory_iterator dirIter(directory);
                boost::filesystem::directory_iterator eod;

                BOOST_FOREACH(boost::filesystem::path const &path, std::make_pair(dirIter, eod))
                {
                    if(boost::filesystem::is_regular_file(path))
                    {
                        m_ChildFiles.push_back(File(path.string()));
                    }
                    else if(boost::filesystem::is_directory(path))
                    {
                        m_ChildDirectories.push_back(Directory(path.string()));
                    }
                }

                if(recursive)
                {
                    for(unsigned i = 0; i < m_ChildDirectories.size(); i++)
                    {
                        m_ChildDirectories[i].delve(true);
                    }
                }
            }
        }

        //----------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------

        //----------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------
    }
}