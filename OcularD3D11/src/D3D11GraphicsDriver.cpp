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
#include "D3D11GraphicsDriver.hpp"
#include "Renderer/Window/WindowWin32.hpp"
#include "Texture/D3D11RenderTexture.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11GraphicsDriver::D3D11GraphicsDriver()
        {
            m_D3DDevice = nullptr;
            m_D3DDeviceContext = nullptr;
            m_D3DSwapChain = nullptr;
        }

        D3D11GraphicsDriver::~D3D11GraphicsDriver()
        {
            if(m_D3DDevice)
            {
                m_D3DDevice->Release();
                m_D3DDevice = nullptr;
            }

            if(m_D3DDeviceContext)
            {
                m_D3DDeviceContext->Release();
                m_D3DDeviceContext = nullptr;
            }

            if(m_D3DSwapChain)
            {
                m_D3DSwapChain->Release();
                m_D3DSwapChain = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool D3D11GraphicsDriver::initialize()
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

            if(m_D3DDevice == nullptr)
            {
                std::shared_ptr<Core::AWindow> mainWindow = OcularWindows->getMainWindow();

                if(validateWindow(mainWindow, hwnd))
                {
                    Core::WindowWin32* windowWin32 = dynamic_cast<Core::WindowWin32*>(mainWindow.get());

                    if(createDeviceAndSwapChain(windowWin32, hwnd))
                    {
                        const Core::WindowDescriptor windowDescr = windowWin32->getDescriptor();

                        TextureDescriptor rtDescr;
                        rtDescr.width     = windowDescr.width;
                        rtDescr.height    = windowDescr.height;
                        rtDescr.type      = TextureType::RenderTexture2D;
                        rtDescr.cpuAccess = TextureAccess::None;
                        rtDescr.gpuAccess = TextureAccess::ReadWrite;
                        rtDescr.filter    = TextureFilterMode::Point;

                        D3D11RenderTexture* renderTexture = dynamic_cast<D3D11RenderTexture*>(createRenderTexture(rtDescr));

                        if(renderTexture)
                        {
                            windowWin32->setRenderTexture(renderTexture);
                            result = true;
                        }
                        else
                        {
                            OcularLogger->fatal("Failed to create Backbuffer RTV", OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "initialize"));
                        }
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

        Texture* D3D11GraphicsDriver::createTexture(TextureDescriptor const& descriptor)
        {
            Texture* result = nullptr;

            switch(descriptor.type) 
            {
            case TextureType::Texture2D:
                result = createTexture2D(descriptor);
                break;

            case TextureType::RenderTexture2D:
                result = createRenderTexture(descriptor);
                break;

            default:
                OcularLogger->error("Unsupported texture type for D3D11", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "createTexture"));
                break;
            }

            return result;
        }

        Texture2D* D3D11GraphicsDriver::createTexture2D(TextureDescriptor const& descriptor)
        {
            Texture2D* result = nullptr;

            if(descriptor.type == TextureType::Texture2D)
            {
            
            }
            else
            {
                OcularLogger->error("Invalid texture type specified", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "createTexture2D"));
            }

            return result;
        }

        RenderTexture* D3D11GraphicsDriver::createRenderTexture(TextureDescriptor const& descriptor)
        {
            RenderTexture* result = nullptr;

            if(descriptor.type == TextureType::RenderTexture2D)
            {
                result = new D3D11RenderTexture(descriptor, m_D3DDevice);
                
            }
            else
            {
                OcularLogger->error("Invalid texture type specified", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "createRenderTexture"));
            }

            return result;
        }

        ID3D11Device* D3D11GraphicsDriver::getD3DDevice() const
        {
            return m_D3DDevice;
        }

        ID3D11DeviceContext* D3D11GraphicsDriver::getD3DDeviceContext() const
        {
            return m_D3DDeviceContext;
        }

        bool D3D11GraphicsDriver::convertTextureDescriptor(TextureDescriptor const& src, D3D11_TEXTURE2D_DESC &dest)
        {
            bool result = true;

            if(validateTextureDescriptor(src))
            {
                ZeroMemory(&dest, sizeof(D3D11_TEXTURE2D_DESC));

                dest.Width = src.width;
                dest.Height = src.height;
                
                switch(src.cpuAccess)
                {
                case TextureAccess::ReadOnly:
                    dest.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                    break;

                case TextureAccess::WriteOnly:
                    dest.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                    break;

                case TextureAccess::ReadWrite:
                    dest.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
                    break;

                default:
                    break;
                }

                if((src.cpuAccess == TextureAccess::WriteOnly) && (src.gpuAccess == TextureAccess::ReadOnly))
                {
                    dest.Usage = D3D11_USAGE_DYNAMIC;
                }
                else  if(src.gpuAccess == TextureAccess::ReadOnly)
                {
                    dest.Usage = D3D11_USAGE_IMMUTABLE;
                }
                else
                {
                    dest.Usage = D3D11_USAGE_DEFAULT;
                }

                switch(src.format)
                {
                case TextureFormat::R32G32B32A32Float:
                    dest.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    break;

                case TextureFormat::R32G32B32A32Unsigned:
                    dest.Format = DXGI_FORMAT_R32G32B32A32_UINT;
                    break;

                case TextureFormat::R32G32B32A32Signed:
                    dest.Format = DXGI_FORMAT_R32G32B32A32_SINT;
                    break;

                case TextureFormat::R32G32B32Float:
                    dest.Format = DXGI_FORMAT_R32G32B32_FLOAT;
                    break;

                case TextureFormat::R32G32B32Unsigned:
                    dest.Format = DXGI_FORMAT_R32G32B32_UINT;
                    break;

                case TextureFormat::R32G32B32Signed:
                    dest.Format = DXGI_FORMAT_R32G32B32_SINT;
                    break;

                case TextureFormat::R32G32Float:
                    dest.Format = DXGI_FORMAT_R32G32_FLOAT;
                    break;

                case TextureFormat::R32G32Unsigned:
                    dest.Format = DXGI_FORMAT_R32G32_UINT;
                    break;

                case TextureFormat::R32G32Signed:
                    dest.Format = DXGI_FORMAT_R32G32_SINT;
                    break;

                case TextureFormat::R32Float:
                    dest.Format = DXGI_FORMAT_R32_FLOAT;
                    break;

                case TextureFormat::R32Unsigned:
                    dest.Format = DXGI_FORMAT_R32_UINT;
                    break;

                case TextureFormat::R32Signed:
                    dest.Format = DXGI_FORMAT_R32_SINT;
                    break;

                case TextureFormat::R8G8B8A8Unsigned:
                    dest.Format = DXGI_FORMAT_R8G8B8A8_UINT;
                    break;

                case TextureFormat::R8G8B8A8Signed:
                    dest.Format = DXGI_FORMAT_R8G8B8A8_SINT;
                    break;

                case TextureFormat::R8G8Unsigned:
                    dest.Format = DXGI_FORMAT_R8G8_UINT;
                    break;

                case TextureFormat::R8G8Signed:
                    dest.Format = DXGI_FORMAT_R8G8_SINT;
                    break;

                case TextureFormat::R8Unsigned:
                    dest.Format = DXGI_FORMAT_R8_UINT;
                    break;

                case TextureFormat::R8Signed:
                    dest.Format = DXGI_FORMAT_R8_SINT;
                    break;

                default:
                    OcularLogger->warning("Unsupported texture format for D3D11. Defaulting to R32G32B32A32Float", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "convertTextureDescriptor"));
                    dest.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    break;
                }

                switch(src.type)
                {
                case TextureType::RenderTexture2D:
                    dest.BindFlags = D3D11_BIND_RENDER_TARGET;
                    break;

                default:
                    dest.BindFlags = 0;
                    break;
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11GraphicsDriver::validateWindow(std::shared_ptr<Core::AWindow> window, HWND& hwnd) const
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

        bool D3D11GraphicsDriver::createDeviceAndSwapChain(Core::WindowWin32 const* window, HWND const hwnd)
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
                    &m_D3DSwapChain,
                    &m_D3DDevice,
                    &featureLevel,
                    &m_D3DDeviceContext
                );

            //------------------------------------------------------------
            // Handle multiple swap chains here?

            //------------------------------------------------------------
            // Error handling

            if(hResult != S_OK)
            {
                OcularLogger->error("Failed to create D3D 11.1 Device and SwapChain with error ", hResult, OCULAR_INTERNAL_LOG("GraphicsDriverDX11", "createDeviceAndSwapChain"));
                result = false;
            }

            return result;
        }

        DXGI_SWAP_CHAIN_DESC D3D11GraphicsDriver::createSwapChainDescription(Core::WindowWin32 const* window) const
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

        bool D3D11GraphicsDriver::validateTextureDescriptor(TextureDescriptor const& descriptor)
        {
            bool result = true;
            
            //------------------------------------------------------------
            // Dimensions 

            if(descriptor.width == 0)
            {
                OcularLogger->error("Texture width must be greater than 0", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
            }
            else if(descriptor.width > OCULAR_MAX_TEXTURE_WIDTH)
            {
                OcularLogger->error("Texture width may not exceed ", OCULAR_MAX_TEXTURE_WIDTH, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
            }

            if(descriptor.height == 0)
            {
                OcularLogger->error("Texture height must be greater than 0", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
            }
            else if(descriptor.height > OCULAR_MAX_TEXTURE_HEIGHT)
            {
                OcularLogger->error("Texture height may not exceed ", OCULAR_MAX_TEXTURE_HEIGHT, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
            }

            //------------------------------------------------------------
            // CPU Access

            /**
             * For the following restrictions, see the D3D11_USAGE flag values at:
             * https://msdn.microsoft.com/en-us/library/windows/desktop/ff476259(v=vs.85).aspx
             *
             * Note: currently do not support STAGING
             *
             * Usage Flags | CPU Read | CPU Write | GPU Read | GPU Write
             * ------------|----------|-----------|----------|------------
             *     DEFAULT |     Y    |     Y     |     Y    |     Y
             *   IMMUTABLE |          |           |     Y    |
             *     DYNAMIC |          |     Y     |     Y    |
             */

            static const std::string genericAccessMessage = "Only the following access combinations are supported: CPU Read/Write + GPU Read/Write, GPU Read, CPU Write + GPU Read";
            
            switch(descriptor.cpuAccess)
            {
            case TextureAccess::ReadOnly:
                OcularLogger->error("D3D11 does not support textures with CPU read-only access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
                break;

            case TextureAccess::WriteOnly:
                if(descriptor.gpuAccess != TextureAccess::ReadOnly)
                {
                    OcularLogger->error("D3D11 does not support textures with CPU write-only access unless accompanied by GPU read-only access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                    result = false;
                }
                break;

            case TextureAccess::ReadWrite:
                if(descriptor.gpuAccess != TextureAccess::ReadWrite)
                {
                    OcularLogger->error("D3D11 does not support textures with CPU read-write access unless accompanied by GPU read-write access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                    result = false;
                }
                break;

            case TextureAccess::None:
                if(descriptor.gpuAccess != TextureAccess::ReadOnly)
                {
                    OcularLogger->error("D3D11 does not support textures with no CPU access unless accompanied by GPU read-only access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                    result = false;
                }
                break;

            default:
                OcularLogger->error("Unsupported CPU access level. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
                break;
            }

            //------------------------------------------------------------
            // GPU Access

            switch(descriptor.gpuAccess)
            {
            case TextureAccess::ReadOnly:
                if((descriptor.cpuAccess != TextureAccess::WriteOnly) && (descriptor.cpuAccess != TextureAccess::None))
                {
                    OcularLogger->error("D3D11 does not support textures with GPU read-only access unless accompanied by CPU write-only or CPU no access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                    result = false;
                }
                break;

            case TextureAccess::WriteOnly:
                OcularLogger->error("D3D11 does not support textures with GPU write-only access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
                break;

            case TextureAccess::ReadWrite:
                if(descriptor.cpuAccess != TextureAccess::ReadWrite) 
                {
                    OcularLogger->error("D3D11 does not support textures with GPU read-write access unless accompanied by CPU read-write access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                    result = false;
                }
                break;

            case TextureAccess::None:
                OcularLogger->error("D3D11 does not support textures with no GPU access. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
                break;

            default:
                OcularLogger->error("Unsupported GPU access level. ", genericAccessMessage, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
            }

            //------------------------------------------------------------
            // Type

            if((descriptor.type != TextureType::Texture2D) && (descriptor.type != TextureType::RenderTexture2D))
            {
                OcularLogger->error("Unsupported Texture Type for D3D11", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
            }

            //------------------------------------------------------------
            // Filter


            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}