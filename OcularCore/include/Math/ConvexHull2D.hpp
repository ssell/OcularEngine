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
#ifndef __H__OCULAR_MATH_CONVEX_HULL_2D__H__
#define __H__OCULAR_MATH_CONVEX_HULL_2D__H__

#include "Vector2.hpp"
#include "LineSegment2D.hpp"
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
         * \class ConvexHull2D
         *
         * A convex hull is the minimum set of points that envelope an
         * arbitrary collection of points.
         *
         * By default, the points comprising the hull are stored as they
         * are discovered and no type of order is guaranteed.
         *
         * The sort method may be called to order them in a counterclockwise fashion.
         */
        class ConvexHull2D
        {
        public:

            /**
             * \param[in] points Arbitrary collection of points to calculate a convex hull for.
             */
            ConvexHull2D(std::vector<Point2f> const& points);
            
            /**
             * \param[in] points    Arbitrary array of points to calculate a convex hull for.
             * \param[in] numPoints Number of points in the array.
             */
            ConvexHull2D(Point2f const*, uint32_t numPoints);

            ~ConvexHull2D();

            /**
             * Sorts the points comprising the convex hull into an ordered counterclockwise polygon.
             */
            void sort();

            /**
             * Returns the number of points that make up the convex hull.
             */
            uint32_t getNumPoints() const;
            
            /**
             * Returns a container with all of the points in the convex hull.
             * The vertices compose a polygon and are stored in a counterclockwise order.
             */
            std::vector<Point2f> const& getHull() const;

        protected:

            void createHull();
            void splitCollection(LineSegment2Df const& segment, std::vector<Point2f>& leftGroup, std::vector<Point2f>& rightGroup);
            void findHull(LineSegment2Df const& segment, std::vector<Point2f>& points);

        private:

            std::vector<Point2f> m_Points;
            std::vector<Point2f> m_Hull;
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