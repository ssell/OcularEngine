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

#include "Texture/TextureLoaders/TextureResourceLoader_BMP.hpp"
#include "Resources/ResourceLoaderRegistrar.hpp"
#include "OcularEngine.hpp"

#include <fstream>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::TextureResourceLoader_BMP)

//------------------------------------------------------------------------------------------

struct BMPHeader
{
    unsigned short headerField;
    unsigned short bpp;

    unsigned fileSize;
    unsigned startOffset;
    unsigned compression;

    int width;
    int height;
};

bool isHeaderValid(BMPHeader const& header);
bool readHeader(std::vector<unsigned char> const& buffer, BMPHeader& header);
bool createPixelDataUncompressed(BMPHeader& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels);
bool createPixelDataCompressed(BMPHeader& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceLoader_BMP::TextureResourceLoader_BMP()
            : TextureResourceLoader(".bmp")
        {

        }

        TextureResourceLoader_BMP::~TextureResourceLoader_BMP()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceLoader_BMP::readFile(Core::File const& file, std::vector<Color>& pixels, unsigned& width, unsigned& height)
        {
            bool result = false;

            std::vector<unsigned char> buffer;
            loadFileIntoBuffer(file, buffer);

            if(buffer.size() > 0)
            {
                BMPHeader header;

                if(readHeader(buffer, header))
                {
                    width  = header.width;
                    height = std::abs(header.height);  // Height reported by header may be negative if data is stored in reverse order
                     
                    if(header.compression == 0)
                    {
                        result = createPixelDataUncompressed(header, buffer, pixels);
                    }
                    else
                    {
                        result = createPixelDataCompressed(header, buffer, pixels);
                    }
                    
                    if(!result)
                    {
                        OcularLogger->error("Failed to create pixel data", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "readFile"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to read file header", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "readFile"));
                }
            }
            else
            {
                OcularLogger->error("File buffer is empty", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "readFile"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

//------------------------------------------------------------------------------------------

bool isHeaderValid(BMPHeader const& header)
{
    bool result = true;

    if((header.width <= 0) || (header.height == 0))  // Height can potentially be negative and still valid
    {
        OcularLogger->error("Invalid image dimensions", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "isHeaderValid"));
        result = false;
    }

    if((header.bpp != 24) && (header.bpp != 32))
    {
        OcularLogger->error("Invalid image pixel depth", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "isHeaderValid"));
    }

    return result;
}

bool readHeader(std::vector<unsigned char> const& buffer, BMPHeader& header)
{
    // http://en.wikipedia.org/wiki/BMP_file_format#Bitmap_file_header

    bool result = false;

    if(buffer.size() >= 54)
    {
        header.headerField = (unsigned short)(buffer[0]);
        header.fileSize    = (unsigned)(buffer[2]);
        header.startOffset = (unsigned)(buffer[10]);
        header.width       = (unsigned)(buffer[18]);
        header.height      = (unsigned)(buffer[22]);
        header.bpp         = (unsigned short)(buffer[28]);
        header.compression = (unsigned)(buffer[30]);

        result = isHeaderValid(header);
    }
    else
    {
        OcularLogger->error("File buffer too small", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "readHeader"));
    }

    return result;
}

bool createPixelDataUncompressed(BMPHeader& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels)
{
    // Image data starts in the lower-left corner and is in BGRA order. 
    // If the reported height in the header is negative, then the data 
    // actually begins in the upper left corner.

    // Padding is added to the end of each row to ensure that the next 
    // row starts on a memory location that is a multiple of four.

    bool result = true;

    int pixelSize  = header.bpp / 8;                       // Bytes per pixel
    int rowWidth   = header.width * pixelSize;             // Row length before padding
    int rowPadding = rowWidth % 4;                         // Rows must be a multiple of 4 bytes in length
    int trueWidth  = rowWidth + rowPadding;                // True length of the row including padding
    int trueHeight = std::abs(header.height);              // Height can be negative if it goes top-to-bottom
    int dimensions = header.width * header.height;         // Total number of pixels in the image
    int startPos   = header.startOffset;                   // Starting position in buffer of the pixel array
    int stopPos    = startPos + (trueWidth * trueHeight);  // Ending position in buffer of the pixel array
             
    bool imageReversed = (header.height < 0);              // If the image height is negative, then start at top-left instead of bottom-left
    int pixelPos = 0;                                      // Starting pixel

    pixels.clear();
    pixels.reserve(dimensions);

    if(!imageReversed)
    {
        for(int i = startPos; i < stopPos; i += trueWidth)
        {
            for(int j = 0; j < rowWidth; j += pixelSize)
            {
                unsigned char b = buffer[i + (j + 0)];
                unsigned char g = buffer[i + (j + 1)];
                unsigned char r = buffer[i + (j + 2)];
                unsigned char a = (pixelSize == 3 ? 255 : buffer[i + (j + 3)]);  // If no alpha-channel, set to 255

                pixels.push_back(Ocular::Color(static_cast<float>(r) / 255.0f, 
                                               static_cast<float>(g) / 255.0f, 
                                               static_cast<float>(b) / 255.0f, 
                                               static_cast<float>(a) / 255.0f));
                pixelPos++;
            }
        }
    }
    else
    {
        OcularLogger->error("Reverse stored image currently not supported", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "createPixelDataUncompressed"));
        result = false;
    }

    return result;
}

bool createPixelDataCompressed(BMPHeader& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels)
{
    bool result = false;

    OcularLogger->error("Only uncompressed bitmap images currently supported", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "createPixelDataCompressed"));

    return result;
}