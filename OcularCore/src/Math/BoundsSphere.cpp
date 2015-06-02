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
            m_Radius = radius;
        }

        Vector3f const& BoundsSphere::getCenter() const
        {
            return m_Center;
        }

        float BoundsSphere::getRadius() const
        {
            return m_Radius;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}