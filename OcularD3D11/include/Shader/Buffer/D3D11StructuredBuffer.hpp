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

#pragma once
#ifndef __H__OCULAR_D3D11_GRAPHICS_STRUCTURED_BUFFER__H__
#define __H__OCULAR_D3D11_GRAPHICS_STRUCTURED_BUFFER__H__

#include "Graphics/Shader/Buffer/GPUBuffer.hpp"
#include <d3d11.h>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \class D3D11StructuredBuffer 
         *
         * Implementation of GPUBuffer to be used with HLSL StructuredBuffers.
         * Buffers of this type are bound to the t# registers.
         *
         * A structured buffer is created by the driver when the following conditions
         * are met by the buffer descriptor:
         *
         *     - CPU Access (None, Read, and/or Write)
         *     - GPU Access (Read Only)
         *     - Element size is non-zero
         *
         * For best performance, data in a StructuredBuffer should be 16-byte aligned (float4).
         */
        class D3D11StructuredBuffer : public GPUBuffer 
        {
        public:
            
            D3D11StructuredBuffer(GPUBufferDescriptor const& descriptor);
            virtual ~D3D11StructuredBuffer();

            //------------------------------------------------------------

            virtual void bind() override;
            virtual void unbind() override;

            virtual bool build(void const* source) override;

            virtual bool read(void* destination, uint32_t start, uint32_t size) override;
            virtual bool write(void const* source, uint32_t start, uint32_t size) override;

            ID3D11Buffer* getD3DBuffer();
            ID3D11ShaderResourceView* getD3DShaderResource();

        protected:

            bool getDevices();
            void releaseResources();

            //------------------------------------------------------------

            ID3D11Device* m_D3DDevice;
            ID3D11DeviceContext* m_D3DDeviceContext;

            ID3D11Buffer* m_D3DBuffer;
            ID3D11ShaderResourceView* m_D3DSRV;

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif