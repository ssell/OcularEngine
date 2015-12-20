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
#ifndef __H__OCULAR_MATH_MATRIX_4X4_TEMP__H__
#define __H__OCULAR_MATH_MATRIX_4X4_TEMP__H__

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
        template<typename T> class Vector3;
        template<typename T> class Vector4;
        class Matrix3x3;
        class Quaternion;

        struct Matrix4x4_Internal;

        /**
         * \class Matrix4x4
         * \brief A 4x4 column-major float matrix
         *
         *     x.x y.x z.x t.x
         *     x.y y.y z.y t.y
         *     x.z y.z z.z t.z
         *     0.0 0.0 0.0 1.0
         *
         *     00 10 20 30
         *     01 11 21 31
         *     02 12 22 32
         *     03 13 23 33
         *
         *     00 04 08 12
         *     01 05 09 13
         *     02 06 10 14
         *     03 07 11 15
         */
        class Matrix4x4
        {
        public:

            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            /**
             * Creates a new 4x4 column-major matrix.
             *
             * \param[in] x0 First element of the x-rotation column
             * \param[in] y0 First element of the y-rotation column
             * \param[in] z0 First element of the z-rotation column
             * \param[in] w0 First element of the position column
             * \param[in] x1 Second element of the x-rotation column
             * \param[in] y1 Second element of the y-rotation column
             * \param[in] z1 Second element of the z-rotation column
             * \param[in] w1 Second element of the position column
             * \param[in] x2 Third element of the x-rotation column
             * \param[in] y2 Third element of the y-rotation column
             * \param[in] z2 Third element of the z-rotation column
             * \param[in] w2 Third element of the position column
             * \param[in] x3 Fourth element of the x-rotation column
             * \param[in] y3 Fourth element of the y-rotation column
             * \param[in] z3 Fourth element of the z-rotation column
             * \param[in] w3 Fourth element of the position column
             */
            Matrix4x4(float x0, float y0, float z0, float w0,
                      float x1, float y1, float z1, float w1,
                      float x2, float y2, float z2, float w2,
                      float x3, float y3, float z3, float w3);

            /**
             * Creates a new 4x4 column-major matrix from an existing 3x3 column-major matrix.
             * \param[in] matrix
             */
            Matrix4x4(Matrix3x3 const& matrix);

            /**
             * Creates a new 4x4 column-major matrix.
             * \param[in] values 16-element float array of values in column-major order ({x0, x1, x2, x3, ..., w0, w1, w2, w3})
             */
            Matrix4x4(float* values);

            /**
             *
             */
            Matrix4x4(Vector4<float> const& col0, Vector4<float> const& col1, Vector4<float> const& col2, Vector4<float> const& col3);

            /**
             * Constructs a 4x4 matrix using a quaternion and position.
             *
             * \param[in] quat
             * \param[in] position
             */
            Matrix4x4(Quaternion const& quat, Vector3<float> const& position);

            /**
             * Constructs a 4x4 matrix using a set of euler angles and position.
             *
             * \param[in] euler    (pitch, yaw, roll)
             * \param[in] position
             */
            Matrix4x4(Vector3<float> const& euler, Vector3<float> const& position);

            /**
             *
             */
            Matrix4x4(Matrix4x4_Internal const& data);

            /**
             *
             */
            Matrix4x4(Matrix4x4 const& other);

            /**
             * Creates a new identity Matrix
             */
            Matrix4x4();

            /**
             *
             */
            ~Matrix4x4();

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            float operator[](uint32_t index);

            Matrix4x4& operator=(Matrix4x4 const& rhs);
            Matrix4x4& operator+=(Matrix4x4 const& rhs);
            Matrix4x4& operator-=(Matrix4x4 const& rhs);
            Matrix4x4& operator*=(Matrix4x4 const& rhs);
            Matrix4x4& operator*=(Vector4<float> const& rhs);
            Matrix4x4& operator*=(float rhs);

            //------------------------------------------------------------------------------
            // GETTERS / SETTERS
            //------------------------------------------------------------------------------
            
            /**
             * Sets an individual element of the matrix. 
             * Matrix elements are ordered as follows:
             *
             *     {rotX.x, rotX.y, rotX.z, rotX.w, rotY.x, rotY.y, rotY.z, rotY.w, rotZ.x, rotZ.y, rotZ.z, rotZ.w, pos.x, pos.y, pos.z, pos.w}
             *
             * or
             *
             *     00 04 08 12
             *     01 05 09 13
             *     02 06 10 14
             *     03 07 11 15
             *
             * \param[in] index Element index to set [0, 16)
             * \param[in] value Value to set the element to
             */
            void setElement(uint32_t index, float value);

            /**
             * Returns an individual element of the matrix. 
             * Matrix elements are ordered as follows:
             *
             *     {rotX.x, rotX.y, rotX.z, rotX.w, rotY.x, rotY.y, rotY.z, rotY.w, rotZ.x, rotZ.y, rotZ.z, rotZ.w, pos.x, pos.y, pos.z, pos.w}
             *
             * or
             *
             *     00 04 08 12
             *     01 05 09 13
             *     02 06 10 14
             *     03 07 11 15
             *
             * \param[in] index Element index to retrieve [0, 16)
             * \return Element value at the specified index.
             */
            float getElement(uint32_t index) const;
            
            /**
             * Sets the value of a single row of the matrix.
             * 
             * \param[in] index Row index [0,4)
             * \param[in] row   Vector of row values 
             */
            void setRow(uint32_t index, Vector4<float> const& row);

            /**
             *
             */
            void setRow(uint32_t index, Vector3<float> const& row);

            /**
             * Retrieves the value of a single row of the matrix.
             *
             * \param[in]  index Row index [0, 4)
             * \param[out] row   Vector to store the row values
             */
            void getRow(uint32_t index, Vector4<float>& row) const;

            /**
             * Sets the value of a single column of the matrix.
             * 
             * \param[in] index Column index [0,4)
             * \param[in] col   Vector of column values 
             */
            void setCol(uint32_t index, Vector4<float> const& col);

            /**
             *
             */
            void setCol(uint32_t index, Vector3<float> const& col);

            /**
             * Retrieves the value of a single column of the matrix.
             *
             * \param[in]  index Column index [0, 4)
             * \param[out] col   Vector to store the column values
             */
            void getCol(uint32_t index, Vector4<float>& col) const;

            /**
             * Sets the matrix data values from an array of floats.
             * \param[in] data An array of at least 16 floating point values (if more, only the first 16 are used).
             */
            void setData(float const* data);

            /**
             * Retrieves the matrix data values as an array of floats.
             * \param[out] data An array of at least 16 floating point values (if more, only the first 16 are filled).
             */
            void getData(float* data) const;

            //------------------------------------------------------------------------------
            // MISC OPERATIONS
            //------------------------------------------------------------------------------
            
            /**
             *
             */
            void invert();

            /**
             *
             */
            Matrix4x4 getInverse() const;

            /**
             *
             */
            float getDeterminant() const;

            /**
             *
             */
            Matrix4x4 getTranspose() const;

            //------------------------------------------------------------------------------
            // STATIC OPERATIONS
            //------------------------------------------------------------------------------

            /**
             *
             */
            static Matrix4x4 CreateTranslationMatrix(Matrix4x4 const& matrix, Vector3<float> const& translate);

            /**
             *
             */
            static Matrix4x4 CreateLookAtMatrix(Vector3<float> const& from, Vector3<float> const& to, Vector3<float> const& up);

            /**
             *
             */
            static Matrix4x4 CreateOrthographicMatrix(float xMin, float xMax, float yMin, float yMax, float nearClip, float farClip);

            /**
             *
             */
            static Matrix4x4 CreatePerspectiveMatrix(float fov, float aspectRatio, float nearClip, float farClip);

            //------------------------------------------------------------------------------
            // MISC
            //------------------------------------------------------------------------------
           
            /**
             * For internal use only.
             * Only modify this pointer if you want your application to crash.
             */
            Matrix4x4_Internal* getInternal() const;

        protected:

        private:

            Matrix4x4_Internal* m_Internal;
        };

        bool operator==(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
        bool operator!=(Matrix4x4 const& lhs, Matrix4x4 const& rhs);

        Matrix4x4 operator+(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
        Matrix4x4 operator-(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
        Matrix4x4 operator*(Matrix4x4 const& lhs, Matrix4x4 const& rhs);
        Matrix4x4 operator*(Matrix4x4 const& lhs, float rhs);
        
        Vector4<float> operator*(Matrix4x4 const& lhs, Vector4<float> const& rhs);

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