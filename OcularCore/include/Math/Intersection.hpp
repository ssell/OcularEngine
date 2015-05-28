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
#include "BoundsAABB.hpp"
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
         * Performs an intersection test on a ray and AABB.
         *
         * \param[in]  ray
         * \param[in]  box
         * \param[out] point The point that the ray and AABB intersect, if they intersect.
         *
         * \return TRUE if the ray and bounding box intersect.
         */
        static bool Intersects(Ray const& ray, BoundsAABB const& box, Vector3f& point);

        /**
         * Performs an intersection test on a ray and frustum.
         *
         * \param[in]  ray
         * \param[in]  frustum
         * \param[out] point   The point that the ray and frustum intersect, if they intersect.
         */
        static bool Intersects(Ray const& ray, Frustum const& frustum, Vector3f& point);
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