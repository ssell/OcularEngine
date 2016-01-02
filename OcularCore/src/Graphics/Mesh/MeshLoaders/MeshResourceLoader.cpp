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

#include "Graphics/Mesh/MeshLoaders/MeshResourceLoader.hpp"
#include "Graphics/Mesh/Mesh.hpp"

#include "Utilities/StringUtils.hpp"
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

                uint32_t numVertices = 0;
                uint32_t numIndices = 0;

                if(readFile(file, vertices, indices, numVertices, numIndices))
                {
                    if(createResource(resource, file, vertices, indices, numVertices, numIndices))
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
                    OcularLogger->error("Failed to parse the Resource file at '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("MeshResourceLoader", "loadResource"));
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool MeshResourceLoader::createResource(
            Core::Resource* &resource, 
            Core::File const& file, 
            std::vector<Graphics::Vertex> const& vertices, 
            std::vector<uint32_t> const& indices, 
            uint32_t const numVertices, 
            uint32_t const numIndices)
        {
            // We are either creating a brand new resource, or loading into memory a pre-existing one.
            // If mesh is NULL, then create a new one. Otherwise, make sure it is unloaded.
            // Then simply provide the vertex and index data to the mesh resource.

            bool result = false;

            if(resource == nullptr)
            {
                resource = new Mesh();
                resource->setSourceFile(file);
            }

            Mesh* mesh = dynamic_cast<Mesh*>(resource);

            if(mesh)
            {
                // Ensure not in memory
                if(mesh->isInMemory())
                {
                    OcularLogger->warning("Loading in a mesh resource that is already in memory", OCULAR_INTERNAL_LOG("MeshResourceLoader", "createResource"));
                    mesh->unload();
                }

                if(!Utils::StringUtils::isEqual(file.getFullPath(), mesh->getSourceFile().getFullPath()))
                {
                    OcularLogger->warning("Source file mismatch for pre-existing resource", OCULAR_INTERNAL_LOG("MeshResourceLoader", "createResource"));
                    mesh->setSourceFile(file);
                }

                VertexBuffer* vertexBuffer = OcularGraphics->createVertexBuffer();
                IndexBuffer* indexBuffer = OcularGraphics->createIndexBuffer();

                if(vertexBuffer)
                {
                    if(indexBuffer)
                    {
                        vertexBuffer->addVertices(vertices, numVertices);
                        
                        if(vertexBuffer->build())
                        {
                            indexBuffer->addIndices(indices, numIndices);

                            if(indexBuffer->build())
                            {
                                mesh->setVertexBuffer(vertexBuffer);
                                mesh->setIndexBuffer(indexBuffer);

                                result = true;
                            }
                            else
                            {
                                OcularLogger->error("Failed to build Index Buffer", OCULAR_INTERNAL_LOG("MeshResourceLoader", "createResource"));
                            }
                        }
                        else
                        {
                            OcularLogger->error("Failed to build Vertex Buffer", OCULAR_INTERNAL_LOG("MeshResourceLoader", "createResource"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Failed to allocate Index Buffer", OCULAR_INTERNAL_LOG("MeshResourceLoader", "createResource"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to allocate Vertex Buffer", OCULAR_INTERNAL_LOG("MeshResourceLoader", "createResource"));
                }
            }
            else
            {
                OcularLogger->error("Provided Resource is not a Mesh or is NULL", OCULAR_INTERNAL_LOG("MeshResourceLoader", "createResource"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}