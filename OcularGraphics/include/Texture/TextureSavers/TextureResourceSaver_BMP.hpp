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
#ifndef __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_SAVER_BMP__H__
#define __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_SAVER_BMP__H__

#include "TextureResourceSaver.hpp"

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
         * \class TextureResourceSaver_BMP
         */
        class TextureResourceSaver_BMP : public TextureResourceSaver 
        {
        public:

            TextureResourceSaver_BMP();
            virtual ~TextureResourceSaver_BMP();

        protected:

            /**
             * See TextureResourceSaver::saveFile
             *
             * \param[in] file File to write to. This file has already been verified to exist and be writeable.
             * \param[in] pixels Texture pixel data to write to the file.
             * \param[in] width  Width of the texture.
             * \param[in] height Height of the texture.
             * \return TRUE if the file was successfully saved.
             */
            virtual bool saveFile(Core::File const& file, std::vector<Color> const& pixels, unsigned const width, unsigned const height);

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