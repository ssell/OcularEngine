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
#ifndef __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER_PLY_PARSER__H__
#define __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER_PLY_PARSER__H__

#include "Graphics/Mesh/Vertex.hpp"
#include "PLYEnums.hpp"

#include <cstdint>
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
         * \class PLYParser
         */
        class PLYParser
        {
        public:

            PLYParser();
            ~PLYParser();

            /**
             * Parses a single line of a PLY file.
             *
             * \param[in]  line      The currently line of the PLY file to parse
             * \param[out] vertices  Vector of mesh vertices
             * \param[out] indices   Vector of mesh indices
             * \param[out] currVert  The current vertices index. If one or more indices were added in this parse, increment this accordingly.
             * \param[out] currIndex The current indices index. If one or more indices were added in this parse, increment this accordingly.
             *
             * \return TRUE if the line was parsed without any errors.
             */
            virtual bool parse(std::string const& line, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t& currVert, uint32_t& currIndex, Math::Vector3f& min, Math::Vector3f& max, bool isASCII = true) = 0;

            //------------------------------------------------------------

            PLYElementType type;
            uint32_t count;

        protected:

            bool splitProperty(std::string const& line, uint32_t tokenCount, uint32_t* tokens);

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