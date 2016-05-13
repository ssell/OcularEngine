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
            : Core::AResourceLoader(".obj", Core::ResourceType::Multi)
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

            bool result = true;

            OBJParser parser;
            OBJState* state = parser.getOBJState();

            if(parser.parseOBJFile(file.getFullPath()) == OBJParser::Result::Success)
            {
                std::vector<OBJGroup const*> groups;
                state->getGroups(groups);

                for(auto iter = groups.begin(); iter != groups.end(); ++iter)
                {
                    Core::Resource* mesh = nullptr;
                    createMesh(mesh, (*iter), state);

                    if(mesh)
                    {
                        mesh->setSourceFile(file);
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

        void ResourceLoader_OBJ::createMesh(Core::Resource* resource, OBJGroup const* group, OBJState const* state) const
        {
            Mesh* mesh = new Mesh();

            //------------------------------------------------------------
            // Calculate the amount of vertices/indices and reserve space for them

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            uint32_t numTris = group->faces.size();

            if(numTris > 0)
            {
                if(group->faces[0].group3.indexSpatial != -1)
                {
                    // The faces in this OBJ were written as quads
                    numTris *= 2;
                }

                vertices.reserve(numTris * 3);
                indices.reserve(numTris * 3);

                //--------------------------------------------------------
                // Populate the vertices container

                for(auto faceIter = group->faces.begin(); faceIter != group->faces.end(); ++faceIter)
                {
                    
                }

                //--------------------------------------------------------
                // Populate the indices container

            }

            //------------------------------------------------------------

            resource = mesh;
        }

        void ResourceLoader_OBJ::addFace(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, OBJFace const* face, OBJState const* state) const
        {
            Vertex vert0;
            Vertex vert1;
            Vertex vert2;

            auto spatial = state->getSpatialData();
            auto texture = state->getTextureData();
            auto normal = state->getNormalData();

            if(face->group0.indexSpatial >= 0)
            {
                
            }

            if(face->group3.indexSpatial == -1)
            {
                
            }
        }

        void ResourceLoader_OBJ::faceToVertex(Vertex& vertex, OBJVertexGroup const& group, OBJState const* state) const
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}