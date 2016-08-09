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

#include "Shader/Buffer/D3D11StructuredBuffer.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        D3D11StructuredBuffer::D3D11StructuredBuffer(GPUBufferDescriptor const& descriptor)
            : GPUBuffer(descriptor)
        {

        }

        D3D11StructuredBuffer::~D3D11StructuredBuffer()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void D3D11StructuredBuffer::bind()
        {

        }

        void D3D11StructuredBuffer::unbind()
        {

        }

        bool D3D11StructuredBuffer::build(void const* source)
        {
            bool result = false;

            return result;
        }
        
        bool D3D11StructuredBuffer::read(void* destination, uint32_t const start, uint32_t const size)
        {
            bool result = false;

            return result;
        }

        bool D3D11StructuredBuffer::write(void const* source, uint32_t const start, uint32_t const size)
        {
            bool result = false;

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}