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
#ifndef __H__OCULAR_GRAPHICS_RANDOM_TEXTURE2D__
#define __H__OCULAR_GRAPHICS_RANDOM_TEXTURE2D__

#include "Texture2D.hpp"
#include "Math/Random/Random.hpp"
#include "Math/Noise/ANoise.hpp"

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
         * \class NoiseTexture2D
         *
         * Creates a Texture2D from a provided noise algorithm.
         *
         * This can either be pure noise from a PRNG or coherent noise from
         * an algorithm in Math::Noise.
         */
        class NoiseTexture2D : public Texture2D 
        {
        public:

            /**
             * Creates a new texture from the provided PRNG.
             *
             * \param[in] descriptor
             * \param[in] prng The pre-seeded PRNG used to generate the texture.
             */
            NoiseTexture2D(TextureDescriptor const& descriptor, std::shared_ptr<Math::Random::ARandom> prng);

            /**
             * Creates a new texture from the provided coherent noise generator.
             * 
             * \param[in] descriptor
             * \param[in] prng    The pre-seeded PRNG used to generate the texture.
             * \param[in] xOffset X-Axis offset into the noise function to begin at
             * \param[in] yOffset Y-Axis offset into the noise function to begin at
             */
            NoiseTexture2D(TextureDescriptor const& descriptor, std::shared_ptr<Math::Noise::ANoise> noise, uint32_t xOffset = 0, uint32_t yOffset = 0);

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