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
#ifndef __H__OCULAR_GRAPHICS_MESH_OBJ_STATE__H__
#define __H__OCULAR_GRAPHICS_MESH_OBJ_STATE__H__

#include "Math/Vector3.hpp"

#include <string>
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
        struct OBJIndex
        {
            uint32_t positionIndex;
            uint32_t normalIndex;
            uint32_t textureIndex;
        };

        struct OBJMesh
        {
            std::string name;
            std::vector<OBJIndex> indices;

            bool active;
        };

        /**
         * \class OBJState
         */
        class OBJState
        {
        public:

            OBJState();
            ~OBJState();

            void clearState();

            void addVertexPosition(float x, float y, float z);
            void addVertexNormals(float x, float y, float z);
            void addVertexTexCoord(float u, float v);

            void addIndices(int32_t position = 0, int32_t normal = 0, int32_t texcoord = 0);

            std::vector<Math::Vector3f> const& getVertexPositions() const;
            std::vector<Math::Vector3f> const& getVertexNormals() const;
            std::vector<Math::Vector2f> const& getVertexTexCoords() const;

            void setCurrentGroups(std::initializer_list<std::string> const& names);

        protected:

        private:

            std::vector<Math::Vector3f> m_PositionData;
            std::vector<Math::Vector3f> m_NormalsData;
            std::vector<Math::Vector2f> m_TexCoordData;

            std::vector<OBJMesh> m_Meshes;
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