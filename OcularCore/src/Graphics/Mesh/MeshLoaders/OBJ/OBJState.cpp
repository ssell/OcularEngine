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

#include "Graphics/Mesh/MeshLoaders/OBJ/OBJState.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        OBJState::OBJState()
        {

        }

        OBJState::~OBJState()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void OBJState::clearState()
        {

        }

        void OBJState::addVertexPosition(float const x, float const y, float const z)
        {
            m_PositionData.push_back(Math::Vector3f(x, y, z));
        }

        void OBJState::addVertexNormals(float const x, float const y, float const z)
        {
            m_NormalsData.push_back(Math::Vector3f(x, y, z));
        }

        void OBJState::addVertexTexCoord(float const u, float const v)
        {
            m_TexCoordData.push_back(Math::Vector2f(u, v));
        }

        void OBJState::addIndices(int32_t position, int32_t normal, int32_t texcoord)
        {
            OBJIndex index;

            // Indices may be negative. If so, they index from the current end of the data list.
            // An index of -1 is the last element in the data list, -2 is the second-to-last, etc.

            if(position < 0)
            {
                position += static_cast<int32_t>(m_PositionData.size());
            }
            
            if(normal < 0)
            {
                normal += static_cast<int32_t>(m_NormalsData.size());
            }
            
            if(texcoord < 0)
            {
                texcoord += static_cast<int32_t>(m_TexCoordData.size());
            }

            // Incoming OBJ indices are 1-based and we maintain that until it is time to build the vertex buffers

            index.positionIndex = position;
            index.normalIndex = normal;
            index.textureIndex = texcoord;

            // Loop is not optimal, but an OBJ model will typically have no more than a handful of meshes/groups

            for(auto iter = m_Meshes.begin(); iter != m_Meshes.end(); ++iter)
            {
                if((*iter).active)
                {
                    (*iter).indices.push_back(index);
                }
            }
        }

        std::vector<Math::Vector3f> const& OBJState::getVertexPositions() const
        {
            return m_PositionData;
        }

        std::vector<Math::Vector3f> const& OBJState::getVertexNormals() const
        {
            return m_NormalsData;
        }

        std::vector<Math::Vector2f> const& OBJState::getVertexTexCoords() const
        {
            return m_TexCoordData;
        }

        void OBJState::setCurrentGroups(std::initializer_list<std::string> const& names)
        {
            // !! Rework so that any new names are added as new meshes

            for(auto iter = m_Meshes.begin(); iter != m_Meshes.end(); ++iter)
            {
                (*iter).active = false;

                for(auto name : names)
                {
                    if(name.compare((*iter).name) == 0)
                    {
                        (*iter).active = true;
                        break;
                    }
                }
            }
        }
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}