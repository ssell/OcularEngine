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

#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Bounds/Ray.hpp"
#include "Math/Geometry/Plane.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BoundsAABB::BoundsAABB(std::list<Point3f> const& points, Math::Matrix4x4 const& matrix)
            : Bounds(BoundsType::AABB)
        {
            construct(points, matrix);
        }

        BoundsAABB::BoundsAABB(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix)
            : Bounds(BoundsType::AABB)
        {
            construct(vertices, matrix);
        }

        BoundsAABB::BoundsAABB(Vector3f const& center, Vector3f const& extents)
            : Bounds(BoundsType::AABB)
        {
            m_Center  = center;
            m_Extents = Vector3f(fmaxf(extents.x, 0.0f), fmaxf(extents.y, 0.0f), fmaxf(extents.z, 0.0f));

            calculateMinMaxPoints();
        }

        BoundsAABB::BoundsAABB()
            : Bounds(BoundsType::AABB)
        {
        
        }

        BoundsAABB::~BoundsAABB()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BoundsAABB::construct(std::list<Point3f> const& points, Math::Matrix4x4 const& matrix)
        {
            float minX = FLT_MAX;
            float minY = FLT_MAX;
            float minZ = FLT_MAX;

            float maxX = FLT_MIN;
            float maxY = FLT_MIN;
            float maxZ = FLT_MIN;

            if(matrix.isIdentity())
            {
                for(auto point : points)
                {
                    minX = fminf(minX, point.x);
                    minY = fminf(minY, point.y);
                    minZ = fminf(minZ, point.z);

                    maxX = fmaxf(maxX, point.x);
                    maxY = fmaxf(maxY, point.y);
                    maxZ = fmaxf(maxZ, point.z);
                }
            }
            else
            {
                for(auto point : points)
                {
                    const Math::Point3f transformed = matrix * point;

                    minX = fminf(minX, transformed.x);
                    minY = fminf(minY, transformed.y);
                    minZ = fminf(minZ, transformed.z);

                    maxX = fmaxf(maxX, transformed.x);
                    maxY = fmaxf(maxY, transformed.y);
                    maxZ = fmaxf(maxZ, transformed.z);
                }
            }

            m_MinPoint = Vector3f(minX, minY, minZ);
            m_MaxPoint = Vector3f(maxX, maxY, maxZ);
            m_Center   = Vector3f::Midpoint(m_MinPoint, m_MaxPoint);
            m_Extents  = m_MaxPoint - m_Center;
        }

        void BoundsAABB::construct(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix)
        {
            float minX = FLT_MAX;
            float minY = FLT_MAX;
            float minZ = FLT_MAX;

            float maxX = FLT_MIN;
            float maxY = FLT_MIN;
            float maxZ = FLT_MIN;

            if(matrix.isIdentity())
            {
                for(auto vertex : vertices)
                {
                    minX = fminf(minX, vertex.position.x);
                    minY = fminf(minY, vertex.position.y);
                    minZ = fminf(minZ, vertex.position.z);

                    maxX = fmaxf(maxX, vertex.position.x);
                    maxY = fmaxf(maxY, vertex.position.y);
                    maxZ = fmaxf(maxZ, vertex.position.z);
                }
            }
            else
            {
                for(auto vertex : vertices)
                {
                    const Math::Vector4f transformed = matrix * vertex.position;

                    minX = fminf(minX, transformed.x);
                    minY = fminf(minY, transformed.y);
                    minZ = fminf(minZ, transformed.z);

                    maxX = fmaxf(maxX, transformed.x);
                    maxY = fmaxf(maxY, transformed.y);
                    maxZ = fmaxf(maxZ, transformed.z);
                }
            }

            m_MinPoint = Vector3f(minX, minY, minZ);
            m_MaxPoint = Vector3f(maxX, maxY, maxZ);
            m_Center   = Vector3f::Midpoint(m_MinPoint, m_MaxPoint);
            m_Extents  = m_MaxPoint - m_Center;
        }

        void BoundsAABB::setCenter(Vector3f const& center)
        {
            m_Center = center;
            calculateMinMaxPoints();
        }

        void BoundsAABB::setExtents(Vector3f const& extents)
        {
            m_Extents = Vector3f(fmaxf(extents.x, 0.0f), fmaxf(extents.y, 0.0f), fmaxf(extents.z, 0.0f));
            calculateMinMaxPoints();
        }

        Vector3f const& BoundsAABB::getCenter() const
        {
            return m_Center;
        }

        Vector3f const& BoundsAABB::getExtents() const
        {
            return m_Extents;
        }

        Vector3f const& BoundsAABB::getMinPoint() const
        {
            return m_MinPoint;
        }

        Vector3f const& BoundsAABB::getMaxPoint() const
        {
            return m_MaxPoint;
        }

        void BoundsAABB::expand(Vector3f const& extents)
        {
            m_Extents += extents;

            m_Extents.x = fmaxf(m_Extents.x, 0.0f);
            m_Extents.y = fmaxf(m_Extents.y, 0.0f);
            m_Extents.z = fmaxf(m_Extents.z, 0.0f);

            calculateMinMaxPoints();
        }

        void BoundsAABB::expandToContain(Vector3f const& point)
        {
            if(!contains(point))
            {
                m_MinPoint = Vector3f(fminf(m_MinPoint.x, point.x),
                                      fminf(m_MinPoint.y, point.y),
                                      fminf(m_MinPoint.z, point.z));

                m_MaxPoint = Vector3f(fmaxf(m_MaxPoint.x, point.x),
                                      fmaxf(m_MaxPoint.y, point.y),
                                      fmaxf(m_MaxPoint.z, point.z));

                m_Center  = Vector3f::Midpoint(m_MinPoint, m_MaxPoint);
                m_Extents = m_MaxPoint - m_Center;
            }
        }

        void BoundsAABB::expandToContain(BoundsAABB const& bounds)
        {
            IntersectionType result;
            contains(bounds, &result);

            if(result != IntersectionType::Inside)
            {
                const Vector3f otherMin = bounds.getMinPoint();
                const Vector3f otherMax = bounds.getMaxPoint();

                m_MinPoint = Vector3f(fminf(m_MinPoint.x, otherMin.x),
                                      fminf(m_MinPoint.y, otherMin.y),
                                      fminf(m_MinPoint.z, otherMin.z));

                m_MaxPoint = Vector3f(fmaxf(m_MaxPoint.x, otherMax.x),
                                      fmaxf(m_MaxPoint.y, otherMax.y),
                                      fmaxf(m_MaxPoint.z, otherMax.z));

                m_Center  = Vector3f::Midpoint(m_MinPoint, m_MaxPoint);
                m_Extents = m_MaxPoint - m_Center;
            }
        }

        //------------------------------------------------------------------------------
        // Intersection and Containment Testing
        //------------------------------------------------------------------------------

        bool BoundsAABB::intersects(Ray const& ray) const
        {
            return ray.intersects((*this));
        }

        bool BoundsAABB::intersects(Ray const& ray, Point3f& point, float& distance) const
        {
            return ray.intersects((*this), point, distance);
        }

        bool BoundsAABB::intersects(BoundsSphere const& bounds) const
        {
            return bounds.intersects((*this));
        }

        bool BoundsAABB::intersects(BoundsAABB const& bounds) const
        {
            // Source: Real-Time Rendering, 3rd Ed. Page 765

            const Vector3f minB = bounds.getMinPoint();
            const Vector3f maxB = bounds.getMaxPoint();

            return !((m_MinPoint.x > maxB.x) || (minB.x > m_MaxPoint.x) ||
                     (m_MinPoint.y > maxB.y) || (minB.y > m_MaxPoint.y) ||
                     (m_MinPoint.z > maxB.z) || (minB.z > m_MaxPoint.z));
        }

        bool BoundsAABB::intersects(BoundsOBB const& bounds) const
        {
            return false;
        }

        bool BoundsAABB::intersects(Plane const& plane, IntersectionType* result) const
        {
            // Source: http://zach.in.tu-clausthal.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/

            const Math::Vector3f n = plane.getNormal();

            Math::Vector3f positive = m_MinPoint;
            Math::Vector3f negative = m_MaxPoint;

            if(n.x >= 0.0f)
            {
                positive.x = m_MaxPoint.x;
                negative.x = m_MinPoint.x;
            }

            if(n.y >= 0.0f)
            {
                positive.y = m_MaxPoint.y;
                negative.y = m_MinPoint.y;
            }

            if(n.z >= 0.0f)
            {
                positive.z = m_MaxPoint.z;
                negative.z = m_MinPoint.z;
            }

            bool intersects = false;

            if(plane.getSignedDistance(positive) > 0.0f)
            {
                *result = IntersectionType::Outside;
            }
            else if(plane.getSignedDistance(negative) > 0.0f)
            {
                *result = IntersectionType::Intersects;
                intersects = true;
            }
            else
            {
                *result = IntersectionType::Inside;
                intersects = true;
            }

            return intersects;
        }

        bool BoundsAABB::contains(Vector3f const& point, IntersectionType* result) const
        {
            IntersectionType tempResult;

            // If just any one of the components lies beyond the min/max points, then it is outside.
            if((point.x > m_MaxPoint.x) || (point.y > m_MaxPoint.y) || (point.z > m_MaxPoint.z) ||
               (point.x < m_MinPoint.x) || (point.y < m_MinPoint.y) || (point.z < m_MinPoint.z))
            {
                tempResult = IntersectionType::Outside;
            }
            else
            {
                tempResult = IntersectionType::Inside;

                if(IsEqual<float>(point.x, m_MaxPoint.x) || IsEqual<float>(point.y, m_MaxPoint.y) || IsEqual<float>(point.z, m_MaxPoint.z) ||
                    IsEqual<float>(point.x, m_MinPoint.x) || IsEqual<float>(point.y, m_MinPoint.y) || IsEqual<float>(point.z, m_MinPoint.z))
                {
                    tempResult = IntersectionType::Intersects;
                }
            }

            if(result)
            {
                (*result) = tempResult;
            }

            return (tempResult == IntersectionType::Outside) ? false : true;  // Avoid MSVC compiler warning from casting direct to bool
        }

        bool BoundsAABB::contains(BoundsAABB const& bounds, IntersectionType* result) const
        {
            IntersectionType tempResult;

            const Vector3f otherMin = bounds.getMinPoint();
            const Vector3f otherMax = bounds.getMaxPoint();

            if((otherMin > m_MaxPoint) || (otherMax < m_MinPoint))
            {
                tempResult = IntersectionType::Outside;
            }
            else
            {
                tempResult = IntersectionType::Inside;

                if((otherMax.x >= m_MaxPoint.x) || (otherMax.y >= m_MaxPoint.y) || (otherMax.z >= m_MaxPoint.z) ||
                    (otherMin.x <= m_MinPoint.x) || (otherMin.y <= m_MinPoint.y) || (otherMin.z <= m_MinPoint.z))
                {
                    tempResult = IntersectionType::Intersects;
                }
            }

            if(result)
            {
                (*result) = tempResult;
            }
            
            return (tempResult == IntersectionType::Outside) ? false : true;  // Avoid MSVC compiler warning from casting direct to bool
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void BoundsAABB::calculateMinMaxPoints()
        {
            m_MinPoint = m_Center - m_Extents;
            m_MaxPoint = m_Center + m_Extents;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}