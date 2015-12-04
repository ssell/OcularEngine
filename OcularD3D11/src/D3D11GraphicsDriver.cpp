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
#include "Math/Color.hpp"

#include "Texture/D3D11Texture2D.hpp"
#include "Texture/D3D11RenderTexture.hpp"
#include "Texture/D3D11DepthTexture.hpp"

#include "Shader/D3D11VertexShader.hpp"
#include "Shader/D3D11GeometryShader.hpp"
#include "Shader/D3D11FragmentShader.hpp"
#include "Shader/D3D11PreTessellationShader.hpp"
#include "Shader/D3D11PostTessellationShader.hpp"
#include "Shader/Uniform/D3D11UniformBuffer.hpp"

#include "RenderState/D3D11RenderState.hpp"

#include "Material/D3D11Material.hpp"

#include "Mesh/D3D11IndexBuffer.hpp"
#include "Mesh/D3D11VertexBuffer.hpp"

#include "D3D11Viewport.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11GraphicsDriver::D3D11GraphicsDriver()
            : m_D3DDevice(nullptr),
              m_D3DDeviceContext(nullptr),
              m_D3DSwapChain(nullptr)
        {

        }

        D3D11GraphicsDriver::~D3D11GraphicsDriver()
        {
            if(D3D11VertexShader::m_D3DInputLayout)
            {
                // Shared object between all Vertex shaders
                D3D11VertexShader::m_D3DInputLayout->Release();
                D3D11VertexShader::m_D3DInputLayout = nullptr;
            }

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
                        //------------------------------------------------
                        // Create RenderTargetView and DepthStencilView

                        const Core::WindowDescriptor windowDescr = windowWin32->getDescriptor();

                        TextureDescriptor rtvDescriptor;
                        rtvDescriptor.width = windowDescr.width;
                        rtvDescriptor.height = windowDescr.height;
                        rtvDescriptor.mipmaps = 1;
                        rtvDescriptor.type = TextureType::RenderTexture2D;
                        rtvDescriptor.format = TextureFormat::R32G32B32A32Float;
                        rtvDescriptor.cpuAccess = TextureAccess::ReadWrite;
                        rtvDescriptor.gpuAccess = TextureAccess::ReadWrite;
                        rtvDescriptor.filter = TextureFilterMode::Point;

                        TextureDescriptor dsvDescriptor;
                        dsvDescriptor.width = windowDescr.width;
                        dsvDescriptor.height = windowDescr.height;
                        dsvDescriptor.mipmaps = 1;
                        dsvDescriptor.type = TextureType::DepthTexture2D;
                        dsvDescriptor.format = TextureFormat::Depth;
                        dsvDescriptor.cpuAccess = TextureAccess::ReadWrite;
                        dsvDescriptor.gpuAccess = TextureAccess::ReadWrite;
                        dsvDescriptor.filter = TextureFilterMode::Point;


                        D3D11RenderTexture* renderTexture = new D3D11RenderTexture(rtvDescriptor, m_D3DDevice, m_D3DSwapChain);
                        D3D11DepthTexture* depthTexture = new D3D11DepthTexture(dsvDescriptor, m_D3DDevice);

                        renderTexture->apply();
                        depthTexture->apply();

                        windowWin32->setRenderTexture(renderTexture);
                        windowWin32->setDepthTexture(depthTexture);

                        //------------------------------------------------
                        // Create and bind render textures

                        ID3D11RenderTargetView* rtv = renderTexture->getD3DRenderTargetView();
                        ID3D11DepthStencilView* dsv = depthTexture->getD3DDepthStencilView();

                        m_D3DDeviceContext->OMSetRenderTargets(1, &rtv, dsv);

                        //------------------------------------------------
                        // Create and bind RenderState

                        m_RenderState = new D3D11RenderState(m_D3DDevice, m_D3DDeviceContext);
                        m_RenderState->bind();

                        result = true;
                    }
                    else
                    {
                        OcularLogger->fatal("Failed to create Device and Swap Chain", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "initialize"));
                    }
                }
                else
                {
                    OcularLogger->fatal("Failed to initialize Graphics Driver: Invalid Window", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "initialize"));
                }
            }
            else
            {
                OcularLogger->warning("Graphics Driver already initialized", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "initialize"));
            }

            return result;
        }

        void D3D11GraphicsDriver::clearBuffers()
        {
            GraphicsDriver::clearBuffers();

            if(m_D3DDeviceContext)
            {
                auto mainWindow = OcularWindows->getMainWindow();

                if(mainWindow)
                {
                    ID3D11RenderTargetView* currentRTV = nullptr;
                    ID3D11DepthStencilView* currentDSV = nullptr;

                    m_D3DDeviceContext->OMGetRenderTargets(1, &currentRTV, &currentDSV);

                    if(currentRTV && currentDSV)
                    {
                        const static float clearColor[4] = { Core::Color::FrigidBlue().r, Core::Color::FrigidBlue().g, Core::Color::FrigidBlue().b, Core::Color::FrigidBlue().a };

                        m_D3DDeviceContext->ClearRenderTargetView(currentRTV, clearColor);
                        m_D3DDeviceContext->ClearDepthStencilView(currentDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
                    }
                }
            }
        }

        void D3D11GraphicsDriver::swapBuffers()
        {
            GraphicsDriver::swapBuffers();

            if(m_D3DSwapChain)
            {
                const HRESULT hResult = m_D3DSwapChain->Present(0, 0);

                if(hResult != S_OK)
                {
                    OcularLogger->error("Failed to swap buffers with error ", hResult, OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "swapBuffers"));
                }
            }
        }

        bool D3D11GraphicsDriver::renderMesh(Mesh* mesh)
        {
            bool result = false;

            if(mesh)
            {
                if(mesh->bind())
                {
                    ID3D11VertexShader* currVS = nullptr;
                    ID3D11PixelShader* currPS = nullptr;
                    ID3D11Buffer* currVB = nullptr;
                    ID3D11Buffer* currIB = nullptr;

                    m_D3DDeviceContext->VSGetShader(&currVS, nullptr, nullptr);
                    m_D3DDeviceContext->PSGetShader(&currPS, nullptr, nullptr);
                    m_D3DDeviceContext->IAGetVertexBuffers(0, 1, &currVB, nullptr, nullptr);
                    m_D3DDeviceContext->IAGetIndexBuffer(&currIB, nullptr, nullptr);

                    m_D3DDeviceContext->DrawIndexed(mesh->getIndexBuffer()->getNumIndices(), 0, 0);
                    result = true;
                }
            }

            return result;
        }

        void D3D11GraphicsDriver::setRenderTexture(RenderTexture* texture)
        {
            GraphicsDriver::setRenderTexture(texture);

            if(texture)
            {
                D3D11RenderTexture* d3dTexture = dynamic_cast<D3D11RenderTexture*>(texture);

                if(d3dTexture)
                {
                    ID3D11RenderTargetView* rtv = d3dTexture->getD3DRenderTargetView();

                    ID3D11RenderTargetView* currRTV = nullptr;
                    ID3D11DepthStencilView* currDSV = nullptr;

                    if(m_D3DDeviceContext)
                    {
                        m_D3DDeviceContext->OMGetRenderTargets(1, &currRTV, &currDSV);

                        if(currRTV != rtv)
                        {
                            m_D3DDeviceContext->OMSetRenderTargets(1, &rtv, currDSV);
                        }
                    }
                }
            }
        }

        void D3D11GraphicsDriver::setDepthTexture(DepthTexture* texture)
        {
            GraphicsDriver::setDepthTexture(texture);

            if(texture)
            {
                D3D11DepthTexture* d3dTexture = dynamic_cast<D3D11DepthTexture*>(texture);

                if(d3dTexture)
                {
                    ID3D11DepthStencilView* dsv = d3dTexture->getD3DDepthStencilView();

                    ID3D11RenderTargetView* currRTV = nullptr;
                    ID3D11DepthStencilView* currDSV = nullptr;

                    if(m_D3DDeviceContext)
                    {
                        m_D3DDeviceContext->OMGetRenderTargets(1, &currRTV, &currDSV);

                        if(currDSV != dsv)
                        {
                            m_D3DDeviceContext->OMSetRenderTargets(1, &currRTV, dsv);
                        }
                    }
                }
            }
        }

        Material* D3D11GraphicsDriver::createMaterial() const
        {
            return new D3D11Material(m_D3DDeviceContext);
        }

        Viewport* D3D11GraphicsDriver::createViewport(float const x, float const y, float const width, float const height, float const minDepth, float const maxDepth) const
        {
            return new D3D11Viewport(m_D3DDeviceContext, x, y, width, height, minDepth, maxDepth);
        }

        //----------------------------------------------------------------------------------
        // Textures
        //----------------------------------------------------------------------------------

        Texture* D3D11GraphicsDriver::createTexture(TextureDescriptor const& descriptor) const
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

            case TextureType::DepthTexture2D:
                result = createDepthTexture(descriptor);
                break;

            default:
                OcularLogger->error("Unsupported texture type for D3D11", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "createTexture"));
                break;
            }

            return result;
        }

        Texture2D* D3D11GraphicsDriver::createTexture2D(TextureDescriptor const& descriptor) const
        {
            Texture2D* result = nullptr;

            if(descriptor.type == TextureType::Texture2D)
            {
                result = new D3D11Texture2D(descriptor, m_D3DDevice);
            }
            else
            {
                OcularLogger->error("Invalid texture type specified", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "createTexture2D"));
            }

            return result;
        }

        RenderTexture* D3D11GraphicsDriver::createRenderTexture(TextureDescriptor const& descriptor) const
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

        DepthTexture* D3D11GraphicsDriver::createDepthTexture(TextureDescriptor const& descriptor) const
        {
            DepthTexture* result = nullptr;

            if(descriptor.type == TextureType::RenderTexture2D)
            {
                result = new D3D11DepthTexture(descriptor, m_D3DDevice);
            }
            else
            {
                OcularLogger->error("Invalid texture type specified", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "createRenderTexture"));
            }

            return result;
        }

        uint32_t D3D11GraphicsDriver::getMaxBoundTextures() const
        {
            return D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
        }

        //----------------------------------------------------------------------------------
        // Shaders
        //----------------------------------------------------------------------------------

        VertexShader* D3D11GraphicsDriver::createVertexShader() const
        {
            return new D3D11VertexShader(m_D3DDevice, m_D3DDeviceContext);
        }

        GeometryShader* D3D11GraphicsDriver::createGeometryShader() const
        {
            return new D3D11GeometryShader(m_D3DDeviceContext);
        }

        FragmentShader* D3D11GraphicsDriver::createFragmentShader() const
        {
            return new D3D11FragmentShader(m_D3DDeviceContext);
        }

        PreTessellationShader* D3D11GraphicsDriver::createPreTessellationShader() const
        {
            return new D3D11PreTessellationShader(m_D3DDeviceContext);
        }

        PostTessellationShader* D3D11GraphicsDriver::createPostTessellationShader() const
        {
            return new D3D11PostTessellationShader(m_D3DDeviceContext);
        }

        UniformBuffer* D3D11GraphicsDriver::createUniformBuffer(UniformBufferType const type) const
        {
            return new D3D11UniformBuffer(type, m_D3DDevice, m_D3DDeviceContext);
        }

        //----------------------------------------------------------------------------------
        // Meshes
        //----------------------------------------------------------------------------------

        IndexBuffer* D3D11GraphicsDriver::createIndexBuffer() const
        {
            return new D3D11IndexBuffer(m_D3DDevice, m_D3DDeviceContext);
        }

        VertexBuffer* D3D11GraphicsDriver::createVertexBuffer() const
        {
            return new D3D11VertexBuffer(m_D3DDevice, m_D3DDeviceContext);
        }

        //----------------------------------------------------------------------------------
        // D3D Specific
        //----------------------------------------------------------------------------------

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
                dest.MipLevels = src.mipmaps;
                dest.ArraySize = 1;
                dest.SampleDesc.Count = 1;
                dest.SampleDesc.Quality = 0;

                //--------------------------------------------------------
                // CPU Access

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

                //--------------------------------------------------------
                // GPU Access

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

                //--------------------------------------------------------
                // Texture Type

                switch(src.type)
                {
                case TextureType::RenderTexture2D:
                    dest.BindFlags = D3D11_BIND_RENDER_TARGET;
                    break;

                case TextureType::DepthTexture2D:
                    dest.BindFlags = D3D11_BIND_DEPTH_STENCIL;
                    dest.CPUAccessFlags = 0;
                    break;

                default:
                    dest.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                    break;
                }

                //--------------------------------------------------------
                // Texture Format 

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

                case TextureFormat::Depth:
                    dest.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
                    break;

                default:
                    OcularLogger->warning("Unsupported texture format for D3D11. Defaulting to R32G32B32A32Float", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "convertTextureDescriptor"));
                    dest.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                    break;
                }
            }

            return result;
        }

        bool D3D11GraphicsDriver::convertTextureDescriptor(D3D11_TEXTURE2D_DESC const& source, TextureDescriptor& dest)
        {
            bool result = true;

            //------------------------------------------------------------
            // Dimensions

            dest.width = source.Width;
            dest.height = source.Height;
            dest.mipmaps = source.MipLevels;

            //------------------------------------------------------------
            // CPU Access

            if((source.CPUAccessFlags & D3D11_CPU_ACCESS_READ) && (source.CPUAccessFlags & D3D11_CPU_ACCESS_WRITE))
            {
                dest.cpuAccess = TextureAccess::ReadWrite;
            }
            else if(source.CPUAccessFlags & D3D11_CPU_ACCESS_READ)
            {
                dest.cpuAccess = TextureAccess::ReadOnly;
            }
            else if(source.CPUAccessFlags & D3D11_CPU_ACCESS_WRITE)
            {
                dest.cpuAccess = TextureAccess::WriteOnly;
            }
            else
            {
                dest.cpuAccess = TextureAccess::None;
            }

            //------------------------------------------------------------
            // GPU Access

            if(source.Usage == D3D11_USAGE_DEFAULT)
            {
                dest.gpuAccess = TextureAccess::ReadWrite;
            }
            else if((source.Usage == D3D11_USAGE_IMMUTABLE) || (source.Usage == D3D11_USAGE_DYNAMIC))
            {
                dest.gpuAccess = TextureAccess::ReadOnly;
            }
            else
            {
                OcularLogger->warning("Unsupported D3D11 Texture2D usage flag ", source.Usage, "; Defaulting to full GPU access", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "convertTextureDescriptor"));
                dest.gpuAccess = TextureAccess::ReadWrite;
                result = false;
            }

            //------------------------------------------------------------
            // Texture Type

            switch(source.BindFlags)
            {
            case 0:
                dest.type = TextureType::Texture2D;
                break;

            case D3D11_BIND_RENDER_TARGET:
                dest.type = TextureType::RenderTexture2D;
                break;

            case D3D11_BIND_DEPTH_STENCIL:
                dest.type = TextureType::DepthTexture2D;
                break;

            default:
                OcularLogger->warning("Unsupported D3D11 Texture2D bind flag ", source.BindFlags, "; Defaulting to Texture2D", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "convertTextureDescriptor"));
                dest.type = TextureType::Texture2D;
                result = false;
                break;
            }

            //------------------------------------------------------------
            // Texture Format

            switch(source.Format)
            {
            case DXGI_FORMAT_R32G32B32A32_FLOAT:
                dest.format = TextureFormat::R32G32B32A32Float;
                break;

            case DXGI_FORMAT_R32G32B32A32_UINT:
                dest.format = TextureFormat::R32G32B32A32Unsigned;
                break;

            case DXGI_FORMAT_R32G32B32A32_SINT:
                dest.format = TextureFormat::R32G32B32A32Signed;
                break;

            case DXGI_FORMAT_R32G32B32_FLOAT:
                dest.format = TextureFormat::R32G32B32Float;
                break;

            case DXGI_FORMAT_R32G32B32_UINT:
                dest.format = TextureFormat::R32G32B32Unsigned;
                break;

            case DXGI_FORMAT_R32G32B32_SINT:
                dest.format = TextureFormat::R32G32B32Signed;
                break;

            case DXGI_FORMAT_R32G32_FLOAT:
                dest.format = TextureFormat::R32G32Float;
                break;

            case DXGI_FORMAT_R32G32_UINT:
                dest.format = TextureFormat::R32G32Unsigned;
                break;

            case DXGI_FORMAT_R32G32_SINT:
                dest.format = TextureFormat::R32G32Signed;
                break;

            case DXGI_FORMAT_R32_FLOAT:
                dest.format = TextureFormat::R32Float;
                break;

            case DXGI_FORMAT_R32_UINT:
                dest.format = TextureFormat::R32Unsigned;
                break;

            case DXGI_FORMAT_R32_SINT:
                dest.format = TextureFormat::R32Signed;
                break;

            case DXGI_FORMAT_R8G8B8A8_UINT:
                dest.format = TextureFormat::R8G8B8A8Unsigned;
                break;

            case DXGI_FORMAT_R8G8B8A8_SINT:
                dest.format = TextureFormat::R8G8B8A8Signed;
                break;

            case DXGI_FORMAT_R8G8_UINT:
                dest.format = TextureFormat::R8G8Unsigned;
                break;

            case DXGI_FORMAT_R8G8_SINT:
                dest.format = TextureFormat::R8G8Signed;
                break;

            case DXGI_FORMAT_R8_UINT:
                dest.format = TextureFormat::R8Unsigned;
                break;

            case DXGI_FORMAT_R8_SINT:
                dest.format = TextureFormat::R8Signed;
                break;

            case DXGI_FORMAT_D24_UNORM_S8_UINT:
                dest.format = TextureFormat::Depth;
                break;

            default:
                OcularLogger->warning("Unsupported D3D11 Texture2D format ", source.Format, "; Defaulting to R32G32B32A32Float", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "convertTextureDescriptor"));
                dest.format = TextureFormat::R32G32B32A32Float;
                result = false;
                break;
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
            bool result = true;

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
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1,
                D3D_FEATURE_LEVEL_10_0,
                D3D_FEATURE_LEVEL_9_3,
                D3D_FEATURE_LEVEL_9_1
            };

            D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

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
                    ARRAYSIZE(featureLevels),
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

            if((windowDesc.displayMode == Core::WindowDisplayMode::WindowedBordered) ||
               (windowDesc.displayMode == Core::WindowDisplayMode::WindowedBorderless))
            {
                result.Windowed = TRUE;
            }

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

            switch(descriptor.type)
            {
            case TextureType::Texture2D:         // Explicitly falls down
            case TextureType::RenderTexture2D:   // Explicitly falls down
            case TextureType::DepthTexture2D:
                break;

            default:
                OcularLogger->error("Unsupported Texture Type for D3D11", OCULAR_INTERNAL_LOG("D3D11GraphicsDriver", "validateTextureDescriptor"));
                result = false;
                break;
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