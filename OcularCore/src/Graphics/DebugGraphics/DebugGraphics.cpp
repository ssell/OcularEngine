/**
* Copyright 2014-2015 Steven T Sell (ssell@vertexfragment.com)
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

#include "Graphics/DebugGraphics/DebugGraphics.hpp"
#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Material/Material.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Debug::Debug()
            : m_Material(nullptr)
        {

        }

        Debug::~Debug()
        {
            for(auto iter = m_DebugShapes.begin(); iter != m_DebugShapes.end(); )
            {
                delete iter->mesh;
                iter = m_DebugShapes.erase(iter);
            }

            delete m_Material;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Debug::addLine(Math::Vector3f const& start, Math::Vector3f const& stop, Core::Color const& color, uint64_t const lifetime)
        {
            DebugShape lineShape;

            lineShape.color = color;
            lineShape.creationTime = OcularClock->getElapsedMS();
            lineShape.lifetime = lifetime;

            //------------------------------------------------------------
            // Build the line mesh
            //------------------------------------------------------------

            Mesh* mesh = new Mesh();
            VertexBuffer* vb = OcularGraphics->createVertexBuffer();
            IndexBuffer* ib = OcularGraphics->createIndexBuffer();

            Vertex startVert;
            startVert.position = start;

            Vertex stopVert;
            stopVert.position = stop;
            
            vb->addVertex(startVert);
            vb->addVertex(stopVert);
            vb->build();

            ib->addIndex(0);
            ib->addIndex(1);
            ib->build();

            mesh->addSubMesh();
            mesh->setVertexBuffer(vb);
            mesh->setIndexBuffer(ib);

            lineShape.mesh = mesh;

            //------------------------------------------------------------

            m_DebugShapes.push_back(lineShape);
        }

        void Debug::addCircle(Math::Vector3f const& center, float radius, Math::Vector3f const& normal, Core::Color const& color, uint32_t const segments, uint64_t const lifetime)
        {
            DebugShape circleShape;

            circleShape.color = color;
            circleShape.creationTime = OcularClock->getElapsedMS();
            circleShape.lifetime = lifetime;

            //------------------------------------------------------------
            // Build the circle mesh
            //------------------------------------------------------------

            Mesh* mesh = new Mesh();
            VertexBuffer* vb = OcularGraphics->createVertexBuffer();
            IndexBuffer* ib = OcularGraphics->createIndexBuffer();

            Math::Transform transform;
            transform.lookAt(normal.getNormalized());

            Math::Matrix4x4 rotation = transform.getModelMatrix();

            // First we build the vertices in '2D' centered around the world origin

            const float stepAngle = 2.0f * static_cast<float>(Math::PI) / segments;

            for(uint32_t i = 0; i < segments; i++)
            {
                Vertex vertex;

                vertex.position.x = (radius * cosf(stepAngle * i));
                vertex.position.y = (-radius * sinf(stepAngle * i));
                vertex.position.z = 0.0f;

                vertex.position = rotation * vertex.position;

                vb->addVertex(vertex);
            }

            for(uint32_t i = 0; i < segments; i++)
            {
                if(i < (segments - 1))
                {
                    ib->addIndex(i);
                    ib->addIndex(i + 1);
                }
                else
                {
                    ib->addIndex(i);
                    ib->addIndex(0);
                }
            }
            
            //------------------------------------------------------------
            // Build the mesh

            vb->build();
            ib->build();

            mesh->addSubMesh();
            mesh->setVertexBuffer(vb);
            mesh->setIndexBuffer(ib);

            circleShape.mesh = mesh;

            //------------------------------------------------------------

            m_DebugShapes.push_back(circleShape);
        }

        void Debug::render()
        {
            removeDeadShapes();

            // If there are shapes to draw and we have the material
            if(m_DebugShapes.size() && fetchMaterial())  
            {
                for(auto iter = m_DebugShapes.begin(); iter != m_DebugShapes.end(); ++iter)
                {
                    m_Material->setUniform("Color", 0, iter->color);
                    m_Material->bind();

                    OcularGraphics->renderMesh(iter->mesh);
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool Debug::fetchMaterial()
        {
            if(!m_Material)
            {
                Core::BuilderNode builder(nullptr, "", "", "");;

                m_Material = OcularGraphics->createMaterial();
                Material* referenceMaterial = OcularResources->getResource<Material>("OcularCore/Materials/Flat");

                if(referenceMaterial)
                {
                    referenceMaterial->onSave(&builder);

                    m_Material->onLoad(&builder);
                    m_Material->setFillMode(FillMode::Wireframe);
                    m_Material->setPrimitiveStyle(PrimitiveStyle::LineList);
                }
            }

            return (m_Material != nullptr);
        }

        void Debug::removeDeadShapes()
        {
            const uint64_t currTime = OcularClock->getElapsedMS();

            for(auto iter = m_DebugShapes.begin(); iter != m_DebugShapes.end(); )
            {
                if(iter->lifetime != 0)
                {
                    if((currTime - iter->creationTime) > iter->lifetime)
                    {
                        // The shape's time is up
                        delete iter->mesh;
                        iter = m_DebugShapes.erase(iter);

                        continue;
                    }
                }

                ++iter;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}