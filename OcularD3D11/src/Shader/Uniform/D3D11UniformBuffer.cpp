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
#include "Shader/Uniform/D3D11UniformBuffer.hpp"
#include "D3D11GraphicsDriver.hpp"

namespace
{
    static const uint32_t UniformPackingAlignment = 16;
}

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11UniformBuffer::D3D11UniformBuffer(UniformBufferType const type, ID3D11Device* device, ID3D11DeviceContext* context)
            : UniformBuffer(type),
              m_D3DDevice(device),
              m_D3DDeviceContext(context),
              m_D3DBuffer(nullptr)
        {
        
        }

        D3D11UniformBuffer::~D3D11UniformBuffer()
        {
            unbind();

            if(m_UniformData)
            {
                // Since we do _aligned_malloc to create the data, we can not rely on the 
                // default destructor's delete to release it
                _aligned_free(m_UniformData);
                m_UniformData = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11UniformBuffer::bind()
        {
            UniformBuffer::bind();
            
            if(m_Uniforms.empty())
            {
                // Fast exit if there are no uniforms to bind
                return;
            }

            if(m_D3DDevice == nullptr)
            {
                /**
                 * The issue here is that the CameraManger is requesting to create UniformBuffer objects
                 * inside the main OcularEngine initialization method. But at that point, OcularGraphics
                 * has not been fully initialized (only created) as the driver requires a window to have
                 * been created to use the HWND during D3D11 setup.
                 */

                OcularLogger->warning("Using workaround for poor initialization routine", OCULAR_INTERNAL_LOG("D3D11UniformBuffer", "bind"));
                D3D11GraphicsDriver* driver = (D3D11GraphicsDriver*)OcularGraphics.get();

                if(driver)
                {
                    m_D3DDevice = driver->getD3DDevice();
                    m_D3DDeviceContext = driver->getD3DDeviceContext();
                }
            }

            if(m_D3DDevice)
            {
                if(m_D3DDeviceContext)
                {
                    //----------------------------------------------------
                    // Make sure buffer is built and up-to-date

                    if(m_IsDirty)
                    {
                        packUniformData();

                        if(m_D3DBuffer == nullptr)
                        {
                            buildD3DBuffer();
                        }
                        else
                        {
                            updateD3DBuffer();
                        }

                        m_IsDirty = false;
                    }

                    //----------------------------------------------------
                    // Bind the buffer data to the shader stages

                    // Setting a constant buffer is a very costly operation.
                    // Make sure we are not setting the already active buffer.

                    // This is possible when, for example, rendering multiple
                    // objects with the same material. The same per-object buffer
                    // is universally shared, and will be updated for every object.
                    // Thus calling a bind will just perform an update (data mapping)
                    // and not require any additional action.

                    ID3D11Buffer* currentBuffer = nullptr;

                    m_D3DDeviceContext->VSGetConstantBuffers(0, 1, &currentBuffer);

                    if((currentBuffer == nullptr) || (currentBuffer != m_D3DBuffer))
                    {
                        m_D3DDeviceContext->VSSetConstantBuffers(m_Type, 1, &m_D3DBuffer);
                        m_D3DDeviceContext->PSSetConstantBuffers(m_Type, 1, &m_D3DBuffer);
                    }
                }
                else
                {
                    OcularLogger->error("D3D11 Device Context is NULL", OCULAR_INTERNAL_LOG("D3D11UniformBuffer", "bind"));
                }
            }
            else
            {
                OcularLogger->error("D3D11 Device is NULL", OCULAR_INTERNAL_LOG("D3D11UniformBuffer", "bind"));
            }
        }

        void D3D11UniformBuffer::unbind()
        {
            UniformBuffer::unbind();

            // We actually don't do anything in unbind to prevent needless buffer switching
            // because switching constant buffers is very expensive.

            // if(m_D3DDeviceContext)
            // {
            //     m_D3DDeviceContext->PSSetConstantBuffers(m_Type, 1, nullptr);
            //     m_D3DDeviceContext->VSSetConstantBuffers(m_Type, 1, nullptr);
            // }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void D3D11UniformBuffer::packUniformData()
        {
            /**
             * This method most likely could be placed in the UniformBuffer class.
             * But, there is potentially some very-API specific packing going on here.
             *
             * For D3D11, everything must be packed along 16-byte registers and this
             * behaviour may or may not be the same for OpenGL (have not yet gotten to
             * writing the GL4 library, and it's been several years since using OpenGL).
             *
             * If OpenGL ends up having identical requirements, then this method will
             * be migrated to the parent UniformBuffer class.
             */
            
            /**
             * Here we pack everything along 16-byte sections of the raw data array.
             * This means that padding will need to be added for both single-float 
             * uniform values and for Matrix3x3 values.
             *
             * Examples:
             *
             *          float -> {value, padding, padding , padding}
             *
             *       Vector4f -> {value.x, value.y, value.z, value.w}
             *
             *     Matrix3x3 -> {value[0][0], value[0][1], value[0][2], padding,
             *                    value[1][0], value[1][1], value[1][2], padding,
             *                    value[2][0], value[2][1], value[2][2], padding}
             *
             *     Matrix4x4 -> {value[0][0], value[0][1], value[0][2], value[0][3],
             *                    value[1][0], value[1][1], value[1][2], value[1][3],
             *                    value[2][0], value[2][1], value[2][2], value[2][3],
             *                    value[3][0], value[3][1], value[3][2], value[3][3]}
             */

            Uniform* lastUniform = &m_Uniforms[0];

            for(uint32_t i = 0; i < m_Uniforms.size(); i++)
            {
                if(m_Uniforms[i].getRegister() > lastUniform->getRegister())
                {
                    lastUniform = &m_Uniforms[i];
                }
            }

            if(lastUniform)
            {
                //--------------------------------------------------------
                // Get the expected data size

                uint32_t numRegisters = lastUniform->getRegister();    // Last declared register. This final uniform may stretch over multiple registers.

                if(lastUniform->getSize() > 4)
                {
                    // Uniform is a Matrix, and will stretch over 4 total registers (irregardless of whether it is 3x3 or 4x4)
                    numRegisters += 3;  // One of the registers is already accounted for; Total of 3 additional registers
                }

                const uint32_t dataSize = ((numRegisters + 1) * sizeof(float) * 4);  // Each register is 4 floats in size

                //--------------------------------------------------------
                // Create and/or resize the raw data if necessary

                if((m_UniformData == nullptr) || (m_UniformDataSize != dataSize))
                {
                    if(m_UniformData)
                    {
                        _aligned_free(m_UniformData);
                        m_UniformData = nullptr;
                    }

                    // _aligned_malloc is Windows only, but that is OK for this Direct3D implementation
                    // If porting to non-Windows, see memalign functions for GCC (http://man7.org/linux/man-pages/man3/posix_memalign.3.html)
                    m_UniformData = (float*)_aligned_malloc(dataSize, UniformPackingAlignment);
                    memset(m_UniformData, 0, dataSize);

                    m_UniformDataSize = dataSize;
                }

                //--------------------------------------------------------
                // Fill the raw data. Currently we just refill the entire buffer, but this may be changed in the future.

                uint32_t bufferIndex = 0;

                for(uint32_t i = 0; i < m_Uniforms.size(); i++)
                {
                    float* data = m_Uniforms[i].getData();

                    if(data)
                    {
                        bufferIndex = (m_Uniforms[i].getRegister() * 4);  // Each register is 4 floats in size

                        switch(m_Uniforms[i].getSize())
                        {
                        case 1:
                            m_UniformData[bufferIndex] = data[0];
                            break;

                        case 4:
                            memcpy(&m_UniformData[bufferIndex], data, sizeof(float) * 4);
                            break;

                        case 12:
                            memcpy(&m_UniformData[bufferIndex], data, sizeof(float) * 12);
                            break;

                        case 16:
                            memcpy(&m_UniformData[bufferIndex], data, sizeof(float) * 16);
                            break;

                        default:
                            OcularLogger->error("Unexpected data copy case", OCULAR_INTERNAL_LOG("D3D11UniformBuffer", "packUniformData"));
                            break;
                        }
                    }
                }
            }
        }

        void D3D11UniformBuffer::buildD3DBuffer()
        {
            if(m_D3DBuffer)
            {
                m_D3DBuffer->Release();
                m_D3DBuffer = nullptr;
            }

            D3D11_BUFFER_DESC bufferDescr;
            ZeroMemory(&bufferDescr, sizeof(D3D11_BUFFER_DESC));
            bufferDescr.ByteWidth      = m_UniformDataSize;
            bufferDescr.Usage          = D3D11_USAGE_DYNAMIC;
            bufferDescr.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
            bufferDescr.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            
            D3D11_SUBRESOURCE_DATA bufferData;
            ZeroMemory(&bufferData, sizeof(D3D11_SUBRESOURCE_DATA));
            bufferData.pSysMem = m_UniformData;

            const HRESULT hResult = m_D3DDevice->CreateBuffer(&bufferDescr, &bufferData, &m_D3DBuffer);

            if(hResult != S_OK)
            {
                OcularLogger->error("Failed to create D3DBuffer with error ", hResult, OCULAR_INTERNAL_LOG("D3D11UniformBuffer", "buildD3DBuffer"));
            }
        }

        void D3D11UniformBuffer::updateD3DBuffer()
        {
            D3D11_BUFFER_DESC bufferDescr;
            m_D3DBuffer->GetDesc(&bufferDescr);

            if(bufferDescr.ByteWidth != m_UniformDataSize)
            {
                // Actual buffer size has changed.
                // No choice but to completely rebuild the buffer.
                buildD3DBuffer();
            }
            else
            {
                D3D11_MAPPED_SUBRESOURCE mappedResource;
                HRESULT hResult = m_D3DDeviceContext->Map(m_D3DBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

                if(hResult != S_OK)
                {
                    OcularLogger->error("Failed to map the buffer resource data", OCULAR_INTERNAL_LOG("D3D11UniformBuffer", "updateD3DBuffer"));
                }

                memcpy(mappedResource.pData, m_UniformData, m_UniformDataSize);
                m_D3DDeviceContext->Unmap(m_D3DBuffer, 0);
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}