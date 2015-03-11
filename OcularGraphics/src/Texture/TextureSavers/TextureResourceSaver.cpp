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

#include "Texture/TextureSavers/TextureResourceSaver.hpp"
#include "Texture/Texture2D.hpp"
#include "Utilities/StringUtils.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceSaver::TextureResourceSaver(std::string const& extension)
            : Core::AResourceSaver(extension)
        {
        
        }

        TextureResourceSaver::~TextureResourceSaver()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceSaver::saveResource(Core::Resource* resource, Core::File const& file)
        {
            bool result = false;

            Core::File tempFile = file;

            if(isFileValid(tempFile))
            {
            
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceSaver::isFileValid(Core::File& file)
        {
            bool result = false;

            if(file.exists())
            {
                if(file.canWrite())
                {
                    if(Utils::StringUtils::isEqual(file.getExtension(), m_SupportedExtension, true))
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Resource file '", file.getFullPath(), "' is an unsupported file type; Expected '", m_SupportedExtension, "'", OCULAR_INTERNAL_LOG("TextureResourceSaver", "isFileValid"));
                    }
                }
                else
                {
                    OcularLogger->error("Unable to write to file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("TextureResourceSaver", "isFileValid"));
                }
            }
            else
            {
                if(file.create(true))
                {
                    result = isFileValid(file);
                }
                else 
                {
                    OcularLogger->error("Specified file destination '", file.getFullPath(), "' does not exist and unable to create matching file", OCULAR_INTERNAL_LOG("TextureResourceSaver", "isFileValid"));
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}