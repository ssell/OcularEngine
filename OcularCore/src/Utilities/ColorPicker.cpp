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
                    OcularGraphics->clearBuffers(Core::Color::White());

                    RenderObjects(visibleObjects, material);
                }
                
                //--------------------------------------------------------
                // Determine picked object
                //--------------------------------------------------------

                const uint32_t pickedIndex = GetPickedIndex(camera, x, y);

                if(pickedIndex < visibleObjects.size())
                {
                    result = visibleObjects[pickedIndex];
                }

                //OcularResources->saveResource(camera->getRenderTexture(), Core::File("pick.png"));
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

        void ColorPicker::RenderObjects(std::vector<Core::SceneObject*>& objects, Graphics::Material* material)
        {
            auto objectUniformBuffer = OcularGraphics->createUniformBuffer(Graphics::UniformBufferType::PerObject);

            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;

            Core::Camera* camera = OcularCameras->getActiveCamera();

            Math::Matrix4x4 currViewMatrix;
            Math::Matrix4x4 currProjMatrix;

            if(camera)
            {
                currViewMatrix = camera->getViewMatrix();
                currProjMatrix = camera->getProjectionMatrix();
            }

            //------------------------------------------------------------
            // Render each Object
            //------------------------------------------------------------

            Sort(objects);

            for(auto object : objects)
            {
                auto renderable = object->getRenderable();

                if(renderable)
                {
                    if(renderable->preRender())
                    {
                        //------------------------------------------------
                        // Bind the per object uniforms (model matrix, etc.)

                        objectUniformBuffer->setFixedData(object->getUniformData(currViewMatrix, currProjMatrix));
                        objectUniformBuffer->bind();

                        //------------------------------------------------
                        // Set the unique object color

                        material->setUniform("Color", 0, Math::Vector4f((r / 255.0f), (g / 255.0f), (b / 255.0f), 1.0f));
                        
                        //------------------------------------------------
                        // Render the object with the color picking material

                        renderable->render(material);
                        renderable->postRender();
                    }
                }
                
                //--------------------------------------------------------
                // Update the render color after every object (even if that object isn't rendered)
                //--------------------------------------------------------

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
            
            //------------------------------------------------------------
            // Clean Up
            //------------------------------------------------------------

            delete objectUniformBuffer;
        }

        void ColorPicker::Sort(std::vector<Core::SceneObject*>& objects)
        {
            // Modified version of Renderer::sort

            for(auto iter = objects.begin(); iter != objects.end(); )
            {
                if((*iter)->getRenderable() == nullptr)
                {
                    iter = objects.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }

            Core::Camera* camera = OcularCameras->getActiveCamera();

            if(camera)
            {
                const Math::Vector3f cameraPos = camera->getPosition(false);

                std::sort(objects.begin(), objects.end(), [&cameraPos] (Core::SceneObject* first, Core::SceneObject* second)->bool
                {
                    // std::sort returns TRUE if the first argument is before the second argument
                    bool result = true;

                    const uint32_t firstPriority = first->getRenderable()->getRenderPriority();
                    const uint32_t secondPriority = second->getRenderable()->getRenderPriority();

                    if(firstPriority == secondPriority)
                    {
                        const Math::Vector3f firstPos = first->getPosition(false);
                        const Math::Vector3f secondPos = second->getPosition(false);

                        const Math::Vector3f firstToCamera = (firstPos - cameraPos);
                        const Math::Vector3f secondToCamera = (secondPos - cameraPos);

                        const float firstDistance = firstToCamera.dot(firstToCamera);    // Get squared distance to camera
                        const float secondDistance = secondToCamera.dot(secondToCamera);
                        
                        result = (firstDistance < secondDistance);
                    }
                    else
                    {
                        result = (firstPriority < secondPriority);
                    }

                    return result;
                });
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
                
                const uint32_t r = static_cast<uint32_t>(Math::RoundDecimal<float>((color.r * 255.0f), 0));
                const uint32_t g = static_cast<uint32_t>(Math::RoundDecimal<float>((color.g * 255.0f), 0));
                const uint32_t b = static_cast<uint32_t>(Math::RoundDecimal<float>((color.b * 255.0f), 0));

                // The colors were assigned in an incremental fashion.
                // So we can easily calculate which object was picked based on the color
                // without having to search through the object container.

                if((r != 255) && (g != 255) && (b != 255))
                {
                    result = (static_cast<uint32_t>(color.b * 65025.0f) + static_cast<uint32_t>(color.g * 255.0f) + r);
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}