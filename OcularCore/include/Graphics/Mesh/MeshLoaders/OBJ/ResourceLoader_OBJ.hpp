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
#ifndef __H__OCULAR_GRAPHICS_RESOURCE_LOADER_OBJ__H__
#define __H__OCULAR_GRAPHICS_RESOURCE_LOADER_OBJ__H__

#include "Resources/ResourceLoader.hpp"
#include "Graphics/Mesh/Vertex.hpp"

#include <vector>

//------------------------------------------------------------------------------------------

class OBJState;
class OBJGroup;
struct OBJFace;
struct OBJVertexGroup;

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
        class Mesh;

        /**
         * \class ResourceLoader_OBJ
         *
         * ResourceLoader implementation for the Wavefront OBJ geometric data file format.
         * 
         * The OBJ file format can describe multiple individual meshes, and so this ResourceLoader
         * creates and returns a MultiResource instance. In addition to the MultiResource, it also
         * loads in each individual mesh as a Mesh resource.
         *
         * See the OBJImporter class for information on how to use an OBJ file in the Ocular Engne.
         */
        class ResourceLoader_OBJ : public Core::AResourceLoader
        {
        public:

            ResourceLoader_OBJ();
            virtual ~ResourceLoader_OBJ();

            virtual bool loadResource(Core::Resource* &resource, Core::File const& file) override;

            /**
             * Loads a specific OBJ group as an individual Mesh resource.
             * 
             * It should be noted that loading an individual group requires the full parsing of the OBJ file.
             * If the file contains multiple groups, then loadResource or OBJImporter may be more efficient.
             */
            virtual bool loadSubResource(Core::Resource* &resource, Core::File const& file, std::string const& mappingName) override;
            virtual bool exploreResource(Core::File const& file) override;

        protected:

            bool isFileValid(Core::File const& file) const;

            void createMesh(Mesh* mesh, OBJGroup const* group);
            void addFace(OBJFace const* face, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, Math::Vector3f& min, Math::Vector3f& max);
            void faceToVertex(std::vector<Vertex>& vertices, OBJVertexGroup const& group, Math::Vector3f& min, Math::Vector3f& max);

            std::string buildParentMapping(std::string const& mapping) const;

        private:

            uint32_t m_CurrVertexIndex;
            uint32_t m_CurrIndexIndex;

            OBJState* m_CurrState;
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