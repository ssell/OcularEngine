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

#include "Math/Euler.hpp"
#include "Math/Matrix3x3.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Equality.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Euler::Euler()
        {
            yaw   = 0.0f;
            pitch = 0.0f;
            roll  = 0.0f;
        }

        Euler::Euler(float const pYaw, float const pPitch, float const pRoll)
        {
            yaw   = pYaw;
            pitch = pPitch;
            roll  = pRoll;
        }

        Euler::Euler(Matrix3x3f const& rotationMatrix)
        {
            // Source: 
            // Real-Time Rendering 3rd Edition 
            // 4.2.2 Extracting Parameters from the Euler Transform
            // Page 68

            yaw   = std::atan2(-rotationMatrix.getElement(2, 0), rotationMatrix.getElement(2, 2));
            pitch = std::asin(rotationMatrix.getElement(2, 1));
            roll  = std::atan2(-rotationMatrix.getElement(0, 1), rotationMatrix.getElement(1, 1));

            if(IsEqual<float>(std::cos(pitch), 0.0f))
            {
                yaw  = 0.0f;
                roll = std::atan2(rotationMatrix.getElement(1, 0), rotationMatrix.getElement(0, 0));
            }
        }

        Euler::Euler(Quaternion const& quaternion)
        {
            // Source: 
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm

            float qw = quaternion.w;
            float qx = quaternion.x;
            float qy = quaternion.y;
            float qz = quaternion.z;

            float qww = qw * qw;
            float qxx = qx * qx;
            float qyy = qy * qy;
            float qzz = qz * qz;

            float unit = qxx + qyy + qzz + qww;
            float test = (qx * qy) + (qz * qw);

            if(test > (0.499f * unit))
            {
                // North Pole Singularity
                yaw   = 2.0f * atan2(qx, qw);
                pitch = static_cast<float>(PI_OVER_TWO);
                roll  = 0.0f;
            }
            else if(test < (-0.499f * unit))
            {
                // South Pole Singularity
                yaw   = -2.0f * atan2(qx, qw);
                pitch = static_cast<float>(-PI_OVER_TWO);
                roll  = 0.0f;
            }
            else
            {
                yaw   = atan2((2.0f * qy * qw) - (2.0f * qx * qz), qxx - qyy - qzz + qww);
                pitch = asin((2.0f * qx * qy) + (2.0f * qz * qw));
                roll  = atan2((2.0f * qx * qw) - (2.0f * qy * qz), -qxx + qyy - qzz + qww);
            }
        }

        Euler::~Euler()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        Matrix3x3f Euler::toRotationMatrix() const
        {
            return Matrix3x3f(*this);
        }

        Quaternion Euler::toQuaternion() const
        {
            return Quaternion(*this);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}