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
#ifndef __H__OCULAR_MATH_VECTOR_3__H__
#define __H__OCULAR_MATH_VECTOR_3__H__

#include "Exception.hpp"
#include "Common.hpp"
#include <cmath>

//------------------------------------------------------------------------------------------

/**
* \addtogroup Ocular
* @{
*/
namespace Ocular
{
    /**
    * \addtogroup Core
    * @{
    */
    namespace Core
    {
        /**
        * \class Vector3
        */
        template<typename T>
        class Vector3
        {
        public:

            Vector3(T const x, T const y, T const z)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }

            Vector3()
            {
                this->x = static_cast<T>(0);
                this->y = static_cast<T>(0);
                this->z = static_cast<T>(0);
            }

            ~Vector3()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            bool operator==(Vector3<T> const rhs)
            {
                // TODO : need smart compare for floating point
                return (m_Content.x == rhs.x) && (m_Content.y == rhs.y) && (m_Content.z == rhs.z);
            }

            bool operator!=(Vector3<T> const rhs)
            {
                return !(*this == rhs);
            }

            Vector3<T>& operator=(Vector3<T> const rhs)
            {
                m_Content.x = rhs.x;
                m_Content.y = rhs.y;
                m_Content.z = rhs.z;

                return *this;
            }

            Vector3<T>& operator+(Vector3<T> const rhs)
            {
                return Vector3<T>(m_Content.x + rhs.x, m_Content.y + rhs.y, m_Content.z + rhs.z);
            }

            Vector3<T>& operator+(T const rhs)
            {
                return Vector3<T>(m_Content.x + rhs, m_Content.y + rhs, m_Content.z + rhs);
            }

            Vector3<T>& operator+=(Vector3<T> const rhs)
            {
                m_Content.x += rhs.x;
                m_Content.y += rhs.y;
                m_Content.z += rhs.z;

                return *this;
            }

            Vector3<T>& operator+=(T const rhs)
            {
                m_Content.x += rhs;
                m_Content.y += rhs;
                m_Content.z += rhs;

                return *this;
            }

            Vector3<T>& operator-(Vector3<T> const rhs)
            {
                return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
            }

            Vector3<T>& operator-(T const rhs)
            {
                return Vector3<T>(x - rhs, y - rhs, z - rhs);
            }

            Vector3<T>& operator-=(Vector3<T> const rhs)
            {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;

                return *this;
            }

            Vector3<T>& operator-=(T const rhs)
            {
                x -= rhs;
                y -= rhs;
                z -= rhs;

                return *this;
            }

            Vector3<T>& operator*(Vector3<T> const rhs)
            {
                return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
            }

            Vector3<T>& operator*(T const rhs)
            {
                return Vector3<T>(x * rhs, y * rhs, z * rhs);
            }

            Vector3<T>& operator*=(Vector3<T> const rhs)
            {
                x *= rhs.x;
                y *= rhs.y;
                z *= rhs.z;

                return *this;
            }

            Vector3<T>& operator*=(T const rhs)
            {
                x *= rhs;
                y *= rhs;
                z *= rhs;

                return *this;
            }

            Vector3<T>& operator/(Vector3<T> const rhs)
            {
                return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
            }

            Vector3<T>& operator/(T const rhs)
            {
                return Vector3<T>(x / rhs, y / rhs, z / rhs);
            }

            Vector3<T>& operator/=(Vector3<T> const rhs)
            {
                x /= rhs.x;
                y /= rhs.y;
                z /= rhs.z;

                return *this;
            }

            Vector3<T>& operator/=(T const rhs)
            {
                x /= rhs;
                y /= rhs;
                z /= rhs;

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

                return std::sqrt((dX * dX) + (dY * dY) + (dZ * dZ));
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
                    return Vector3<T>(static_cast<T>(0),
                                      static_cast<T>(0),
                                      static_cast<T>(0));
                }
                else
                {
                    return Vector3<T>(vec.x / static_cast<T>(length),
                                      vec.y / static_cast<T>(length),
                                      vec.z / static_cast<T>(length));
                }
            }

            /**
             * Maintains the direction of the provided vector but clamps its magnitude (length).
             *
             * \param[in] lower The lower bounds to clamp to
             * \param[in] upper The upper bounds to clamp to
             */
            void clampMagnitude(T const lower, T const upper)
            {
                return Vector3<T>(((vec.x > upper) ? upper : (vec.x < lower) ? lower : vec.x),
                                  ((vec.y > upper) ? upper : (vec.y < lower) ? lower : vec.y),
                                  ((vec.z > upper) ? upper : (vec.z < lower) ? lower : vec.z));
            }

            /**
		     * The cross product is a third vector that is perpendicular to the two original vectors.
             *
             * \param[in] rhs The second vector to cross multiply with
             * \return The cross product of the two vectors
             */
            Vector3<T> cross(Vector3<T> const rhs)
            {
                return Vector3<T>((lhs.y * rhs.z) - (lhs.z * rhs.y),
                                  (lhs.z * rhs.x) - (lhs.x * rhs.z),
                                  (lhs.x * rhs.y) - (lhs.y * rhs.x));
            }

            /**
		     * The dot product is a value equal to the magnitudes of the two vectors multiplied 
		     * together and then multiplied by the cosine of the angle between them.
             *
		     * \param[in] rhs The second vector dot multiply with
             * \return The dot product of the two vectors (in radians)
             */
            double dot(Vector3<T> const rhs)
            {
                return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
            }

            /**
             * This is equivalent to taking the acos of the dot product.<br/>
		     * The returned angle is the acute angle, i.e the smallest of the two angles.
             *
             * \param[in] rhs The second vector to calculate the angle with
             * \return The angle, in radians, between the vectors
             */
            double angleBetween(Vector3<T> const rhs)
            {
                double angle = std::acos(dot(lhs, rhs));

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
            double distanceTo(Vector3<T> const rhs)
            {
                Vector3<T> distance = (*this) - rhs;
                return distance.getMagnitude();
            }

            /**
            * Linearly interpolates the two vectors using the specified fraction.<br/><br/>
            *
            * When <code>fraction == 0</code>, the return is equal to <code>from</code>.
		    * When <code>fraction == 1</code>, the return is equal to <code>to</code>.
            *
            * \param[in] from     The 'start' vector.
            * \param[in] to       The 'end' vector.
            * \param[in] fraction The fraction to interpolate by.
            * \return The resultant interpolated vector.
            */
            static Vector3<T> lerp(Vector3<T> const from, Vector3<T> const to, double fraction)
            {
                // Adapted from http://msdn.microsoft.com/en-us/library/windows/desktop/bb509618(v=vs.85).aspx
                fraction = Clamp<double>(fraction, 0.0, 1.0);
                return (from * (1.0 - fraction)) + (to * fraction);
            }

            /**
            * Spherically interpolates the two vectors using the specified fraction.<br/><br/>
            *
            * When slerping, the vectors are treated as directions as opposed to points
		    * in space (as in lerp). The resultant direction is interpolated by the angle
		    * between the vectors, and the magnitude is interpolated by those of the
		    * two input vectors.
            *
            * \param[in] from     The 'start' vector.
            * \param[in] to       The 'end' vector.
            * \param[in] fraction The fraction to interpolate by.
            * \return The resultant interpolated vector.
            */
            static Vector3<T> slerp(Vector3<T> const from, Vector3<T> const to, double fraction)
            {
                // Adapted from http://en.wikipedia.org/wiki/Slerp

                fraction = Clamp<double>(fraction, 0.0, 1.0);
                double omega = angleBetween(from, to);

                double lhs = std::sin((1.0 - fraction) * omega) / std::sin(omega);
                double rhs = std::sin(fraction * omega) / std::sin(omega);

                return (lhs * from) + (rhs * to);
            }

            //------------------------------------------------------------------------------
            // VARIABLES
            //------------------------------------------------------------------------------

            union{ T x, r; };
            union{ T y, g; };
            union{ T z, b; };

        protected:

        private:
        };

        // Common vector formats
        typedef Vector3<float> Vector3f;
        typedef Vector3<double> Vector3d;

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