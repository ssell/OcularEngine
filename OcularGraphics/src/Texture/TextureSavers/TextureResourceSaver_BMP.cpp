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

#define FLOAT_TO_UCHAR(x) static_cast<unsigned char>(x * 0.00392156862f)

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

            unsigned char BMPHeader[14] = { };
            unsigned char DIBHeader[40] = { };

            memset(BMPHeader, 0x00, 14);
            memset(DIBHeader, 0x00, 40);
            
            //----------------------------------------
            // Fill the temp buffers with all mandatory data

            long dataSize = (width * height * 4);    // width * height * bpp
            long fileSize = dataSize + 54;           // size of pixel array + headers
            long startPos = 54;                      // pixel array begins immediately after the headers

            BMPHeader[0] = 0x42;  // 'B'
            BMPHeader[1] = 0x4D;  // 'M'

            memcpy(&BMPHeader[2],  &fileSize, sizeof(long));
            memcpy(&BMPHeader[10], &startPos, sizeof(long));
            memcpy(&DIBHeader[4],  &width,    sizeof(long));
            memcpy(&DIBHeader[8],  &height,   sizeof(long));
            memcpy(&DIBHeader[20], &dataSize, sizeof(long));

            //----------------------------------------
            // Write buffers to file

            outStream.write(reinterpret_cast<char*>(BMPHeader), 14);
            outStream.write(reinterpret_cast<char*>(DIBHeader), 40);

            result = true;
            return result;
        }

        bool TextureResourceSaver_BMP::writePixelArray(std::ofstream& outStream, std::vector<Color> const& pixels, unsigned width, unsigned height)
        {
            bool result = false;

            std::vector<unsigned char> pixelData;
            pixelData.reserve(width * height * 4);
            
            unsigned pos = 0;

            for(auto pixelIter = pixels.begin(); pixelIter != pixels.end(); pixelIter++)
            {
                // BMP stores pixel data in BGR/A format
                pixelData[pos++] = FLOAT_TO_UCHAR(pixelIter->b);
                pixelData[pos++] = FLOAT_TO_UCHAR(pixelIter->g);
                pixelData[pos++] = FLOAT_TO_UCHAR(pixelIter->r);
                pixelData[pos++] = FLOAT_TO_UCHAR(pixelIter->a);
            }

            outStream.write(reinterpret_cast<char*>(&pixelData[0]), pixelData.size());

            result = true;
            return result;
        }

    }
}