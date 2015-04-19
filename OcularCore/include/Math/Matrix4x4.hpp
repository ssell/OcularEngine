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
                m_Contents[0]  = p00;
                m_Contents[1]  = p01;
                m_Contents[2]  = p02;
                m_Contents[3]  = p03;

                // Y-Axis Rotation
                m_Contents[4]  = p10;
                m_Contents[5]  = p11;
                m_Contents[6]  = p12;
                m_Contents[7]  = p13;

                // Z-Axis Rotation
                m_Contents[8]  = p20;
                m_Contents[9]  = p21;
                m_Contents[10] = p22;
                m_Contents[11] = p23;

                // Position
                m_Contents[12] = p30;
                m_Contents[13] = p31;
                m_Contents[14] = p32;
                m_Contents[15] = p33;
            }

            /**
             * \param[in] matrix
             */
            Matrix4x4(Matrix4x4<T> const& matrix)
            {
                m_Contents[0]  = matrix[0];
                m_Contents[1]  = matrix[1];
                m_Contents[2]  = matrix[2];
                m_Contents[3]  = matrix[3];
                m_Contents[4]  = matrix[4];
                m_Contents[5]  = matrix[5];
                m_Contents[6]  = matrix[6];
                m_Contents[7]  = matrix[7];
                m_Contents[8]  = matrix[8];
                m_Contents[9]  = matrix[9];
                m_Contents[10] = matrix[10];
                m_Contents[11] = matrix[11];
                m_Contents[12] = matrix[12];
                m_Contents[13] = matrix[13];
                m_Contents[14] = matrix[14];
                m_Contents[15] = matrix[15];
            }

            /*
             * \param[in] matrix
             */
            Matrix4x4(Matrix3x3<T> const& matrix)
            {
                setIdentity();

                m_Contents[0]  = matrix[0];
                m_Contents[1]  = matrix[1];
                m_Contents[2]  = matrix[2];
                m_Contents[3]  = matrix[3];
                m_Contents[4]  = matrix[4];
                m_Contents[5]  = matrix[5];
                m_Contents[6]  = matrix[6];
                m_Contents[7]  = matrix[7];
                m_Contents[8]  = matrix[8];
            }

            /**
             * \param[in] row0 Row 0 contents (x-rotation)
             * \param[in] row1 Row 1 contents (y-rotation)
             * \param[in] row2 Row 2 contents (z-rotation)
             * \param[in] row3 Row 3 contents (position)
             */
            Matrix4x4(Vector4<T> const &row0, Vector4<T> const &row1, Vector4<T> const &row2, Vector4<T> const &row3)
            {
                m_Contents[0]  = row0.x;
                m_Contents[1]  = row0.y;
                m_Contents[2]  = row0.z;
                m_Contents[3]  = row0.w;

                m_Contents[4]  = row1.x;
                m_Contents[5]  = row1.y;
                m_Contents[6]  = row1.z;
                m_Contents[7]  = row1.w;

                m_Contents[8]  = row2.x;
                m_Contents[9]  = row2.y;
                m_Contents[10] = row2.z;
                m_Contents[11] = row2.w;

                m_Contents[12] = row3.x;
                m_Contents[13] = row3.y;
                m_Contents[14] = row3.z;
                m_Contents[15] = row3.w;
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

            T& operator[](unsigned const &index)
            {
                if(index > 15)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Contents[index];
            }

            const T& operator[](unsigned const &index) const
            {
                if(index > 15)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Contents[index];
            }

            Matrix4x4<T>& operator=(Matrix4x4<T> const &rhs)
            {
                for(unsigned i = 0; i < 16; i++)
                {
                    m_Contents[i] = rhs[i];
                }

                return (*this);
            }

            Matrix4x4<T>& operator+=(Matrix4x4<T> const &rhs)
            {
                for(unsigned i = 0; i < 16; i++)
                {
                    m_Contents[i] += rhs[i];
                }

                return (*this);
            }

            Matrix4x4<T>& operator-=(Matrix4x4<T> const &rhs)
            {
                for(unsigned i = 0; i < 16; i++)
                {
                    m_Contents[i] -= rhs[i];
                }

                return (*this);
            }

            Matrix4x4<T>& operator*=(Matrix4x4<T> const &rhs)
            {
                Matrix4x4<T> oldContents = (*this);

                m_Contents[0]  = (oldContents[0] * rhs[0])  + (oldContents[4] * rhs[1])  + (oldContents[8] * rhs[2])  + (oldContents[12] * rhs[3]);
                m_Contents[4]  = (oldContents[0] * rhs[4])  + (oldContents[4] * rhs[5])  + (oldContents[8] * rhs[6])  + (oldContents[12] * rhs[7]);
                m_Contents[8]  = (oldContents[0] * rhs[8])  + (oldContents[4] * rhs[9])  + (oldContents[8] * rhs[10]) + (oldContents[12] * rhs[11]);
                m_Contents[12] = (oldContents[0] * rhs[12]) + (oldContents[4] * rhs[13]) + (oldContents[8] * rhs[14]) + (oldContents[12] * rhs[15]);
                
                m_Contents[1]  = (oldContents[1] * rhs[0])  + (oldContents[5] * rhs[1])  + (oldContents[9] * rhs[2])  + (oldContents[13] * rhs[3]);
                m_Contents[5]  = (oldContents[1] * rhs[4])  + (oldContents[5] * rhs[5])  + (oldContents[9] * rhs[6])  + (oldContents[13] * rhs[7]);
                m_Contents[9]  = (oldContents[1] * rhs[8])  + (oldContents[5] * rhs[9])  + (oldContents[9] * rhs[10]) + (oldContents[13] * rhs[11]);
                m_Contents[13] = (oldContents[1] * rhs[12]) + (oldContents[5] * rhs[13]) + (oldContents[9] * rhs[14]) + (oldContents[13] * rhs[15]);
                
                m_Contents[2]  = (oldContents[2] * rhs[0])  + (oldContents[6] * rhs[1])  + (oldContents[10] * rhs[2])  + (oldContents[14] * rhs[3]);
                m_Contents[6]  = (oldContents[2] * rhs[4])  + (oldContents[6] * rhs[5])  + (oldContents[10] * rhs[6])  + (oldContents[14] * rhs[7]);
                m_Contents[10] = (oldContents[2] * rhs[8])  + (oldContents[6] * rhs[9])  + (oldContents[10] * rhs[10]) + (oldContents[14] * rhs[11]);
                m_Contents[14] = (oldContents[2] * rhs[12]) + (oldContents[6] * rhs[13]) + (oldContents[10] * rhs[14]) + (oldContents[14] * rhs[15]);
                
                m_Contents[3]  = (oldContents[3] * rhs[0])  + (oldContents[7] * rhs[1])  + (oldContents[11] * rhs[2])  + (oldContents[15] * rhs[3]);
                m_Contents[7]  = (oldContents[3] * rhs[4])  + (oldContents[7] * rhs[5])  + (oldContents[11] * rhs[6])  + (oldContents[15] * rhs[7]);
                m_Contents[11] = (oldContents[3] * rhs[8])  + (oldContents[7] * rhs[9])  + (oldContents[11] * rhs[10]) + (oldContents[15] * rhs[11]);
                m_Contents[15] = (oldContents[3] * rhs[12]) + (oldContents[7] * rhs[13]) + (oldContents[11] * rhs[14]) + (oldContents[15] * rhs[15]);

                return (*this);
            }

            Matrix4x4<T>& operator*=(T const rhs)
            {
                for(unsigned i = 0; i < 16; i++)
                {
                    m_Contents[i] *= rhs;
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
                return Vector3<T>(m_Contents[0], m_Contents[1], m_Contents[2]);
            }

            /**
             * \return The Y-Axis rotation vector
             */
            Vector3<T> getYRotation() const
            {
                return Vector3<T>(m_Contents[4], m_Contents[5], m_Contents[6]);
            }

            /**
             * \return The Z-Axis rotation vector
             */
            Vector3<T> getZRotation() const
            {
                return Vector3<T>(m_Contents[8], m_Contents[9], m_Contents[10]);
            }

            /**
             * \return The Position vector
             */
            Vector3<T> getPosition() const
            {
                return Vector3<T>(m_Contents[12], m_Contents[13], m_Contents[14]);
            }

            /**
             * \return The element at the specified row [0-3] and colum [0-3] combination
             */
            T getElement(unsigned const row, unsigned const column) const
            {
                if(row > 3)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Row Access");
                }

                if(column > 3)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Column Access");
                }

                return m_Contents[(row * 4) + column];
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

                return m_Contents[index];
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
                m_Contents[0]  = static_cast<T>(1);
                m_Contents[1]  = static_cast<T>(0);
                m_Contents[2]  = static_cast<T>(0);
                m_Contents[3]  = static_cast<T>(0);

                // Y-Axis Rotation
                m_Contents[4]  = static_cast<T>(0);
                m_Contents[5]  = static_cast<T>(1);
                m_Contents[6]  = static_cast<T>(0);
                m_Contents[7]  = static_cast<T>(0);

                // Z-Axis Rotation
                m_Contents[8]  = static_cast<T>(0);
                m_Contents[9]  = static_cast<T>(0);
                m_Contents[10] = static_cast<T>(1);
                m_Contents[11] = static_cast<T>(0);

                // Position
                m_Contents[12] = static_cast<T>(0);
                m_Contents[13] = static_cast<T>(0);
                m_Contents[14] = static_cast<T>(0);
                m_Contents[15] = static_cast<T>(1);
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
                m_Contents[0] = x;
                m_Contents[1] = y;
                m_Contents[2] = z;
            }

            /**
             * Sets the X-Axis rotation vector.
             *
             * \param[in] vec The X-Axis rotation vector
             */
            void setXRotation(Vector3<T> const &vec)
            {
                m_Contents[0] = vec.x;
                m_Contents[1] = vec.y;
                m_Contents[2] = vec.z;
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
                m_Contents[4] = x;
                m_Contents[5] = y;
                m_Contents[6] = z;
            }

            /**
             * Sets the Y-Axis rotation vector.
             *
             * \param[in] vec The Y-Axis rotation vector
             */
            void setYRotation(Vector3<T> const &vec)
            {
                m_Contents[4] = vec.x;
                m_Contents[5] = vec.y;
                m_Contents[6] = vec.z;
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
                m_Contents[8]  = x;
                m_Contents[9]  = y;
                m_Contents[10] = z;
            }

            /**
             * Sets the Z-Axis rotation vector.
             *
             * \param[in] vec The Z-Axis rotation vector
             */
            void setZRotation(Vector3<T> const &vec)
            {
                m_Contents[8]  = vec.x;
                m_Contents[9]  = vec.y;
                m_Contents[10] = vec.z;
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
                m_Contents[12] = x;
                m_Contents[13] = y;
                m_Contents[14] = z;
            }

            /**
             * Sets the position vector.
             *
             * \param[in] vec The position vector
             */
            void setPosition(Vector3<T> const &vec)
            {
                m_Contents[12] = vec.x;
                m_Contents[13] = vec.y;
                m_Contents[14] = vec.z;
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

                m_Contents[(row * 4) + column] = value;
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

                m_Contents[index] = value;
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

                matrix[0]  = 2.0f / (xMax - xMin);
                matrix[5]  = 2.0f / (yMax - yMin);
                matrix[10] = -2.0f / (farClip - nearClip);
                matrix[12] = -((xMax + xMin) / (xMax - xMin));
                matrix[13] = -((yMax + yMin) / (yMax - yMin));
                matrix[14] = -((farClip + nearClip) / (farClip - nearClip));

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

                matrix[0]  = (2.f * nearClip) / (xMax - xMin);
			    matrix[5]  = (2.f * nearClip) / (yMax - yMin);
			    matrix[8]  = (xMax + xMin) / (xMax - xMin);
			    matrix[9]  = (yMax + yMin) / (yMax - yMin);
			    matrix[10] = -((farClip + nearClip) / (farClip - nearClip));
			    matrix[11] = -1.f;
			    matrix[14] = -((2.f * (farClip * nearClip)) / (farClip - nearClip));
			    matrix[15] = 0.f;

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

                result[0]  = matrix[0];
                result[1]  = matrix[4];
                result[2]  = matrix[8];
                result[3]  = matrix[12];

                result[4]  = matrix[1];
                result[5]  = matrix[5];
                result[6]  = matrix[9];
                result[7]  = matrix[13];

                result[8]  = matrix[2];
                result[9]  = matrix[6];
                result[10] = matrix[10];
                result[11] = matrix[14];

                result[12] = matrix[3];
                result[13] = matrix[7];
                result[14] = matrix[11];
                result[15] = matrix[15];

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

                T coef00 = matrix[10] * matrix[15] - matrix[14] * matrix[11];
                T coef02 = matrix[6]  * matrix[15] - matrix[14] * matrix[7];
                T coef03 = matrix[6]  * matrix[11] - matrix[10] * matrix[7];

                T coef04 = matrix[9]  * matrix[15] - matrix[13] * matrix[11];
                T coef06 = matrix[5]  * matrix[15] - matrix[13] * matrix[7];
                T coef07 = matrix[5]  * matrix[11] - matrix[9]  * matrix[7];

                T coef08 = matrix[9]  * matrix[14] - matrix[13] * matrix[10];
                T coef10 = matrix[5]  * matrix[14] - matrix[13] * matrix[6];
                T coef11 = matrix[5]  * matrix[10] - matrix[9]  * matrix[6];

                T coef12 = matrix[8]  * matrix[15] - matrix[12] * matrix[11];
                T coef14 = matrix[4]  * matrix[15] - matrix[12] * matrix[7];
                T coef15 = matrix[4]  * matrix[11] - matrix[8]  * matrix[7];

                T coef16 = matrix[8]  * matrix[14] - matrix[12] * matrix[10];
                T coef18 = matrix[4]  * matrix[14] - matrix[12] * matrix[6];
                T coef19 = matrix[4]  * matrix[10] - matrix[8]  * matrix[6];

                T coef20 = matrix[8]  * matrix[13] - matrix[12] * matrix[9];
                T coef22 = matrix[4]  * matrix[13] - matrix[12] * matrix[5];
                T coef23 = matrix[4]  * matrix[9]  - matrix[8]  * matrix[5];

                Vector4<T> fac0(coef00, coef00, coef02, coef03);
                Vector4<T> fac1(coef04, coef04, coef06, coef07);
                Vector4<T> fac2(coef08, coef08, coef10, coef11);
                Vector4<T> fac3(coef12, coef12, coef14, coef15);
                Vector4<T> fac4(coef16, coef16, coef18, coef19);
                Vector4<T> fac5(coef20, coef20, coef22, coef23);

                Vector4<T> vec0(matrix[4], matrix[0], matrix[0], matrix[0]);
                Vector4<T> vec1(matrix[5], matrix[1], matrix[1], matrix[1]);
                Vector4<T> vec2(matrix[6], matrix[2], matrix[2], matrix[2]);
                Vector4<T> vec3(matrix[7], matrix[3], matrix[3], matrix[3]);
              
                Vector4<T> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
                Vector4<T> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
                Vector4<T> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
                Vector4<T> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

                Vector4<T> signA(static_cast<T>(1),  static_cast<T>(-1), static_cast<T>(1),  static_cast<T>(-1));
                Vector4<T> signB(static_cast<T>(-1), static_cast<T>(1),  static_cast<T>(-1), static_cast<T>(1));

                Matrix4x4<T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

                Vector4<T> invVec(inverse[0], inverse[1], inverse[2], inverse[3]);
                Vector4<T> rowVec(matrix[0],  matrix[4],  matrix[8],  matrix[12]);
                Vector4<T> dot0 = rowVec * invVec;

                T dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);
                T oneOverDeterminant = static_cast<T>(1) / dot1;

                return inverse * oneOverDeterminant;
            }

        protected:

        private:

            T m_Contents[16];
        };
        
        //----------------------------------------------------------------------------------

        template<typename T>
        bool operator==(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            return IsEqual<T>(lhs[0],  rhs[0])  && IsEqual<T>(lhs[1],  rhs[1])  &&
                   IsEqual<T>(lhs[2],  rhs[2])  && IsEqual<T>(lhs[3],  rhs[3])  &&
                   IsEqual<T>(lhs[4],  rhs[4])  && IsEqual<T>(lhs[5],  rhs[5])  &&
                   IsEqual<T>(lhs[6],  rhs[6])  && IsEqual<T>(lhs[7],  rhs[7])  &&
                   IsEqual<T>(lhs[8],  rhs[8])  && IsEqual<T>(lhs[9],  rhs[9])  &&
                   IsEqual<T>(lhs[10], rhs[10]) && IsEqual<T>(lhs[11], rhs[11]) &&
                   IsEqual<T>(lhs[12], rhs[12]) && IsEqual<T>(lhs[13], rhs[13]) &&
                   IsEqual<T>(lhs[14], rhs[14]) && IsEqual<T>(lhs[15], rhs[15]);
        }
        
        template<typename T>
        bool operator!=(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            return !(lhs == rhs);
        }

        template<typename T>
        Matrix4x4<T> operator+(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            Matrix4x4<T> result(lhs[0]  + rhs[0],  lhs[1]  + rhs[1],
                                lhs[2]  + rhs[2],  lhs[3]  + rhs[3],
                                lhs[4]  + rhs[4],  lhs[5]  + rhs[5],
                                lhs[6]  + rhs[6],  lhs[7]  + rhs[7],
                                lhs[8]  + rhs[8],  lhs[9]  + rhs[9],
                                lhs[10] + rhs[10], lhs[11] + rhs[11],
                                lhs[12] + rhs[12], lhs[13] + rhs[13],
                                lhs[14] + rhs[14], lhs[15] + rhs[15]);

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator-(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            Matrix4x4<T> result(lhs[0]  - rhs[0],  lhs[1]  - rhs[1],
                                lhs[2]  - rhs[2],  lhs[3]  - rhs[3],
                                lhs[4]  - rhs[4],  lhs[5]  - rhs[5],
                                lhs[6]  - rhs[6],  lhs[7]  - rhs[7],
                                lhs[8]  - rhs[8],  lhs[9]  - rhs[9],
                                lhs[10] - rhs[10], lhs[11] - rhs[11],
                                lhs[12] - rhs[12], lhs[13] - rhs[13],
                                lhs[14] - rhs[14], lhs[15] - rhs[15]);

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator*(Matrix4x4<T> const &lhs, Matrix4x4<T> const &rhs)
        {
            Matrix4x4<T> result;

            result[0]  = (lhs[0]  * rhs[0]) + (lhs[1]  * rhs[4]) + (lhs[2] * rhs[8])  + (lhs[3]  * rhs[12]);
            result[1]  = (lhs[0]  * rhs[1]) + (lhs[1]  * rhs[5]) + (lhs[2] * rhs[9])  + (lhs[3]  * rhs[13]);
            result[2]  = (lhs[0]  * rhs[2]) + (lhs[1]  * rhs[6]) + (lhs[2] * rhs[10]) + (lhs[3]  * rhs[14]);
            result[3]  = (lhs[0]  * rhs[3]) + (lhs[1]  * rhs[7]) + (lhs[2] * rhs[11]) + (lhs[3]  * rhs[15]);

            result[4]  = (lhs[4]  * rhs[0]) + (lhs[5]  * rhs[4]) + (lhs[6] * rhs[8])  + (lhs[7]  * rhs[12]);
            result[5]  = (lhs[4]  * rhs[1]) + (lhs[5]  * rhs[5]) + (lhs[6] * rhs[9])  + (lhs[7]  * rhs[13]);
            result[6]  = (lhs[4]  * rhs[2]) + (lhs[5]  * rhs[6]) + (lhs[6] * rhs[10]) + (lhs[7]  * rhs[14]);
            result[7]  = (lhs[4]  * rhs[3]) + (lhs[5]  * rhs[7]) + (lhs[6] * rhs[11]) + (lhs[7]  * rhs[15]);

            result[8]  = (lhs[8]  * rhs[0]) + (lhs[9]  * rhs[4]) + (lhs[10] * rhs[8])  + (lhs[11] * rhs[12]);
            result[9]  = (lhs[8]  * rhs[1]) + (lhs[9]  * rhs[5]) + (lhs[10] * rhs[9])  + (lhs[11] * rhs[13]);
            result[10] = (lhs[8]  * rhs[2]) + (lhs[9]  * rhs[6]) + (lhs[10] * rhs[10]) + (lhs[11] * rhs[14]);
            result[11] = (lhs[8]  * rhs[3]) + (lhs[9]  * rhs[7]) + (lhs[10] * rhs[11]) + (lhs[11] * rhs[15]);

            result[12] = (lhs[12] * rhs[0]) + (lhs[13] * rhs[4]) + (lhs[14] * rhs[8])  + (lhs[15] * rhs[12]);
            result[13] = (lhs[12] * rhs[1]) + (lhs[13] * rhs[5]) + (lhs[14] * rhs[9])  + (lhs[15] * rhs[13]);
            result[14] = (lhs[12] * rhs[2]) + (lhs[13] * rhs[6]) + (lhs[14] * rhs[10]) + (lhs[15] * rhs[14]);
            result[15] = (lhs[12] * rhs[3]) + (lhs[13] * rhs[7]) + (lhs[14] * rhs[11]) + (lhs[15] * rhs[15]);

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator*(Matrix4x4<T> const &lhs, T const rhs)
        {
            Matrix4x4<T> result;

            for(unsigned i = 0; i < 16; i++)
            {
                result[i] = lhs[i] * rhs;
            }

            return result;
        }

        template<typename T>
        Matrix4x4<T> operator*(Matrix4x4<T> const &lhs, Vector4<T> const &rhs)
        {
            Matrix4x4<T> result;

            for(unsigned i = 0; i < 3; i++)
            {
                result[(i * 4) + 0] = lhs[(i * 4) + 0] * rhs.x;
                result[(i * 4) + 1] = lhs[(i * 4) + 1] * rhs.y;
                result[(i * 4) + 2] = lhs[(i * 4) + 2] * rhs.z;
                result[(i * 4) + 3] = lhs[(i * 4) + 3] * rhs.w;
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