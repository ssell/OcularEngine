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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_LOADER__H__
#define __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_LOADER__H__

#include "Resources/ResourceLoader.hpp"
#include "Math/Color.hpp"
#include "Common.hpp"

#include <vector>

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
         * \class TextureResourceLoader
         *
         * This is a common base implementation for all other ResourceLoaders that deal with
         * creating and loading Texture2D resources. It provides a common base loadResource
         * method as well as multiple utility helper methods.
         *
         * By inheriting from TextureResourceLoader instead of AResourceLoader, the developer
         * needs to only worry about their specific readFile implementation.
         */
        class TextureResourceLoader : public Core::AResourceLoader
        {
        public:

            TextureResourceLoader(std::string const& extension);
            virtual ~TextureResourceLoader();

            virtual bool loadResource(Core::Resource* &resource, Core::File const& file, std::string const& mappingName) override;

        protected:

            /**
             * Each TextureResourceLoader must provide a custom implementation for it's specific file type.
             *
             * \param[in] file Source file to read from.
             * \param[out] pixels Texture pixel data read in from the file.
             * \param[out] width  Width of the texture.
             * \param[out] height Height of the texture.
             * \return TRUE if file was read in successfully.
             */
            virtual bool readFile(Core::File const& file, std::vector<Core::Color>& pixels, unsigned& width, unsigned& height) = 0;

            /**
             * Creates the new Texture2D resource from provided pixel data.
             *
             * \param[out] resource The newly created resource.
             * \param[in]  file     Source file for the resource.
             * \param[in]  pixels   Pixel data for the texture arranged by rows.
             * \param[in]  width    Width of the texture.
             * \param[in]  height   Height of the texture.
             * \return TRUE if creation was successful.
             */
            virtual bool createResource(Core::Resource* &resource, Core::File const& file, std::vector<Core::Color> const& pixels, unsigned const& width, unsigned const& height);
            
            /**
             * Attempts to load the binary contents of the specified file into the provided empty buffer.
             * If the data was properly retrieved, it will then be converted to the current system's native endianness.
             *
             * \param[in]  file           Source file of the resource texture.
             * \param[out] buffer         Raw binary data of the file.
             * \param[in]  fileEndianness The endianness of the file.
             */
            virtual void loadFileIntoBuffer(Core::File const& file, std::vector<unsigned char>& buffer, Endianness fileEndianness);

        private:
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