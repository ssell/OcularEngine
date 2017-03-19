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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_SUB_MESH__H__
#define __H__OCULAR_GRAPHICS_SUB_MESH__H__

#include "Graphics/Mesh/VertexBuffer.hpp"
#include "Graphics/Mesh/IndexBuffer.hpp"

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
        class IndexBuffer;
        class VertexBuffer;

        /**
         * \class SubMesh 
         * \brief Combination of a VertexBuffer and IndexBuffer
         */
        class SubMesh
        {
        public:

            SubMesh();
            ~SubMesh();

            /**
             * Binds the Vertex and Index Buffers of this SubMesh
             */
            bool bind();

            /**
             * Unbinds the Vertex and Index Buffers of this SubMesh
             */
            void unbind();

            /**
             * Unloads this Mesh from CPU and GPU memory
             */
            void unload();

            /**
             * Sets the VertexBuffer for this Mesh.
             *
             * After modifying vertex data, one should call either calculateMinMaxPoints()
             * or setMinMaxPoints() so that bounding volumes, etc. based off of this mesh
             * will be accurate.
             *
             * The Mesh takes ownership of the buffer and will delete it when 
             * it is no longer in use.
             *
             * \param[in] buffer
             */
            void setVertexBuffer(VertexBuffer* buffer);
            
            /**
             * Returns a pointer to the current vertex buffer of this mesh, which can then be modified.
             *
             * After modifying vertex data, one should call either calculateMinMaxPoints()
             * or setMinMaxPoints() so that bounding volumes, etc. based off of this mesh
             * will be accurate.
             *
             * Any changes made to the buffer will not take affect until VertexBuffer::build is called
             * and the Mesh is rebound.
             *
             * \return A pointer to the current VertexBuffer for this mesh.
             */
            VertexBuffer* getVertexBuffer();
            
            /**
             * Sets the IndexBuffer for this Mesh.
             *
             * \note The Mesh takes ownership of the buffer and will delete it when 
             *       it is no longer in use.
             *
             * \param[in] buffer
             */
            void setIndexBuffer(IndexBuffer* buffer);
            
            /**
             * \note Any changes made to the buffer will not take affect until IndexBuffer::build is called
             *       and the Mesh is rebound.
             *
             * \return A pointer to the current IndexBuffer for this mesh.
             */
            IndexBuffer* getIndexBuffer();

        protected:
            
            VertexBuffer* m_VertexBuffer;
            IndexBuffer* m_IndexBuffer;

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