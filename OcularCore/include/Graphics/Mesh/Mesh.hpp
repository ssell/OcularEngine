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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_MESH__H__
#define __H__OCULAR_GRAPHICS_MESH__H__

#include "Resources/Resource.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

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
         * \class Mesh 
         * \brief Combination of a VertexBuffer and IndexBuffer
         */
        class Mesh : public Core::Resource
        {
        public:

            Mesh();
            ~Mesh();

            /**
             * Binds the Vertex and Index Buffers of this Mesh
             */
            virtual bool bind();

            /**
             * Unbinds the Vertex and Index Buffers of this Mesh
             */
            virtual void unbind();

            /**
             * Unloads this Mesh from CPU and GPU memory
             */
            virtual void unload() override;

            /**
             * Sets the VertexBuffer for this Mesh.
             *
             * \note The Mesh takes ownership of the buffer and will delete it when 
             *       it is no longer in use.
             *
             * \param[in] buffer
             */
            void setVertexBuffer(VertexBuffer* buffer);
            
            /**
             * \note Any changes made to the buffer will not take affect until VertexBuffer::build is called
             *       and the Mesh is rebound.
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