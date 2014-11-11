/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_ENGINE_MATH_COMMON__H__
#define __H__OCULAR_ENGINE_MATH_COMMON__H__

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
        static const double PI           = 3.14159265;
        static const double PI_TWO       = 6.28318531;
        static const double PI_OVER_180  = 0.01745329;
        static const double PI_UNDER_180 = 57.2957796;
        static const double PHI          = 1.61803399;

        static const double EPSILON_DOUBLE = 0.0001;
        static const double EPSILON_FLOAT  = 0.0001f;

        /**
         * Clamps the specified value to the range of [lower, upper]
         *
         * \param[in] value The value to clamp
         * \param[in] lower The lower bounds of the clamping region
         * \param[in] upper The upper bounds of the clamping region
         */
        template<typename T>
        static T Clamp(T const value, T const lower, T const upper)
        {
            return ((value < lower) ? lower : (value > upper) ? upper : value);
        }

        /**
         * Rounds the provided value to the specified precision level.<br/>
         * This method deals with the rounding of decimal points.<br/><br/>
         *
         * Examples:<br/><br/>
         *
         * RoundUpDecimal(0.2749999, 2) = 0.28 <br/>
         * RoundUpDecimal(0.86736, 3) = 0.868
         *
         * \param[in] value Value to round
         * \param[in] precision Number of decimal points to round to
         */
        template<typename T>
        static T RoundUpDecimal(T value, int const precision)
        {
            value *= std::pow(10, precision);
            value = std::ceil(value);
            value /= std::pow(10, precision);

            return value;
        }

        /**
         * Rounds the provided value to the specified precision level.<br/>
         * This method deals with the rounding to the nearest power of ten increment.<br/><br/>
         *
         * For example, if precision is 3, it will round to the nearest thousands. 
         * If precision is 2, it will round to the nearest hundreds.<br/><br/>
         *
         * Examples:<br/><br/>
         *
         * RoundUpPowTen(1250, 3) = 2000 <br/>
         * RoundUpPowTen(18, 2) = 100
         *
         * \param[in] value Value to round
         * \param[in] precision Closest pow of ten to round to
         */
        template<typename T>
        static T RoundUpPowTen(T value, int const precision)
        {
            value /= std::pow(10, precision);
            value  = std::ceil(value);
            value *= std::pow(10, precision);

            return value;
        }

        /**
         * Rounds the provided value to the specified precision level.<br/>
         * This method deals with the rounding of decimal points.<br/><br/>
         *
         * Examples:<br/><br/>
         *
         * RoundUpDecimal(0.2749999, 2) = 0.27 <br/>
         * RoundUpDecimal(0.86736, 3) = 0.867
         *
         * \param[in] value Value to round
         * \param[in] precision Number of decimal points to round to
         */
        template<typename T>
        static T RoundDownDecimal(T value, int const precision)
        {
            value *= std::pow(10, precision);
            value = std::floor(value);
            value /= std::pow(10, precision);

            return value;
        }

        /**
         * Rounds the provided value to the specified precision level.<br/>
         * This method deals with the rounding to the nearest power of ten increment.<br/><br/>
         *
         * For example, if precision is 3, it will round to the nearest thousands.
         * If precision is 2, it will round to the nearest hundreds.<br/><br/>
         *
         * Examples:<br/><br/>
         *
         * RoundUpPowTen(1250, 3) = 1000 <br/>
         * RoundUpPowTen(18, 2) = 0
         *
         * \param[in] value Value to round
         * \param[in] precision Closest pow of ten to round to
         */
        template<typename T>
        static T RoundDownPowTen(T value, int const precision)
        {
            value /= std::pow(10, precision);
            value = std::floor(value);
            value *= std::pow(10, precision);

            return value;
        }

        /**
         * Rounds the provided value to the specified precision level.<br/>
         * This method deals with the rounding of decimal points.<br/><br/>
         *
         * This will round either up or down, depending on which is closest.<br/><br/>
         *
         * Examples:<br/><br/>
         *
         * RoundDecimal(2.67, 2) = 2.70 <br/>
         * RoundDecimal(2.63, 2) = 2.60
         *
         * \param[in] value Value to round
         * \param[in] precision Number of decimal points to round to
         */
        template<typename T>
        static T RoundDecimal(T value, int const precision)
        {
            T up = RoundUpDecimal(value, precision);
            T down = RoundDownDecimal(value, precision);

            T upDiff   = static_cast<T>(std::abs(static_cast<double>(value) - static_cast<double>(up)));
            T downDiff = static_cast<T>(std::abs(static_cast<double>(value) - static_cast<double>(down)));

            if(upDiff < downDiff)
            {
                return up;
            }
            else
            {
                return down;
            }
        }

        /**
         * Rounds the provided value to the specified precision level.<br/>
         * This method deals with the rounding to the nearest power of ten increment.<br/><br/>
         *
         * For example, if precision is 3, it will round to the nearest thousands.
         * If precision is 2, it will round to the nearest hundreds.<br/><br/>
         *
         * Examples:<br/><br/>
         *
         * RoundPowTen(1700, 3) = 2000 <br/>
         * RoundPowTen(1300, 3) = 1000
         *
         * \param[in] value Value to round
         * \param[in] precision Number of decimal points to round to
         */
        template<typename T>
        static T RoundPowTen(T value, int const precision)
        {
            T up = RoundUpPowTen(value, precision);
            T down = RoundDownPowTen(value, precision);

            T upDiff = static_cast<T>(std::abs(static_cast<double>(value)-static_cast<double>(up)));
            T downDiff = static_cast<T>(std::abs(static_cast<double>(value)-static_cast<double>(down)));

            if(upDiff < downDiff)
            {
                return up;
            }
            else
            {
                return down;
            }
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