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
#ifndef __H__OCULAR_CORE_RENDERABLE_POINT_LIGHT__H__
#define __H__OCULAR_CORE_RENDERABLE_POINT_LIGHT__H__

#include "Scene/ARenderable.hpp"

#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class Material;
        class Mesh;
    }

    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class PointLightRenderable
         *
         * Implementation of ARenderable used by Point Lights during debug rendering.
         * Displays a billboard at the origin of the light, and optionally also displays
         * a rendering of the light bounds.
         */
        class PointLightRenderable : public ARenderable
        {
        public:

            PointLightRenderable(std::string const& name = "PointLightRenderable", SceneObject* parent = nullptr);
            virtual ~PointLightRenderable();

            virtual bool initialize() override;

            virtual bool preRenderDebug() override;
            virtual void renderDebug() override;
            virtual void postRenderDebug() override;

        protected:

            bool buildExtentsMaterial();
            bool buildExtentsMesh();

            // Graphics objects used to render the optional light extents rings

            static Graphics::Material* m_ExtentsMaterial;
            static Graphics::Mesh* m_ExtentsMesh;

            static uint32_t m_InternalReference;

            Math::Quaternion m_StoredRotation;
            Math::Vector3f m_StoredScale;

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
