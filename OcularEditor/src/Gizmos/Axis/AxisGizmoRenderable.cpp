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

#include "stdafx.h"

#include "Gizmos/Axis/AxisGizmoRenderable.hpp"
#include "Gizmos/Axis/AxisComponentGizmo.hpp"

#include "Graphics/Shader/ShaderProgram.hpp"
#include "Renderer/RenderPriority.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        AxisGizmoRenderable::AxisGizmoRenderable()
            : Core::ARenderable("AxisGizmoRenderable", "AxisGizmoRenderable"),
              m_Material(nullptr),
              m_Mesh(nullptr)
        {
            
        }

        AxisGizmoRenderable::~AxisGizmoRenderable()
        {
            // We delete the material as we manually created it
            // But we did not create the Mesh, so leave it for the ResourceManager to clean up

            delete m_Material;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool AxisGizmoRenderable::initialize()
        {
            delete m_Material;
            m_Material = nullptr;

            return initializeMaterial() && initializeMesh();
        }

        bool AxisGizmoRenderable::preRender()
        {
            // Temporarily disable depth testing so the axis arrow is drawn on top of all other objects

            auto renderState = OcularGraphics->getRenderState();

            if(renderState)
            {
                auto depthState = renderState->getDepthStencilState();

                depthState.enableDepthTesting = false;

                renderState->setDepthStencilState(depthState);
                renderState->bind();
            }

            return true;
        }

        void AxisGizmoRenderable::render()
        {
            if(m_Material && m_Mesh)
            {
                m_Material->bind();
                OcularGraphics->renderMesh(m_Mesh, 0);
            }
        }

        void AxisGizmoRenderable::postRender()
        {
            // Re-enable depth testing

            auto renderState = OcularGraphics->getRenderState();

            if(renderState)
            {
                auto depthState = renderState->getDepthStencilState();

                depthState.enableDepthTesting = true;

                renderState->setDepthStencilState(depthState);
                renderState->bind();
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool AxisGizmoRenderable::initializeMaterial()
        {
            bool result = false;

            auto flatShaders = OcularResources->getResource<Graphics::ShaderProgram>("OcularCore/Shaders/Flat");

            if(flatShaders)
            {
                m_Material = OcularGraphics->createMaterial();

                if(m_Material)
                {
                    m_Material->setVertexShader(flatShaders->getVertexShader());
                    m_Material->setFragmentShader(flatShaders->getFragmentShader());
                    m_Material->setRenderPriority(static_cast<uint32_t>(Core::RenderPriority::Overlay) - 1);    // Render as last non-overlay object

                    AxisComponentGizmo* parent = dynamic_cast<AxisComponentGizmo*>(m_Parent);

                    if(parent)
                    {
                        Core::Color color = Core::Color::ErrorPink();

                        switch(parent->axis)
                        {
                        case Axis::X:
                            color = Core::Color::Red();
                            break;

                        case Axis::Y:
                            color = Core::Color::Green();
                            break;

                        case Axis::Z:
                            color = Core::Color::Blue();
                            break;

                        default:
                            break;
                        }

                        m_Material->setUniform("Color", 0, color);
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Invalid parent type (expected AxisComponentGizmo)", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterial"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create a new Material", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterial"));
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve Flat shaders", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterial"));
            }

            return result;
        }

        bool AxisGizmoRenderable::initializeMesh()
        {
            bool result = true;
            m_Mesh = OcularResources->getResource<Graphics::Mesh>("OcularCore/Meshes/AxisGizmoArrow");

            if(m_Mesh = nullptr)
            {
                OcularLogger->error("Failed to retrieve AxisGizmoArrow mesh", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMesh"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}