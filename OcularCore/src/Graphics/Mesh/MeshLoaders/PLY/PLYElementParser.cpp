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
#include <string>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        PLYElementParser::PLYElementParser()
            : PLYParser()
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
            // Parse the property line in a single pass for best performance

            bool result = true;
            uint32_t propIndex = 1;
            float value = std::stof(line);

            insertPropertyValue(0, value, vertices[currVert]);

            for(uint32_t i = 1; i < line.size(); i++)
            {
                if(line[i] == ' ')
                {
                    value = std::stof(&line[i]);
                    insertPropertyValue(propIndex, value, vertices[currVert]);
                    propIndex++;
                }
            }

            currVert++;

            return result;
        }

        void PLYElementParser::addProperty(PLYPropertyType const type) 
        {
            m_Properties.push_back(type);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void PLYElementParser::insertPropertyValue(int propIndex, float propValue, Vertex& vertex)
        {
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

            default:
                break;
            }
        }
    }
}