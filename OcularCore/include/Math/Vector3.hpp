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
#ifndef __H__OCULAR_MATH_VECTOR_3__H__
#define __H__OCULAR_MATH_VECTOR_3__H__

#include "Vector2.hpp"
#include "Euler.hpp"
#include "Equality.hpp"
#include "Exceptions/Exception.hpp"

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
        /**
         * \class Vector3
         */
        template<typename T>
        class Vector3
        {
        public:

            Vector3(T* values)
            {
                x = values[0];
                y = values[1];
                z = values[2];
            }

            Vector3(Quaternion const& quat)
            {

            }

            Vector3(Euler const& euler)
            {
                x = static_cast<T>(euler.getYaw());
                y = static_cast<T>(euler.getPitch());
                z = static_cast<T>(euler.getRoll());
            }

            Vector3(Vector2<T> const& vec)
            {
                x = vec.x;
                y = vec.y;
                z = 0.0f;
            }

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

                default:
                    THROW_EXCEPTION("Out-Of-Bounds Vector Access");
                    return x;
                }
            }

            Vector3<T> operator-()
            {
                return Vector3<T>(-x, -y, -z);
            }

            Vector3<T>& operator=(Vector3<T> const& rhs)
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;

                return *this;
            }

            Vector3<T>& operator+=(Vector3<T> const& rhs)
            {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;

                return *this;
            }

            Vector3<T>& operator+=(T const rhs)
            {
                x += rhs;
                y += rhs;
                z += rhs;

                return *this;
            }

            Vector3<T>& operator-=(Vector3<T> const& rhs)
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

            Vector3<T>& operator*=(Vector3<T> const& rhs)
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

            Vector3<T>& operator/=(Vector3<T> const& rhs)
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
            T getMagnitude() const
            {
                return std::sqrt((x * x) + (y * y) + (z * z));
            }

            /**
             * \return The length of the vector.
             */
            T getLength() const
            {
                return getMagnitude();
            }

            /**
             * Normalizes the vector. <br/>
             * When normalized, a vector maintains its direction but its magnitude is set to 1.0.
             *
             * \note This method modifies the internal data stored in the vector. See getNormalized if this is not desired.
             */
            void normalize()
            {
                // Normalization is simply multiplying the vector by the reciprocal of its magnitude. 

                T length = getMagnitude();

                if(IsEqual<T>(length, static_cast<T>(0)))
                {
                    x = static_cast<T>(0);
                    y = static_cast<T>(0);
                    z = static_cast<T>(0);
                }
                else
                {
                    x /= static_cast<T>(length);
                    y /= static_cast<T>(length);
                    z /= static_cast<T>(length);
                }
            }

            /**
             * Returns the normalized form of this vector
             */
            Vector3<T> getNormalized() const
            {
                Vector3<T> result(x, y, z);
                result.normalize();

                return result;
            }

            /**
             * The cross product is a third vector that is perpendicular to the two original vectors.
             *
             * \note Order is important for cross product
             *
             * \param[in] rhs The second vector to cross multiply with
             * \return The cross product of the two vectors
             */
            Vector3<T> cross(Vector3<T> const& rhs) const
            {
                return Vector3<T>((y * rhs.z) - (z * rhs.y),
                    (z * rhs.x) - (x * rhs.z),
                    (x * rhs.y) - (y * rhs.x));
            }

            /**
             * The dot product is a value equal to the magnitudes of the two vectors multiplied
             * together and then multiplied by the cosine of the angle between them.
             *
             * \param[in] rhs The second vector dot multiply with
             * \return The dot product of the two vectors (in radians)
             */
            T dot(Vector3<T> const& rhs) const
            {
                return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
            }

            /**
             * This is equivalent to taking the acos of the dot product.<br/>
             * The returned angle is the acute angle, i.e the smallest of the two angles.
             *
             * \param[in] rhs The second vector to calculate the angle with
             * \return The angle, in radians, between the vectors
             */
            double angleBetween(Vector3<T> const& rhs) const
            {
                Vector3<T> normalLHS = getNormalized();
                Vector3<T> normalRHS = rhs.getNormalized();

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
            T distanceTo(Vector3<T> const& rhs) const
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
            static Vector3<T> Lerp(Vector3<T> const from, Vector3<T> const to, T fraction)
            {
                T zero = static_cast<T>(0);
                T one = static_cast<T>(1);

                // Adapted from http://msdn.microsoft.com/en-us/library/windows/desktop/bb509618(v=vs.85).aspx
                fraction = Clamp<T>(fraction, zero, one);
                return (from * (one - fraction)) + (to * fraction);
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
            static Vector3<T> Slerp(Vector3<T> const& from, Vector3<T> const& to, double fraction)
            {
                // Adapted from http://en.wikipedia.org/wiki/Slerp

                fraction = Clamp<double>(fraction, 0.0, 1.0);
                double omega = angleBetween(from, to);

                double lhs = std::sin((1.0 - fraction) * omega) / std::sin(omega);
                double rhs = std::sin(fraction * omega) / std::sin(omega);

                return (lhs * from) + (rhs * to);
            }

            /**
             * Calculates the midpoint of the two provided points.
             *
             * \param[in] a
             * \param[in] b
             * \return The midpoint vector
             */
            static Vector3<T> Midpoint(Vector3<T> const& a, Vector3<T> const& b)
            {
                T two = static_cast<T>(2);

                return Vector3<T>(((a.x + b.x) / two),
                    ((a.y + b.y) / two),
                    ((a.z + b.z) / two));
            }

            //------------------------------------------------------------------------------
            // SPECIAL STATIC VECTORS
            //------------------------------------------------------------------------------

            // Ocular uses a right-handed coordinate system

            static Vector3<T> Identity() { return Vector3<T>(static_cast<T>( 0.0f), static_cast<T>( 0.0f), static_cast<T>( 0.0f)); }
            static Vector3<T> Up()       { return Vector3<T>(static_cast<T>( 0.0f), static_cast<T>( 1.0f), static_cast<T>( 0.0f)); }
            static Vector3<T> Down()     { return Vector3<T>(static_cast<T>( 0.0f), static_cast<T>(-1.0f), static_cast<T>( 0.0f)); }
            static Vector3<T> Left()     { return Vector3<T>(static_cast<T>(-1.0f), static_cast<T>( 0.0f), static_cast<T>( 0.0f)); }
            static Vector3<T> Right()    { return Vector3<T>(static_cast<T>( 1.0f), static_cast<T>( 0.0f), static_cast<T>( 0.0f)); }
            static Vector3<T> Forward()  { return Vector3<T>(static_cast<T>( 0.0f), static_cast<T>( 0.0f), static_cast<T>(-1.0f)); }
            static Vector3<T> Backward() { return Vector3<T>(static_cast<T>( 0.0f), static_cast<T>( 0.0f), static_cast<T>( 1.0f)); }

            //------------------------------------------------------------------------------
            // VARIABLES
            //------------------------------------------------------------------------------

            union{ T x, r, u, s; };
            union{ T y, g, v, t; };
            union{ T z, b, w; };

        protected:

        private:
        };

        //----------------------------------------------------------------------------------
        
        template<typename T>
        bool operator==(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return IsEqual<T>(lhs.x, rhs.x) && IsEqual<T>(lhs.y, rhs.y) && IsEqual<T>(lhs.z, rhs.z);
        }
        
        template<typename T>
        bool operator!=(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return !(lhs == rhs);
        }

        template<typename T>
        bool operator>(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return ((lhs.x > rhs.x) && (lhs.y > rhs.y) && (lhs.z > rhs.z));
        }

        template<typename T>
        bool operator<(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return ((lhs.x < rhs.x) && (lhs.y < rhs.y) && (lhs.z < rhs.z));
        }

        template<typename T>
        Vector3<T> operator+(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return Vector3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        template<typename T>
        Vector3<T> operator+(Vector3<T> const& lhs, T const& rhs)
        {
            return Vector3<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
        }

        template<typename T>
        Vector3<T> operator-(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return Vector3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }

        template<typename T>
        Vector3<T> operator-(Vector3<T> const& lhs, T const& rhs)
        {
            return Vector3<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
        }

        template<typename T>
        Vector3<T> operator*(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return Vector3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
        }

        template<typename T>
        Vector3<T> operator*(Vector3<T> const& lhs, T const& rhs)
        {
            return Vector3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
        }

        template<typename T>
        Vector3<T> operator/(Vector3<T> const& lhs, Vector3<T> const& rhs)
        {
            return Vector3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
        }

        template<typename T>
        Vector3<T> operator/(Vector3<T> const& lhs, T const& rhs)
        {
            return Vector3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
        }

        //--------------------------------------------
        // Common vector formats

        typedef Vector3<float> Vector3f;
        typedef Vector3<double> Vector3d;

        typedef Vector3f Point3f;
        typedef Vector3d Point3d;

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