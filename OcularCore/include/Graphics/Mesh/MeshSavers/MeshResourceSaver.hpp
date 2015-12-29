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
#ifndef __H__OCULAR_GRAPHICS_MESH_RESOURCE_SAVER__H__
#define __H__OCULAR_GRAPHICS_MESH_RESOURCE_SAVER__H__

#include "Resources/ResourceSaver.hpp"
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
        class VertexBuffer;
        class IndexBuffer;

        /**
         * \class MeshResourceSaver
         *
         * This is a common base implementation for all other ResourceSavers that deal with
         * saving Mesh resources to disk. It provides a common base saveResource
         * method as well as multiple utility helper methods.
         *
         * By inheriting from MeshResourceSaver instead of AResourceSaver, the developer
         * needs to only worry about their specific saveFile implementation.
         */
        class MeshResourceSaver : public Core::AResourceSaver
        {
        public:

            MeshResourceSaver(std::string const& extension);
            virtual ~MeshResourceSaver();

            virtual bool saveResource(Core::Resource* resource, Core::File const& file);

        protected:

            /**
             * Each MeshResourceSaver must provide a custom implementation for it's specific file type.
             *
             * The input into this method is guaranteed to be valid. This means
             *
             *   - The source file exists and is writeable
             *   - The dimensions are valid
             *   - There is a non-zero number of pixels, and their number is equal to (width * height)
             *
             * \param[in] file         File to write to. This file has already been verified to exist and be writeable.
             * \param[in] vertexBuffer Vertex data to write
             * \param[in] indexBuffer  Index data to write
             *
             * \return TRUE if the file was successfully saved.
             */
            virtual bool saveFile(Core::File const& file, VertexBuffer const* vertexBuffer, IndexBuffer const* indexBuffer) = 0;

            /**
             * Checks if the specified file is valid. It can be valid in one of two ways:
             *
             *   - The file exists and is writeable
             *   - The file did not previously exist, but it (and potentially it's parent directories) successfully created
             *
             * \return TRUE if the file is valid.
             */
            virtual bool isFileValid(Core::File& file);

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