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

#include "stdafx.h"

#include "Renderer/EditorForwardRenderer.hpp"
#include "Renderer/RendererRegistrar.hpp"
#include "Scene/ARenderable.hpp"

OCULAR_REGISTER_RENDERER(Ocular::Editor::ForwardRenderer, "EditorForwardRenderer")

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ForwardRenderer::ForwardRenderer()
            : Renderer(),
              m_SelectedMaterial(nullptr)
        {

        }

        ForwardRenderer::~ForwardRenderer()
        {
            delete m_SelectedMaterial;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void ForwardRenderer::render(std::vector<Core::SceneObject*>& objects)
        {
            static bool once = true;

            OcularGraphics->clearBuffers(OcularCameras->getActiveCamera()->getClearColor());

            sort(objects);

            OcularLights->updateLights(true);

            //------------------------------------------------------------
            // Render all objects
            //------------------------------------------------------------

            bindUniforms(nullptr);
            OcularGraphics->renderDebug();    // Draw any debug shapes first

            auto selectedObject = OcularEditor.getSelectedObject();

            for(auto object : objects)
            {
                auto renderable = object->getRenderable();

                if(renderable)
                {
                    if(renderable->preRender())
                    {
                        bindUniforms(object);

                        renderable->render();
                        renderable->postRender();
                    }
                }
            }
            
            //------------------------------------------------------------
            // Render the selected object as wireframe
            //------------------------------------------------------------

            // Temporary until material support multi-passes

            buildSelectedMaterial();

            if(selectedObject && selectedObject->isVisible())
            {
                auto renderable = selectedObject->getRenderable();

                if(renderable)
                {
                    if(renderable->preRender())
                    {
                        bindUniforms(selectedObject);

                        renderable->render(m_SelectedMaterial);
                        renderable->postRender();
                    }
                }
            }
            
            //------------------------------------------------------------

            OcularGraphics->swapBuffers();
        }

        void ForwardRenderer::render(std::vector<Core::SceneObject*>& objects, Graphics::Material* material)
        {
            OcularGraphics->clearBuffers(OcularCameras->getActiveCamera()->getClearColor());

            bindUniforms(nullptr);
            OcularGraphics->renderDebug();    // Draw any debug shapes first

            sort(objects);

            for(auto object : objects)
            {
                auto renderable = object->getRenderable();

                if(renderable)
                {
                    if(renderable->preRender())
                    {
                        bindUniforms(object);

                        renderable->render(material);
                        renderable->postRender();
                    }
                }
            }

            OcularGraphics->swapBuffers();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void ForwardRenderer::buildSelectedMaterial()
        {
            if(!m_SelectedMaterial)
            {
                m_SelectedMaterial = new Graphics::Material();
                Graphics::Material* sourceMaterial = OcularResources->getResource<Graphics::Material>("OcularCore/Materials/Flat");

                if(sourceMaterial)
                {
                    Core::BuilderNode builderNode(nullptr, "", "", "");

                    sourceMaterial->onSave(&builderNode);
                    m_SelectedMaterial->onLoad(&builderNode);

                    // Temporary use of hardware wireframe until geometry shader wireframe

                    m_SelectedMaterial->setFillMode(Graphics::FillMode::Wireframe);
                    m_SelectedMaterial->setUniform("_Color", 0, Core::Color::GreenHighlight());
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}