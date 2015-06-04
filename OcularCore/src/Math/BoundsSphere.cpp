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

#include "Math/BoundsSphere.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BoundsSphere::BoundsSphere(std::list<Point3f> const& points)
        {
            construct(points);
        }

        BoundsSphere::BoundsSphere(Vector3f const& center, float const radius)
        {
            m_Center = center;
            m_Radius = radius;
        }

        BoundsSphere::BoundsSphere()
        {
        
        }

        BoundsSphere::~BoundsSphere()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BoundsSphere::construct(std::list<Point3f> const& points)
        {
            // Source: Graphics Gems, Page 301

            //------------------------------------------------------------
            // 1. Find the points in the collection that are the greatest
            //    extents of each axis.

            Vector3f xMin, yMin, zMin;
            Vector3f xMax, yMax, zMax;

            xMin.x = yMin.y = zMin.z = FLT_MAX;
            xMax.x = yMax.y = zMax.z = FLT_MIN;

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

        void BoundsSphere::setCenter(Vector3f const& center)
        {
            m_Center = center;
        }

        void BoundsSphere::setRadius(float const radius)
        {
            m_Radius = Max<float>(radius, 0.0f);
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
            m_Radius = Max(m_Radius + amount, 0.0f);
        }

        void BoundsSphere::expandToContain(Point3f const& point)
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

        bool BoundsSphere::contains(Point3f const& point, IntersectionType* result) const
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