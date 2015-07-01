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
#ifndef __H__OCULAR_ENGINE_MATH_COMMON__H__
#define __H__OCULAR_ENGINE_MATH_COMMON__H__

#include "Definitions.hpp"
#include "Equality.hpp"
#include "Interpolation.hpp"

#include <cmath>
#include <cstdint>
#include <algorithm>

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
        //----------------------------------------------------------------------------------
        // Enums
        //----------------------------------------------------------------------------------

        enum class IntersectionType : int8_t
        {
            Intersects = 0,   ///< The object intersects the bounds and is not fully inside or outside.
            Outside = 1,      ///< There is no intersection and the object is full
            Inside = 2
        };

        //----------------------------------------------------------------------------------
        // Type Checking
        //----------------------------------------------------------------------------------

        /**
         * \struct TypeIsInteger
         * \brief Used to determine if a template type is an integer.
         *
         * Example of usage:
         *
         *     if(TypeIsInteger<T>::value)
         *     {
         *         // Do integer-based operation
         *     }
         *     else
         *     {
         *         // Do floating-point operation
         *     }
         *
         * Value will be equal to TRUE in all cases except for when T is a float or double.
         */
        template<typename T>
        struct TypeIsInteger { static const bool value = true; };

        template<>
        struct TypeIsInteger<float> { static const bool value = false; };

        template<>
        struct TypeIsInteger<double> { static const bool value = false; };

        //----------------------------------------------------------------------------------
        // Common Functions
        //----------------------------------------------------------------------------------

        /**
         * Performs a fast floor operation on the provided floating point value.
         *
         * \param[in] value
         */
        static int32_t Floor(const float value)
        {
            return (value > 0) ? static_cast<int>(value) : static_cast<int>(value) - 1;
        }
        
        /**
         * Performs a fast floor operation on the provided floating point value.
         *
         * \param[in] value
         */
        static int32_t Floor(const double value)
        {
            return (value > 0) ? static_cast<int>(value) : static_cast<int>(value) - 1;
        }

        /**
         * Calculates the inverse square root of the value.
         *
         * \param[in] value
         */
        template<typename T>
        static T InverseSqrt(T const& value)
        {
            return static_cast<T>(1) / sqrt(value);
        }

        /**
         * Normalises the specified value into the provided range. Example:
         *
         *     Normalise(240.0f, -180.0f, 180.0f) = 60.0f
         *
         * \param[in] value
         * \param[in] rangeStart Start of the range (smallest allowed value)
         * \param[in] rangeEnd   End of the range (largest allowed value)
         */
        template<typename T>
        static T Normalize(T const& value, T const& rangeStart, T const& rangeEnd)
        {
            // Yes this is a naive implementation. Have yet to find another that
            // works on all types (integer, floating-point, positive, negative).

            T result = value;
            T width  = rangeEnd - rangeStart;

            while(result > rangeEnd)
            {
                result -= width;
            }

            while(result < rangeStart)
            {
                result += width;
            }

            return result;
        }

        /**
         * Converts the input radians value into degrees.
         *
         * \param[in] radians
         */
        template<typename T>
        static T RadiansToDegrees(T const& radians)
        {
            double dRads = static_cast<double>(radians);
            dRads = Normalize<double>(dRads, -PI_TWO, PI_TWO);

            return static_cast<T>(dRads * PI_UNDER_180);
        }

        /**
         * Converts the input degrees value into radians.
         *
         * \param[in] degrees
         */
        template<typename T>
        static T DegreesToRadians(T const& degrees)
        {
            double dDegs = static_cast<double>(degrees);
            dDegs = Normalize<double>(dDegs, -360.0, 360.0);

            return static_cast<T>(dDegs * PI_OVER_180);
        }

        /**
         * Clamps the specified value to the range of [lower, upper]
         *
         * \param[in] value The value to clamp
         * \param[in] lower The lower bounds of the clamping region
         * \param[in] upper The upper bounds of the clamping region
         */
        template<typename T>
        static T Clamp(T const value, T const lower = static_cast<T>(0), T const upper = static_cast<T>(1))
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

		/**
		 * Counts and returns the number of leading zeros in the provided 32-bit unsigned integer.
		 * 
		 * \param[in] value
		 * \return Number of leading zeros.
		 */
		static inline uint32_t Clz(uint32_t const value)
		{
			// Yes, there are multiple intrinsic methods available (_lzcnt, _lzcnt_u32, __builtin_clz) but Ocular
			// is not targetting a specific architecture, compiler, OS, etc. and there are no native C++ calls for this op.

			// Source: http://embeddedgurus.com/state-space/2014/09/fast-deterministic-and-portable-counting-leading-zeros/

			static uint8_t const table[] = {
				32U, 31U, 30U, 30U, 29U, 29U, 29U, 29U,
				28U, 28U, 28U, 28U, 28U, 28U, 28U, 28U,
				27U, 27U, 27U, 27U, 27U, 27U, 27U, 27U,
				27U, 27U, 27U, 27U, 27U, 27U, 27U, 27U,
				26U, 26U, 26U, 26U, 26U, 26U, 26U, 26U,
				26U, 26U, 26U, 26U, 26U, 26U, 26U, 26U,
				26U, 26U, 26U, 26U, 26U, 26U, 26U, 26U,
				26U, 26U, 26U, 26U, 26U, 26U, 26U, 26U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				25U, 25U, 25U, 25U, 25U, 25U, 25U, 25U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U,
				24U, 24U, 24U, 24U, 24U, 24U, 24U, 24U
			};

			uint32_t n;

			if(value >= (1U << 16))
			{
				if(value >= (1U << 24))
				{
					n = 24U;
				}
				else
				{
					n = 16U;
				}
			}
			else
			{
				if(value >= (1U << 8))
				{
					n = 8U;
				}
				else
				{
					n = 0U;
				}
			}

			return (uint32_t)(table[value >> n]) - n;
		}

		/**
		 * Counts and returns the number of leading zeros in the provided 64-bit unsigned integer.
		 * 
		 * \param[in] value
		 * \return Number of leading zeros.
		 */
		static inline uint32_t Clz(uint64_t value)
		{
			// Yes, there are multiple intrinsic methods available (_lzcnt64, _lzcnt_u64, __builtin_clz) but Ocular
			// is not targetting a specific architecture, compiler, OS, etc. and there are no native C++ calls for this op.
			
			// Naive implementation, yes. But all of the 'fancy' solutions seem to break down with 64-bit values.

			// Source: http://codingforspeed.com/counting-the-number-of-leading-zeros-for-a-32-bit-integer-signed-or-unsigned/

			uint32_t result = 0;

			if(value == 0)
			{
				result = 64;
			}
			else
			{
				while(value >>= 1)
				{
					result++;
				}

				result = (64 - (result + 1));
			}

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

#endif