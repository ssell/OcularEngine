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
#ifndef __H__OCULAR_MATH_MATRIX_3X3_TEMP__H__
#define __H__OCULAR_MATH_MATRIX_3X3_TEMP__H__

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
        class Matrix4x4;
        class Quaternion;

        struct Matrix3x3_Internal;

        /**
         * \class Matrix3x3
         * \brief A 3x3 column-major float matrix
         *
         *     x.x y.x z.x
         *     x.y y.y z.y
         *     x.z y.z z.z
         *
         *     00 10 20
         *     01 11 21
         *     02 12 22
         *
         *     00 03 06
         *     01 04 07
         *     02 05 08
         */
        class Matrix3x3
        {
        public:

            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            /**
             * Creates a new 3x3 column-major matrix.
             *
             * \param[in] x0 First element of the x-rotation column
             * \param[in] y0 First element of the y-rotation column
             * \param[in] z0 First element of the z-rotation column
             * \param[in] x1 Second element of the x-rotation column
             * \param[in] y1 Second element of the y-rotation column
             * \param[in] z1 Second element of the z-rotation column
             * \param[in] x2 Third element of the x-rotation column
             * \param[in] y2 Third element of the y-rotation column
             * \param[in] z2 Third element of the z-rotation column
             */
            Matrix3x3(float x0, float y0, float z0,
                      float x1, float y1, float z1,
                      float x2, float y2, float z2);

            /**
             * Creates a new 3x3 column-major matrix.
             * \param[in] values 9-element float array of values in column-major order ({x0, x1, x2, ..., z2, z3})
             */
            Matrix3x3(float* values);

            /**
             *
             */
            Matrix3x3(Matrix3x3_Internal const& data);

            /**
             *
             */
            Matrix3x3(Matrix3x3 const& other);

            /**
             * Creates a new identity Matrix
             */
            Matrix3x3();

            /**
             *
             */
            ~Matrix3x3();

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            float operator[](uint32_t index);

            Matrix3x3& operator=(Matrix3x3 const& rhs);
            Matrix3x3& operator+=(Matrix3x3 const& rhs);
            Matrix3x3& operator-=(Matrix3x3 const& rhs);
            Matrix3x3& operator*=(Matrix3x3 const& rhs);
            Matrix3x3& operator*=(float rhs);
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
            Matrix3x3 getInverse() const;

            /**
             *
             */
            Matrix3x3 getTranspose() const;

            //------------------------------------------------------------------------------
            // STATIC OPERATIONS
            //------------------------------------------------------------------------------

            //------------------------------------------------------------------------------
            // MISC
            //------------------------------------------------------------------------------
            
            /**
             * For internal use only.
             * Only modify this pointer if you want your application to crash.
             */
            Matrix3x3_Internal* getInternal() const;

        protected:

            

        private:

            Matrix3x3_Internal* m_Internal;
        };

        bool operator==(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
        bool operator!=(Matrix3x3 const& lhs, Matrix3x3 const& rhs);

        Matrix3x3 operator+(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
        Matrix3x3 operator-(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
        Matrix3x3 operator*(Matrix3x3 const& lhs, Matrix3x3 const& rhs);
        Matrix3x3 operator*(Matrix3x3 const& lhs, float rhs);
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