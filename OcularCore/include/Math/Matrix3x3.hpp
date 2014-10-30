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
#ifndef __H__OCULAR_MATH_MATRIX_3X3__H__
#define __H__OCULAR_MATH_MATRIX_3X3__H__

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
         * \class Matrix3x3
         */
        template<typename T>
        class Matrix3x3
        {
        public:

            Matrix3x3(T const p00, T const p01, T const p02,
                      T const p10, T const p11, T const p12,
                      T const p20, T const p21, T const p22)
            {
                m_Contents[0] = p00;
                m_Contents[1] = p01;
                m_Contents[2] = p02;
                m_Contents[3] = p10;
                m_Contents[4] = p11;
                m_Contents[5] = p12;
                m_Contents[6] = p20;
                m_Contents[7] = p21;
                m_Contents[8] = p22;
            }

            Matrix3x3()
            {

            }

            ~Matrix3x3()
            {

            }

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------
            
            T& operator[](unsigned index)
            {
                if(index > 8)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Content[index];
            }

            const T& operator[](unsigned index) const
            {
                if(index > 8)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Access");
                }

                return m_Content[index];
            }

            Matrix3x3<T>& operator=(Matrix3x3<T> const rhs)
            {
                for(unsigned i = 0; i < 9; i++)
                {
                    m_Contents[i] = rhs[i];
                }

                return (*this);
            }

            bool operator==(Matrix3x3<T> const rhs)
            {
                // TODO : need smart compare for floating point
                return (m_Content[0] == rhs[0]) && (m_Content[1] == rhs[1]) && (m_Content[2] == rhs[2]) && 
                       (m_Content[3] == rhs[3]) && (m_Content[4] == rhs[4]) && (m_Content[5] == rhs[5]) &&
                       (m_Content[6] == rhs[6]) && (m_Content[7] == rhs[7]) && (m_Content[8] == rhs[8]));
            }

            bool operator!=(Matrix3x3<T> const rhs)
            {
                return !(*this == rhs);
            }

            Matrix3x3<T>& operator+(Matrix3x3<T> const rhs)
            {
                Matrix3x3<T> result(m_Content[0] + rhs[0], m_Content[1] + rhs[1],
                                    m_Content[2] + rhs[2], m_Content[3] + rhs[3],
                                    m_Content[4] + rhs[4], m_Content[5] + rhs[5],
                                    m_Content[6] + rhs[6], m_Content[7] + rhs[7],
                                    m_Content[8] + rhs[8]);

                return result;
            }

            Matrix3x3<T>& operator+=(Matrix3x3<T> const rhs)
            {
                for(unsigned i = 0; i < 9; i++)
                {
                    m_Contents[i] += rhs[i];
                }

                return (*this);
            }

            Matrix3x3<T>& operator-(Matrix3x3<T> const rhs)
            {
                Matrix3x3<T> result(m_Content[0] - rhs[0], m_Content[1] - rhs[1],
                                    m_Content[2] - rhs[2], m_Content[3] - rhs[3],
                                    m_Content[4] - rhs[4], m_Content[5] - rhs[5],
                                    m_Content[6] - rhs[6], m_Content[7] - rhs[7],
                                    m_Content[8] - rhs[8])

                return result;
            }

            Matrix3x3<T>& operator-=(Matrix3x3<T> const rhs)
            {
                for(unsigned i = 0; i < 9; i++)
                {
                    m_Contents[i] -= rhs[i];
                }

                return (*this);
            }

            Matrix3x3<T>& operator*(Matrix3x3<T> const rhs)
            {
                Matrix3x3<T> result;

                for(unsigned i = 0; i < 9; i++)
                {
                    result[i] = m_Contents[i] * rhs;
                }

                return result;
            }

            Matrix3x3<T>& operator*(T const rhs)
            {
                Matrix3x3<T> result(m_Content[0] * rhs[0], m_Content[1] * rhs[1],
                                    m_Content[2] * rhs[2], m_Content[3] * rhs[3],
                                    m_Content[4] * rhs[4], m_Content[5] * rhs[5],
                                    m_Content[6] * rhs[6], m_Content[7] * rhs[7],
                                    m_Content[8] * rhs[8]);

                return result;
            }

            Matrix3x3<T>& operator*(Vector3<T> const rhs)
            {
                Matrix3x3<T> result;

                for(unsigned i = 0; i < 2; i++)
                {
                    result[(i * 3) + 0] = m_Contents[(i * 3) + 0] * rhs.x;
                    result[(i * 3) + 1] = m_Contents[(i * 3) + 1] * rhs.y;
                    result[(i * 3) + 2] = m_Contents[(i * 3) + 2] * rhs.z;
                }

                return result;
            }

            Matrix3x3<T>& operator*=(Matrix3x3<T> const rhs)
            {
                for(unsigned i = 0; i < 9; i++)
                {
                    m_Contents[i] *= rhs[i];
                }

                return (*this);
            }

            Matrix3x3<T>& operator*=(T const rhs)
            {
                for(unsigned i = 0; i < 9; i++)
                {
                    m_Contents[i] *= rhs;
                }

                return (*this);
            }

            Matrix3x3<T>& operator*=(Vector3<T> const rhs)
            {
                for(unsigned i = 0; i < 3; i++)
                {
                    m_Contents[(i * 3) + 0] *= rhs.x;
                    m_Contents[(i * 3) + 1] *= rhs.y;
                    m_Contents[(i * 3) + 2] *= rhs.z;
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
                return Vector3<T>(m_Contents[3], m_Contents[4], m_Contents[5]);
            }

            /**
             * \return The Z-Axis rotation vector
             */
            Vector3<T> getZRotation()
            {
                return Vector3<T>(m_Contents[6], m_Contents[7], m_Contents[8]);
            }

            /**
             * \return The element at the specified row [0-2] and colum [0-2] combination
             */
            T getElement(unsigned const row, unsigned const column)
            {
                if(row > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Row Access");
                }

                if(column > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Column Access");
                }

                return m_Contents[(row * 3) + column];
            }

            /**
             * \return The element at the specified index [0-8]
             */
            T getElement(unsigned const index)
            {
                if(index > 8)
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
                m_Contents[0] = static_cast<T>(1);
                m_Contents[1] = static_cast<T>(0);
                m_Contents[2] = static_cast<T>(0);

                // Y-Axis Rotation
                m_Contents[4] = static_cast<T>(0);
                m_Contents[5] = static_cast<T>(1);
                m_Contents[6] = static_cast<T>(0);

                // Z-Axis Rotation
                m_Contents[8] = static_cast<T>(0);
                m_Contents[9] = static_cast<T>(0);
                m_Contents[10] = static_cast<T>(1);
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
             * Sets the X-Axis rotation vector.
             *
             * \param[in] vec The X-Axis rotation vector
             */
            void setXRotation(Vector3<T> const vec)
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
            void setYRotation(T const x, T const y, T const z)
            {
                m_Contents[3] = x;
                m_Contents[4] = y;
                m_Contents[5] = z;
            }

            /**
             * Sets the Y-Axis rotation vector.
             *
             * \param[in] vec The Y-Axis rotation vector
             */
            void setYRotation(Vector3<T> const vec)
            {
                m_Contents[3] = vec.x;
                m_Contents[4] = vec.y;
                m_Contents[5] = vec.z;
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
                m_Contents[6] = x;
                m_Contents[7] = y;
                m_Contents[8] = z;
            }

            /**
             * Sets the Z-Axis rotation vector.
             *
             * \param[in] vec The Z-Axis rotation vector
             */
            void setZRotation(Vector3<T> const vec)
            {
                m_Contents[6] = vec.x;
                m_Contents[7] = vec.y;
                m_Contents[8] = vec.z;
            }
            
            /**
             * Sets the value of the element at the specified row/column position.
             *
             * \param[in] row    Row of the element [0,2]
             * \param[in] column Column of the element [0,2]
             * \param[in] value  Value to set
             */
            void setElement(unsigned const row, unsigned const column, T const value)
            {
                if(row > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Row Access");
                }

                if(column > 2)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Column Access");
                }

                m_Contents[(row * 3) + column] = value;
            }

            /**
             * Sets the value of the element at the specified index.
             *
             * \param[in] index Index of the element [0,8]
             * \param[in] value Value to set
             */
            void setElement(unsigned const index, T const value)
            {
                if(index > 8)
                {
                    THROW_EXCEPTION("Out-Of-Bounds Matrix Index Access");
                }

                m_Contents[index] = value;
            }

            //------------------------------------------------------------------------------
            // OPERATIONS
            //------------------------------------------------------------------------------

        protected:

        private:

            T m_Contents[9];
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