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
#include "Shader/D3D11UniformBuffer.hpp"

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
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void D3D11UniformBuffer::bind()
        {
            UniformBuffer::bind();

            //------------------------------------------------------------
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

            //------------------------------------------------------------
            // Bind the buffer data to the shader stages

            if(m_D3DBuffer)
            {
                if(m_D3DDeviceContext)
                {
                    m_D3DDeviceContext->VSSetConstantBuffers(m_Type, 1, &m_D3DBuffer);
                    m_D3DDeviceContext->PSSetConstantBuffers(m_Type, 1, &m_D3DBuffer);
                }
            }
        }

        void D3D11UniformBuffer::unbind()
        {
            UniformBuffer::unbind();

            if(m_D3DDeviceContext)
            {
                m_D3DDeviceContext->PSSetConstantBuffers(m_Type, 1, nullptr);
                m_D3DDeviceContext->VSSetConstantBuffers(m_Type, 1, nullptr);
            }
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
             *     Matrix3x3f -> {value[0][0], value[0][1], value[0][2], padding,
             *                    value[1][0], value[1][1], value[1][2], padding,
             *                    value[2][0], value[2][1], value[2][2], padding}
             *
             *     Matrix4x4f -> {value[0][0], value[0][1], value[0][2], value[0][3],
             *                    value[1][0], value[1][1], value[1][2], value[1][3],
             *                    value[2][0], value[2][1], value[2][2], value[2][3],
             *                    value[3][0], value[3][1], value[3][2], value[3][3]}
             */

            Uniform const* lastUniform = &m_Uniforms[(m_Uniforms.size() - 1)];

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

                const uint32_t dataSize = numRegisters * UniformPackingAlignment;

                //--------------------------------------------------------
                // Create and/or resize the raw data if necessary

                if((m_UniformData == nullptr) || (m_UniformDataSize != dataSize))
                {
                    if(m_UniformData)
                    {
                        delete[] m_UniformData;
                    }

                    // _aligned_malloc is Windows only, but that is OK for this Direct3D implementation
                    // If porting to non-Windows, see memalign functions for GCC (http://man7.org/linux/man-pages/man3/posix_memalign.3.html)
                    m_UniformData = (float*)_aligned_malloc(dataSize, UniformPackingAlignment);
                    m_UniformDataSize = dataSize;
                }

                //--------------------------------------------------------
                // Fill the raw data. Currently we just refill the entire buffer, but this may be changed in the future.


            }
        }

        void D3D11UniformBuffer::buildD3DBuffer()
        {
        
        }

        void D3D11UniformBuffer::updateD3DBuffer()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}