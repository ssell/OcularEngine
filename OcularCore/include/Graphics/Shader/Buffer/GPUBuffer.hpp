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
#ifndef __H__OCULAR_GRAPHICS_GPU_BUFFER__H__
#define __H__OCULAR_GRAPHICS_GPU_BUFFER__H__

#include <cstdint>

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
         * \enum GPUBufferAccess
         */
        enum class GPUBufferAccess
        {
            None  = 0,
            Read,
            Write,
            ReadWrite
        };

        /**
         * \enum GPUBufferStage
         */
        enum class GPUBufferStage
        {
            None     = 0,
            Vertex   = 1,
            Geometry = 2,
            Fragment = 4
        };

        /**
         * \struct GPUBufferDescriptor
         */
        struct GPUBufferDescriptor
        {
            GPUBufferDescriptor();
            ~GPUBufferDescriptor();

            GPUBufferAccess cpuAccess;     ///< CPU access level
            GPUBufferAccess gpuAccess;     ///< GPU access level 

            GPUBufferStage stage;          ///< Which shader stage to bind the buffer to

            uint32_t bufferSize;           ///< Total size of the buffer in bytes
            uint32_t elementSize;          ///< Size of each individual element in the buffer
            uint32_t slot;                 ///< Register to bind the buffer to (a `t` register in HLSL)
        };

        /**
         * \class GPUBuffer
         * \brief A generic buffer that can be uploaded to the GPU.
         */
        class GPUBuffer
        {
        public:

            GPUBuffer(GPUBufferDescriptor const& descriptor);
            ~GPUBuffer();

            //------------------------------------------------------------

            /**
             * Binds the buffer to shader stage and slot specified in the descriptor.
             */
            virtual void bind();

            /**
             * Unbinds the buffer in the stage and slot specified by the descriptor.
             */
            virtual void unbind();

            /**
             * Attempts to (re)build the buffer.
             * For buffers built without CPU write access, this is the only way to provide data.
             *
             * \param[in] source Optional source data. If NULL, buffer will be populated with 0.
             */
            virtual bool build(void const* source);

            /**
             * Attempts to read data from the buffer.  
             * Only available to buffers created with Read CPU Access.
             *
             * \param[out] destination Destination to copy buffer data into. 
             * \param[in]  start       Starting offset into the GPU buffer to start reading from.
             * \param[in]  size        Size of data to be read.
             *
             * \result May return FALSE if: buffer does not have read cpu access, start + size
             *         exceeds gpu buffer size, destination is NULL, or API failure during reading.
             */
            virtual bool read(void* destination, uint32_t start, uint32_t size);
            
            /**
             * Attempts to write data to the buffer.
             * Only available to buffers created with Write CPU Access.
             *
             * \param[in] source Source of data to place into buffer. If source is NULL, buffer will be filled with 0.
             * \param[in] start  Starting offset into the GPU buffer to start writing to.
             * \param[in] size   Size of the data to write.
             *
             * \return May return FALSE if: buffer does not have write cpu access, start + size
             *         exceeds gpu buffer size, or API failure during reading.
             */
            virtual bool write(void const* source, uint32_t start, uint32_t size);

            /**
             * \return Reference to the buffer descriptor.
             */
            GPUBufferDescriptor const& getDescriptor() const;

        protected:

            GPUBufferDescriptor m_Descriptor;

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