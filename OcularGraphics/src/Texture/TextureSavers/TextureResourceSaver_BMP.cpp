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

#include "Texture/TextureSavers/TextureResourceSaver_BMP.hpp"
#include "Resources/ResourceSaverRegistrar.hpp"

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

        bool TextureResourceSaver_BMP::saveFile(Core::File const& file, std::vector<Color> const& pixels, unsigned const width, unsigned const height)
        {
            bool result = false;

            std::ofstream outStream(file.getFullPath(), std::ios_base::binary | std::ios_base::out);

            if(outStream.is_open())
            {
                if(writeHeaders(outStream, width, height))
                {
                    if(writePixelArray(outStream, pixels, width, height))
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Failed to write pixel information to '", file.getFullPath(), "' for resource saving", OCULAR_INTERNAL_LOG("TextureResourceSaver_BMP", "saveFile"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to write header information to '", file.getFullPath(), "' for resource saving", OCULAR_INTERNAL_LOG("TextureResourceSaver_BMP", "saveFile"));
                }

                outStream.close();
            }
            else
            {
                OcularLogger->error("Failed to open file '", file.getFullPath(), "' for resource saving", OCULAR_INTERNAL_LOG("TextureResourceSaver_BMP", "saveFile"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceSaver_BMP::writeHeaders(std::ofstream& outStream, long const width, long const height)
        {
            bool result = false;

            //----------------------------------------
            // Create empty temp buffers

            unsigned char headerBuffer[54] = { };

            memset(headerBuffer, 0x00, 54);
            
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

            headerBuffer[0] = 0x42;  // 'B'
            headerBuffer[1] = 0x4D;  // 'M'

            memcpy(&headerBuffer[2],  &fileSize,     sizeof(long));
            memcpy(&headerBuffer[10], &startPos,     sizeof(long));
            memcpy(&headerBuffer[14], &dibSize,      sizeof(long));
            memcpy(&headerBuffer[18], &width,        sizeof(long));
            memcpy(&headerBuffer[22], &height,       sizeof(long));
            memcpy(&headerBuffer[26], &colorPlanes,  sizeof(short));
            memcpy(&headerBuffer[28], &bitsPerPixel, sizeof(short));
            memcpy(&headerBuffer[34], &dataSize,     sizeof(long));
            memcpy(&headerBuffer[38], &resolutionX,  sizeof(long));
            memcpy(&headerBuffer[42], &resolutionY,  sizeof(long));

            //----------------------------------------
            // Write buffers to file

            outStream.write(reinterpret_cast<char*>(headerBuffer), 54);

            result = true;
            return result;
        }

        bool TextureResourceSaver_BMP::writePixelArray(std::ofstream& outStream, std::vector<Color> const& pixels, unsigned width, unsigned height)
        {
            bool result = false;

            std::vector<unsigned char> pixelData;
            pixelData.reserve(width * height * 4);
            
            for(auto pixelIter = pixels.begin(); pixelIter != pixels.end(); pixelIter++)
            {
                // BMP stores pixel data in BGR/A format
                pixelData.push_back(FLOAT_TO_UCHAR(pixelIter->b));
                pixelData.push_back(FLOAT_TO_UCHAR(pixelIter->g));
                pixelData.push_back(FLOAT_TO_UCHAR(pixelIter->r));
                pixelData.push_back(FLOAT_TO_UCHAR(pixelIter->a));
            }

            outStream.write(reinterpret_cast<char*>(&pixelData[0]), pixelData.size());

            result = true;
            return result;
        }

    }
}