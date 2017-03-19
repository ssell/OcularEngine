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
#ifndef __H__OCULAR_CORE_SCENE_CAMERA__H__
#define __H__OCULAR_CORE_SCENE_CAMERA__H__

#include "Priority.hpp"
#include "Scene/SceneObject.hpp"

#include "Graphics/Texture/RenderTexture.hpp"
#include "Graphics/Texture/DepthTexture.hpp"
#include "Graphics/Viewport.hpp"

#include "Events/AEventListener.hpp"

#include "Math/Geometry/Frustum.hpp"
#include "Math/Bounds/Ray.hpp"

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
        enum class ProjectionType
        {
            Unknown = 0,
            Perspective,
            Orthographic
        };

        struct PerspectiveProjection
        {
            float fieldOfView;
            float aspectRatio;
            float nearClip;
            float farClip;

            PerspectiveProjection();
        };

        struct OrthographicProjection
        {
            float xMin;
            float xMax;
            float yMin;
            float yMax;
            float nearClip;
            float farClip;

            OrthographicProjection();
        };

        /**
         * \class Camera
         */
        class Camera : public SceneObject, AEventListener
        {
        public:

            /**
             * \param[in] name   
             * \param[in] parent
             */
            Camera(std::string const& name, SceneObject* parent = nullptr);

            Camera();

            virtual ~Camera();
            
            /**
             * \param[in] renderTexture
             */
            void setRenderTexture(Graphics::RenderTexture* renderTexture);
            
            /**
             * \return The current render texture
             */
            Graphics::RenderTexture* getRenderTexture();
            
            /**
             * \param[in] depthTexture
             */
            void setDepthTexture(Graphics::DepthTexture* depthTexture);
            
            /**
             * \return The current depth texture
             */
            Graphics::DepthTexture* getDepthTexture();
            
            /**
             * \return The type of projection matrix currently in use.
             */
            ProjectionType getProjectionType() const;
            
            /**
             * \return The settings of the last set perspective matrix.
             */
            PerspectiveProjection getPerspectiveProjection() const;
            
            /**
             * \return The settings of the last set orthographic matrix.
             */
            OrthographicProjection getOrthographicProjection() const;
            
            /**
             * Creates a new orthographic projection matrix and sets it as the projection matrix.
             *
             * \param[in] xMin
             * \param[in] xMax
             * \param[in] yMin
             * \param[in] yMax
             * \param[in] nearClip
             * \param[in] farClip
             */
            void setProjectionOrthographic(float xMin, float xMax, float yMin, float yMax, float nearClip, float farClip);

            void setProjectionOrthographic(OrthographicProjection const& projection);
            
            /**
             * Creates a new perspective projection matrix and sets it as the projection matrix.
             *
             * \param[in] fov
             * \param[in] aspectRatio
             * \param[in] nearClip
             * \param[in] farClip
             */
            void setProjectionPerspective(float fov, float aspectRatio, float nearClip, float farClip);

            void setProjectionPerspective(PerspectiveProjection const& projection);
            
            /**
             * Sets a custom projection matrix.
             *
             * \note The projection will not be updated during a WindowResizeEvent. If the projection needs to
             *       be updated after a resize, then a custom event handler will need to be created.
             *
             * \param[in] matrix
             */
            void setProjectionMatrix(Math::Matrix4x4 const& matrix);
            
            /**
             * \return The view matrix
             */
            Math::Matrix4x4 const& getViewMatrix();
            
            /**
             * \return The projection matrix
             */
            Math::Matrix4x4 const& getProjectionMatrix() const;
            
            /**
             * \param[in] updateFrustum If true, updates the frustum with the latest view/proj matrices.
             * \return The camera's frustum
             */
            Math::Frustum const& getFrustum(bool updateFrustum = true);
            
            /**
             * Sets the camera's priority level
             * \param[in] priority
             */
            void setPriority(Priority priority);
            
            /**
             * \return The camera's priority level. 
             */
            Priority getPriority() const;
            
            /**
             * Sets the camera's viewport.
             *
             * \param[in] x
             * \param[in] y
             * \param[in] width
             * \param[in] height
             * \param[in] minDepth
             * \param[in] maxDepth
             * \param[in] updateMatrix 
             */
            void setViewport(float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f, bool updateMatrix = true);
            
            /**
             * \return Current viewport
             */
            Graphics::Viewport* getViewport() const;

            /**
             * Sets if the viewport is fixed.
             *
             * If the viewport is fixed, it will not update and resize
             * automatically with the window. By default, the viewport
             * is not fixed.
             *
             * \param[in] fixed
             */
            void setFixedViewport(bool fixed);

            /**
             * \return TRUE if the viewport is fixed
             */
            bool getIsFixedViewport() const;
            
            /**
             * Sets if the projection is fixed.
             *
             * If the projection is fixed, it will not update and resize
             * automatically with the window. By default, the projection
             * is not fixed.
             *
             * \param[in] fixed
             */
            void setFixedProjection(bool fixed);
            
            /**
             * \return TRUE if the projection is fixed
             */
            bool getIsFixedProjection() const;

            /**
             *
             */
            void setClearColor(Core::Color const& color);

            /**
             *
             */
            Color const& getClearColor() const;
            
            /**
             * Converts a given screen coordinate to a world-space position.
             *
             * \param[in] screenPos Screen coordinate to convert. (0,0) is top-left, and (width, height) is bottom-right.
             * \param[in] depth     Depth of coordinate. See GraphicsDriver::getDepthRange for the appropriate value if point should be on near plane.
             *
             * \return World-space coordinate.
             */
            Math::Vector3f screenToWorld(Math::Vector2i const& screenPos, float depth);

            /**
             * Converts a given world space position to a screen-space coordinate.
             *
             * \param[in] pos
             */
            Math::Vector2i worldToScreen(Math::Vector3f const& worldPos);

            /**
             * Returns a ray projected from the camera at the given screen coordinates.
             *
             * \param[in] x
             * \param[in] y
             */
            Math::Ray getPickRay(Math::Vector2i const& screenPos);

            /**
             * Handles WindowResizeEvent instances.
             *
             * Upon a WindowResizeEvent, the viewport and projection (if perspective)
             * will be updated according to the new window size.
             * 
             * The viewport and projection updating will not occur if
             * they are set to fixed (setFixedProjection and setFixedViewport).
             */
            virtual bool onEvent(std::shared_ptr<AEvent> event) override;

        protected:

            void onCreation();
            void exposeVariables();

            void updateViewport(float width, float height);

            /**
             * Converts the screen-space coordinates to normalized-space.
             */
            Math::Vector4f screenToNDC(Math::Vector2i const& screenPos, float depth) const;

            //------------------------------------------------------------

            ProjectionType m_ProjType;

            PerspectiveProjection m_PerspectiveProj;
            OrthographicProjection m_OrthographicProj;

            Math::Matrix4x4 m_ViewMatrix;
            Math::Matrix4x4 m_ProjMatrix;

            Math::Frustum m_Frustum;

            Graphics::RenderTexture* m_RenderTexture;
            Graphics::DepthTexture* m_DepthTexture;
            Graphics::Viewport* m_Viewport;

            Core::Color m_ClearColor;

            Priority m_Priority;

            bool m_IsFixedViewport;
            bool m_IsFixedProjection;
            bool m_IsFrustumDirty;

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