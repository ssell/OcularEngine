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
        /*! Sample filtering modes */
        enum class TextureFilterMode : unsigned
        {
            Point = 0,     ///< Use Point filtering
            Bilinear,        ///< Use Bilinear filtering
            Trilinear,       ///< Use Trilinear filtering
            Anisotropic      ///< Use Anisotropic filtering
        };

        enum class TextureUsageMode : unsigned
        {
            Static = 0x0,    ///< Texture will not be updated at runtime
            Dynamic          ///< Texture may be updated at runtime
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