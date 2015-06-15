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
#ifndef __H__OCULAR_MATH_FRUSTUM__H__
#define __H__OCULAR_MATH_FRUSTUM__H__

#include "Math/Matrix4x4.hpp"
#include "Math/Geometry/Plane.hpp"
#include <array>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Math
     * @{
     */
    namespace Math
    {
        class BoundsAABB;
        class BoundsOBB;
        class BoundsSphere;

        /**
         * \class Frustum
         *
         * A frustum is defined by a view and projection matrix and is used
         * to perform culling tests which define what is and isn't visible.
         *
         * For an object (point, bounding volume, etc.) to be considered inside
         * of the frustum, it must not be outside of any of the 6 infinite planes
         * that define it. The outside of a plane is defined as the positive 
         * half-space: the direction in which the plane's normal is pointing.
         *
         * If an object is either inside and/or intersects all of the individual
         * planes, then it is inside the frustum.
         */
        class Frustum
        {
        public:

            Frustum();
            ~Frustum();

            //------------------------------------------------------------
            // View and Projection matrix setting
            //------------------------------------------------------------

            /**
             * \param[in] upVector
             */
            void setUp(Vector3f const& upVector);

            /**
             * Sets the view matrix that helps to define this frustum.
             * \param[in] viewMatrix
             */
            void setView(Matrix4x4f const& viewMatrix);

            /**
             * Sets the position and rotation that defines the view matrix of this frustum.
             *
             * \param[in] position
             * \param[in] rotation
             */
            void setView(Vector3f const& position, Quaternion const& rotation);

            /**
             * Sets the projection matrix that helps to define this frustum.
             * \param[in] projectionMatrix
             */
            void setProjection(Matrix4x4f const& projectionMatrix);

            /**
             * Sets the properties of an orthographic projection that defines the
             * projection matrix of this frustum.
             * 
             * \param[in] xMin     Left-side of near clip plane
             * \param[in] xMax     Right-side of near clip plane
             * \param[in] yMin     Bottom-side of near clip plane
             * \param[in] yMax     Top-side of near clip plane
             * \param[in] nearClip Distance from point-of-view to near clip plane.
             * \param[in] farClip  Distance from point-of-view to far clip plane.
             */
            void setProjection(float xMin, float xMax, float yMin, float yMax, float nearClip, float farClip);

            /**
             * Sets the properties of an perspective projection that defines the
             * projection matrix of this frustum.
             * 
             * \param[in] fov         Specifies the field of view angle, in degrees, in the y direction.
             * \param[in] aspectRatio Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of width to height.
             * \param[in] nearClip    Distance from point-of-view to near clip plane.
             * \param[in] farClip     Distance from point-of-view to far clip plane.
             */
            void setProjection(float fov, float aspectRatio, float nearClip, float farClip);

            /**
             * Sets the combination view-projection matrix that this frustum is based off of.
             * \param[in] viewProjection
             */
            void setViewProjection(Matrix4x4f const& viewProjection);

            //------------------------------------------------------------
            // Misc Getters
            //------------------------------------------------------------

            /**
             * \return The point this frustum originates from.
             */
            Vector3f const& getPointOfView() const;

            /**
             * \return The direction this frustum is facing.
             */
            Vector3f const& getDirection() const;

            //------------------------------------------------------------
            // Containment Testing
            //------------------------------------------------------------

            /**
             * Tests to determine if the frustum contains the specified bounding sphere.
             *
             * \param[in] point
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(Point3f const& point) const;

            /**
             * Tests to determine if the frustum contains the specified bounding sphere.
             *
             * \param[in] bounds
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsSphere const& bounds) const;
            
            /**
             * Tests to determine if the frustum contains the specified AABB.
             *
             * \param[in] bounds
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsAABB const& bounds) const;
            
            /**
             * Tests to determine if the frustum contains the specified OBB.
             *
             * \param[in] bounds
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsOBB const& bounds) const;

            //------------------------------------------------------------
            // Property Retrieval
            //------------------------------------------------------------

            /**
             * \return The distance from the point-of-view to the near clip plane. 
             *         Anything behind this point will be culled.
             */
            float getNearClipDistance() const;

            /**
             * \return The distance from the point-of-view to the far clip plane.
             *         Anything beyond this point will be culled.
             */
            float getFarClipDistance() const;

            /**
             * \return The left infinite plane that helps define this frustum.
             */
            Plane const& getLeftPlane() const;

            /**
             * \return The right infinite plane that helps define this frustum.
             */
            Plane const& getRightPlane() const;

            /**
             * \return The top infinite plane that helps define this frustum.
             */
            Plane const& getTopPlane() const;

            /**
             * \return The bottom infinite plane that helps define this frustum.
             */
            Plane const& getBottomPlane() const;

            /**
             * \return The near infinite plane that helps define this frustum.
             */
            Plane const& getNearPlane() const;

            /**
             * \return The far infinite plane that helps define this frustum.
             */
            Plane const& getFarPlane() const;

        protected:

            void createPlanes(float xMin, float xMax, float yMin, float yMax, float nearClip, float farClip);

        private:

            Vector3f m_PointOfView;
            Vector3f m_Direction;
            Vector3f m_Right;
            Vector3f m_Up;

            Plane m_LeftPlane;
            Plane m_RightPlane;
            Plane m_TopPlane;
            Plane m_BottomPlane;
            Plane m_NearPlane;
            Plane m_FarPlane;

            float m_NearClip;
            float m_FarClip;
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