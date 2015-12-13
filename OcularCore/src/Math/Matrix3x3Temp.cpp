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

#include "Math/Matrix3x3Temp.hpp"
#include "Math/MathInternal.hpp"
#include "Math/QuaternionTemp.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Matrix3x3::Matrix3x3(float const x0, float const y0, float const z0,
                             float const x1, float const y1, float const z1,
                             float const x2, float const y2, float const z2)
        {
            m_Internal = new Matrix3x3_Internal(
                glm::mat3x3(x0, y0, z0,
                            x1, y1, z1,
                            x2, y2, z2));
        }

        Matrix3x3::Matrix3x3(float* values)
        {
            m_Internal = new Matrix3x3_Internal();

            if(values)
            {
                m_Internal->matrix =
                    glm::mat3x3(values[0], values[3], values[6],
                                values[1], values[4], values[7],
                                values[2], values[5], values[8]);
            }
        }

        Matrix3x3::Matrix3x3(Quaternion const& quat)
        {
            m_Internal = new Matrix3x3_Internal(glm::mat3_cast(quat.getInternal()->quat));
        }

        Matrix3x3::Matrix3x3(Vector3<float> const& euler)
        {
            m_Internal = new Matrix3x3_Internal(glm::mat3_cast(glm::quat(euler.x, euler.y, euler.z)));
        }

        Matrix3x3::Matrix3x3(Matrix3x3_Internal const& data)
        {
            m_Internal = new Matrix3x3_Internal(data.matrix);
        }

        Matrix3x3::Matrix3x3(Matrix3x3 const& other)
        {
            m_Internal = new Matrix3x3_Internal(other.m_Internal->matrix);
        }

        Matrix3x3::Matrix3x3()
        {
            m_Internal = new Matrix3x3_Internal();
        }

        Matrix3x3::~Matrix3x3()
        {
            if(m_Internal)
            {
                delete m_Internal;
                m_Internal = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------
        // OPERATORS
        //----------------------------------------------------------------

        float Matrix3x3::operator[](uint32_t index)
        {
            float result = 0.0f;

            if(index < 9)
            {
                result = m_Internal->matrix[(index / 3)][(index % 3)];
            }

            return result;
        }

        Matrix3x3& Matrix3x3::operator=(Matrix3x3 const& rhs)
        {
            m_Internal->matrix = rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix3x3& Matrix3x3::operator+=(Matrix3x3 const& rhs)
        {
            m_Internal->matrix += rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix3x3& Matrix3x3::operator-=(Matrix3x3 const& rhs)
        {
            m_Internal->matrix -= rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix3x3& Matrix3x3::operator*=(Matrix3x3 const& rhs)
        {
            m_Internal->matrix *= rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix3x3& Matrix3x3::operator*=(Vector4<float> const& rhs)
        {
            m_Internal->matrix *= glm::vec4(rhs.x, rhs.y, rhs.z, rhs.w);
            return (*this);
        }

        Matrix3x3& Matrix3x3::operator*=(float const rhs)
        {
            m_Internal->matrix *= rhs;
            return (*this);
        }

        bool operator==(Matrix3x3 const& lhs, Matrix3x3 const& rhs)
        {
            return (lhs.getInternal()->matrix == rhs.getInternal()->matrix);
        }

        bool operator!=(Matrix3x3 const& lhs, Matrix3x3 const& rhs)
        {
            return (lhs.getInternal()->matrix != rhs.getInternal()->matrix);
        }

        Matrix3x3 operator+(Matrix3x3 const& lhs, Matrix3x3 const& rhs)
        {
            return Matrix3x3(Matrix3x3_Internal(lhs.getInternal()->matrix + rhs.getInternal()->matrix));
        }

        Matrix3x3 operator-(Matrix3x3 const& lhs, Matrix3x3 const& rhs)
        {
            return Matrix3x3(Matrix3x3_Internal(lhs.getInternal()->matrix - rhs.getInternal()->matrix));
        }

        Matrix3x3 operator*(Matrix3x3 const& lhs, Matrix3x3 const& rhs)
        {
            return Matrix3x3(Matrix3x3_Internal(lhs.getInternal()->matrix * rhs.getInternal()->matrix));
        }

        Matrix3x3 operator*(Matrix3x3 const& lhs, Vector4<float> const& rhs)
        {
            return Matrix3x3(Matrix3x3_Internal(lhs.getInternal()->matrix * glm::vec4(rhs.x, rhs.y, rhs.z, rhs.w)));
        }

        Matrix3x3 operator*(Matrix3x3 const& lhs, float const rhs)
        {
            return Matrix3x3(Matrix3x3_Internal(lhs.getInternal()->matrix * rhs));
        }

        //----------------------------------------------------------------
        // GETTERS / SETTERS
        //----------------------------------------------------------------

        void Matrix3x3::setElement(uint32_t const index, float const value)
        {
            if(index < 9)
            {
                m_Internal->matrix[(index / 3)][(index % 3)] = value;
            }
        }

        float Matrix3x3::getElement(uint32_t const index) const
        {
            float result = 0.0f;

            if(index < 9)
            {
                result = m_Internal->matrix[(index / 3)][(index % 3)];
            }

            return result;
        }

        void Matrix3x3::setRow(uint32_t const index, Vector3<float> const& row)
        {
            if(index < 3)
            {
                m_Internal->matrix[0][index] = row[0];
                m_Internal->matrix[1][index] = row[1];
                m_Internal->matrix[2][index] = row[2];
            }
        }

        void Matrix3x3::getRow(uint32_t const index, Vector3<float>& row) const
        {
            if(index < 3)
            {
                row[0] = m_Internal->matrix[0][index];
                row[1] = m_Internal->matrix[1][index];
                row[2] = m_Internal->matrix[2][index];
            }
        }

        void Matrix3x3::setCol(uint32_t const index, Vector3<float> const& col)
        {
            if(index < 3)
            {
                m_Internal->matrix[index][0] = col[0];
                m_Internal->matrix[index][1] = col[1];
                m_Internal->matrix[index][2] = col[2];
            }
        }

        void Matrix3x3::getCol(uint32_t const index, Vector3<float>& col) const
        {
            if(index < 3)
            {
                col[0] = m_Internal->matrix[index][0];
                col[1] = m_Internal->matrix[index][1];
                col[2] = m_Internal->matrix[index][2];
            }
        }

        void Matrix3x3::setData(float const* data)
        {
            m_Internal->matrix[0][0] = data[0]; m_Internal->matrix[1][0] = data[3]; m_Internal->matrix[2][0] = data[6];
            m_Internal->matrix[0][1] = data[1]; m_Internal->matrix[1][1] = data[4]; m_Internal->matrix[2][1] = data[7];
            m_Internal->matrix[0][2] = data[2]; m_Internal->matrix[1][2] = data[5]; m_Internal->matrix[2][2] = data[8];
        }

        void Matrix3x3::getData(float* data) const
        {
            data[0] = m_Internal->matrix[0][0]; data[3] = m_Internal->matrix[1][0]; data[6] = m_Internal->matrix[2][0];
            data[1] = m_Internal->matrix[0][1]; data[4] = m_Internal->matrix[1][1]; data[7] = m_Internal->matrix[2][1];
            data[2] = m_Internal->matrix[0][2]; data[5] = m_Internal->matrix[1][2]; data[8] = m_Internal->matrix[2][2];
        }

        //----------------------------------------------------------------
        // MISC OPERATIONS
        //----------------------------------------------------------------

        float Matrix3x3::getDeterminant() const
        {
            return glm::determinant(m_Internal->matrix);
        }

        Matrix3x3 Matrix3x3::getInverse() const
        {
            return Matrix3x3(Matrix3x3_Internal(glm::inverse(m_Internal->matrix)));
        }

        Matrix3x3 Matrix3x3::getTranspose() const
        {
            return Matrix3x3(Matrix3x3_Internal(glm::transpose(m_Internal->matrix)));
        }

        //----------------------------------------------------------------
        // STATIC OPERATIONS
        //----------------------------------------------------------------

        //----------------------------------------------------------------
        // MISC
        //----------------------------------------------------------------

        Matrix3x3_Internal* Matrix3x3::getInternal() const
        {
            return m_Internal;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}