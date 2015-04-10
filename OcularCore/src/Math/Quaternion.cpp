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
        
        }

        Quaternion::Quaternion(Euler const& euler)
        {
        
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

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}