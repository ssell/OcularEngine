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
#ifndef __H__OCULAR_MATH_MATRIX_4X4__H__
#define __H__OCULAR_MATH_MATRIX_4X4__H__

#include "Exception.hpp"
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
         * Implementation of a generic 4x4 matrix. 
         * Represented as:
         *
         *    x.x, x.y, x.z, 0
         *    y.x, y.y, y.z, 0
         *    z.x, z.y, z.z, 0
         *    p.x, p.y, p.z, 1  
         *
         * Stored internally in a single array as:
         *
         *   {x.x, x.y, x.z, 0, y.x, y.y, y.z, 0, z.x, z.y, z.z, 0, p.x, p.y, p.z, 1}
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

            Matrix4x4(Matrix3x3<T> const &matrix)
            {
                setIdentity();

                setXRotation(matrix.getXRotation());
                setYRotation(matrix.getYRotation());
                setZRotation(matrix.getZRotation());
            }

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

            bool operator==(Matrix4x4<T> const &rhs)
            {
                return IsEqual<T>(m_Contents[0],  rhs[0])  && IsEqual<T>(m_Contents[1],  rhs[1])  &&
                       IsEqual<T>(m_Contents[2],  rhs[2])  && IsEqual<T>(m_Contents[3],  rhs[3])  &&
                       IsEqual<T>(m_Contents[4],  rhs[4])  && IsEqual<T>(m_Contents[5],  rhs[5])  &&
                       IsEqual<T>(m_Contents[6],  rhs[6])  && IsEqual<T>(m_Contents[7],  rhs[7])  &&
                       IsEqual<T>(m_Contents[8],  rhs[8])  && IsEqual<T>(m_Contents[9],  rhs[9])  &&
                       IsEqual<T>(m_Contents[10], rhs[10]) && IsEqual<T>(m_Contents[11], rhs[11]) &&
                       IsEqual<T>(m_Contents[12], rhs[12]) && IsEqual<T>(m_Contents[13], rhs[13]) &&
                       IsEqual<T>(m_Contents[14], rhs[14]) && IsEqual<T>(m_Contents[15], rhs[15]);
            }

            bool operator!=(Matrix4x4<T> const &rhs)
            {
                return !(*this == rhs);
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
            Vector3<T> getXRotation()
            {
                return Vector3<T>(m_Contents[0], m_Contents[1], m_Contents[2]);
            }

            /**
             * \return The Y-Axis rotation vector
             */
            Vector3<T> getYRotation()
            {
                return Vector3<T>(m_Contents[4], m_Contents[5], m_Contents[6]);
            }

            /**
             * \return The Z-Axis rotation vector
             */
            Vector3<T> getZRotation()
            {
                return Vector3<T>(m_Contents[8], m_Contents[9], m_Contents[10]);
            }

            /**
             * \return The Position vector
             */
            Vector3<T> getPosition()
            {
                return Vector3<T>(m_Contents[12], m_Contents[13], m_Contents[14]);
            }

            /**
             * \return The element at the specified row [0-3] and colum [0-3] combination
             */
            T getElement(unsigned const &row, unsigned const &column)
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
            T getElement(unsigned const &index)
            {
                if(index > 15)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Index Access");
                }

                return m_Contents[index];
            }

            float* getContents()
            {
                return m_Contents;
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
            static Matrix4x4<T> createInverse(Matrix4x4<T> const &matrix)
            {
                Matrix4x4<T> result;

                float determinant = 0.0f;
                float determinantIJ = 0.0f;

                //------------------------------------
                // Calculate the 4x4 determinant

                for(int i = 0; i < 4; i++)
                {
                    determinantIJ = calcDeterminant(matrix, 0, i);
                    determinant += (i & 0x1) ? (-matrix[i] * determinantIJ) : (matrix[i] * determinantIJ);
                }

                determinant = 1.0f / determinant;

                //------------------------------------
                // Calculate the inverse
                
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        determinantIJ = calcDeterminant(matrix, j, i);
                        result[(i * 4) + j] = ((i + j) & 0x1) ? (-determinantIJ * determinant) : (determinantIJ * determinant);
                    }
                }

                return result;
            }

        protected:

        private:

            static float calcDeterminant(Matrix4x4<T> const &matrix, int const &i, int const &j)
            {
                int x;
                int y;

			    float result;
                float mat[3][3];

			    x = 0;

			    for(int ii = 0; ii < 4; ii++)
			    {
				    if(ii == i)
                    {
					    continue;
                    }

				    y = 0;

				    for(int jj = 0; jj < 4; jj++)
				    {
					    if(jj == j)
                        {
					        continue;
                        }

					    mat[x][y] = matrix[(ii * 4) + jj];
					    y++;
				    }

				    x++;
			    }

			    result  = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]);
			    result -= mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
			    result += mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);

			    return result;
            }

            T m_Contents[16];
        };

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

            result[0]  = (lhs[0] * rhs[0])  + (lhs[4] * rhs[1])  + (lhs[8] * rhs[2])  + (lhs[12] * rhs[3]);
            result[4]  = (lhs[0] * rhs[4])  + (lhs[4] * rhs[5])  + (lhs[8] * rhs[6])  + (lhs[12] * rhs[7]);
            result[8]  = (lhs[0] * rhs[8])  + (lhs[4] * rhs[9])  + (lhs[8] * rhs[10]) + (lhs[12] * rhs[11]);
            result[12] = (lhs[0] * rhs[12]) + (lhs[4] * rhs[13]) + (lhs[8] * rhs[14]) + (lhs[12] * rhs[15]);

            result[1]  = (lhs[1] * rhs[0])  + (lhs[5] * rhs[1])  + (lhs[9] * rhs[2])  + (lhs[13] * rhs[3]);
            result[5]  = (lhs[1] * rhs[4])  + (lhs[5] * rhs[5])  + (lhs[9] * rhs[6])  + (lhs[13] * rhs[7]);
            result[9]  = (lhs[1] * rhs[8])  + (lhs[5] * rhs[9])  + (lhs[9] * rhs[10]) + (lhs[13] * rhs[11]);
            result[13] = (lhs[1] * rhs[12]) + (lhs[5] * rhs[13]) + (lhs[9] * rhs[14]) + (lhs[13] * rhs[15]);

            result[2]  = (lhs[2] * rhs[0])  + (lhs[6] * rhs[1])  + (lhs[10] * rhs[2])  + (lhs[14] * rhs[3]);
            result[6]  = (lhs[2] * rhs[4])  + (lhs[6] * rhs[5])  + (lhs[10] * rhs[6])  + (lhs[14] * rhs[7]);
            result[10] = (lhs[2] * rhs[8])  + (lhs[6] * rhs[9])  + (lhs[10] * rhs[10]) + (lhs[14] * rhs[11]);
            result[13] = (lhs[2] * rhs[12]) + (lhs[6] * rhs[13]) + (lhs[10] * rhs[14]) + (lhs[14] * rhs[15]);

            result[3]  = (lhs[3] * rhs[0])  + (lhs[7] * rhs[1])  + (lhs[11] * rhs[2])  + (lhs[15] * rhs[3]);
            result[7]  = (lhs[3] * rhs[4])  + (lhs[7] * rhs[5])  + (lhs[11] * rhs[6])  + (lhs[15] * rhs[7]);
            result[11] = (lhs[3] * rhs[8])  + (lhs[7] * rhs[9])  + (lhs[11] * rhs[10]) + (lhs[15] * rhs[11]);
            result[15] = (lhs[3] * rhs[12]) + (lhs[7] * rhs[13]) + (lhs[11] * rhs[14]) + (lhs[15] * rhs[15]);

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