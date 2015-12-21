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

#include "Graphics/Mesh/MeshLoaders/MeshResourceLoader.hpp"
#include "Graphics/Mesh/Mesh.hpp"

#include "OcularEngine.hpp"

#include <fstream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MeshResourceLoader::MeshResourceLoader(std::string const& extension)
            : Core::AResourceLoader(extension)
        {
        
        }

        MeshResourceLoader::~MeshResourceLoader()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool MeshResourceLoader::loadResource(Core::Resource* &resource, Core::File const& file)
        {
            bool result = false;

            if(isFileValid(file))
            {
                std::vector<Graphics::Vertex> vertices;
                std::vector<uint32_t> indices;

                if(readFile(file, vertices, indices))
                {
                    if(createResource(resource, file, vertices, indices))
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Failed to create Resource", OCULAR_INTERNAL_LOG("MeshResourceLoader", "loadResource"));
                    }
                }
                else
                {
                    OcularLogger->error("Resource file at '", file.getFullPath(), "' is invalid", OCULAR_INTERNAL_LOG("MeshResourceLoader", "loadResource"));
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool MeshResourceLoader::createResource(Core::Resource* &resource, Core::File const& file, std::vector<Graphics::Vertex> const& vertices, std::vector<uint32_t> const& indices)
        {
            // We are either creating a brand new resource, or loading into memory a pre-existing one.

            bool result = false;

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}