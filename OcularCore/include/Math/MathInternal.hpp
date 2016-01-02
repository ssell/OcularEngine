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

/**
 * Various defines strictly for internal use.
 * These structures are employed so that there are no GLM, etc. reference visible to the end user.
 */

#pragma once
#ifndef __H__OCULAR_MATH_INTERNAL__H__
#define __H__OCULAR_MATH_INTERNAL__H__

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Math
     * @{
     */
    namespace Math
    {
        struct Matrix3x3_Internal
        { 
            Matrix3x3_Internal(glm::mat3x3 const& data);
            Matrix3x3_Internal();
            
            glm::mat3x3 matrix;
        };

        struct Matrix4x4_Internal
        { 
            Matrix4x4_Internal(glm::mat4x4 const& data);
            Matrix4x4_Internal();
            
            glm::mat4x4 matrix;
        };

        struct Quaternion_Internal
        {
            Quaternion_Internal(glm::quat const& data);
            Quaternion_Internal();

            glm::quat quat;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif