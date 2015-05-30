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
#ifndef __H__OCULAR_MATH_INTERSECTION__H__
#define __H__OCULAR_MATH_INTERSECTION__H__

#include "Ray.hpp"
#include "BoundsSphere.hpp"
#include "BoundsAABB.hpp"
#include "BoundsOBB.hpp"
#include "Frustum.hpp"

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
         * Performs an intersection test on two rays.
         * 
         * \param[in]  rayA
         * \param[in]  rayB
         * \param[out] point The point that the rays intersect, if they intersect.
         *
         * \return TRUE if the two rays intersect.
         */
        static bool Intersects(Ray const& rayA, Ray const& rayB, Vector3f& point);

        /**
         * Performs an intersection test on a ray and bounding sphere.
         *
         * \param[in] ray
         * \param[in] bounds
         *
         * \return TRUE if the ray and bounding sphere intersect.
         */
        static bool Intersects(Ray const& ray, BoundsSphere const& bounds);

        /**
         * Performs an intersection test on a ray and bounding sphere.
         *
         * This version of the method also returns the point at which the two intersect.
         * If speed is of the uptmost concern and/or the exact point of intersection is
         * not required, then the other version may be used instead.
         *
         * \param[in]  ray
         * \param[in]  bounds
         * \param[out] point    The point that the ray and bounding sphere intersects.
         * \param[out] distance The distance from the ray origin to the point of intersection.
         *
         * \return TRUE if the ray and bounding sphere intersect.
         */
        static bool Intersects(Ray const& ray, BoundsSphere const& bounds, Vector3f& point, float& distance);

        /**
         * Performs an intersection test on a ray and AABB.
         *
         * \param[in]  ray
         * \param[in]  bounds
         *
         * \return TRUE if the ray and AABB intersect.
         */
        static bool Intersects(Ray const& ray, BoundsAABB const& bounds);

        /**
         * Performs an intersection test on a ray and AABB.
         *
         * This version of the method also returns the point at which the two intersect.
         * If speed is of the uptmost concern and/or the exact point of intersection is
         * not required, then the other version may be used instead.
         *
         * \param[in]  ray
         * \param[in]  bounds
         * \param[out] point    The point that the ray and AABB intersect, if they intersect.
         * \param[out] distance The distance from the ray origin to the point of intersection.
         *
         * \return TRUE if the ray and AABB intersect.
         */
        static bool Intersects(Ray const& ray, BoundsAABB const& bounds, Vector3f& point, float& distance);

        /**
         * Performs an intersection test on a ray and AABB.
         *
         * \param[in]  ray
         * \param[in]  bounds
         *
         * \return TRUE if the ray and AABB intersect.
         */
        static bool Intersects(Ray const& ray, BoundsOBB const& bounds);

        /**
         * Performs an intersection test on a ray and OBB.
         *
         * This version of the method also returns the point at which the two intersect.
         * If speed is of the uptmost concern and/or the exact point of intersection is
         * not required, then the other version may be used instead.
         *
         * \param[in]  ray
         * \param[in]  bounds
         * \param[out] point    The point that the ray and AABB intersect, if they intersect.
         * \param[out] distance The distance from the ray origin to the point of intersection.
         *
         * \return TRUE if the ray and OBB intersect.
         */
        static bool Intersects(Ray const& ray, BoundsOBB const& bounds, Vector3f& point, float& distance);

        /**
         * Performs an intersection test on two bounding spheres.
         *
         * \param[in] boundsA
         * \param[in] boundsB
         *
         * \return TRUE if the two bounding spheres intersect.
         */
        static bool Intersects(BoundsSphere const& boundsA, BoundsSphere const& boundsB);

        /**
         * Performs an intersection test on a bounding sphere and AABB.
         *
         * \param[in] boundsA
         * \param[in] boundsB
         *
         * \return TRUE if the bounding sphere and AABB intersect.
         */
        static bool Intersects(BoundsSphere const& boundsA, BoundsAABB const& boundsB);

        /**
         * Performs an intersection test on a bounding sphere and AABB.
         *
         * \param[in] boundsA
         * \param[in] boundsB
         *
         * \return TRUE if the bounding sphere and AABB intersect.
         */
        static bool Intersects(BoundsAABB const& boundsA, BoundsSphere const& boundsB);
        
        /**
         * Performs an intersection test on two AABBs.
         *
         * \param[in] boundsA
         * \param[in] boundsB
         *
         * \return TRUE if the two AABBs intersect.
         */
        static bool Intersects(BoundsAABB const& boundsA, BoundsAABB const& boundsB);
        
        /**
         * Performs an intersection test on two OBBs.
         *
         * \param[in] boundsA
         * \param[in] boundsB
         *
         * \return TRUE if the two OBBs intersect.
         */
        static bool Intersects(BoundsOBB const& boundsA, BoundsOBB const& boundsB);

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