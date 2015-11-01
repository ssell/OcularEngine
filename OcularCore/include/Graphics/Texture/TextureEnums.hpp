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
            RenderTexture2D
        };

        /**
         * \enum TextureFormat
         */
        enum class TextureFormat : unsigned
        {
            None = 0
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