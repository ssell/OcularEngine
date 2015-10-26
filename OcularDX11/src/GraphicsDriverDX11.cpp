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
                std::shared_ptr<Core::AWindow> mainWindow = OcularWindows->getMainWindow();

                if(validateWindow(mainWindow, hwnd))
                {
                    Core::WindowWin32* windowWin32 = dynamic_cast<Core::WindowWin32*>(mainWindow.get());

                    if(createDeviceAndSwapChain(windowWin32, hwnd))
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

        bool GraphicsDriverDX11::createDeviceAndSwapChain(Core::WindowWin32 const* window, HWND const hwnd)
        {
            bool result = false;

            //------------------------------------------------------------
            // Set up for device creation

            uint32_t createDeviceFlags = 0;

#ifdef _DEBUG
            createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

            const D3D_DRIVER_TYPE driverTypes[] =
            {
                D3D_DRIVER_TYPE_HARDWARE,
                D3D_DRIVER_TYPE_WARP,
                D3D_DRIVER_TYPE_REFERENCE
            };

            const D3D_FEATURE_LEVEL featureLevels[] =
            {
                D3D_FEATURE_LEVEL_11_1,
                D3D_FEATURE_LEVEL_11_0
            };

            D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;

            //------------------------------------------------------------
            // Create the Swap Chain descriptor

            const DXGI_SWAP_CHAIN_DESC swapChainDesc = createSwapChainDescription(window);

            //------------------------------------------------------------
            // Create the devices and swap chain

            const HRESULT hResult = D3D11CreateDeviceAndSwapChain(
                    nullptr,
                    D3D_DRIVER_TYPE_HARDWARE,
                    nullptr,
                    createDeviceFlags,
                    featureLevels,
                    2,
                    D3D11_SDK_VERSION,
                    &swapChainDesc,
                    &m_SwapChain,
                    &m_Device,
                    &featureLevel,
                    &m_DeviceContext
                );

            //------------------------------------------------------------
            // Handle multiple swap chains here?

            //------------------------------------------------------------
            // Error handling

            if(hResult != S_OK)
            {
                OcularLogger->error("Failed to create D3D 11.1 Device and SwapChain with error: ", hResult, OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "createDeviceAndSwapChain"));
                result = false;
            }

            return result;
        }

        DXGI_SWAP_CHAIN_DESC GraphicsDriverDX11::createSwapChainDescription(Core::WindowWin32 const* window) const
        {
            Core::WindowDescriptor windowDesc = window->getDescriptor();

            DXGI_SWAP_CHAIN_DESC result;
            ZeroMemory(&result, sizeof(result));

            result.BufferCount                        = 1;
            result.BufferDesc.Width                   = windowDesc.width;
            result.BufferDesc.Height                  = windowDesc.height;
            result.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
            result.BufferDesc.RefreshRate.Numerator   = 60;
            result.BufferDesc.RefreshRate.Denominator = 1;
            result.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            result.OutputWindow                       = window->getHWND();
            result.SampleDesc.Count                   = 1;
            result.SampleDesc.Quality                 = 0;
            result.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            result.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
            result.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
            result.Flags                              = 0;
            result.Windowed                           = ((windowDesc.displayMode == Core::WindowDisplayMode::WindowedBordered) ||
                                                         (windowDesc.displayMode == Core::WindowDisplayMode::WindowedBorderless));

            return result;
        }


        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}