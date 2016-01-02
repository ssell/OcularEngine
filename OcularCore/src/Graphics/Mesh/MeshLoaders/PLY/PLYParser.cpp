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

#include "Graphics/Mesh/MeshLoaders/PLY/PLYParser.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        PLYParser::PLYParser()
            : type(PLYElementType::Unknown), count(0)
        {

        }

        PLYParser::~PLYParser()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool PLYParser::splitProperty(std::string const& line, uint32_t tokenCount, uint32_t* tokens)
        {
            /**
             * A very specialized string splitter used to tokenize property lines.
             * Given the nature of the PLY format, the following assumptions can be madeL
             *
             *     - The delimiter is always a space (' ')
             *     - We already know how many tokens to expect
             *
             * We also don't care about placing the tokens into individual strings or buffers.
             * Instead we can employ just their index, so there is no need to copy string data around.
             */

            bool result = true;
            uint32_t currToken = 0;

            tokens[currToken] = 0;

            for(uint32_t i = 1; i < line.size(); i++)
            {
                if(line[i] == ' ')
                {
                    tokens[currToken] = i;
                    currToken++;

                    if(currToken >= tokenCount)
                    {
                        result = false;
                        break;
                    }
                }
            }

            return result;
        }
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}