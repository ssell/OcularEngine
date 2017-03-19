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
#ifndef __H__OCULAR_GRAPHICS_D3D11_RENDER_STATE__H__
#define __H__OCULAR_GRAPHICS_D3D11_RENDER_STATE__H__

#include "Graphics/RenderState/RenderState.hpp"
#include <d3d11.h>

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
         * \class D3D11RenderState
         */
        class D3D11RenderState : public RenderState
        {
        public:

            D3D11RenderState(ID3D11Device* device, ID3D11DeviceContext* context);
            virtual ~D3D11RenderState();

            virtual void bind() override;
            virtual void setDepthStencilState(DepthStencilState const& state) override;

            ID3D11RasterizerState* getD3DRasterizerState();
            ID3D11DepthStencilState* getD3DDepthStencilState();
            ID3D11BlendState* getD3DBlendState();

            D3D11_PRIMITIVE_TOPOLOGY getD3DPrimitiveTopology();

        protected:

            bool createD3DRasterizerState();
            bool createD3DDepthStencilState();
            bool createD3DBlendState();

            D3D11_RASTERIZER_DESC createRenderStateDescr();
            D3D11_DEPTH_STENCIL_DESC createDepthStencilStateDescr();
            D3D11_BLEND_DESC createBlendStateDescr();

            D3D11_BLEND convertBlendType(BlendType type) const;
            D3D11_BLEND_OP convertBlendEquation(BlendEquation equation) const;
            D3D11_STENCIL_OP convertStencilOperation(StencilOperation operation) const;
            D3D11_COMPARISON_FUNC convertDepthStencilComparison(DepthStencilComparison comparison) const;

            //------------------------------------------------------------

            ID3D11Device*            m_D3DDevice;
            ID3D11DeviceContext*     m_D3DDeviceContext;
            ID3D11RasterizerState*   m_D3DRasterizerState;
            ID3D11DepthStencilState* m_D3DDepthStencilState;
            ID3D11BlendState*        m_D3DBlendState;
            D3D11_PRIMITIVE_TOPOLOGY m_D3DPrimitiveTopology;

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