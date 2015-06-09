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

#include "Math/Geometry/Polygon2D.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Polygon2D::Polygon2D(std::vector<Point2f> const& points)
        {
            m_CenterCalculated = false;
            m_SignedAreaCalculated = false;

            m_Points.assign(points.begin(), points.end());
        }

        Polygon2D::Polygon2D(Point2f const* points, uint32_t numPoints)
        {
            m_CenterCalculated = false;
            m_SignedAreaCalculated = false;

            m_Points.reserve(numPoints);

            if(points)
            {
                for(uint32_t i = 0; i < numPoints; i++)
                {
                    m_Points[i] = points[i];
                }
            }
        }

        Polygon2D::~Polygon2D()
        {
            m_Points.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        /**
         * Calculates the center (centroid) of the polygon.
         */
        Point2f Polygon2D::getCenter()
        {
            // Source: http://en.wikipedia.org/wiki/Centroid#Centroid_of_polygon

            if(!m_CenterCalculated)
            {
                const uint32_t size = m_Points.size();

                float xPos = 0.0f;
                float yPos = 0.0f;
                float partialArea = 0.0f;

                uint32_t j = 0;
                float k = 0.0f;

                for(uint32_t i = 0; i < size; i++)
                {
                    j = (i + 1) % size;
                    k = ((m_Points[i].x * m_Points[j].y) - (m_Points[j].x * m_Points[i].y));

                    partialArea += k;

                    xPos += (m_Points[i].x + m_Points[j].x) * k;
                    yPos += (m_Points[i].y + m_Points[j].y) * k;
                }

                m_SignedArea = (partialArea * 0.5f);

                xPos *= (1.0f / (6.0f * m_SignedArea));
                yPos *= (1.0f / (6.0f * m_SignedArea));

                m_Center = Vector2f(xPos, yPos);

                m_SignedAreaCalculated = true;
                m_CenterCalculated = true;
            }

            return m_Center;
        }

        /**
         * Calculates and returns the signed area of the polygon.
         */
        float Polygon2D::getSignedArea()
        {
            if(!m_SignedAreaCalculated)
            {
                const uint32_t size = m_Points.size();
                float partialArea = 0.0f;

                for(uint32_t i = 0; i < size; i++)
                {
                    partialArea += (m_Points[i].x * m_Points[(i + 1) % size].y) - (m_Points[(i + 1) % size].x * m_Points[i].y);
                }

                m_SignedArea = (partialArea * 0.5f);
                m_SignedAreaCalculated = true;
            }

            return m_SignedArea;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}