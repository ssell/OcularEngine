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

#include "OcularEngine.hpp"
#include "Utilities/StringOps.hpp"
#include "Texture/TextureLoaders/TextureResourceLoader_PNG.hpp"
#include "Resources/ResourceLoaderRegistrar.hpp"

#include <string>
#include <fstream>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::TextureResourceLoader_PNG)

//------------------------------------------------------------------------------------------

struct PNGChunk
{
    unsigned length;     // Length of the chunk in bytes
    unsigned dataStart;  // Absolute position (in bytes) of where this chunk's data begins in the file
    unsigned checksum;   // Cyclic redundancy code/checksum

    std::string name;    // Name of the chunk. This is used in multiple ways 
};

void getAllChunks(std::vector<unsigned char> const& dataBuffer, std::vector<PNGChunk>& chunks);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceLoader_PNG::TextureResourceLoader_PNG()
            : TextureResourceLoader(".png")
        {
        
        }

        TextureResourceLoader_PNG::~TextureResourceLoader_PNG()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceLoader_PNG::readFile(Core::File const& file, std::vector<Color>& pixels, unsigned& width, unsigned& height)
        {
            bool result = false;

            std::vector<unsigned char> buffer;
            loadFileIntoBuffer(file, buffer, Endianness::Big);

            if(buffer.size() > 0)
            {
                std::vector<PNGChunk> fileChunks;
                getAllChunks(buffer, fileChunks);

                if(fileChunks.size() > 0)
                {
                
                }
                else
                {
                    OcularLogger->error("Chunk list is empty", OCULAR_INTERNAL_LOG("TextureResourceLoader_PNG", "readFile"));
                }
            }
            else
            {
                OcularLogger->error("File buffer is empty", OCULAR_INTERNAL_LOG("TextureResourceLoader_PNG", "readFile"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

//------------------------------------------------------------------------------------------
// NON-MEMBER FUNCTIONS
//------------------------------------------------------------------------------------------

void getAllChunks(std::vector<unsigned char> const& dataBuffer, std::vector<PNGChunk>& chunks)
{
    // Explores the file data buffer and populates a list of all chunks contained within it.
    // This chunk listing will later be used to populate the pixel array, etc.

    unsigned dataPos = 8;   // First chunk begins after the 8-byte header signature

    while((dataPos + 4) < dataBuffer.size())
    {
        PNGChunk newChunk;

        newChunk.length    = *(unsigned*)(&dataBuffer[dataPos]);

        if((dataPos + newChunk.length + 12) < dataBuffer.size())       // Make sure there is enough space remaining in the buffer for another chunk
        {
            char tempName[4] = {static_cast<char>(dataBuffer[dataPos + 4]),
                                static_cast<char>(dataBuffer[dataPos + 5]),
                                static_cast<char>(dataBuffer[dataPos + 6]),
                                static_cast<char>(dataBuffer[dataPos + 7])};

            newChunk.name      = tempName;
            newChunk.dataStart = dataPos + 8;                          // Chunk data always begins 8 bytes after the length index
            newChunk.checksum  = *(unsigned*)(&dataBuffer[dataPos + 8 + newChunk.length]);

            dataPos += newChunk.length + 12;     // length (4) + type (4) + data (newChunk.length) + CRC (4)
            chunks.push_back(newChunk);

            if(Ocular::Utils::StringOps::isEqual(newChunk.name, "IEND"))
            {
                // End of the file
                break;
            }
        }
        else
        {
            break;
        }
    }
}