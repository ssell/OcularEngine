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

#include "stdafx.hpp"
#include "RenderState/D3D11RenderState.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11RenderState::D3D11RenderState(ID3D11Device* device, ID3D11DeviceContext* context)
            : RenderState(),
              m_D3DDevice(device),
              m_D3DDeviceContext(context),
              m_D3DRasterizerState(nullptr),
              m_D3DDepthStencilState(nullptr),
              m_IsRasterizerStateDirty(true),
              m_IsDepthStencilStateDirty(true),
              m_IsPrimitiveTopologyDirty(true),
              m_D3DPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        {
            ZeroMemory(&m_D3DRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
            m_D3DRasterizerDesc.FillMode              = D3D11_FILL_SOLID;
            m_D3DRasterizerDesc.CullMode              = D3D11_CULL_NONE; //D3D11_CULL_BACK;
            m_D3DRasterizerDesc.FrontCounterClockwise = true;
            m_D3DRasterizerDesc.DepthBias             = 0;
            m_D3DRasterizerDesc.DepthBiasClamp        = 0.0f;
            m_D3DRasterizerDesc.SlopeScaledDepthBias  = 0.0f;
            m_D3DRasterizerDesc.DepthClipEnable       = true;
            m_D3DRasterizerDesc.ScissorEnable         = false;
            m_D3DRasterizerDesc.MultisampleEnable     = false;
            m_D3DRasterizerDesc.AntialiasedLineEnable = false;

            ZeroMemory(&m_D3DDepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	        m_D3DDepthStencilDesc.DepthEnable                  = true;
	        m_D3DDepthStencilDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
	        m_D3DDepthStencilDesc.DepthFunc                    = D3D11_COMPARISON_LESS;
	        m_D3DDepthStencilDesc.StencilEnable                = true;
	        m_D3DDepthStencilDesc.StencilReadMask              = 0xFF;
	        m_D3DDepthStencilDesc.StencilWriteMask             = 0xFF;
	        m_D3DDepthStencilDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	        m_D3DDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	        m_D3DDepthStencilDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	        m_D3DDepthStencilDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
	        m_D3DDepthStencilDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
	        m_D3DDepthStencilDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
	        m_D3DDepthStencilDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
	        m_D3DDepthStencilDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;
        }

        D3D11RenderState::~D3D11RenderState()
        {
            if(m_D3DRasterizerState)
            {
                m_D3DRasterizerState->Release();
                m_D3DRasterizerState = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11RenderState::bind()
        {
            HRESULT hResult = S_OK;

            if(m_D3DDeviceContext && m_D3DDevice)
            {
                //--------------------------------------------------------
                // Update Rasterizer State

                if(m_IsRasterizerStateDirty)
                {
                    if(m_D3DRasterizerState)
                    {
                        m_D3DRasterizerState->Release();
                        m_D3DRasterizerState = nullptr;
                    }

                    hResult = m_D3DDevice->CreateRasterizerState(&m_D3DRasterizerDesc, &m_D3DRasterizerState);

                    if(hResult == S_OK)
                    {
                        m_D3DDeviceContext->RSSetState(m_D3DRasterizerState);
                        m_IsRasterizerStateDirty = false;
                    }
                    else
                    {
                        OcularLogger->error("Failed to create new Rasterizer State", OCULAR_INTERNAL_LOG("D3D11RenderState", "bind"));
                    }
                }

                //--------------------------------------------------------
                // Update Depth Stencil State

                if(m_IsDepthStencilStateDirty)
                {
                    if(m_D3DDepthStencilState)
                    {
                        m_D3DDepthStencilState->Release();
                        m_D3DDepthStencilState = nullptr;
                    }

                    hResult = m_D3DDevice->CreateDepthStencilState(&m_D3DDepthStencilDesc, &m_D3DDepthStencilState);

                    if(hResult == S_OK)
                    {
                        m_D3DDeviceContext->OMSetDepthStencilState(m_D3DDepthStencilState, 1);
                        m_IsDepthStencilStateDirty = false;
                    }
                    else
                    {
                        OcularLogger->error("Failed to create new Depth Stencil State", OCULAR_INTERNAL_LOG("D3D11RenderState", "bind"));
                    }
                }

                //--------------------------------------------------------
                // Update Primitive Topology

                if(m_IsPrimitiveTopologyDirty)
                {
                    m_D3DDeviceContext->IASetPrimitiveTopology(m_D3DPrimitiveTopology);
                    m_IsPrimitiveTopologyDirty = false;
                }
            }
            else
            {
                OcularLogger->error("D3D11 Device and/or Context is NULL", OCULAR_INTERNAL_LOG("D3D11RenderState", "bind"));
            }
        }

        void D3D11RenderState::setFillMode(FillMode const mode)
        {
            if(m_FillMode != mode)
            {
                RenderState::setFillMode(mode);

                switch(mode)
                {
                case FillMode::Wireframe:
                    m_D3DRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
                    break;

                case FillMode::Solid:
                default:
                    m_D3DRasterizerDesc.FillMode = D3D11_FILL_SOLID;
                    break;
                }

                m_IsRasterizerStateDirty = true;
            }
        }

        void D3D11RenderState::setCullMode(CullMode const mode)
        {
            if(m_CullMode != mode)
            {
                RenderState::setCullMode(mode);

                switch(mode)
                {
                case CullMode::None:
                    m_D3DRasterizerDesc.CullMode = D3D11_CULL_NONE;
                    break;

                case CullMode::Front:
                    m_D3DRasterizerDesc.CullMode = D3D11_CULL_FRONT;
                    break;

                case CullMode::Back:
                default:
                    m_D3DRasterizerDesc.CullMode = D3D11_CULL_BACK;
                    break;
                }

                m_IsRasterizerStateDirty = true;
            }
        }

        void D3D11RenderState::setCullDirection(CullDirection const direction)
        {
            if(m_CullDirection != direction)
            {
                RenderState::setCullDirection(direction);

                if(direction == CullDirection::Clockwise)
                {
                    m_D3DRasterizerDesc.FrontCounterClockwise = false;
                }
                else
                {
                    m_D3DRasterizerDesc.FrontCounterClockwise = true;
                }

                m_IsRasterizerStateDirty = true;
            }
        }

        void D3D11RenderState::setPrimitiveStyle(PrimitiveStyle const style)
        {
            if(m_PrimitiveStyle != style)
            {
                RenderState::setPrimitiveStyle(style);

                switch(style)
                {
                case PrimitiveStyle::TriangleStrip:
                    m_D3DPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                    break;

                case PrimitiveStyle::PointList:
                    m_D3DPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
                    break;

                case PrimitiveStyle::LineList:
                    m_D3DPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                    break;

                case PrimitiveStyle::LineStrip:
                    m_D3DPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
                    break;

                case PrimitiveStyle::TriangleList:
                default:
                    m_D3DPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                    break;

                }

                m_IsPrimitiveTopologyDirty = true;
            }
        }

        void D3D11RenderState::setDepthTesting(bool const testing)
        {
            if(m_EnableDepthTesting != testing)
            {
                RenderState::setDepthTesting(testing);

                m_D3DRasterizerDesc.DepthClipEnable = testing;
                m_IsRasterizerStateDirty = true;
            }
        }

        void D3D11RenderState::setScissorTesting(bool const testing)
        {
            if(m_EnableScissorTesting != testing)
            {
                RenderState::setScissorTesting(testing);

                m_D3DRasterizerDesc.ScissorEnable = testing;
                m_IsRasterizerStateDirty = true;
            }
        }

        void D3D11RenderState::setRenderTextureMultisampling(bool const multisampling)
        {
            if(m_EnableMultisampling != multisampling)
            {
                RenderState::setRenderTextureMultisampling(multisampling);

                m_D3DRasterizerDesc.MultisampleEnable = multisampling;
                m_IsRasterizerStateDirty = true;
            }
        }

        void D3D11RenderState::setLineAntialising(bool const antialiasing)
        {
            if(m_EnableLineAntialiasing != antialiasing)
            {
                RenderState::setLineAntialising(antialiasing);

                m_D3DRasterizerDesc.AntialiasedLineEnable = antialiasing;
                m_IsRasterizerStateDirty = true;
            }
        }



        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}