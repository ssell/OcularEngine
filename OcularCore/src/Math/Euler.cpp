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