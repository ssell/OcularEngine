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
#include "Texture/D3D11DepthTexture.hpp"
#include "D3D11GraphicsDriver.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11DepthTexture::D3D11DepthTexture(TextureDescriptor const& descriptor, ID3D11Device* device)
            : DepthTexture(descriptor), 
              m_D3DDevice(device), 
              m_D3DTexture(nullptr), 
              m_D3DDepthStencilView(nullptr), 
              m_D3DShaderResourceView(nullptr),
              m_D3DFormat(DXGI_FORMAT_UNKNOWN)
        {

        }

        D3D11DepthTexture::~D3D11DepthTexture()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        ID3D11Texture2D* D3D11DepthTexture::getD3DTexture()
        {
            return m_D3DTexture;
        }

        ID3D11DepthStencilView* D3D11DepthTexture::getD3DDepthStencilView()
        {
            return m_D3DDepthStencilView;
        }

        void D3D11DepthTexture::unload()
        {
            DepthTexture::unload();

            if(m_D3DTexture)
            {
                m_D3DTexture->Release();
                m_D3DTexture = nullptr;
            }

            if(m_D3DDepthStencilView)
            {
                m_D3DDepthStencilView->Release();
                m_D3DDepthStencilView = nullptr;
            }

            if(m_D3DShaderResourceView)
            {
                m_D3DShaderResourceView->Release();
                m_D3DShaderResourceView = nullptr;
            }
        }

        void D3D11DepthTexture::apply()
        {
            DepthTexture::apply();

            if(m_D3DDepthStencilView == nullptr)
            {
                // We are creating the resources and not just applying changes...

                if(!createD3DResources())
                {
                    OcularLogger->error("Failed to create D3D resources", OCULAR_INTERNAL_LOG("D3D11DepthTexture", "apply"));
                    unload();
                }
            }
            else
            {
                // We are (attempting) to apply changes to the resources
                if((m_Descriptor.cpuAccess == TextureAccess::WriteOnly) || (m_Descriptor.cpuAccess == TextureAccess::ReadWrite))
                {
                    /// \todo Apply CPU changes to DSV
                }
                else
                {
                    OcularLogger->warning("Unable to apply changes to textures created without CPU write access", OCULAR_INTERNAL_LOG("D3D11DepthTexture", "apply"));
                }
            }
        }

        void D3D11DepthTexture::refresh()
        {
            DepthTexture::refresh();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11DepthTexture::createD3DResources()
        {
            bool result = false;

            if(m_D3DDevice)
            {
                if(createD3DTexture2D())
                {
                    if(createD3DDepthStencil())
                    {
                        if(createD3DShaderResource())
                        {
                            result = true;
                        }
                    }
                    else
                    {
                        OcularLogger->error("Failed to create D3D11 Depth Stencil", OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DResources"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11 Texture2D", OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DResources"));
                }
            }
            else
            {
                OcularLogger->error("D3D11 Device is NULL", OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DResources"));
            }

            return result;
        }

        bool D3D11DepthTexture::createD3DTexture2D()
        {
            bool result = false;
            D3D11_TEXTURE2D_DESC descriptor;

            if(D3D11GraphicsDriver::convertTextureDescriptor(m_Descriptor, descriptor))
            {
                m_D3DFormat = descriptor.Format;
                const HRESULT hResult = m_D3DDevice->CreateTexture2D(&descriptor, nullptr, &m_D3DTexture);

                if(hResult == S_OK)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11Texture2D with error ", hResult, OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DTexture2D"));
                }
            }
            else
            {
                OcularLogger->error("Invalid TextureDescriptor", OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DTexture2D"));
            }

            return result;
        }

        bool D3D11DepthTexture::createD3DDepthStencil()
        {
            bool result = true;

            D3D11_DEPTH_STENCIL_VIEW_DESC dsvDescr;
            ZeroMemory(&dsvDescr, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
            dsvDescr.Format        = DXGI_FORMAT_UNKNOWN;
            dsvDescr.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

            HRESULT hResult = m_D3DDevice->CreateDepthStencilView(m_D3DTexture, &dsvDescr, &m_D3DDepthStencilView);

            if(hResult != S_OK)
            {
                OcularLogger->error("Failed to create D3D11DepthStencilView with error ", hResult, OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DDepthStencil"));
                result = false;
            }

            return result;
        }

        bool D3D11DepthTexture::createD3DShaderResource()
        {
            bool result = true;

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDescr;
            ZeroMemory(&srvDescr, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
            srvDescr.Format = m_D3DFormat;
            srvDescr.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            srvDescr.Texture2D.MipLevels = m_Descriptor.mipmaps;

            const HRESULT hResult = m_D3DDevice->CreateShaderResourceView(m_D3DTexture, &srvDescr, &m_D3DShaderResourceView);

            if(hResult != S_OK)
            {
                OcularLogger->error("Failed to create D3D11ShaderResourceView with error ", hResult, OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DShaderResource"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}