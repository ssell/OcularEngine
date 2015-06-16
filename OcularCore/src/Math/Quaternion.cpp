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

#include "Math/Quaternion.hpp"
#include "Math/Matrix3x3.hpp"
#include "Math/Euler.hpp"
#include "Math/MathCommon.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Quaternion::Quaternion()
        {
            w = 1.0f;
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        Quaternion::Quaternion(float const pW, float const pX, float const pY, float const pZ)
        {
            w = pW;
            x = pX;
            y = pY;
            z = pZ;
        }

        Quaternion::Quaternion(Matrix3x3f const& rotationMatrix)
        {
            // Currently the matrix -> quaternion -> matrix conversion is a bit off somewhere (see first chunk of commented out code).
            // But... the matrix -> euler, and euler-> quaternion work perfectly. So...
            // See TestConversions: QuaternionMatrix for more details.

            Euler euler = rotationMatrix.toEuler();

            const float cY = cos(euler.m_Yaw   * 0.5f);
            const float cP = cos(euler.m_Pitch * 0.5f);
            const float cR = cos(euler.m_Roll  * 0.5f);
            const float sY = sin(euler.m_Yaw   * 0.5f);
            const float sP = sin(euler.m_Pitch * 0.5f);
            const float sR = sin(euler.m_Roll  * 0.5f);

            w =  (cR * cP * cY) + (sR * sP * sY);
            x =  (cR * sP * sY) - (sR * cP * cY);
            y = -(cR * sP * cY) - (sR * cP * sY);
            z =  (cR * cP * sY) - (sR * sP * cY);

            /*
            // Source: 
            // Real-Time Rendering 3rd Edition 
            // 4.3.2 Quaternion Transforms
            // Page 76

            // Also:
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
            // http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q47

            float m00 = rotationMatrix[0][0];
            float m01 = rotationMatrix[0][1];
            float m02 = rotationMatrix[0][2];
            float m10 = rotationMatrix[1][0];
            float m11 = rotationMatrix[1][1];
            float m12 = rotationMatrix[1][2];
            float m20 = rotationMatrix[2][0];
            float m21 = rotationMatrix[2][1];
            float m22 = rotationMatrix[2][2];

            float trace = m00 + m11 + m22;

            float invS = 0.0f;
            float s = 0.0f;

            if(trace > 0.0f)
            {
                invS = InverseSqrt(trace + 1.0f);
                s = 0.5f * invS;

                w = 0.5f * (1.0f / invS);
                x = (m12 - m21) * s;
                y = (m20 - m02) * s;
                z = (m01 - m10) * s;
            }
            else
            {
                unsigned i = 0;

                if(m11 > m00)
                {
                    i = 1;
                }

                if(m22 > rotationMatrix[i][i])
                {
                    i = 2;
                }

                static const int next[3] = { 1, 2, 0 };
                int j = next[i];
                int k = next[j];

                s = rotationMatrix[i][i] - rotationMatrix[j][j] - rotationMatrix[k][k] + 1.0f;
                invS = InverseSqrt(s);

                float quat[4];
                quat[i] = 0.5f * (1.0f / invS);

                s = 0.5f * invS;
                
                quat[3] = (rotationMatrix[j][k] - rotationMatrix[k][j]) * s;
                quat[j] = (rotationMatrix[i][j] + rotationMatrix[j][i]) * s;
                quat[k] = (rotationMatrix[i][k] + rotationMatrix[k][i]) * s;

                w = quat[3];
                x = quat[0];
                y = quat[1];
                z = quat[2];
            }*/

            /*
            float trace = rotationMatrix[0][0] + rotationMatrix[1][1] + rotationMatrix[2][2];
            float s = 0.0f;

            if(trace > EPSILON_FLOAT)
            {
                s = sqrt(trace) * 2.0f; 
                w = 0.25f * s;
                x = (rotationMatrix[1][2] - rotationMatrix[2][1]) / s;
                y = (rotationMatrix[2][0] - rotationMatrix[0][2]) / s;
                z = (rotationMatrix[0][1] - rotationMatrix[1][0]) / s;
            }
            else
            {
                if((rotationMatrix[0][0] > rotationMatrix[1][1]) && (rotationMatrix[0][0] > rotationMatrix[2][2]))
                {
                    s = (1.0f + rotationMatrix[0][0] - rotationMatrix[1][1] - rotationMatrix[2][2]) * 2.0f;
                    w = (rotationMatrix[1][2] - rotationMatrix[2][1]) / s;
                    x = 0.25f * s;
                    y = (rotationMatrix[0][1] + rotationMatrix[1][0]) / s;
                    z = (rotationMatrix[2][0] + rotationMatrix[0][2]) / s;
                }
                else if(rotationMatrix[1][1] > rotationMatrix[2][2])
                {
                    s = (1.0f + rotationMatrix[1][1] - rotationMatrix[0][0] - rotationMatrix[2][2]) * 2.0f;
                    w = (rotationMatrix[2][0] - rotationMatrix[0][2]) / s;
                    x = (rotationMatrix[0][1] + rotationMatrix[1][0]) / s;
                    y = 0.25f * s;
                    z = (rotationMatrix[1][2] + rotationMatrix[2][1]) / s;
                }
                else
                {
                    s = (1.0f + rotationMatrix[2][2] - rotationMatrix[0][0] - rotationMatrix[1][1]) * 2.0f;
                    w = (rotationMatrix[0][1] - rotationMatrix[1][0]) / s;
                    x = (rotationMatrix[2][0] + rotationMatrix[0][2]) / s;
                    y = (rotationMatrix[1][2] + rotationMatrix[2][1]) / s;
                    z = 0.25f * s;
                }
            }
            */
        }

        Quaternion::Quaternion(Euler const& euler)
        {
            // Source:
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm

            // We directly access the internal contents as getYaw, etc. return in degrees and we want radians.

            const float cY = cos(euler.m_Yaw   * 0.5f);
            const float cP = cos(euler.m_Pitch * 0.5f);
            const float cR = cos(euler.m_Roll  * 0.5f);
            const float sY = sin(euler.m_Yaw   * 0.5f);
            const float sP = sin(euler.m_Pitch * 0.5f);
            const float sR = sin(euler.m_Roll  * 0.5f);

            w =  (cR * cP * cY) + (sR * sP * sY);
            x =  (cR * sP * sY) - (sR * cP * cY);
            y = -(cR * sP * cY) - (sR * cP * sY);
            z =  (cR * cP * sY) - (sR * sP * cY);
        }

        Quaternion::Quaternion(Vector3<float> const& eulerVector)
        {
            const Euler euler(eulerVector.getNormalized());

            const float cY = cos(euler.m_Yaw   * 0.5f);
            const float cP = cos(euler.m_Pitch * 0.5f);
            const float cR = cos(euler.m_Roll  * 0.5f);
            const float sY = sin(euler.m_Yaw   * 0.5f);
            const float sP = sin(euler.m_Pitch * 0.5f);
            const float sR = sin(euler.m_Roll  * 0.5f);

            w =  (cR * cP * cY) + (sR * sP * sY);
            x =  (cR * sP * sY) - (sR * cP * cY);
            y = -(cR * sP * cY) - (sR * cP * sY);
            z =  (cR * cP * sY) - (sR * sP * cY);
        }

        Quaternion::Quaternion(Vector3<float> const& axis, float const angle)
        {
            const float angleRad  = DegreesToRadians<float>(angle);
            const float halfAngle = angleRad * 0.5f;
            const float angleSin  = sin(halfAngle);
            const float angleCos  = cos(halfAngle);

            w = angleCos;
            x = angleSin * axis.x;
            y = angleSin * axis.y;
            z = angleSin * axis.z;
        }

        Quaternion::~Quaternion()
        {
        
        }

        //----------------------------------------------------------------------------------
        // OPERATORS
        //----------------------------------------------------------------------------------

        Quaternion Quaternion::operator=(Quaternion const& rhs)
        {
            w = rhs.w;
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;

            return (*this);
        }

        Quaternion operator+(Quaternion const& lhs, Quaternion const& rhs)
        {
            return Quaternion((lhs.w + rhs.w), (lhs.x + rhs.x), (lhs.y + rhs.y), (lhs.z + rhs.z));
        }

        Quaternion operator-(Quaternion const& lhs, Quaternion const& rhs)
        {
            return Quaternion((lhs.w - rhs.w), (lhs.x - rhs.x), (lhs.y - rhs.y), (lhs.z - rhs.z));
        }

        Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs)
        {
            Quaternion result;

            result.w = (lhs.w * rhs.w) - (lhs.x * rhs.x) - (lhs.y * rhs.y) - (lhs.z * rhs.z);
		    result.x = (lhs.w * rhs.x) + (lhs.x * rhs.w) + (lhs.y * rhs.z) - (lhs.z * rhs.y);
		    result.y = (lhs.w * rhs.y) + (lhs.y * rhs.w) + (lhs.z * rhs.x) - (lhs.x * rhs.z);
		    result.z = (lhs.w * rhs.z) + (lhs.z * rhs.w) + (lhs.x * rhs.y) - (lhs.y * rhs.x);

            return result;
        }

        Vector3<float> operator*(Quaternion const& lhs, Vector3<float> const& rhs)
        {
            Vector3<float> quatVec(rhs.x, rhs.y, rhs.z);
            Vector3<float> uv  = quatVec.cross(rhs);
            Vector3<float> uuv = quatVec.cross(uv);

            return (rhs + ((uv * lhs.w) + uuv) * 2.0f);
        }

        Vector3<float> operator*(Vector3<float> const& lhs, Quaternion const& rhs)
        {
            return (rhs.getInverse() * lhs);
        }

        Quaternion operator*(Quaternion const& lhs, float const& rhs)
        {
            return Quaternion((lhs.w * rhs), (lhs.x * rhs), (lhs.y * rhs), (lhs.z * rhs));
        }

        Quaternion operator*(float const& lhs, Quaternion const& rhs)
        {
            return Quaternion((rhs.w * lhs), (rhs.x * lhs), (rhs.y * lhs), (rhs.z * lhs));
        }

        Quaternion operator/(Quaternion const& lhs, float const& rhs)
        {
            return Quaternion((lhs.w / rhs), (lhs.x / rhs), (lhs.y / rhs), (lhs.z / rhs));
        }

        bool operator==(Quaternion const& lhs, Quaternion const& rhs)
        {
            return (IsEqual<float>(lhs.w, rhs.w) &&
                    IsEqual<float>(lhs.x, rhs.x) && 
                    IsEqual<float>(lhs.y, rhs.y) &&
                    IsEqual<float>(lhs.z, rhs.z));
        }

        bool operator!=(Quaternion const& lhs, Quaternion const& rhs)
        {
            return !(lhs == rhs);
        }


        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        Matrix3x3f Quaternion::toRotationMatrix() const
        {
            return Matrix3x3f(*this);
        }

        Euler Quaternion::toEuler() const
        {
            return Euler(*this);
        }

        bool Quaternion::isNormalized() const
        {
            return IsEqual<float>(fabs(1.0f - getLengthSquared()), 0.0f);
        }

        Vector3<float> Quaternion::rotate(Vector3<float> const& vector) const
        {
            Vector3<float> result;
            Vector3<float> quatVector(x, y, z);

            result  = quatVector.cross(vector) * w * 2.0f;
            result += (vector * ((quatVector.dot(quatVector) * -1.0f) + (w * w)));
            result += (quatVector * (2.0f * quatVector.dot(vector)));

            return result;
        }

        void Quaternion::normalize()
        {
            const float squareSum = (w * w) + (x * x) + (y * y) + (z * z);
            const float scale = InverseSqrt(squareSum);

            w *= scale;
            x *= scale;
            y *= scale;
            z *= scale;
        }

        Quaternion Quaternion::getNormalized() const
        {
            Quaternion result = *this;
            result.normalize();

            return result;
        }

        float Quaternion::getLength() const
        {
            return sqrt(dot(*this));
        }

        float Quaternion::getLengthSquared() const
        {
            const float length = getLength();
            return (length * length);
        }

        Quaternion Quaternion::getInverse() const
        {
            return (getConjugate() / dot(*this));
        }

        Quaternion Quaternion::getConjugate() const
        {
            return Quaternion(w, -x, -y, -z);
        }

        Vector3<float> Quaternion::getXRotationAxis() const
        {
            return rotate(Vector3<float>(1.0f, 0.0f, 0.0f));
        }

        Vector3<float> Quaternion::getYRotationAxis() const
        {
            return rotate(Vector3<float>(0.0f, 1.0f, 0.0f));
        }

        Vector3<float> Quaternion::getZRotationAxis() const
        {
            /// \todo Is this correct? Should it instead be using Vector3f::forward() ?
            return rotate(Vector3<float>(0.0f, 0.0f, 1.0f));
        }

        float Quaternion::dot(Quaternion const& rhs) const
        {
            return ((x * rhs.x) + (y * rhs.y)) + ((z * rhs.z) + (w * rhs.w));
        }

        //------------------------------------------------------------
        // STATIC METHODS
        //------------------------------------------------------------

        Quaternion Quaternion::CreateLookAtRotation(Vector3<float> const& eye, Vector3<float> const& lookAt, Vector3<float> const& up)
        {
            Quaternion result;

            Vector3f forward = (lookAt - eye).getNormalized();
            float dot = Vector3f::forward().dot(forward);

            if(abs(dot + 1.0f) < EPSILON_FLOAT)
            {
                result.w = static_cast<float>(PI);
                result.x = Vector3f::up().x;
                result.y = Vector3f::up().y;
                result.z = Vector3f::up().z;
            }
            else if(abs(dot - 1.0f) < EPSILON_FLOAT)
            {
                // Do nothing. Return identity.
            }
            else
            {
                float    rotationAngle = acos(dot);
                Vector3f rotationAxis  = Vector3f::forward().cross(forward).getNormalized();

                result = Quaternion(rotationAxis, rotationAngle);
            }

            return result;
        }

        Quaternion Quaternion::RotateVector(Vector3<float> const& from, Vector3<float> const& to)
        {
            // Source: 
            // Real-Time Rendering 3rd Edition 
            // 4.3.2 Quaternion Transforms
            // Page 79

            /*
                              1                  sqrt(2(1+e))
            (qv, qw) = ( ------------ * (s X t), ------------ )
                         sqrt(2(1+e))                 2
            */

            Quaternion result;

            Vector3<float> s = from.getNormalized();
            Vector3<float> t = to.getNormalized();
           
            float e = s.dot(t);
            float v = sqrt(2.0f * (1.0f + e));

            Vector3<float> imaginary = (s.cross(t)) * (1.0f / v);
            
            result.w = v / 2.0f;
            result.x = imaginary.x;
            result.y = imaginary.y;
            result.z = imaginary.z;

            return result;
        }

        Quaternion Quaternion::Lerp(Quaternion const& a, Quaternion const& b, float const& t)
        {
            return (a * (1.0f - t)) + (b * t);
        }

        Quaternion Quaternion::Bilerp(Quaternion const& q00, Quaternion const& q10, Quaternion const& q01, Quaternion const& q11, float const& x, float const& y)
        {
            return Lerp(Lerp(q00, q10, x), Lerp(q01, q11, x), y);
        }

        Quaternion Quaternion::Slerp(Quaternion const& a, Quaternion const& b, float const& t)
        {
            Quaternion result;
            Quaternion c = b;

            float theta = a.dot(b);

            if(theta < 0.0f)
            {   
                c = c * -1.0f;
                theta = -theta;
            }

            if(theta > (1.0f - EPSILON_FLOAT))
            {
                // Perform a lerp when close to 1 to avoid division by 0
                result = Lerp(a, b, t);
            }
            else
            {
                float angle = acos(theta);
                result = ((a * sin((1.0f - t) * angle)) + (c * sin(t * angle))) / sin(angle);
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}