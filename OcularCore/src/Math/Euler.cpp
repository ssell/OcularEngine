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
            m_Yaw   = 0.0f;
            m_Pitch = 0.0f;
            m_Roll  = 0.0f;
        }

        Euler::Euler(float const pYaw, float const pPitch, float const pRoll)
        {
            m_Yaw   = DegreesToRadians<float>(pYaw);
            m_Pitch = DegreesToRadians<float>(pPitch);
            m_Roll  = DegreesToRadians<float>(pRoll);
        }

        Euler::Euler(Matrix3x3f const& rotationMatrix)
        {
            // Source: 
            // Real-Time Rendering 3rd Edition 
            // 4.2.2 Extracting Parameters from the Euler Transform
            // Page 68

            m_Yaw   = std::atan2(-rotationMatrix.getElement(2, 0), rotationMatrix.getElement(2, 2));
            m_Pitch = std::asin(rotationMatrix.getElement(2, 1));
            m_Roll  = std::atan2(-rotationMatrix.getElement(0, 1), rotationMatrix.getElement(1, 1));

            if(IsEqual<float>(std::cos(m_Pitch), 0.0f))
            {
                m_Pitch  = 0.0f;
                m_Roll = std::atan2(rotationMatrix.getElement(1, 0), rotationMatrix.getElement(0, 0));
            }
        }

        Euler::Euler(Quaternion const& quaternion)
        {
            // Source: 
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm

            static const float PoleSingularity = 0.4999995f;

            float qw = quaternion.w;
            float qx = quaternion.x;
            float qy = quaternion.y;
            float qz = quaternion.z;

            float qww = qw * qw;
            float qxx = qx * qx;
            float qyy = qy * qy;
            float qzz = qz * qz;

            float test = (qz * qx) - (qw * qy);

            //--------------------------------------------------------

            m_Yaw = atan2(2.0f * ((qw * qz) + (qx * qy)), (1.0f - 2.0f * (qyy + qzz)));

            if(test > PoleSingularity)
            {
                m_Roll  = m_Yaw - 2.0f * atan2(qx, qw);
                m_Pitch = 1.57079633f;    // 90 degrees
            }
            else if(test < -PoleSingularity)
            {
                m_Roll  = -m_Yaw - 2.0f * atan2(qx, qw);
                m_Pitch = 4.71238898f;    // 270 degrees
            }
            else
            {
                m_Roll  = atan2(-2.0f * ((qw * qx) + (qy * qz)), 1.0f - 2.0f * (qxx + qyy));
                m_Pitch = asin(2.0f * test);
            }

            normalise();
        }

        Euler::~Euler()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //------------------------------------------------------------
        // GETTERS / SETTERS
        //------------------------------------------------------------

        float Euler::getYaw() const
        {
            return RadiansToDegrees<float>(m_Yaw);
        }

        float Euler::getPitch() const
        {
            return RadiansToDegrees<float>(m_Pitch);
        }

        float Euler::getRoll() const
        {
            return RadiansToDegrees<float>(m_Roll);
        }

        void Euler::setYaw(float const& yaw)
        {
            m_Yaw = yaw;
        }

        void Euler::setPitch(float const& pitch)
        {
            m_Pitch = pitch;
        }

        void Euler::setRoll(float const& roll)
        {
            m_Roll = roll;
        }

        //------------------------------------------------------------
        // CONVERSIONS
        //------------------------------------------------------------

        Matrix3x3f Euler::toRotationMatrix() const
        {
            return Matrix3x3f(*this);
        }

        Quaternion Euler::toQuaternion() const
        {
            return Quaternion(*this);
        }

        //------------------------------------------------------------
        // OPERATIONS
        //------------------------------------------------------------

        void Euler::normalise()
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