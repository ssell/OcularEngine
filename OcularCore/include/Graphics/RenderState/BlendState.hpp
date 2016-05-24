/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_GRAPHICS_BLEND_STATE__H__
#define __H__OCULAR_GRAPHICS_BLEND_STATE__H__

#include "Math/Vector4.hpp"

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
         * \enum BlendState
         */
        enum class BlendType
        {
            Zero = 0,                                 ///< Maps to D3D11_BLEND_ZERO and GL_ZERO
            One,                                      ///< Maps to D3D11_BLEND_ONE and GL_ONE
            SrcColor,                                 ///< Maps to D3D11_BLEND_SRC_COLOR and GL_SRC_COLOR
            OneMinusSrcColor,                         ///< Maps to D3D11_BLEND_INV_SRC_COLOR and GL_ONE_MINUS_SRC_COLOR
            SrcAlpha,                                 ///< Maps to D3D11_BLEND_SRC_ALPHA and GL_SRC_ALPHA
            OneMinusSrcAlpha,                         ///< Maps to D3D11_BLEND_INV_SRC_ALPHA and GL_ONE_MINUS_SRC_ALPHA
            DestAlpha,                                ///< Maps to D3D11_BLEND_DEST_ALPHA and GL_DST_ALPHA
            OneMinusDestAlpha,                        ///< Maps to D3D11_BLEND_INV_DEST_ALPHA and GL_ONE_MINUS_DST_ALPHA
            DestColor,                                ///< Maps to D3D11_BLEND_DEST_COLOR and GL_DST_COLOR
            OneMinusDestColor,                        ///< Maps to D3D11_BLEND_INV_DEST_COLOR and GL_ONE_MINUS_DST_COLOR
            AlphaSaturate,                            ///< Maps to D3D11_BLEND_SRC_ALPHA_SAT and GL_SRC_ALPHA_SATURATE
            BlendFactor,                              ///< Maps to D3D11_BLEND_BLEND_FACTOR and GL_CONSTANT_COLOR
            OneMinusBlendFactor,                      ///< Maps to D3D11_BLEND_INV_BLEND_FACTOR and GL_ONE_MINUS_CONSTANT_COLOR
            AlphaBlendFactor,                         ///< Maps to GL_CONSTANT_ALPHA (not supported on D3D renderers)
            OneMinusAlphaBlendFactor,                 ///< Maps to GL_ONE_MINUS_CONSTANT_ALPHA (not supported on D3D renderers)
            Src1Color,                                ///< Maps to D3D11_BLEND_SRC1_COLOR and GL_SRC1_COLOR
            OneMinusSrc1Color,                        ///< Maps to D3D11_BLEND_INV_SRC1_COLOR and GL_ONE_MINUS_SRC1_COLOR
            Src1Alpha,                                ///< Maps to D3D11_BLEND_SRC1_ALPHA and GL_SRC1_ALPHA
            OneMinusSrc1Alpha                         ///< Maps to D3D11_BLEND_INV_SRC1_ALPHA and GL_ONE_MINUS_SRC1_ALPHA
        };

        /**
         * \enum BlendEquation
         */
        enum class BlendEquation
        {
            Add = 0,                                  ///< Maps to D3D11_BLEND_OP_ADD and GL_FUNC_ADD
            Subtract,                                 ///< Maps to D3D11_BLEND_OP_SUBTRACT and GL_FUNC_SUBTRACT
            ReverseSubtract,                          ///< Maps to D3D11_BLEND_OP_REV_SUBTRACT and GL_FUNC_REVERSE_SUBTRACT
            Min,                                      ///< Maps to D3D11_BLEND_OP_MIN and GL_MIN
            Max                                       ///< Maps tp D3D11_BLEND_OP_MAX and GL_MAX
        };

        /**
         * \struct BlendState
         *
         * |    State Component   | Default Value |
         * | -------------------- | ------------- |
         * | Enable Blending      | True          |
         * | Src Blend            | One           |
         * | Dest Blend           | Zero          |
         * | Alpha Src Blend      | One           |
         * | Alpha Dest Blend     | Zero          |
         * | Blend Equation       | Add           |
         * | Alpha Blend Equation | Add           |
         * | Blend Factor         | (1, 1, 1, 1)  |
         */
        struct BlendState
        {
            bool enableBlending;                      ///< If TRUE, blending operations will be performed.

            BlendType srcBlend;                       ///< The operation to perform on pixel RGB values output from the Fragment/Pixel shaders.
            BlendType destBlend;                      ///< The operation to perform on the current pixel RGB value in the RenderTexture.
            BlendType alphaSrcBlend;                  ///< The operation to perform on pixel alpha value output from the Fragment/Pixel shaders.
            BlendType alphaDestBlend;                 ///< The operation to perform on the current pixel alpha value in the RenderTexture.

            BlendEquation blendEquation;              ///< How to combine the srcBlend and destBlend operations.
            BlendEquation alphaBlendEquation;         ///< How to combine the alphaSrcBlend and alphaDestBlend operations.

            Math::Vector4f blendFactor;               ///< Custom blend factor employed when using BlendType::BlendFactor, BlendType::OneMinusBlendFactor, BlendType::AlphaBlendFactor, and/or BlendType::OneMinusAlphaBlendFactor
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