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

#include "Resources/ResourceLoader.hpp"

#include "OcularEngine.hpp"
#include "Utilities/StringOps.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTOR
        //----------------------------------------------------------------------------------

        AResourceLoader::AResourceLoader(std::string const& extension)
        {
            m_SupportedExtension = extension;
        }

        AResourceLoader::~AResourceLoader()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        std::string AResourceLoader::getSupportedFileType() const 
        {
            return m_SupportedExtension;
        }

        bool AResourceLoader::loadResource(Resource* &resource, File const& file)
        {
            return false;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool AResourceLoader::isFileValid(Core::File const& file) const
        {
            bool result = false;

            if(file.exists())
            {
                if(file.canRead())
                {
                    if(Utils::StringOps::isEqual(file.getExtension(), m_SupportedExtension, true))
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Resource file '", file.getFullPath(), "' is an unsupported file type; Expected '", m_SupportedExtension, "'", OCULAR_INTERNAL_LOG("TextureResourceLoader", "isFileValid"));
                    }
                }
                else
                {
                    OcularLogger->error("Unable to read resource file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("TextureResourceLoader", "isFileValid"));
                }
            }
            else
            {
                OcularLogger->error("Specified resource file '", file.getFullPath(), "' does not exist", OCULAR_INTERNAL_LOG("TextureResourceLoader", "isFileValid"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}