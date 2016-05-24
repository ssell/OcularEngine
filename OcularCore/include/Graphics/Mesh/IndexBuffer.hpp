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
#ifndef __H__OCULAR_GRAPHICS_INDEX_BUFFER__H__
#define __H__OCULAR_GRAPHICS_INDEX_BUFFER__H__

#include <cstdint>
#include <vector>

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
         * \class IndexBuffer 
         *
         * Generic IndexBuffer for use in rendering meshes and other geometric objects.
         * 
         * It should be noted that attempting to build, bind, or unbind an instance of this
         * parent class will have no effect. Because of this, IndexBuffers should generally
         * not be directly created (via new or other means), but instead be requested for
         * with the current GraphicsDriver. Example:
         *
         * \code
         *     uint32_t indices[3] = { 0, 1, 2 };
         *
         *     //---------------------------------------------------------
         *     // Build, Bind, and Unbind do nothing
         *
         *     IndexBuffer* badBuffer = new IndexBuffer();
         *
         *     badBuffer->addIndices(indices, 3);
         *     badBuffer->build(); 
         *     badBuffer->bind();
         *
         *     delete badBuffer;
         *     badBuffer = nullptr;
         *
         *     //---------------------------------------------------------
         *     // Build, Bind, and Unbind work as expected
         *
         *     // Here the IndexBuffer is actually a D3D11IndexBuffer, etc.
         *     IndexBuffer* goodBuffer = OcularGraphics->createIndexBuffer();
         *
         *     goodBuffer->addIndices(indices, 3);
         *     goodBuffer->build();
         *     goodBuffer->bind();
         *
         *     delete goodBuffer;
         *     goodBuffer = nullptr;
         * \endcode
         */
        class IndexBuffer
        {
        public:

            IndexBuffer();
            virtual ~IndexBuffer();

            /**
             * Builds the index buffer. Must be called prior to first use, or after any changes
             * to the contents of the buffer.
             *
             * \note If this is an instance of IndexBuffer and not a child implementation (ie D3D11IndexBuffer, etc.)
             *       then this call will do nothing and always return FALSE.
             *
             * \return TRUE if the buffer was successfully built. Will return FALSE if there was an error.
             */
            virtual bool build();

            /**
             * Binds the index buffer for use in rendering.
             * 
             * \note If this is an instance of IndexBuffer and not a child implementation (ie D3D11IndexBuffer, etc.)
             *       then this call will do nothing.
             */
            virtual void bind();

            /**
             * Unbinds the index buffer and sets the currently bound index buffer to NULL.<br/>
             * This has no effect if this buffer is not the currently bound buffer.
             *
             * \note If this is an instance of IndexBuffer and not a child implementation (ie D3D11IndexBuffer, etc.)
             *       then this call will do nothing.
             */
            virtual void unbind();

            /**
             * Adds (appends) an index to the internal index buffer.
             *
             * \note that IndexBuffer::build must be called in order for any changes to take effect.
             * \param[in] index
             */
            virtual void addIndex(uint32_t index);

            /**
             * Adds (appends) a vector of indices to the internal index buffer.
             *
             * \note that IndexBuffer::build must be called in order for any changes to take effect.
             * \param[in] indices
             */
            virtual void addIndices(std::vector<uint32_t> const& indices);

            /**
             * Adds (appends) a vector of indices to the internal index buffer.
             *
             * \note that IndexBuffer::build must be called in order for any changes to take effect.
             * \param[in] indices
             * \param[in] count   The number of indices to append from the provided vector
             */
            virtual void addIndices(std::vector<uint32_t> const& indices, uint32_t count);
            
            /**
             * Adds (appends) an array of indices to the internal index buffer.
             *
             * \note that IndexBuffer::build must be called in order for any changes to take effect.
             * \param[in] indices
             * \param[in] count   The number of indices to append from the provided vector
             */
            virtual void addIndices(uint32_t const* indices, uint32_t count);

            /**
             * \param[in] index Index of the index to retrieve on range [0, getNumIndices())
             * \return The index at the specified index.
             */
            uint32_t getIndex(uint32_t index);

            /**
             * \return Reference to a vector of all indices stored within this buffer
             */
            std::vector<uint32_t> const& getIndices() const;

            /**
             * \return The number of indices stored in this buffer
             */
            uint32_t getNumIndices() const;

        protected:

            std::vector<uint32_t> m_Indices;

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