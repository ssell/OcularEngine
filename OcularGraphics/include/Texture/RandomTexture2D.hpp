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

#ifndef __H__OCULAR_GRAPHICS_RANDOM_TEXTURE2D__
#define __H__OCULAR_GRAPHICS_RANDOM_TEXTURE2D__

#include "Texture2D.hpp"
#include "Math/Random/Random.hpp"

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
         * \class RandomTexture2D
         *
         * Creates a Texture2D from a provided PRNG.
         */
        class RandomTexture2D : public Texture2D 
        {
        public:

            /**
             *
             * \param[in] prng   The pre-seeded PRNG used to generate the texture.
             * \param[in] width  Texture width.
             * \param[in] height Texture height.
             * \param[in] filter
             * \param[in] usage
             */
            RandomTexture2D(std::shared_ptr<Math::Random::ARandom> prng, uint32_t width, uint32_t height, 
                TextureFilterMode filter = TextureFilterMode::Bilinear, TextureUsageMode usage = TextureUsageMode::Static);

        protected:

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