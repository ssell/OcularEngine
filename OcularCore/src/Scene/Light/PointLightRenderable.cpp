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

#include "Scene/Light/PointLightRenderable.hpp"
#include "Scene/Light/LightSource.hpp"

#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Mesh/VertexBuffer.hpp"
#include "Graphics/Mesh/IndexBuffer.hpp"
#include "Graphics/Material/Material.hpp"

#include "OcularEngine.hpp"

// We do not register this renderable as it is not a 'public'
// renderable and is used only by the PointLight class.

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        Graphics::Mesh* PointLightRenderable::m_ExtentsMesh = nullptr;
        Graphics::Material* PointLightRenderable::m_ExtentsMaterial = nullptr;
        uint32_t PointLightRenderable::m_InternalReference = 0;

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PointLightRenderable::PointLightRenderable(std::string const& name, SceneObject* parent)
            : ARenderable(name, "PointLightRenderable", parent)
        {
            m_InternalReference++;

            if(!m_ExtentsMaterial)
            {
                buildExtentsMaterial();
            }

            if(!m_ExtentsMesh)
            {
                buildExtentsMesh();
            }
        }

        PointLightRenderable::~PointLightRenderable()
        {
            m_InternalReference--;

            if(m_InternalReference == 0)
            {
                if(m_ExtentsMaterial)
                {
                    delete m_ExtentsMaterial;
                    m_ExtentsMaterial = nullptr;
                }

                if(m_ExtentsMesh)
                {
                    delete m_ExtentsMesh;
                    m_ExtentsMesh = nullptr;
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool PointLightRenderable::initialize()
        {
            bool result = true;

            return result;
        }

        bool PointLightRenderable::preRenderDebug()
        {
            bool result = true;

            if(m_Parent)
            {
                float range = 1.0f;
                LightSource* lightParent = dynamic_cast<LightSource*>(m_Parent);

                if(lightParent)
                {
                    range = lightParent->getRange();
                }

                m_StoredRotation = m_Parent->getRotation();
                m_StoredScale = m_Parent->getScale();

                m_Parent->lookAt(OcularCameras->getActiveCamera()->getPosition(false));
                m_Parent->setScale(Math::Vector3f(range, range, range));
            }

            return result;
        }

        void PointLightRenderable::renderDebug()
        {
            if(m_ExtentsMaterial && m_ExtentsMesh)
            {
                m_ExtentsMaterial->bind();

                for(uint32_t i = 0; i < m_ExtentsMesh->getNumSubMeshes(); i++)
                {
                    OcularGraphics->renderMesh(m_ExtentsMesh, i);
                }
            }
        }

        void PointLightRenderable::postRenderDebug()
        {
            if(m_Parent)
            {
                m_Parent->setRotation(m_StoredRotation);
                m_Parent->setScale(m_StoredScale);
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool PointLightRenderable::buildExtentsMaterial()
        {
            bool result = false;

            m_ExtentsMaterial = OcularGraphics->createMaterial();
            Graphics::Material* sourceMaterial = OcularResources->getResource<Graphics::Material>("OcularCore/Materials/Flat");

            if(sourceMaterial)
            {
                BuilderNode builder(nullptr, "", "", "");

                sourceMaterial->onSave(&builder);
                m_ExtentsMaterial->onLoad(&builder);

                m_ExtentsMaterial->setUniform("Color", 0, Core::Color::Yellow());
                m_ExtentsMaterial->setFillMode(Graphics::FillMode::Wireframe);
                m_ExtentsMaterial->setPrimitiveStyle(Graphics::PrimitiveStyle::LineStrip);

                result = true;
            }

            return result;
        }

        bool PointLightRenderable::buildExtentsMesh()
        {
            bool result = true;

            Ocular::Graphics::VertexBuffer* vb = OcularGraphics->createVertexBuffer();
            Ocular::Graphics::IndexBuffer* ib = OcularGraphics->createIndexBuffer();

            const uint32_t segments = 64;

            const float radius = 1.0f;
            const float stepAngle = 2.0f * static_cast<float>(Math::PI) / segments;

            //------------------------------------------------------------
            // Build the vertex buffer

            for(uint32_t i = 0; i < segments; i++)
            {
                Graphics::Vertex vertex;

                vertex.position.x = (radius * cosf(stepAngle * i));
                vertex.position.y = (-radius * sinf(stepAngle * i));
                vertex.position.z = 0.0f;

                vb->addVertex(vertex);
            }
            
            if(!vb->build())
            {
                result = false;
            }

            //------------------------------------------------------------
            // Build the index buffer

            for(uint32_t i = 0; i < segments; i++)
            {
                ib->addIndex(i);
            }

            ib->addIndex(0);

            if(!ib->build())
            {
                result = false;
            }

            //------------------------------------------------------------
            // Build the mesh

            m_ExtentsMesh = new Graphics::Mesh();

            m_ExtentsMesh->addSubMesh();
            m_ExtentsMesh->setVertexBuffer(vb);
            m_ExtentsMesh->setIndexBuffer(ib);

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}