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
#ifndef __H__OCULAR_MATH_BOUNDS_SPHERE__H__
#define __H__OCULAR_MATH_BOUNDS_SPHERE__H__

#include "Math/Vector3.hpp"
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
         * \class BoundsSphere
         */
        class BoundsSphere
        {
        public:

            BoundsSphere(std::list<Point3f> const& points);
            BoundsSphere(Vector3f const& center, float radius);
            BoundsSphere();
            ~BoundsSphere();

            /**
             * Constructs the bounds from a collection of spatial points.
             * \param[in] points
             */
            void construct(std::list<Point3f> const& points);
            
            /**
             * Sets the center of the bounding sphere.
             * \param[in] center
             */
            void setCenter(Vector3f const& center);

            /**
             * Sets the radius of the bounding sphere.
             * \param[in] radius
             */
            void setRadius(float radius);

            /**
             * Returns the center of the bounding sphere.
             */
            Vector3f const& getCenter() const;
            
            /**
             * Returns the radius of the bounding sphere.
             */
            float getRadius() const;

            /**
             * Expands the radius of the bounding sphere by the specified amount.
             * \param[in] amount
             */
            void expand(float const amount);

            /**
             * Expands the bounding sphere so that it contains the specified point.
             * If the point is already in the sphere then no action is taken.
             *
             * \param[in] point
             */
            void expandToContain(Point3f const& point);

            /**
             * Calculates if the bounds contains the specified point.
             *
             * To test for just intersection, see the series of Ocular::Math::Intersects functions.
             *
             * \param[in]  point
             * \param[out] result The exact result of the containment test (intersection, outside, inside).
             *
             * \return TRUE if point is inside or intersects.
             */
            bool contains(Point3f const& point, IntersectionType* result = nullptr) const;

            /**
             * Calculates if any portion of the specified bounding sphere is contained within the spere.
             *
             * To test for just intersection, see the series of Ocular::Math::Intersects functions.
             *
             * \param[in]  sphere
             * \param[out] result The exact result of the containment test (intersection, outside, inside).
             *
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsSphere const& sphere, IntersectionType* result = nullptr) const;

        protected:

        private:

            Vector3f m_Center;
            float m_Radius;

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