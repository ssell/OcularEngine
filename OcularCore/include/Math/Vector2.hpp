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
#ifndef __H__OCULAR_MATH_VECTOR_2__H__
#define __H__OCULAR_MATH_VECTOR_2__H__

#include "Equality.hpp"
#include "MathCommon.hpp"

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
        * \class Vector2
        */
        template<typename T>
        class Vector2
        {
        public:

            Vector2(T const &pX, T const &pY)
            {
                x = pX;
                y = pY;
            }

            Vector2()
            {
                x = static_cast<T>(0);
                y = static_cast<T>(0);
            }

            ~Vector2()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            bool operator==(Vector2<T> const &rhs)
            {
                return IsEqual<T>(x, rhs.x) && IsEqual<T>(y, rhs.y);
            }

            bool operator!=(Vector2<T> const &rhs)
            {
                return !(*this == rhs);
            }

            Vector2<T>& operator=(Vector2<T> const &rhs)
            {
                x = rhs.x;
                y = rhs.y;

                return *this;
            }

            Vector2<T>& operator+=(Vector2<T> const &rhs)
            {
                x += rhs.x;
                y += rhs.y;

                return *this;
            }

            Vector2<T>& operator+=(T const &rhs)
            {
                x += rhs;
                y += rhs;

                return *this;
            }

            Vector2<T>& operator-=(Vector2<T> const &rhs)
            {
                x -= rhs.x;
                y -= rhs.y;

                return *this;
            }

            Vector2<T>& operator-=(T const &rhs)
            {
                x -= rhs;
                y -= rhs;

                return *this;
            }

            Vector2<T>& operator*=(Vector2<T> const &rhs)
            {
                x *= rhs.x;
                y *= rhs.y;

                return *this;
            }

            Vector2<T>& operator*=(T const &rhs)
            {
                x *= rhs;
                y *= rhs;

                return *this;
            }

            Vector2<T>& operator/=(Vector2<T> const &rhs)
            {
                x /= rhs.x;
                y /= rhs.y;

                return *this;
            }

            Vector2<T>& operator/=(T const &rhs)
            {
                x /= rhs;
                y /= rhs;

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

                return std::sqrt((dX * dX) + (dY * dY));
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
            *
            * \note This method modifies the internal data stored in the vector. See getNormalized 
            * if this is not desired.
            */
            void normalize()
            {
                // Normalization is simply multiplying the vector by the reciprocal of its magnitude. 

                double length = getMagnitude();

                if(IsEqual<T>(length, static_cast<T>(0)))
                {
                    x = static_cast<T>(0);
                    y = static_cast<T>(0);
                }
                else
                {
                    x /= static_cast<T>(length);
                    y /= static_cast<T>(length);
                }
            }

            /**
             * Returns the normalized form of this vector
             */
            Vector2<T> getNormalized() const
            {
                Vector2<T> result(x, y);
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
            T dot(Vector2<T> const &rhs)
            {
                return (x * rhs.x) + (y * rhs.y);
            }

            /**
            * This is equivalent to taking the acos of the dot product.<br/>
            * The returned angle is the acute angle, i.e the smallest of the two angles.
            *
            * \param[in] rhs The second vector to calculate the angle with
            * \return The angle, in radians, between the vectors
            */
            double angleBetween(Vector2<T> const &rhs)
            {
                Vector2<T> normalLHS = getNormalized();
                Vector2<T> normalRHS = rhs.getNormalized();

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
            double distanceTo(Vector2<T> const &rhs)
            {
                Vector2<T> distance = (*this) - rhs;
                return distance.getMagnitude();
            }

            //------------------------------------------------------------------------------
            // VARIABLES
            //------------------------------------------------------------------------------

            union { T x, u, s; };
            union { T y, v, t; };

        protected:

        private:
        };

        template<typename T>
        Vector2<T> operator+(Vector2<T> const &lhs, Vector2<T> const &rhs)
        {
            return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        template<typename T>
        Vector2<T> operator+(Vector2<T> const &lhs, T const rhs)
        {
            return Vector2<T>(lhs.x + rhs, lhs.y + rhs);
        }

        template<typename T>
        Vector2<T> operator-(Vector2<T> const &lhs, Vector2<T> const &rhs)
        {
            return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
        }

        template<typename T>
        Vector2<T> operator-(Vector2<T> const &lhs, T const &rhs)
        {
            return Vector2<T>(lhs.x - rhs, lhs.y - rhs);
        }

        template<typename T>
        Vector2<T> operator*(Vector2<T> const &lhs, Vector2<T> const &rhs)
        {
            return Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
        }

        template<typename T>
        Vector2<T> operator*(Vector2<T> const &lhs, T const &rhs)
        {
            return Vector2<T>(lhs.x * rhs, lhs.y * rhs);
        }

        template<typename T>
        Vector2<T> operator/(Vector2<T> const &lhs, Vector2<T> const &rhs)
        {
            return Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
        }

        template<typename T>
        Vector2<T> operator/(Vector2<T> const &lhs, T const &rhs)
        {
            return Vector2<T>(lhs.x / rhs, lhs.y / rhs);
        }

        //--------------------------------------------
        // Common vector formats

        typedef Vector2<float> Vector2f;
        typedef Vector2<double> Vector2d;

        typedef Vector2f Point2f;
        typedef Vector2d Point2d;

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