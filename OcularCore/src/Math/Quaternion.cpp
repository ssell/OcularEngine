/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Math/Quaternion.hpp"
#include "Math/MathInternal.hpp"
#include "Math/Matrix3x3.hpp"
#include "Math/Matrix4x4.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

#include "Utilities/StringRegistrar.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        OCULAR_REGISTER_TO_STRING(Quaternion, OCULAR_TO_STRING_LAMBDA 
        { 
            std::string result;

            if(raw)
            {
                Quaternion* quat = void_cast<Quaternion*>(raw);

                if(quat)
                {
                    std::stringstream sstream;
                    sstream << quat->x() << " " << quat->y() << " " << quat->z() << " " << quat->w();

                    result = sstream.str();
                }
            }

            return result; 
        });

        OCULAR_REGISTER_FROM_STRING(Quaternion, OCULAR_FROM_STRING_LAMBDA
        {
            if(out)
            {
                Quaternion* result = void_cast<Quaternion*>(out);

                if(result)
                {
                    size_t cumulativePos = 0;
                    size_t nextPos = 0;

                    try
                    {
                        result->x() = std::stof(str.substr(cumulativePos), &nextPos);
                        cumulativePos += nextPos;
                        
                        result->y() = std::stof(str.substr(cumulativePos), &nextPos);
                        cumulativePos += nextPos;
                        
                        result->z() = std::stof(str.substr(cumulativePos), &nextPos);
                        cumulativePos += nextPos;
                        
                        result->w() = std::stof(str.substr(cumulativePos), &nextPos);
                    }
                    catch(std::invalid_argument const& e)
                    {
                        OcularLogger->error("Failed to convert string '", str, "' to Quaternion with error: ", e.what(), OCULAR_INTERNAL_LOG("Quaternion", "FromString"));
                    }
                }
            }
        });

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Quaternion::Quaternion(float const w, float const x, float const y, float const z)
        {
            m_Internal = new Quaternion_Internal(glm::quat(w, x, y, z));
        }

        Quaternion::Quaternion(float const angle, Vector3<float> const& axis)
        {
            m_Internal = new Quaternion_Internal(glm::quat(Math::DegreesToRadians(angle), glm::vec3(axis.x, axis.y, axis.z)));
        }

        Quaternion::Quaternion(Vector3<float> const& euler)
        { 
            // GLM expects vec3(pitch, yaw, roll)
            m_Internal = new Quaternion_Internal(glm::quat(glm::vec3(euler.y, euler.x, euler.z)));
        }

        Quaternion::Quaternion(Matrix3x3 const& matrix)
        {
            m_Internal = new Quaternion_Internal();
            Matrix3x3_Internal* matrixInternal = matrix.getInternal();

            if(matrixInternal)
            {
                m_Internal->quat = glm::quat(matrixInternal->matrix);
            }
        }

        Quaternion::Quaternion(Matrix4x4 const& matrix)
        {
            m_Internal = new Quaternion_Internal();
            Matrix4x4_Internal* matrixInternal = matrix.getInternal();

            if(matrixInternal)
            {
                m_Internal->quat = glm::quat(matrixInternal->matrix);
            }
        }

        Quaternion::Quaternion(Quaternion_Internal const& data)
        {
            m_Internal = new Quaternion_Internal(data.quat);
        }

        Quaternion::Quaternion(Quaternion const& other)
        {
            m_Internal = new Quaternion_Internal(other.m_Internal->quat);
        }

        Quaternion::Quaternion()
        {
            m_Internal = new Quaternion_Internal();
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
            m_Internal->quat = rhs.m_Internal->quat;
            return (*this);
        }

        Quaternion& Quaternion::operator+=(Quaternion const& rhs)
        {
            m_Internal->quat += rhs.m_Internal->quat;
            return (*this);
        }

        Quaternion& Quaternion::operator*=(Quaternion const& rhs)
        {
            m_Internal->quat *= rhs.m_Internal->quat;
            return (*this);
        }

        Quaternion& Quaternion::operator*=(float const rhs)
        {
            m_Internal->quat *= rhs;
            return (*this);
        }

        Quaternion& Quaternion::operator/=(float const rhs)
        {
            m_Internal->quat /= rhs;
            return (*this);
        }

        bool operator==(Quaternion const& lhs, Quaternion const& rhs)
        {
            return (lhs.getInternal()->quat == rhs.getInternal()->quat);
        }

        bool operator!=(Quaternion const& lhs, Quaternion const& rhs)
        {
            return !(lhs == rhs);
        }

        Quaternion operator+(Quaternion const& lhs, Quaternion const& rhs)
        {
            return Quaternion(Quaternion_Internal(lhs.getInternal()->quat + rhs.getInternal()->quat));
        }

        Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs)
        {
            return Quaternion(Quaternion_Internal(lhs.getInternal()->quat * rhs.getInternal()->quat));
        }

        Quaternion operator*(Quaternion const& lhs, float const rhs)
        {
            return Quaternion(Quaternion_Internal(lhs.getInternal()->quat * rhs));
        }

        Quaternion operator/(Quaternion const& lhs, float const rhs)
        {
            return Quaternion(Quaternion_Internal(lhs.getInternal()->quat / rhs));
        }

        Vector3<float> operator*(Quaternion const& lhs, Vector3<float> const& rhs)
        {
            glm::vec3 vec(rhs.x, rhs.y, rhs.z);
            vec = lhs.getInternal()->quat * vec;

            return Vector3<float>(vec.x, vec.y, vec.z);
        }

        Vector4<float> operator*(Quaternion const& lhs, Vector4<float> const& rhs)
        {
            glm::vec4 vec(rhs.x, rhs.y, rhs.z, rhs.w);
            vec = lhs.getInternal()->quat * vec;

            return Vector4<float>(vec.x, vec.y, vec.z, vec.w);
        }

        //----------------------------------------------------------------
        // GETTERS / SETTERS
        //----------------------------------------------------------------

        float& Quaternion::w()
        {
            return m_Internal->quat.w;
        }

        float& Quaternion::x()
        {
            return m_Internal->quat.x;
        }

        float& Quaternion::y()
        {
            return m_Internal->quat.y;
        }

        float& Quaternion::z()
        {
            return m_Internal->quat.z;
        }

        //----------------------------------------------------------------
        // GENERAL OPERATIONS
        //----------------------------------------------------------------

        float Quaternion::dot(Quaternion const& rhs)
        {
            Quaternion_Internal* rhsInternal = rhs.getInternal();
            return (glm::dot(m_Internal->quat, rhsInternal->quat));
        }

        void Quaternion::inverse()
        {
            m_Internal->quat = glm::inverse(m_Internal->quat);
        }

        Quaternion Quaternion::getInverse() const
        {
            return Quaternion(Quaternion_Internal(glm::inverse(m_Internal->quat)));
        }

        Quaternion Quaternion::getConjugate() const
        {
            return Quaternion(Quaternion_Internal(glm::conjugate(m_Internal->quat)));
        }

        void Quaternion::normalize()
        {
            m_Internal->quat = glm::normalize(m_Internal->quat);
        }

        Quaternion Quaternion::getNormalized() const
        {
            return Quaternion(Quaternion_Internal(glm::normalize(m_Internal->quat)));
        }

        float Quaternion::getLength() const
        {
            return glm::length(m_Internal->quat);
        }

        float Quaternion::getYaw() const
        {
            return glm::yaw(m_Internal->quat);
        }

        float Quaternion::getPitch() const
        {
            return glm::pitch(m_Internal->quat);
        }

        float Quaternion::getRoll() const
        {
            return glm::roll(m_Internal->quat);
        }

        float Quaternion::getAngle() const
        {
            return glm::angle(m_Internal->quat);
        }

        Vector3<float> Quaternion::getAxis() const
        {
            glm::vec3 axis = glm::axis(m_Internal->quat);
            return Vector3<float>(axis[0], axis[1], axis[2]);
        }

        Quaternion Quaternion::cross(Quaternion const& rhs) const
        {
            return Quaternion(Quaternion_Internal(glm::cross(m_Internal->quat, rhs.m_Internal->quat)));
        }

        //----------------------------------------------------------------
        // STATIC OPERATIONS
        //----------------------------------------------------------------

        Quaternion Quaternion::CreateLookAtRotation(Vector3<float> const& from, Vector3<float> const& to, Vector3<float> const& up)
        {
            Quaternion result;

            glm::mat4 lookAtMatrix = glm::lookAtRH(glm::vec3(from.x, from.y, from.z), glm::vec3(to.x, to.y, to.z), glm::vec3(up.x, up.y, up.z));
            result = Quaternion(Quaternion_Internal(glm::quat(lookAtMatrix)));

            return result;
        }

        Quaternion Quaternion::Rotate(Quaternion const& source, float angle, Vector3<float> const& axis)
        {
            return Quaternion(Quaternion_Internal(glm::rotate(source.getInternal()->quat, angle, glm::vec3(axis.x, axis.y, axis.z))));
        }

        Quaternion Quaternion::Mix(Quaternion const& a, Quaternion const& b, float const f)
        {
            return Quaternion(Quaternion_Internal(glm::mix(a.m_Internal->quat, b.m_Internal->quat, f)));
        }

        Quaternion Quaternion::Lerp(Quaternion const& a, Quaternion const& b, float const f)
        {
            return Quaternion(Quaternion_Internal(glm::lerp(a.m_Internal->quat, b.m_Internal->quat, f)));
        }

        Quaternion Quaternion::Slerp(Quaternion const& a, Quaternion const& b, float const f)
        {
            return Quaternion(Quaternion_Internal(glm::slerp(a.m_Internal->quat, b.m_Internal->quat, f)));
        }

        Quaternion Quaternion::Bilerp(Quaternion const& q00, Quaternion const& q10, Quaternion const& q01, Quaternion const& q11, float const x, float const y)
        {
            return Lerp(Lerp(q00, q10, x), Lerp(q01, q11, x), y);
        }

        //----------------------------------------------------------------
        // MISC
        //----------------------------------------------------------------

        Quaternion_Internal* Quaternion::getInternal() const
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
