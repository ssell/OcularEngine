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

#include "Graphics/RenderState/RenderState.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        RenderState::RenderState()
            : m_IsRasterStateDirty(true),
              m_IsBlendStateDirty(true),
              m_IsDepthStencilStateDirty(true)
        {
            m_RasterState.fillMode               = FillMode::Solid;
            m_RasterState.cullMode               = CullMode::Back;
            m_RasterState.cullDirection          = CullDirection::CounterClockwise;
            m_RasterState.primitiveStyle         = PrimitiveStyle::TriangleList;
            m_RasterState.enableMultisampling    = true;
            m_RasterState.enableLineAntialiasing = true;

            m_BlendState.enableBlending     = false;
            m_BlendState.srcBlend           = BlendType::One;
            m_BlendState.destBlend          = BlendType::Zero;
            m_BlendState.alphaSrcBlend      = BlendType::One;
            m_BlendState.alphaDestBlend     = BlendType::Zero;
            m_BlendState.blendEquation      = BlendEquation::Add;
            m_BlendState.alphaBlendEquation = BlendEquation::Add;
            m_BlendState.blendFactor        = Math::Vector4f(1.0f, 1.0f, 1.0f, 1.0f);

            m_DepthStencilState.enableStencilTesting = true;
            m_DepthStencilState.frontFace.stencilPassOp = StencilOperation::IncreaseClamp;
            m_DepthStencilState.backFace.comparisonFunction = DepthStencilComparison::NeverPass;
            m_DepthStencilState.stencilReferenceValue = 0;
        }

        RenderState::~RenderState()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void RenderState::bind()
        {

        }

        void RenderState::setRasterState(RasterState const& state)
        {
            m_RasterState = state;
            m_IsRasterStateDirty = true;
        }

        RasterState RenderState::getRasterState() const
        {
            return m_RasterState;
        }

        void RenderState::setBlendState(BlendState const& state)
        {
            m_BlendState = state;
            m_IsBlendStateDirty = true;
        }

        BlendState RenderState::getBlendState() const
        {
            return m_BlendState;
        }

        void RenderState::setDepthStencilState(DepthStencilState const& state)
        {
            m_DepthStencilState = state;
            m_IsDepthStencilStateDirty;
        }

        DepthStencilState RenderState::getDepthStencilState() const
        {
            return m_DepthStencilState;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}