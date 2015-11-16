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
#include "Texture/D3D11Texture2D.hpp"
#include "D3D11GraphicsDriver.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11Texture2D::D3D11Texture2D(TextureDescriptor const& descriptor, ID3D11Device* device)
            : Texture2D(descriptor),
              m_D3DDevice(nullptr),
              m_D3DTexture(nullptr),
              m_D3DShaderResourceView(nullptr),
              m_D3DFormat(DXGI_FORMAT_UNKNOWN)
        {

        }

        D3D11Texture2D::~D3D11Texture2D()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11Texture2D::unload()
        {
            Texture2D::unload();

            if(m_D3DTexture)
            {
                m_D3DTexture->Release();
                m_D3DTexture = nullptr;
            }

            if(m_D3DShaderResourceView)
            {
                m_D3DShaderResourceView->Release();
                m_D3DShaderResourceView = nullptr;
            }
        }

        void D3D11Texture2D::apply()
        {
            Texture2D::apply();

            if(m_D3DTexture == nullptr)
            {
                // We are (re)creating the resources and not just applying changes...
                // Upon creation we can provide source texture data

                if(createD3DTexture2D())
                {
                    if(!createD3DShaderResource())
                    {
                        OcularLogger->error("Failed to create D3D11 Shader Resource", OCULAR_INTERNAL_LOG("D3D11Texture2D", "apply"));
                        unload();
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11 Texture2D", OCULAR_INTERNAL_LOG("D3D11Texture2D", "apply"));
                    unload();
                }
            }
            else
            {
                // We are (attempting) to apply changes to the resources
                if((m_Descriptor.cpuAccess == TextureAccess::WriteOnly) || (m_Descriptor.cpuAccess == TextureAccess::ReadWrite))
                {
                    /// \todo Apply CPU changes to Texture2D
                }
                else
                {
                    OcularLogger->warning("Unable to apply changes to textures created without CPU write access", OCULAR_INTERNAL_LOG("D3D11Texture2D", "apply"));
                }
            }
        }

        void D3D11Texture2D::refresh()
        {
            Texture2D::refresh();

            /// \todo Refresh CPU data with Texture2D
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11Texture2D::createD3DTexture2D()
        {
            bool result = false;

            D3D11_TEXTURE2D_DESC descriptor;
            
            if(D3D11GraphicsDriver::convertTextureDescriptor(m_Descriptor, descriptor))
            {
                D3D11_SUBRESOURCE_DATA initData;
                initData.pSysMem          = &m_Pixels[0];
                initData.SysMemPitch      = (m_Descriptor.width * 4 * sizeof(float));
                initData.SysMemSlicePitch = ((m_Descriptor.width * m_Descriptor.height) * 4 * sizeof(float));

                HRESULT hResult = m_D3DDevice->CreateTexture2D(&descriptor, &initData, &m_D3DTexture);

                if(hResult == S_OK)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11Texture2D with error ", hResult, OCULAR_INTERNAL_LOG("D3D11Texture2D", "createD3DTexture2D"));
                }
            }
            else
            {
                OcularLogger->error("Invalid TextureDescriptor", OCULAR_INTERNAL_LOG("D3D11Texture2D", "createD3DTexture2D"));
            }

            return result;
        }

        bool D3D11Texture2D::createD3DShaderResource()
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
                OcularLogger->error("Failed to create D3D11ShaderResourceView with error ", hResult, OCULAR_INTERNAL_LOG("D3D11Texture2D", "createD3DShaderResource"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}