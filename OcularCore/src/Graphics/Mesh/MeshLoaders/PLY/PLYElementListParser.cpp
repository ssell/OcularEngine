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

#include "Graphics/Mesh/MeshLoaders/PLY/PLYElementListParser.hpp"
#include "OcularEngine.hpp"

#include <string>
#include <exception>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        PLYElementListParser::PLYElementListParser()
            : PLYParser()
        {
            memset(m_IndexBuffer, 0, sizeof(uint32_t) * 4);
        }

        PLYElementListParser::~PLYElementListParser()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool PLYElementListParser::parse(std::string const& line, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t& currVert, uint32_t& currIndex, bool isASCII)
        {
            bool result = true;

            if(type == PLYElementType::Face)
            {
                size_t currPos = 0;
                size_t nextPos = 0;

                uint32_t numIndices = 0;
                uint32_t numParsed = 0;

                try
                {
                    numIndices = std::stoul(line, &currPos);
                    
                    if(numIndices == 3)
                    {
                        for( ; numParsed < numIndices; numParsed++, currPos += nextPos)
                        {
                            m_IndexBuffer[numParsed] = std::stoul(&line[currPos], &nextPos);
                        }

                        addTriangleFace(indices, currIndex);
                    }
                    else if(numIndices == 4)
                    {
                        for( ; numParsed < numIndices; numParsed++, currPos += nextPos)
                        {
                            m_IndexBuffer[numParsed] = std::stoul(&line[currPos], &nextPos);
                        }

                        addQuadFace(indices, currIndex);
                    }
                    else
                    {
                        result = false;
                        OcularLogger->error("Invalid number of indices (", numIndices, "); Must be 3 or 4", OCULAR_INTERNAL_LOG("PLYElementListParser", "parse"));
                    }
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", &line[currPos], "' to ulong with error:", e.what(), OCULAR_INTERNAL_LOG("PLYElementListParser", "parse"));
                }
            }
            else
            {
                result = false;
                OcularLogger->error("Element list parsing is currently only available for Index data", OCULAR_INTERNAL_LOG("PLYElementListParser", "parse"));
            }

            return result;
        }
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void PLYElementListParser::addTriangleFace(std::vector<uint32_t>& indices, uint32_t& currIndex) const
        {
            indices[currIndex++] = m_IndexBuffer[0];
            indices[currIndex++] = m_IndexBuffer[1];
            indices[currIndex++] = m_IndexBuffer[2];
        }

        void PLYElementListParser::addQuadFace(std::vector<uint32_t>& indices, uint32_t& currIndex) const
        {
            // Turn a single quad face into two triangles

            indices[currIndex++] = m_IndexBuffer[0];
            indices[currIndex++] = m_IndexBuffer[1];
            indices[currIndex++] = m_IndexBuffer[2];
            indices[currIndex++] = m_IndexBuffer[2];
            indices[currIndex++] = m_IndexBuffer[3];
            indices[currIndex++] = m_IndexBuffer[0];
        }
    }
}