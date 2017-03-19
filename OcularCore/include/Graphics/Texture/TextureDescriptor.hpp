/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_GRAPHICS_TEXTURE_DESCRIPTOR__H__
#define __H__OCULAR_GRAPHICS_TEXTURE_DESCRIPTOR__H__

#include <cstdint>
#include "TextureEnums.hpp"

//------------------------------------------------------------------------------------------

/*!
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
         * \struct TextureDescriptor
         *
         * A generic texture descriptor. Typically supplied
         * to the GraphicsDriver to create the API specific
         * texture instances.
         */
        struct TextureDescriptor
        {
            uint32_t width;                      ///< Width of the texture in pixels
            uint32_t height;                     ///< Height of the texture in pixels
            uint32_t mipmaps;                    ///< Levels of mipmaps to create. 0 creates an entire mipmap chain, 1 has the single texture level-of-detail, etc.
            uint32_t pixelSize;                  ///< Size of each pixel in bytes

            TextureType type;                    ///< The type of texture 
            TextureFormat format;                ///< The format of this texture
            TextureFilterMode filter;            ///< Filtering mode to apply to the texture when rendered

            TextureAccess gpuAccess;             ///< The level of access required by the GPU
            TextureAccess cpuAccess;             ///< The level of access requried by the CPU

            TextureDescriptor()
                : width(800), 
                  height(600), 
                  mipmaps(1), 
                  pixelSize(32),
                  type(TextureType::Texture2D), 
                  format(TextureFormat::R32G32B32A32Float), 
                  filter(TextureFilterMode::Point), 
                  gpuAccess(TextureAccess::ReadWrite), 
                  cpuAccess(TextureAccess::None)
            {

            }
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