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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_TEXTURE_ENUMS__H__
#define __H__OCULAR_GRAPHICS_TEXTURE_ENUMS__H__

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
         * \enum TextureFilterMode
         * \brief Sample filtering modes 
         */
        enum class TextureFilterMode : unsigned
        {
            Point = 0,       ///< Use Point filtering
            Bilinear,        ///< Use Bilinear filtering
            Trilinear,       ///< Use Trilinear filtering
            Anisotropic      ///< Use Anisotropic filtering
        };

        /**
         * \enum TextureAccess
         * \brief Describes how the texture will be used
         */
        enum class TextureAccess : unsigned 
        {
            ReadWrite = 0,
            ReadOnly,
            WriteOnly,
            None
        };

        /**
         * \enum TextureType
         * \note Not all texture types are supported by all APIs
         */
        enum class TextureType : unsigned
        {
            Texture2D = 0,
            RenderTexture2D,
            DepthTexture2D,
            CubeMap
        };

        /**
         * \enum TextureFormat
         */
        enum class TextureFormat : unsigned
        {
            R32G32B32A32Float = 0,    ///< Four-component 128-bit floating-point format with 32-bits per channel (RGBA)
            R32G32B32A32Unsigned,     ///< Four-component 128-bit unsigned integer format with 32-bits per channel (RGBA)
            R32G32B32A32Signed,       ///< Four-component 128-bit signed integer format with 32-bits per channel (RGBA)
            R32G32B32Float,           ///< Three-component 96-bit floating-point format with 32-bits per channel (RGB)
            R32G32B32Unsigned,        ///< Three-component 96-bit unsigned integer format with 32-bits per channel (RGB)
            R32G32B32Signed,          ///< Three-component 96 bit signed integer format with 32-bits per channel (RGB)
            R32G32Float,              ///< Two-component 64-bit floating-point format with 32-bits per channel (RG)
            R32G32Unsigned,           ///< Two-component 64-bit unsigned integer format with 32-bits per channel (RG)
            R32G32Signed,             ///< Two-component 64-bit signed integer format with 32-bits per channel (RG)
            R32Float,                 ///< Single component 32-bit floating-point format with 32-bits per channel (R)
            R32Unsigned,              ///< Single component 32-bit unsigned integer format with 32-bits per channel (R)
            R32Signed,                ///< Single component 32-bit signed integer format with 32-bits per channel (R)
            R16G16B16A16Float,        ///< Four-component 64-bit floating-point format with 16-bits per channel (RGBA)
            R16G16B16A16Unsigned,     ///< Four-component 64-bit unsigned integer format with 16-bits per channel (RGBA)
            R16G16B16A16Signed,       ///< Four-component 64-bit signed integer format with 16-bits per channel (RGBA)
            R16G16B16Float,           ///< Three-component 48-bit floating-point format with 16-bits per channel (RGB)
            R16G16B16Unsigned,        ///< Three-component 48-bit unsigned integer format with 16-bits per channel (RGB)
            R16G16B16Signed,          ///< Three-component 48 bit signed integer format with 16-bits per channel (RGB)
            R16G16Float,              ///< Two-component 32-bit floating-point format with 16-bits per channel (RG)
            R16G16Unsigned,           ///< Two-component 32-bit unsigned integer format with 16-bits per channel (RG)
            R16G16Signed,             ///< Two-component 32-bit signed integer format with 16-bits per channel (RG)
            R16Float,                 ///< Single component 16-bit floating-point format with 16-bits per channel (R)
            R16Unsigned,              ///< Single component 16-bit unsigned integer format with 16-bits per channel (R)
            R16Signed,                ///< Single component 16-bit signed integer format with 16-bits per channel (R)
            R8G8B8A8Float,            ///< Four-component 16-bit floating-point format with 8-bits per channel (RGBA)
            R8G8B8A8Unsigned,         ///< Four-component 16-bit unsigned integer format with 8-bits per channel (RGBA)
            R8G8B8A8Signed,           ///< Four-component 16-bit signed integer format with 8-bits per channel (RGBA)
            R8G8B8Float,              ///< Three-component 24-bit floating-point format with 8-bits per channel (RGB)
            R8G8B8Unsigned,           ///< Three-component 24-bit unsigned integer format with 8-bits per channel (RGB)
            R8G8B8Signed,             ///< Three-component 24 bit signed integer format with 8-bits per channel (RGB)
            R8G8Float,                ///< Two-component 16-bit floating-point format with 8-bits per channel (RG)
            R8G8Unsigned,             ///< Two-component 16-bit unsigned integer format with 8-bits per channel (RG)
            R8G8Signed,               ///< Two-component 16-bit signed integer format with 8-bits per channel (RG)
            R8Float,                  ///< Single component 8-bit floating-point format with 8-bits per channel (R)
            R8Unsigned,               ///< Single component 8-bit unsigned integer format with 8-bits per channel (R)
            R8Signed,                 ///< Single component 8-bit signed integer format with 8-bits per channel (R)
            Depth                     ///< API-dependent texture format for special depth textures
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