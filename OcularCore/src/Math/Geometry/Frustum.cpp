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
        {
        
        }

        Frustum::~Frustum()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // View and Projection matrix setting
        //----------------------------------------------------------------------------------

        void Frustum::setForward(Vector3f const& forwardVector)
        {
            m_Forward = forwardVector;
            m_Right = m_Forward.cross(m_Up);
        }

        void Frustum::setUp(Vector3f const& upVector)
        {
            m_Up = upVector.getNormalized();
            m_Right = m_Forward.cross(m_Up);
        }
        
        void Frustum::setView(Vector3f const& position, Vector3f const& forwardVector, Vector3f const& upVector)
        {
            m_Origin  = position;
            m_Forward = forwardVector;
            m_Up      = upVector;
            m_Right   = m_Forward.cross(m_Up);
        }

        void Frustum::setProjectionOrthographic(float const xMin, float const xMax, float const yMin, float const yMax, float const nearClip, float const farClip)
        {
            m_MinX = xMin;
            m_MaxX = xMax;
            m_MinY = yMin;
            m_MaxY = yMax;

            m_NearClip = nearClip;
            m_FarClip  = farClip;
        }

        void Frustum::setProjectionPerspective(float const fov, float const aspectRatio, float const nearClip, float const farClip)
        {
            // Source: http://www.songho.ca/opengl/gl_transform.html#projection

            const float tangent = tan(DegreesToRadians<float>(fov * 0.5f));
            const float height  = nearClip * tangent;
            const float width   = height * aspectRatio;

            m_MinX = -width;
            m_MaxX =  width;
            m_MinY = -height;
            m_MaxY =  height;

            m_NearClip = nearClip;
            m_FarClip  = farClip;
        }

        /*
        void Frustum::setViewProjection(Matrix4x4 const& viewProjection)
        {
            m_LeftPlane.setPoint(m_Origin);
            m_LeftPlane.setNormal(Vector3f(viewProjection[3][0] + viewProjection[0][0], viewProjection[3][1] + viewProjection[0][1], viewProjection[3][2] + viewProjection[0][2]));
            m_LeftPlane.normalize();

            m_RightPlane.setPoint(m_Origin);
            m_RightPlane.setNormal(Vector3f(viewProjection[3][0] - viewProjection[0][0], viewProjection[3][1] - viewProjection[0][1], viewProjection[3][2] - viewProjection[0][2]));
            m_RightPlane.normalize();

            m_BottomPlane.setPoint(m_Origin);
            m_BottomPlane.setNormal(Vector3f(viewProjection[3][0] + viewProjection[1][0], viewProjection[3][1] + viewProjection[1][1], viewProjection[3][2] + viewProjection[1][2]));
            m_BottomPlane.normalize();

            m_TopPlane.setPoint(m_Origin);
            m_TopPlane.setNormal(Vector3f(viewProjection[3][0] - viewProjection[1][0], viewProjection[3][1] - viewProjection[1][1], viewProjection[3][2] - viewProjection[1][2]));
            m_TopPlane.normalize();

            m_NearPlane.setPoint(m_Origin);
            m_NearPlane.setNormal(Vector3f(viewProjection[3][0] + viewProjection[2][0], viewProjection[3][1] + viewProjection[2][1], viewProjection[3][2] + viewProjection[2][2]));
            m_NearPlane.normalize();

            m_FarPlane.setPoint(m_Origin);
            m_FarPlane.setNormal(Vector3f(viewProjection[3][0] - viewProjection[2][0], viewProjection[3][1] - viewProjection[2][1], viewProjection[3][2] - viewProjection[2][2]));
            m_FarPlane.normalize();

            //------------------------------------------------------------------------------
            // Transform unit cube by inverse viewProj matrix to turn it into a frustum.

            const Matrix4x4 inverseMatrix = viewProjection.getInverse();
            
            m_NearCorners[0] = Vector3f(-1.0f, -1.0f, -1.0f);
            m_NearCorners[1] = Vector3f( 1.0f, -1.0f, -1.0f);
            m_NearCorners[2] = Vector3f( 1.0f,  1.0f, -1.0f);
            m_NearCorners[3] = Vector3f(-1.0f,  1.0f, -1.0f);
            
            m_FarCorners[0] = Vector3f(-1.0f, -1.0f, 1.0f);
            m_FarCorners[1] = Vector3f( 1.0f, -1.0f, 1.0f);
            m_FarCorners[2] = Vector3f( 1.0f,  1.0f, 1.0f);
            m_FarCorners[3] = Vector3f(-1.0f,  1.0f, 1.0f);

            for(int i = 0; i < 4; i++)
            {
                m_NearCorners[i] = inverseMatrix.transform(m_NearCorners[i]);
                m_FarCorners[i]  = inverseMatrix.transform(m_FarCorners[i]);
            }
        }
        */

        //----------------------------------------------------------------
        // Misc Getters
        //----------------------------------------------------------------

        Vector3f const& Frustum::getOrigin() const
        {
            return m_Origin;
        }

        Vector3f const& Frustum::getForward() const
        {
            return m_Forward;
        }

        Vector3f const& Frustum::getUp() const
        {
            return m_Up;
        }

        Vector3f const& Frustum::getRight() const
        {
            return m_Right;
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

            IntersectionType type;
            bool result = true;

            if(!m_NearPlane.intersects(bounds, &type))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_LeftPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_RightPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_BottomPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_TopPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_FarPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            return result;
        }

        bool Frustum::contains(BoundsAABB const& bounds) const
        {
            // If the bounds is outside of a single plane, then we return false.
            // Otherwise, if it is inside/intersects all planes then return true.

            IntersectionType type;
            bool result = true;

            if(!m_NearPlane.intersects(bounds, &type))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_LeftPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_RightPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_BottomPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_TopPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_FarPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            return result;
        }

        bool Frustum::contains(BoundsOBB const& bounds) const
        {
            // If the bounds is outside of a single plane, then we return false.
            // Otherwise, if it is inside/intersects all planes then return true.

            IntersectionType type;
            bool result = true;

            if(!m_NearPlane.intersects(bounds, &type))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_LeftPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_RightPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_BottomPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_TopPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            if((result) && (!m_FarPlane.intersects(bounds, &type)))
            {
                result = (type == IntersectionType::Inside);
            }

            return result;
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

        void Frustum::rebuild()
        {
            // Source: http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/

            /**
             * We can construct a plane from either a single point and normal, or from three points on the plane.
             * We use both of these methods when extracting all six planes from the frustum.
             *
             * For the near and far planes we calculate their centers and use the frustum's direction as the normal.
             *
             * The near clip center is found by projecting along the frustum direction from origin for a length equal to the nearClip distance.
             * It's normal is opposite of the frustum direction.
             *
             * The far clip center is found by projecting along the frustum direction from origin for a length equal to the farClip distance.
             * It's normal is the frustum direction.
             *
             * The remaining four planes (left, right, top, and bottom) will be constructed from three points that will define the planes.
             * For all four planes, we can use a combination of the following five points:
             *
             *     - Frustum origin
             *     - Near plane top-left corner point
             *     - Near plane top-right corner point
             *     - Near plane bottom-left corner point
             *     - Near plane bottom-right corner point
             *
             * Conveniently, the frustum origin lies on all four of the planes. The rest of the planes are composed as follows:
             *
             *     Left:   (origin, near bottom left, near top left)
             *     Right:  (origin, near bottom right, near top right)
             *     Top:    (origin, near top right, near top left)
             *     Bottom: (origin, near bottom right, near top left)
             */

            //------------------------------------------------------------
            // Find the individual points for the planes

            const float nearHalfWidth  = (m_MaxX - m_MinX) * 0.5f;
            const float nearHalfHeight = (m_MaxY - m_MinY) * 0.5f;

            const Vector3f nearCenter = m_Origin + (m_Forward * m_NearClip);
            const Vector3f farCenter  = m_Origin + (m_Forward * m_FarClip);
            
            const Vector3f nearTopDiff   = (m_Up * nearHalfHeight);
            const Vector3f nearRightDiff = (m_Right * nearHalfWidth);
            
            //------------------------------------------------------------
            // Find the near corner points

            m_NearCorners[0] = (nearCenter - nearTopDiff) - nearRightDiff;
            m_NearCorners[1] = (nearCenter - nearTopDiff) + nearRightDiff;
            m_NearCorners[2] = (nearCenter + nearTopDiff) + nearRightDiff;
            m_NearCorners[3] = (nearCenter + nearTopDiff) - nearRightDiff;

            //------------------------------------------------------------
            // Construct the planes from the discovered points

            m_NearPlane   = Plane(m_Origin + (m_Forward * m_NearClip), -m_Forward);
            m_FarPlane    = Plane(m_Origin + (m_Forward * m_FarClip),   m_Forward);
            
            m_LeftPlane   = Plane(m_Origin, m_NearCorners[3], m_NearCorners[0]);
            m_RightPlane  = Plane(m_Origin, m_NearCorners[1], m_NearCorners[2]);
            m_TopPlane    = Plane(m_Origin, m_NearCorners[2], m_NearCorners[3]);
            m_BottomPlane = Plane(m_Origin, m_NearCorners[0], m_NearCorners[1]);

            //------------------------------------------------------------
            // Find the far corner points

            m_FarCorners[0] = Plane::GetIntersectionPoint(m_FarPlane, m_LeftPlane,  m_BottomPlane);
            m_FarCorners[1] = Plane::GetIntersectionPoint(m_FarPlane, m_RightPlane, m_BottomPlane);
            m_FarCorners[2] = Plane::GetIntersectionPoint(m_FarPlane, m_RightPlane, m_TopPlane);
            m_FarCorners[3] = Plane::GetIntersectionPoint(m_FarPlane, m_LeftPlane,  m_TopPlane);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}