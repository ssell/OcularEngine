/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Resources/ResourceSaver.hpp"
#include "Utilities/EndianOps.hpp"
#include <fstream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTOR
        //----------------------------------------------------------------------------------

        AResourceSaver::AResourceSaver(std::string const& extension, ResourceType type)
            : m_SupportedExtension(extension),
              m_Type(type)
        {

        }

        AResourceSaver::~AResourceSaver()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        std::string AResourceSaver::getSupportedFileType() const 
        {
            return m_SupportedExtension;
        }

        bool AResourceSaver::saveResource(Resource* resource, File const& file)
        {
            return false;
        }

        ResourceType AResourceSaver::getResourceType() const
        {
            return m_Type;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool AResourceSaver::writeFile(Core::File const& file, std::vector<unsigned char> buffer, Endianness fileEndianness)
        {
            bool result = false;

            std::ofstream outStream(file.getFullPath(), std::ios_base::out | std::ios_base::binary);

            if(outStream.is_open())
            {
                // We can write to the file. First perform the endian conversion.

                for(unsigned i = 0; i < buffer.size(); i++)
                {
                    Utils::EndianOps::convert(Endianness::Native, fileEndianness, buffer[i]);
                }

                outStream.write(reinterpret_cast<char*>(&buffer[0]), buffer.size());
                outStream.close();

                result = true;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}