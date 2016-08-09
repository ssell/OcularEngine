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

#include "GPUBuffer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        GPUBufferDescriptor::GPUBufferDescriptor()
            : cpuAccess(GPUBufferAccess::None),
              gpuAccess(GPUBufferAccess::None),
              stage(GPUBufferStage::None),
              bufferSize(0),
              elementSize(0),
              slot(0)
        {

        }

        GPUBufferDescriptor::~GPUBufferDescriptor()
        {

        }

        GPUBuffer::GPUBuffer(GPUBufferDescriptor const& descriptor)
            : m_Descriptor(descriptor)
        {

        }

        GPUBuffer::~GPUBuffer()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void GPUBuffer::bind()
        {

        }

        void GPUBuffer::unbind()
        {

        }

        bool GPUBuffer::build(void const* source)
        {
            return false;
        }

        bool GPUBuffer::read(void* destination, uint32_t const start, uint32_t size)
        {
            return false;
        }

        bool GPUBuffer::write(void const* source, uint32_t const start, uint32_t const size)
        {
            return false;
        }

        GPUBufferDescriptor const& GPUBuffer::getDescriptor() const
        {
            return m_Descriptor;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}