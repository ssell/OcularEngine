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
#ifndef __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_LOADER__H__
#define __H__OCULAR_GRAPHICS_TEXTURE_RESOURCE_LOADER__H__

#include "Resources/ResourceLoader.hpp"
#include "Math/Vector4.hpp"

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
         */
        class TextureResourceLoader : public Core::AResourceLoader
        {
        public:

            TextureResourceLoader(std::string const& extension);
            virtual ~TextureResourceLoader();

            virtual bool loadResource(Core::Resource* resource, Core::File const& file);

        protected:

            virtual bool isValidFile(Core::File const& file);
            virtual bool createResource(Core::Resource* resource, Core::File const& file, std::vector<Color> const& pixels, unsigned const& width, unsigned const& height);

            virtual bool readFile(Core::File const& file, std::vector<Color>& pixels, unsigned& width, unsigned& height) = 0;

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