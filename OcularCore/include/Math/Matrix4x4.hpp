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
#ifndef __H__OCULAR_MATH_MATRIX_4X4__H__
#define __H__OCULAR_MATH_MATRIX_4X4__H__

#include "Exceptions/Exception.hpp"
#include "Matrix3x3.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
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
         * \class Matrix4x4
         *
         * Implementation of a generic 4x4 matrix. <br/>
         * Represented as:
         *
         * \code
         *    x.x, x.y, x.z, 0
         *    y.x, y.y, y.z, 0
         *    z.x, z.y, z.z, 0
         *    p.x, p.y, p.z, 1  
         * \endcode
         *
         * Stored internally in a single array as:
         *
         * \code
         *   {x.x, x.y, x.z, 0, y.x, y.y, y.z, 0, z.x, z.y, z.z, 0, p.x, p.y, p.z, 1}
         * \endcode
         *
         * Where 
         *
         *   x = X-Axis Rotation 
         *   y = Y-Axis Rotation
         *   z = Z-Axis Rotation
         *   p = Position Vector
         */
        template<typename T>
        class Matrix4x4
        {
        public:

            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            /**
             * \param[in] p00 X-Axis rotation x element
             * \param[in] p01 X-Axis rotation y element
             * \param[in] p02 X-Axis rotation z element
             * \param[in] p03 X-Axis rotation w element (should be 0)
             * \param[in] p10 Y-Axis rotation x element
             * \param[in] p11 Y-Axis rotation y element
             * \param[in] p12 Y-Axis rotation z element
             * \param[in] p13 Y-Axis rotation w element (should be 0)
             * \param[in] p20 Z-Axis rotation x element
             * \param[in] p21 Z-Axis rotation y element
             * \param[in] p22 Z-Axis rotation z element
             * \param[in] p23 Z-Axis rotation w element (should be 0)
             * \param[in] p30 Position vector x element
             * \param[in] p31 Position vector y element
             * \param[in] p32 Position vector z element
             * \param[in] p33 Position vector w element (should be 0)
             */
            Matrix4x4(T const &p00, T const &p01, T const &p02, T const &p03,
                      T const &p10, T const &p11, T const &p12, T const &p13,
                      T const &p20, T const &p21, T const &p22, T const &p23,
                      T const &p30, T const &p31, T const &p32, T const &p33)
            {
                // X-Axis Rotation
                m_Contents[0][0] = p00;
                m_Contents[0][1] = p01;
                m_Contents[0][2] = p02;
                m_Contents[0][3] = p03;

                // Y-Axis Rotation
                m_Contents[1][0] = p10;
                m_Contents[1][1] = p11;
                m_Contents[1][2] = p12;
                m_Contents[1][3] = p13;

                // Z-Axis Rotation
                m_Contents[2][0] = p20;
                m_Contents[2][1] = p21;
                m_Contents[2][2] = p22;
                m_Contents[2][3] = p23;

                // Position
                m_Contents[3][0] = p30;
                m_Contents[3][1] = p31;
                m_Contents[3][2] = p32;
                m_Contents[3][3] = p33;
            }

            /**
             * \param[in] matrix
             */
            Matrix4x4(Matrix4x4<T> const& matrix)
            {
                m_Contents[0][0] = matrix[0][0];
                m_Contents[0][1] = matrix[0][1];
                m_Contents[0][2] = matrix[0][2];
                m_Contents[0][3] = matrix[0][3];
                m_Contents[1][0] = matrix[1][0];
                m_Contents[1][1] = matrix[1][1];
                m_Contents[1][2] = matrix[1][2];
                m_Contents[1][3] = matrix[1][3];
                m_Contents[2][0] = matrix[2][0];
                m_Contents[2][1] = matrix[2][1];
                m_Contents[2][2] = matrix[2][2];
                m_Contents[2][3] = matrix[2][3];
                m_Contents[3][0] = matrix[3][0];
                m_Contents[3][1] = matrix[3][1];
                m_Contents[3][2] = matrix[3][2];
                m_Contents[3][3] = matrix[3][3];
            }

            /*
             * \param[in] matrix
             */
            Matrix4x4(Matrix3x3<T> const& matrix)
            {
                setIdentity();

                m_Contents[0][0] = matrix[0][0];
                m_Contents[0][1] = matrix[0][1];
                m_Contents[0][2] = matrix[0][2];
                m_Contents[0][3] = matrix[0][3];
                m_Contents[1][0] = matrix[1][0];
                m_Contents[1][1] = matrix[1][1];
                m_Contents[1][2] = matrix[1][2];
                m_Contents[1][3] = matrix[1][3];
                m_Contents[2][0] = matrix[2][0];
            }

            /**
             * \param[in] row0 Row 0 contents (x-rotation)
             * \param[in] row1 Row 1 contents (y-rotation)
             * \param[in] row2 Row 2 contents (z-rotation)
             * \param[in] row3 Row 3 contents (position)
             */
            Matrix4x4(Vector4<T> const &row0, Vector4<T> const &row1, Vector4<T> const &row2, Vector4<T> const &row3)
            {
                m_Contents[0][0] = row0.x;
                m_Contents[0][1] = row0.y;
                m_Contents[0][2] = row0.z;
                m_Contents[0][3] = row0.w;

                m_Contents[1][0] = row1.x;
                m_Contents[1][1] = row1.y;
                m_Contents[1][2] = row1.z;
                m_Contents[1][3] = row1.w;

                m_Contents[2][0] = row2.x;
                m_Contents[2][1] = row2.y;
                m_Contents[2][2] = row2.z;
                m_Contents[2][3] = row2.w;

                m_Contents[3][0] = row3.x;
                m_Contents[3][1] = row3.y;
                m_Contents[3][2] = row3.z;
                m_Contents[3][3] = row3.w;
            }

            /**
             * Initializes to the Identity matrix
             */
            Matrix4x4()
            {
                setIdentity();
            }

            ~Matrix4x4()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            /**
             * Returns the Vector4<T> row of the given index. This can be accessed like:
             * 
             *     matrix[row][col] = 5.0f;
             *     float value = matrix[row][col];
             *
             * \param[in] index Valid row index [0,3]
             */
            Vector4<T>& operator[](unsigned const &index)
            {
                if(index > 3)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Contents[index];
            }

            /**
             * Returns the Vector4<T> row of the given index. This can be accessed like:
             * 
             *     matrix[row][col] = 5.0f;
             *     float value = matrix[row][col];
             *
             * \param[in] index Valid row index [0,3]
             */
            Vector4<T> operator[](unsigned const &index) const
            {
                if(index > 3)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Contents[index];
            }

            Matrix4x4<T>& operator=(Matrix4x4<T> const &rhs)
            {
                for(unsigned row = 0; row < 4; row++)
                {
                    for(unsigned col = 0; col < 4; col++)
                    {
                        m_Contents[row][col] = rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix4x4<T>& operator+=(Matrix4x4<T> const &rhs)
            {
                for(unsigned row = 0; row < 4; row++)
                {
                    for(unsigned col = 0; col < 4; col++)
                    {
                        m_Contents[row][col] += rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix4x4<T>& operator-=(Matrix4x4<T> const &rhs)
            {
                for(unsigned row = 0; row < 4; row++)
                {
                    for(unsigned col = 0; col < 4; col++)
                    {
                        m_Contents[row][col] -= rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix4x4<T>& operator*=(Matrix4x4<T> const &rhs)
            {
                Matrix4x4<T> oldContents = (*this);

                m_Contents[0][0] = (oldContents[0][0] * rhs[0][0])  + (oldContents[1][0] * rhs[0][1])  + (oldContents[2][0] * rhs[0][2])  + (oldContents[3][0] * rhs[0][3]);
                m_Contents[1][0] = (oldContents[0][0] * rhs[1][0])  + (oldContents[1][0] * rhs[1][1])  + (oldContents[2][0] * rhs[1][2])  + (oldContents[3][0] * rhs[1][3]);
                m_Contents[2][0] = (oldContents[0][0] * rhs[2][0])  + (oldContents[1][0] * rhs[2][1])  + (oldContents[2][0] * rhs[2][2]) + (oldContents[3][0] * rhs[2][3]);
                m_Contents[3][0] = (oldContents[0][0] * rhs[3][0]) + (oldContents[1][0] * rhs[3][1]) + (oldContents[2][0] * rhs[3][2]) + (oldContents[3][0] * rhs[3][3]);
                
                m_Contents[0][1] = (oldContents[0][1] * rhs[0][0]) + (oldContents[1][1] * rhs[0][1])  + (oldContents[2][1] * rhs[0][2])  + (oldContents[3][1] * rhs[0][3]);
                m_Contents[1][1] = (oldContents[0][1] * rhs[1][0]) + (oldContents[1][1] * rhs[1][1])  + (oldContents[2][1] * rhs[1][2])  + (oldContents[3][1] * rhs[1][3]);
                m_Contents[2][1] = (oldContents[0][1] * rhs[2][0]) + (oldContents[1][1] * rhs[2][1])  + (oldContents[2][1] * rhs[2][2]) + (oldContents[3][1] * rhs[2][3]);
                m_Contents[3][1] = (oldContents[0][1] * rhs[3][0]) + (oldContents[1][1] * rhs[3][1]) + (oldContents[2][1] * rhs[3][2]) + (oldContents[3][1] * rhs[3][3]);
                
                m_Contents[0][2] = (oldContents[0][2] * rhs[0][0]) + (oldContents[1][2] * rhs[0][1])  + (oldContents[2][2] * rhs[0][2])  + (oldContents[3][2] * rhs[0][3]);
                m_Contents[1][2] = (oldContents[0][2] * rhs[1][0]) + (oldContents[1][2] * rhs[1][1])  + (oldContents[2][2] * rhs[1][2])  + (oldContents[3][2] * rhs[1][3]);
                m_Contents[2][2] = (oldContents[0][2] * rhs[2][0]) + (oldContents[1][2] * rhs[2][1])  + (oldContents[2][2] * rhs[2][2]) + (oldContents[3][2] * rhs[2][3]);
                m_Contents[3][2] = (oldContents[0][2] * rhs[3][0]) + (oldContents[1][2] * rhs[3][1]) + (oldContents[2][2] * rhs[3][2]) + (oldContents[3][2] * rhs[3][3]);
                
                m_Contents[0][3] = (oldContents[0][3] * rhs[0][0]) + (oldContents[1][3] * rhs[0][1])  + (oldContents[2][3] * rhs[0][2])  + (oldContents[3][3] * rhs[0][3]);
                m_Contents[1][3] = (oldContents[0][3] * rhs[1][0]) + (oldContents[1][3] * rhs[1][1])  + (oldContents[2][3] * rhs[1][2])  + (oldContents[3][3] * rhs[1][3]);
                m_Contents[2][3] = (oldContents[0][3] * rhs[2][0]) + (oldContents[1][3] * rhs[2][1])  + (oldContents[2][3] * rhs[2][2]) + (oldContents[3][3] * rhs[2][3]);
                m_Contents[3][3] = (oldContents[0][3] * rhs[3][0]) + (oldContents[1][3] * rhs[3][1]) + (oldContents[2][3] * rhs[3][2]) + (oldContents[3][3] * rhs[3][3]);

                return (*this);
            }

            Matrix4x4<T>& operator*=(T const rhs)
            {
                for(unsigned row = 0; row < 4; row++)
                {
                    for(unsigned col = 0; col < 4; col++)
                    {
                        m_Contents[row][col] *= rhs[row][col];
                    }
                }

                return (*this);
            }

            Matrix4x4<T>& operator*=(Vector4<T> const &rhs)
            {
                for(unsigned i = 0; i < 3; i++)
                {
                    m_Contents[(i * 4) + 0] *= rhs.x;
                    m_Contents[(i * 4) + 1] *= rhs.y;
                    m_Contents[(i * 4) + 2] *= rhs.z;
                    m_Contents[(i * 4) + 3] *= rhs.w;
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
             * \return The Position vector
             */
            Vector3<T> getPosition() const
            {
                return Vector3<T>(m_Contents[3][0], m_Contents[3][1], m_Contents[3][2]);
            }

            /**
             * \return The 3x3 Rotation/Scaling Matrix 
             */
            Matrix3x3<T> getRotationScalingMatrix() const
            {
                return Matrix3x3<T>(m_Contents[0][0], m_Contents[0][1], m_Contents[0][2], 
                                    m_Contents[1][0], m_Contents[1][1], m_Contents[1][2],
                                    m_Contents[2][0], m_Contents[2][1], m_Contents[2][2]);
            }

            /**
             * \return The element at the specified index [0-15]
             */
            T getElement(unsigned const index) const
            {
                if(index > 15)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Index Access");
                }

                return m_Contents[(index / 4)][(index % 4)];
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
                m_Contents[0][3] = static_cast<T>(0);

                // Y-Axis Rotation
                m_Contents[1][0] = static_cast<T>(0);
                m_Contents[1][1] = static_cast<T>(1);
                m_Contents[1][2] = static_cast<T>(0);
                m_Contents[1][3] = static_cast<T>(0);

                // Z-Axis Rotation
                m_Contents[2][0] = static_cast<T>(0);
                m_Contents[2][1] = static_cast<T>(0);
                m_Contents[2][2] = static_cast<T>(1);
                m_Contents[2][3] = static_cast<T>(0);

                // Position
                m_Contents[3][0] = static_cast<T>(0);
                m_Contents[3][1] = static_cast<T>(0);
                m_Contents[3][2] = static_cast<T>(0);
                m_Contents[3][3] = static_cast<T>(1);
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
             * Sets the position vector.
             *
             * \param[in] x X component of the position vector
             * \param[in] y Y component of the position vector
             * \param[in] z Z component of the position vector
             */
            void setPosition(T const &x, T const &y, T const &z)
            {
                m_Contents[3][0] = x;
                m_Contents[3][1] = y;
                m_Contents[3][2] = z;
            }

            /**
             * Sets the position vector.
             *
             * \param[in] vec The position vector
             */
            void setPosition(Vector3<T> const &vec)
            {
                m_Contents[3][0] = vec.x;
                m_Contents[3][1] = vec.y;
                m_Contents[3][2] = vec.z;
            }

            /**
             * Sets the value of the element at the specified row/column position.
             *
             * \param[in] row    Row of the element [0,3]
             * \param[in] column Column of the element [0,3]
             * \param[in] value  Value to set
             */
            void setElement(unsigned const &row, unsigned const &column, T const &value)
            {
                if(row > 3)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Row Access");
                }

                if(column > 3)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Column Access");
                }

                m_Contents[row][column] = value;
            }

            /**
             * Sets the value of the element at the specified index.
             *
             * \param[in] index Index of the element [0,15]
             * \param[in] value Value to set
             */
            void setElement(unsigned const &index, T const &value)
            {
                if(index > 15)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Index Access");
                }

                m_Contents[(index / 4)][(index % 4)] = value;
            }

            //------------------------------------------------------------------------------
            // OPERATIONS
            //------------------------------------------------------------------------------

            /**
             * Creates an orthographic projection matrix with the specified attributes.
             *
             * \param[in] xMin
             * \param[in] xMax
             * \param[in] yMin
             * \param[in] yMax
             * \param[in] nearClip
             * \param[in] farClip
             *
             * \return The orthographic projection matrix
             */
            static Matrix4x4<T> createOrthographicMatrix(float const &xMin, float const &xMax, float const &yMin, float const &yMax, 
                                                         float const &nearClip, float const &farClip)
            {
                Matrix4x4<T> matrix;

                matrix[0][0] = 2.0f / (xMax - xMin);
                matrix[1][1] = 2.0f / (yMax - yMin);
                matrix[2][2] = -2.0f / (farClip - nearClip);
                matrix[3][0] = -((xMax + xMin) / (xMax - xMin));
                matrix[3][1] = -((yMax + yMin) / (yMax - yMin));
                matrix[3][2] = -((farClip + nearClip) / (farClip - nearClip));

                return matrix;
            }

            /**
             * Creates a perspective projection matrix with the specified attributes.
             *
             * \param[in] fov
             * \param[in] aspectRatio Screen Width / Screen Height
             * \param[in] nearClip
             * \param[in] farClip
             *
             * \return The perspective projection matrix
             */
            static Matrix4x4<T> createPerspectiveMatrix(float const &fov, float const &aspectRatio, float const &nearClip, float const &farClip)
            {
                Matrix4x4<T> matrix;

                float yMax = nearClip * std::tanf(fov * 0.5f);
                float yMin = -yMax;
                float xMin = yMin * aspectRatio;
                float xMax = -xMin;

                matrix[0][0] = (2.f * nearClip) / (xMax - xMin);
			    matrix[1][1] = (2.f * nearClip) / (yMax - yMin);
			    matrix[2][0] = (xMax + xMin) / (xMax - xMin);
			    matrix[2][1] = (yMax + yMin) / (yMax - yMin);
			    matrix[2][2] = -((farClip + nearClip) / (farClip - nearClip));
			    matrix[2][3] = -1.f;
			    matrix[3][2] = -((2.f * (farClip * nearClip)) / (farClip - nearClip));
			    matrix[3][3] = 0.f;

                return matrix;
            }

            /**
             * Creates and returns the transpose of the provided matrix.
             *
             * \return The transpose matrix
             */
            static Matrix4x4<T> createTransposeMatrix(Matrix4x4<T> const &matrix)
            {
                Matrix4x4<T> result;

                result[0][0] = matrix[0][0];
                result[0][1] = matrix[1][0];
                result[0][2] = matrix[2][0];
                result[0][3] = matrix[3][0];

                result[1][0] = matrix[0][1];
                result[1][1] = matrix[1][1];
                result[1][2] = matrix[2][1];
                result[1][3] = matrix[3][1];

                result[2][0] = matrix[0][2];
                result[2][1] = matrix[1][2];
                result[2][2] = matrix[2][2];
                result[2][3] = matrix[3][2];

                result[3][0] = matrix[0][3];
                result[3][1] = matrix[1][3];
                result[3][2] = matrix[2][3];
                result[3][3] = matrix[3][3];

                return result;
            }

            /**
             * Creates a returns the inverse of the provided matrix.
             * 
             * \return The inverse matrix
             */
            static Matrix4x4<T> createInverseMatrix(Matrix4x4<T> const &matrix)
            {
                /*
                  00  01  02  03
                  04  05  06  07
                  08  09  10  11
                  12  13  14  15

                  0
                  5
                  10
                  15

                   1 <-> 4
                   2 <-> 8
                   3 <-> 12
                   6 <-> 9
                   7 <-> 13
                  11 <-> 14
                */

                T coef00 = matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3];
                T coef02 = matrix[1][2]  * matrix[3][3] - matrix[3][2] * matrix[1][3];
                T coef03 = matrix[1][2]  * matrix[2][3] - matrix[2][2] * matrix[1][3];

                T coef04 = matrix[2][1]  * matrix[3][3] - matrix[3][1] * matrix[2][3];
                T coef06 = matrix[1][1]  * matrix[3][3] - matrix[3][1] * matrix[1][3];
                T coef07 = matrix[1][1]  * matrix[2][3] - matrix[2][1]  * matrix[1][3];

                T coef08 = matrix[2][1]  * matrix[3][2] - matrix[3][1] * matrix[2][2];
                T coef10 = matrix[1][1]  * matrix[3][2] - matrix[3][1] * matrix[1][2];
                T coef11 = matrix[1][1]  * matrix[2][2] - matrix[2][1]  * matrix[1][2];

                T coef12 = matrix[2][0]  * matrix[3][3] - matrix[3][0] * matrix[2][3];
                T coef14 = matrix[1][0]  * matrix[3][3] - matrix[3][0] * matrix[1][3];
                T coef15 = matrix[1][0]  * matrix[2][3] - matrix[2][0]  * matrix[1][3];

                T coef16 = matrix[2][0]  * matrix[3][2] - matrix[3][0] * matrix[2][2];
                T coef18 = matrix[1][0]  * matrix[3][2] - matrix[3][0] * matrix[1][2];
                T coef19 = matrix[1][0]  * matrix[2][2] - matrix[2][0]  * matrix[1][2];

                T coef20 = matrix[2][0]  * matrix[3][1] - matrix[3][0] * matrix[2][1];
                T coef22 = matrix[1][0]  * matrix[3][1] - matrix[3][0] * matrix[1][1];
                T coef23 = matrix[1][0]  * matrix[2][1]  - matrix[2][0]  * matrix[1][1];

                Vector4<T> fac0(coef00, coef00, coef02, coef03);
                Vector4<T> fac1(coef04, coef04, coef06, coef07);
                Vector4<T> fac2(coef08, coef08, coef10, coef11);
                Vector4<T> fac3(coef12, coef12, coef14, coef15);
                Vector4<T> fac4(coef16, coef16, coef18, coef19);
                Vector4<T> fac5(coef20, coef20, coef22, coef23);

                Vector4<T> vec0(matrix[1][0], matrix[0][0], matrix[0][0], matrix[0][0]);
                Vector4<T> vec1(matrix[1][1], matrix[0][1], matrix[0][1], matrix[0][1]);
                Vector4<T> vec2(matrix[1][2], matrix[0][2], matrix[0][2], matrix[0][2]);
                Vector4<T> vec3(matrix[1][3], matrix[0][3], matrix[0][3], matrix[0][3]);
              
                Vector4<T> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
                Vector4<T> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
                Vector4<T> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
                Vector4<T> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

                Vector4<T> signA(static_cast<T>(1),  static_cast<T>(-1), static_cast<T>(1),  static_cast<T>(-1));
                Vector4<T> signB(static_cast<T>(-1), static_cast<T>(1),  static_cast<T>(-1), static_cast<T>(1));

                Matrix4x4<T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

                Vector4<T> invVec(inverse[0][0], inverse[0][1], inverse[0][2], inverse[0][3]);
                Vector4<T> rowVec(matrix[0][0],  matrix[1][0],  matrix[2][0],  matrix[3][0]);
                Vector4<T> dot0 = rowVec * invVec;

                T dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);
                T oneOverDeterminant = static_cast<T>(1) / dot1;

                return inverse * oneOverDeterminant;
            }

        protected:

        private:

            Vector4<T> m_Contents[4];
        };
        
        //----------------------------------------------------------------------------------

        template<typename T>
        bool operator==(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            return IsEqual<T>(lhs[0][0], rhs[0][0]) && IsEqual<T>(lhs[0][1], rhs[0][1]) &&
                   IsEqual<T>(lhs[0][2], rhs[0][2]) && IsEqual<T>(lhs[0][3], rhs[0][3]) &&
                   IsEqual<T>(lhs[1][0], rhs[1][0]) && IsEqual<T>(lhs[1][1], rhs[1][1]) &&
                   IsEqual<T>(lhs[1][2], rhs[1][2]) && IsEqual<T>(lhs[1][3], rhs[1][3]) &&
                   IsEqual<T>(lhs[2][0], rhs[2][0]) && IsEqual<T>(lhs[2][1], rhs[2][1]) &&
                   IsEqual<T>(lhs[2][2], rhs[2][2]) && IsEqual<T>(lhs[2][3], rhs[2][3]) &&
                   IsEqual<T>(lhs[3][0], rhs[3][0]) && IsEqual<T>(lhs[3][1], rhs[3][1]) &&
                   IsEqual<T>(lhs[3][2], rhs[3][2]) && IsEqual<T>(lhs[3][3], rhs[3][3]);
        }
        
        template<typename T>
        bool operator!=(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            return !(lhs == rhs);
        }

        template<typename T>
        Matrix4x4<T> operator+(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            Matrix4x4<T> result(lhs[0][0] + rhs[0][0], lhs[0][1] + rhs[0][1],
                                lhs[0][2] + rhs[0][2], lhs[0][3] + rhs[0][3],
                                lhs[1][0] + rhs[1][0], lhs[1][1] + rhs[1][1],
                                lhs[1][2] + rhs[1][2], lhs[1][3] + rhs[1][3],
                                lhs[2][0] + rhs[2][0], lhs[2][1] + rhs[2][1],
                                lhs[2][2] + rhs[2][2], lhs[2][3] + rhs[2][3],
                                lhs[3][0] + rhs[3][0], lhs[3][1] + rhs[3][1],
                                lhs[3][2] + rhs[3][2], lhs[3][3] + rhs[3][3]);

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator-(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            Matrix4x4<T> result(lhs[0][0] - rhs[0][0], lhs[0][1] - rhs[0][1],
                                lhs[0][2] - rhs[0][2], lhs[0][3] - rhs[0][3],
                                lhs[1][0] - rhs[1][0], lhs[1][1] - rhs[1][1],
                                lhs[1][2] - rhs[1][2], lhs[1][3] - rhs[1][3],
                                lhs[2][0] - rhs[2][0], lhs[2][1] - rhs[2][1],
                                lhs[2][2] - rhs[2][2], lhs[2][3] - rhs[2][3],
                                lhs[3][0] - rhs[3][0], lhs[3][1] - rhs[3][1],
                                lhs[3][2] - rhs[3][2], lhs[3][3] - rhs[3][3]);

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator*(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            Matrix4x4<T> result;

            result[0][0] = (lhs[0][0] * rhs[0][0]) + (lhs[0][1] * rhs[1][0]) + (lhs[0][2] * rhs[2][0]) + (lhs[0][3] * rhs[3][0]);
            result[0][1] = (lhs[0][0] * rhs[0][1]) + (lhs[0][1] * rhs[1][1]) + (lhs[0][2] * rhs[2][1]) + (lhs[0][3] * rhs[3][1]);
            result[0][2] = (lhs[0][0] * rhs[0][2]) + (lhs[0][1] * rhs[1][2]) + (lhs[0][2] * rhs[2][2]) + (lhs[0][3] * rhs[3][2]);
            result[0][3] = (lhs[0][0] * rhs[0][3]) + (lhs[0][1] * rhs[1][3]) + (lhs[0][2] * rhs[2][3]) + (lhs[0][3] * rhs[3][3]);

            result[1][0] = (lhs[1][0] * rhs[0][0]) + (lhs[1][1] * rhs[1][0]) + (lhs[1][2] * rhs[2][0]) + (lhs[1][3] * rhs[3][0]);
            result[1][1] = (lhs[1][0] * rhs[0][1]) + (lhs[1][1] * rhs[1][1]) + (lhs[1][2] * rhs[2][1]) + (lhs[1][3] * rhs[3][1]);
            result[1][2] = (lhs[1][0] * rhs[0][2]) + (lhs[1][1] * rhs[1][2]) + (lhs[1][2] * rhs[2][2]) + (lhs[1][3] * rhs[3][2]);
            result[1][3] = (lhs[1][0] * rhs[0][3]) + (lhs[1][1] * rhs[1][3]) + (lhs[1][2] * rhs[2][3]) + (lhs[1][3] * rhs[3][3]);

            result[2][0] = (lhs[2][0] * rhs[0][0]) + (lhs[2][1] * rhs[1][0]) + (lhs[2][2] * rhs[2][0]) + (lhs[2][3] * rhs[3][0]);
            result[2][1] = (lhs[2][0] * rhs[0][1]) + (lhs[2][1] * rhs[1][1]) + (lhs[2][2] * rhs[2][1]) + (lhs[2][3] * rhs[3][1]);
            result[2][2] = (lhs[2][0] * rhs[0][2]) + (lhs[2][1] * rhs[1][2]) + (lhs[2][2] * rhs[2][2]) + (lhs[2][3] * rhs[3][2]);
            result[2][3] = (lhs[2][0] * rhs[0][3]) + (lhs[2][1] * rhs[1][3]) + (lhs[2][2] * rhs[2][3]) + (lhs[2][3] * rhs[3][3]);

            result[3][0] = (lhs[3][0] * rhs[0][0]) + (lhs[3][1] * rhs[1][0]) + (lhs[3][2] * rhs[2][0]) + (lhs[3][3] * rhs[3][0]);
            result[3][1] = (lhs[3][0] * rhs[0][1]) + (lhs[3][1] * rhs[1][1]) + (lhs[3][2] * rhs[2][1]) + (lhs[3][3] * rhs[3][1]);
            result[3][2] = (lhs[3][0] * rhs[0][2]) + (lhs[3][1] * rhs[1][2]) + (lhs[3][2] * rhs[2][2]) + (lhs[3][3] * rhs[3][2]);
            result[3][3] = (lhs[3][0] * rhs[0][3]) + (lhs[3][1] * rhs[1][3]) + (lhs[3][2] * rhs[2][3]) + (lhs[3][3] * rhs[3][3]);

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator*(Matrix4x4<T> const &lhs, T const rhs)
        {
            Matrix4x4<T> result;

            for(unsigned row = 0; row < 4; row++)
            {
                for(unsigned col = 0; col < 4; col++)
                {
                    result[row][col] = lhs[row][col] * rhs;
                }
            }

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator*(Matrix4x4<T> const &lhs, Vector4<T> const &rhs)
        {
            Matrix4x4<T> result;

            for(unsigned i = 0; i < 3; i++)
            {
                result[i][0] = lhs[i][0] * rhs.x;
                result[i][1] = lhs[i][1] * rhs.y;
                result[i][2] = lhs[i][2] * rhs.z;
                result[i][3] = lhs[i][3] * rhs.w;
            }

            return result;
        }

        //--------------------------------------------
        // Common matrix formats

        typedef Matrix4x4<float> Matrix4x4f;
        typedef Matrix4x4<double> Matrix4x4d;

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