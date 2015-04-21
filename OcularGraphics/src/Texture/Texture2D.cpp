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
#include "OcularEngine.hpp"

#include <algorithm>

#define TEXTURE_INDEX(x,y) m_Pixels[((y * m_Width) + x)]

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Texture2D::Texture2D(unsigned const width, unsigned const height, TextureFilterMode const filter, TextureUsageMode const usage)
            : Texture(filter, usage)
        {
            m_Width  = width;
            m_Height = height;

            unsigned size = width * height;

            m_Pixels.reserve(size);
            
            for(unsigned i = 0; i < size; i++)
            {
                m_Pixels.push_back(Color());
            }
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

        void Texture2D::apply()
        {
            // Adjust for potential new width/height
            // OpenGL and DirectX childs will have to update texture on GPU
        }

        Color Texture2D::getPixel(unsigned const x, unsigned const y)
        {
            Color result(0.0f, 0.0f, 0.0f, 1.0f);

            if((x >= 0) && (x < m_Width) && (y >= 0) && (y < m_Height))
            {
                result = TEXTURE_INDEX(x, y);
            }

            return result;
        }

        bool Texture2D::setPixel(unsigned const x, unsigned const y, Color const& color)
        {
            bool result = false;

            if((x >= 0) && (x < m_Width) && (y >= 0) && (y < m_Height))
            {
                TEXTURE_INDEX(x, y) = color;
                result = true;
            }

            m_IsInMemory = result;
            return result;
        }

        bool Texture2D::getPixels(std::vector<Color>& pixels, unsigned const startX, unsigned const startY, int const width, int const height)
        {
            bool result = false;

            if((startX >= 0) && (startX < m_Width) && (startY >= 0) && (startY < m_Height))
            {
                int workingWidth  = width;     // The width and height of the subsection of the texture to get
                int workingHeight = height;

                getTrueDimensions(startX, startY, workingWidth, workingHeight);

                int totalSize = workingWidth * workingHeight;

                if(totalSize > 0)
                {
                    pixels.clear();
                    pixels.reserve(totalSize);

                    for(unsigned iterY = startY; iterY < (startY + workingHeight); iterY++)
                    {
                        for(unsigned iterX = startX; iterX < (startX + workingWidth); iterX++)
                        {
                            pixels.push_back(getPixel(iterX, iterY));  // Use getPixel instead of direct access for the added
                        }                                              // safety-checks provided in that method
                    }

                    result = true;
                }
            }

            return result;
        }

        bool Texture2D::setPixels(std::vector<Color> const& pixels, unsigned const startX, unsigned const startY, int const width, int const height)
        {
            bool result = false;

            if((startX >= 0) && (startX < m_Width) && (startY >= 0) && (startY < m_Height))
            {
                int workingWidth  = width;     // The width and height of the subsection of the texture to set
                int workingHeight = height;

                getTrueDimensions(startX, startY, workingWidth, workingHeight);

                unsigned totalSize = static_cast<unsigned>(workingWidth) * static_cast<unsigned>(workingHeight);

                if((totalSize > 0) && (totalSize <= pixels.size()))
                {
                    int index = 0;
                    result = true;

                    for(unsigned iterY = startY; (iterY < (startY + workingHeight)) && (result); iterY++)   // Break out if we had a failed pixel set
                    {
                        for(unsigned iterX = startX; (iterX < (startX + workingWidth)) && (result); iterX++)
                        {
                            result = setPixel(iterX, iterY, pixels[(iterY * width) + iterX]);  // Use setPixel instead of direct access for the added safety-checks provided in that method
                        }
                    }
                }
            }

            m_IsInMemory = result;
            return result;
        }

        unsigned Texture2D::getWidth() const
        {
            return m_Width;
        }

        void Texture2D::setWidth(unsigned const& width)
        {
            if(width > 0)
            {
                m_Width = width;
            }
        }

        unsigned Texture2D::getHeight() const
        {
            return m_Height;
        }

        void Texture2D::setHeight(unsigned const& height)
        {
            if(height > 0)
            {
                m_Height = height;
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Texture2D::getTrueDimensions(unsigned const startX, unsigned const startY, int& trueWidth, int& trueHeight)
        {
            if((trueWidth < 0) ||                    // Specified to use remainder of width from startX
               ((startX + trueWidth) > m_Width))     // Provided width is too wide; Scale it back.
            {
                trueWidth = m_Width - startX;
            }

            if((trueHeight < 0) ||                   // Specified to use remainder of height from startY
              ((startY + trueHeight) > m_Height))   // Provided height is too tall; Scale it back.
            {
                trueHeight = m_Height - startY;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

#undef TEXTURE_INDEX