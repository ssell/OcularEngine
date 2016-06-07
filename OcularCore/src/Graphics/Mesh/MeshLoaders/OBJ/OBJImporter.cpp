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

#include "Graphics/Mesh/MeshLoaders/OBJ/OBJImporter.hpp"
#include "Graphics/Mesh/MeshLoaders/OBJ/OBJMeshMetadata.hpp"

#include "Resources/MultiResource.hpp"
#include "Scene/Renderables/MeshRenderable.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------=

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------=

        Core::SceneObject* OBJImporter::Import(std::string const& path)
        {
            Core::SceneObject* result = nullptr;
            Core::MultiResource* resource = OcularResources->getResource<Core::MultiResource>(path);

            if(resource)
            {
                //--------------------------------------------------------
                // Create empty parent object
                //--------------------------------------------------------

                const std::string name = Core::File(resource->getSourceFile()).getName();

                result = OcularScene->createObject(name, nullptr);

                if(result)
                {
                    //----------------------------------------------------
                    // For each mesh resource, create a new child SceneObject
                    //----------------------------------------------------

                    std::vector<Core::Resource*> resources;
                    resource->getSubResources(resources);

                    for(auto subresource : resources)
                    {
                        Mesh* mesh = dynamic_cast<Mesh*>(subresource);

                        if(mesh)
                        {
                            Core::SceneObject* child = OcularScene->createObject(mesh->getName(), result);
                            Core::MeshRenderable* renderable = child->setRenderable<Core::MeshRenderable>();

                            if(renderable)
                            {
                                renderable->setMesh(mesh);

                                // For each submesh, set the appropriate matching material

                                OBJMeshMetadata* metadata = dynamic_cast<OBJMeshMetadata*>(mesh->getMetadata());

                                if(metadata)
                                {
                                    for(uint32_t i = 0; i < mesh->getNumSubMeshes(); i++)
                                    {
                                        const std::string mappingName = resource->getMappingName() + "/" + metadata->getSubmeshMaterialPair(i);
                                        renderable->setMaterial(mappingName, i, true);
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create empty SceneObject", OCULAR_INTERNAL_LOG("OBJImporter", "Import"));
                }
            }
            else
            {
                OcularLogger->error("Failed to find matching Resource at path '", path, "'", OCULAR_INTERNAL_LOG("OBJImporter", "Import"));
            }

            return result;
        }

        bool OBJImporter::FindMeshes(std::string const& path, std::vector<std::string>& names)
        {
            bool result = false;

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------=

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}