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
#include "Utilities/EndianOps.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_TGA.hpp"
#include "Resources/ResourceLoaderRegistrar.hpp"

#include <string>
#include <fstream>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::TextureResourceLoader_TGA)

//------------------------------------------------------------------------------------------

struct TGAHeader
{
    unsigned short width;
    unsigned short height;
    unsigned char  bpp;      // Bytes per pixel
    unsigned char  type;     
};

bool isValidHeader(TGAHeader const& header);
bool readHeader(std::vector<unsigned char> const& buffer, TGAHeader& header);
bool readUncompressedTrueVision(TGAHeader const& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels);
bool readCompressedTrueVision(TGAHeader const& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceLoader_TGA::TextureResourceLoader_TGA()
            : TextureResourceLoader(".tga")
        {
        
        }

        TextureResourceLoader_TGA::~TextureResourceLoader_TGA()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceLoader_TGA::readFile(Core::File const& file, std::vector<Color>& pixels, unsigned& width, unsigned& height)
        {
            bool result = false;

            std::vector<unsigned char> buffer;
            loadFileIntoBuffer(file, buffer, Endianness::Little);

            TGAHeader header;

            if(readHeader(buffer, header))
            {
                if(isValidHeader(header))
                {
                    width  = header.width;
                    height = header.height;

                    if(header.type == 2)
                    {
                        if(readUncompressedTrueVision(header, buffer, pixels))
                        {
                            result = true;
                        }
                        else
                        {
                            OcularLogger->error("Failed to read uncompressed True Vision image", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "readFile"));
                        }
                    }
                    else 
                    {
                        if(readCompressedTrueVision(header, buffer, pixels))
                        {
                            result = true;
                        }
                        else
                        {
                            OcularLogger->error("Failed to read compressed True Vision image", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "readFile"));
                        }
                    }
                }
                else
                {
                    OcularLogger->error("Failed to validate TGA header information", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "readFile"));
                }
            }
            else
            {
                OcularLogger->error("Failed to read TGA header", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "readFile"));
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

bool readHeader(std::vector<unsigned char> const& buffer, TGAHeader& header)
{
    bool result = false;

    if(buffer.size() >= 18)
    {
        header.type   = *(unsigned char*)(&buffer[2]);
        header.width  = *(unsigned short*)(&buffer[12]);
        header.height = *(unsigned short*)(&buffer[14]);
        header.bpp    = *(unsigned char*)(&buffer[16]) / 8;

        result = true;
    }
    else
    {
        OcularLogger->error("File buffer too small", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "readHeader"));
    }

    return result;
}

bool isValidHeader(TGAHeader const& header)
{
    bool result = true;

    if((header.width == 0) || (header.height == 0))
    {
        result = false;
        OcularLogger->error("Invalid image dimensions", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "isValidHeader"));
    }

    if((header.type != 2) && (header.type != 10))
    {
        result = false;
        OcularLogger->error("Unsupported TGA image type (", header.type, ")", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "isValidHeader"));
    }

    if((header.bpp != 3) && (header.bpp != 4))
    {
        result = false;
        OcularLogger->error("Unsupported image color depth (", header.bpp * 8, ")", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "isValidHeader"));
    }

    return result;
}

bool readUncompressedTrueVision(TGAHeader const& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels)
{
    bool result = false;
    
    unsigned numPixels = header.width * header.height;
    unsigned totalSize = numPixels * header.bpp;
    unsigned bufferPos = 18;
    
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;

    if(buffer.size() >= (18 + totalSize))  // header + raw image data
    {
        pixels.clear();
        pixels.reserve(numPixels);

        for(unsigned i = 0; (i < numPixels) && (bufferPos + (header.bpp - 1) < buffer.size()); i++)
        {
            // TGA images are stored in BGR/A format

            b = buffer[bufferPos++];
            g = buffer[bufferPos++];
            r = buffer[bufferPos++];
            a = (header.bpp == 4 ? buffer[bufferPos++] : 255);

            pixels.push_back(Ocular::Color(static_cast<float>(r) / 255.0f, 
                                           static_cast<float>(g) / 255.0f, 
                                           static_cast<float>(b) / 255.0f, 
                                           static_cast<float>(a) / 255.0f));
        }

        result = true;
    }
    else
    {
        OcularLogger->error("Image buffer too small", OCULAR_INTERNAL_LOG("TextureResourceLoader_TGA", "readUncompressedTrueVision"));
    }

    return result;
}

bool readCompressedTrueVision(TGAHeader const& header, std::vector<unsigned char> const& buffer, std::vector<Ocular::Color>& pixels)
{
    bool result = true;

    /**
	 * The compression is relatively simple. We check to see if the next chunk of data
	 * is RAW or RLE. If RAW, then we read normally. If RLE, then we copy the pixel an
	 * x amount of times.
	 *
	 * The chunk is RAW if the chunk value is <= 127. The length of the chunk is then
	 * that value + 1. So we just read in chunk value + 1 pixels.
	 *
	 * If the chunk is RLE, then the value is > 127. Simply subtract 127, read the next
	 * pixel and then copy it that number of times.
	 *
	 * Repeat this until all pixels have been read.
	 */

    unsigned totalPixel = header.width * header.height;
    unsigned pixelCount = 0;
    unsigned bufferPos  = 18;
    unsigned chunkValue = 0;

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;

    pixels.clear();
    pixels.reserve(totalPixel);

    while(pixelCount < totalPixel)
    {

        // Start reading a new chunk
        chunkValue = *(unsigned char*)(&buffer[bufferPos++]);

        if(chunkValue <= 127)
        {
            // Raw
            chunkValue += 1;

            for(unsigned i = 0; i < chunkValue; i++)
            {
                b = buffer[bufferPos++];
                g = buffer[bufferPos++];
                r = buffer[bufferPos++];
                a = (header.bpp == 4 ? buffer[bufferPos++] : 255);

                pixels.push_back(Ocular::Color(static_cast<float>(r) / 255.0f, 
                                                static_cast<float>(g) / 255.0f, 
                                                static_cast<float>(b) / 255.0f, 
                                                static_cast<float>(a) / 255.0f));

                pixelCount++;
            }
        }
        else
        {
            // RLE
            chunkValue -= 127;

            b = buffer[bufferPos++];
            g = buffer[bufferPos++];
            r = buffer[bufferPos++];
            a = (header.bpp == 4 ? buffer[bufferPos++] : 255);

            for(unsigned i = 0; i < chunkValue; i++)
            {
                pixels.push_back(Ocular::Color(static_cast<float>(r) / 255.0f, 
                                                static_cast<float>(g) / 255.0f, 
                                                static_cast<float>(b) / 255.0f, 
                                                static_cast<float>(a) / 255.0f));

                pixelCount++;
            }
        }
    }

    return result;
}