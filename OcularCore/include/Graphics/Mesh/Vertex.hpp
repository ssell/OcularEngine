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
#ifndef __H__OCULAR_GRAPHICS_VERTEX__H__
#define __H__OCULAR_GRAPHICS_VERTEX__H__

#include "Math/Vector4.hpp"
#include "Math/Color.hpp"

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
        // No need for packing since all individual elements are 32-bits (or multiples thereof) long (?)

        /**
         * \struct Vertex
         */
        struct Vertex
        {
            float position[4];
           // Math::Vector3f position;    ///< Spatial coordinates of the vertex
           // Math::Vector4f color;       ///< Base color of the vertex
           // Math::Vector3f normal;      ///< Normal coordinates of the vertex
           // Math::Vector2f uv0;         ///< Texture coordinates of the vertex
           // Math::Vector2f uv1;         ///< Texture coordinates of the vertex
           // Math::Vector2f uv2;         ///< Texture coordinates of the vertex
           // Math::Vector2f uv3;         ///< Texture coordinates of the vertex

            //Vertex()
            //{
            //    color = Core::Color::ErrorPink();
            //}
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