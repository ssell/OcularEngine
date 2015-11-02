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
#include "Texture/D3D11RenderTexture.hpp"
#include "D3D11GraphicsDriver.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11RenderTexture::D3D11RenderTexture(TextureDescriptor const& descriptor, ID3D11Device* device)
            : RenderTexture(descriptor)
        {
            m_D3DDevice = device;
            m_D3DTexture = nullptr;
            m_D3DRenderTargetView = nullptr;
            m_D3DSwapChain = nullptr;
        }

        D3D11RenderTexture::D3D11RenderTexture(TextureDescriptor const& descriptor, ID3D11Device* device, IDXGISwapChain* swapchain)
            : RenderTexture(descriptor)
        {
            m_D3DDevice = device;
            m_D3DTexture = nullptr;
            m_D3DRenderTargetView = nullptr;
            m_D3DSwapChain = swapchain;
        }

        D3D11RenderTexture::~D3D11RenderTexture()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        ID3D11Texture2D* D3D11RenderTexture::getD3DTexture()
        {
            return m_D3DTexture;
        }

        ID3D11RenderTargetView* D3D11RenderTexture::getD3DRenderTargetView()
        {
            return m_D3DRenderTargetView;
        }

        void D3D11RenderTexture::unload()
        {
            RenderTexture::unload();

            if(m_D3DTexture)
            {
                m_D3DTexture->Release();
                m_D3DTexture = nullptr;
            }

            if(m_D3DRenderTargetView)
            {
                m_D3DRenderTargetView->Release();
                m_D3DRenderTargetView = nullptr;
            }
        }

        void D3D11RenderTexture::apply()
        {
            RenderTexture::apply();

            if((m_D3DRenderTargetView == nullptr) || (m_D3DTexture == nullptr))
            {
                // We are (re)creating the resources and not just applying changes...
                // Upon creation we can provide source texture data

                // Unload just incase for some reason one or the other is null and the other isn't (which should never ever happen)
                unload();

                if(!createD3DResources())
                {
                    OcularLogger->error("Failed to create D3D resources", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "apply"));
                    unload();
                }
            }
            else
            {
                // We are (attempting) to apply changes to the resources
                if((m_Descriptor.cpuAccess == TextureAccess::WriteOnly) || (m_Descriptor.cpuAccess == TextureAccess::ReadWrite))
                {
                    /// \todo Apply CPU changes to RTV
                }
                else
                {
                    OcularLogger->warning("Unable to apply changes to textures created without CPU write access", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "apply"));
                }
            }
        }

        void D3D11RenderTexture::refresh()
        {
            RenderTexture::refresh();

            /// \todo Refresh CPU data with RTV
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11RenderTexture::createD3DResources()
        {
            bool result = false;
            
            if(m_D3DDevice)
            {
                if(createD3DTexture2D())
                {
                    if(createD3DRenderTarget())
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Failed to create D3D11 Render Target", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DResources"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11 Texture2D", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DResources"));
                }
            }
            else
            {
                OcularLogger->error("D3D11 Device is NULL", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DResources"));
            }

            return result;
        }

        bool D3D11RenderTexture::createD3DTexture2D()
        {
            bool result = false;
            HRESULT hResult = S_OK;
            D3D11_TEXTURE2D_DESC descriptor;

            if(m_D3DSwapChain)
            {
                hResult = m_D3DSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_D3DTexture);
                
                if(hResult)
                {
                    m_D3DTexture->GetDesc(&descriptor);
                    D3D11GraphicsDriver::convertTextureDescriptor(descriptor, m_Descriptor);
                }
                else
                {
                    OcularLogger->error("Failed to retrieve D3D11SwapChain backbuffer with error ", hResult, OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DTexture2D"));
                }
            }
            else if(D3D11GraphicsDriver::convertTextureDescriptor(m_Descriptor, descriptor))
            {
                D3D11_SUBRESOURCE_DATA initData;
                initData.pSysMem          = &m_Pixels[0];
                initData.SysMemPitch      = (m_Descriptor.width * 4 * sizeof(float));
                initData.SysMemSlicePitch = ((m_Descriptor.width * m_Descriptor.height) * 4 * sizeof(float));

                hResult = m_D3DDevice->CreateTexture2D(&descriptor, &initData, &m_D3DTexture);

                if(hResult == S_OK)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11Texture2D with error ", hResult, OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DTexture2D"));
                }
            }
            else
            {
                OcularLogger->error("Invalid TextureDescriptor", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DTexture2D"));
            }

            return result;
        }

        bool D3D11RenderTexture::createD3DRenderTarget()
        {
            bool result = true;
            HRESULT hResult = m_D3DDevice->CreateRenderTargetView(m_D3DTexture, nullptr, &m_D3DRenderTargetView);

            if(hResult != S_OK)
            {
                OcularLogger->error("Failed to create D3D11RenderTargetView with error ", hResult, OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DRenderTarget"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}