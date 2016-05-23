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
#include "Graphics/Material/Material.hpp"
#include "Resources/MultiResource.hpp"

#include "Resources/ResourceLoaderRegistrar.hpp"
#include "OcularEngine.hpp"

#include "objparser/OBJParser.hpp"

#include <fstream>
#include <utility>

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

            if(isFileValid(file))
            {
                if(resource == nullptr)
                {
                    resource = new Core::MultiResource();
                    resource->setSourceFile(file);
                    resource->setMappingName(OcularResources->getResourceMappingName(file));
                }
                else if(resource->isInMemory())
                {
                    resource->unload();
                }

                Core::MultiResource* multiResource = dynamic_cast<Core::MultiResource*>(resource);

                //--------------------------------------------------------
                // Attempt to parse the file

                OBJParser parser;
                m_CurrState = parser.getOBJState();

                if(parser.parseOBJFile(file.getFullPath()) == OBJParser::Result::Success)
                {
                    createMeshes(multiResource);
                    createMaterials(multiResource);
                }
                else
                {
                    OcularLogger->error("Failed to parse file '", file.getFullPath(), "' with error: ", parser.getLastError(), OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "loadResource"));
                    result = false;
                }
            }
            else
            {
                result = false;
            }

            return result;
        }

        bool ResourceLoader_OBJ::loadSubResource(Core::Resource* &resource, Core::File const& file, std::string const& mappingName)
        {
            // Requested to load an individual mesh contained within the OBJ
            
            bool result = true;

            if(isFileValid(file))
            {
                std::string parentName;
                std::string subName;

                splitParentSubNames(mappingName, parentName, subName);

                Core::MultiResource* parentResource = OcularResources->getResource<Core::MultiResource>(parentName);

                if(parentResource)
                {
                    resource = parentResource->getSubResource(subName);
                }
                else
                {
                    OcularLogger->error("Failed to load parent MultiResource of '", mappingName, "'", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "loadSubResource"));
                    result = false;
                }
            }
            else
            {
                result = false;
            }

            return result;
        }

        bool ResourceLoader_OBJ::exploreResource(Core::File const& file)
        {
            /**
             * Explores the OBJ file. For each 'group' tag found that is not 'default' it
             * will add a new Resource mapping path to the global ResourceManager.
             *
             * Also checks for materials via the 'usemtl' tag.
             */

            bool result = false;

            if(!isFileValid(file))
            {
                return result;
            }

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
                                    OcularResources->addResource((mappingName + "/" + (*iter)), file, nullptr, Core::ResourceType::Mesh);
                                }
                            }
                        }
                        else if(line[0] == 'u')
                        {
                            std::vector<std::string> tokens;
                            Utils::String::Split(line, ' ', tokens);

                            if(Utils::String::IsEqual(tokens[0], "usemtl"))
                            {
                                OcularResources->addResource((mappingName + "/" + tokens[1]), file, nullptr, Core::ResourceType::Material);
                            }
                        }
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
        
        //----------------------------------------------------------------------------------
        // Mesh Methods
        //----------------------------------------------------------------------------------

        void ResourceLoader_OBJ::createMeshes(Core::MultiResource* multiResource)
        {
            std::vector<OBJGroup const*> groups;
            m_CurrState->getGroups(groups);

            //----------------------------------------------------
            // Iterate over all groups and create a mesh for each

            for(auto iter = groups.begin(); iter != groups.end(); ++iter)
            {
                OBJGroup const* group = (*iter);

                if(group && !OcularString->IsEqual(group->name, "default", true))
                {
                    Mesh* mesh = new Mesh();
                    createMesh(mesh, group);

                    multiResource->addSubResource(mesh, group->name);
                }
            }
        }

        void ResourceLoader_OBJ::createMesh(Mesh* mesh, OBJGroup const* group)
        {
            Math::Vector3f min = Math::Vector3f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
            Math::Vector3f max = Math::Vector3f(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

            uint32_t currentState = 0;                          // The active render state of the OBJ
            const uint32_t numFaces = static_cast<uint32_t>(group->faces.size());

            //------------------------------------------------------------
            // Initialize the Vertex/Index Containers
            //------------------------------------------------------------

            // One buffer per material used in group

            std::vector<std::pair<std::string, std::vector<Vertex>>> vertexBuffers;      // First element is material name
            std::vector<std::pair<std::string, std::vector<uint32_t>>> indexBuffers;

            for(std::vector<OBJFace>::size_type i = 0; i < group->faces.size(); i++)
            {
                OBJFace const* face = &group->faces[i];

                // If the render state has changed
                if(face->renderState != currentState)
                {
                    currentState = face->renderState;
                    auto renderState = m_CurrState->getRenderState(currentState);

                    // Has the material been encountered before?
                    
                    bool newMaterial = true;

                    for(auto iter = vertexBuffers.begin(); iter != vertexBuffers.end(); ++iter)
                    {
                        if(Utils::String::IsEqual(renderState.material, iter->first))
                        {
                            newMaterial = false;
                            break;
                        }
                    }

                    if(newMaterial)      
                    {
                        vertexBuffers.push_back(std::make_pair(renderState.material, std::vector<Vertex>()));
                        vertexBuffers.back().second.reserve(numFaces * 6);    // Assume worst-case: only one submesh, and all faces are quads
                        
                        indexBuffers.push_back(std::make_pair(renderState.material, std::vector<uint32_t>()));
                        indexBuffers.back().second.reserve(numFaces * 4);
                    }
                }
            }

            //------------------------------------------------------------
            // Fill the Vertex/Index Containers
            //------------------------------------------------------------

            if(vertexBuffers.size())
            {
                currentState = 0;

                std::pair<std::string, std::vector<Vertex>>* currVertices =  &vertexBuffers[0];
                std::pair<std::string, std::vector<uint32_t>>* currIndices = &indexBuffers[0];

                // For each face in the group
                for(std::vector<OBJFace>::size_type i = 0; i < group->faces.size(); i++)
                {
                    OBJFace const* face = &group->faces[i];

                    // If the face is using a different render state
                    if(face->renderState != currentState)
                    {
                        currentState = face->renderState;
                        auto renderState = m_CurrState->getRenderState(currentState);

                        // Find the vertex/index containers associated with the material in the new state
                        for(uint32_t i = 0; i < static_cast<uint32_t>(vertexBuffers.size()); i++)
                        {
                            if(Utils::String::IsEqual(renderState.material, vertexBuffers[i].first))
                            {
                                currVertices = &vertexBuffers[i];
                                currIndices = &indexBuffers[i];
                                break;
                            }
                        }
                    }

                    addFace(&group->faces[i], &currVertices->second, &currIndices->second, min, max);
                }
            }

            //------------------------------------------------------------
            // Create submeshes for each map entry 
            //------------------------------------------------------------

            for(uint32_t i = 0; i < static_cast<uint32_t>(vertexBuffers.size()); i++)
            {
                SubMesh* submesh = new SubMesh();

                auto vb = OcularGraphics->createVertexBuffer();
                vb->addVertices(vertexBuffers[i].second);
                vb->build();

                auto ib = OcularGraphics->createIndexBuffer();
                ib->addIndices(indexBuffers[i].second);
                ib->build();

                submesh->setVertexBuffer(vb);
                submesh->setIndexBuffer(ib);

                mesh->addSubMesh(submesh);
                mesh->setMinMaxPoints(min, max);
            }
        }

        void ResourceLoader_OBJ::addFace(
            OBJFace const* face, 
            std::vector<Vertex>* vertices, 
            std::vector<uint32_t>* indices, 
            Math::Vector3f& min, 
            Math::Vector3f& max)
        {
            faceToVertex(vertices, face->group0, min, max);
            faceToVertex(vertices, face->group1, min, max);
            faceToVertex(vertices, face->group2, min, max);

            if(face->group3.indexSpatial < 0)
            {
                const uint32_t currVertIndex = static_cast<uint32_t>(vertices->size());

                indices->push_back(currVertIndex - 3);
                indices->push_back(currVertIndex - 2);
                indices->push_back(currVertIndex - 1);
            }
            else
            {
                // Convert the single quad face to two triangle faces

                faceToVertex(vertices, face->group3, min, max);
                
                const uint32_t currVertIndex = static_cast<uint32_t>(vertices->size());
                
                indices->push_back(currVertIndex - 4);
                indices->push_back(currVertIndex - 3);
                indices->push_back(currVertIndex - 2);
                indices->push_back(currVertIndex - 2);
                indices->push_back(currVertIndex - 1);
                indices->push_back(currVertIndex - 4);
            }
        }

        void ResourceLoader_OBJ::faceToVertex(
            std::vector<Vertex>* vertices, 
            OBJVertexGroup const& group, 
            Math::Vector3f& min,
            Math::Vector3f& max)
        {
            Vertex vert;

            if(group.indexSpatial >= 0)
            { 
                OBJVector4 const* vec = &(m_CurrState->getSpatialData()->at(group.indexSpatial));
                vert.position = { vec->x, vec->y, vec->z };

                min.x = std::min(min.x, vert.position.x);
                min.y = std::min(min.y, vert.position.y);
                min.z = std::min(min.z, vert.position.z);
            
                max.x = std::max(max.x, vert.position.x);
                max.y = std::max(max.y, vert.position.y);
                max.z = std::max(max.z, vert.position.z);
            }

            if(group.indexTexture >= 0)
            {
                OBJVector2 const* vec = &(m_CurrState->getTextureData()->at(group.indexSpatial));
                vert.uv0 = { vec->x, vec->y };
            }

            if(group.indexNormal >= 0)
            {
                OBJVector4 const* vec = &(m_CurrState->getSpatialData()->at(group.indexSpatial));
                vert.normal = { vec->x, vec->y, vec->z };
            }

            vertices->push_back(vert);
        }
        
        //----------------------------------------------------------------------------------
        // Material Methods
        //----------------------------------------------------------------------------------

        void ResourceLoader_OBJ::createMaterials(Core::MultiResource* multiResource)
        {
            const std::string relPath = multiResource->getMappingName().substr(0, multiResource->getMappingName().find_last_of('/'));

            std::vector<OBJMaterial const*> objMaterials;
            m_CurrState->getMaterials(objMaterials);

            for(auto objMaterial : objMaterials)
            {
                if(objMaterial)
                {
                    Material* material = OcularGraphics->createMaterial();
                    createMaterial(material, objMaterial, relPath);

                    multiResource->addSubResource(material, objMaterial->getName());
                }
            }
        }

        void ResourceLoader_OBJ::createMaterial(Material* material, OBJMaterial const* objMaterial, std::string const& relPath)
        {
            auto diffuse = objMaterial->getDiffuseTexture();

            if(diffuse.getPath().size())
            {
                std::string path = relPath + "/" + diffuse.getPath();
                path = path.substr(0, path.find_last_of('.'));

                Texture* texture = OcularResources->getResource<Texture>(path);

                if(texture)
                {
                    material->setTexture(0, "Diffuse", texture);
                }
            }
        }
        
        //----------------------------------------------------------------------------------
        // Misc Methods
        //----------------------------------------------------------------------------------

        bool ResourceLoader_OBJ::isFileValid(Core::File const& file) const
        {
            bool result = true;

            if(!file.exists())
            {
                OcularLogger->error("Specified file does not exist '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "isFileValid"));
                result = false;
            }

            if(!OcularString->IsEqual(file.getExtension(), ".obj", true))
            {
                OcularLogger->error("Invalid extension for file '", file.getFullPath(), "'; Expected '.obj'", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "isFileValid"));
                result = false;
            }

            if(!file.canRead())
            {
                OcularLogger->error("Invalid read access for file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("ResourceLoader_OBJ", "isFileValid"));
                result = false;
            }

            return result;
        }

        void ResourceLoader_OBJ::splitParentSubNames(std::string const& mappingName, std::string& parent, std::string& sub) const
        {
            auto find = mappingName.find_last_of('/');

            if(find != std::string::npos)
            {
                parent = mappingName.substr(0, find); 
                sub = mappingName.substr(find + 1, std::string::npos);
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}