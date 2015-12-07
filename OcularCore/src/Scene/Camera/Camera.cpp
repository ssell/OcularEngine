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

#include "Scene/Camera/Camera.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Camera::Camera(std::string const& name, SceneObject* parent)
            : SceneObject(name, parent),
              m_RenderTexture(nullptr),
              m_Priority(Priority::Medium)
        {
            OcularCameras->addCamera(this);
        }

        Camera::~Camera()
        {
            OcularCameras->removeCamera(this);
            m_RenderTexture = nullptr;

            if(m_Viewport)
            {
                delete m_Viewport;
                m_Viewport = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Camera::setRenderTexture(Graphics::RenderTexture* renderTexture)
        {
            m_RenderTexture = renderTexture;
        }

        Graphics::RenderTexture* Camera::getRenderTexture()
        {
            return m_RenderTexture;
        }

        void Camera::setDepthTexture(Graphics::DepthTexture* depthTexture)
        {
            m_DepthTexture = depthTexture;
        }

        Graphics::DepthTexture* Camera::getDepthTexture()
        {
            return m_DepthTexture;
        }

        void Camera::setProjectionOrthographic(float const xMin, float const xMax, float const yMin, float const yMax, 
                                               float const nearClip, float const farClip)
        {
            m_ProjMatrix = Math::Matrix4x4f::CreateOrthographicMatrix(xMin, xMax, yMin, yMax, nearClip, farClip);
            m_Frustum.setProjectionOrthographic(xMin, xMax, yMin, yMax, nearClip, farClip);
        }

        void Camera::setProjectionPerspective(float const fov, float const aspectRatio, float const nearClip, float const farClip)
        {
            m_ProjMatrix = Math::Matrix4x4f::CreatePerspectiveMatrix(fov, aspectRatio, nearClip, farClip);
            m_Frustum.setProjectionPerspective(fov, aspectRatio, nearClip, farClip);
        }

        void Camera::setProjectionMatrix(Math::Matrix4x4f const& matrix)
        {
            m_ProjMatrix = matrix;
        }

        Math::Matrix4x4f const& Camera::getViewMatrix()
        {
            m_ViewMatrix = Math::Matrix4x4f::CreateLookAtMatrix(m_Transform.getPosition(), Math::Vector3f(0.0f, 0.0f, 0.0f));
            return m_ViewMatrix;
        }

        Math::Matrix4x4f const& Camera::getProjectionMatrix() const
        {
            return m_ProjMatrix;
        }

        Math::Frustum const& Camera::getFrustum() const
        {
            return m_Frustum;
        }

        void Camera::setPriority(Priority priority)
        {
            m_Priority = priority;
        }

        Priority Camera::getPriority() const
        {
            return m_Priority;
        }

        void Camera::setViewport(float const x, float const y, float const width, float const height, float const minDepth, float const maxDepth)
        {
            if(m_Viewport)
            {
                delete m_Viewport;
            }

            m_Viewport = OcularGraphics->createViewport(x, y, width, height, minDepth, maxDepth);

            if(OcularCameras->getActiveCamera() == this)
            {
                m_Viewport->bind();
            }
        }

        Graphics::Viewport* Camera::getViewport()
        {
            return m_Viewport;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}