/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Graphics/Texture/TextureSavers/TextureResourceSaver_PNG.hpp"
#include "Resources/ResourceSaverRegistrar.hpp"

#include "libpng/png.h"

#include <algorithm>

OCULAR_REGISTER_RESOURCE_SAVER(Ocular::Graphics::TextureResourceSaver_PNG)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceSaver_PNG::TextureResourceSaver_PNG()
            : TextureResourceSaver(".png")
        {
        
        }

        TextureResourceSaver_PNG::~TextureResourceSaver_PNG()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceSaver_PNG::saveFile(Core::File const& file, std::vector<Core::Color> const& pixels, unsigned const width, unsigned const height)
        {
            bool result = false;

            //----------------------------------------
            // Create the PNG image descriptor

            png_image image;

            memset(&image, 0, sizeof(image));
            image.version = PNG_IMAGE_VERSION;
            image.width   = static_cast<png_uint_32>(width);
            image.height  = static_cast<png_uint_32>(height);
            image.format  = PNG_FORMAT_RGBA;

            //----------------------------------------
            // Create the PNG image buffer

            png_bytep buffer;
            buffer = (png_bytep)malloc(PNG_IMAGE_SIZE(image));

            unsigned bufferPos = 0;
            unsigned pixelPos  = 0;

            if(buffer)
            {
                for(unsigned y = 0; y < height; y++)
                {
                    for(unsigned x = 0; x < width; x++)
                    {
                        // Our color pixels start at the bottom-left corner while
                        // the PNG format expects them to start at the upper-left corner.
                        pixelPos = (((height - 1) - y) * width) + x;
                        
                        buffer[bufferPos++] = static_cast<png_byte>(pixels[pixelPos].r * 255.0f);
                        buffer[bufferPos++] = static_cast<png_byte>(pixels[pixelPos].g * 255.0f);
                        buffer[bufferPos++] = static_cast<png_byte>(pixels[pixelPos].b * 255.0f);
                        buffer[bufferPos++] = static_cast<png_byte>(pixels[pixelPos].a * 255.0f);
                    }
                }

                //------------------------------------
                // Write the PNG to disk

                if(png_image_write_to_file(&image, file.getFullPath().c_str(), 0, buffer, 0/*(width * 4)*/, 0))
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to write texture to PNG file", OCULAR_INTERNAL_LOG("TextureResourceSaver_PNG", "saveFile"));
                }

                free(buffer);
            }
            else
            {
                OcularLogger->error("Failed to allocate PNG buffer for texture save", OCULAR_INTERNAL_LOG("TextureResourceSaver_PNG", "saveFile"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}