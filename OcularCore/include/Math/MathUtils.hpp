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
#ifndef __H__OCULAR_ENGINE_MATH_UTILS__H__
#define __H__OCULAR_ENGINE_MATH_UTILS__H__

#include "Vector4.hpp"

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
         * Calculates a point on the edge of a circle.
         *
         * \param[in] center Center of the circle
         * \param[in] radius Circle radius (distance from point to circle center)
         * \param[in] angle  Angle of point in degrees
         */
        static Vector2f PointOnCircle(Vector2f const& center, float const radius, float const angle)
        {
            const float angleRad = DegreesToRadians(angle);
            
            Vector2f result = center;

            result.x += cosf(angleRad) * radius;
            result.y += sinf(angleRad) * radius;

            return result;
        }

        /**
         * Calculates a point on the surface of a sphere.
         *
         * \param[in] center Center of the sphere
         * \param[in] radius Sphere radius (distance from point to sphere center)
         * \param[in] angleX Angle of the x-rotation in degrees
         * \param[in] angleY Angle of the y-rotation in degrees
         */
        static Vector3f PointOnSphere(Vector3f const& center, float const radius, float const angleX, float const angleY)
        {
            const float radX = DegreesToRadians(angleX);
            const float radY = DegreesToRadians(angleY);

            Vector3f result = center;

            result.x += cosf(radX) * sinf(radY) * radius;
            result.y += sinf(radX) * sinf(radY) * radius;
            result.z += cosf(radY) * radius;

            return result;
        }
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif#pragma once
