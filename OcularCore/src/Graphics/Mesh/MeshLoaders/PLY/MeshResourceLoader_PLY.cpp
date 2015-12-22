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

#include "Graphics/Mesh/MeshLoaders/PLY/MeshResourceLoader_PLY.hpp"
#include "Graphics/Mesh/MeshLoaders/PLY/PLYElementParser.hpp"
#include "Graphics/Mesh/MeshLoaders/PLY/PLYElementListParser.hpp"

#include "Resources/ResourceLoaderRegistrar.hpp"
#include "OcularEngine.hpp"

#include <fstream>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::MeshResourceLoader_PLY)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MeshResourceLoader_PLY::MeshResourceLoader_PLY()
            : MeshResourceLoader(".ply")
        {

        }

        MeshResourceLoader_PLY::~MeshResourceLoader_PLY()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool MeshResourceLoader_PLY::readFile(Core::File const& file, std::vector<Graphics::Vertex>& vertices, std::vector<uint32_t>& indices)
        {
            bool result = false;

            std::ifstream stream(file.getFullPath(), std::ios::in);

            if(stream.is_open())
            {
                if(parseHeader(stream))
                {
                    if(parseBody(stream, vertices, indices))
                    {
                        result = true;
                    }
                    else
                    {

                    }
                }
                else
                {

                }

                stream.close();
            }

            return result;
        }

        bool MeshResourceLoader_PLY::parseHeader(std::ifstream& stream)
        {
            /**
             * Header is split into the following pieces:
             *
             *     - Identifier
             *     - Element definition
             *     - End of header
             *
             * In addition to this, any line of the file (including the header), may be
             * a comment. A comment is any line that begins with 'comment'. Example:
             *
             *     comment This line is a comment
             *
             * The identifier informs us that this is a PLY file and what type of PLY file.
             * A file is marked as a PLY by having it's very first line be equal to 'ply'.
             * The next line will then tell which of the following kinds of PLY files it is:
             *
             *     ASCII
             *     Binary (little endian)
             *     Binary (big endian)
             *
             * So an identifier will look like:
             *
             *     ply
             *     format ascii 1.0
             *
             * or
             *
             *     ply
             *     format binary_little_endian 1.0
             *
             * etc.
             *
             * The rest of the header is dedicated to defining the elements that make 
             * up the body of the PLY header. This can occur in one of two different ways.
             * Either an element definition followed by a variable number of property 
             * definitions, or an element definition followed by a single property list.
             *
             * The element definition also tells us what kind of element it is, and how
             * many individual elements there are. Example:
             *
             *     element vertex 8
             *     property float x
             *     property float y
             *     property float z
             *     element face 6
             *     property list uchar int vertex_index
             *
             * The above tells us there will be 8 vertex elements, each defined as (x, y, z).
             * It will then be followed by 6 face elements, defined as a variable number
             * of integer indices.
             *
             * Finally, the end of the header is marked by 'end_header'. All together,
             * a header may resemble:
             *
             *     ply
             *     format ascii 1.0
             *     example A sample header
             *     element vertex 8
             *     property float x
             *     property float y
             *     property float z
             *     element face 6
             *     property list uchar int vertex_index
             *     end_header
             *
             * It should be noted there are no limits to the number of elements or their
             * properties. There is also no standard set of element types. But the following
             * are generally accepted:
             *
             *     vertex
             *     face
             *     edge
             *
             * Of which, we currently support vertex and face. Any unsupported or unknown 
             * element types will simply be skipped over while parsing the body.
             *
             * See below for more information:
             * http://paulbourke.net/dataformats/ply/
             */
            bool result = true;

            if(isValidPLYFile(stream))
            {
                std::string line;

                PLYParser* currentParser = nullptr;

                while((std::getline(stream, line)) && (line.compare("end_header") != 0))
                {      
                    if(!isComment(line))
                    {
                        if(isElement(line))
                        {
                            // An element definition line
                            parseElement(stream, line, currentParser);
                        }
                        else
                        {
                            // An individual property definition
                            if(isElementList(line))
                            {
                                parsePropertyList(line, dynamic_cast<PLYElementListParser*>(currentParser));
                            }
                            else
                            {
                                parseProperty(line, dynamic_cast<PLYElementParser*>(currentParser));
                            }
                        }
                    }
                }

                m_Parsers.push_back(currentParser);
            }
            else
            {
                result = false;
                OcularLogger->error("File is not a valid PLY", OCULAR_INTERNAL_LOG("MeshResourceLoader_PLY", "parseHeader"));
            }

            return result;
        }

        bool MeshResourceLoader_PLY::parseElement(std::ifstream& stream, std::string& line, PLYParser* parser)
        {
            bool result = true;

            // We want both the actual element definition line and also 
            // the first property of the element. That way we can see
            // if this is a normal element, or an element list.

            const std::string elementDefinition = line;
                            
            if((std::getline(stream, line)) && (line.compare("end_header") != 0))
            {
                if(parser)
                {
                    // This is not the first element. Store the last one in our list
                    m_Parsers.push_back(parser);
                }

                // Now to determine if we need to create a PLYElementParser or a PLYElementListParser
                // If the first property begins with 'property list', then it will an PLYElementListParser.
                
                if(isElementList(line))
                {
                    parser = new PLYElementListParser();
                    parsePropertyList(line, dynamic_cast<PLYElementListParser*>(parser));
                }
                else
                {
                    parser = new PLYElementParser();
                    parseProperty(line, dynamic_cast<PLYElementParser*>(parser));
                }
                
                result = parseElementNameAndCount(elementDefinition, parser);
            }
            else
            {
                result = false;
                OcularLogger->error("Unexpected end of file preceding line '", elementDefinition, "'", OCULAR_INTERNAL_LOG("MeshResourceLoader_PLY", "parseHeader"));
            }

            return result;
        }

        bool MeshResourceLoader_PLY::parseElementNameAndCount(std::string const& line, PLYParser* parser) const
        {
            bool result = true;

            return result;
        }

        bool MeshResourceLoader_PLY::parseProperty(std::string const& line, PLYElementParser* parser) const
        {
            bool result = true;

            return result;
        }

        bool MeshResourceLoader_PLY::parsePropertyList(std::string const& line, PLYElementListParser* parser) const
        {
            bool result = true;

            return result;
        }

        bool MeshResourceLoader_PLY::parseBody(std::ifstream& stream, std::vector<Graphics::Vertex>& vertices, std::vector<uint32_t>& indices)
        {
            bool result = true;

            std::list<PLYParser*>::iterator iter = m_Parsers.begin();
            std::string line; 

            uint32_t currVertex       = 0;
            uint32_t currIndex        = 0;
            uint32_t currElementCount = 0;

            while((std::getline(stream, line) && (iter != m_Parsers.end())))
            { 
                if(!isComment(line))
                {
                    if(!(*iter)->parse(line, vertices, indices, currVertex, currIndex))
                    {
                        result = false;
                        OcularLogger->error("Failed to parse line '", line, "'", OCULAR_INTERNAL_LOG("MeshResourceLoader_PLY", "parseBody"));
                    }

                    currElementCount++;

                    if(currElementCount >= (*iter)->count)
                    {
                        iter++;
                    }
                }
            }

            return result;
        }

        bool MeshResourceLoader_PLY::isValidPLYFile(std::ifstream& stream) const
        {
            bool result = false;

            std::string line;
            std::getline(stream, line);

            if(line.compare("ply") == 0)
            {

            }
            else
            {
                OcularLogger->error("The first line of a PLY file must be 'ply'", OCULAR_INTERNAL_LOG("MeshResourceLoader_PLY", "isValidPLYFile"));
            }

            return result;
        }

        bool MeshResourceLoader_PLY::isComment(std::string const& line) const
        {
            bool result = false;

            if(line.size() >= 7)
            {
                if((line[0] == 'c') && (line[1] == 'o') && (line[2] == 'm') && (line[3] == 'm') && (line[4] == 'e') && (line[5] == 'n') && (line[6] == 't'))
                {
                    result = true;
                }
            }

            return result;
        }

        bool MeshResourceLoader_PLY::isElement(std::string const& line) const
        {
            bool result = false;

            if(line.size() >= 7)
            {
                if((line[0] == 'e') && (line[1] == 'l') && (line[2] == 'e') && (line[3] == 'm') && (line[4] == 'e') && (line[5] == 'n') && (line[6] == 't'))
                {
                    result = true;
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}