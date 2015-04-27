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
#ifndef __H__OCULAR_MATH_MATRIX_3X3__H__
#define __H__OCULAR_MATH_MATRIX_3X3__H__

#include "Equality.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Euler.hpp"

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
         * \class Matrix3x3
         *
         * Implementation of a generic 3x3 matrix. <br/>
         * Represented as:
         *
         * \code
         *    x.x, x.y, x.z
         *    y.x, y.y, y.z
         *    z.x, z.y, z.z
         * \endcode
         *
         * Stored internally in a single array as:
         *
         * \code
         *   {x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z}
         * \endcode
         *
         * Where
         *
         *   x = X-Axis Rotation
         *   y = Y-Axis Rotation
         *   z = Z-Axis Rotation
         */
        template<typename T>
        class Matrix3x3
        {
        public:

            /*
             * \param[in] matrix
             */
            Matrix3x3(Matrix3x3<T> const& matrix)
            {
                setIdentity();

                m_Contents[0][0]  = matrix[0][0];
                m_Contents[0][1]  = matrix[0][1];
                m_Contents[0][2]  = matrix[0][2];
                m_Contents[1][0]  = matrix[1][0];
                m_Contents[1][1]  = matrix[1][1];
                m_Contents[1][2]  = matrix[1][2];
                m_Contents[2][0]  = matrix[2][0];
                m_Contents[2][1]  = matrix[2][1];
                m_Contents[2][2]  = matrix[2][2];
            }

            /**
             * \param[in] p00 X-Axis rotation x element
             * \param[in] p01 X-Axis rotation y element
             * \param[in] p02 X-Axis rotation z element
             * \param[in] p10 Y-Axis rotation x element
             * \param[in] p11 Y-Axis rotation y element
             * \param[in] p12 Y-Axis rotation z element
             * \param[in] p20 Z-Axis rotation x element
             * \param[in] p21 Z-Axis rotation y element
             * \param[in] p22 Z-Axis rotation z element
             */
            Matrix3x3(T const &p00, T const &p01, T const &p02,
                      T const &p10, T const &p11, T const &p12,
                      T const &p20, T const &p21, T const &p22)
            {
                m_Contents[0][0] = p00;
                m_Contents[0][1] = p01;
                m_Contents[0][2] = p02;
                m_Contents[1][0] = p10;
                m_Contents[1][1] = p11;
                m_Contents[1][2] = p12;
                m_Contents[2][0] = p20;
                m_Contents[2][1] = p21;
                m_Contents[2][2] = p22;
            }

            /**
             * \param[in] row0 Row 0 contents (x-rotation)
             * \param[in] row1 Row 1 contents (y-rotation)
             * \param[in] row2 Row 2 contents (z-rotation)
             */
            Matrix3x3(Vector3<T> const &row0, Vector3<T> const &row1, Vector3<T> const &row2)
            {
                m_Contents[0][0] = row0.x;
                m_Contents[0][1] = row0.y;
                m_Contents[0][2] = row0.z;

                m_Contents[1][0] = row1.x;
                m_Contents[1][1] = row1.y;
                m_Contents[1][2] = row1.z;

                m_Contents[2][0] = row2.x;
                m_Contents[2][1] = row2.y;
                m_Contents[2][2] = row2.z;
            }

            /**
             * Initializes a 3x3 rotational matrix from a quaternion.
             * \param[in] quaternion
             */
            Matrix3x3(Quaternion const& quaternion)
            {
                // Source: 
                // Real-Time Rendering 3rd Edition 
                // 4.3.2 Quaternion Transforms
                // Page 76

                // Also:
                // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm

                Quaternion normalized = quaternion.getNormalized();

                T w = static_cast<T>(normalized.w);
                T x = static_cast<T>(normalized.x);
                T y = static_cast<T>(normalized.y);
                T z = static_cast<T>(normalized.z);

                T one = static_cast<T>(1);
                T two = static_cast<T>(2);

                m_Contents[0][0] = one - two * ((y * y) + (z * z));
                m_Contents[0][1] =       two * ((x * y) + (w * z));
                m_Contents[0][2] =       two * ((x * z) - (w * y));

                m_Contents[1][0] =       two * ((x * y) - (w * z));
                m_Contents[1][1] = one - two * ((x * x) + (z * z));
                m_Contents[1][2] =       two * ((y * z) + (w * x));

                m_Contents[2][0] =       two * ((x * z) + (w * y));
                m_Contents[2][1] =       two * ((y * z) - (w * x));
                m_Contents[2][2] = one - two * ((x * x) + (y * y));
            }

            /**
             * Initializes a 3x3 rotational matrix from a Euler angles.
             * \param[in] euler
             */
            Matrix3x3(Euler const& euler)
            {
                // Source: 
                // Real-Time Rendering 3rd Edition 
                // 4.2.2 Extracting Parameters from the Euler Transform
                // Page 68

                // Also:
                // http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToMatrix/index.htm

                // We directly access the internal contents as getYaw, etc. return in degrees and we want radians.

                float y = euler.m_Yaw;
                float p = euler.m_Pitch;
                float r = euler.m_Roll;

                float cosy = std::cos(y);
                float siny = std::sin(y);
                float cosp = std::cos(p);
                float sinp = std::sin(p);
                float cosr = std::cos(r);
                float sinr = std::sin(r);

                m_Contents[0][0] = (cosr * cosy) - (sinr * sinp * siny);
                m_Contents[0][1] = -sinr * cosp;
                m_Contents[0][2] = (cosr * siny) + (sinr * sinp * cosy);

                m_Contents[1][0] = (sinr * cosy) + (cosr * sinp * siny);
                m_Contents[1][1] = cosr * cosp;
                m_Contents[1][2] = (sinr * siny) - (cosr * sinp * cosy);

                m_Contents[2][0] = -cosp * siny;
                m_Contents[2][1] = sinp;
                m_Contents[2][2] = cosp * cosy;
            }

            /**
             * Initializes to the Identity matrix
             */
            Matrix3x3()
            {
                setIdentity();
            }

            ~Matrix3x3()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            /**
             * Returns the Vector3<T> row of the given index. This can be accessed like:
             * 
             *     matrix[row][col] = 5.0f;
             *     float value = matrix[row][col];
             *
             * \param[in] index Valid row index [0,2]
             */
            Vector3<T>& operator[](unsigned const &index)
            {
                if(index > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Contents[index];
            }

            /**
             * Returns the Vector3<T> row of the given index. This can be accessed like:
             * 
             *     matrix[row][col] = 5.0f;
             *     float value = matrix[row][col];
             *
             * \param[in] index Valid row index [0,2]
             */
            Vector3<T> operator[](unsigned const& index) const
            {
                if(index > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Contents[index];
            }

            Matrix3x3<T>& operator=(Matrix3x3<T> const &rhs)
            {
                for(unsigned row = 0; row < 3; row++)
                {
                    for(unsigned col = 0; col < 3; col++)
                    {
                        m_Contents[row][col] = rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix3x3<T>& operator+=(Matrix3x3<T> const &rhs)
            {
                for(unsigned row = 0; row < 3; row++)
                {
                    for(unsigned col = 0; col < 3; col++)
                    {
                        m_Contents[row][col] += rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix3x3<T>& operator-=(Matrix3x3<T> const &rhs)
            {
                for(unsigned row = 0; row < 3; row++)
                {
                    for(unsigned col = 0; col < 3; col++)
                    {
                        m_Contents[row][col] -= rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix3x3<T>& operator*=(Matrix3x3<T> const &rhs)
            {
                Matrix3x3<T> oldContents = (*this);

                m_Contents[0][0] = oldContents[0][0] * rhs[0][0] + oldContents[1][0] * rhs[0][1] + oldContents[2][0] * rhs[0][2];
			    m_Contents[1][0] = oldContents[0][0] * rhs[1][0] + oldContents[1][0] * rhs[1][1] + oldContents[2][0] * rhs[1][2];
			    m_Contents[2][0] = oldContents[0][0] * rhs[2][0] + oldContents[1][0] * rhs[2][1] + oldContents[2][0] * rhs[2][2];

			    m_Contents[0][1] = oldContents[0][1] * rhs[0][0] + oldContents[1][1] * rhs[0][1] + oldContents[2][1] * rhs[0][2];
			    m_Contents[1][1] = oldContents[0][1] * rhs[1][0] + oldContents[1][1] * rhs[1][1] + oldContents[2][1] * rhs[1][2];
			    m_Contents[2][1] = oldContents[0][1] * rhs[2][0] + oldContents[1][1] * rhs[2][1] + oldContents[2][1] * rhs[2][2];

			    m_Contents[0][2] = oldContents[0][2] * rhs[0][0] + oldContents[1][2] * rhs[0][1] + oldContents[2][2] * rhs[0][2];
			    m_Contents[1][2] = oldContents[0][2] * rhs[1][0] + oldContents[1][2] * rhs[1][1] + oldContents[2][2] * rhs[1][2];
			    m_Contents[2][2] = oldContents[0][2] * rhs[2][0] + oldContents[1][2] * rhs[2][1] + oldContents[2][2] * rhs[2][2];

                return (*this);
            }

            Matrix3x3<T>& operator*=(T const &rhs)
            {
                for(unsigned row = 0; row < 3; row++)
                {
                    for(unsigned col = 0; col < 3; col++)
                    {
                        m_Contents[row][col] *= rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix3x3<T>& operator*=(Vector3<T> const &rhs)
            {
                for(unsigned i = 0; i < 3; i++)
                {
                    m_Contents[i][0] *= rhs.x;
                    m_Contents[i][1] *= rhs.y;
                    m_Contents[i][2] *= rhs.z;
                }

                return (*this);
            }

            //------------------------------------------------------------------------------
            // GETTERS
            //------------------------------------------------------------------------------

            /**
             * \return The X-Axis rotation vector
             */
            Vector3<T> getXRotation() const
            {
                return Vector3<T>(m_Contents[0][0], m_Contents[0][1], m_Contents[0][2]);
            }

            /**
             * \return The Y-Axis rotation vector
             */
            Vector3<T> getYRotation() const
            {
                return Vector3<T>(m_Contents[1][0], m_Contents[1][1], m_Contents[1][2]);
            }

            /**
             * \return The Z-Axis rotation vector
             */
            Vector3<T> getZRotation() const
            {
                return Vector3<T>(m_Contents[2][0], m_Contents[2][1], m_Contents[2][2]);
            }

            /**
             * \return The element at the specified index [0-8]
             */
            T getElement(unsigned const index) const
            {
                if(index > 8)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Index Access");
                }

                return m_Contents[(index / 3)][(index % 3)];
            }

            //------------------------------------------------------------------------------
            // SETTERS
            //------------------------------------------------------------------------------

            /**
             * Sets matrix as the identity matrix.
             */
            void setIdentity()
            {
                // X-Axis Rotation
                m_Contents[0][0] = static_cast<T>(1);
                m_Contents[0][1] = static_cast<T>(0);
                m_Contents[0][2] = static_cast<T>(0);

                // Y-Axis Rotation
                m_Contents[1][0] = static_cast<T>(0);
                m_Contents[1][1] = static_cast<T>(1);
                m_Contents[1][2] = static_cast<T>(0);

                // Z-Axis Rotation
                m_Contents[2][0] = static_cast<T>(0);
                m_Contents[2][1] = static_cast<T>(0);
                m_Contents[2][2] = static_cast<T>(1);
            }

            /**
             * Sets the X-Axis rotation vector.
             *
             * \param[in] x X component of the rotation vector
             * \param[in] y Y component of the rotation vector
             * \param[in] z Z component of the rotation vector
             */
            void setXRotation(T const &x, T const &y, T const &z)
            {
                m_Contents[0][0] = x;
                m_Contents[0][1] = y;
                m_Contents[0][2] = z;
            }

            /**
             * Sets the X-Axis rotation vector.
             *
             * \param[in] vec The X-Axis rotation vector
             */
            void setXRotation(Vector3<T> const &vec)
            {
                m_Contents[0][0] = vec.x;
                m_Contents[0][1] = vec.y;
                m_Contents[0][2] = vec.z;
            }

            /**
             * Sets the Y-Axis rotation vector.
             *
             * \param[in] x X component of the rotation vector
             * \param[in] y Y component of the rotation vector
             * \param[in] z Z component of the rotation vector
             */
            void setYRotation(T const &x, T const &y, T const &z)
            {
                m_Contents[1][0] = x;
                m_Contents[1][1] = y;
                m_Contents[1][2] = z;
            }

            /**
             * Sets the Y-Axis rotation vector.
             *
             * \param[in] vec The Y-Axis rotation vector
             */
            void setYRotation(Vector3<T> const &vec)
            {
                m_Contents[1][0] = vec.x;
                m_Contents[1][1] = vec.y;
                m_Contents[1][2] = vec.z;
            }

            /**
             * Sets the Z-Axis rotation vector.
             *
             * \param[in] x X component of the rotation vector
             * \param[in] y Y component of the rotation vector
             * \param[in] z Z component of the rotation vector
             */
            void setZRotation(T const &x, T const &y, T const &z)
            {
                m_Contents[2][0] = x;
                m_Contents[2][1] = y;
                m_Contents[2][2] = z;
            }

            /**
             * Sets the Z-Axis rotation vector.
             *
             * \param[in] vec The Z-Axis rotation vector
             */
            void setZRotation(Vector3<T> const &vec)
            {
                m_Contents[2][0] = vec.x;
                m_Contents[2][1] = vec.y;
                m_Contents[2][2] = vec.z;
            }
            
            /**
             * Sets the value of the element at the specified row/column position.
             *
             * \param[in] row    Row of the element [0,2]
             * \param[in] column Column of the element [0,2]
             * \param[in] value  Value to set
             */
            void setElement(unsigned const &row, unsigned const &column, T const &value)
            {
                if(row > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Row Access");
                }

                if(column > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Column Access");
                }

                m_Contents[row][column] = value;
            }

            /**
             * Sets the value of the element at the specified index.
             *
             * \param[in] index Index of the element [0,8]
             * \param[in] value Value to set
             */
            void setElement(unsigned const &index, T const &value)
            {
                if(index > 8)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Index Access");
                }

                m_Contents[(index / 3)][(index % 3)] = value;
            }

            //------------------------------------------------------------------------------
            // CONVERSIONS
            //------------------------------------------------------------------------------

            /**
             * Converts this rotation matrix to a quaternion.
             * \return The converted quaternion.
             */
            Quaternion toQuaternion() const 
            {
                return Quaternion(*this);
            }
            
            /**
             * Converts this rotation matrix to Euler angles.
             * \return The converted Euler angles.
             */
            Euler toEuler() const 
            {
                return Euler(*this);
            }

            //------------------------------------------------------------------------------
            // OPERATIONS
            //------------------------------------------------------------------------------

            /**
             * Calculates and returns the determinant of the matrix.
             */
            T getDeterminant() const
            {
                return (  m_Contents[0][0] * (m_Contents[1][1] * m_Contents[2][2] - m_Contents[1][2] * m_Contents[2][1])
                        - m_Contents[0][1] * (m_Contents[1][0] * m_Contents[2][2] - m_Contents[1][2] * m_Contents[2][0])
                        + m_Contents[0][2] * (m_Contents[1][0] * m_Contents[2][1] - m_Contents[1][1] * m_Contents[2][0]));
            }

            /**
             * Returns true if the matrix is a special reflection matrix.
             *
             * A reflection matrix must be handled carefully as it can cause
             * issues such as reverse vertex orders which can lead to incorrect
             * lighting and backface culling.
             */
            bool isReflective() const
            {
                return (getDeterminant() < 0.0f);
            }

            /**
             * Creates and returns the inverse of this matrix.
             * \note This method can throw an exception if the determinant is zero.
             */
            Matrix3x3<T> getInverse() const
            {
                Matrix3x3<T> result;

                T determinant = getDeterminant();

                if(!IsZero<T>(determinant))
                {
                    T oneOverDeterminant = static_cast<T>(1) / determinant;

                    result[0][0] =  (m_Contents[1][1] * m_Contents[2][2] - m_Contents[1][2] * m_Contents[2][1]) * oneOverDeterminant;
                    result[0][1] = -(m_Contents[0][1] * m_Contents[2][2] - m_Contents[0][2] * m_Contents[2][1]) * oneOverDeterminant;
                    result[0][2] =  (m_Contents[0][1] * m_Contents[1][2] - m_Contents[0][2] * m_Contents[1][1]) * oneOverDeterminant;

                    result[1][0] = -(m_Contents[1][0] * m_Contents[2][2] - m_Contents[1][2] * m_Contents[2][0]) * oneOverDeterminant;
                    result[1][1] =  (m_Contents[0][0] * m_Contents[2][2] - m_Contents[0][2] * m_Contents[2][0]) * oneOverDeterminant;
                    result[1][2] = -(m_Contents[0][0] * m_Contents[1][2] - m_Contents[0][2] * m_Contents[1][0]) * oneOverDeterminant;

                    result[2][0] =  (m_Contents[1][0] * m_Contents[2][1] - m_Contents[1][1] * m_Contents[2][0]) * oneOverDeterminant;
                    result[2][1] = -(m_Contents[0][0] * m_Contents[2][1] - m_Contents[0][1] * m_Contents[2][0]) * oneOverDeterminant;
                    result[2][2] =  (m_Contents[0][0] * m_Contents[1][1] - m_Contents[0][1] * m_Contents[1][0]) * oneOverDeterminant;
                }
                else
                {
                    THROW_EXCEPTION("Caught Divide By Zero (Determinant during Inverse)");
                }

                return result;
            }

            /**
             * Creates and returns the transpose of this matrix.
             *
             * \return The transpose matrix
             */
            Matrix3x3<T> getTranspose() const
            {
                Matrix3x3<T> result;

                result[0][0] = m_Contents[0][0];
                result[0][1] = m_Contents[1][0];
                result[0][2] = m_Contents[2][0];

                result[1][0] = m_Contents[0][1];
                result[1][1] = m_Contents[1][1];
                result[1][2] = m_Contents[2][1];

                result[2][0] = m_Contents[0][2];
                result[2][1] = m_Contents[1][2];
                result[2][2] = m_Contents[2][2];

                return result;
            }

            //------------------------------------------------------------------------------
            // STATIC OPERATIONS
            //------------------------------------------------------------------------------

            /**
             * Creates a matrix which scales by the specified amount.
             * \param[in] scale
             */
            static Matrix3x3<T> createScalingMatrix(T const& scale)
            {
                Matrix3x3<T> result;
                
                result[0][0] = scale;
                result[1][1] = scale;
                result[2][2] = scale;

                return result;
            }

            /**
             * Creates a matrix which scales by the specified amount.
             * \param[in] scale
             */
            static Matrix3x3<T> createScalingMatrix(Vector3<T> const& scale)
            {
                Matrix3x3<T> result;
                
                result[0][0] = scale.x;
                result[1][1] = scale.y;
                result[2][2] = scale,z;

                return result;
            }

        protected:

        private:

            Vector3<T> m_Contents[3];
        };

        //----------------------------------------------------------------------------------
        
        template<typename T>
        bool operator==(Matrix3x3<T> const &lhs, Matrix3x3<T> const &rhs)
        {
            return IsEqual<T>(lhs[0][0], rhs[0][0]) && IsEqual<T>(lhs[0][1], rhs[0][1]) &&
                   IsEqual<T>(lhs[0][2], rhs[0][2]) && IsEqual<T>(lhs[1][0], rhs[1][0]) &&
                   IsEqual<T>(lhs[1][1], rhs[1][1]) && IsEqual<T>(lhs[1][2], rhs[1][2]) &&
                   IsEqual<T>(lhs[2][0], rhs[2][0]) && IsEqual<T>(lhs[2][1], rhs[2][1]) &&
                   IsEqual<T>(lhs[2][2], rhs[2][2]);
        }
        
        template<typename T>
        bool operator!=(Matrix3x3<T> const &lhs, Matrix3x3<T> const &rhs)
        {
            return !(lhs == rhs);
        }

        template<typename T>
        Matrix3x3<T> operator+(Matrix3x3<T> const &lhs, Matrix3x3<T> const &rhs)
        {
            Matrix3x3<T> result(lhs[0][0] + rhs[0][0], lhs[0][1] + rhs[0][1],
                                lhs[0][2] + rhs[0][2], lhs[1][0] + rhs[1][0],
                                lhs[1][1] + rhs[1][1], lhs[1][2] + rhs[1][2],
                                lhs[2][0] + rhs[2][0], lhs[2][1] + rhs[2][1],
                                lhs[2][2] + rhs[2][2]);

            return result;
        }

        template<typename T>
        Matrix3x3<T> operator-(Matrix3x3<T> const &lhs, Matrix3x3<T> const &rhs)
        {
            Matrix3x3<T> result(lhs[0][0] - rhs[0][0], lhs[0][1] - rhs[0][1],
                                lhs[0][2] - rhs[0][2], lhs[1][0] - rhs[1][0],
                                lhs[1][1] - rhs[1][1], lhs[1][2] - rhs[1][2],
                                lhs[2][0] - rhs[2][0], lhs[2][1] - rhs[2][1],
                                lhs[2][2] - rhs[2][2]);

            return result;
        }

        template<typename T>
        Matrix3x3<T> operator*(Matrix3x3<T> const &lhs, Matrix3x3<T> const &rhs)
        {
            Matrix3x3<T> result;

            result[0][0] = (lhs[0][0] * rhs[0][0]) + (lhs[0][1] * rhs[1][0]) + (lhs[0][2] * rhs[2][0]);
            result[0][1] = (lhs[0][0] * rhs[0][1]) + (lhs[0][1] * rhs[1][1]) + (lhs[0][2] * rhs[2][1]);
            result[0][2] = (lhs[0][0] * rhs[0][2]) + (lhs[0][1] * rhs[1][2]) + (lhs[0][2] * rhs[2][2]);

            result[1][0] = (lhs[1][0] * rhs[0][0]) + (lhs[1][1] * rhs[1][0]) + (lhs[1][2] * rhs[2][0]);
            result[1][1] = (lhs[1][0] * rhs[0][1]) + (lhs[1][1] * rhs[1][1]) + (lhs[1][2] * rhs[2][1]);
            result[1][2] = (lhs[1][0] * rhs[0][2]) + (lhs[1][1] * rhs[1][2]) + (lhs[1][2] * rhs[2][2]);

            result[2][0] = (lhs[2][0] * rhs[0][0]) + (lhs[2][1] * rhs[1][0]) + (lhs[2][2] * rhs[2][0]);
            result[2][1] = (lhs[2][0] * rhs[0][1]) + (lhs[2][1] * rhs[1][1]) + (lhs[2][2] * rhs[2][1]);
            result[2][2] = (lhs[2][0] * rhs[0][2]) + (lhs[2][1] * rhs[1][2]) + (lhs[2][2] * rhs[2][2]);

            return result;
        }

        template<typename T>
        Matrix3x3<T> operator*(Matrix3x3<T> const &lhs, T const &rhs)
        {
            Matrix3x3<T> result;

            for(unsigned row = 0; row < 3; row++)
            {
                for(unsigned col = 0; col < 3; col++)
                {
                    result[row][col] = lhs[row][col] * rhs;
                }
            }

            return result;
        }

        template<typename T>
        Matrix3x3<T> operator*(Matrix3x3<T> const &lhs, Vector3<T> const &rhs)
        {
            Matrix3x3<T> result;

            for(unsigned i = 0; i < 2; i++)
            {
                result[i][0] = lhs[i][0] * rhs.x;
                result[i][1] = lhs[i][1] * rhs.y;
                result[i][2] = lhs[i][2] * rhs.z;
            }

            return result;
        }

        //--------------------------------------------
        // Common matrix formats

        typedef Matrix3x3<float> Matrix3x3f;
        typedef Matrix3x3<double> Matrix3x3d;

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