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
#ifndef __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER_PLY__H__
#define __H__OCULAR_GRAPHICS_MESH_RESOURCE_LOADER_PLY__H__

#include "Graphics/Mesh/MeshLoaders/MeshResourceLoader.hpp"
#include "PLYEnums.hpp"

#include <list>
#include <fstream>

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
        class PLYParser;
        class PLYElementParser;
        class PLYElementListParser;

        /**
         * \class MeshResourceLoader_PLY
         *
         * Implementation of AResourceLoader that handles the loading of
         * files with the '.ply' extension as meshes.
         */
        class MeshResourceLoader_PLY : public MeshResourceLoader
        {
        public:

            MeshResourceLoader_PLY();
            virtual ~MeshResourceLoader_PLY();

        protected:

            virtual bool readFile(Core::File const& file, std::vector<Graphics::Vertex>& vertices, std::vector<uint32_t>& indices) override;

            bool parseHeader(std::ifstream& stream);
            bool parseElement(std::ifstream& stream, std::string& line, PLYParser* parser);
            bool parseElementNameAndCount(std::string const& line, PLYParser* parser) const;
            bool parseProperty(std::string const& line, PLYElementParser* parser) const;
            bool parsePropertyList(std::string const& line, PLYElementListParser* parser) const;

            bool parseBody(std::ifstream& stream, std::vector<Graphics::Vertex>& vertices, std::vector<uint32_t>& indices);

            bool isValidPLYFile(std::ifstream& stream) const;
            bool isComment(std::string const& line) const;
            bool isElement(std::string const& line) const;
            bool isElementList(std::string const& line) const;
            bool isFormatASCII(std::string const& line) const;

            PLYPropertyType toPropertyType(std::string const& str) const;
            PLYElementType toElementType(std::string const& str) const;

        private:

            std::list<PLYParser*> m_Parsers;
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