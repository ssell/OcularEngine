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
              m_D3DDeviceContext(context)
        {
            m_ShaderResourceViews = new ID3D11ShaderResourceView*[m_Textures.size()];
            m_NullShaderResourceViews = new ID3D11ShaderResourceView*[m_Textures.size()];

            for(uint32_t i = 0; i < m_Textures.size(); i++)
            {
                m_ShaderResourceViews[i] = nullptr;
                m_NullShaderResourceViews = nullptr;
            }
        }

        D3D11Material::~D3D11Material()
        {
            unbind();

            for(uint32_t i = 0; i < m_Textures.size(); i++)
            {
                m_ShaderResourceViews[i]->Release();
                m_ShaderResourceViews[i] = nullptr;
            }

            delete[] m_ShaderResourceViews;
            delete[] m_NullShaderResourceViews;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11Material::bind()
        {
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
                D3D11Texture* d3dTexture = (D3D11Texture*)texture;

                if(d3dTexture)
                {
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

        void D3D11Material::bindTextures()
        {
            if(m_D3DDeviceContext)
            {
                const uint32_t size = static_cast<uint32_t>(m_Textures.size());

                if(m_VertexShader)
                {
                    m_D3DDeviceContext->VSSetShaderResources(0, size, m_ShaderResourceViews);
                }

                if(m_GeometryShader)
                {
                    m_D3DDeviceContext->GSSetShaderResources(0, size, m_ShaderResourceViews);
                }

                if(m_FragmentShader)
                {
                    m_D3DDeviceContext->PSSetShaderResources(0, size, m_ShaderResourceViews);
                }
            }
            else
            {
                OcularLogger->warning("Attempting to bind material textures with a NULL context", OCULAR_INTERNAL_LOG("D3D11Material", "bindTextures"));
            }
        }

        void D3D11Material::unbindTextures()
        {
           if(m_D3DDeviceContext)
            {
                const uint32_t size = static_cast<uint32_t>(m_Textures.size());

                if(m_VertexShader)
                {
                    m_D3DDeviceContext->VSSetShaderResources(0, size, m_NullShaderResourceViews);
                }

                if(m_GeometryShader)
                {
                    m_D3DDeviceContext->GSSetShaderResources(0, size, m_NullShaderResourceViews);
                }

                if(m_FragmentShader)
                {
                    m_D3DDeviceContext->PSSetShaderResources(0, size, m_NullShaderResourceViews);
                }
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