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
#ifndef __H__OCULAR_GRAPHICS_RENDER_STATE__H__
#define __H__OCULAR_GRAPHICS_RENDER_STATE__H__

#include "RenderEnums.hpp"

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
         * \class RenderState
         *
         * Default states:
         *
         *             Fill Mode: Solid
         *             Cull Mode: Back
         *        Cull Direction: CounterClockwise
         *       Primitive Style: TriangleList
         *         Depth Testing: true
         *       Scissor Testing: true
         *         Multisampling: true
         *     Line Antialiasing: true
         */
        class RenderState
        {
        public:

            RenderState();
            ~RenderState();
            
            /**
             * Sets the current RenderState.
             */
            virtual void bind();

            /**
             * ...
             *
             * \param[in] mode
             */
            virtual void setFillMode(FillMode mode);

            /**
             * \return ...
             */
            FillMode getFillMode() const;
            
            /**
             * ...
             *
             * \param[in] mode
             */
            virtual void setCullMode(CullMode mode);

            /**
             * \return ...
             */
            CullMode getCullMode() const;
            
            /**
             * ...
             *
             * \param[in] direction
             */
            virtual void setCullDirection(CullDirection direction);

            /**
             * \return ...
             */
            CullDirection getCullDirection() const;
            
            /**
             * ...
             *
             * \param[in] style
             */
            virtual void setPrimitiveStyle(PrimitiveStyle style);

            /**
             * \return ...
             */
            PrimitiveStyle getPrimitiveStyle() const;
            
            /**
             * ...
             *
             * \param[in] testing
             */
            virtual void setDepthTesting(bool testing);

            /**
             * \return ...
             */
            bool getDepthTesting() const;
            
            /**
             * ...
             *
             * \param[in] testing
             */
            virtual void setScissorTesting(bool testing);

            /**
             * \return ...
             */
            bool getScissorTesting() const;
            
            /**
             * ...
             *
             * \param[in] multisampling
             */
            virtual void setRenderTextureMultisampling(bool multisampling);

            /**
             * \return ...
             */
            bool getRenderTextureMultisampling() const;
            
            /**
             * ...
             *
             * \param[in] antialiasing
             */
            virtual void setLineAntialising(bool antialiasing);

            /**
             * \return ...
             */
            bool getLineAntialising() const;

        protected:

            FillMode m_FillMode;                  ///< Determines if triangles are filled during rasterization
            CullMode m_CullMode;                  ///< Determines what type of triangles to cull
            CullDirection m_CullDirection;        ///< Determines what is considered front/back-facing triangles
            PrimitiveStyle m_PrimitiveStyle;      ///< Determines how vertex data is interpreted

            bool m_EnableDepthTesting;            ///< Enables/disables depth testing
            bool m_EnableScissorTesting;          ///< Enables/disables scissor testing
            bool m_EnableMultisampling;           ///< Enables/disable RenderTexture antialiasing
            bool m_EnableLineAntialiasing;        ///< Enables line primitive antialiasing

        private:
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