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
                uint32_t numIndices = 0;

                try
                {
                    numIndices = std::stoul(line);
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to parse string '", line, "' to unsigned long with error: ", e.what(), OCULAR_INTERNAL_LOG("PLYElementListParser", "parse"));
                }

                if((result) && ((numIndices == 3) || (numIndices == 4)))
                {
                    uint32_t* indexBuffer = new uint32_t[numIndices];
                    memset(indexBuffer, 0, sizeof(uint32_t) * numIndices);

                    uint32_t indexIndex = 0;

                    for(uint32_t i = 1; (i < line.size()) && (result); i++)
                    {
                        if(line[i] == ' ')
                        {
                            uint32_t index = 0;

                            try
                            {
                                index = std::stoul(&line[i]);
                                indexBuffer[indexIndex] = index;
                                indexIndex++;
                            }
                            catch(std::invalid_argument const& e)
                            {
                                result = false;
                                OcularLogger->error("Failed to parse string '", line, "' to unsigned long with error: ", e.what(), OCULAR_INTERNAL_LOG("PLYElementListParser", "parse"));
                            }


                            if(indexIndex >= numIndices)
                            {
                                break;
                            }
                        }
                    }

                    if(indexIndex == numIndices)
                    {
                        if(numIndices == 3)
                        {
                            addTriangleFace(indexBuffer, indices, currIndex);
                        }
                        else
                        {
                            addQuadFace(indexBuffer, indices, currIndex);
                        }
                    }
                    else
                    {
                        result = false;
                        OcularLogger->error("Failed to fully parse line '", line, "' as it ended when more tokens were expected", OCULAR_INTERNAL_LOG("PLYElementListParser", "parse"));
                    }

                    delete[] indexBuffer;
                    indexBuffer = nullptr;
                }
                else
                {
                    result = false;
                    OcularLogger->error("Unsupported number of indices for face. Only triangle (3) and quad (4) faces are currently supported", OCULAR_INTERNAL_LOG("PLYElementListParser", "parse"));
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

        void PLYElementListParser::addTriangleFace(uint32_t const* newIndices, std::vector<uint32_t>& indices, uint32_t& currIndex) const
        {
            indices[currIndex++] = newIndices[0];
            indices[currIndex++] = newIndices[1];
            indices[currIndex++] = newIndices[2];
        }

        void PLYElementListParser::addQuadFace(uint32_t const* newIndices, std::vector<uint32_t>& indices, uint32_t& currIndex) const
        {
            // Turn a single quad face into two triangles

            indices[currIndex++] = newIndices[0];
            indices[currIndex++] = newIndices[1];
            indices[currIndex++] = newIndices[2];
            indices[currIndex++] = newIndices[2];
            indices[currIndex++] = newIndices[3];
            indices[currIndex++] = newIndices[0];
        }
    }
}