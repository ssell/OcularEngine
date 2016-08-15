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

#pragma once
#ifndef __H__OCULAR_CORE_LIGHT_MANAGER__H__
#define __H__OCULAR_CORE_LIGHT_MANAGER__H__

#include "Scene/Light/LightSource.hpp"
#include "Scene/Light/GPULight.hpp"
#include "Math/Geometry/Frustum.hpp"

#include <vector>
#include <unordered_map>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class GPUBuffer;
    }

    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class LightManager
         */
        class LightManager
        {
            friend class LightSource;

        public:

            LightManager();
            ~LightManager();

            void updateLights(bool cullVisible = true);

            static const uint32_t LightBufferSlot;    // The GPUBuffer slot used by the LightManager to pass light data

        protected:

            void registerLightSource(LightSource* light);
            void unregisterLightSource(LightSource* light);

            void getVisibleLights(std::vector<LightSource*>& visibleLights, bool cull);
            bool isLightVisible(LightSource const* light, Math::Frustum const& frustum) const;
            bool isPointLightVisible(LightSource const* light, Math::Frustum const& frustum) const;
            bool isSpotlightVisible(LightSource const* light, Math::Frustum const& frustum) const;
            bool isDirectionalLightVisible(LightSource const* light, Math::Frustum const& frustum) const;

            void buildGPUBuffer(uint32_t visibleCount);
            void fillGPUBuffer(std::vector<LightSource*> const& visibleLights);

            //------------------------------------------------------------

            std::unordered_map<std::string, LightSource*> m_Lights;   // Key is UUID string
            std::vector<GPULight> m_GPULights;

            Graphics::GPUBuffer* m_GPUBuffer;  // Buffer to store light data for GPU use
            uint32_t m_BufferLightCapacity;    // Maximum number of lights the current GPU buffer can store

            uint32_t m_PrevNumVisible;

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif 