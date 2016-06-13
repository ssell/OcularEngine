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

#include "Utilities/ColorPicker.hpp"
#include "Scene/ARenderable.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        Core::SceneObject* ColorPicker::Pick(Core::Camera* camera, uint32_t const x, uint32_t const y)
        {
            Core::SceneObject* result = nullptr;
            Graphics::Material* material = GetMaterial();

            if(camera && material)
            {
                //--------------------------------------------------------
                // Fetch all visible objects
                //--------------------------------------------------------

                std::vector<Core::SceneObject*> visibleObjects;
                OcularScene->getVisibleSceneObjects(visibleObjects, camera->getFrustum());
                
                //--------------------------------------------------------
                // Render all visible objects to the specified Camera's RTV
                //--------------------------------------------------------

                if(visibleObjects.size())
                {    
                    OcularCameras->setActiveCamera(camera);

                    const Core::Color oldClear = camera->getClearColor();
                    camera->setClearColor(Core::Color::White());

                    OcularGraphics->clearBuffers();

                    RenderObjects(visibleObjects, material);

                    camera->setClearColor(oldClear);
                }
                
                //--------------------------------------------------------
                // Determine picked object
                //--------------------------------------------------------

                const uint32_t pickedIndex = GetPickedIndex(camera, x, y);

                if(pickedIndex < visibleObjects.size())
                {
                    result = visibleObjects[pickedIndex];
                }

                OcularResources->saveResource(camera->getRenderTexture(), Core::File("pick.png"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        Graphics::Material* ColorPicker::GetMaterial()
        {
            return OcularResources->getResource<Graphics::Material>("OcularCore/Materials/ColorPicking");
        }

        void ColorPicker::RenderObjects(std::vector<Core::SceneObject*> const& objects, Graphics::Material* material)
        {
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;

            for(auto object : objects)
            {
                auto renderable = object->getRenderable();

                if(renderable)
                {
                    if(renderable->preRender())
                    {
                        material->setUniform("Color", 0, Math::Vector4f((r / 255.0f), (g / 255.0f), 1.0f, 1.0f));

                        renderable->render(material);
                        renderable->postRender();
                    }
                }

                // Increment after every object, even if we dont render it 

                r += 1.0f;

                if(r >= 255.0f)   // We reserve pure white (255, 255, 255, 255) as the camera clear color
                {
                    r = 0.0f;
                    g += 1.0f;
                }

                if(g >= 255.0f)
                {
                    g = 0.0f;
                    b += 1.0f;
                }

                if(b >= 255.0f)
                {
                    OcularLogger->warning("Exceeded maximum number of color combinations", OCULAR_INTERNAL_LOG("ColorPicker", "Pick"));
                    break;
                }
            }
        }

        uint32_t ColorPicker::GetPickedIndex(Core::Camera* camera, uint32_t const x, uint32_t const y)
        {
            uint32_t result = std::numeric_limits<uint32_t>::max();
            auto rtv = camera->getRenderTexture();

            if(rtv)
            {
                rtv->refresh();

                Core::Color color = rtv->getPixel(x, y);
                
                const uint32_t r = static_cast<uint32_t>(color.r * 255.0f);
                const uint32_t g = static_cast<uint32_t>(color.r * 255.0f);
                const uint32_t b = static_cast<uint32_t>(color.r * 255.0f);

                // The colors were assigned in an incremental fashion.
                // So we can easily calculate which object was picked based on the color
                // without having to search through the object container.

                if((r != 255) && (g != 255) && (b != 255))
                {
                    result = (static_cast<uint32_t>(color.b * 65025.0f) + static_cast<uint32_t>(color.g * 255.0f) + static_cast<uint32_t>(color.r));
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}