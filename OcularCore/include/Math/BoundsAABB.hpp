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

            BoundsAABB(Vector3f const& center, Vector3f const& extents);
            BoundsAABB();
            ~BoundsAABB();

            void setCenter(Vector3f const& center);
            void setExtents(Vector3f const& extents);

            Vector3f const& getCenter() const;
            Vector3f const& getExtents() const;

            void expand(Vector3f const& extents);
            void expandToContain(Vector3f const& point);
            void expandToContain(BoundsAABB const& bounds);

            bool contains(Vector3f const& point) const;
            bool contains(BoundsAABB const& bounds) const;

        protected:

        private:

            Vector3f m_Center;
            Vector3f m_Extents;
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