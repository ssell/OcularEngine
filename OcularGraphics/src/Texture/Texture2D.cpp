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

#include "Texture/Texture2D.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Texture2D::Texture2D(unsigned const width, unsigned const height, TEXTURE_FILTER_MODE const filter, TEXTURE_USAGE_MODE const usage)
            : Texture(filter, usage)
        {
            m_Width  = width;
            m_Height = height;
        }

        Texture2D::~Texture2D()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Texture2D::unload()
        {
        
        }

        Color Texture2D::getPixel(int const x, int const y)
        {
            Color result(0.0f, 0.0f, 0.0f, 1.0f);

            return result;
        }

        void Texture2D::setPixel(int const x, int const y, Color const& color)
        {
        
        }

        void Texture2D::getPixels(std::vector<Color>& pixels, int const startX, int const startY, int const width, int const height)
        {
        
        }

        void Texture2D::setPixels(std::vector<Color> const& pixels, int const startX, int const startY, int const width, int const height)
        {
        
        }

        unsigned Texture2D::getWidth() const
        {
            return m_Width;
        }

        unsigned Texture2D::getHeight() const
        {
            return m_Height;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}