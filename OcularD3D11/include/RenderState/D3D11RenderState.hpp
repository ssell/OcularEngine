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

            virtual void setFillMode(FillMode mode) override;
            virtual void setCullMode(CullMode mode) override;
            virtual void setCullDirection(CullDirection direction) override;
            virtual void setPrimitiveStyle(PrimitiveStyle style) override;
            virtual void setDepthTesting(bool testing) override;
            virtual void setScissorTesting(bool testing) override;
            virtual void setRenderTextureMultisampling(bool multisampling) override;
            virtual void setLineAntialising(bool antialiasing) override;

            ID3D11RasterizerState* getD3DRasterizerState();
            D3D11_PRIMITIVE_TOPOLOGY getD3DPrimitiveTopology();

            bool getIsRasterizerStateDirty() const;
            bool getIsPrimitiveTopologyDirty() const;

        protected:

            bool m_IsRasterizerStateDirty;
            bool m_IsPrimitiveTopologyDirty;

            ID3D11Device*            m_D3DDevice;
            ID3D11DeviceContext*     m_D3DDeviceContext;
            ID3D11RasterizerState*   m_D3DRasterizerState;
            D3D11_RASTERIZER_DESC    m_D3DRasterizerDesc;
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