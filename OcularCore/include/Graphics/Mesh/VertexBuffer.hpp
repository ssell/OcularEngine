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
#ifndef __H__OCULAR_GRAPHICS_VERTEX_BUFFER__H__
#define __H__OCULAR_GRAPHICS_VERTEX_BUFFER__H__

#include "Vertex.hpp"
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
         * \class VertexBuffer 
         *
         * Generic VertexBuffer for use in rendering meshes and other geometric objects.
         * 
         * It should be noted that attempting to build, bind, or unbind an instance of this
         * parent class will have no effect. Because of this, VertexBuffers should generally
         * not be directly created (via new or other means), but instead be requested for
         * with the current GraphicsDriver. Example:
         *
         * \code
         *     Vertex vertices[3] = { ... };
         *
         *     //---------------------------------------------------------
         *     // Build, Bind, and Unbind do nothing
         *
         *     VertexBuffer* badBuffer = new VertexBuffer();
         *
         *     badBuffer->addVertices(vertices, 3);
         *     badBuffer->build(); 
         *     badBuffer->bind();
         *
         *     delete badBuffer;
         *     badBuffer = nullptr;
         *
         *     //---------------------------------------------------------
         *     // Build, Bind, and Unbind work as expected
         *
         *     // Here the IndexBuffer is actually a D3D11VertexBuffer, etc.
         *     VertexBuffer* goodBuffer = OcularGraphics->createVertexBuffer();
         *
         *     goodBuffer->addVertices(vertices, 3);
         *     goodBuffer->build();
         *     goodBuffer->bind();
         *
         *     delete goodBuffer;
         *     goodBuffer = nullptr;
         * \endcode
         */
        class VertexBuffer
        {
        public:

            VertexBuffer();
            virtual ~VertexBuffer();

            /**
             * Builds the vertex buffer. Must be called prior to first use, or after any changes
             * to the contents of the buffer.
             *
             * \note If this is an instance of VertexBuffer and not a child implementation (ie D3D11VertexBuffer, etc.)
             *       then this call will do nothing and always return FALSE.
             *
             * \return TRUE if the buffer was successfully built. Will return FALSE if there was an error.
             */
            virtual bool build();
            
            /**
             * Binds the vertex buffer for use in rendering.
             * 
             * \note If this is an instance of VertexBuffer and not a child implementation (ie D3D11VertexBuffer, etc.)
             *       then this call will do nothing.
             */
            virtual void bind();

            /**
             * Unbinds the vertex buffer and sets the currently bound vertex buffer to NULL.<br/>
             * This has no effect if this buffer is not the currently bound buffer.
             *
             * \note If this is an instance of VertexBuffer and not a child implementation (ie D3D11VertexBuffer, etc.)
             *       then this call will do nothing.
             */
            virtual void unbind();

            /**
             * Adds (appends) a vertex to the internal vertex buffer.
             *
             * \note that VertexBuffer::build must be called in order for any changes to take effect.
             * \param[in] vertex
             */
            virtual void addVertex(Vertex const& vertex);
            
            /**
             * Adds (appends) a vector of vertices to the internal vertex buffer.
             *
             * \note that VertexBuffer::build must be called in order for any changes to take effect.
             * \param[in] vertices
             */
            virtual void addVertices(std::vector<Vertex> const& vertices);

            /**
             * Adds (appends) a vector of indices to the internal index buffer.
             *
             * \note that VertexBuffer::build must be called in order for any changes to take effect.
             * \param[in] vertices
             * \param[in] count    The number of vertices to append from the provided vector
             */
            virtual void addVertices(std::vector<Vertex> const& vertices, uint32_t count);
            
            /**
             * Adds (appends) an array of indices to the internal index buffer.
             *
             * \note that VertexBuffer::build must be called in order for any changes to take effect.
             * \param[in] vertices
             * \param[in] count    The number of vertices to append from the provided vector
             */
            virtual void addVertices(Vertex const* vertices, uint32_t count);

            /**
             * \param[in] index Index of the vertex to retrieve on range [0, getNumVertices())
             * \return The vertex at the specified index.
             */
            Vertex const* getVertex(uint32_t index) const;

            /**
             * \return Reference to a vector of all vertices stored within this buffer
             */
            std::vector<Vertex> const& getVertices() const;

            /**
             * \return The number of vertices stored in this buffer
             */
            uint32_t getNumVertices() const;

        protected:

            std::vector<Vertex> m_Vertices;

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