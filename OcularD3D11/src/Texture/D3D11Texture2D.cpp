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
            : Texture2D(descriptor), D3D11Texture(device)
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

                if(createD3DTexture2D(m_Descriptor))
                {
                    if(!createD3DShaderResource(m_Descriptor))
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
            D3D11Texture::refresh(m_Pixels, m_Descriptor);
            m_IsInMemory = true;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11Texture2D::createD3DTexture2D(TextureDescriptor const& descriptor)
        {
            bool result = false;

            D3D11_TEXTURE2D_DESC texDescr;
            
            if(D3D11GraphicsDriver::ConvertTextureDescriptor(descriptor, texDescr))
            {
                D3D11_SUBRESOURCE_DATA initData;
                initData.pSysMem          = &m_Pixels[0];
                initData.SysMemPitch      = (descriptor.width * 4 * sizeof(float));
                initData.SysMemSlicePitch = ((descriptor.width * descriptor.height) * 4 * sizeof(float));

                HRESULT hResult = m_D3DDevice->CreateTexture2D(&texDescr, &initData, &m_D3DTexture);

                if(hResult == S_OK)
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11Texture2D with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11Texture2D", "createD3DTexture2D"));
                }
            }
            else
            {
                OcularLogger->error("Invalid TextureDescriptor", OCULAR_INTERNAL_LOG("D3D11Texture2D", "createD3DTexture2D"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}