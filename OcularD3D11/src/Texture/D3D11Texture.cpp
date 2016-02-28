/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#include "Texture/D3D11Texture.hpp"
#include "D3D11GraphicsDriver.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11Texture::D3D11Texture(ID3D11Device* device)
            : m_D3DDevice(device),
              m_D3DTexture(nullptr),
              m_D3DShaderResourceView(nullptr)
        {

        }

        D3D11Texture::~D3D11Texture()
        {
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

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        ID3D11Texture2D* D3D11Texture::getD3DTexture2D()
        {
            return m_D3DTexture;
        }

        ID3D11ShaderResourceView* D3D11Texture::getD3DShaderResource()
        {
            return m_D3DShaderResourceView;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11Texture::createD3DTexture2D(TextureDescriptor const& descriptor)
        {
            bool result = false;
            D3D11_TEXTURE2D_DESC textureDescr;

            if(D3D11GraphicsDriver::ConvertTextureDescriptor(descriptor, textureDescr))
            {
                m_D3DFormat = textureDescr.Format;
                const HRESULT hResult = m_D3DDevice->CreateTexture2D(&textureDescr, nullptr, &m_D3DTexture);

                if(hResult == S_OK)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11Texture2D with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DTexture2D"));
                }
            }
            else
            {
                OcularLogger->error("Invalid TextureDescriptor", OCULAR_INTERNAL_LOG("D3D11DepthTexture", "createD3DTexture2D"));
            }

            return result;
        }

        bool D3D11Texture::createD3DShaderResource(TextureDescriptor const& descriptor)
        {
            bool result = true;

            /*if(m_D3DTexture)
            {
                D3D11_TEXTURE2D_DESC descr;
                m_D3DTexture->GetDesc(&descr);

                if(descr.BindFlags & D3D11_BIND_SHADER_RESOURCE)
                {
                    D3D11_SHADER_RESOURCE_VIEW_DESC srvDescr;
                    ZeroMemory(&srvDescr, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
                    srvDescr.Format = m_D3DFormat;
                    srvDescr.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                    srvDescr.Texture2D.MipLevels = descriptor.mipmaps;

                    const HRESULT hResult = m_D3DDevice->CreateShaderResourceView(m_D3DTexture, &srvDescr, &m_D3DShaderResourceView);

                    if(hResult != S_OK)
                    {
                        D3D11_TEXTURE2D_DESC descr;
                        m_D3DTexture->GetDesc(&descr);

                        OcularLogger->error("Failed to create D3D11ShaderResourceView with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11Texture", "createD3DShaderResource"));
                        result = false;
                    }
                }
                else
                {
                    OcularLogger->warning("Attempting to create D3D11 SRV from texture without SRV bind flags", OCULAR_INTERNAL_LOG("D3D11Texture", "createD3DShaderResource"));
                }
            }
            else
            {
                OcularLogger->warning("Attempting to create D3D11 SRV from NULL texture", OCULAR_INTERNAL_LOG("D3D11Texture", "createD3DShaderResource"));
            }*/

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}