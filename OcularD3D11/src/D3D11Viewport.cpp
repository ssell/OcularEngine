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
#include "D3D11Viewport.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11Viewport::D3D11Viewport(ID3D11DeviceContext* context, float const x, float const y, float const width, float const height, float const minDepth, float const maxDepth)
            : Viewport(x, y, width, height, minDepth, maxDepth),
              m_D3DDeviceContext(context)
        {
            m_D3DViewport.TopLeftX = x;
            m_D3DViewport.TopLeftY = y;
            m_D3DViewport.Width    = width;
            m_D3DViewport.Height   = height;
            m_D3DViewport.MinDepth = minDepth;
            m_D3DViewport.MaxDepth = maxDepth;

            if((x < static_cast<float>(D3D11_VIEWPORT_BOUNDS_MIN)) || (x > static_cast<float>(D3D11_VIEWPORT_BOUNDS_MAX)))
            {
                OcularLogger->warning("Viewport X Origin of ", x, " lies outside of D3D11 bounds of [", D3D11_VIEWPORT_BOUNDS_MIN, ", ", D3D11_VIEWPORT_BOUNDS_MAX, "]; Clamping value", OCULAR_INTERNAL_LOG("D3D11Viewport", "D3D11Viewport"));
                m_D3DViewport.TopLeftX = Math::Clamp<float>(x, static_cast<float>(D3D11_VIEWPORT_BOUNDS_MIN), static_cast<float>(D3D11_VIEWPORT_BOUNDS_MAX));
            }
            
            if((y < static_cast<float>(D3D11_VIEWPORT_BOUNDS_MIN)) || (y > static_cast<float>(D3D11_VIEWPORT_BOUNDS_MAX)))
            {
                OcularLogger->warning("Viewport Y Origin of ", y, " lies outside of D3D11 bounds of [", D3D11_VIEWPORT_BOUNDS_MIN, ", ", D3D11_VIEWPORT_BOUNDS_MAX, "]; Clamping value", OCULAR_INTERNAL_LOG("D3D11Viewport", "D3D11Viewport"));
                m_D3DViewport.TopLeftY = Math::Clamp<float>(y, static_cast<float>(D3D11_VIEWPORT_BOUNDS_MIN), static_cast<float>(D3D11_VIEWPORT_BOUNDS_MAX));
            }

            if(width < 0.0f)
            {
                OcularLogger->warning("Viewport Width of ", width, " is invalid; May not be negative", OCULAR_INTERNAL_LOG("D3D11Viewport", "D3D11Viewport"));
                m_D3DViewport.Width = 0.0f;
            }

            if(height < 0.0f)
            {
                OcularLogger->warning("Viewport Height of ", height, " is invalid; May not be negative", OCULAR_INTERNAL_LOG("D3D11Viewport", "D3D11Viewport"));
                m_D3DViewport.Height = 0.0f;
            }

            if((minDepth < 0.0f) || (minDepth > 1.0f))
            {
                OcularLogger->warning("Viewport Minimum Depth of ", maxDepth, " is outside of D3D11 bounds of [0.0, 1.0]; Clamping value", OCULAR_INTERNAL_LOG("D3D11Viewport", "D3D11Viewport"));
                m_D3DViewport.MinDepth = Math::Clamp<float>(minDepth);
            }

            if((maxDepth < 0.0f) || (maxDepth > 1.0f))
            {
                OcularLogger->warning("Viewport Maximum Depth of ", minDepth, " is outside of D3D11 bounds of [0.0, 1.0]; Clamping value", OCULAR_INTERNAL_LOG("D3D11Viewport", "D3D11Viewport"));
                m_D3DViewport.MaxDepth = Math::Clamp<float>(maxDepth);
            }
        }

        D3D11Viewport::~D3D11Viewport()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11Viewport::bind()
        {
            Viewport::bind();

            if(m_D3DDeviceContext)
            {
                m_D3DDeviceContext->RSSetViewports(1, &m_D3DViewport);
            }
            else
            {
                OcularLogger->warning("Failed to bind D3D11Viewport due to NULL Device Context", OCULAR_INTERNAL_LOG("D3D11Viewport", "bind"));
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