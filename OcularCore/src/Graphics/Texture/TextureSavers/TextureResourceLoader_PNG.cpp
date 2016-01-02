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

#include "OcularEngine.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/EndianOps.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_PNG.hpp"
#include "Resources/ResourceLoaderRegistrar.hpp"

#include "libpng/png.h"

#include <string>
#include <fstream>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::TextureResourceLoader_PNG)

//------------------------------------------------------------------------------------------

unsigned getBufferPos(unsigned const& x, unsigned const& y, unsigned const& width, unsigned const& height);

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

        bool TextureResourceLoader_PNG::readFile(Core::File const& file, std::vector<Core::Color>& pixels, unsigned& width, unsigned& height)
        {
            bool result = false;

            png_image image;

            memset(&image, 0, sizeof(image));
            image.version = PNG_IMAGE_VERSION;

            if(png_image_begin_read_from_file(&image, file.getFullPath().c_str()))
            {
                png_bytep buffer;

                image.format = PNG_FORMAT_RGBA;
                buffer = (png_bytep)malloc(PNG_IMAGE_SIZE(image));

                if(buffer)
                {
                    if(png_image_finish_read(&image, NULL, buffer, 0, NULL))
                    {
                        Core::Color newPixel;

                        unsigned numPixels = image.width * image.height;
                        unsigned bufferPos = 0;

                        pixels.reserve(numPixels);

                        width  = image.width;
                        height = image.height;

                        for(unsigned y = 0; y < image.height; y++)
                        {
                            for(unsigned x = 0; x < image.width; x++)
                            {
                                bufferPos = getBufferPos(x, y, width, height);

                                newPixel.r = static_cast<float>(buffer[bufferPos + 0]) / 255.0f;
                                newPixel.g = static_cast<float>(buffer[bufferPos + 1]) / 255.0f;
                                newPixel.b = static_cast<float>(buffer[bufferPos + 2]) / 255.0f;
                                newPixel.a = static_cast<float>(buffer[bufferPos + 3]) / 255.0f;

                                pixels.push_back(newPixel);
                            }
                        }

                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Failed to finish reading file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("TextureResourceLoader_PNG", "readFile"));
                    }

                    free(buffer);
                }
                else
                {
                    OcularLogger->error("Failed to allocate memory for texture", OCULAR_INTERNAL_LOG("TextureResourceLoader_PNG", "readFile"));
                }
            }
            else
            {
                OcularLogger->error("Failed to begin read of file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("TextureResourceLoader_PNG", "readFile"));
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


unsigned getBufferPos(unsigned const& x, unsigned const& y, unsigned const& width, unsigned const& height)
{
    // Ocular (0,0) is the lower-left corner, while
    // PNG (0,0) is the upper-left corner. 

    return ((((height - 1) - y) * width) * 4) + (x * 4);
}