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
#include "GraphicsDriverDX11.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        GraphicsDriverDX11::GraphicsDriverDX11()
        {
            m_Device = nullptr;
            m_DeviceContext = nullptr;
            m_SwapChain = nullptr;
        }

        GraphicsDriverDX11::~GraphicsDriverDX11()
        {
            if(m_Device)
            {
                m_Device->Release();
                m_Device = nullptr;
            }

            if(m_DeviceContext)
            {
                m_DeviceContext->Release();
                m_DeviceContext = nullptr;
            }

            if(m_SwapChain)
            {
                m_SwapChain->Release();
                m_SwapChain = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool GraphicsDriverDX11::initialize()
        {
            bool result = false;

            if(m_Device == nullptr)
            {
                //--------------------------------------------------------
            }

            return result;
        }

        ID3D11Device* GraphicsDriverDX11::getDevice() const
        {
            return m_Device;
        }

        ID3D11DeviceContext* GraphicsDriverDX11::getDeviceContext() const
        {
            return m_DeviceContext;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}