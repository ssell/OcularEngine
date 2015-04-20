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
            // Source: 
            // Real-Time Rendering 3rd Edition 
            // 4.3.2 Quaternion Transforms
            // Page 76

            // Also:
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
            
            float m00 = rotationMatrix.getElement(0, 0);
            float m01 = rotationMatrix.getElement(0, 1);
            float m02 = rotationMatrix.getElement(0, 2);
            float m10 = rotationMatrix.getElement(1, 0);
            float m11 = rotationMatrix.getElement(1, 1);
            float m12 = rotationMatrix.getElement(1, 2);
            float m20 = rotationMatrix.getElement(2, 0);
            float m21 = rotationMatrix.getElement(2, 1);
            float m22 = rotationMatrix.getElement(2, 2);

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

                if(m22 > rotationMatrix.getElement(i, i))
                {
                    i = 2;
                }

                static const int next[3] = { 1, 2, 0 };
                int j = next[i];
                int k = next[j];

                s = rotationMatrix.getElement(i, i) - rotationMatrix.getElement(j, j) - rotationMatrix.getElement(k, k) + 1.0f;
                invS = InverseSqrt(s);

                float quat[4];
                quat[i] = 0.5f * (1.0f / invS);

                s = 0.5f * invS;
                
                quat[3] = (rotationMatrix.getElement(j, k) - rotationMatrix.getElement(k, j)) * s;
                quat[j] = (rotationMatrix.getElement(i, j) + rotationMatrix.getElement(j, i)) * s;
                quat[k] = (rotationMatrix.getElement(i, k) + rotationMatrix.getElement(k, i)) * s;

                w = quat[3];
                x = quat[0];
                y = quat[1];
                z = quat[2];
            }
        }

        Quaternion::Quaternion(Euler const& euler)
        {
            // Source:
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm

            // We directly access the internal contents as getYaw, etc. return in degrees and we want radians.

            float cY = cos(euler.m_Yaw   * 0.5f);
            float cP = cos(euler.m_Pitch * 0.5f);
            float cR = cos(euler.m_Roll  * 0.5f);
            float sY = sin(euler.m_Yaw   * 0.5f);
            float sP = sin(euler.m_Pitch * 0.5f);
            float sR = sin(euler.m_Roll  * 0.5f);

            w =  (cR * cP * cY) + (sR * sP * sY);
            x =  (cR * sP * sY) - (sR * cP * cY);
            y = -(cR * sP * cY) - (sR * cP * sY);
            z =  (cR * cP * sY) - (sR * sP * cY);
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

        void Quaternion::rotate(Vector3<float>& vector) const
        {
            Vector3<float> result;
            Vector3<float> quatVector(x, y, z);

            result  = quatVector.cross(vector) * w * 2.0f;
            result += (vector * ((quatVector.dot(quatVector) * -1.0f) + (w * w)));
            result += (quatVector * (2.0f * quatVector.dot(vector)));

            vector = result;
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
            Vector3<float> result;

            // --- TODO

            return result;
        }

        Vector3<float> Quaternion::getYRotationAxis() const
        {
            Vector3<float> result;

            // --- TODO

            return result;
        }

        Vector3<float> Quaternion::getZRotationAxis() const
        {
            Vector3<float> result;

            // --- TODO

            return result;
        }

        float Quaternion::dot(Quaternion const& rhs) const
        {
            return ((x * rhs.x) + (y * rhs.y)) + ((z * rhs.z) + (w * rhs.w));
        }

        //------------------------------------------------------------
        // STATIC METHODS
        //------------------------------------------------------------

        Quaternion Quaternion::createLookAtRotation(Vector3<float> const& forward, Vector3<float> const& upward)
        {
            Quaternion result;

            // --- TODO

            return result;
        }

        Quaternion Quaternion::lerp(Quaternion const& a, Quaternion const& b, float const& t)
        {
            return (a * (1.0f - t)) + (b * t);
        }

        Quaternion Quaternion::bilerp(Quaternion const& q00, Quaternion const& q10, Quaternion const& q01, Quaternion const& q11, float const& x, float const& y)
        {
            return lerp(lerp(q00, q10, x), lerp(q01, q11, x), y);
        }

        Quaternion Quaternion::slerp(Quaternion const& a, Quaternion const& b, float const& t)
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
                result = lerp(a, b, t);
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