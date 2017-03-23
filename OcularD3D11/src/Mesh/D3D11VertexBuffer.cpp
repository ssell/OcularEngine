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
#include "Mesh/D3D11VertexBuffer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11VertexBuffer::D3D11VertexBuffer(ID3D11Device* device, ID3D11DeviceContext* context)
            : VertexBuffer(),
              m_D3DDevice(device),
              m_D3DDeviceContext(context),
              m_D3DVertexBuffer(nullptr)
        {

        }

        D3D11VertexBuffer::~D3D11VertexBuffer()
        {
            if(m_D3DVertexBuffer)
            {
                m_D3DVertexBuffer->Release();
                m_D3DVertexBuffer = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool D3D11VertexBuffer::build()
        {
            bool result = true;

            if(m_D3DDevice)
            {
                if(m_Vertices.size())
                {
                    if(m_D3DVertexBuffer)
                    {
                        // Rebuilding the buffer? Release the old one
                        m_D3DVertexBuffer->Release();
                        m_D3DVertexBuffer = nullptr;
                    }

                    D3D11_BUFFER_DESC bufferDescr;
                    ZeroMemory(&bufferDescr, sizeof(D3D11_BUFFER_DESC));
                    bufferDescr.Usage = D3D11_USAGE_DEFAULT;
                    bufferDescr.ByteWidth = static_cast<uint32_t>(sizeof(Vertex) * m_Vertices.size());
                    bufferDescr.BindFlags = D3D11_BIND_VERTEX_BUFFER;

                    D3D11_SUBRESOURCE_DATA bufferData;
                    ZeroMemory(&bufferData, sizeof(D3D11_SUBRESOURCE_DATA));
                    bufferData.pSysMem = &m_Vertices[0];

                    const HRESULT hResult = m_D3DDevice->CreateBuffer(&bufferDescr, &bufferData, &m_D3DVertexBuffer);

                    if(hResult != S_OK)
                    {
                        OcularLogger->error("Failed to create D3D11 Vertex Buffer with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11VertexBuffer", "build"));
                        result = false;
                    }
                }
                else
                {
                    OcularLogger->error("Vertex Buffer must have at least one vertex", OCULAR_INTERNAL_LOG("D3D11VertexBuffer", "build"));
                    result = false;
                }
            }
            else
            {
                OcularLogger->error("D3D Device is NULL", OCULAR_INTERNAL_LOG("D3D11VertexBuffer", "build"));
                result = false;
            }

            return result;
        }

        void D3D11VertexBuffer::bind()
        {
            if(m_D3DDeviceContext)
            {
                ID3D11Buffer* currBuffer = nullptr;
                m_D3DDeviceContext->IAGetVertexBuffers(0, 1, &currBuffer, nullptr, nullptr);

                if(m_D3DVertexBuffer != currBuffer)
                {
                    static const uint32_t stride = sizeof(Vertex);
                    uint32_t offset = 0;

                    if(m_D3DVertexBuffer)
                    {
                        m_D3DDeviceContext->IASetVertexBuffers(0, 1, &m_D3DVertexBuffer, &stride, &offset);
                    }
                    else
                    {
                        m_D3DDeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
                    }
                }

                if(currBuffer)
                {
                    currBuffer->Release();
                    currBuffer = nullptr;
                }
            }
            else
            {
                OcularLogger->warning("Attempting to bind D3D11 Vertex Buffer with NULL Device Context", OCULAR_INTERNAL_LOG("D3D11VertexBuffer", "bind"));
            }
        }

        void D3D11VertexBuffer::unbind()
        {
            if(m_D3DDeviceContext)
            {
                // Only unbind if we are the currently bound buffer
                ID3D11Buffer* currBuffer = nullptr;
                m_D3DDeviceContext->IAGetVertexBuffers(0, 1, &currBuffer, nullptr, nullptr);

                if(m_D3DVertexBuffer == currBuffer)
                {
                    static const uint32_t stride = sizeof(Vertex);
                    m_D3DDeviceContext->IASetVertexBuffers(0, 0, nullptr, &stride, 0);
                }

                if(currBuffer)
                {
                    currBuffer->Release();
                    currBuffer = nullptr;
                }
            }
        }

        ID3D11Buffer* D3D11VertexBuffer::getD3DVertexBuffer()
        {
            return m_D3DVertexBuffer;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}