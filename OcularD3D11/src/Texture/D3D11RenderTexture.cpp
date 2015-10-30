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

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11RenderTexture::D3D11RenderTexture(uint32_t width, uint32_t height, TextureFilterMode filter, TextureUsageMode usage)
            : RenderTexture(width, height, filter, usage)
        {
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

        bool D3D11RenderTexture::create(ID3D11Device const* device)
        {
            bool result = false;

            if(m_D3DRenderTargetView)
            {
                // Texture is already created
                result = true;
            }
            else
            {
                if(device)
                {
                    D3D11_TEXTURE2D_DESC rtvDescr;
                    ZeroMemory(&rtvDescr, sizeof(D3D11_TEXTURE2D_DESC));

                    rtvDescr.Width = m_Width;
                    rtvDescr.Height = m_Height;
                }
                else
                {
                    OcularLogger->warning("D3D Device is NULL", OCULAR_INTERNAL_LOG("D3D11RenderTexture", "create"));
                }
            }

            return result;
        }

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

        }

        void D3D11RenderTexture::unload()
        {
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

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}