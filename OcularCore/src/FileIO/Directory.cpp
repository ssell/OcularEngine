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

#include "FileIO/Directory.hpp"
#include "Utilities/StringRegistrar.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/foreach.hpp>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        OCULAR_REGISTER_TO_STRING(Directory, OCULAR_TO_STRING_LAMBDA
        {
            std::string result;

            if(raw)
            {
                Directory* file = void_cast<Directory*>(raw);

                if(file)
                {
                    result = file->getFullPath();
                }
            }

            return result;
        });

        OCULAR_REGISTER_FROM_STRING(Directory, OCULAR_FROM_STRING_LAMBDA
        {
            if(out)
            {
                Directory* result = void_cast<Directory*>(out); 

                if(result)
                {
                    result->setPath(str);
                }
            }
        });

        //----------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------

        Directory::Directory(std::string const path)
            : File(path)
        {
            
        }

        Directory::~Directory()
        {

        }

        //----------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------

        std::vector<Directory> Directory::getChildDirectories(bool recursive) const
        {
            std::vector<Directory> result = m_ChildDirectories;

            if(recursive)
            {
                for(auto iter = m_ChildDirectories.begin(); iter != m_ChildDirectories.end(); ++iter)
                {
                    std::vector<Directory> children = iter->getChildDirectories(true);
                    result.reserve(result.size() + children.size());
                    result.insert(result.end(), children.begin(), children.end());
                }
            }

            return result;
        }

        std::vector<File> Directory::getChildFiles(bool recursive) const
        {
            std::vector<File> result = m_ChildFiles;

            if(recursive)
            {
                for(auto iter = m_ChildDirectories.begin(); iter != m_ChildDirectories.end(); ++iter)
                {
                    std::vector<File> children = iter->getChildFiles(true);
                    result.reserve(result.size() + children.size());
                    result.insert(result.end(), children.begin(), children.end());
                }
            }

            return result;
        }

        void Directory::explore(bool const recursive)
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
                        m_ChildDirectories[i].explore(true);
                    }
                }
            }
        }

        bool Directory::create(bool createDirectories)
        {
            bool result = false;

            if((!m_IsReal) && (m_Name.find(":") == std::string::npos))
            {
                if((m_Directory.compare("/") != 0) && (m_Directory.compare("\\")))
                {
                    Directory parent(m_Directory);
                    parent.create(true);

                    boost::filesystem::create_directories(boost::filesystem::path(m_FullPath));
                }
            }

            return result;
        }

        //----------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------

        //----------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------
    }
}