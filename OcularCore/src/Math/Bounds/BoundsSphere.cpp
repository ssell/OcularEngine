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

#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
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

        BoundsSphere::BoundsSphere(std::list<Vector3f> const& points, Math::Matrix4x4 const& matrix)
            : Bounds(BoundsType::AABB)
        {
            construct(points, matrix);
        }

        BoundsSphere::BoundsSphere(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix)
            : Bounds(BoundsType::AABB)
        {
            construct(vertices, matrix);
        }

        BoundsSphere::BoundsSphere(Vector3f const& center, float const radius)
            : Bounds(BoundsType::AABB)
        {
            m_Center = center;
            m_Radius = radius;
        }

        BoundsSphere::BoundsSphere()
            : Bounds(BoundsType::AABB)
        {
            m_Radius = 0.0f;
        }

        BoundsSphere::~BoundsSphere()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BoundsSphere::construct(std::list<Vector3f> const& points, Math::Matrix4x4 const& matrix)
        {
            // Source: Graphics Gems, Page 301

            //------------------------------------------------------------
            // 1. Find the points in the collection that are the greatest
            //    extents of each axis.

            Vector3f xMin, yMin, zMin;
            Vector3f xMax, yMax, zMax;

            xMin.x = yMin.y = zMin.z = FLT_MAX;
            xMax.x = yMax.y = zMax.z = FLT_MIN;

            if(matrix.isIdentity())
            {
                for(auto point : points)
                {
                    if(point.x < xMin.x)
                    {
                        xMin = point;
                    }

                    if(point.y < yMin.y)
                    {
                        yMin = point;
                    }

                    if(point.z < zMin.z)
                    {
                        zMin = point;
                    }

                    if(point.x > xMax.x)
                    {
                        xMax = point;
                    }

                    if(point.y > yMax.y)
                    {
                        yMax = point;
                    }

                    if(point.y > zMax.z)
                    {
                        zMax = point;
                    }
                }
            }
            else
            {
                for(auto point : points)
                {
                    const Math::Point3f transformed = matrix * point;

                    if(point.x < xMin.x)
                    {
                        xMin = transformed;
                    }

                    if(point.y < yMin.y)
                    {
                        yMin = transformed;
                    }

                    if(point.z < zMin.z)
                    {
                        zMin = transformed;
                    }

                    if(point.x > xMax.x)
                    {
                        xMax = transformed;
                    }

                    if(point.y > yMax.y)
                    {
                        yMax = transformed;
                    }

                    if(point.y > zMax.z)
                    {
                        zMax = transformed;
                    }
                }
            }

            //------------------------------------------------------------
            // 2. Calculate the distance (squared) of each pair of maximal extents.

            const Vector3f xSpan = xMax - xMin;
            const Vector3f ySpan = yMax - yMin;
            const Vector3f zSpan = zMax - zMin;

            const float xDistanceSquared = xSpan.dot(xSpan);
            const float yDistanceSquared = ySpan.dot(ySpan);
            const float zDistanceSquared = zSpan.dot(zSpan);

            //------------------------------------------------------------
            // 3. Determine which pair of min/max points have the greatest
            //    distance between them.

            Vector3f endpointMin = xMin;
            Vector3f endpointMax = xMax;

            if((yDistanceSquared >= xDistanceSquared) && (yDistanceSquared >= zDistanceSquared))
            {
                endpointMin = yMin;
                endpointMax = yMax;
            }
            else if((zDistanceSquared >= xDistanceSquared) && (zDistanceSquared >= yDistanceSquared))
            {
                endpointMin = zMin;
                endpointMax = zMax;
            }

            //------------------------------------------------------------
            // 4. Calculate initial center and radius

            m_Center = Vector3f::Midpoint(endpointMin, endpointMax);
            
            Vector3f radiusVector = endpointMax - m_Center;

            m_Radius = radiusVector.getLength();

            //------------------------------------------------------------
            // 5. Adjust the center and radius to ensure that all points are contained.
            
            Vector3f pointToCenter;
            float radiiSquared = m_Radius * m_Radius;
            float pointToCenterDistanceSquared = 0.0f;

            for(auto point : points)
            {
                // Ensure point is within the sphere    
                pointToCenter = point - m_Center;
                pointToCenterDistanceSquared = pointToCenter.dot(pointToCenter);

                if(pointToCenterDistanceSquared > radiiSquared)
                {
                    // This point sits outside of the sphere
                    // Calculate new radius and center

                    float oldCenterToPointDistance = sqrtf(pointToCenterDistanceSquared);
                    m_Radius = (m_Radius + oldCenterToPointDistance) * 0.5f;
                    float newCenterToPointDistance = oldCenterToPointDistance - m_Radius;

                    // Everything makes sense to me up to this point. Need to investigate/test to assure myself.
                    m_Center = ((m_Center * m_Radius) + (point * newCenterToPointDistance)) / oldCenterToPointDistance;
                }
            }
        }

        void BoundsSphere::construct(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix)
        {
            // Source: Graphics Gems, Page 301

            //------------------------------------------------------------
            // 1. Find the points in the collection that are the greatest
            //    extents of each axis.

            Vector3f xMin, yMin, zMin;
            Vector3f xMax, yMax, zMax;

            xMin.x = yMin.y = zMin.z = FLT_MAX;
            xMax.x = yMax.y = zMax.z = FLT_MIN;

            if(matrix.isIdentity())
            {
                for(auto vertex : vertices)
                {
                    const Math::Vector3f position = vertex.position.xyz();

                    if(vertex.position.x < xMin.x)
                    {
                        xMin = position;
                    }

                    if(vertex.position.y < yMin.y)
                    {
                        yMin = position;
                    }

                    if(vertex.position.z < zMin.z)
                    {
                        zMin = position;
                    }

                    if(vertex.position.x > xMax.x)
                    {
                        xMax = position;
                    }

                    if(vertex.position.y > yMax.y)
                    {
                        yMax = position;
                    }

                    if(vertex.position.y > zMax.z)
                    {
                        zMax = position;
                    }
                }
            }
            else
            {
                for(auto vertex : vertices)
                {
                    const Math::Vector3f transformed = matrix * vertex.position.xyz();

                    if(vertex.position.x < xMin.x)
                    {
                        xMin = transformed;
                    }

                    if(vertex.position.y < yMin.y)
                    {
                        yMin = transformed;
                    }

                    if(vertex.position.z < zMin.z)
                    {
                        zMin = transformed;
                    }

                    if(vertex.position.x > xMax.x)
                    {
                        xMax = transformed;
                    }

                    if(vertex.position.y > yMax.y)
                    {
                        yMax = transformed;
                    }

                    if(vertex.position.y > zMax.z)
                    {
                        zMax = transformed;
                    }
                }
            }

            //------------------------------------------------------------
            // 2. Calculate the distance (squared) of each pair of maximal extents.

            const Vector3f xSpan = xMax - xMin;
            const Vector3f ySpan = yMax - yMin;
            const Vector3f zSpan = zMax - zMin;

            const float xDistanceSquared = xSpan.dot(xSpan);
            const float yDistanceSquared = ySpan.dot(ySpan);
            const float zDistanceSquared = zSpan.dot(zSpan);

            //------------------------------------------------------------
            // 3. Determine which pair of min/max points have the greatest
            //    distance between them.

            Vector3f endpointMin = xMin;
            Vector3f endpointMax = xMax;

            if((yDistanceSquared >= xDistanceSquared) && (yDistanceSquared >= zDistanceSquared))
            {
                endpointMin = yMin;
                endpointMax = yMax;
            }
            else if((zDistanceSquared >= xDistanceSquared) && (zDistanceSquared >= yDistanceSquared))
            {
                endpointMin = zMin;
                endpointMax = zMax;
            }

            //------------------------------------------------------------
            // 4. Calculate initial center and radius

            m_Center = Vector3f::Midpoint(endpointMin, endpointMax);
            
            Vector3f radiusVector = endpointMax - m_Center;

            m_Radius = radiusVector.getLength();

            //------------------------------------------------------------
            // 5. Adjust the center and radius to ensure that all points are contained.
            
            Vector3f pointToCenter;
            float radiiSquared = m_Radius * m_Radius;
            float pointToCenterDistanceSquared = 0.0f;

            for(auto vertex : vertices)
            {
                // Ensure point is within the sphere    
                pointToCenter = vertex.position.xyz() - m_Center;
                pointToCenterDistanceSquared = pointToCenter.dot(pointToCenter);

                if(pointToCenterDistanceSquared > radiiSquared)
                {
                    // This point sits outside of the sphere
                    // Calculate new radius and center

                    float oldCenterToPointDistance = sqrtf(pointToCenterDistanceSquared);
                    m_Radius = (m_Radius + oldCenterToPointDistance) * 0.5f;
                    float newCenterToPointDistance = oldCenterToPointDistance - m_Radius;

                    // Everything makes sense to me up to this point. Need to investigate/test to assure myself.
                    m_Center = ((m_Center * m_Radius) + (vertex.position.xyz() * newCenterToPointDistance)) / oldCenterToPointDistance;
                }
            }
        }

        void BoundsSphere::setCenter(Vector3f const& center)
        {
            m_Center = center;
        }

        void BoundsSphere::setRadius(float const radius)
        {
            m_Radius = fmaxf(radius, 0.0f);
        }

        Vector3f const& BoundsSphere::getCenter() const
        {
            return m_Center;
        }

        float BoundsSphere::getRadius() const
        {
            return m_Radius;
        }
        
        void BoundsSphere::expand(float const amount)
        {
            m_Radius = fmaxf(m_Radius + amount, 0.0f);
        }

        void BoundsSphere::expandToContain(Vector3f const& point)
        {
            /* 
            This is identical to the second pass of the algorithm employed in the construct method.

                - Determine if point is in sphere. If not,

                - Find the difference between the distance of the point to the center
                  and the radius of the sphere.

                - This difference is the distance of how far we must expand the sphere
                  in order to encapsulate the point.

                - Increase the radius by half of the difference. The sphere is now half-way
                  to being able to encapsulate the point.

                - Shift the center the final half of the distance towards the point. The
                  point should now be fully enclosed by the sphere.
            */

            if(!contains(point))
            {
                const Vector3f pointToOldCenter = point - m_Center;
                const float pointToOldCenterDistance = pointToOldCenter.getLength();

                m_Radius = (m_Radius + pointToOldCenterDistance) * 0.5f;

                const float distanceDifference = pointToOldCenterDistance - m_Radius;

                m_Center = ((m_Center * m_Radius) + (point * distanceDifference)) / pointToOldCenterDistance;
            }
        }

        void BoundsSphere::expandToContain(BoundsSphere const& other)
        {
            // We calculate the furthest point in the second sphere from this sphere,
            // and then we expand to contain that point.

            const Math::Vector3f otherCenter = other.getCenter();
            const Math::Vector3f toOther     = (otherCenter - m_Center).getNormalized();
            const Math::Vector3f furthest    = otherCenter + (toOther * other.getRadius());

            expandToContain(furthest);
        }

        //------------------------------------------------------------------------------
        // Intersection and Containment Testing
        //------------------------------------------------------------------------------

        bool BoundsSphere::intersects(Ray const& ray) const
        {
            return ray.intersects((*this));
        }

        bool BoundsSphere::intersects(Ray const& ray, Vector3f& point, float& distance) const
        {
            return ray.intersects((*this), Vector3f(point.x, point.y, point.z), distance);
        }

        bool BoundsSphere::intersects(BoundsSphere const& bounds) const
        {
            // Source: Real-Time Rendering, 3rd Ed. Page 763

            const Vector3f distance = m_Center - bounds.getCenter();

            const float radiiSum = m_Radius + bounds.getRadius();
            const float distanceSquared = distance.dot(distance);
            const float radiiSumSquared = radiiSum * radiiSum;

            return !(distanceSquared > radiiSumSquared);
        }

        bool BoundsSphere::intersects(BoundsAABB const& bounds) const
        {
            // Source: Real-Time Rendering, 3rd Ed. Page 764

            const Vector3f aabbMin = bounds.getMinPoint();
            const Vector3f aabbMax = bounds.getMaxPoint();

            const Vector3f a(fmaxf((aabbMin.x - m_Center.x), 0.0f),
                             fmaxf((aabbMin.y - m_Center.y), 0.0f),
                             fmaxf((aabbMin.z - m_Center.z), 0.0f));

            const Vector3f b(fmaxf((m_Center.x - aabbMax.x), 0.0f),
                             fmaxf((m_Center.y - aabbMax.y), 0.0f),
                             fmaxf((m_Center.z - aabbMax.z), 0.0f));

            const Vector3f c = a + b;

            float distance = c.dot(c);
                       
            return !(distance > (m_Radius * m_Radius));
        }

        bool BoundsSphere::intersects(BoundsOBB const& bounds) const
        {
            return false;
        }

        bool BoundsSphere::intersects(Plane const& plane, IntersectionType* result) const
        {
            IntersectionType tempResult = IntersectionType::Inside;
            bool intersects = false;

            Vector3f center3 = Vector3f(m_Center.x, m_Center.y, m_Center.z);

            const float distance = plane.getSignedDistance(center3);
            const float absDistance = fabsf(distance);

            if(distance < 0.0f)
            {
                // Bounds center is inside the plane.
                // Test if it is fully inside or if it intersects.

                if(absDistance > m_Radius)
                {
                    // Radius does not extend to the plane edge
                    tempResult = IntersectionType::Inside;
                }
                else
                {
                    // The radius intersects the plane
                    tempResult = IntersectionType::Intersects;
                }

                intersects = true;
            }
            else
            {
                // Bounds center is outside the plane. 
                // Test if it is fully outside or if it intersects.

                if(absDistance > m_Radius)
                {
                    // Radius does not extend to the plane edge
                    tempResult = IntersectionType::Outside;
                }
                else
                {
                    // The radius intersects the plane
                    tempResult = IntersectionType::Intersects;
                    intersects = true;
                }
            }
            
            if(result)
            {
                (*result) = tempResult;
            }
            
            return intersects;
        }

        bool BoundsSphere::contains(Vector3f const& point, IntersectionType* result) const
        {
            IntersectionType tempResult = IntersectionType::Outside;

            const Vector3f pointToCenter = point - m_Center;

            const float distanceSquared = pointToCenter.dot(pointToCenter);
            const float radiiSquared = m_Radius * m_Radius;

            if(IsEqual<float>(radiiSquared, distanceSquared))
            {
                tempResult = IntersectionType::Intersects;
            }
            else if(distanceSquared < radiiSquared)
            {
                tempResult = IntersectionType::Inside;
            }

            if(result)
            {
                (*result) = tempResult;
            }

            return (tempResult == IntersectionType::Outside) ? false : true;
        }

        bool BoundsSphere::contains(BoundsSphere const& sphere, IntersectionType* result) const
        {
            IntersectionType tempResult = IntersectionType::Inside;

            const Vector3f sphereToSphere = sphere.getCenter() - m_Center;

            const float sphereRadius = sphere.getRadius();
            const float sphereDistance = sphereToSphere.getLength();

            if(sphereRadius > m_Radius)
            {
                // Can't possibly be entirely inside, so either intersects or outside
                if(sphereDistance > sphereRadius)
                {
                    tempResult = IntersectionType::Outside;
                }
                else
                {
                    tempResult = IntersectionType::Intersects;
                }
            }
            else
            {
                // Possibility of being inside, outside, or intersecting
                if(sphereDistance > (sphereRadius + m_Radius))
                {
                    tempResult = IntersectionType::Outside;
                }
                else if(sphereDistance >= (m_Radius - sphereRadius))
                {
                    tempResult = IntersectionType::Intersects;
                }
            }

            if(result)
            {
                (*result) = tempResult;
            }

            return ((*result) == IntersectionType::Outside) ? false : true;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}