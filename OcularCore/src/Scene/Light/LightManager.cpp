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

#include "Scene/Light/LightManager.hpp"
#include "Math/Bounds/BoundsSphere.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        const uint32_t LightManager::LightBufferSlot = 8;

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        LightManager::LightManager()
            : m_GPUBuffer(nullptr),
              m_BufferLightCapacity(128),
              m_PrevNumVisible(0)
        {
            m_GPULights.resize(m_BufferLightCapacity);
        }

        LightManager::~LightManager()
        {
            if(m_GPUBuffer)
            {
                delete m_GPUBuffer;
                m_GPUBuffer = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void LightManager::updateLights(bool const cullVisible)
        {
            std::vector<LightSource*> visibleLights;

            getVisibleLights(visibleLights, cullVisible);

            buildGPUBuffer(static_cast<uint32_t>(visibleLights.size()));    // Builds a new buffer if current is NULL or too small
            fillGPUBuffer(visibleLights);                                   // Also performs the binding operation

            m_PrevNumVisible = static_cast<uint32_t>(visibleLights.size());
        }

        void LightManager::setAmbientLightColor(Color const& color)
        {
            m_GPUAmbientLight.color = color;
        }

        Color LightManager::getAmbientLightColor() const
        {
            return m_GPUAmbientLight.color;
        }

        void LightManager::setAmbientLightIntensity(float const intensity)
        {
            m_GPUAmbientLight.parameters.x = intensity;
        }

        float LightManager::getAmbientLightIntensity() const
        {
            return m_GPUAmbientLight.parameters.x;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void LightManager::registerLightSource(LightSource* light)
        {
            if(light)
            {
                const std::string uuidStr = light->getUUID().toString();
                auto find = m_Lights.find(uuidStr);

                if(find == m_Lights.end())
                {
                    m_Lights.insert(std::make_pair(uuidStr, light));
                }
            }
        }

        void LightManager::unregisterLightSource(LightSource* light)
        {
            if(light)
            {
                const std::string uuidStr = light->getUUID().toString();
                auto find = m_Lights.find(uuidStr);

                if(find != m_Lights.end())
                {
                    m_Lights.erase(find);
                }
            }
        }

        void LightManager::updateUUID(UUID const& uuid)
        {
            const std::string uuidStr = uuid.toString();
            auto find = m_Lights.find(uuidStr);

            if(find != m_Lights.end())
            {
                auto object = find->second;

                m_Lights.erase(find);

                m_Lights.insert(std::make_pair(object->getUUID().toString(), object));
            }
        }

        void LightManager::getVisibleLights(std::vector<LightSource*>& visibleLights, bool cull)
        {
            visibleLights.reserve(m_Lights.size());

            if(cull)
            {
                Camera* activeCamera = OcularCameras->getActiveCamera();

                if(activeCamera)
                {
                    const Math::Frustum cameraFrustum = activeCamera->getFrustum();

                    for(auto pair : m_Lights)
                    {
                        if(isLightVisible(pair.second, cameraFrustum))
                        {
                            visibleLights.emplace_back(pair.second);
                        }
                    }
                }
            }
            else
            {
                for(auto pair : m_Lights)
                {
                    visibleLights.emplace_back(pair.second);
                }
            }
        }

        bool LightManager::isLightVisible(LightSource const* light, Math::Frustum const& frustum) const
        {
            bool result = false;

            if(light)
            {
                if(light->isActive())
                {
                    if(Math::IsEqual(light->getLightType(), 1.0f))
                    {
                        result = isPointLightVisible(light, frustum);
                    }
                    else if(Math::IsEqual(light->getLightType(), 2.0f))
                    {
                        result = isSpotlightVisible(light, frustum);
                    }
                    else if(Math::IsEqual(light->getLightType(), 3.0f))
                    {
                        result = isDirectionalLightVisible(light, frustum);
                    }
                }
            }

            return result;
        }

        bool LightManager::isPointLightVisible(LightSource const* light, Math::Frustum const& frustum) const
        {
            // Perform a bounding sphere intersection with the current camera's view frustum to determine visibility.
            return frustum.contains(Math::BoundsSphere(light->getPosition(false), light->getRange()));
        }

        bool LightManager::isSpotlightVisible(LightSource const* light, Math::Frustum const& frustum) const
        {
            // For simplicity (and speed), again just perform a simple bounding sphere check.
            return frustum.contains(Math::BoundsSphere(light->getPosition(false), light->getRange()));
        }

        bool LightManager::isDirectionalLightVisible(LightSource const* light, Math::Frustum const& frustum) const
        {
            // A directional light affects the entire scene, so it is always visible.
            return true;
        }

        void LightManager::buildGPUBuffer(uint32_t const visibleCount)
        {
            if(visibleCount > m_BufferLightCapacity)
            {
                // If we exceed the capacity of the current light buffer 
                // then we need to increase the capacity and rebuild it.

                while(visibleCount > m_BufferLightCapacity)
                {
                    m_BufferLightCapacity *= 2;
                }

                m_GPULights.resize(m_BufferLightCapacity);
                
                delete m_GPUBuffer;
                m_GPUBuffer = nullptr;
            }

            if(!m_GPUBuffer)
            {
                Graphics::GPUBufferDescriptor descr;

                descr.cpuAccess   = Graphics::GPUBufferAccess::Write;
                descr.gpuAccess   = Graphics::GPUBufferAccess::Read;
                descr.elementSize = sizeof(GPULight);
                descr.bufferSize  = m_BufferLightCapacity * descr.elementSize;
                descr.stage       = Graphics::GPUBufferStage::Fragment;
                descr.slot        = LightBufferSlot;
                
                m_GPUBuffer = OcularGraphics->createGPUBuffer(descr);
                m_GPUBuffer->build(nullptr);
            } 
        }

        void LightManager::fillGPUBuffer(std::vector<LightSource*> const& visibleLights)
        {
            if(m_GPUBuffer && visibleLights.size())
            {
                const uint32_t currNumVisible = static_cast<uint32_t>(visibleLights.size());

                //--------------------------------------------------------
                // Reset the unused part of the source buffer

                if(m_PrevNumVisible > currNumVisible)
                {
                    std::fill((m_GPULights.begin() + currNumVisible), (m_GPULights.begin() + m_PrevNumVisible), GPULight());
                }
                
                //--------------------------------------------------------
                // Populate the source buffer

                // Index 0 is always the ambient light properties

                m_GPULights[0] = m_GPUAmbientLight;

                // Fill the dynamic lights

                for(uint32_t i = 0; i < visibleLights.size(); i++)
                {
                    // Offset m_GPULights index by 1 to account for ambient at index 0
                    m_GPULights[(i + 1)](visibleLights[i]);
                }
                
                //--------------------------------------------------------
                // Transfer data to the GPU buffer

                if(m_GPUBuffer->write(&m_GPULights[0], 0, sizeof(GPULight) * m_BufferLightCapacity))
                {
                    m_GPUBuffer->bind();
                }
                else
                {
                    OcularLogger->warning("Failed to fill GPU light buffer", OCULAR_INTERNAL_LOG("LightManager", "fillGPUBuffer"));
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}