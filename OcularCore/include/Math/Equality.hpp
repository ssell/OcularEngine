/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_ENGINE_MATH_EQUALITY__H__
#define __H__OCULAR_ENGINE_MATH_EQUALITY__H__

#include "MathCommon.hpp"
#include <cmath>

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
        // We have overridden versions for double and float but maintain the use of templates for 
        // them (despite them not needing templates) to keep convention consistant between all types.

        // TODO: There is a different way of accomplishing this but I do not remember.

        /**
         * Floating point comparison of double types.
         */
        template<typename T>
        static bool IsEqual(double const a, double const b, double epsilon = EPSILON_DOUBLE)
        {
            //return std::fabs(a - b) <= (((std::fabs(a) > std::fabs(b)) ? std::fabs(b) : std::fabs(a)) * epsilon);
            return std::abs(a - b) < epsilon;
        }
        
        /**
         * Floating point comparison of float types.
         */
        template<typename T>
        static bool IsEqual(float const a, float const b, float epsilon = EPSILON_FLOAT)
        {
            //return std::fabs(a - b) <= (((std::fabs(a) > std::fabs(b)) ? std::fabs(b) : std::fabs(a)) * epsilon);
            return std::abs(a - b) < epsilon;
        }
        
        /**
         * Default type comparison.
         */
        template<typename T>
        static bool IsEqual(T const a, T const b)
        {
            return (a == b);
        }

        template<typename T>
        static bool IsZero(T const a)
        {
            return IsEqual<T>(a, static_cast<T>(0));
        }

        template<typename T>
        static bool IsOne(T const a)
        {
            return IsEqual<T>(a, static_cast<T>(1));
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

#endif