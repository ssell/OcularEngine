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
#include "Mesh/D3D11IndexBuffer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11IndexBuffer::D3D11IndexBuffer(ID3D11Device* device, ID3D11DeviceContext* context)
            : IndexBuffer(),
              m_D3DDevice(device),
              m_D3DDeviceContext(context),
              m_D3DIndexBuffer(nullptr)
        {

        }

        D3D11IndexBuffer::~D3D11IndexBuffer()
        {
            if(m_D3DIndexBuffer)
            {
                unbind();

                m_D3DIndexBuffer->Release();
                m_D3DIndexBuffer = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool D3D11IndexBuffer::build()
        {
            bool result = true;

            if(m_D3DDevice)
            {
                if(m_D3DIndexBuffer)
                {
                    // Rebuilding the buffer? Release the old one
                    m_D3DIndexBuffer->Release();
                    m_D3DIndexBuffer = nullptr;
                }

                D3D11_BUFFER_DESC bufferDescr;
                ZeroMemory(&bufferDescr, sizeof(D3D11_BUFFER_DESC));
                bufferDescr.Usage     = D3D11_USAGE_DEFAULT;
                bufferDescr.ByteWidth = sizeof(uint32_t) * m_Indices.size();
                bufferDescr.BindFlags = D3D11_BIND_INDEX_BUFFER;
                
                D3D11_SUBRESOURCE_DATA bufferData;
                ZeroMemory(&bufferData, sizeof(D3D11_SUBRESOURCE_DATA));
                bufferData.pSysMem = &m_Indices[0];

                const HRESULT hResult = m_D3DDevice->CreateBuffer(&bufferDescr, &bufferData, &m_D3DIndexBuffer);

                if(hResult != S_OK)
                {
                    OcularLogger->error("Failed to create D3D11 Index Buffer with error ", hResult, OCULAR_INTERNAL_LOG("D3D11IndexBuffer", "build"));
                    result = false;
                }
            }
            else
            {
                OcularLogger->error("D3D Device is NULL", OCULAR_INTERNAL_LOG("D3D11IndexBuffer", "build"));
                result = false;
            }

            return result;
        }

        void D3D11IndexBuffer::bind()
        {
            if(m_D3DDeviceContext)
            {
                ID3D11Buffer* currBuffer = nullptr;
                m_D3DDeviceContext->IAGetIndexBuffer(&currBuffer, nullptr, nullptr);

                if(m_D3DIndexBuffer != currBuffer)
                {
                    m_D3DDeviceContext->IASetIndexBuffer(m_D3DIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
                }

                if(currBuffer)
                {
                    currBuffer->Release();
                    currBuffer = nullptr;
                }
            }
            else
            {
                OcularLogger->warning("Attempting to bind D3D11 Index Buffer with NULL Device Context", OCULAR_INTERNAL_LOG("D3D11IndexBuffer", "bind"));
            }
        }

        void D3D11IndexBuffer::unbind()
        {
            if(m_D3DDeviceContext)
            {
                // Only unbind if we are the currently bound buffer
                ID3D11Buffer* currBuffer = nullptr;
                m_D3DDeviceContext->IAGetIndexBuffer(&currBuffer, nullptr, nullptr);

                if(m_D3DIndexBuffer == currBuffer)
                {
                    m_D3DDeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
                }

                if(currBuffer)
                {
                    currBuffer->Release();
                    currBuffer = nullptr;
                }
            }
        }

        ID3D11Buffer* D3D11IndexBuffer::getD3DIndexBuffer()
        {
            return m_D3DIndexBuffer;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}