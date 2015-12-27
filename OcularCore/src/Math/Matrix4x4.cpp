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

#include "Math/Matrix4x4.hpp"
#include "Math/MathInternal.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Matrix3x3.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Matrix4x4::Matrix4x4(float const x0, float const y0, float const z0, float const w0,
                             float const x1, float const y1, float const z1, float const w1,
                             float const x2, float const y2, float const z2, float const w2,
                             float const x3, float const y3, float const z3, float const w3)
        {
            m_Internal = new Matrix4x4_Internal(
                glm::mat4x4(x0, y0, z0, w0,
                            x1, y1, z1, w1,
                            x2, y2, z2, w2,
                            x3, y3, z3, w3));
        }

        Matrix4x4::Matrix4x4(Matrix3x3 const& matrix)
        {
            m_Internal = new Matrix4x4_Internal(glm::mat4x4(matrix.getInternal()->matrix));
        }

        Matrix4x4::Matrix4x4(float* values)
        {
            m_Internal = new Matrix4x4_Internal();

            if(values)
            {
                m_Internal->matrix =
                    glm::mat4x4(values[0], values[4], values[8],  values[12],
                                values[1], values[5], values[9],  values[13],
                                values[2], values[6], values[10], values[14],
                                values[3], values[7], values[11], values[15]);
            }
        }

        Matrix4x4::Matrix4x4(Vector4<float> const& col0, Vector4<float> const& col1, Vector4<float> const& col2, Vector4<float> const& col3)
        {
            m_Internal = new Matrix4x4_Internal(
                glm::mat4x4(col0.x, col1.x, col2.x, col3.x,
                            col0.y, col1.y, col2.y, col3.y,
                            col0.z, col1.z, col2.z, col3.z,
                            col0.w, col1.w, col2.w, col3.w));
        }

        Matrix4x4::Matrix4x4(Vector3<float> const& position, Quaternion const& rotation)
        {
            m_Internal = new Matrix4x4_Internal(glm::mat4x4(glm::mat3_cast(rotation.getInternal()->quat)));
            
            m_Internal->matrix[3][0] = position[0];
            m_Internal->matrix[3][1] = position[1];
            m_Internal->matrix[3][2] = position[2];
        }

        Matrix4x4::Matrix4x4(Vector3<float> const& position, Vector3<float> const& eulerRotation)
        {
            m_Internal = new Matrix4x4_Internal(glm::mat4x4(glm::mat3_cast(glm::quat(glm::vec3(eulerRotation.x, eulerRotation.y, eulerRotation.z)))));
            
            m_Internal->matrix[3][0] = position[0];
            m_Internal->matrix[3][1] = position[1];
            m_Internal->matrix[3][2] = position[2];
        }

        Matrix4x4::Matrix4x4(Vector3<float> const& position, Quaternion const& rotation, Vector3<float> const& scale)
        {
            m_Internal = new Matrix4x4_Internal(glm::mat4x4(glm::mat3_cast(rotation.getInternal()->quat)));

            m_Internal->matrix[3][0] = position[0];
            m_Internal->matrix[3][1] = position[1];
            m_Internal->matrix[3][2] = position[2];

            const Matrix4x4 scaleMatrix = CreateScaleMatrix(scale);

            (*this) *= scaleMatrix;
        }

        Matrix4x4::Matrix4x4(Matrix4x4_Internal const& data)
        {
            m_Internal = new Matrix4x4_Internal(data.matrix);
        }

        Matrix4x4::Matrix4x4(Matrix4x4 const& other)
        {
            m_Internal = new Matrix4x4_Internal(other.m_Internal->matrix);
        }

        Matrix4x4::Matrix4x4()
        {
            m_Internal = new Matrix4x4_Internal();
        }

        Matrix4x4::~Matrix4x4()
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

        float Matrix4x4::operator[](uint32_t index)
        {
            //[index % 4][index / 4] returns as column major
            //[index / 4][index % 4] returns as row major
            return m_Internal->matrix[(index % 4)][(index / 4)];
        }

        Matrix4x4& Matrix4x4::operator=(Matrix4x4 const& rhs)
        {
            m_Internal->matrix = rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix4x4& Matrix4x4::operator+=(Matrix4x4 const& rhs)
        {
            m_Internal->matrix += rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix4x4& Matrix4x4::operator-=(Matrix4x4 const& rhs)
        {
            m_Internal->matrix -= rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix4x4& Matrix4x4::operator*=(Matrix4x4 const& rhs)
        {
            m_Internal->matrix *= rhs.m_Internal->matrix;
            return (*this);
        }

        Matrix4x4& Matrix4x4::operator*=(float const rhs)
        {
            m_Internal->matrix *= rhs;
            return (*this);
        }

        Matrix4x4& Matrix4x4::operator*=(Vector4<float> const& rhs)
        {
            m_Internal->matrix *= glm::vec4(rhs.x, rhs.y, rhs.z, rhs.w);
            return (*this);
        }

        bool operator==(Matrix4x4 const& lhs, Matrix4x4 const& rhs)
        {
            return (lhs.getInternal()->matrix == rhs.getInternal()->matrix);
        }

        bool operator!=(Matrix4x4 const& lhs, Matrix4x4 const& rhs)
        {
            return (lhs.getInternal()->matrix != rhs.getInternal()->matrix);
        }

        Matrix4x4 operator+(Matrix4x4 const& lhs, Matrix4x4 const& rhs)
        {
            return Matrix4x4(Matrix4x4_Internal(lhs.getInternal()->matrix + rhs.getInternal()->matrix));
        }

        Matrix4x4 operator-(Matrix4x4 const& lhs, Matrix4x4 const& rhs)
        {
            return Matrix4x4(Matrix4x4_Internal(lhs.getInternal()->matrix - rhs.getInternal()->matrix));
        }

        Matrix4x4 operator*(Matrix4x4 const& lhs, Matrix4x4 const& rhs)
        {
            return Matrix4x4(Matrix4x4_Internal(lhs.getInternal()->matrix * rhs.getInternal()->matrix));
        }

        Matrix4x4 operator*(Matrix4x4 const& lhs, float const rhs)
        {
            return Matrix4x4(Matrix4x4_Internal(lhs.getInternal()->matrix * rhs));
        }

        Vector4<float> operator*(Matrix4x4 const& lhs, Vector4<float> const& rhs)
        {
            glm::vec4 vec(rhs.x, rhs.y, rhs.z, rhs.w);
            vec = lhs.getInternal()->matrix * vec;

            return Vector4<float>(vec.x, vec.y, vec.z, vec.w);
        }

        //----------------------------------------------------------------
        // GETTERS / SETTERS
        //----------------------------------------------------------------

        void Matrix4x4::setElement(uint32_t const index, float const value)
        {
            if(index < 16)
            {
                m_Internal->matrix[(index % 4)][(index / 4)] = value;
            }
        }

        float Matrix4x4::getElement(uint32_t const index) const
        {
            float result = 0.0f;

            if(index < 16)
            {
                //[index % 4][index / 4] returns as column major
                //[index / 4][index % 4] returns as row major
                result = m_Internal->matrix[(index % 4)][(index / 4)];
            }

            return result;
        }

        void Matrix4x4::setRow(uint32_t const index, Vector4<float> const& row)
        {
            if(index < 4)
            {
                m_Internal->matrix[0][index] = row[0];
                m_Internal->matrix[1][index] = row[1];
                m_Internal->matrix[2][index] = row[2];
                m_Internal->matrix[3][index] = row[3];
            }
        }

        void Matrix4x4::setRow(uint32_t const index, Vector3<float> const& row)
        {
            if(index < 4)
            {
                m_Internal->matrix[0][index] = row[0];
                m_Internal->matrix[1][index] = row[1];
                m_Internal->matrix[2][index] = row[2];
            }
        }

        void Matrix4x4::getRow(uint32_t const index, Vector4<float>& row) const
        {
            if(index < 4)
            {
                row[0] = m_Internal->matrix[0][index];
                row[1] = m_Internal->matrix[1][index];
                row[2] = m_Internal->matrix[2][index];
                row[3] = m_Internal->matrix[3][index];
            }
        }

        void Matrix4x4::setCol(uint32_t const index, Vector4<float> const& col)
        {
            if(index < 4)
            {
                m_Internal->matrix[index][0] = col[0];
                m_Internal->matrix[index][1] = col[1];
                m_Internal->matrix[index][2] = col[2];
                m_Internal->matrix[index][3] = col[3];
            }
        }

        void Matrix4x4::setCol(uint32_t const index, Vector3<float> const& col)
        {
            if(index < 4)
            {
                m_Internal->matrix[index][0] = col[0];
                m_Internal->matrix[index][1] = col[1];
                m_Internal->matrix[index][2] = col[2];
            }
        }

        void Matrix4x4::getCol(uint32_t const index, Vector4<float>& col) const
        {
            if(index < 4)
            {
                col[0] = m_Internal->matrix[index][0];
                col[1] = m_Internal->matrix[index][1];
                col[2] = m_Internal->matrix[index][2];
                col[3] = m_Internal->matrix[index][3];
            }
        }

        void Matrix4x4::setData(float const* data)
        {
            m_Internal->matrix[0][0] = data[0]; m_Internal->matrix[1][0] = data[4]; m_Internal->matrix[2][0] = data[8];  m_Internal->matrix[3][0] = data[12];
            m_Internal->matrix[0][1] = data[1]; m_Internal->matrix[1][1] = data[5]; m_Internal->matrix[2][1] = data[9];  m_Internal->matrix[3][1] = data[13];
            m_Internal->matrix[0][2] = data[2]; m_Internal->matrix[1][2] = data[6]; m_Internal->matrix[2][2] = data[10]; m_Internal->matrix[3][2] = data[14];
            m_Internal->matrix[0][3] = data[3]; m_Internal->matrix[1][3] = data[7]; m_Internal->matrix[2][3] = data[11]; m_Internal->matrix[3][3] = data[15];
        }

        void Matrix4x4::getData(float* data) const
        {
            data[0] = m_Internal->matrix[0][0]; data[4] = m_Internal->matrix[1][0]; data[8]  = m_Internal->matrix[2][0]; data[12] = m_Internal->matrix[3][0];
            data[1] = m_Internal->matrix[0][1]; data[5] = m_Internal->matrix[1][1]; data[9]  = m_Internal->matrix[2][1]; data[13] = m_Internal->matrix[3][1];
            data[2] = m_Internal->matrix[0][2]; data[6] = m_Internal->matrix[1][2]; data[10] = m_Internal->matrix[2][2]; data[14] = m_Internal->matrix[3][2];
            data[3] = m_Internal->matrix[0][3]; data[7] = m_Internal->matrix[1][3]; data[11] = m_Internal->matrix[2][3]; data[15] = m_Internal->matrix[3][3];
        }

        //----------------------------------------------------------------
        // MISC OPERATIONS
        //----------------------------------------------------------------

        void Matrix4x4::invert()
        {
            m_Internal->matrix = glm::inverse(m_Internal->matrix);
        }

        Matrix4x4 Matrix4x4::getInverse() const
        {
            return Matrix4x4(Matrix4x4_Internal(glm::inverse(m_Internal->matrix)));
        }

        float Matrix4x4::getDeterminant() const
        {
            return glm::determinant(m_Internal->matrix);
        }

        Matrix4x4 Matrix4x4::getTranspose() const
        {
            return Matrix4x4(Matrix4x4_Internal(glm::transpose(m_Internal->matrix)));
        }

        //----------------------------------------------------------------
        // STATIC OPERATIONS
        //----------------------------------------------------------------

        Matrix4x4 Matrix4x4::CreateTranslationMatrix(Vector3<float> const& translate, Matrix4x4 const& matrix)
        {
            return Matrix4x4(Matrix4x4_Internal(glm::translate(matrix.getInternal()->matrix, glm::vec3(translate.x, translate.y, translate.z))));
        }

        Matrix4x4 Matrix4x4::CreateScaleMatrix(Vector3<float> const& scale, Matrix4x4 const& matrix)
        {
            return Matrix4x4(Matrix4x4_Internal(glm::scale(matrix.getInternal()->matrix, glm::vec3(scale.x, scale.y, scale.z))));
        }

        Matrix4x4 Matrix4x4::CreateLookAtMatrix(Vector3<float> const& from, Vector3<float> const& to, Vector3<float> const& up)
        {
            return Matrix4x4(Matrix4x4_Internal(glm::lookAtRH(glm::vec3(from.x, from.y, from.z), glm::vec3(to.x, to.y, to.z), glm::vec3(up.x, up.y, up.z))));
        }

        Matrix4x4 Matrix4x4::CreateOrthographicMatrix(float const xMin, float const xMax, float const yMin, float const yMax, float const nearClip, float const farClip)
        {
            return Matrix4x4(Matrix4x4_Internal(glm::ortho(xMin, xMax, yMin, yMax, nearClip, farClip)));
        }

        Matrix4x4 Matrix4x4::CreatePerspectiveMatrix(float const fov, float const aspectRatio, float const nearClip, float const farClip)
        {
            // Keep in mind: http://www.gamedev.net/topic/669955-glmlookat-with-directx/#entry5239993
            Matrix4x4 result = Matrix4x4(Matrix4x4_Internal(glm::perspectiveRH(Math::DegreesToRadians(fov), aspectRatio, nearClip, farClip)));
            return result;
        }

        //----------------------------------------------------------------
        // MISC
        //----------------------------------------------------------------

        Matrix4x4_Internal* Matrix4x4::getInternal() const
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