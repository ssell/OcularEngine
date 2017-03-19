/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_MATH_RAY__H__
#define __H__OCULAR_MATH_RAY__H__

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
        class BoundsSphere;
        class BoundsAABB;
        class BoundsOBB;
        class Plane;

        /**
         * \class Ray
         *
         * An infinite line that has an origin and direction.
         */
        class Ray
        {
        public:

            /**
             * Creates a ray with the specified origin and direction.
             *
             * \param[in] origin 
             * \param[in] direction Normalized vector direction.
             */
            Ray(Vector3f const& origin, Vector3f const& direction);
            
            Ray();
            ~Ray();

            /**
             * Sets the origin of the ray.
             */
            void setOrigin(Vector3f const& origin);

            /**
             * Sets the normalized direction of the ray.
             */
            void setDirection(Vector3f const& direction);

            /**
             * Returns the origin of the ray.
             */
            Vector3f const& getOrigin() const;

            /**
             * Returns the normalized direction of the ray.
             */
            Vector3f const& getDirection() const;

            /**
             * Returns the point that lies the given distance along the ray
             */
            Vector3f getPointAlong(float distance) const;

            //------------------------------------------------------------------------------
            // Intersection and Containment Testing
            //------------------------------------------------------------------------------
            
            /**
             * Performs an intersection test on a ray and point.
             * 
             * \param[in] point
             * \return TRUE if the two rays intersect.
             */
            bool intersects(Point3f const& point) const;

            /**
             * Performs an intersection test on two rays.
             * 
             * \param[in] other
             * \return TRUE if the two rays intersect.
             */
            bool intersects(Ray const& other) const;

            /**
             * Performs an intersection test on two rays.
             * 
             * \param[in]  other
             * \param[out] point    The point that the rays intersect, if they intersect.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the two rays intersect.
             */
            bool intersects(Ray const& other, Point3f& point, float& distance) const;
            
            /**
             * Performs an intersection test on a ray and bounding sphere.
             *
             * \param[in] bounds
             * \return TRUE if the ray and bounding sphere intersect.
             */
            bool intersects(BoundsSphere const& bounds) const;

            /**
             * Performs an intersection test on a ray and bounding sphere.
             *
             * This version of the method also returns the point at which the two intersect.
             * If speed is of the uptmost concern and/or the exact point of intersection is
             * not required, then the other version may be used instead.
             *
             * \param[in]  bounds
             * \param[out] point    The point that the ray and bounding sphere intersects.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the ray and bounding sphere intersect.
             */
            bool intersects(BoundsSphere const& bounds, Point3f& point, float& distance) const;
            
            /**
             * Performs an intersection test on a ray and AABB.
             *
             * \param[in] bounds
             * \return TRUE if the ray and AABB intersect.
             */
            bool intersects(BoundsAABB const& bounds) const;
            
            /**
             * Performs an intersection test on a ray and AABB.
             *
             * This version of the method also returns the point at which the two intersect.
             * If speed is of the uptmost concern and/or the exact point of intersection is
             * not required, then the other version may be used instead.
             *
             * \param[in]  bounds
             * \param[out] point    The point that the ray and AABB intersect, if they intersect.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the ray and AABB intersect.
             */
            bool intersects(BoundsAABB const& bounds, Point3f& point, float& distance) const;
            
            /**
             * Performs an intersection test on a ray and OBB.
             *
             * \param[in] bounds
             * \return TRUE if the ray and OBB intersect.
             */
            bool intersects(BoundsOBB const& bounds) const;
            
            /**
             * Performs an intersection test on a ray and OBB.
             *
             * This version of the method also returns the point at which the two intersect.
             * If speed is of the uptmost concern and/or the exact point of intersection is
             * not required, then the other version may be used instead.
             *
             * \param[in]  bounds
             * \param[out] point    The point that the ray and OBB intersect, if they intersect.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the ray and OBB intersect.
             */
            bool intersects(BoundsOBB const& bounds, Point3f& point, float& distance) const;

            /**
             * Performs an intersection test on a ray and plane.
             *
             * Note that this operation is actually a line-plane intersection.
             * The line begins at ray origin and extends RAY_LINE_LENGTH.
             *
             * \param[in] plane
             * \return TRUE if the ray and plane intersect.
             */
            bool intersects(Plane const& plane) const;

            /**
             * Performs an intersection test on a ray and plane.
             *
             * Note that this operation is actually a line-plane intersection.
             * The line begins at ray origin and extends RAY_LINE_LENGTH.
             *
             * \param[in]  plane
             * \param[out] point The point that the ray and AABB intersect, if they intersect.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the ray and plane intersect.
             */
            bool intersects(Plane const& plane, Vector3f& point, float& distance) const;

        protected:

        private:

            Vector3f m_Origin;
            Vector3f m_Direction;

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