/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Graphics/Texture/TextureSavers/TextureResourceSaver_BMP.hpp"
#include "Resources/ResourceSaverRegistrar.hpp"
#include <algorithm>

#define FLOAT_TO_UCHAR(x) static_cast<unsigned char>(x * 255.0f)

OCULAR_REGISTER_RESOURCE_SAVER(Ocular::Graphics::TextureResourceSaver_BMP)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceSaver_BMP::TextureResourceSaver_BMP()
            : TextureResourceSaver(".bmp")
        {
        
        }

        TextureResourceSaver_BMP::~TextureResourceSaver_BMP()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceSaver_BMP::saveFile(Core::File const& file, std::vector<Core::Color> const& pixels, unsigned const width, unsigned const height)
        {
            bool result = false;

            std::vector<unsigned char> fileBuffer((54 + (width * height * 4)), static_cast<unsigned char>(0));  // 54 bytes exactly for header; Then rest for the pixel array
          
            if(writeHeaders(fileBuffer, width, height))
            {
                if(writePixelArray(fileBuffer, pixels, width, height))
                {
                    // BMP files should be written using Little Endian ordering
                    if(writeFile(file, fileBuffer, Endianness::Little))
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Failed to write file buffer to disk", OCULAR_INTERNAL_LOG("TextureResourceSaver_BMP", "saveFile"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to write pixel array to file buffer", OCULAR_INTERNAL_LOG("TextureResourceSaver_BMP", "saveFile"));
                }
            }
            else
            {
                OcularLogger->error("Failed to write headers to file buffer", OCULAR_INTERNAL_LOG("TextureResourceSaver_BMP", "saveFile"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceSaver_BMP::writeHeaders(std::vector<unsigned char>& fileBuffer, long const width, long const height)
        {
            bool result = false;

            //----------------------------------------
            // Fill the temp buffers with all mandatory data

            long  dataSize     = (width * height * 4);    // width * height * bpp
            long  fileSize     = dataSize + 54;           // size of pixel array + headers
            long  dibSize      = 40;                      // size of the DIB Header
            long  startPos     = 54;                      // pixel array begins immediately after the headers
            short colorPlanes  = 1;
            short bitsPerPixel = 32;
            long  resolutionX  = 2835;
            long  resolutionY  = 2835;

            fileBuffer[0] = 0x42;  // 'B'
            fileBuffer[1] = 0x4D;  // 'M'

            memcpy(&fileBuffer[2],  &fileSize,     sizeof(long));
            memcpy(&fileBuffer[10], &startPos,     sizeof(long));
            memcpy(&fileBuffer[14], &dibSize,      sizeof(long));
            memcpy(&fileBuffer[18], &width,        sizeof(long));
            memcpy(&fileBuffer[22], &height,       sizeof(long));
            memcpy(&fileBuffer[26], &colorPlanes,  sizeof(short));
            memcpy(&fileBuffer[28], &bitsPerPixel, sizeof(short));
            memcpy(&fileBuffer[34], &dataSize,     sizeof(long));
            memcpy(&fileBuffer[38], &resolutionX,  sizeof(long));
            memcpy(&fileBuffer[42], &resolutionY,  sizeof(long));

            return true;
        }

        bool TextureResourceSaver_BMP::writePixelArray(std::vector<unsigned char>& fileBuffer, std::vector<Core::Color> const& pixels, unsigned width, unsigned height)
        {
            bool result = false;
            int filePos = 54;    // Header is always 54 bytes long and we will always be starting the pixel array immediately after it

            for(auto pixelIter = pixels.begin(); pixelIter != pixels.end(); ++pixelIter)
            {
                // BMP stores pixel data in BGR/A format
                fileBuffer[filePos++] = FLOAT_TO_UCHAR(pixelIter->b);
                fileBuffer[filePos++] = FLOAT_TO_UCHAR(pixelIter->g);
                fileBuffer[filePos++] = FLOAT_TO_UCHAR(pixelIter->r);
                fileBuffer[filePos++] = FLOAT_TO_UCHAR(pixelIter->a);
            }

            result = true;
            return result;
        }

    }
}