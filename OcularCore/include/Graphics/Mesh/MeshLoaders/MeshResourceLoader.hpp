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
#ifndef __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER__H__
#define __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER__H__

#include "Resources/ResourceLoader.hpp"
#include "Graphics/Mesh/Vertex.hpp"

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
         * \class MeshResourceLoader
         *
         * This is a common base implementation for all other ResourceLoaders that deal with
         * creating and loading mesh resources. It provides a common base loadResource
         * method as well as multiple utility helper methods.
         *
         * By inheriting from MeshResourceLoader instead of AResourceLoader, the developer
         * needs to only worry about their specific readFile implementation.
         */
        class MeshResourceLoader : public Core::AResourceLoader
        {
        public:

            MeshResourceLoader(std::string const& extension);
            virtual ~MeshResourceLoader();

            virtual bool loadResource(Core::Resource* &resource, Core::File const& file) override;

        protected:

            /**
             * Each MeshResourceLoader must provide a custom implementation for it's specific file type.
             *
             * \param[in]  file     Source file to read from.
             * \param[out] vertices Texture pixel data read in from the file.
             * \param[out] indices  Width of the texture.
             *
             * \return TRUE if file was read in successfully.
             */
            virtual bool readFile(Core::File const& file, std::vector<Graphics::Vertex>& vertices, std::vector<uint32_t>& indices) = 0;

            /**
             * Creates the new Mesh resource from provided data.
             *
             * \param[out] resource The newly created resource.
             * \param[in]  file     Source file for the resource.
             * \param[in]  pixels   Pixel data for the texture arranged by rows.
             * \param[in]  width    Width of the texture.
             * \param[in]  height   Height of the texture.
             * \return TRUE if creation was successful.
             */
            virtual bool createResource(Core::Resource* &resource, Core::File const& file, std::vector<Graphics::Vertex> const& vertices, std::vector<uint32_t> const& indices);

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