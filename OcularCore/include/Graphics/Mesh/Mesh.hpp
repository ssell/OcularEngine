/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#include "Graphics/Mesh/SubMesh.hpp"
#include "Math/Vector3.hpp"

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
        class SubMesh;
        class VertexBuffer;
        class IndexBuffer;

        /**
         * \class Mesh 
         * \brief Combination of a VertexBuffer and IndexBuffer
         */
        class Mesh : public Core::Resource
        {
        public:

            Mesh();
            virtual ~Mesh();
            
            //------------------------------------------------------------
            // Virtual Methods
            //------------------------------------------------------------

            /**
             * Does nothing.
             *
             * See SubMesh::Bind to bind a vertex/index buffer pair.
             */
            virtual bool bind();

            /**
             * Does nothing.
             *
             * See SubMesh::Unind to unbind a vertex/index buffer pair.
             */
            virtual void unbind();

            /**
             * Unloads this Mesh from CPU and GPU memory
             */
            virtual void unload() override;
            
            //------------------------------------------------------------
            // Buffer Methods
            //------------------------------------------------------------

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
             * \param[in] submesh Index of the submesh that should receive the new buffer.
             */
            void setVertexBuffer(VertexBuffer* buffer, uint32_t submesh = 0);
            
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
             * \param[in] submesh The index of the submesh whose buffer should be retrieved.
             * \return A pointer to the specified IndexBuffer. May be NULL.
             */
            VertexBuffer* getVertexBuffer(uint32_t submesh = 0);
            
            /**
             * Sets the IndexBuffer for this Mesh.
             *
             * \note The Mesh takes ownership of the buffer and will delete it when 
             *       it is no longer in use.
             *
             * \param[in] buffer
             * \param[in] submesh Index of the submesh that should receive the new buffer.
             */
            void setIndexBuffer(IndexBuffer* buffer, uint32_t submesh = 0);
            
            /**
             * \note Any changes made to the buffer will not take affect until IndexBuffer::build is called
             *       and the Mesh is rebound.
             *
             * \param[in] submesh The index of the submesh whose buffer should be retrieved.
             * \return A pointer to the specified IndexBuffer. May be NULL.
             */
            IndexBuffer* getIndexBuffer(uint32_t submesh = 0);
            
            //------------------------------------------------------------
            // Min/Max Point Methods
            //------------------------------------------------------------

            /**
             * Calculates the minimum and maximum vertex spatial points within the mesh.
             * \note Potentially slow on extremely large data sets.
             */
            void calculateMinMaxPoints();

            /**
             * Sets the minimum and maximum vertex spatial points within the mesh data.
             *
             * These should represent the extrema along each of the local axis, and do
             * not necessarily correlate to an actual vertex within the mesh.
             *
             * \param[in] min
             * \param[in] max
             */
            void setMinMaxPoints(Math::Vector3f const& min, Math::Vector3f const& max);

            /** 
             * Returns the minimum vertex spatial point along all 3 axis.
             * This point does not necessarily correspond with an actual vertex position.
             *
             * Note that this point is cached, and is thus retrieved in constant time. It
             * is also the local point prior to any transformations that may be performed
             * on the parent renderer/model/etc. (translate, scale, rotate).
             *
             * \return Minimum point along all 3 local axis.
             */
            Math::Vector3f const& getMinPoint() const;

            /** 
             * Returns the maximum vertex spatial point along all 3 axis.
             * This point does not necessarily correspond with an actual vertex position.
             *
             * Note that this point is cached, and is thus retrieved in constant time. It
             * is also the local point prior to any transformations that may be performed
             * on the parent renderer/model/etc. (translate, scale, rotate).
             *
             * \return Maximum point along all 3 local axis.
             */
            Math::Vector3f const& getMaxPoint() const;
            
            //------------------------------------------------------------
            // Sub-Mesh Methods
            //------------------------------------------------------------

            /**
             * Returns the SubMesh at the specified index.
             * 
             * \param[in] index
             * \return Pointer to the requested SubMesh. Returns NULL if the specified index is out-of-bounds.
             */
            SubMesh* getSubMesh(uint32_t index) const;

            /**
             * Adds a SubMesh to the Mesh.
             *
             * If provided SubMesh is NULL, then a new SubMesh is created.
             *
             * \note The Mesh assumes ownership of the SubMesh and will delete it upon destruction or removal.
             *
             * \param[in] submesh
             * \return Index of the newly added SubMesh
             */
            uint32_t addSubMesh(SubMesh* submesh = nullptr);

            /**
             * Sets the SubMesh at the specified index.
             *
             * The pre-existing SubMesh is deleted during this action.
             *
             * \note The Mesh assumes ownership of the SubMesh and will delete it upon destruction or removal.
             *
             * \param[in] submesh
             * \param[in] index
             *
             * \return Returns TRUE if the SubMesh was correctly set. Returns FALSE if the specified index is invalid.
             */
            bool setSubMesh(SubMesh* submesh, uint32_t index);
            
            /**
             * Destroys the SubMesh at the specified index.
             *
             * \param[in] index
             * \return Returns TRUE if the SubMesh was successfully destroyed. Returns FALSE if the specified index is invalid.
             */
            bool removeSubMesh(uint32_t index);
            
            /**
             * \return Returns the number of SubMeshes that comprise this Mesh.
             */
            uint32_t getNumSubMeshes() const;

        protected:

            Math::Vector3f m_MinPoint;
            Math::Vector3f m_MaxPoint;

            std::vector<SubMesh*> m_SubMeshes;

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