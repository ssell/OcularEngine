/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Utilities/Types.hpp"
#include <cstdint>

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

        class Euler;
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
            Matrix3x3(Vector3<float> const& col0, Vector3<float> const& col1, Vector3<float> const& col2);

            /**
             * Constructs a 3x3 rotational matrix from a quaternion.
             * \param[in] quat
             */
            Matrix3x3(Quaternion const& quat);

            /**
             * Constructs a 3x3 rotational matrix from a set of Euler angles.
             * \param[in] euler
             */
            Matrix3x3(Euler const& euler);

            /**
             * Constructs a 3x3 rotational matrix from a set of euler angles.
             * \param[in] euler (pitch, yaw, roll)
             */
            Matrix3x3(Vector3<float> const& euler);

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
            Matrix3x3& operator*=(Vector3<float> const& rhs);
            Matrix3x3& operator*=(float rhs);

            //------------------------------------------------------------------------------
            // GETTERS / SETTERS
            //------------------------------------------------------------------------------

            /**
             * Sets an individual element of the matrix. 
             * Matrix elements are ordered as follows:
             *
             *     {rotX.x, rotX.y, rotX.z, rotY.x, rotY.y, rotY.z, rotZ.x, rotZ.y, rotZ.z}
             *
             * or
             *
             *     0 3 6
             *     1 4 7
             *     2 5 8
             *
             * \param[in] index Element index to set [0, 9)
             * \param[in] value Value to set the element to
             */
            void setElement(uint32_t index, float value);

            /**
             * Returns an individual element of the matrix. 
             * Matrix elements are ordered as follows:
             *
             *     {rotX.x, rotX.y, rotX.z, rotY.x, rotY.y, rotY.z, rotZ.x, rotZ.y, rotZ.z}
             *
             * or
             *
             *     0 3 6
             *     1 4 7
             *     2 5 8
             *
             * \param[in] index Element index to retrieve.
             * \return Element value at the specified index.
             */
            float getElement(uint32_t index) const;
            
            /**
             * Sets the value of a single row of the matrix.
             * 
             * \param[in] index Row index [0,3)
             * \param[in] row   Vector of row values 
             */
            void setRow(uint32_t index, Vector3<float> const& row);

            /**
             * Retrieves the value of a single row of the matrix.
             *
             * \param[in]  index Row index [0, 3)
             * \param[out] row   Vector to store the row values
             */
            void getRow(uint32_t index, Vector3<float>& row) const;
            
            /**
             *
             */
            Vector3<float> getRow(uint32_t index) const;

            /**
             * Sets the value of a single column of the matrix.
             * 
             * \param[in] index Column index [0,3)
             * \param[in] col   Vector of column values 
             */
            void setCol(uint32_t index, Vector3<float> const& col);

            /**
             * Retrieves the value of a single column of the matrix.
             *
             * \param[in]  index Column index [0, 3)
             * \param[out] col   Vector to store the column values
             */
            void getCol(uint32_t index, Vector3<float>& col) const;
            
            /**
             *
             */
            Vector3<float> getCol(uint32_t index) const;

            /**
             * Sets the matrix data values from an array of floats.
             * \param[in] data An array of at least 9 floating point values (if more, only the first 9 are used).
             */
            void setData(float const* data);

            /**
             * Retrieves the matrix data values as an array of floats.
             * \param[out] data An array of at least 9 floating point values (if more, only the first 9 are filled).
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
            Matrix3x3 getInverse() const;

            /**
             *
             */
            float getDeterminant() const;

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
        
        Vector3<float> operator*(Matrix3x3 const& lhs, Vector3<float> const& rhs);

    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

OCULAR_REGISTER_TYPE_CUSTOM(Ocular::Math::Matrix3x3, "Matrix3x3");

//------------------------------------------------------------------------------------------

#endif