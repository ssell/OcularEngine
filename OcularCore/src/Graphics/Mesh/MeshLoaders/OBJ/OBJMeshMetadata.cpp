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

#include "Graphics/Mesh/MeshLoaders/OBJ/OBJMeshMetadata.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        OBJMeshMetadata::OBJMeshMetadata()
            : Core::ResourceMetadata("OBJMeshMetadata")
        {

        }

        OBJMeshMetadata::~OBJMeshMetadata()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void OBJMeshMetadata::setSubmeshMaterialPair(uint32_t const submeshIndex, std::string const& material)
        {
            m_SubmeshMaterialPairs[submeshIndex] = material;
        }

        std::string OBJMeshMetadata::getSubmeshMaterialPair(uint32_t const submeshIndex) const
        {   
            std::string result;
            auto find = m_SubmeshMaterialPairs.find(submeshIndex);

            if(find != m_SubmeshMaterialPairs.end())
            {
                result = (*find).second;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}
