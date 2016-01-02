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

#include "Math/MathInternal.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // Matrix3x3
        //----------------------------------------------------------------------------------

        Matrix3x3_Internal::Matrix3x3_Internal(glm::mat3x3 const& data)
            : matrix(data)
        {

        }

        Matrix3x3_Internal::Matrix3x3_Internal()
        {

        }

        //----------------------------------------------------------------------------------
        // Matrix4x4
        //----------------------------------------------------------------------------------

        Matrix4x4_Internal::Matrix4x4_Internal(glm::mat4x4 const& data)
            : matrix(data)
        {

        }

        Matrix4x4_Internal::Matrix4x4_Internal()
        {

        }

        //----------------------------------------------------------------------------------
        // Quaternion
        //----------------------------------------------------------------------------------

        Quaternion_Internal::Quaternion_Internal(glm::quat const& data)
            : quat(data)
        {

        }

        Quaternion_Internal::Quaternion_Internal()
        {

        }
    }
}