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

#include "Renderer/ForwardRenderer.hpp"
#include "Renderer/RendererRegistrar.hpp"
#include "Scene/ARenderable.hpp"

#include "OcularEngine.hpp"

OCULAR_REGISTER_RENDERER(Ocular::Core::ForwardRenderer, "ForwardRenderer")

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ForwardRenderer::ForwardRenderer()
            : Renderer()
        {

        }

        ForwardRenderer::~ForwardRenderer()
        {
            
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void ForwardRenderer::render(std::vector<SceneObject*>& objects)
        {
            OcularGraphics->clearBuffers(OcularCameras->getActiveCamera()->getClearColor());

            sort(objects);

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

            OcularGraphics->swapBuffers();
        }

        void ForwardRenderer::render(std::vector<SceneObject*>& objects, Graphics::Material* material)
        {
            OcularGraphics->clearBuffers(OcularCameras->getActiveCamera()->getClearColor());

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
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}