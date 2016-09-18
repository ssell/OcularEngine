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

#include "Math/Geometry/Frustum.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Bounds/BoundsSphere.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
                
        Frustum::Frustum()
            : m_FieldOfView(0.0f),
              m_AspectRatio(0.0f),
              m_MinX(0.0f),
              m_MaxX(0.0f),
              m_MinY(0.0f),
              m_MaxY(0.0f)
        {
        
        }

        Frustum::~Frustum()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Frustum::rebuild()
        {
            // Rebuilds the clipping planes as well as the near and far corners.

            const Math::Matrix4x4 viewProjMatrix = m_ProjMatrix * m_ViewMatrix;
            const Math::Matrix4x4 invViewProjMatrix = viewProjMatrix.getInverse();

            //------------------------------------------------------------
            // Set corners in NDC-space

            Math::Vector4f nearLowerLeft  = Math::Vector4f(-1.0f, -1.0f, 0.0f, 1.0f);
            Math::Vector4f nearLowerRight = Math::Vector4f( 1.0f, -1.0f, 0.0f, 1.0f);
            Math::Vector4f nearUpperRight = Math::Vector4f( 1.0f,  1.0f, 0.0f, 1.0f);
            Math::Vector4f nearUpperLeft  = Math::Vector4f(-1.0f,  1.0f, 0.0f, 1.0f);

            Math::Vector4f farLowerLeft   = Math::Vector4f(-1.0f, -1.0f, 1.0f, 1.0f);
            Math::Vector4f farLowerRight  = Math::Vector4f( 1.0f, -1.0f, 1.0f, 1.0f);
            Math::Vector4f farUpperRight  = Math::Vector4f( 1.0f,  1.0f, 1.0f, 1.0f);
            Math::Vector4f farUpperLeft   = Math::Vector4f(-1.0f,  1.0f, 1.0f, 1.0f);
            
            //------------------------------------------------------------
            // Mutiply by inverse view-projection matrix

            nearLowerLeft  = invViewProjMatrix * nearLowerLeft;
            nearLowerRight = invViewProjMatrix * nearLowerRight;
            nearUpperRight = invViewProjMatrix * nearUpperRight;
            nearUpperLeft  = invViewProjMatrix * nearUpperLeft;

            farLowerLeft   = invViewProjMatrix * farLowerLeft;
            farLowerRight  = invViewProjMatrix * farLowerRight;
            farUpperRight  = invViewProjMatrix * farUpperRight;
            farUpperLeft   = invViewProjMatrix * farUpperLeft;
            
            //------------------------------------------------------------
            // Divide by w term

            nearLowerLeft  /= nearLowerLeft.w;
            nearLowerRight /= nearLowerRight.w;
            nearUpperRight /= nearUpperRight.w;
            nearUpperLeft  /= nearUpperLeft.w;
            
            farLowerLeft   /= farLowerLeft.w;
            farLowerRight  /= farLowerRight.w;
            farUpperRight  /= farUpperRight.w;
            farUpperLeft   /= farUpperLeft.w;

            //------------------------------------------------------------
            // Set world-space corners

            m_NearCorners[0] = nearLowerLeft.xyz();
            m_NearCorners[1] = nearLowerRight.xyz();
            m_NearCorners[2] = nearUpperRight.xyz();
            m_NearCorners[3] = nearUpperLeft.xyz();

            m_FarCorners[0]  = farLowerLeft.xyz();
            m_FarCorners[1]  = farLowerRight.xyz();
            m_FarCorners[2]  = farUpperRight.xyz();
            m_FarCorners[3]  = farUpperLeft.xyz();

            //------------------------------------------------------------
            // Build bounding planes

            m_LeftPlane   = Plane(m_NearCorners[0], m_NearCorners[3], m_FarCorners[3]);
            m_TopPlane    = Plane(m_NearCorners[3], m_NearCorners[2], m_FarCorners[2]);
            m_RightPlane  = Plane(m_NearCorners[1], m_FarCorners[1],  m_FarCorners[2]);
            m_BottomPlane = Plane(m_NearCorners[0], m_FarCorners[0],  m_FarCorners[1]);
            m_NearPlane   = Plane(m_NearCorners[0], m_NearCorners[1], m_NearCorners[2]);
            m_FarPlane    = Plane(m_FarCorners[0],  m_FarCorners[3],  m_FarCorners[2]);
        }

        //----------------------------------------------------------------------------------
        // View and Projection matrix setting
        //----------------------------------------------------------------------------------

        void Frustum::setViewMatrix(Math::Matrix4x4 const& viewMatrix)
        {
            m_ViewMatrix = viewMatrix;
            m_Origin = m_ViewMatrix.getCol(3).xyz();
        }

        void Frustum::setProjectionMatrix(Math::Matrix4x4 const& projMatrix)
        {
            m_ProjMatrix = projMatrix;
        }

        Math::Matrix4x4 Frustum::getViewMatrix() const
        {
            return m_ViewMatrix;
        }

        Math::Matrix4x4 Frustum::getProjectionMatrix() const
        {
            return m_ProjMatrix;
        }

        //----------------------------------------------------------------
        // Misc Getters
        //----------------------------------------------------------------

        Vector3f const& Frustum::getOrigin() const
        {
            return m_Origin;
        }

        std::array<Vector3f, 4> const& Frustum::getNearClipCorners() const
        {
            return m_NearCorners;
        }

        std::array<Vector3f, 4> const& Frustum::getFarClipCorners() const
        {
            return m_FarCorners;
        }

        //----------------------------------------------------------------
        // Containment Testing
        //----------------------------------------------------------------

        bool Frustum::contains(Point3f const& point) const
        {
            // If the point is outside of a single plane, then we return false.
            // Otherwise, if it is inside/intersects all planes then return true.

            // If distance is 0 then there is an intersection.
            // If distance is negative it is inside the plane.

            return (m_NearPlane.getSignedDistance(point)   < EPSILON_FLOAT) &&
                   (m_LeftPlane.getSignedDistance(point)   < EPSILON_FLOAT) &&
                   (m_RightPlane.getSignedDistance(point)  < EPSILON_FLOAT) &&
                   (m_BottomPlane.getSignedDistance(point) < EPSILON_FLOAT) &&
                   (m_TopPlane.getSignedDistance(point)    < EPSILON_FLOAT) &&
                   (m_FarPlane.getSignedDistance(point)    < EPSILON_FLOAT);
        }

        bool Frustum::contains(BoundsSphere const& bounds) const
        {
            // If the bounds is outside of a single plane, then we return false.
            // Otherwise, if it is inside/intersects all planes then return true.

            // Plane::intersects returns TRUE if intersects or inside.
            // We make no distinction between the two and only care that
            // it is not entirely outside of the frustum.

            return (m_NearPlane.intersects(bounds) &&
                    m_FarPlane.intersects(bounds) &&
                    m_LeftPlane.intersects(bounds) &&
                    m_RightPlane.intersects(bounds) &&
                    m_TopPlane.intersects(bounds) &&
                    m_BottomPlane.intersects(bounds));
        }

        bool Frustum::contains(BoundsAABB const& bounds) const
        {
            // If the bounds is outside of a single plane, then we return false.
            // Otherwise, if it is inside/intersects all planes then return true.

            // Plane::intersects returns TRUE if intersects or inside.
            // We make no distinction between the two and only care that
            // it is not entirely outside of the frustum.

            return (m_NearPlane.intersects(bounds) &&
                    m_FarPlane.intersects(bounds) &&
                    m_LeftPlane.intersects(bounds) &&
                    m_RightPlane.intersects(bounds) &&
                    m_TopPlane.intersects(bounds) &&
                    m_BottomPlane.intersects(bounds));
        }

        bool Frustum::contains(BoundsOBB const& bounds) const
        {
            // If the bounds is outside of a single plane, then we return false.
            // Otherwise, if it is inside/intersects all planes then return true.

            // Plane::intersects returns TRUE if intersects or inside.
            // We make no distinction between the two and only care that
            // it is not entirely outside of the frustum.

            return (m_NearPlane.intersects(bounds) &&
                    m_FarPlane.intersects(bounds) &&
                    m_LeftPlane.intersects(bounds) &&
                    m_RightPlane.intersects(bounds) &&
                    m_TopPlane.intersects(bounds) &&
                    m_BottomPlane.intersects(bounds));
        }

        //----------------------------------------------------------------
        // Property Retrieval
        //----------------------------------------------------------------

        float Frustum::getNearClipDistance() const
        {
            return m_NearClip;
        }

        float Frustum::getFarClipDistance() const
        {
            return m_FarClip;
        }

        Plane const& Frustum::getLeftPlane() const
        {
            return m_LeftPlane;
        }

        Plane const& Frustum::getRightPlane() const
        {
            return m_RightPlane;
        }

        Plane const& Frustum::getTopPlane() const
        {
            return m_TopPlane;
        }

        Plane const& Frustum::getBottomPlane() const
        {
            return m_BottomPlane;
        }

        Plane const& Frustum::getNearPlane() const
        {
            return m_NearPlane;
        }

        Plane const& Frustum::getFarPlane() const
        {
            return m_FarPlane;
        }

        float Frustum::getFieldOfView() const
        {
            return m_FieldOfView;
        }

        float Frustum::getAspectRatio() const
        {
            return m_AspectRatio;
        }

        float Frustum::getXMin() const
        {
            return m_MinX;
        }

        float Frustum::getXMax() const
        {
            return m_MaxX;
        }

        float Frustum::getYMin() const
        {
            return m_MinY;
        }

        float Frustum::getYMax() const
        {
            return m_MaxY;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}