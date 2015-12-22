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
#ifndef __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER_PLY_ELEMENT_PARSER__H__
#define __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER_PLY_ELEMENT_PARSER__H__

#include "PLYParser.hpp"
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
         * \class PLYElementParser
         */
        class PLYElementParser : public PLYParser
        {
        public:

            PLYElementParser();
            virtual ~PLYElementParser();
            
            /**
             * \note Currently unsafe. May crash if more than expected number of token delimiters (' ') is encountered in the property line.
             */
            virtual bool parse(std::string const& line, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t& currVert, uint32_t& currIndex, bool isASCII = true) override;

            void addProperty(PLYPropertyType type);

        protected:

        private:
            
            void insertPropertyValue(int propIndex, float propValue, Vertex& vertex);

            std::vector<PLYPropertyType> m_Properties;
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