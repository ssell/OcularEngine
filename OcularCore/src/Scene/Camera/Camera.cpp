/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#include "Events/Events/WindowResizeEvent.hpp"
#include "Renderer/Window/Window.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

static const float DefaultFOV    = 90.0f;
static const float DefaultNear   = 0.01f;
static const float DefaultFar    = 10000.0f;
static const float DefaultWidth  = 1024.0f;
static const float DefaultHeight = 768.0f;

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Camera::Camera(std::string const& name, SceneObject* parent)
            : SceneObject(name, parent),
              m_ProjType(ProjectionType::Perspective),
              m_RenderTexture(nullptr),
              m_DepthTexture(nullptr),
              m_Viewport(nullptr),
              m_Priority(Priority::Medium),
              m_IsFixedViewport(false),
              m_IsFixedProjection(false)

        {
            OcularCameras->addCamera(this);
            OcularEvents->registerListener(this, Priority::Medium);

            //------------------------------------------------------------
            // Set default viewport and projection

            auto mainWindow = OcularWindows->getMainWindow();

            float width  = DefaultWidth;
            float height = DefaultHeight;

            if(mainWindow)
            {
                const WindowDescriptor descriptor = mainWindow->getDescriptor();

                width  = static_cast<float>(descriptor.width);
                height = static_cast<float>(descriptor.height);

                // If this is the only camera set it's RenderTexture, etc. to the main window
                if(this == OcularCameras->getMainCamera())
                {
                    m_RenderTexture = mainWindow->getRenderTexture();
                    m_DepthTexture = mainWindow->getDepthTexture();
                }
            }

            m_PerspectiveProj.fieldOfView = DefaultFOV;
            m_PerspectiveProj.aspectRatio = (width / height);
            m_PerspectiveProj.nearClip = DefaultNear;
            m_PerspectiveProj.farClip = DefaultFar;

            setViewport(0.0f, 0.0f, width, height);
            setProjectionPerspective(m_PerspectiveProj.fieldOfView, m_PerspectiveProj.aspectRatio, m_PerspectiveProj.nearClip, m_PerspectiveProj.farClip);
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

        ProjectionType Camera::getProjectionType() const
        {
            return m_ProjType;
        }

        PerspectiveProjection Camera::getPerspectiveProjection() const
        {
            return m_PerspectiveProj;
        }

        OrthographicProjection Camera::getOrthographicProjection() const
        {
            return m_OrthographicProj;
        }

        void Camera::setProjectionOrthographic(float const xMin, float const xMax, float const yMin, float const yMax, 
                                               float const nearClip, float const farClip)
        {
            m_ProjType = ProjectionType::Orthographic;

            m_OrthographicProj.xMin     = xMin;
            m_OrthographicProj.xMax     = xMax;
            m_OrthographicProj.yMin     = yMin;
            m_OrthographicProj.yMax     = yMax;
            m_OrthographicProj.nearClip = nearClip;
            m_OrthographicProj.farClip  = farClip;

            m_ProjMatrix = Math::Matrix4x4::CreateOrthographicMatrix(xMin, xMax, yMin, yMax, nearClip, farClip);
            m_Frustum.setProjectionOrthographic(xMin, xMax, yMin, yMax, nearClip, farClip);
        }

        void Camera::setProjectionPerspective(float const fov, float const aspectRatio, float const nearClip, float const farClip)
        {
            m_ProjType = ProjectionType::Perspective;

            m_PerspectiveProj.fieldOfView = fov;
            m_PerspectiveProj.aspectRatio = aspectRatio;
            m_PerspectiveProj.nearClip    = nearClip;
            m_PerspectiveProj.farClip     = farClip;

            m_ProjMatrix = Math::Matrix4x4::CreatePerspectiveMatrix(fov, aspectRatio, nearClip, farClip);
            m_Frustum.setProjectionPerspective(fov, aspectRatio, nearClip, farClip);
        }

        void Camera::setProjectionMatrix(Math::Matrix4x4 const& matrix)
        {
            m_ProjType = ProjectionType::Unknown;
            m_ProjMatrix = matrix;
        }

        Math::Matrix4x4 const& Camera::getViewMatrix()
        {
            getModelMatrix(m_ViewMatrix);
            m_ViewMatrix.invert();

            return m_ViewMatrix;
        }

        Math::Matrix4x4 const& Camera::getProjectionMatrix() const
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

        Graphics::Viewport* Camera::getViewport() const
        {
            return m_Viewport;
        }

        bool Camera::onEvent(std::shared_ptr<AEvent> event)
        {
            if(event->isType<Events::WindowResizeEvent>())
            {
                Events::WindowResizeEvent* resizeEvent = dynamic_cast<Events::WindowResizeEvent*>(event.get());

                if(!m_IsFixedProjection)
                {
                    if(m_ProjType == ProjectionType::Perspective)
                    {
                        m_PerspectiveProj.aspectRatio = (static_cast<float>(resizeEvent->width) / static_cast<float>(resizeEvent->height));
                        setProjectionPerspective(m_PerspectiveProj.fieldOfView, m_PerspectiveProj.aspectRatio, m_PerspectiveProj.nearClip, m_PerspectiveProj.farClip);
                    }
                    //else if(m_ProjType == ProjectionType::Orthographic)
                    //{
                        // Ortho xMin/xMax, etc. may not be set on width/height
                        //setProjectionOrthographic(0.0f, m_ProjWidth, 0.0f, m_ProjHeight, m_NearClip, m_FarClip);
                    //}
                    //else
                    //{
                        // Unknown. Do nothing
                    //}
                }

                if(!m_IsFixedViewport)
                {
                    float originX     = 0.0f;
                    float originY     = 0.0f;
                    float width       = DefaultWidth;
                    float height      = DefaultHeight;
                    float minDepth    = 0.0f;
                    float maxDepth    = 1.0f;

                    if(m_Viewport)
                    {
                        originX  = m_Viewport->getOriginX();
                        originY  = m_Viewport->getOriginY();
                        width    = m_Viewport->getWidth();
                        height   = m_Viewport->getHeight();
                        minDepth = m_Viewport->getMinDepth();
                        maxDepth = m_Viewport->getMaxDepth();
                    }

                    setViewport(originX, originY, width, height, minDepth, maxDepth);
                }
            }

            return true;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}