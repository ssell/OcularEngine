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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_SHADER_UNIFORMS_PER_CAMERA__H__
#define __H__OCULAR_GRAPHICS_SHADER_UNIFORMS_PER_CAMERA__H__

#include "Math/Matrix4x4.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \struct UniformPerCamera
         * \brief The fixed struct for all Uniform data for Cameras/Views.
         */
        struct UniformPerCamera
        {
            Math::Matrix4x4 viewMatrix;
            Math::Matrix4x4 projMatrix;
            Math::Matrix4x4 viewProjMatrix;
            Math::Vector4f eyePosition;

            static uint32_t Size() { return 208; }
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