/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Math/Bounds/Bounds.hpp"
#include "Math/Vector3.hpp"

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
        class Ray;
        class BoundsSphere;
        class BoundsAABB;
        class Plane;

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
        class BoundsOBB : public Bounds
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
             * /param[in] center
             */
            void setCenter(Vector3f const& center);

            /**
             * Returns the positive half-lengths of the box.
             * These are the distances along each local axis to the box edge.
             */
            Vector3f const& getExtents() const;
            
            /**
             * /param[in] extents
             */
            void setExtents(Vector3f const& extents);

            /**
             * Returns the normalized direction of the x-axis of the bounding box.
             */
            Vector3f const& getDirectionX() const;
            
            /**
             * /param[in] dirX
             */
            void setDirectionX(Vector3f const& dirX);

            /**
             * Returns the normalized direction of the y-axis of the bounding box.
             */
            Vector3f const& getDirectionY() const;
            
            /**
             * /param[in] dirY
             */
            void setDirectionY(Vector3f const& dirY);

            /**
             * Returns the normalized direction of the z-axis of the bounding box.
             */
            Vector3f const& getDirectionZ() const;

            /**
             * /param[in] dirZ
             */
            void setDirectionZ(Vector3f const& dirZ);

            //------------------------------------------------------------------------------
            // Intersection and Containment Testing
            //------------------------------------------------------------------------------

            /**
             * Performs an intersection test on a ray and OBB.
             *
             * \param[in] ray
             * \return TRUE if the ray and OBB intersect.
             */
            bool intersects(Ray const& ray) const;

            /**
             * Performs an intersection test on a bounding sphere and OBB.
             *
             * \param[in] bounds
             * \return TRUE if the bounding sphere and OBB intersect.
             */
            bool intersects(BoundsSphere const& bounds) const;

            /**
             * Performs an intersection test on a AABB and OBB.
             *
             * \param[in] bounds
             * \return TRUE if the AABB and OBB intersect.
             */
            bool intersects(BoundsAABB const& bounds) const;
            
            
            /**
             * Performs an intersection test on two OBBs.
             *
             * \param[in] bounds
             * \return TRUE if the two OBBs intersect.
             */
            bool intersects(BoundsOBB const& bounds) const;

            /**
             * Performs an intersection test on a plane and OBB.
             *
             * If the result is Inside, then the OBB is located entirely within the plane's positive half space. <br/>
             * If the result is Outside, then the OBB is located entirely outside the plane's positive half space.
             *
             * The positive half space of the plane is the direction that the plane is facing, as described by it's normal.
             *
             * As an example, say we have the plane defined as:
             *
             *      Point: (0.0, 0.0, 0.0)
             *     Normal: (0.0, 1.0, 0.0)
             *
             * The plane is 'facing up' along the world origin.
             *
             * If the intersection test returns Outside, then the AABB is entirely in the +y world space. <br/>
             * If the intersection test returns Inside, then the AABB is entirely in the -y world space.
             *
             * \param[in]  plane
             * \param[out] result Detailed intersection result.
             *
             * \return TRUE if the plane and OBB intersects, otherwise FALSE.
             */
            bool intersects(Plane const& plane, IntersectionType* result = nullptr) const;

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