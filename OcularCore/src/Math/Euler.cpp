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

#include "Math/Euler.hpp"
#include "Math/Matrix3x3.hpp"
#include "Math/Vector3.hpp"
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

        Euler::Euler(Vector3<float> const& vector)
        {
            Vector3<float> normalized = vector.getNormalized();

            m_Yaw   = vector.x;
            m_Pitch = vector.y;
            m_Roll  = vector.z;
        }

        Euler::Euler(Matrix3x3 const& rotationMatrix)
        {
            Quaternion quat(rotationMatrix);

            m_Yaw   = quat.getYaw();
            m_Pitch = quat.getPitch();
            m_Roll  = quat.getRoll();
        }

        Euler::Euler(Quaternion const& quaternion)
        {
            m_Yaw   = quaternion.getYaw();
            m_Pitch = quaternion.getPitch();
            m_Roll  = quaternion.getRoll();
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

        float Euler::getYawRadians() const
        {
            return m_Yaw;
        }

        float Euler::getPitch() const
        {
            return RadiansToDegrees<float>(m_Pitch);
        }

        float Euler::getPitchRadians() const
        {
            return m_Pitch;
        }

        float Euler::getRoll() const
        {
            return RadiansToDegrees<float>(m_Roll);
        }

        float Euler::getRollRadians() const
        {
            return m_Roll;
        }

        void Euler::setYaw(float const yaw)
        {
            m_Yaw = DegreesToRadians<float>(yaw);
        }

        void Euler::setYawRadians(float const yaw)
        {
            m_Yaw = yaw;
        }

        void Euler::setPitch(float const pitch)
        {
            m_Pitch = DegreesToRadians<float>(pitch);
        }

        void Euler::setPitchRadians(float const pitch)
        {
            m_Pitch = pitch;
        }

        void Euler::setRoll(float const roll)
        {
            m_Roll = DegreesToRadians<float>(roll);
        }

        void Euler::setRollRadians(float const roll)
        {
            m_Roll = roll;
        }

        //------------------------------------------------------------
        // CONVERSIONS
        //------------------------------------------------------------

        Matrix3x3 Euler::toRotationMatrix() const
        {
            return Matrix3x3(*this);
        }

        Quaternion Euler::toQuaternion() const
        {
            return Quaternion(*this);
        }

        //------------------------------------------------------------
        // OPERATIONS
        //------------------------------------------------------------

        float Euler::normalizeAxis(float const& angle) 
        {
            float result;
            
            result = Clamp(angle, 0.0f, 360.0f);

            if(result > 180.0f)
            {
                result -= 360.0f;
            }

            return result;
        }
        
        float Euler::denormalizeAxis(float const& angle) 
        {
            float result;
            
            result = fmod(angle, 360.0f);

            if(result < 0.0f)
            {
                result += 360.0f;
            }

            return result;
        }

        void Euler::normalize()
        {
            m_Yaw   = normalizeAxis(m_Yaw);
            m_Pitch = normalizeAxis(m_Pitch);
            m_Roll  = normalizeAxis(m_Roll);
        }

        Euler Euler::getNormalized() const
        {
            Euler result = *this;
            result.normalize();

            return result;
        }

        void Euler::denormalize() 
        {
            m_Yaw   = denormalizeAxis(m_Yaw);
            m_Pitch = denormalizeAxis(m_Pitch);
            m_Roll  = denormalizeAxis(m_Roll);
        }

        Euler Euler::getDenormalized() const
        {
            Euler result = *this;
            result.denormalize();

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