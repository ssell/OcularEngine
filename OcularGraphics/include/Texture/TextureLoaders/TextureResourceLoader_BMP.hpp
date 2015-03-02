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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_LOADER_BMP__H__
#define __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_LOADER_BMP__H__

#include "TextureResourceLoader.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \struct BMPHeader
         */
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

        /**
         * \class TextureResourceLoader_BMP
         *
         * Implementation of AResourceLoader that handles the loading of
         * files with the '.bmp' extension as uncompressed 24/32-bit bitmap images.
         *
         * These files are loaded as a Texture2D.
         */
        class TextureResourceLoader_BMP : public TextureResourceLoader
        {
        public:

            TextureResourceLoader_BMP();
            virtual ~TextureResourceLoader_BMP();

        protected:

            virtual bool readFile(Core::File const& file, std::vector<Color>& pixels, unsigned& width, unsigned& height);
            
        private:

            bool readHeader(std::vector<unsigned char> const& buffer, BMPHeader& header);
            bool isHeaderValid(BMPHeader const& header);

            bool createPixelDataUncompressed(BMPHeader& header, std::vector<unsigned char> const& buffer, std::vector<Color>& pixels);
            bool createPixelDataCompressed(BMPHeader& header, std::vector<unsigned char> const& buffer, std::vector<Color>& pixels);
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif