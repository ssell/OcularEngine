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

#include "Renderer/Renderer.hpp"
#include "Renderer/RenderPriority.hpp"

#include "Scene/SceneObject.hpp"
#include "Scene/ARenderable.hpp"

#include "OcularEngine.hpp"

#include <algorithm>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Renderer::Renderer()
            : m_UniformBufferPerObject(nullptr)
        {

        }

        Renderer::~Renderer()
        {
            if(m_UniformBufferPerObject)
            {
                delete m_UniformBufferPerObject;
                m_UniformBufferPerObject = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Renderer::sort(std::vector<SceneObject*>& objects)
        {
            Camera* camera = OcularCameras->getActiveCamera();

            if(camera)
            {
                const Math::Vector3f cameraPos = camera->getPosition(false);             // Use world position

                std::sort(objects.begin(), objects.end(), [&cameraPos] (SceneObject* first, SceneObject* second)->bool
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

                        if(firstPriority < static_cast<uint32_t>(RenderPriority::Transparent))
                        {
                            // Non-transparent/overlay elements are rendered front-to-back
                            result = (firstDistance < secondDistance);
                        }
                        else
                        {
                            // Transparent/overlay elements are rendered back-to-front
                            result = (firstDistance > secondDistance);
                        }
                    }
                    else
                    {
                        result = (firstPriority < secondPriority);
                    }

                    return result;
                });
            }
        }

        void Renderer::bindUniforms(SceneObject* object)
        {
            if(!m_UniformBufferPerObject)
            {
                m_UniformBufferPerObject = OcularGraphics->createUniformBuffer(Graphics::UniformBufferType::PerObject);
            }

            if(object)
            {
                m_UniformBufferPerObject->setFixedData(object->getUniformData());
            }
            else
            {
                // If NULL, use a default uniform buffer (identity model matrix, etc.)
                Graphics::UniformPerObject uniformBuffer;
                m_UniformBufferPerObject->setFixedData(uniformBuffer); 
            }
            
            m_UniformBufferPerObject->bind();
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}