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
#include "Gizmos/Axis/AxisGizmo.hpp"

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
              m_MaterialNormal(nullptr),
              m_MaterialSelected(nullptr),
              m_Mesh(nullptr),
              m_IsSelected(false)
        {
            
        }

        AxisGizmoRenderable::~AxisGizmoRenderable()
        {
            // We delete the material as we manually created it
            // But we did not create the Mesh, so leave it for the ResourceManager to clean up

            delete m_MaterialNormal;
            delete m_MaterialSelected;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool AxisGizmoRenderable::initialize()
        {
            bool result = false;

            delete m_MaterialNormal;
            m_MaterialNormal = nullptr;

            delete m_MaterialSelected;
            m_MaterialSelected = nullptr;

            if(initializeMaterials())
            {
                if(initializeMesh())
                {
                    result = true;
                }
            }

            return result;
        }

        bool AxisGizmoRenderable::preRender()
        {
            // If the first component of this gizmo to be rendered, clear the depth-buffer.
            // This is an easy way to ensure we are drawn ontop of the rest of the scene.

            AxisComponentGizmo* parent = dynamic_cast<AxisComponentGizmo*>(m_Parent);

            if(parent)
            {
                AxisGizmo* parentParent = dynamic_cast<AxisGizmo*>(parent->getParent());

                if(parentParent)
                {
                    parentParent->clearDepthBuffer();
                }
            }

            return true;
        }

        void AxisGizmoRenderable::render()
        {
            if(m_Mesh)
            {
                if(m_MaterialNormal && !m_IsSelected)
                {
                    m_MaterialNormal->bind();
                }
                else if(m_MaterialSelected && m_IsSelected)
                {
                    m_MaterialSelected->bind();
                }

                OcularGraphics->renderMesh(m_Mesh, 0);
            }
        }

        void AxisGizmoRenderable::render(Graphics::Material* material)
        {
            if(material && m_Mesh)
            {
                material->bind();
                OcularGraphics->renderMesh(m_Mesh, 0);
            }
        }

        uint32_t AxisGizmoRenderable::getRenderPriority() const
        {
            uint32_t result = static_cast<uint32_t>(Core::RenderPriority::Opaque);

            if(m_MaterialNormal)
            {
                result = m_MaterialNormal->getRenderPriority();
            }

            return result;
        }

        void AxisGizmoRenderable::setSelected(bool const selected)
        {
            m_IsSelected = selected;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool AxisGizmoRenderable::initializeMaterials()
        {
            return (initializeMaterialNormal() && initializeMaterialSelected());
        }

        bool AxisGizmoRenderable::initializeMaterialNormal()
        {
            bool result = false;

            auto flatShaders = OcularResources->getResource<Graphics::ShaderProgram>("OcularCore/Shaders/Flat");

            if(flatShaders)
            {
                m_MaterialNormal = OcularGraphics->createMaterial();

                if(m_MaterialNormal)
                {
                    m_MaterialNormal->setVertexShader(flatShaders->getVertexShader());
                    m_MaterialNormal->setFragmentShader(flatShaders->getFragmentShader());
                    m_MaterialNormal->setRenderPriority(static_cast<uint32_t>(Core::RenderPriority::Overlay) - 1);    // Render as last non-overlay object

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

                        m_MaterialNormal->setUniform("Color", 0, color);
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Invalid parent type (expected AxisComponentGizmo)", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterialNormal"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create a new Material", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterialNormal"));
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve Flat shaders", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterialNormal"));
            }

            return result;
        }

        bool AxisGizmoRenderable::initializeMaterialSelected()
        {
            bool result = false;

            auto flatShaders = OcularResources->getResource<Graphics::ShaderProgram>("OcularCore/Shaders/Flat");

            if(flatShaders)
            {
                m_MaterialSelected = OcularGraphics->createMaterial();

                if(m_MaterialSelected)
                {
                    m_MaterialSelected->setVertexShader(flatShaders->getVertexShader());
                    m_MaterialSelected->setFragmentShader(flatShaders->getFragmentShader());
                    m_MaterialSelected->setRenderPriority(static_cast<uint32_t>(Core::RenderPriority::Overlay) - 1);    // Render as last non-overlay object

                    AxisComponentGizmo* parent = dynamic_cast<AxisComponentGizmo*>(m_Parent);

                    if(parent)
                    {
                        m_MaterialSelected->setUniform("Color", 0, Core::Color::Yellow());
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Invalid parent type (expected AxisComponentGizmo)", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterialNormal"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create a new Material", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterialNormal"));
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve Flat shaders", OCULAR_INTERNAL_LOG("AxisGizmoRenderable", "initializeMaterialNormal"));
            }

            return result;
        }

        bool AxisGizmoRenderable::initializeMesh()
        {
            bool result = true;
            m_Mesh = OcularResources->getResource<Graphics::Mesh>("OcularCore/Meshes/AxisGizmoArrow/AxisGizmoArrow");

            if(!m_Mesh)
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