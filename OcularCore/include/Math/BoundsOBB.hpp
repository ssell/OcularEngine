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
#ifndef __H__OCULAR_MATH_BOUNDS_OBB__H__
#define __H__OCULAR_MATH_BOUNDS_OBB__H__

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
         * \class BoundsOBB
         *
         * Implementation of an Oriented Bounding Box.
         *
         * Essentially an OBB is an AABB that can be arbitrarily rotated.
         * They are more expensive to create and their intersection tests
         * are more complicated, but have the benefit of not needing to
         * be recalculated every time their contents are rotated.
         *
         * Additionally, in most cases an OBB will also provide a tighter
         * fit than an AABB.
         */
        class BoundsOBB
        {
        public:

            BoundsOBB(Vector3f const& center, Vector3f const& extents, Vector3f const& xDir, Vector3f const& yDir, Vector3f const& zDir);
            BoundsOBB();
            ~BoundsOBB();

            /**
             * Returns the center of the bounding box.
             */
            Vector3f const& getCenter() const;

            /**
             * Returns the positive half-lengths of the box.
             * These are the distances along each local axis to the box edge.
             */
            Vector3f const& getExtents() const;

            /**
             * Returns the normalized direction of the x-axis of the bounding box.
             */
            Vector3f const& getDirectionX() const;

            /**
             * Returns the normalized direction of the y-axis of the bounding box.
             */
            Vector3f const& getDirectionY() const;

            /**
             * Returns the normalized direction of the z-axis of the bounding box.
             */
            Vector3f const& getDirectionZ() const;


        protected:

        private:

            Vector3f m_Center;      ///< Center point of the box
            Vector3f m_Extents;     ///< Positive half-lengths
            Vector3f m_DirectionX;  ///< Normalized direction of the X side direction
            Vector3f m_DirectionY;  ///< Normalized direction of the Y side direction
            Vector3f m_DirectionZ;  ///< Normalized direction of the Z side direction
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