/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_CORE_SCENE_CAMERA__H__
#define __H__OCULAR_CORE_SCENE_CAMERA__H__

#include "Priority.hpp"
#include "Scene/SceneObject.hpp"
#include "Graphics/Texture/RenderTexture.hpp"
#include "Math/Geometry/Frustum.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class Camera
         */
        class Camera : public SceneObject
        {
        public:

            Camera(std::string const& name, SceneObject* parent = nullptr);
            virtual ~Camera();

            void setRenderTexture(Graphics::RenderTexture* renderTexture);
            Graphics::RenderTexture const* getRenderTexture() const;

            void setProjectionOrthographic(float xMin, float xMax, float yMin, float yMax, float nearClip, float farClip);
            void setProjectionPerspective(float fov, float aspectRatio, float nearClip, float farClip);

            Math::Matrix4x4f const& getViewMatrix() const;
            Math::Matrix4x4f const& getProjectionMatrix() const;
            Math::Frustum const& getFrustum() const;

            void setPriority(Priority priority);
            Priority getPriority() const;

        protected:

            Math::Matrix4x4f m_ViewMatrix;
            Math::Matrix4x4f m_ProjMatrix;

            Math::Frustum m_Frustum;

            Graphics::RenderTexture* m_RenderTexture;

            Priority m_Priority;

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