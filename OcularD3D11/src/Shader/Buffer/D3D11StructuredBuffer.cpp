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

#include "Shader/Buffer/D3D11StructuredBuffer.hpp"
#include "D3D11GraphicsDriver.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        D3D11StructuredBuffer::D3D11StructuredBuffer(GPUBufferDescriptor const& descriptor)
            : GPUBuffer(descriptor),
              m_D3DDevice(nullptr),
              m_D3DDeviceContext(nullptr),
              m_D3DBuffer(nullptr),
              m_D3DSRV(nullptr)
        {

        }

        D3D11StructuredBuffer::~D3D11StructuredBuffer()
        {
            releaseResources();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void D3D11StructuredBuffer::bind()
        {
            if(getDevices())
            {
                // It is OK to bind a NULL SRV, though it may be unintended.

                if(static_cast<uint32_t>(m_Descriptor.stage) & static_cast<uint32_t>(GPUBufferStage::Vertex))
                {
                    m_D3DDeviceContext->VSSetShaderResources(m_Descriptor.slot, 1, &m_D3DSRV);
                }
                
                if(static_cast<uint32_t>(m_Descriptor.stage) & static_cast<uint32_t>(GPUBufferStage::Geometry))
                {
                    m_D3DDeviceContext->GSSetShaderResources(m_Descriptor.slot, 1, &m_D3DSRV);
                }
                
                if(static_cast<uint32_t>(m_Descriptor.stage) & static_cast<uint32_t>(GPUBufferStage::Fragment))
                {
                    m_D3DDeviceContext->PSSetShaderResources(m_Descriptor.slot, 1, &m_D3DSRV);
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve the D3D11 Device and/or Device Context", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "bind"));
            }
        }

        void D3D11StructuredBuffer::unbind()
        {
            if(getDevices())
            {
                if(static_cast<uint32_t>(m_Descriptor.stage) & static_cast<uint32_t>(GPUBufferStage::Vertex))
                {
                    m_D3DDeviceContext->VSSetShaderResources(m_Descriptor.slot, 1, nullptr);
                }
                
                if(static_cast<uint32_t>(m_Descriptor.stage) & static_cast<uint32_t>(GPUBufferStage::Geometry))
                {
                    m_D3DDeviceContext->GSSetShaderResources(m_Descriptor.slot, 1, nullptr);
                }
                
                if(static_cast<uint32_t>(m_Descriptor.stage) & static_cast<uint32_t>(GPUBufferStage::Fragment))
                {
                    m_D3DDeviceContext->PSSetShaderResources(m_Descriptor.slot, 1, nullptr);
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve the D3D11 Device and/or Device Context", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "bind"));
            }
        }

        bool D3D11StructuredBuffer::build(void const* source)
        {
            bool result = false;

            if(getDevices())
            {
                releaseResources();

                //--------------------------------------------------------
                // Build D3D Buffer Description

                D3D11_BUFFER_DESC bufferDescr;
                ZeroMemory(&bufferDescr, sizeof(D3D11_BUFFER_DESC));

                bufferDescr.ByteWidth = m_Descriptor.bufferSize;
                bufferDescr.StructureByteStride = m_Descriptor.elementSize;
                bufferDescr.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                bufferDescr.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

                switch(m_Descriptor.cpuAccess)
                {
                case GPUBufferAccess::Read:
                    bufferDescr.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                    break;

                case GPUBufferAccess::Write:
                    bufferDescr.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                    break;

                case GPUBufferAccess::ReadWrite:
                    bufferDescr.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
                    break;

                default:
                    bufferDescr.CPUAccessFlags = 0;
                    break;
                }

                if(m_Descriptor.gpuAccess == GPUBufferAccess::ReadWrite)
                {
                    bufferDescr.Usage = D3D11_USAGE_DEFAULT;
                }
                else if(m_Descriptor.gpuAccess == GPUBufferAccess::Read)
                {
                    if(m_Descriptor.cpuAccess == GPUBufferAccess::None)
                    {
                        bufferDescr.Usage = D3D11_USAGE_IMMUTABLE;
                    }
                    else
                    {
                        bufferDescr.Usage = D3D11_USAGE_DYNAMIC;
                    }
                }

                //--------------------------------------------------------
                // Create the 

                D3D11_SUBRESOURCE_DATA data;

                data.pSysMem = source;
                data.SysMemPitch = 0;
                data.SysMemSlicePitch = 0;
                
                //--------------------------------------------------------

                HRESULT hResult = m_D3DDevice->CreateBuffer(&bufferDescr, &data, &m_D3DBuffer);

                if(SUCCEEDED(hResult))
                {
                    D3D11_SHADER_RESOURCE_VIEW_DESC srvDescr;
                    ZeroMemory(&srvDescr, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

                    srvDescr.Format               = DXGI_FORMAT_UNKNOWN;
                    srvDescr.ViewDimension        = D3D11_SRV_DIMENSION_BUFFER;
                    srvDescr.Buffer.ElementOffset = 0;
                    srvDescr.Buffer.ElementWidth  = m_Descriptor.elementSize;

                    hResult = m_D3DDevice->CreateShaderResourceView(m_D3DBuffer, &srvDescr, &m_D3DSRV);

                    if(SUCCEEDED(hResult))
                    {
                        result = true;
                    }
                    else
                    {
                        m_D3DBuffer->Release();
                        m_D3DBuffer = nullptr;

                        OcularLogger->error("Failed to create D3D11 SRV", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "build"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to create D3D11 Buffer", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "build"));
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve the D3D11 Device and/or Device Context", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "build"));
            }

            return result;
        }
        
        bool D3D11StructuredBuffer::read(void* destination, uint32_t const start, uint32_t const size)
        {
            bool result = false;

            if(getDevices())
            {
                if(m_D3DBuffer)
                {
                    if((m_Descriptor.cpuAccess == GPUBufferAccess::Read) || (m_Descriptor.cpuAccess == GPUBufferAccess::ReadWrite))
                    {
                        D3D11_MAPPED_SUBRESOURCE mapped;
                        ZeroMemory(&mapped, sizeof(D3D11_MAPPED_SUBRESOURCE));

                        const HRESULT hResult = m_D3DDeviceContext->Map(m_D3DBuffer, 0, D3D11_MAP_READ, 0, &mapped);

                        if(SUCCEEDED(hResult))
                        {
                            if(start < m_Descriptor.bufferSize)
                            {
                                uint32_t availReadSize = m_Descriptor.bufferSize - start;
                                uint32_t trueReadSize = size;

                                if(size > availReadSize)
                                {
                                    memset(destination, 0, size);
                                    trueReadSize = availReadSize;
                                    OcularLogger->error("Requested to read from D3D11 Structured Buffer starting at index ", start, " for ", size, " bytes, but only ", availReadSize, " bytes exist (buffer size of ", m_Descriptor.bufferSize, "). Destination buffer data beyond the valid size will be set to 0", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "read"));
                                }
                                
                                memcpy(destination, static_cast<char*>(mapped.pData) + start, trueReadSize);

                                result = true;
                            }
                            else
                            {
                                OcularLogger->error("Starting index out-of-bounds (start at ", start, " with buffer size ", m_Descriptor.bufferSize, ")", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "read"));
                            }

                            m_D3DDeviceContext->Unmap(m_D3DBuffer, 0);
                        }
                        else
                        {
                            OcularLogger->error("Failed to map D3D11 Buffer", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "read"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Requested to perform read on buffer that was not created with CPU read access", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "read"));
                    }
                }
                else
                {
                    OcularLogger->error("Requested to perform read on buffer that has not been created (see D3D11StructuredBuffer::build)", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "read"));
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve the D3D11 Device and/or Device Context", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "read"));
            }

            return result;
        }

        bool D3D11StructuredBuffer::write(void const* source, uint32_t const start, uint32_t const size)
        {
            bool result = false;

            if(getDevices())
            {
                if(m_D3DBuffer)
                {
                    if((m_Descriptor.cpuAccess == GPUBufferAccess::Write) || (m_Descriptor.cpuAccess == GPUBufferAccess::ReadWrite))
                    {
                        D3D11_MAPPED_SUBRESOURCE mapped;
                        ZeroMemory(&mapped, sizeof(D3D11_MAPPED_SUBRESOURCE));

                        const HRESULT hResult = m_D3DDeviceContext->Map(m_D3DBuffer, 0, D3D11_MAP_WRITE, 0, &mapped);

                        if(SUCCEEDED(hResult))
                        {
                            if(start < m_Descriptor.bufferSize)
                            {
                                uint32_t availWriteSize = m_Descriptor.bufferSize - start;
                                uint32_t trueWriteSize = size;

                                if(size > availWriteSize)
                                {
                                    trueWriteSize = availWriteSize;
                                    OcularLogger->error("Requested to write to D3D11 Structured Buffer starting at index ", start, " for ", size, " bytes, but only ", availWriteSize, " bytes exist (buffer size of ", m_Descriptor.bufferSize, ")", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "write"));
                                }

                                memcpy(static_cast<char*>(mapped.pData) + start, source, trueWriteSize);

                                result = true;
                            }
                            else
                            {
                                OcularLogger->error("Starting index out-of-bounds (start at ", start, " with buffer size ", m_Descriptor.bufferSize, ")", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "read"));
                            }

                            m_D3DDeviceContext->Unmap(m_D3DBuffer, 0);
                        }
                        else
                        {
                            OcularLogger->error("Failed to map D3D11 Buffer", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "write"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Requested to perform write on buffer that was not created with CPU write access", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "write"));
                    }
                }
                else
                {
                    OcularLogger->error("Requested to perform write on buffer that has not been created (see D3D11StructuredBuffer::build)", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "write"));
                }
            }
            else
            {
                OcularLogger->error("Failed to retrieve the D3D11 Device and/or Device Context", OCULAR_INTERNAL_LOG("D3D11StructuredBuffer", "write"));
            }

            return result;
        }

        ID3D11Buffer* D3D11StructuredBuffer::getD3DBuffer()
        {
            return m_D3DBuffer;
        }

        ID3D11ShaderResourceView* D3D11StructuredBuffer::getD3DShaderResource()
        {
            return m_D3DSRV;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        bool D3D11StructuredBuffer::getDevices()
        {
            bool result = true;

            if((m_D3DDevice == nullptr) || (m_D3DDeviceContext == nullptr))
            {
                D3D11GraphicsDriver* driver = dynamic_cast<D3D11GraphicsDriver*>(OcularGraphics.get());

                if(driver)
                {
                    m_D3DDevice = driver->getD3DDevice();
                    m_D3DDeviceContext = driver->getD3DDeviceContext();

                    if((m_D3DDevice == nullptr) || (m_D3DDeviceContext == nullptr))
                    {
                        result = false;
                    }
                }
                else
                {
                    result = false;
                }
            }

            return result;
        }

        void D3D11StructuredBuffer::releaseResources()
        {
            if(m_D3DSRV)
            {
                m_D3DSRV->Release();
                m_D3DSRV = nullptr;
            }

            if(m_D3DBuffer)
            {
                m_D3DBuffer->Release();
                m_D3DBuffer = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}