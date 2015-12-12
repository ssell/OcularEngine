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

#include "Math/QuaternionTemp.hpp"
#include "Math/MathInternal.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Quaternion::Quaternion(float const w, float const x, float const y, float const z)
        {

        }

        Quaternion::Quaternion(float const angle, Vector3<float> const& axis)
        {

        }

        Quaternion::Quaternion(Vector3<float> const& euler)
        {

        }

        Quaternion::Quaternion(Matrix3x3 const& matrix)
        {

        }

        Quaternion::Quaternion(Matrix4x4 const& matrix)
        {

        }

        Quaternion::Quaternion(Quaternion_Internal const& data)
        {

        }

        Quaternion::Quaternion(Quaternion const& other)
        {

        }

        Quaternion::Quaternion()
        {

        }

        Quaternion::~Quaternion()
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

        Quaternion& Quaternion::operator=(Quaternion const& rhs)
        {

        }

        Quaternion& Quaternion::operator+=(Quaternion const& rhs)
        {

        }

        Quaternion& Quaternion::operator-=(Quaternion const& rhs)
        {

        }

        Quaternion& Quaternion::operator*=(Quaternion const& rhs)
        {

        }

        Quaternion& Quaternion::operator/=(Quaternion const& rhs)
        {

        }

        bool operator==(Quaternion const& lhs, Quaternion const& rhs)
        {

        }

        bool operator!=(Quaternion const& lhs, Quaternion const& rhs)
        {

        }

        Quaternion operator+(Quaternion const& lhs, Quaternion const& rhs)
        {

        }

        Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs)
        {

        }

        Quaternion operator*(Quaternion const& lhs, float const rhs)
        {

        }

        Quaternion operator/(Quaternion const& lhs, float const rhs)
        {

        }

        Vector3<float> operator*(Quaternion const& lhs, Vector3<float> const& rhs)
        {

        }

        Vector4<float> operator*(Quaternion const& lhs, Vector4<float> const& rhs)
        {

        }

        //----------------------------------------------------------------
        // GETTERS / SETTERS
        //----------------------------------------------------------------

        float Quaternion::w()
        {

        }

        float Quaternion::x()
        {

        }

        float Quaternion::y()
        {

        }

        float Quaternion::z()
        {

        }

        //----------------------------------------------------------------
        // GENERAL OPERATIONS
        //----------------------------------------------------------------

        Quaternion Quaternion::dot(Quaternion const& rhs)
        {

        }

        void Quaternion::inverse()
        {

        }

        Quaternion Quaternion::getInverse() const
        {

        }

        Quaternion Quaternion::getConjugate() const
        {

        }

        void Quaternion::normalize()
        {

        }

        Quaternion Quaternion::getNormalized() const
        {

        }

        float Quaternion::getLength() const
        {

        }

        float Quaternion::getYaw() const
        {

        }

        float Quaternion::getPitch() const
        {

        }

        float Quaternion::getRoll() const
        {

        }

        float Quaternion::getAngle() const
        {

        }

        Vector3<float> Quaternion::getAxis() const
        {

        }

        float Quaternion::cross(Vector3<float> const& vector)
        {

        }

        //----------------------------------------------------------------
        // STATIC OPERATIONS
        //----------------------------------------------------------------

        Quaternion Quaternion::Rotate(Quaternion const& source, float angle, Vector3<float> const& axis)
        {

        }

        Quaternion Quaternion::Mix(Quaternion const& a, Quaternion const& b, float const f)
        {

        }

        Quaternion Quaternion::Lerp(Quaternion const& a, Quaternion const& b, float const t)
        {

        }

        Quaternion Quaternion::Slerp(Quaternion const& a, Quaternion const& b, float const t)
        {

        }

        Quaternion Quaternion::Bilerp(Quaternion const& q00, Quaternion const& q10, Quaternion const& q01, Quaternion const& q11)
        {

        }

        //----------------------------------------------------------------
        // MISC
        //----------------------------------------------------------------

        Quaternion_Internal Quaternion::getInternal()
        {

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}
