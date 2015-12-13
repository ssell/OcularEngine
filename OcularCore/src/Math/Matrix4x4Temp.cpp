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

#include "Math/Matrix4x4Temp.hpp"
#include "Math/MathInternal.hpp"

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
            return m_Internal->matrix[(index / 4)][(index % 4)];
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

        /*
        Matrix4x4& Matrix4x4::operator*=(Vector4 const& rhs)
        {
            m_Internal->matrix *= rhs;
            return (*this);
        }
        */

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

        /*
        Matrix4x4 operator*(Matrix4x4 const& lhs, Vector4 const& rhs)
        {
        
        }
        */

        //----------------------------------------------------------------
        // GETTERS / SETTERS
        //----------------------------------------------------------------



        //----------------------------------------------------------------
        // MISC OPERATIONS
        //----------------------------------------------------------------

        float Matrix4x4::getDeterminant() const
        {
            return glm::determinant(m_Internal->matrix);
        }

        Matrix4x4 Matrix4x4::getInverse() const
        {
            return Matrix4x4(Matrix4x4_Internal(glm::inverse(m_Internal->matrix)));
        }

        Matrix4x4 Matrix4x4::getTranspose() const
        {
            return Matrix4x4(Matrix4x4_Internal(glm::transpose(m_Internal->matrix)));
        }

        //----------------------------------------------------------------
        // STATIC OPERATIONS
        //----------------------------------------------------------------

        Matrix4x4 Matrix4x4::CreateOrthographicMatrix(float const xMin, float const xMax, float const yMin, float const yMax, float const nearClip, float const farClip)
        {
            return Matrix4x4(Matrix4x4_Internal(glm::ortho(xMin, xMax, yMin, yMax, nearClip, farClip)));
        }

        Matrix4x4 Matrix4x4::CreatePerspectiveMatrix(float const fov, float const aspectRatio, float const nearClip, float const farClip)
        {
            return Matrix4x4(Matrix4x4_Internal(glm::perspective(fov, aspectRatio, nearClip, farClip)));
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