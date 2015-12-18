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

#include "Scene/Renderables/RenderablePrimitiveCube.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        RenderablePrimitiveCube::RenderablePrimitiveCube(std::string const& name, SceneObject* parent)
            : ARenderable(name, parent)
        {

        }

        RenderablePrimitiveCube::~RenderablePrimitiveCube()
        {
            // Our mesh was manually created and is not a shared resource, so delete it
            if(m_Mesh)
            {
                delete m_Mesh;
                m_Mesh = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool RenderablePrimitiveCube::initialize()
        {
            bool result = ARenderable::initialize();

            if(result)
            {
                if(createMesh())
                {
                    m_Material = OcularResources->getResource<Graphics::Material>("Materials/Flat");

                    if(m_Material)
                    {
                        m_Material->setUniform("MaterialColor", 0, Math::Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
                    }
                    else
                    {
                        result = false;
                        OcularLogger->error("Failed to load Material", OCULAR_INTERNAL_LOG("RenderablePrimitiveCube", "initialize"));
                    }
                }
                else
                {
                    result = false;
                    OcularLogger->error("Failed to manually create Mesh", OCULAR_INTERNAL_LOG("RenderablePrimitiveCube", "initialize"));
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool RenderablePrimitiveCube::createMesh()
        {
            bool result = false;

            if(m_Mesh == nullptr)
            {
                m_Mesh = new Graphics::Mesh();

                Graphics::VertexBuffer* vertexBuffer = OcularGraphics->createVertexBuffer();
                Graphics::IndexBuffer* indexBuffer = OcularGraphics->createIndexBuffer();

                if(vertexBuffer && indexBuffer)
                {
                    //----------------------------------------------------
                    // Create the Vertices

                    Graphics::Vertex vertices[8];

                    vertices[0].position = Math::Vector3f(-0.5f, 0.0f,  0.5f);
                    vertices[1].position = Math::Vector3f( 0.5f, 0.0f,  0.5f);
                    vertices[2].position = Math::Vector3f( 0.5f, 1.0f,  0.5f);
                    vertices[3].position = Math::Vector3f(-0.5f, 1.0f,  0.5f);
                    vertices[4].position = Math::Vector3f(-0.5f, 0.0f, -0.5f);
                    vertices[5].position = Math::Vector3f(-0.5f, 1.0f, -0.5f);
                    vertices[6].position = Math::Vector3f( 0.5f, 0.0f, -0.5f);
                    vertices[7].position = Math::Vector3f( 0.5f, 1.0f, -0.5f);

                    /*vertices[0].position = Math::Vector3f(-1.0f, -1.0f,  1.0f);
                    vertices[1].position = Math::Vector3f( 1.0f, -1.0f,  1.0f);
                    vertices[2].position = Math::Vector3f( 1.0f,  1.0f,  1.0f);
                    vertices[3].position = Math::Vector3f(-1.0f,  1.0f,  1.0f);
                    vertices[4].position = Math::Vector3f(-1.0f, -1.0f, -1.0f);
                    vertices[5].position = Math::Vector3f(-1.0f,  1.0f, -1.0f);
                    vertices[6].position = Math::Vector3f( 1.0f, -1.0f, -1.0f);
                    vertices[7].position = Math::Vector3f( 1.0f,  1.0f, -1.0f);*/

                    vertices[0].color = Math::Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
                    vertices[1].color = Math::Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
                    vertices[2].color = Math::Vector4f(0.0f, 0.0f, 1.0f, 1.0f);
                    vertices[3].color = Math::Vector4f(1.0f, 1.0f, 0.0f, 1.0f);
                    vertices[4].color = Math::Vector4f(0.0f, 1.0f, 1.0f, 1.0f);
                    vertices[5].color = Math::Vector4f(1.0f, 0.0f, 1.0f, 1.0f);
                    vertices[6].color = Math::Vector4f(0.5f, 1.0f, 0.75f, 1.0f);
                    vertices[7].color = Math::Vector4f(0.75f, 0.5f, 1.0f, 1.0f);

                    vertexBuffer->addVertices(vertices, 8);

                    if(vertexBuffer->build())
                    {
                        //------------------------------------------------
                        // Create the Indices

                        uint32_t indices[36] =
                        {
                            0, 1, 2,
                            2, 3, 0,
                            4, 0, 3,
                            3, 5, 4,
                            6, 4, 5,
                            5, 7, 6,
                            1, 6, 7,
                            7, 2, 1,
                            3, 2, 7,
                            7, 5, 3,
                            1, 0, 4,
                            4, 6, 1
                        };

                        indexBuffer->addIndices(indices, 36);

                        if(indexBuffer->build())
                        {
                            //------------------------------------------------
                            // Add buffers to the Mesh

                            m_Mesh->setVertexBuffer(vertexBuffer);
                            m_Mesh->setIndexBuffer(indexBuffer);

                            result = true;
                        }
                        else
                        {
                            OcularLogger->error("Failed to build Index Buffer", OCULAR_INTERNAL_LOG("RenderablePrimitiveCube", "createMesh"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Failed to build Vertex Buffer", OCULAR_INTERNAL_LOG("RenderablePrimitiveCube", "createMesh"));
                    }
                }
                else
                {
                    if(vertexBuffer == nullptr)
                    {
                        OcularLogger->error("Failed to create Vertex Buffer", OCULAR_INTERNAL_LOG("RenderablePrimitiveCube", "createMesh"));
                    }

                    if(indexBuffer == nullptr)
                    {
                        OcularLogger->error("Failed to create Index Buffer", OCULAR_INTERNAL_LOG("RenderablePrimitiveCube", "createMesh"));
                    }
                }

                if(!result)
                {
                    delete vertexBuffer;
                    delete indexBuffer;
                    delete m_Mesh;

                    m_Mesh = nullptr;
                }
            }
            else
            {
                result = true;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}