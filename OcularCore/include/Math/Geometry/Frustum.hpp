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
             * Rebuilds the frustum using the current view and projection settings.
             */
            void rebuild();

            /**
             * Sets the view matrix that helps define this frustum.
             * \note Must call rebuild to update the frustum.
             */
            void setViewMatrix(Math::Matrix4x4 const& viewMatrix);

            /**
             * Sets the projection matrix that helps define this frustum.
             * \note Must call rebuild to update the frustum.
             */
            void setProjectionMatrix(Math::Matrix4x4 const& projMatrix);

            Math::Matrix4x4 getViewMatrix() const;

            Math::Matrix4x4 getProjectionMatrix() const;

            //------------------------------------------------------------
            // Misc Getters
            //------------------------------------------------------------

            /**
             * \return The point this frustum originates from.
             */
            Vector3f const& getOrigin() const;

            /**
             * Returns the four corners the comprise the finite portion of the near clip plane.
             * These corners are ordered counter-clockwise from the bottom left:
             *
             *     [0] : Bottom left
             *     [1] : Bottom right
             *     [2] : Top right
             *     [3] : Top left
             */
            std::array<Vector3f, 4> const& getNearClipCorners() const;

            /**
             * Returns the four corners the comprise the finite portion of the far clip plane.
             * These corners are ordered counter-clockwise from the bottom left:
             *
             *     [0] : Bottom left
             *     [1] : Bottom right
             *     [2] : Top right
             *     [3] : Top left
             */
            std::array<Vector3f, 4> const& getFarClipCorners() const;

            //------------------------------------------------------------
            // Containment Testing
            //------------------------------------------------------------

            /**
             * Tests to determine if the frustum contains the specified point.
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

            /**
             * \return The field-of-view. If an orthographic projection, returns 0
             */
            float getFieldOfView() const;

            /**
             * \return The aspect ratio. If an orthographic projection, returns 0
             */
            float getAspectRatio() const;

            /**
             * \return The minimum x value. Used only with orthographic projections.
             */
            float getXMin() const;
            
            /**
             * \return The maximum x value. Used only with orthographic projections.
             */
            float getXMax() const;
            
            /**
             * \return The minimum y value. Used only with orthographic projections.
             */
            float getYMin() const;
            
            /**
             * \return The maximum y value. Used only with orthographic projections.
             */
            float getYMax() const;

        protected:

        private:

            Math::Matrix4x4 m_ViewMatrix;
            Math::Matrix4x4 m_ProjMatrix;

            float m_MinX;
            float m_MaxX;
            float m_MinY;
            float m_MaxY;
            float m_NearClip;
            float m_FarClip;

            // Perspective-specific variables saved for user querying

            float m_FieldOfView;
            float m_AspectRatio;

            Vector3f m_Origin;

            std::array<Vector3f, 4> m_NearCorners;  ///< Corners of the finite near clip plane ordered counter-clockwise from bottom left
            std::array<Vector3f, 4> m_FarCorners;   ///< Corners of the finite far clip plane ordered counter-clockwise from bottom left

            Plane m_LeftPlane;
            Plane m_RightPlane;
            Plane m_TopPlane;
            Plane m_BottomPlane;
            Plane m_NearPlane;
            Plane m_FarPlane;
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