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

#include "Scene/Camera/Camera.hpp"
#include "Scene/Camera/CameraRenderable.hpp"

#include "Scene/SceneObjectRegistrar.hpp"
#include "Events/Events/WindowResizeEvent.hpp"
#include "Renderer/Window/Window.hpp"

#include "OcularEngine.hpp"

OCULAR_REGISTER_SCENEOBJECT(Ocular::Core::Camera, "Camera");

//------------------------------------------------------------------------------------------

static const float DefaultFOV    = 60.0f;
static const float DefaultNear   = 0.01f;
static const float DefaultFar    = 1000.0f;
static const float DefaultWidth  = 1024.0f;
static const float DefaultHeight = 768.0f;

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PerspectiveProjection::PerspectiveProjection()
            : fieldOfView(DefaultFOV),
              aspectRatio(DefaultWidth / DefaultHeight),
              nearClip(DefaultNear),
              farClip(DefaultFar)
        {

        }

        OrthographicProjection::OrthographicProjection()
            :  xMin(0.0f),
               xMax(0.0f),
               yMin(0.0f),
               yMax(0.0f),
               nearClip(DefaultNear),
               farClip(DefaultFar)
        {
        
        }

        Camera::Camera(std::string const& name, SceneObject* parent)
            : SceneObject(name, parent, "Camera"),
              m_ProjType(ProjectionType::Perspective),
              m_RenderTexture(nullptr),
              m_DepthTexture(nullptr),
              m_Viewport(nullptr),
              m_Priority(Priority::Medium),
              m_IsFixedViewport(false),
              m_IsFixedProjection(false),
              m_ClearColor(Core::Color::DefaultClearGray())

        {
            onCreation();
            exposeVariables();
        }

        Camera::Camera()
            : SceneObject("Camera", nullptr, "Camera"),
              m_ProjType(ProjectionType::Perspective),
              m_RenderTexture(nullptr),
              m_DepthTexture(nullptr),
              m_Viewport(nullptr),
              m_Priority(Priority::Medium),
              m_IsFixedViewport(false),
              m_IsFixedProjection(false),
              m_ClearColor(Core::Color::DefaultClearGray())
        {
            onCreation();
            exposeVariables();
        }

        Camera::~Camera()
        {
            OcularEvents->unregisterListener(this);

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
            m_Frustum.setProjectionMatrix(m_ProjMatrix);
        }

        void Camera::setProjectionOrthographic(OrthographicProjection const& projection)
        {
            setProjectionOrthographic(projection.xMin, projection.xMax, projection.yMin, projection.yMax, projection.nearClip, projection.farClip);
        }

        void Camera::setProjectionPerspective(float const fov, float const aspectRatio, float const nearClip, float const farClip)
        {
            m_ProjType = ProjectionType::Perspective;

            m_PerspectiveProj.fieldOfView = fov;
            m_PerspectiveProj.aspectRatio = aspectRatio;
            m_PerspectiveProj.nearClip    = nearClip;
            m_PerspectiveProj.farClip     = farClip;

            m_ProjMatrix = Math::Matrix4x4::CreatePerspectiveMatrix(fov, aspectRatio, nearClip, farClip);
            m_Frustum.setProjectionMatrix(m_ProjMatrix);
        }

        void Camera::setProjectionPerspective(PerspectiveProjection const& projection)
        {
            setProjectionPerspective(projection.fieldOfView, projection.aspectRatio, projection.nearClip, projection.farClip);
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

        Math::Frustum const& Camera::getFrustum(bool const updateFrustum) 
        {
            if(updateFrustum)
            {
                m_Frustum.setViewMatrix(m_ViewMatrix);
                m_Frustum.setProjectionMatrix(m_ProjMatrix);
                m_Frustum.rebuild();
            }

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

        void Camera::setViewport(float const x, float const y, float const width, float const height, float const minDepth, float const maxDepth, bool updateMatrix)
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
            
            if(updateMatrix)
            {
                if(m_ProjType == ProjectionType::Perspective)
                {
                    setProjectionPerspective(m_PerspectiveProj.fieldOfView, (width / height), m_PerspectiveProj.nearClip, m_PerspectiveProj.farClip);
                }
                else
                {
                    setProjectionOrthographic(m_OrthographicProj.xMin, (m_OrthographicProj.xMin + width), 
                                              m_OrthographicProj.yMin, (m_OrthographicProj.yMin + height),
                                              m_OrthographicProj.nearClip, m_OrthographicProj.farClip);
                }
            }
        }

        Graphics::Viewport* Camera::getViewport() const
        {
            return m_Viewport;
        }

        bool Camera::onEvent(std::shared_ptr<AEvent> event)
        {
            if(event->isType<WindowResizeEvent>())
            {
                WindowResizeEvent* resizeEvent = dynamic_cast<WindowResizeEvent*>(event.get());
                AWindow* window = resizeEvent->window;

                if(window)
                {
                    Graphics::RenderTexture* texture = window->getRenderTexture();

                    if((texture) && (texture == m_RenderTexture))
                    {
                        updateViewport(static_cast<float>(resizeEvent->width), static_cast<float>(resizeEvent->height));
                    }
                }
            }

            return true;
        }

        void Camera::setFixedViewport(bool fixed)
        {
            m_IsFixedViewport = fixed;
        }

        bool Camera::getIsFixedViewport() const
        {
            return m_IsFixedViewport;
        }

        void Camera::setFixedProjection(bool fixed)
        {
            m_IsFixedProjection = fixed;
        }

        bool Camera::getIsFixedProjection() const
        {
            return m_IsFixedProjection;
        }

        void Camera::setClearColor(Core::Color const& color)
        {
            m_ClearColor = color;
        }

        Color const& Camera::getClearColor() const
        {
            return m_ClearColor;
        }

        Math::Vector3f Camera::screenToWorld(Math::Vector2i const& screenPos, float const depth)
        {
            /**
             * To convert from screen space to world space we simply do the reverse
             * of the typical rendering transformations:
             *
             *     1. Convert from screen-space to NDC-space
             *     2. Calculate inverse view-projection matrix
             *     3. Transform NDC-space coordinate by view-projection inverse
             *     4. Divide resulting transformed point by w (perspective division).
             */

            Math::Vector3f result;

            Math::Vector4f  normPos     = screenToNDC(screenPos, depth);
            Math::Matrix4x4 viewProjInv = (m_ProjMatrix * m_ViewMatrix).getInverse();
            Math::Vector4f  projPos     = viewProjInv * normPos;

            projPos.w = 1.0f / projPos.w;

            result.x = projPos.x * projPos.w;
            result.y = projPos.y * projPos.w;
            result.z = projPos.z * projPos.w;

            return result;
        }

        Math::Vector2i Camera::worldToScreen(Math::Vector3f const& worldPos)
        {
            Math::Vector2i result;
            
            const Math::Matrix4x4 viewProjMatrix = getProjectionMatrix() * m_Transform.getModelMatrix();
            const Math::Vector3f projSpacePoint = viewProjMatrix * worldPos;

            result.x = static_cast<int32_t>(Math::RoundDecimal(((projSpacePoint.x + 1.0f) * 0.5f), 0) * m_Viewport->getWidth());
            result.y = static_cast<int32_t>(Math::RoundDecimal(((1.0f - projSpacePoint.y) * 0.5f), 0) * m_Viewport->getHeight());

            return result;
        }

        Math::Ray Camera::getPickRay(Math::Vector2i const& screenPos)
        {
            /**
             * To generate a pick ray we must do two things:
             *
             *     1. Convert screen-space coordinates to world-space
             *     2. Calculate a direction for the ray
             */

            float nearDepth = 0.0f;
            float farDepth = 0.0f;

            OcularGraphics->getDepthRange(&nearDepth, &farDepth);

            const Math::Vector3f worldPosNear = screenToWorld(screenPos, nearDepth);
            const Math::Vector3f worldPosFar = screenToWorld(screenPos, farDepth);

            const Math::Vector3f rayDir = (worldPosFar - worldPosNear).getNormalized();

            return Math::Ray(worldPosNear, rayDir);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Camera::onCreation()
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

            //------------------------------------------------------------
            // Add renderable

            auto renderable = setRenderable<CameraRenderable>();

            if(renderable)
            {
                renderable->initialize();
            }
        }

        void Camera::exposeVariables()
        {
            OCULAR_EXPOSE(m_ClearColor);
        }

        void Camera::updateViewport(float const width, float const height)
        {
            if((!Math::IsEqual<float>(width, m_Viewport->getWidth())) || (!Math::IsEqual<float>(height, m_Viewport->getHeight())))
            {
                if(!m_IsFixedViewport)
                {
                    setViewport(m_Viewport->getOriginX(), m_Viewport->getOriginY(), width, height, m_Viewport->getMinDepth(), m_Viewport->getMaxDepth());
                }

                if(!m_IsFixedProjection)
                {
                    if(m_ProjType == ProjectionType::Perspective)
                    {
                        m_PerspectiveProj.aspectRatio = (static_cast<float>(width) / static_cast<float>(height));
                        setProjectionPerspective(m_PerspectiveProj.fieldOfView, m_PerspectiveProj.aspectRatio, m_PerspectiveProj.nearClip, m_PerspectiveProj.farClip);
                    }
                }
            }
        }

        Math::Vector4f Camera::screenToNDC(Math::Vector2i const& screenPos, float const depth) const
        {
            /** 
             * Screen space ranges from:
             *
             *     0 <= x <= screen width
             *     0 <= y <= screen height
             *
             * Where (0,0) is the top-left corner.
             *
             * Normalized space ranges from:
             *
             *     -1.0 <= x <= 1.0
             *     -1.0 <= y <= 1.0
             *
             * Where (0,0) is the screen center.
             *
             * So, we must transform the screen-space x/y to ndc-space x/y.
             * .z is the depth and .w is 1.0. 
             */

            Math::Vector4f result(0.0f, 0.0f, depth, 1.0f);

            if(m_Viewport)
            {
                // Convert screen x/y to a [0.0,1.0] normalized value

                result.x = (static_cast<float>(screenPos.x) / m_Viewport->getWidth());
                result.y = (static_cast<float>(screenPos.y) / m_Viewport->getHeight());

                // Fit the normalized value to the [-1.0,1.0] range of NDC space

                result.x = (result.x * 2.0f) - 1.0f;
                result.y = 1.0f - (result.y * 2.0f);      // Remember y is reversed in screen-space
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}