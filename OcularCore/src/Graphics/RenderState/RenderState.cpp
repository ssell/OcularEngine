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
            : m_FillMode(FillMode::Solid),
              m_CullMode(CullMode::Back),
              m_CullDirection(CullDirection::CounterClockwise),
              m_PrimitiveStyle(PrimitiveStyle::TriangleList),
              m_EnableDepthTesting(true),
              m_EnableScissorTesting(true),
              m_EnableMultisampling(true),
              m_EnableLineAntialiasing(true)
        {

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

        void RenderState::setFillMode(FillMode const mode)
        {
            m_FillMode = mode;
        }

        FillMode RenderState::getFillMode() const
        {
            return m_FillMode;
        }

        void RenderState::setCullMode(CullMode const mode)
        {
            m_CullMode = mode;
        }

        CullMode RenderState::getCullMode() const
        {
            return m_CullMode;
        }

        void RenderState::setCullDirection(CullDirection const direction)
        {
            m_CullDirection = direction;
        }

        CullDirection RenderState::getCullDirection() const
        {
            return m_CullDirection;
        }

        void RenderState::setPrimitiveStyle(PrimitiveStyle const style)
        {
            m_PrimitiveStyle = style;
        }

        PrimitiveStyle RenderState::getPrimitiveStyle() const
        {
            return m_PrimitiveStyle;
        }

        void RenderState::setDepthTesting(bool const testing)
        {
            m_EnableDepthTesting = testing;
        }

        bool RenderState::getDepthTesting() const
        {
            return m_EnableDepthTesting;
        }

        void RenderState::setScissorTesting(bool const testing)
        {
            m_EnableScissorTesting = testing;
        }

        bool RenderState::getScissorTesting() const
        {
            return m_EnableScissorTesting;
        }

        void RenderState::setRenderTextureMultisampling(bool const multisampling)
        {
            m_EnableMultisampling = multisampling;
        }

        bool RenderState::getRenderTextureMultisampling() const
        {
            return m_EnableMultisampling;
        }

        void RenderState::setLineAntialising(bool const antialiasing)
        {
            m_EnableLineAntialiasing = antialiasing;
        }

        bool RenderState::getLineAntialising() const
        {
            return m_EnableLineAntialiasing;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}