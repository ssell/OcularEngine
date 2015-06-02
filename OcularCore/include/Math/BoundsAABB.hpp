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
#ifndef __H__OCULAR_MATH_BOUNDS_AABB__H__
#define __H__OCULAR_MATH_BOUNDS_AABB__H__

#include "Vector3.hpp"
#include <list>

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
         * \class BoundsAABB
         *
         * Implementation of an Axis Aligned Bounding Box.
         *
         * As per it's name, an AABB is always aligned according to the world axis and
         * thus can never rotate. Instead, when the object it contains is rotated, the
         * AABB must be recalculated.
         *
         * Intersection testing with AABBs is very fast, but can be fairly inaccurate, 
         * and thus they are typically used for first pass tests of culling and collision tests.
         *
         * To perform an intersection test see the Ocular::Math::Intersects functions.
         */
        class BoundsAABB
        {
        public:

            /**
             * Creates a new AABB from a list of spatial points.
             * \param[in] points
             */
            BoundsAABB(std::list<Point3f> const& points);

            /**
             * Creates a new AABB with the specified parameters.
             *
             * \param[in] center Center position of the AABB
             * \param[in] extents Extents along each axis from the center. So an extents of (5.0, 5.0, 5.0) would result in a 10x10x10 AABB.
             */
            BoundsAABB(Vector3f const& center, Vector3f const& extents);

            BoundsAABB();

            ~BoundsAABB();

            /**
             * Constructs the bounds from a collection of spatial points.
             *
             * \param[in] points
             */
            void construct(std::list<Point3f> const& points);

            /**
             * Sets the center point of the bounding box.
             *
             * The minimum and maximum points will be automatically updated
             * to take into account the new center.
             *
             * \param[in] center
             */
            void setCenter(Vector3f const& center);

            /**
             * Sets the positive half-lengths of the bounding box sides.
             *
             * The minimum and maximum points will be automatically updated
             * to take into account the new extents.
             *
             * \param[in] extents
             */
            void setExtents(Vector3f const& extents);

            /**
             * \return The center point of the bounding box.
             */
            Vector3f const& getCenter() const;

            /**
             * \return The extents (side half-lenths) of the bounding box.
             */
            Vector3f const& getExtents() const;

            /**
             * \return The smallest point furthest from the center that is contained within the box.
             */
            Vector3f const& getMinPoint() const;

            /**
             * \return The largest point furthest from the center that is contained within the box.
             */
            Vector3f const& getMaxPoint() const;

            /**
             * Linearly modifies the extents according to the specified values.
             * 
             * If positie modifiers are given, then the box will expand outward.
             * If negative modifiers are given, then the box will shrink inward.
             *
             * The extents can not be negative and thus will be clamped to 0.0 if necessary.
             *
             * \param[in] modifier
             */
            void expand(Vector3f const& modifier);

            /**
             * Expands the bounding box so that it contains the specified point.
             * If the box already contains the point, then no action will be taken.
             *
             * \param[in] point
             */
            void expandToContain(Vector3f const& point);

            /**
             * Expands the bounding box so that it contains the specified bounds.
             * If the box already fully contains the bounds, then no action will be taken.
             *
             * \param[in] point
             */
            void expandToContain(BoundsAABB const& bounds);

            /**
             * Calculates if the bounds contains the specified point.
             *
             * To test for just intersection, see the series of Ocular::Math::Intersects functions.
             *
             * \param[in]  point
             * \param[out] result         The exact result of the containment test (intersection, outside, inside).
             * \param[in]  testIntersects If true, performs additional steps to test if the point is fully inside or intersects.
             *                            If false, the only possible results are Inside or Outside (an intersection would result in an Inside result).
             *
             * \return TRUE if point is inside or intersects.
             */
            bool contains(Vector3f const& point, ContainsResult* result = nullptr, bool testIntersects = false) const;

            /**
             * Calculates if any portion of the specified bounds is contained within the AABB.
             *
             * To test for just intersection, see the series of Ocular::Math::Intersects functions.
             *
             * \param[in]  bounds
             * \param[out] result         The exact result of the containment test (intersection, outside, inside).
             * \param[in]  testIntersects If true, performs additional steps to test if the point is fully inside or intersects.
             *                            If false, the only possible results are Inside or Outside (an intersection would result in an Inside result).
             *
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsAABB const& bounds, ContainsResult* result = nullptr, bool testIntersects = false) const;

        protected:

            void calculateMinMaxPoints();

        private:

            Vector3f m_Center;      ///< Center point of the box
            Vector3f m_Extents;     ///< Positive half-lengths
            Vector3f m_MinPoint;    
            Vector3f m_MaxPoint;
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