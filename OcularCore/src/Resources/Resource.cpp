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

#include "Resources/Resource.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Resource::Resource(File const& source)
            : m_SourceFile(source),
              m_Name(source.getName()),
              m_SizeInMemory(0),
              m_Type(ResourceType::Undefined)
        {

        }

        Resource::Resource()
            : m_SourceFile(File()),
              m_Name(""),
              m_SizeInMemory(0),
              m_Type(ResourceType::Undefined)
        {

        }

        Resource::~Resource()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        File Resource::getSourceFile() const 
        {
            return m_SourceFile;
        }

        void Resource::setSourceFile(File const& file)
        {
            m_SourceFile = file;
        }

        bool Resource::isInMemory() const
        {
            return m_IsInMemory;
        }

        uint64_t Resource::getSize() const
        {
            return m_SizeInMemory;
        }

        ResourceType Resource::getResourceType() const
        {
            return m_Type;
        }

        void Resource::forceLoad()
        {
            /// \todo Resources forceLoad
        }

        void Resource::setName(std::string const& name)
        {
            m_Name = name;
        }

        std::string const& Resource::getName() const
        {
            return m_Name;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}