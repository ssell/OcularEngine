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

        void D3D11RenderTexture::apply()
        {
            RenderTexture::apply();


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

            D3D11_TEXTURE2D_DESC descriptor;
            
            if(D3D11GraphicsDriver::convertTextureDescriptor(m_Descriptor, descriptor))
            {
                HRESULT hResult = m_D3DDevice->CreateTexture2D(&descriptor, NULL, &m_D3DTexture);

                if(hResult = S_OK)
                {
                    result = true;
                }
                else
                {
                
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
            bool result = false;

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}