/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

namespace
{
    const float OneOver255 = 0.00392156862f;
}

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
            
            if(m_D3DTexture)
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
            }
            else
            {
                OcularLogger->warning("Attempting to create D3D11 SRV from NULL texture", OCULAR_INTERNAL_LOG("D3D11Texture", "createD3DShaderResource"));
                result = false;
            }

            return result;
        }

        void D3D11Texture::refresh(std::vector<Core::Color>& pixels, Graphics::TextureDescriptor const& descriptor)
        {
            // Downloads texture data from the GPU to the specified CPU pixels container
            
            // Create a separate staging texture to read from
            ID3D11Texture2D* stagingTexture = createStagingTexture();

            if(stagingTexture)
            {
                // Retrieve the device context
                D3D11GraphicsDriver* driver = dynamic_cast<D3D11GraphicsDriver*>(OcularGraphics.get());

                if(driver)
                {
                    auto context = driver->getD3DDeviceContext();

                    if(context)
                    {
                        D3D11_MAPPED_SUBRESOURCE mappedResource;
                        ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

                        const uint32_t subresourceIndex = D3D11CalcSubresource(0, 0, 0);

                        // Copy the contents of our texture to the staging texture
                        context->CopyResource(stagingTexture, m_D3DTexture);

                        // Map the contents of the staging texture to a subresource
                        const HRESULT hResult = context->Map(stagingTexture, subresourceIndex, D3D11_MAP_READ, 0, &mappedResource);

                        if(SUCCEEDED(hResult))
                        {
                            pixels.clear();
                            pixels.resize(descriptor.width * descriptor.height);

                            uint8_t* buffer = new uint8_t[descriptor.width * descriptor.height * descriptor.pixelSize];
                            memset(buffer, 0, descriptor.width * descriptor.height * descriptor.pixelSize);

                            copyData(
                                mappedResource.pData, 
                                buffer, 
                                mappedResource.RowPitch, 
                                descriptor.width * descriptor.pixelSize,
                                descriptor.height);

                            context->Unmap(stagingTexture, subresourceIndex);

                            switch(descriptor.pixelSize)
                            {
                            case 4:
                                copyToPixels4(buffer, pixels, descriptor);
                                break;

                            case 8:
                                copyToPixels8(buffer, pixels, descriptor);
                                break;

                            case 16:
                                copyToPixels16(buffer, pixels, descriptor);
                                break;

                            default:
                                OcularLogger->error("Invalid pixel size of ", descriptor.pixelSize, " for memory copy (expected 4, 8, or 16)", OCULAR_INTERNAL_LOG("D3D11Texture", "refresh"));
                                break;
                            }

                            delete [] buffer;
                        }
                        else
                        {
                            OcularLogger->error("Failed to map resource with error: ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11Texture", "refresh"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Invalid device context", OCULAR_INTERNAL_LOG("D3D11Texture2D", "refresh"));
                    }
                }
                else
                {
                    OcularLogger->error("Invalid graphics driver", OCULAR_INTERNAL_LOG("D3D11Texture2D", "refresh"));
                }

                stagingTexture->Release();
                stagingTexture = nullptr;
            }
            else
            {
                OcularLogger->error("Invalid staging texture", OCULAR_INTERNAL_LOG("D3D11Texture2D", "refresh"));
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        ID3D11Texture2D* D3D11Texture::createStagingTexture()
        {
            ID3D11Texture2D* result = nullptr;

            D3D11_TEXTURE2D_DESC descr;
            m_D3DTexture->GetDesc(&descr);

            descr.BindFlags = 0;
            descr.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            descr.Usage = D3D11_USAGE_STAGING;

            HRESULT hResult = m_D3DDevice->CreateTexture2D(&descr, nullptr, &result);

            if(FAILED(hResult))
            {
                OcularLogger->error("Failed to create staging texture with error: ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11Texture", "createStagingTexture"));
            }

            return result;
        }

        void D3D11Texture::copyData(void const* source, void* dest, uint32_t const sourceWidth, uint32_t const destWidth, uint32_t const height)
        {
            if(sourceWidth == destWidth)
            {
                memcpy(dest, source, sourceWidth * height);
            }
            else
            {
                // Widths are different due to added padding on the source buffer.
                // Must copy row-by-row to account for this.

                uint8_t const* sourcePtr = static_cast<uint8_t const*>(source);
                uint8_t* destPtr = static_cast<uint8_t*>(dest);

                for(uint32_t row = 0; row < height; row++)
                {
                    memcpy(destPtr, sourcePtr, destWidth);

                    sourcePtr += sourceWidth;
                    destPtr += destWidth;
                }
            }
        }

        void D3D11Texture::copyToPixels4(uint8_t const* source, std::vector<Core::Color>& dest, Graphics::TextureDescriptor const& descriptor)
        {
            uint32_t j = 0;

            for(uint32_t i = 0; i < dest.size(); i++)
            {
                dest[i].r = static_cast<float>(source[j++] * OneOver255);
                dest[i].g = static_cast<float>(source[j++] * OneOver255);
                dest[i].b = static_cast<float>(source[j++] * OneOver255);
                dest[i].a = static_cast<float>(source[j++] * OneOver255);
            }
        }

        void D3D11Texture::copyToPixels8(uint8_t const* source, std::vector<Core::Color>& dest, Graphics::TextureDescriptor const& descriptor)
        {
            uint32_t j = 0;

            for(uint32_t i = 0; i < dest.size(); i++)
            {
                dest[i].r = static_cast<float>(source[j += 2] * OneOver255);
                dest[i].g = static_cast<float>(source[j += 2] * OneOver255);
                dest[i].b = static_cast<float>(source[j += 2] * OneOver255);
                dest[i].a = static_cast<float>(source[j += 2] * OneOver255);
            }
        }

        void D3D11Texture::copyToPixels16(uint8_t const* source, std::vector<Core::Color>& dest, Graphics::TextureDescriptor const& descriptor)
        {
            memcpy(&dest[0], source, descriptor.width * descriptor.height * descriptor.pixelSize);
        }

    }
}