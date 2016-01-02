/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_MATH_POLYGON_2D__H__
#define __H__OCULAR_MATH_POLYGON_2D__H__

#include "Math/Vector2.hpp"
#include <vector>

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
        /**
         * \class Polygon2D
         *
         * Helper class that can perform common actions on a polygon.
         *
         * The points are expected to be ordered as the occur along the 
         * polygon's perimeter and form a regular polygon.
         */
        class Polygon2D
        {
        public:

            Polygon2D(std::vector<Point2f> const& points);
            Polygon2D(Point2f const*, uint32_t numPoints);
            ~Polygon2D();

            /**
             * Calculates the center (centroid) of the polygon.
             */
            Point2f getCenter();

            /**
             * Calculates and returns the signed area of the polygon.
             *
             * \note If the points are ordered in a clockwise manner, then
             *       the area will have a negative sign.
             */
            float getSignedArea();

        protected:

        private:

            std::vector<Point2f> m_Points;

            Point2f m_Center;
            bool m_CenterCalculated;

            float m_SignedArea;
            bool m_SignedAreaCalculated;
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