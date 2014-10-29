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

#include "Matrix3x3.hpp"
#include "Vector3.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
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
            Matrix4x4(T const p00, T const p01, T const p02, T const p03,
                T const p10, T const p11, T const p12, T const p13,
                T const p20, T const p21, T const p22, T const p23,
                T const p30, T const p31, T const p32, T const p33)
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

            Matrix4x4(Matrix3x3<T> const matrix)
            {

            }

            Matrix4x4()
            {
                setIdentity();
            }

            ~Matrix()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------


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
            T getElement(unsigned const row, unsigned const column)
            {
                T value = static_cast<T>(0);

                if((row < 4) && (column < 4))
                {
                    value = m_Contents[(row * 4) + column];
                }

                return value;
            }

            /**
            * \return The element at the specified index [0-15]
            */
            T getElement(unsigned const index)
            {
                T value = static_cast<T>(0);

                if(index < 16)
                {
                    value = m_Contents[index];
                }

                return value;
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
            void setXRotation(T const x, T const y, T const z)
            {
                m_Contents[0] = x;
                m_Contents[1] = y;
                m_Contents[2] = z;
            }

            /**
             * Sets the Y-Axis rotation vector.
             *
             * \param[in] x X component of the rotation vector
             * \param[in] y Y component of the rotation vector
             * \param[in] z Z component of the rotation vector
             */
            void setYRotation(T const x, T const y, T const z)
            {
                m_Contents[4] = x;
                m_Contents[5] = y;
                m_Contents[6] = z;
            }

            /**
             * Sets the Z-Axis rotation vector.
             *
             * \param[in] x X component of the rotation vector
             * \param[in] y Y component of the rotation vector
             * \param[in] z Z component of the rotation vector
             */
            void setZRotation(T const x, T const y, T const z)
            {
                m_Contents[8]  = x;
                m_Contents[9]  = y;
                m_Contents[10] = z;
            }

            /**
             * Sets the position vector.
             *
             * \param[in] x X component of the position vector
             * \param[in] y Y component of the position vector
             * \param[in] z Z component of the position vector
             */
            void setPosition(T const x, T const y, T const z)
            {
                m_Contents[12] = x;
                m_Contents[13] = y;
                m_Contents[14] = z;
            }

            /**
             * Sets the value of the element at the specified row/column position.
             *
             * \param[in] row    Row of the element [0,3]
             * \param[in] column Column of the element [0,3]
             * \param[in] value  Value to set
             */
            void setElement(unsigned const row, unsigned const column, T const value)
            {
                if((row < 4) && (column < 4))
                {
                    m_Contents[(row * 4) + column] = value;
                }
            }

            /**
             * Sets the value of the element at the specified index.
             *
             * \param[in] index Index of the element [0,15]
             * \param[in] value Value to set
             */
            void setElement(unsigned const index, T const value)
            {
                if(index < 16)
                {
                    m_Contents[index] = value;
                }
            }

            //------------------------------------------------------------------------------
            // OPERATIONS
            //------------------------------------------------------------------------------

        protected:

        private:

            T m_Contents[16];
        };

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