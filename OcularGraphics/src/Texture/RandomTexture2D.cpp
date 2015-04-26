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

#include "Texture/RandomTexture2D.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        RandomTexture2D::RandomTexture2D(std::shared_ptr<Math::Random::ARandom> prng, uint32_t width, uint32_t height, TextureFilterMode filter, TextureUsageMode usage)
            : Texture2D(width, height, filter, usage)
        {
            uint32_t numPixels = width * height;
            float pixelColor = 0.0f;
            
            m_Pixels.reserve(numPixels);

            for(uint32_t i = 0; i < numPixels; i++)
            {
                pixelColor = prng->nextf();
                m_Pixels[i] = Color(pixelColor, pixelColor, pixelColor, 1.0f);
            }

            m_IsInMemory = true;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}