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
            : RenderTexture(descriptor),
              D3D11Texture(device),
              m_D3DRenderTargetView(nullptr)
        {

        }

        D3D11RenderTexture::D3D11RenderTexture(TextureDescriptor const& descriptor, ID3D11Device* device, IDXGISwapChain* swapchain)
            : RenderTexture(descriptor),
              D3D11Texture(device),
              m_D3DRenderTargetView(nullptr),
              m_D3DSwapChain(swapchain)
        {

        }

        D3D11RenderTexture::~D3D11RenderTexture()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

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

            if(m_D3DShaderResourceView)
            {
                m_D3DShaderResourceView->Release();
                m_D3DShaderResourceView = nullptr;
            }
        }

        void D3D11RenderTexture::apply()
        {
            RenderTexture::apply();

            if(m_D3DRenderTargetView == nullptr)
            {
                // We are creating the resources and not just applying changes...
                // Upon creation we can provide source texture data

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
            D3D11Texture::refresh(m_Pixels, m_Descriptor);
            m_IsInMemory = true;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11RenderTexture::createD3DResources()
        {
            bool result = false;
            
            if(m_D3DDevice)
            {
                if(createD3DTexture2D(m_Descriptor))
                {
                    if(createD3DRenderTarget())
                    {
                        if(createD3DShaderResource(m_Descriptor))
                        {
                            result = true;
                        }
                        else
                        {
                            OcularLogger->error("Failed to create D3D11 Shader Resource", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DResources"));
                        }
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

        bool D3D11RenderTexture::createD3DTexture2D(TextureDescriptor const& descriptor)
        {
            bool result = false;
            HRESULT hResult = S_OK;
            D3D11_TEXTURE2D_DESC texDescr;

            if(m_D3DSwapChain)
            {
                //--------------------------------------------------------
                // Create the backbuffer Texture2D from the SwapChain buffer

                hResult = m_D3DSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_D3DTexture);
                
                if(hResult == S_OK)
                {
                    m_D3DTexture->GetDesc(&texDescr);
                    D3D11GraphicsDriver::ConvertTextureDescriptor(texDescr, m_Descriptor);
                    m_D3DFormat = texDescr.Format;

                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to retrieve D3D11SwapChain backbuffer with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DTexture2D"));
                }
            }
            else if(D3D11GraphicsDriver::ConvertTextureDescriptor(m_Descriptor, texDescr))
            {
                //--------------------------------------------------------
                // Create the backbuffer Texture2D from scratch using pixel data

                D3D11_SUBRESOURCE_DATA initData;
                initData.pSysMem          = &m_Pixels[0];
                initData.SysMemPitch      = (m_Descriptor.width * 4 * sizeof(float));
                initData.SysMemSlicePitch = ((m_Descriptor.width * m_Descriptor.height) * 4 * sizeof(float));

                m_D3DFormat = texDescr.Format;
                hResult = m_D3DDevice->CreateTexture2D(&texDescr, &initData, &m_D3DTexture);

                if(hResult == S_OK)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11Texture2D with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DTexture2D"));
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

            D3D11_RENDER_TARGET_VIEW_DESC descr;
            ZeroMemory(&descr, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));


            HRESULT hResult = m_D3DDevice->CreateRenderTargetView(m_D3DTexture, nullptr, &m_D3DRenderTargetView);

            if(hResult != S_OK)
            {
                OcularLogger->error("Failed to create D3D11RenderTargetView with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11RenderTexture", "createD3DRenderTarget"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}