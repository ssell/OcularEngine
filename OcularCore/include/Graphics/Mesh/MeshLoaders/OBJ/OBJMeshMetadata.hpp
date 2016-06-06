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
#ifndef __H__OCULAR_GRAPHICS_OBJ_MESH_METADATA__H__
#define __H__OCULAR_GRAPHICS_OBJ_MESH_METADATA__H__

#include "Resources/ResourceMetadata.hpp"
#include <unordered_map>

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
         * \class OBJMeshMetadata
         *
         * Metadata used when importing entire OBJ files as SceneObjects.
         * Maintains a map of which Materials are paired with which Submeshes.
         */
        class OBJMeshMetadata : public ResourceMetadata
        {
        public:

            OBJMeshMetadata();
            virtual ~OBJMeshMetadata();

            void setSubmeshMaterialPair(uint32_t submeshIndex, std::string const& material);
            std::string getSubmeshMaterialPair(uint32_t submeshIndex) const;            

        protected:

        private:

            std::unordered_map<uint32_t, std::string> m_SubmeshMaterialPairs;
        };
    }
    /**
     * }@ End of Doxygen Group
     */
}
/**
 * }@ End of Doxygen Group
 */

//------------------------------------------------------------------------------------------

#endif
