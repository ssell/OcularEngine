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
#include "Renderer/Window/WindowWin32.hpp"

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
            /**
             * Initialization follows the steps below:
             * 
             *     1. Verify the window
             *     2. Create the device, device context, and swap chain
             *     3. Set the default render states
             */

            bool result = false;
            HWND hwnd = 0;

            if(m_Device == nullptr)
            {
                auto mainWindow = OcularWindows->getMainWindow();

                if(validateWindow(mainWindow, hwnd))
                {
                    if(createDeviceAndSwapChain(mainWindow, hwnd))
                    {
                        // Set default states
                        // ...

                        result = true;
                    }
                    else
                    {
                        OcularLogger->fatal("Failed to create Device and Swap Chain", OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "initialize"));   
                    }
                }
                else
                {
                    OcularLogger->fatal("Failed to initialize Graphics Driver: Invalid Window", OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "initialize"));
                }
            }
            else
            {
                OcularLogger->warning("Graphics Driver already initialized", OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "initialize"));
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

        bool GraphicsDriverDX11::validateWindow(std::shared_ptr<Core::AWindow> window, HWND& hwnd) const
        {
            bool result = false;

            if(window)
            {
                Core::WindowWin32* window32 = dynamic_cast<Core::WindowWin32*>(window.get());

                if(window32)
                {
                    hwnd = window32->getHWND();

                    if(IsWindow(hwnd))
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Invalid HWND", OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "validateWindow"));
                    }
                }
                else
                {
                    OcularLogger->error("Invalid window type for DirectX application", OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "validateWindow"));
                }
            }
            else
            {
                OcularLogger->error("Window is NULL", OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "validateWindow"));
            }

            return result;
        }

        bool GraphicsDriverDX11::createDeviceAndSwapChain(std::shared_ptr<Core::AWindow> window, HWND const hwnd)
        {
            bool result = false;

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}