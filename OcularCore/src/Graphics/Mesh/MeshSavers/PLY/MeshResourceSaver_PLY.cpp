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

#include "Graphics/Mesh/MeshSavers/PLY/MeshResourceSaver_PLY.hpp"
#include "Resources/ResourceSaverRegistrar.hpp"
#include <algorithm>

OCULAR_REGISTER_RESOURCE_SAVER(Ocular::Graphics::MeshResourceSaver_PLY)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MeshResourceSaver_PLY::MeshResourceSaver_PLY()
            : MeshResourceSaver(".ply")
        {
        
        }

        MeshResourceSaver_PLY::~MeshResourceSaver_PLY()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool MeshResourceSaver_PLY::saveFile(Core::File const& file, VertexBuffer const* vertexBuffer, IndexBuffer const* indexBuffer)
        {
            bool result = false;

            if(vertexBuffer && indexBuffer)
            {
                const uint32_t numVertices = vertexBuffer->getNumVertices();
                const uint32_t numIndices  = indexBuffer->getNumIndices();
                const uint32_t numFaces    = numIndices / 3;

                if(validateGeometryCount(numVertices, numIndices, numFaces))
                {
                    std::ofstream stream(file.getFullPath(), std::ios_base::out);

                    if(stream.is_open())
                    {
                        if(writeHeader(stream, numVertices, numFaces))
                        {
                            if(writeBody(stream, vertexBuffer, indexBuffer))
                            {
                                result = true;
                            }
                            else
                            {
                                OcularLogger->error("Failed to write file body", OCULAR_INTERNAL_LOG("MeshResourceSaver_PLY", "saveFile"));
                            }
                        }
                        else
                        {
                            OcularLogger->error("Failed to write file header", OCULAR_INTERNAL_LOG("MeshResourceSaver_PLY", "saveFile"));
                        }

                        stream.close();
                    }
                    else
                    {
                        OcularLogger->error("Failed to open file '", file.getFullPath(), "' for write", OCULAR_INTERNAL_LOG("MeshResourceSaver_PLY", "saveFile"));
                    }
                }
            }

            return result;
        }

        bool MeshResourceSaver_PLY::validateGeometryCount(uint32_t const numVertices, uint32_t const numIndices, uint32_t const numFaces) const
        {
            bool result = true;

            if(numVertices < 3)
            {
                result = false;
                OcularLogger->error("Invalid number of vertices: ", numVertices, ". Mesh must have minimum of 3 vertices", OCULAR_INTERNAL_LOG("MeshResourceSaver_PLY", "validateGeometryCount"));
            }

            if(numIndices < 3)
            {
                result = false;
                OcularLogger->error("Invalid number of indices: ", numIndices, ". Mesh must have minimum of 3 indices", OCULAR_INTERNAL_LOG("MeshResourceSaver_PLY", "validateGeometryCount"));
            }
            else if((numIndices % 3))
            {
                result = false;
                OcularLogger->error("Invalid number of indices: ", numIndices, ". Mesh must have a multiple of 3 indices", OCULAR_INTERNAL_LOG("MeshResourceSaver_PLY", "validateGeometryCount"));
            }

            if(numFaces < 1)
            {
                result = false;
                OcularLogger->error("Invalid number of faces: ", numFaces, ". Mesh must have minimum of 1 face", OCULAR_INTERNAL_LOG("MeshResourceSaver_PLY", "validateGeometryCount"));
            }

            return result;
        }

        bool MeshResourceSaver_PLY::writeHeader(std::ofstream& stream, uint32_t numVertices, uint32_t numFaces) const
        {
            bool result = true;

            stream << 
                "ply\n"
                "format ascii 1.0\n"
                "comment Created by Ocular Engine\n"
                "element vertex " << numVertices << "\n"
                "property float x\n"
                "property float y\n"
                "property float z\n"
                "property float nx\n"
                "property float ny\n"
                "property float nz\n"
                "element face " << numFaces << "\n"
                "property list uchar uint vertex_indices\n"
                "end_header\n";

            return result;
        }

        bool MeshResourceSaver_PLY::writeBody(std::ofstream& stream, VertexBuffer const* vertexBuffer, IndexBuffer const* indexBuffer) const
        {
            bool result = true;

            std::vector<Vertex> const vertices = vertexBuffer->getVertices();
            std::vector<uint32_t> const indices = indexBuffer->getIndices();

            for(uint32_t i = 0; i < vertices.size(); i++)
            {
                stream << vertices[i].position.x << " " << vertices[i].position.y << " " << vertices[i].position.z << " " 
                       << vertices[i].normal.x << " " << vertices[i].normal.y << " " << vertices[i].normal.z << "\n";
            }

            for(uint32_t i = 0; i < indices.size(); i += 3)
            {
                stream << "3 " << indices[i] << " " << indices[i + 1] << " " << indices[i + 2] << "\n";
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}