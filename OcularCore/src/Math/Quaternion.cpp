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
            w = 0.0f;
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

            if(trace > 0.0f)
            {
                float s = sqrt(trace + 1.0f) * 2.0f;
                w = 0.25f * s;
                x = (m21 - m12) / s;
                y = (m02 - m20) / s;
                z = (m10 - m01) / s;
            }
            else if((m00 > m11) && (m00 > m22))
            {
                float s = sqrt(1.0f + m00 - m11 - m22) * 2.0f;
                w = (m21 - m12) / s;
                x = 0.25f * s;
                y = (m01 + m10) / s;
                z = (m02 + m20) / s;
            }
            else if(m11 > m22)
            {
                float s = sqrt(1.0f + m11 - m00 - m22) * 2.0f;
                w = (m02 - m20) / s;
                x = (m01 + m10) / s;
                y = 0.25f * s;
                z = (m12 + m21) / s;
            }
            else
            {
                float s = sqrt(1.0f + m22 - m00 - m11) * 2.0f;
                w = (m10 - m01) / s;
                x = (m02 + m20) / s;
                y = (m12 + m21) / s;
                z = 0.25f * s;
            }
        }

        Quaternion::Quaternion(Euler const& euler)
        {
            // Source:
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm

            // We directly access the internal contents as getYaw, etc. return in degrees and we want radians.

            float c1 = cos(euler.m_Yaw / 2.0f);
            float c2 = cos(euler.m_Pitch / 2.0f);
            float c3 = cos(euler.m_Roll / 2.0f);
            float s1 = sin(euler.m_Yaw / 2.0f);
            float s2 = sin(euler.m_Pitch / 2.0f);
            float s3 = sin(euler.m_Roll / 2.0f);

            w = (c1 * c2 * c3) - (s1 * s2 * s3);
            x = (s1 * s2 * c3) + (c1 * c2 * s3);
            y = (s1 * c2 * c3) + (c1 * s2 * s3);
            z = (c1 * s2 * c3) - (s1 * c2 * s3);
        }

        Quaternion::~Quaternion()
        {
        
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

        void Quaternion::normalize()
        {
        
        }

        Quaternion Quaternion::getNormalized() const
        {
            return Quaternion();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}