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
#ifndef __H__OCULAR_GRAPHICS_DEPTH_STENCIL_STATE__H__
#define __H__OCULAR_GRAPHICS_DEPTH_STENCIL_STATE__H__

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
         *
         */
        enum class DepthStencilComparison
        {
            AlwaysPass = 0,       ///< Always passes the comparison
            NeverPass,            ///< Never passes the comparison
            Equal,                ///< Passes if the source and destination values are equal
            NotEqual,             ///< Passes if the source and destination values are not equal
            Less,                 ///< Passes if the source value is less than the destination value
            LessEqual,            ///< Passes if the source value is less than or equal to the destination value
            Greater,              ///< Passes if the source value is greater than the destination value
            GreaterEqual,         ///< Passes if the source value is greater than or equal to the destination value
            Undefined
        };

        /**
         * Defines the operation to be performed upon the stencil buffer data.
         */
        enum class StencilOperation
        {
            Keep = 0,             ///< Keep the existing stencil data
            Replace,              ///< Replace the stencil data with the reference value (DepthStencilState::stencilReferenceValue)
            Zero,                 ///< Set the stencil data to 0
            Invert,               ///< Invert the stencil data
            IncreaseClamp,        ///< Increment the data by 1 and clamp to 255 if necessary
            DecreaseClamp,        ///< Decrement the data by 1 and clamp to 0 if necessary
            IncreaseWrap,         ///< Increment the data by 1 and wrap to 0 if necessary
            DecreaseWrap,         ///< Decrement the data by 1 and wrap to 255 if necessary
            Undefined
        };

        /**
         * \struct DepthBiasState
         */
        struct DepthBiasState
        {
            DepthBiasState()
                : depthBias(0.0f),
                  depthBiasClamp(0.0f),
                  slopeScaledDepthBias(0.0f)
            {

            }

            //------------------------------------------------------------

            float depthBias;
            float depthBiasClamp;
            float slopeScaledDepthBias;
        };

        /**
         * \struct StencilFaceDescr
         */
        struct StencilFaceDescr
        {
            StencilFaceDescr()
                : stencilPassOp(StencilOperation::Keep),
                  stencilFailOp(StencilOperation::Keep),
                  stencilPassDepthFailOp(StencilOperation::Keep),
                  comparisonFunction(DepthStencilComparison::AlwaysPass)
            {

            }

            //------------------------------------------------------------

            StencilOperation stencilPassOp;             ///< Operation to perform when both stencil and depth testing passes
            StencilOperation stencilFailOp;             ///< Operation to perform when stencil testing fails
            StencilOperation stencilPassDepthFailOp;    ///< Operation to perform when stencil testing passes, but depth testing fails

            DepthStencilComparison comparisonFunction;  ///< Function to compare source data against destination data 
        };

        /**
         * \struct DepthStencilState
         */
        struct DepthStencilState
        {
            DepthStencilState()
                : enableDepthTesting(true),
                  enableStencilTesting(false),
                  stencilReferenceValue(1),
                  stencilReadMask(0xFF),
                  stencilWriteMask(0xFF)
            {

            }

            //------------------------------------------------------------

            DepthBiasState depthBias;            ///< 

            bool enableDepthTesting;             ///< 
            bool enableStencilTesting;           ///< 

            uint8_t stencilReferenceValue;       ///< 
            uint8_t stencilReadMask;             ///< 
            uint8_t stencilWriteMask;            ///< 

            StencilFaceDescr frontFace;          ///< 
            StencilFaceDescr backFace;           ///< 
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