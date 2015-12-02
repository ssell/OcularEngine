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
#include "Shader/D3D11VertexShader.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        ID3D11InputLayout* D3D11VertexShader::m_D3DInputLayout = nullptr;

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11VertexShader::D3D11VertexShader(ID3D11Device* device, ID3D11DeviceContext* context)
            : VertexShader(),
              m_D3DDevice(device),
              m_D3DDeviceContext(context),
              m_D3DShader(nullptr),
              m_D3DBlob(nullptr)
        {
            m_Type = Core::ResourceType::Shader;
        }

        D3D11VertexShader::~D3D11VertexShader()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void D3D11VertexShader::unload()
        {
            VertexShader::unload();

            if(m_D3DInputLayout)
            {
                m_D3DInputLayout->Release();
                m_D3DInputLayout = nullptr;
            }

            if(m_D3DShader)
            {
                m_D3DShader->Release();
                m_D3DShader = nullptr;
            }

            if(m_D3DBlob)
            {
                m_D3DBlob->Release();
                m_D3DBlob = nullptr;
            }
        }

        void D3D11VertexShader::bind()
        {
            VertexShader::bind();

            if(m_D3DInputLayout == nullptr)
            {
                createInputLayout();
            }

            if(m_D3DDeviceContext)
            {
                m_D3DDeviceContext->VSSetShader(m_D3DShader, nullptr, 0);
            }
        }
            
        void D3D11VertexShader::unbind()
        {
            VertexShader::unbind();

            if(m_D3DDeviceContext)
            {
                m_D3DDeviceContext->VSSetShader(nullptr, nullptr, 0);
            }
        }

        void D3D11VertexShader::setD3DShader(ID3D11VertexShader* shader)
        {
            if(m_D3DShader)
            {
                m_D3DShader->Release();
            }

            m_D3DShader = shader;
        }

        ID3D11VertexShader* D3D11VertexShader::getD3DShader()
        {
            return m_D3DShader;
        }

        void D3D11VertexShader::setD3DBlob(ID3DBlob* blob)
        {
            if(m_D3DBlob)
            {
                m_D3DBlob->Release();
            }

            m_D3DBlob = blob;
        }

        ID3DBlob* D3D11VertexShader::getD3DBlob()
        {
            return m_D3DBlob;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11VertexShader::createInputLayout()
        {
            bool result = false;

            if(m_D3DDevice)
            {
                if(m_D3DBlob)
                {
                    D3D11_INPUT_ELEMENT_DESC inputElements[7] =
                    {
                        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0},
                        {"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                        {"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                        {"TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
                        {"TEXCOORD", 3, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
                    };

                    const HRESULT hResult = m_D3DDevice->CreateInputLayout(inputElements, ARRAYSIZE(inputElements), m_D3DBlob->GetBufferPointer(), m_D3DBlob->GetBufferSize(), &m_D3DInputLayout);

                    if(hResult != S_OK)
                    {
                        OcularLogger->error("Failed to create D3D11 Input Layout with error ", hResult, OCULAR_INTERNAL_LOG("D3D11VertexShader", "createInputLayout"));
                    }
                    else
                    {
                        if(m_D3DDeviceContext)
                        {
                            m_D3DDeviceContext->IASetInputLayout(m_D3DInputLayout);
                            result = true;
                        }
                        else
                        {
                            m_D3DInputLayout->Release();
                            m_D3DInputLayout = nullptr;

                            OcularLogger->error("D3D11 Device Context is NULL", OCULAR_INTERNAL_LOG("D3D11VertexShader", "createInputLayout"));
                        }
                    }
                }
                else
                {
                    OcularLogger->error("Compiled Shader Blob is NULL", OCULAR_INTERNAL_LOG("D3D11VertexShader", "createInputLayout"));
                }
            }
            else
            {
                OcularLogger->error("D3D11 Device is NULL", OCULAR_INTERNAL_LOG("D3D11VertexShader", "createInputLayout"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}