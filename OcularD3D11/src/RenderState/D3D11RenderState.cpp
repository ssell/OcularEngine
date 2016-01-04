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
              m_D3DBlendState(nullptr),
              m_D3DPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        {

        }

        D3D11RenderState::~D3D11RenderState()
        {
            if(m_D3DRasterizerState)
            {
                m_D3DRasterizerState->Release();
                m_D3DRasterizerState = nullptr;
            }

            if(m_D3DDepthStencilState)
            {
                m_D3DDepthStencilState->Release();
                m_D3DDepthStencilState = nullptr;
            }

            if(m_D3DBlendState)
            {
                m_D3DBlendState->Release();
                m_D3DBlendState = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11RenderState::bind()
        {
            if(m_IsRasterStateDirty)
            {
                if(!createD3DRasterizerState())
                {
                    OcularLogger->error("Failed to create updated D3D Rasterizer State", OCULAR_INTERNAL_LOG("D3D11RenderState", "bind"));
                }

                m_IsRasterStateDirty = false;
            }

            if(m_IsDepthStencilStateDirty)
            {
                if(!createD3DDepthStencilState())
                {
                    OcularLogger->error("Failed to create updated D3D Depth Stencil State", OCULAR_INTERNAL_LOG("D3D11RenderState", "bind"));
                }

                m_IsDepthStencilStateDirty = false;
            }

            if(m_IsBlendStateDirty)
            {
                if(!createD3DBlendState())
                {
                    OcularLogger->error("Failed to create updated D3D Blend State", OCULAR_INTERNAL_LOG("D3D11RenderState", "bind"));
                }

                m_IsBlendStateDirty = false;
            }

            const float blendFactor[4] = { m_BlendState.blendFactor.x, m_BlendState.blendFactor.y, m_BlendState.blendFactor.z, m_BlendState.blendFactor.w };

            m_D3DDeviceContext->RSSetState(m_D3DRasterizerState);
            m_D3DDeviceContext->OMSetDepthStencilState(m_D3DDepthStencilState, 1);
            m_D3DDeviceContext->OMSetBlendState(m_D3DBlendState, blendFactor, 0xffffffff);
            m_D3DDeviceContext->IASetPrimitiveTopology(m_D3DPrimitiveTopology);
        }

        void D3D11RenderState::setDepthStencilState(DepthStencilState const& state)
        {
            if(!Math::IsEqual<float>(state.depthBias.depthBias, m_DepthStencilState.depthBias.depthBias) ||
               !Math::IsEqual<float>(state.depthBias.depthBiasClamp, m_DepthStencilState.depthBias.depthBiasClamp) ||
               !Math::IsEqual<float>(state.depthBias.slopeScaledDepthBias, m_DepthStencilState.depthBias.slopeScaledDepthBias))
            {
                // D3D11 handles depth bias in the rasterizer state
                m_IsRasterStateDirty = true;
            }

            m_DepthStencilState = state;
            m_IsDepthStencilStateDirty = true;
        }

        ID3D11RasterizerState* D3D11RenderState::getD3DRasterizerState()
        {
            return m_D3DRasterizerState;
        }

        ID3D11DepthStencilState* D3D11RenderState::getD3DDepthStencilState()
        {
            return m_D3DDepthStencilState;
        }

        ID3D11BlendState* D3D11RenderState::getD3DBlendState()
        {
            return m_D3DBlendState;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11RenderState::createD3DRasterizerState()
        {
            bool result = true;

            const D3D11_RASTERIZER_DESC descr = createRenderStateDescr();
            const HRESULT hResult = m_D3DDevice->CreateRasterizerState(&descr, &m_D3DRasterizerState);

            if(FAILED(hResult))
            {
                OcularLogger->error("Failed to create new D3D11 RasterizerState", OCULAR_INTERNAL_LOG("D3D11RenderState", "createD3DRasterizerState"));
                result = false;
            }

            return result;
        }

        bool D3D11RenderState::createD3DDepthStencilState()
        {
            bool result = true;

            const D3D11_DEPTH_STENCIL_DESC descr = createDepthStencilStateDescr();
            const HRESULT hResult = m_D3DDevice->CreateDepthStencilState(&descr, &m_D3DDepthStencilState);

            if(FAILED(hResult))
            {
                OcularLogger->error("Failed to create new D3D11 DepthStencilState", OCULAR_INTERNAL_LOG("D3D11RenderState", "createD3DDepthStencilState"));
                result = false;
            }

            return result;
        }

        bool D3D11RenderState::createD3DBlendState()
        {
            bool result = true;

            const D3D11_BLEND_DESC descr = createBlendStateDescr();
            const HRESULT hResult = m_D3DDevice->CreateBlendState(&descr, &m_D3DBlendState);

            if(FAILED(hResult))
            {
                OcularLogger->error("Failed to create new D3D11 BlendState", OCULAR_INTERNAL_LOG("D3D11RenderState", "createD3DBlendState"));
                result = false;
            }

            return result;
        }

        D3D11_RASTERIZER_DESC D3D11RenderState::createRenderStateDescr()
        {
            D3D11_RASTERIZER_DESC result;
            ZeroMemory(&result, sizeof(D3D11_RASTERIZER_DESC));

            //------------------------------------------------------------------------------
            // Fill Mode

            switch(m_RasterState.fillMode)
            {
            case FillMode::Wireframe:
                result.FillMode = D3D11_FILL_WIREFRAME;
                break;

            case FillMode::Solid:
            default:
                result.FillMode = D3D11_FILL_SOLID;
                break;
            }

            //------------------------------------------------------------------------------
            // Cull Mode

            switch(m_RasterState.cullMode)
            {
            case CullMode::None:
                result.CullMode = D3D11_CULL_NONE;
                break;

            case CullMode::Front:
                result.CullMode = D3D11_CULL_FRONT;
                break;

            case CullMode::Back:
            default:
                result.CullMode = D3D11_CULL_BACK;
                break;
            }

            //------------------------------------------------------------------------------
            // Cull Direction

            switch(m_RasterState.cullDirection)
            {
            case CullDirection::Clockwise:
                result.FrontCounterClockwise = FALSE;
                break;

            case CullDirection::CounterClockwise:
            default:
                result.FrontCounterClockwise = TRUE;
                break;
            }

            //------------------------------------------------------------------------------
            // Primtive Style

            switch(m_RasterState.primitiveStyle)
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

            //------------------------------------------------------------------------------
            // Enable Depth Testing

            if(m_DepthStencilState.enableDepthTesting)
            {
                result.DepthClipEnable = TRUE;
            }
            else
            {
                result.DepthClipEnable = FALSE;
            }

            //------------------------------------------------------------------------------
            // Enable Scissor Testing

            if(m_DepthStencilState.enableScissorTesting)
            {
                result.ScissorEnable = TRUE;
            }
            else
            {
                result.ScissorEnable = FALSE;
            }

            //------------------------------------------------------------------------------
            // Enable Multisampling

            result.MultisampleEnable = m_RasterState.enableMultisampling;

            //------------------------------------------------------------------------------
            // Enable Line Antialiasing
            
            result.AntialiasedLineEnable = m_RasterState.enableLineAntialiasing;

            //------------------------------------------------------------------------------
            // Depth Bias

            result.DepthBias = static_cast<int32_t>(m_DepthStencilState.depthBias.depthBias);
            result.DepthBiasClamp = m_DepthStencilState.depthBias.depthBiasClamp;
            result.SlopeScaledDepthBias = m_DepthStencilState.depthBias.slopeScaledDepthBias;

            return result;
        }

        D3D11_DEPTH_STENCIL_DESC D3D11RenderState::createDepthStencilStateDescr()
        {
            D3D11_DEPTH_STENCIL_DESC result;
            ZeroMemory(&result, sizeof(D3D11_DEPTH_STENCIL_DESC));

            result.DepthEnable                  = m_DepthStencilState.enableDepthTesting;
            result.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
            result.DepthFunc                    = D3D11_COMPARISON_LESS;
            result.StencilEnable                = m_DepthStencilState.enableScissorTesting;
            result.StencilReadMask              = 0xFF;
            result.StencilWriteMask             = 0xFF;
            result.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
            result.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
            result.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
            result.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
            result.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
            result.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
            result.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
            result.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;

            return result;
        }

        D3D11_BLEND_DESC D3D11RenderState::createBlendStateDescr()
        {
            D3D11_BLEND_DESC result;
            ZeroMemory(&result, sizeof(D3D11_BLEND_DESC));

            D3D11_RENDER_TARGET_BLEND_DESC descr;
            ZeroMemory(&descr, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

            descr.SrcBlend       = convertBlendType(m_BlendState.srcBlend);
            descr.DestBlend      = convertBlendType(m_BlendState.destBlend);
            descr.SrcBlendAlpha  = convertBlendType(m_BlendState.alphaSrcBlend);
            descr.DestBlendAlpha = convertBlendType(m_BlendState.alphaDestBlend);
            descr.BlendOp        = convertBlendEquation(m_BlendState.blendEquation);
            descr.BlendOpAlpha   = convertBlendEquation(m_BlendState.alphaBlendEquation);
            descr.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

            result.AlphaToCoverageEnable = false;
            result.IndependentBlendEnable = false;
            
            for(uint32_t i = 0; i < 8; i++)
            {
                // Maximum of 8 render targets
                // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476087(v=vs.85).aspx
                result.RenderTarget[i] = descr;
            }

            return result;
        }

        D3D11_BLEND D3D11RenderState::convertBlendType(BlendType const type) const
        {
            D3D11_BLEND result;

            switch(type)
            {
            case BlendType::Zero:
                result = D3D11_BLEND_ZERO;
                break;

            case BlendType::One:
                result = D3D11_BLEND_ONE;
                break;

            case BlendType::SrcColor:
                result = D3D11_BLEND_SRC_COLOR;
                break;

            case BlendType::OneMinusSrcColor:
                result = D3D11_BLEND_INV_SRC_COLOR;
                break;

            case BlendType::SrcAlpha:
                result = D3D11_BLEND_SRC_ALPHA;
                break;

            case BlendType::OneMinusSrcAlpha:
                result = D3D11_BLEND_INV_SRC_ALPHA;
                break;

            case BlendType::DestAlpha:
                result = D3D11_BLEND_DEST_ALPHA;
                break;

            case BlendType::OneMinusDestAlpha:
                result = D3D11_BLEND_INV_DEST_ALPHA;
                break;

            case BlendType::DestColor:
                result = D3D11_BLEND_DEST_COLOR;
                break;

            case BlendType::OneMinusDestColor:
                result = D3D11_BLEND_INV_DEST_COLOR;
                break;

            case BlendType::AlphaSaturate:
                result = D3D11_BLEND_SRC_ALPHA_SAT;
                break;

            case BlendType::BlendFactor:
                result = D3D11_BLEND_BLEND_FACTOR;
                break;

            case BlendType::OneMinusBlendFactor:
                result = D3D11_BLEND_INV_BLEND_FACTOR;
                break;

            case BlendType::Src1Color:
                result = D3D11_BLEND_SRC1_COLOR;
                break;

            case BlendType::OneMinusSrc1Color:
                result = D3D11_BLEND_INV_SRC1_COLOR;
                break;

            case BlendType::Src1Alpha:
                result = D3D11_BLEND_SRC1_ALPHA;
                break;

            case BlendType::OneMinusSrc1Alpha:
                result = D3D11_BLEND_INV_SRC1_ALPHA;
                break;
                
            case BlendType::AlphaBlendFactor:
            case BlendType::OneMinusAlphaBlendFactor:
            default:
                result = D3D11_BLEND_ZERO;
                OcularLogger->warning("Unknown or Invalid blend type ", static_cast<uint32_t>(type), " specified for D3D11. Defaulting to D3D11_BLEND_ZERO", OCULAR_INTERNAL_LOG("D3D11RenderState", "convertBlendType"));
                break;
            }

            return result;
        }

        D3D11_BLEND_OP D3D11RenderState::convertBlendEquation(BlendEquation const equation) const
        {
            D3D11_BLEND_OP result;

            switch(equation)
            {
            case BlendEquation::Add:
                result = D3D11_BLEND_OP_ADD;
                break;

            case BlendEquation::Subtract:
                result = D3D11_BLEND_OP_SUBTRACT;
                break;

            case BlendEquation::ReverseSubtract:
                result = D3D11_BLEND_OP_REV_SUBTRACT;
                break;

            case BlendEquation::Min:
                result = D3D11_BLEND_OP_MIN;
                break;

            case BlendEquation::Max:
                result = D3D11_BLEND_OP_MAX;
                break;

            default:
                result = D3D11_BLEND_OP_ADD;
                OcularLogger->warning("Unknown or Invalid blend equation ", static_cast<uint32_t>(equation), " specified for D3D11. Default to D3D11_BLEND_OP_ADD", OCULAR_INTERNAL_LOG("D3D11RenderState", "convertBlendType"));
                break;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}