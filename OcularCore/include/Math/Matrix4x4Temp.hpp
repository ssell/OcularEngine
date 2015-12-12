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
#include "Math/Matrix3x3Temp.hpp"

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
        class Vector3;
        class Vector4;
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
            Matrix4x4& operator*=(float rhs);
            //Matrix4x4& operator*=(Vector4 const& rhs);

            //------------------------------------------------------------------------------
            // GETTERS / SETTERS
            //------------------------------------------------------------------------------

            //------------------------------------------------------------------------------
            // MISC OPERATIONS
            //------------------------------------------------------------------------------

            /**
             *
             */
            float getDeterminant() const;

            /**
             *
             */
            Matrix4x4 getInverse() const;

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
            static Matrix4x4 CreateOrthographicMatrix(float xMin, float xMax, float yMin, float yMax, float nearClip, float farClip);

            /**
             *
             */
            static Matrix4x4 CreatePerspectiveMatrix(float fov, float aspectRatio, float nearClip, float farClip);

            //------------------------------------------------------------------------------
            // MISC
            //------------------------------------------------------------------------------

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
        //Matrix4x4 operator*(Matrix4x4 const& lhs, Vector4 const& rhs);

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