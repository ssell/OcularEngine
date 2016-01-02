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
#ifndef __H__OCULAR_GRAPHICS_RENDER_STATE__H__
#define __H__OCULAR_GRAPHICS_RENDER_STATE__H__

#include "BlendState.hpp"
#include "RasterState.hpp"
#include "DepthStencilState.hpp"

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
             * Sets the RasterState settings for the application.
             * \note Must call bind to enable any changes.
             *
             * \param[in] state
             */
            virtual void  setRasterState(RasterState const& state);

            /**
             *
             */
            RasterState getRasterState() const;

            /**
             * Sets the BlendState settings for the application.
             * \note Must call bind to enable any changes.
             *
             * \param[in] state
             */
            virtual void  setBlendState(BlendState const& state);

            /**
             *
             */
            BlendState getBlendState() const;

            /**
             * Sets the DepthStencilState settings for the application.
             * \note Must call bind to enable any changes.
             *
             * \param[in] state
             */
            virtual void  setDepthStencilState(DepthStencilState const& state);

            /**
             *
             */
            DepthStencilState getDepthStencilState() const;

        protected:

            RasterState m_RasterState;
            BlendState m_BlendState;
            DepthStencilState m_DepthStencilState;

            bool m_IsRasterStateDirty;
            bool m_IsBlendStateDirty;
            bool m_IsDepthStencilStateDirty;

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