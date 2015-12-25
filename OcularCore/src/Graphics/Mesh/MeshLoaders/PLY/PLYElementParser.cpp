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

#include "Graphics/Mesh/MeshLoaders/PLY/PLYElementParser.hpp"
#include "OcularEngine.hpp"

#include <exception>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        PLYElementParser::PLYElementParser()
            : PLYParser(),
              m_NumProperties(0)
        {

        }

        PLYElementParser::~PLYElementParser()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool PLYElementParser::parse(std::string const& line, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t& currVert, uint32_t& currIndex, bool isASCII)
        {
            /**
             * Each line represents a single element defined by a variable number of properties.
             * An example of a line that may be parsed is:
             *
             *     0.0 1.0 0.0
             *
             * Which was defined as:
             *
             *     element vertex 1
             *     property float x
             *     property float y
             *     property float z
             *
             * So it is the positional vector of a vertex with value (0.0, 1.0, 0.0).
             */

            bool result = true;

            if(type == PLYElementType::Vertex)
            {
                size_t currPos = 0;
                size_t nextPos = 0;

                uint32_t numParsed = 0;

                try
                {
                    for( ; numParsed < m_NumProperties; numParsed++, currPos += nextPos)
                    {
                        insertPropertyValue(numParsed, std::stof(&line[currPos], &nextPos), vertices[currVert]);
                    }
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", &line[currPos], "' to float with error:", e.what(), OCULAR_INTERNAL_LOG("PLYElementParser", "parse"));
                }
            }

            currVert++;

            return result;
        }

        void PLYElementParser::addProperty(PLYPropertyType const type) 
        {
            m_Properties.push_back(type);
            m_NumProperties++;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void PLYElementParser::insertPropertyValue(int propIndex, float propValue, Vertex& vertex)
        {
            // Indices will never be done as single properties

            switch(m_Properties[propIndex])
            {
            case PLYPropertyType::X:
                vertex.position.x = propValue;
                break;
                
            case PLYPropertyType::Y:
                vertex.position.y = propValue;
                break;
                
            case PLYPropertyType::Z:
                vertex.position.z = propValue;
                break;

            case PLYPropertyType::NormalX:
                vertex.normal.x = propValue;
                break;

            case PLYPropertyType::NormalY:
                vertex.normal.y = propValue;
                break;

            case PLYPropertyType::NormalZ:
                vertex.normal.z = propValue;
                break;

            default:
                break;
            }
        }

        bool PLYElementParser::isTrailingWhitespace(std::string const& string, uint32_t const& index) const
        {
            bool result = false;

            if(string[index] == ' ')
            {
                if(index == (string.size() - 1))
                {
                    result = true;
                }
                else
                {
                    result = isTrailingWhitespace(string, (index + 1));
                }
            }

            return result;
        }
    }
}