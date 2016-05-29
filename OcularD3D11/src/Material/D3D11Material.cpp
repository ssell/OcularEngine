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
#include "Material/D3D11Material.hpp"
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

        D3D11Material::D3D11Material(ID3D11DeviceContext* context)
            : Material(),
              m_D3DDeviceContext(context),
              m_D3DSampler(nullptr)
        {
            m_ShaderResourceViews.resize(m_Textures.size(), nullptr);
            m_NullShaderResourceViews.resize(m_Textures.size(), nullptr);

            createSampler();
        }

        D3D11Material::~D3D11Material()
        {
            unbind();

            for(uint32_t i = 0; i < static_cast<uint32_t>(m_Textures.size()); i++)
            {
                m_ShaderResourceViews[i]->Release();
                m_ShaderResourceViews[i] = nullptr;
            }

            m_ShaderResourceViews.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11Material::bind()
        {
            bindStateChanges();
            bindShaders();
            bindTextures();
        }

        void D3D11Material::unbind()
        {
            unbindShaders();
            unbindTextures();
        }

        bool D3D11Material::setTexture(uint32_t index, std::string const& name, Texture* texture)
        {
            bool result = Material::setTexture(index, name, texture);

            if(result)
            {
                D3D11Texture* d3dTexture = dynamic_cast<D3D11Texture*>(texture);

                if(d3dTexture)
                {
                    if(m_ShaderResourceViews.size() < m_Textures.size())
                    {
                        m_ShaderResourceViews.resize(m_Textures.size(), nullptr);
                        m_NullShaderResourceViews.resize(m_Textures.size(), nullptr);
                    }

                    if(m_ShaderResourceViews[index])
                    {
                        m_ShaderResourceViews[index]->Release();
                    }

                    m_ShaderResourceViews[index] = d3dTexture->getD3DShaderResource();
                }
                else
                {
                    removeTexture(index);
                    OcularLogger->error("Cannot bind a non-D3D11 texture to a D3D11 Material", OCULAR_INTERNAL_LOG("D3D11Material", "setTexture"));

                    result = false;
                }
            }

            return result;
        }

        void D3D11Material::removeTexture(uint32_t const index)
        {
            Material::removeTexture(index);

            if(m_ShaderResourceViews[index])
            {
                m_ShaderResourceViews[index]->Release();
                m_ShaderResourceViews[index] = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void D3D11Material::createSampler()
        {
            D3D11_SAMPLER_DESC descr;
            ZeroMemory(&descr, sizeof(D3D11_SAMPLER_DESC));

            descr.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	        descr.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	        descr.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	        descr.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	        descr.MipLODBias = 0.0f;
	        descr.MaxAnisotropy = 1;
	        descr.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	        descr.BorderColor[0] = 0;
	        descr.BorderColor[1] = 0;
	        descr.BorderColor[2] = 0;
	        descr.BorderColor[3] = 0;
	        descr.MinLOD = 0;
	        descr.MaxLOD = D3D11_FLOAT32_MAX;

            ID3D11Device* device = nullptr;

            if(m_D3DDeviceContext)
            {
                m_D3DDeviceContext->GetDevice(&device);

                if(device)
                {
                    HRESULT hResult = device->CreateSamplerState(&descr, &m_D3DSampler);

                    if(FAILED(hResult))
                    {
                        OcularLogger->error("Failed to create D3D11Sampler for Material '", m_MappingName, "'", OCULAR_INTERNAL_LOG("D3D11Material", "createSampler"));
                    }
                }
            }
        }

        void D3D11Material::bindTextures()
        {
            if(m_D3DDeviceContext && m_ShaderResourceViews.size())
            {
                const uint32_t size = static_cast<uint32_t>(m_Textures.size());

                if(m_D3DSampler)
                {
                    m_D3DDeviceContext->PSSetSamplers(0, 1, &m_D3DSampler);
                }

                if(m_VertexShader)
                {
                    m_D3DDeviceContext->VSSetShaderResources(0, size, &m_ShaderResourceViews[0]);
                }

                if(m_GeometryShader)
                {
                    m_D3DDeviceContext->GSSetShaderResources(0, size, &m_ShaderResourceViews[0]);
                }

                if(m_FragmentShader)
                {
                    m_D3DDeviceContext->PSSetShaderResources(0, size, &m_ShaderResourceViews[0]);
                }
            }
        }

        void D3D11Material::unbindTextures()
        {
           if(m_D3DDeviceContext)
            {
                const uint32_t size = static_cast<uint32_t>(m_Textures.size());

                if(m_VertexShader)
                {
                    m_D3DDeviceContext->VSSetShaderResources(0, size, &m_NullShaderResourceViews[0]);
                }

                if(m_GeometryShader)
                {
                    m_D3DDeviceContext->GSSetShaderResources(0, size, &m_NullShaderResourceViews[0]);
                }

                if(m_FragmentShader)
                {
                    m_D3DDeviceContext->PSSetShaderResources(0, size, &m_NullShaderResourceViews[0]);
                }

                m_D3DDeviceContext->PSSetSamplers(0, 1, nullptr);
            }
            else
            {
                OcularLogger->warning("Attempting to unbind material textures with a NULL context", OCULAR_INTERNAL_LOG("D3D11Material", "unbindTextures"));
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}