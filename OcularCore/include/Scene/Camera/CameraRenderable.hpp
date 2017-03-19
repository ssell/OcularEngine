/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_CORE_RENDERABLE_CAMERA__H__
#define __H__OCULAR_CORE_RENDERABLE_CAMERA__H__

#include "Scene/ARenderable.hpp"

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
         * \class CameraRenderable
         *
         * Implementation of ARenderable used by Cameras during debug rendering.
         * Displays the bounds of the camera's viewing frustum.
         */
        class CameraRenderable : public ARenderable
        {
        public:

            CameraRenderable(std::string const& name = "CameraRenderable", SceneObject* parent = nullptr);
            virtual ~CameraRenderable();

            virtual bool initialize() override;

            virtual bool preRenderDebug() override;
            virtual void renderDebug() override;
            virtual void postRenderDebug() override;

        protected:
            
            bool buildFrustumMesh();
            bool buildFrustumMaterial();

            // Graphics objects used to render the debug view frustum bounds
            
            Graphics::Mesh* m_FrustumMesh;
            Graphics::Material* m_FrustumMaterial;

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
