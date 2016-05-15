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

#include "Graphics/Mesh/MeshLoaders/OBJ/ResourceLoader_OBJ.hpp"
#include "Graphics/Mesh/Mesh.hpp"
#include "Resources/MultiResource.hpp"

#include "Resources/ResourceLoaderRegistrar.hpp"
#include "OcularEngine.hpp"

#include "objparser/OBJParser.hpp"

#include <fstream>
#include <map>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::ResourceLoader_OBJ)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceLoader_OBJ::ResourceLoader_OBJ()
            : Core::AResourceLoader(".obj", Core::ResourceType::Multi),
              m_CurrVertexIndex(0),
              m_CurrIndexIndex(0),
              m_CurrState(nullptr)
        {
        
        }

        ResourceLoader_OBJ::~ResourceLoader_OBJ()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool ResourceLoader_OBJ::loadResource(Core::Resource* &resource, Core::File const& file)
        {
            // Requested to the load the entire OBJ as a MultiResource instance

            //------------------------------------------------------------
            // Create or Unload the MultiResource

            bool result = true;

            if(resource == nullptr)
            {
                resource = new Core::MultiResource();
                resource->setSourceFile(file);
            }
            else if(resource->isInMemory())
            {
                resource->unload();
            }

            Core::MultiResource* multiResource = dynamic_cast<Core::MultiResource*>(resource);
            
            //------------------------------------------------------------
            // Attempt to parse the file

            OBJParser parser;
            m_CurrState = parser.getOBJState();

            if(parser.parseOBJFile(file.getFullPath()) == OBJParser::Result::Success)
            {
                std::vector<OBJGroup const*> groups;
                m_CurrState->getGroups(groups);

                //--------------------------------------------------------
                // Iterate over all groups and create a mesh for each

                for(auto iter = groups.begin(); iter != groups.end(); ++iter)
                {
                    OBJGroup const* group = (*iter);

                    if(group)
                    {
                        Core::Resource* mesh = nullptr;
                        createMesh(mesh, group);

                        if(mesh)
                        {
                            mesh->setSourceFile(file);
                        }

                        multiResource->addSubResource(mesh, group->name);
                    }
                }
            }
            else
            {
                OcularLogger->error("Failed to parse file '", file.getFullPath(), "' with error: ", parser.getLastError(), OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "loadResource"));
                result = false;
            }

            return result;
        }

        bool ResourceLoader_OBJ::loadSubResource(Core::Resource* &resource, Core::File const& file, std::string const& mappingName)
        {
            // Requested to load an individual mesh contained within the OBJ

            bool result = false;

            return result;
        }

        bool ResourceLoader_OBJ::exploreResource(Core::File const& file)
        {
            /**
             * Explores the OBJ file. For each 'group' tag found that is not 'default' it
             * will add a new Resource mapping path to the global ResourceManager.
             */

            bool result = false;

            std::fstream instream(file.getFullPath(), std::fstream::in);

            if(instream.is_open())
            {
                std::map<std::string, bool> nameMap;
                const std::string mappingName = OcularResources->getResourceMappingName(file);

                if(mappingName.size() > 0)
                {
                    std::string line;

                    while(std::getline(instream, line))
                    {
                        if(line[0] == 'g')
                        {
                            std::vector<std::string> tokens;
                            Utils::String::Split(line, ' ', tokens);

                            for(auto iter = tokens.begin() + 1; iter != tokens.end(); ++iter)
                            {
                                if(!Utils::String::IsEqual((*iter), "default"))
                                {
                                    nameMap[(*iter)] = true;
                                }
                            }
                        }
                    }

                    for(auto name : nameMap)
                    {
                        // Add each name to the main resource manager
                        OcularResources->addResource((mappingName + "/" + name.first), file, nullptr, Core::ResourceType::Mesh);
                    }

                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to find matching Resource mapping name for file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "exploreResource"));
                }

                instream.close();
            }
            else
            {
                OcularLogger->error("Failed to open file at '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "exploreResource"));
            }

            return result;
        }


        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool ResourceLoader_OBJ::isFileValid(Core::File const& file) const
        {
            bool result = true;

            return result;
        }

        void ResourceLoader_OBJ::createMesh(Core::Resource* resource, OBJGroup const* group)
        {
            Mesh* mesh = new Mesh();

            //------------------------------------------------------------
            // Calculate the amount of vertices/indices and reserve space for them

            Math::Vector3f min = Math::Vector3f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            Math::Vector3f max = Math::Vector3f(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());;

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            uint32_t numFaces = static_cast<uint32_t>(group->faces.size());

            //------------------------------------------------------------
            // Populate the vector of vertices and indices

            if(numFaces > 0)
            {
                if(group->faces[0].group3.indexSpatial >= 0)
                {
                    // Faces are triangles
                    vertices.resize(numFaces * 3);    // 3 unique vertices per face
                    indices.resize(numFaces * 3);     // 3 indices to map face to triangle
                }
                else
                {
                    // Faces are quads
                    vertices.resize(numFaces * 4);    // 4 unique vertices per face
                    indices.resize(numFaces * 6);     // 6 unique indices to map face to two triangles
                }

                for(std::vector<OBJFace>::size_type i = 0; i < group->faces.size(); i++)
                {
                    addFace(&group->faces[i], vertices, indices, min, max);
                }
            }

            //------------------------------------------------------------
            // Pass vertices and indices to the Mesh

            auto vb = OcularGraphics->createVertexBuffer();
            auto ib = OcularGraphics->createIndexBuffer();

            vb->addVertices(vertices);
            ib->addIndices(indices);

            if(vb->build())
            {
                mesh->setVertexBuffer(vb);
            }
            else
            {
                OcularLogger->error("Failed to build Vertex Buffer", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "createMesh"));
            }

            if(ib->build())
            {
                mesh->setIndexBuffer(ib);
            }
            else
            {
                OcularLogger->error("Failed to build Index Buffer", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "createMesh"));
            }

            mesh->setMinMaxPoints(min, max);

            //------------------------------------------------------------

            resource = mesh;
        }

        void ResourceLoader_OBJ::addFace(
            OBJFace const* face, 
            std::vector<Vertex>& vertices, 
            std::vector<uint32_t>& indices, 
            Math::Vector3f& min, 
            Math::Vector3f& max)
        {
            faceToVertex(vertices, face->group0, min, max);
            faceToVertex(vertices, face->group1, min, max);
            faceToVertex(vertices, face->group2, min, max);

            if(face->group3.indexSpatial < 0)
            {
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 2);
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 1);
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 0);
            }
            else
            {
                // Convert the single quad face to two triangle faces

                faceToVertex(vertices, face->group3, min, max);

                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 3);
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 2);
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 1);
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 1);
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 0);
                indices[m_CurrIndexIndex++] = (m_CurrVertexIndex - 3);
            }
        }

        void ResourceLoader_OBJ::faceToVertex(std::vector<Vertex>& vertices, OBJVertexGroup const& group, Math::Vector3f& min, Math::Vector3f& max)
        {
            static const uint32_t VEC3SIZE = sizeof(float) * 3;
            static const uint32_t VEC2SIZE = sizeof(float) * 2;

            if(group.indexSpatial >= 0)
            {
                memcpy(&vertices[m_CurrVertexIndex].position, &(m_CurrState->getSpatialData()[group.indexSpatial]), VEC3SIZE);

                min.x = std::min(min.x, vertices[m_CurrVertexIndex].position.x);
                min.y = std::min(min.y, vertices[m_CurrVertexIndex].position.y);
                min.z = std::min(min.z, vertices[m_CurrVertexIndex].position.z);
            
                max.x = std::max(max.x, vertices[m_CurrVertexIndex].position.x);
                max.y = std::max(max.y, vertices[m_CurrVertexIndex].position.y);
                max.z = std::max(max.z, vertices[m_CurrVertexIndex].position.z);
            }

            if(group.indexTexture >= 0)
            {
                memcpy(&vertices[m_CurrVertexIndex].uv0, &(m_CurrState->getTextureData()[group.indexTexture]), VEC2SIZE);
            }

            if(group.indexNormal >= 0)
            {
                memcpy(&vertices[m_CurrVertexIndex].normal, &(m_CurrState->getTextureData()[group.indexNormal]), VEC3SIZE);
            }

            m_CurrVertexIndex++;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}