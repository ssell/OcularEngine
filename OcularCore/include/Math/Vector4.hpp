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
#ifndef __H__OCULAR_MATH_VECTOR_4__H__
#define __H__OCULAR_MATH_VECTOR_4__H__

#include "Equality.hpp"

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
        * \class Vector4
        */
        template<typename T>
        class Vector4
        {
        public:

            Vector4(T const pX, T const pY, T const pZ, T const pW)
            {
                x = pX;
                y = pY;
                z = pZ;
                w = pW;
            }

            Vector4()
            {
                x = 0.0f;
                y = 0.0f;
                z = 0.0f;
                w = 1.0f;
            }

            ~Vector4()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            bool operator==(Vector4<T> const rhs)
            {
                return IsEqual<T>(x, rhs.x) && IsEqual<T>(y, rhs.y) && IsEqual<T>(z, rhs.z) && IsEqual<T>(w, rhs.w);
            }

            bool operator!=(Vector4<T> const rhs)
            {
                return !(*this == rhs);
            }

            Vector4<T>& operator=(Vector4<T> const rhs)
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
                w = rhs.w;

                return *this;
            }

            Vector4<T>& operator+(Vector4<T> const rhs)
            {
                return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
            }

            Vector4<T>& operator+(T const rhs)
            {
                return Vector4<T>(x + rhs, y + rhs, z + rhs, w + rhs);
            }

            Vector4<T>& operator+=(Vector4<T> const rhs)
            {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                w += rhs.w;

                return *this;
            }

            Vector4<T>& operator+=(T const rhs)
            {
                x += rhs;
                y += rhs;
                z += rhs;
                w += rhs;

                return *this;
            }

            Vector4<T>& operator-(Vector4<T> const rhs)
            {
                return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
            }

            Vector4<T>& operator-(T const rhs)
            {
                return Vector4<T>(x - rhs, y - rhs, z - rhs, w - rhs);
            }

            Vector4<T>& operator-=(Vector4<T> const rhs)
            {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                w -= rhs.w;

                return *this;
            }

            Vector4<T>& operator-=(T const rhs)
            {
                x -= rhs;
                y -= rhs;
                z -= rhs;
                w -= rhs;

                return *this;
            }

            Vector4<T>& operator*(Vector4<T> const rhs)
            {
                return Vector4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
            }

            Vector4<T>& operator*(T const rhs)
            {
                return Vector4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
            }

            Vector4<T>& operator*=(Vector4<T> const rhs)
            {
                x *= rhs.x;
                y *= rhs.y;
                z *= rhs.z;
                w *= rhs.w;

                return *this;
            }

            Vector4<T>& operator*=(T const rhs)
            {
                x *= rhs;
                y *= rhs;
                z *= rhs;
                w *= rhs;

                return *this;
            }

            Vector4<T>& operator/(Vector4<T> const rhs)
            {
                return Vector4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
            }

            Vector4<T>& operator/(T const rhs)
            {
                return Vector4<T>(x / rhs, y / rhs, z / rhs, w / rhs);
            }

            Vector4<T>& operator/=(Vector4<T> const rhs)
            {
                x /= rhs.x;
                y /= rhs.y;
                z /= rhs.z;
                w /= rhs.w;

                return *this;
            }

            Vector4<T>& operator/=(T const rhs)
            {
                x /= rhs;
                y /= rhs;
                z /= rhs;
                w /= rhs;

                return *this;
            }

            //------------------------------------------------------------------------------
            // OPERATIONS
            //------------------------------------------------------------------------------

            /**
             * \return The magnitude (length) of the vector.
             */
            double getMagnitude()
            {
                double dX = static_cast<double>(x);
                double dY = static_cast<double>(y);
                double dZ = static_cast<double>(z);
                double dW = static_cast<double>(w);

                return std::sqrt((dX * dX) + (dY * dY) + (dZ * dZ) + (dW * dW));
            }

            /**
             * \return The length of the vector.
             */
            double getLength()
            {
                return getMagnitude();
            }

            /**
             * Normalizes the vector. When normalized, a vector maintains its direction but its magnitude is set to 1.0.
             */
            void normalize()
            {
                // Normalization is simply multiplying the vector by the reciprocal of its magnitude. 

                double length = magnitude();

                if(areEqual<double>(length, 0.0))
                {
                    return Vector4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
                }
                else
                {
                    return Vector4<T>(x / static_cast<T>(length), 
                                      y / static_cast<T>(length), 
                                      z / static_cast<T>(length),
                                      w / static_cast<T>(length));
                }
            }

            /**
             * The dot product is a value equal to the magnitudes of the two vectors multiplied
             * together and then multiplied by the cosine of the angle between them.
             *
             * \param[in] rhs The second vector dot multiply with
             * \return The dot product of the two vectors (in radians)
             */
            double dot(Vector4<T> const rhs)
            {
                return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
            }

            /**
             * This is equivalent to taking the acos of the dot product.<br/>
             * The returned angle is the acute angle, i.e the smallest of the two angles.
             *
             * \param[in] rhs The second vector to calculate the angle with
             * \return The angle, in radians, between the vectors
             */
            double angleBetween(Vector4<T> const rhs)
            {
                double angle = std::acos(dot(rhs));

                if(angle > PI)
                {
                    angle = PI_TWO - angle;
                }

                return angle;
            }

            /**
             * \param[in] rhs The second vector to calculate the distance with
             * \return The distance between the two vectors
             */
            double distanceTo(Vector4<T> const rhs)
            {
                Vector4<T> distance = (*this) - rhs;
                return distance.getMagnitude();
            }

            //------------------------------------------------------------------------------
            // VARIABLES
            //------------------------------------------------------------------------------

            union { T x, r, u, s; };
            union { T y, g, v, t; };
            union { T z, b, p; };
            union { T w, a, q; };

        protected:

        private:
        };

        // Common vector formats
        typedef Vector4<float> Vector4f;
        typedef Vector4<double> Vector4d;

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