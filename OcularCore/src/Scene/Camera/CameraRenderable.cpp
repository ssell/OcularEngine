/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Scene/Camera/CameraRenderable.hpp"

#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Mesh/VertexBuffer.hpp"
#include "Graphics/Mesh/IndexBuffer.hpp"
#include "Graphics/Material/Material.hpp"

#include "OcularEngine.hpp"

// We do not register this renderable as it is not a 'public'
// renderable and is used only by the Camera class.

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CameraRenderable::CameraRenderable(std::string const& name, SceneObject* parent)
            : ARenderable(name, "CameraRenderable", parent),
              m_FrustumMesh(nullptr),
              m_FrustumMaterial(nullptr)
        {
            if(!m_FrustumMesh)
            {
                buildFrustumMaterial();
            }

            if(!m_FrustumMaterial)
            {
                buildFrustumMesh();
            }
        }

        CameraRenderable::~CameraRenderable()
        {
            if(m_FrustumMesh)
            {
                delete m_FrustumMesh;
                m_FrustumMesh = nullptr;
            }

            if(m_FrustumMaterial)
            {
                delete m_FrustumMaterial;
                m_FrustumMaterial = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool CameraRenderable::initialize()
        {
            return (buildFrustumMaterial() && buildFrustumMesh());
        }

        bool CameraRenderable::preRenderDebug()
        {
            bool result = true;

            return result;
        }

        void CameraRenderable::renderDebug()
        {
            if(m_FrustumMesh && m_FrustumMaterial)
            {
                m_FrustumMaterial->bind();

                for(uint32_t i = 0; i < m_FrustumMesh->getNumSubMeshes(); i++)
                {
                    OcularGraphics->renderMesh(m_FrustumMesh, i);
                }
            }
        }

        void CameraRenderable::postRenderDebug()
        {

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool CameraRenderable::buildFrustumMesh()
        {
            bool result = false;

            if(m_FrustumMesh)
            {
                delete m_FrustumMesh;
                m_FrustumMesh = nullptr;
            }

            Camera* parent = dynamic_cast<Camera*>(m_Parent);

            if(parent)
            {
                Graphics::VertexBuffer* vb = OcularGraphics->createVertexBuffer();
                Graphics::IndexBuffer* ib = OcularGraphics->createIndexBuffer();

                //------------------------------------------------------------
                // Get the corners that comprise the frustum

                Math::Frustum frustum = parent->getFrustum();
                frustum.rebuild();

                auto nearCorners = frustum.getNearClipCorners();
                auto farCorners = frustum.getFarClipCorners();

                //------------------------------------------------------------
                // Build the vertex buffer

                std::vector<Graphics::Vertex> vertices(8);

                vertices[0].position = nearCorners[0];    // Near bottom left
                vertices[1].position = nearCorners[1];    // Near bottom right
                vertices[2].position = nearCorners[2];    // Near top right
                vertices[3].position = nearCorners[3];    // Near top left

                vertices[4].position = farCorners[0];     // Far bottom left
                vertices[5].position = farCorners[1];     // Far bottom right
                vertices[6].position = farCorners[2];     // Far top right
                vertices[7].position = farCorners[3];     // Far top left

                vb->addVertices(vertices);

                if(!vb->build())
                {
                    result = false;
                }

                //--------------------------------------------------------
                // Build the index buffer

                std::vector<uint32_t> indices(24);

                indices[0]  = 0; indices[1]  = 1;         // Line from near bottom left to near bottom right
                indices[2]  = 1; indices[3]  = 2;         // Line from near bottom right to near top right
                indices[4]  = 2; indices[5]  = 3;         // Line from near top right to near top left
                indices[6]  = 3; indices[7]  = 0;         // Line from near top left to near bottom left

                indices[8]  = 4; indices[9]  = 5;         // Line from far bottom left to far bottom right
                indices[10] = 5; indices[11] = 6;         // Line from far bottom right to far top right
                indices[12] = 6; indices[13] = 7;         // Line from far top right to far top left
                indices[14] = 7; indices[15] = 4;         // Line from far top left to far bottom left

                indices[16] = 0; indices[17] = 4;         // Line from near bottom left to far bottom left
                indices[18] = 1; indices[19] = 5;         // Line from near bottom right to far bottom right
                indices[20] = 2; indices[21] = 6;         // Line from near top right to far top right
                indices[22] = 3; indices[23] = 7;         // Line from near top left to far top left

                ib->addIndices(indices);

                if(!ib->build())
                {
                    result = false;
                }

                //--------------------------------------------------------
                // Build the mesh

                m_FrustumMesh = new Graphics::Mesh();

                m_FrustumMesh->addSubMesh();
                m_FrustumMesh->setVertexBuffer(vb);
                m_FrustumMesh->setIndexBuffer(ib);
            }

            return result;
        }

        bool CameraRenderable::buildFrustumMaterial()
        {
            bool result = false;

            m_FrustumMaterial = OcularGraphics->createMaterial();
            Graphics::Material* sourceMaterial = OcularResources->getResource<Graphics::Material>("OcularCore/Materials/Flat");

            if(sourceMaterial)
            {
                BuilderNode builder(nullptr, "", "", "");

                sourceMaterial->onSave(&builder);
                m_FrustumMaterial->onLoad(&builder);

                m_FrustumMaterial->setUniform("Color", 0, Core::Color::White());
                m_FrustumMaterial->setFillMode(Graphics::FillMode::Wireframe);
                m_FrustumMaterial->setPrimitiveStyle(Graphics::PrimitiveStyle::LineList);

                result = true;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}