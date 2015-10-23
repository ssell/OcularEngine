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
#ifndef __H__OCULAR_MATH_VECTOR_4__H__
#define __H__OCULAR_MATH_VECTOR_4__H__

#include "Equality.hpp"
#include "Vector3.hpp"
#include "Exceptions/Exception.hpp"

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

            Vector4(Vector3<T> const& vec, T pW = static_cast<T>(1.0f))
            {
                x = vec.x;
                y = vec.y;
                z = vec.z;
                w = pW;
            }

            Vector4(T const &pX, T const &pY, T const &pZ, T const &pW)
            {
                x = pX;
                y = pY;
                z = pZ;
                w = pW;
            }

            Vector4()
            {
                x = static_cast<T>(0);
                y = static_cast<T>(0);
                z = static_cast<T>(0);
                w = static_cast<T>(1);
            }

            ~Vector4()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------
            
            T& operator[](unsigned const& index)
            {
                switch(index)
                {
                case 0:
                    return x;
                    
                case 1:
                    return y;

                case 2:
                    return z;

                case 3:
                    return w;

                default:
                    THROW_EXCEPTION("Out-Of-Bounds Vector Access");
                    return x;
                }
            }
            
            T operator[](unsigned const& index) const
            {
                switch(index)
                {
                case 0:
                    return x;
                    
                case 1:
                    return y;

                case 2:
                    return z;

                case 3:
                    return w;

                default:
                    THROW_EXCEPTION("Out-Of-Bounds Vector Access");
                    return x;
                }
            }
            
            Vector4<T> operator-()
            {
                return Vector4<T>(-x, -y, -z, -w);
            }

            Vector4<T>& operator=(Vector4<T> const &rhs)
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
                w = rhs.w;

                return *this;
            }

            Vector4<T>& operator+=(Vector4<T> const &rhs)
            {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                w += rhs.w;

                return *this;
            }

            Vector4<T>& operator+=(T const &rhs)
            {
                x += rhs;
                y += rhs;
                z += rhs;
                w += rhs;

                return *this;
            }

            Vector4<T>& operator-=(Vector4<T> const &rhs)
            {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                w -= rhs.w;

                return *this;
            }

            Vector4<T>& operator-=(T const &rhs)
            {
                x -= rhs;
                y -= rhs;
                z -= rhs;
                w -= rhs;

                return *this;
            }

            Vector4<T>& operator*=(Vector4<T> const &rhs)
            {
                x *= rhs.x;
                y *= rhs.y;
                z *= rhs.z;
                w *= rhs.w;

                return *this;
            }

            Vector4<T>& operator*=(T const &rhs)
            {
                x *= rhs;
                y *= rhs;
                z *= rhs;
                w *= rhs;

                return *this;
            }

            Vector4<T>& operator/=(Vector4<T> const &rhs)
            {
                x /= rhs.x;
                y /= rhs.y;
                z /= rhs.z;
                w /= rhs.w;

                return *this;
            }

            Vector4<T>& operator/=(T const &rhs)
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
            T getMagnitude() const
            {
                return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
            }

            /**
             * \return The length of the vector.
             */
            T getLength() const
            {
                return getMagnitude();
            }

            /**
             * Normalizes the vector. When normalized, a vector maintains its direction but its magnitude is set to 1.0.
             */
            void normalize()
            {
                // Normalization is simply multiplying the vector by the reciprocal of its magnitude. 

                double length = getMagnitude();

                if(IsEqual<T>(length, static_cast<T>(0)))
                {
                    x = static_cast<T>(0);
                    y = static_cast<T>(0);
                    z = static_cast<T>(0);
                    w = static_cast<T>(1);
                }
                else
                {
                    x /= static_cast<T>(length);
                    y /= static_cast<T>(length);
                    z /= static_cast<T>(length);
                    w /= static_cast<T>(length);
                }
            }

            /**
             * Returns the normalized form of this vector
             */
            Vector4<T> getNormalized() const
            {
                Vector4<T> result(x, y, z, w);
                result.normalize();

                return result;
            }

            /**
             * The dot product is a value equal to the magnitudes of the two vectors multiplied
             * together and then multiplied by the cosine of the angle between them.
             *
             * \param[in] rhs The second vector dot multiply with
             * \return The dot product of the two vectors (in radians)
             */
            double dot(Vector4<T> const &rhs) const
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
            double angleBetween(Vector4<T> const &rhs) const
            {
                Vector4<T> normalLHS = getNormalized();
                Vector4<T> normalRHS = rhs.getNormalized();

                double angle = std::acos(normalLHS.dot(normalRHS));

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
            double distanceTo(Vector4<T> const &rhs) const
            {
                Vector4<T> distance = (*this) - rhs;
                return distance.getMagnitude();
            }

            /**
             * Homegenizes the vector (divides all components by w so that w == 1)
             */
            void homogenize()
            {
                x /= w;
                y /= w;
                z /= w;
                w /= w;
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

        //----------------------------------------------------------------------------------
        
        template<typename T>
        bool operator==(Vector4<T> const &lhs, Vector4<T> const &rhs)
        {
            return IsEqual<T>(lhs.x, rhs.x) && IsEqual<T>(lhs.y, rhs.y) && IsEqual<T>(lhs.z, rhs.z) && IsEqual<T>(lhs.w, rhs.w);
        }
        
        template<typename T>
        bool operator!=(Vector4<T> const &lhs, Vector4<T> const &rhs)
        {
            return !(lhs == rhs);
        }

        template<typename T>
        Vector4<T> operator+(Vector4<T> const &lhs, Vector4<T> const &rhs)
        {
            return Vector4<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
        }

        template<typename T>
        Vector4<T> operator+(Vector4<T> const &lhs, T const &rhs)
        {
            return Vector4<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
        }

        template<typename T>
        Vector4<T> operator-(Vector4<T> const &lhs, Vector4<T> const &rhs)
        {
            return Vector4<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        }

        template<typename T>
        Vector4<T> operator-(Vector4<T> const &lhs, T const &rhs)
        {
            return Vector4<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
        }

        template<typename T>
        Vector4<T> operator*(Vector4<T> const &lhs, Vector4<T> const &rhs)
        {
            return Vector4<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
        }

        template<typename T>
        Vector4<T> operator*(Vector4<T> const &lhs, T const &rhs)
        {
            return Vector4<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
        }

        template<typename T>
        Vector4<T> operator/(Vector4<T> const &lhs, Vector4<T> const &rhs)
        {
            return Vector4<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
        }

        template<typename T>
        Vector4<T> operator/(Vector4<T> const &lhs, T const &rhs)
        {
            return Vector4<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
        }

        typedef Vector4<float>  Vector4f;
        typedef Vector4<double> Vector4d;

        typedef Vector4f Point4f;
        typedef Vector4d Point4d;
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