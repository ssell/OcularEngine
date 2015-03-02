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
#ifndef __H__OCULAR_GRAPHICS_TEXTURE2D__H__
#define __H__OCULAR_GRAPHICS_TEXTURE2D__H__

#include "Texture.hpp"
#include "Texture/TextureEnums.hpp"

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
         * \class Texture2D
         */
        class Texture2D : public Texture
        {
        public:

            /**
             * \param[in] width
             * \param[in] height
             * \param[in] filter
             * \param[in] usage
             * \param[in] source
             */
            Texture2D(unsigned width, unsigned height, TEXTURE_FILTER_MODE filter = TEXTURE_FILTER_MODE::BILINEAR, TEXTURE_USAGE_MODE usage = TEXTURE_USAGE_MODE::STATIC);

            virtual ~Texture2D();

            //----------------------------------------
            // Inherited

            virtual void unload();
            virtual void apply();

            //----------------------------------------

            /**
             * Retrieves the specified pixel in the texture.
             *
             * \param[in] x
             * \param[in] y
             * \return Color of the pixel located at (x,y) in the texture.
             */
            Color getPixel(int x, int y);

            /**
             * Sets the specified pixel in the texture.
             *
             * \param[in] x
             * \param[in] y
             * \param[in] color
             *
             * \note apply must be called after any pixel setting in order for the texture on GPU to be updated.
             */
            bool setPixel(int x, int y, Color const& color);

            /**
             * Retrieves the pixels in the specified bounds of the texture.
             *
             * The pixels are returned in a vector that stores them in row order. So, for example,
             * if a 3x3 square of pixels was requested starting from the origin, then the return would be:
             *
             *     Color(0,0), Color(1,0), Color(2,0), Color(0,1), Color(1,1), Color(2,1), Color(0,2), Color(1,2), Color(2,2)
             *
             * \param[out] pixels
             * \param[in]  startX
             * \param[in]  startY
             * \param[in]  width  If set to -1, retrieves pixels from startX to end of texture.
             * \param[in]  height If set to -1, retrieves pixels from startY to end of texture.
             */
            bool getPixels(std::vector<Color>& pixels, int startX = 0, int startY = 0, int width = -1, int height = -1);
            
            /**
             * Sets the pixels in the specified bounds of the texture.
             *
             * The provided pixel vector is expected to be in row order. So, for example,
             * if a 3x3 square of pixels was set starting from the origin (bottom-left corner), then the pixels would be:
             *
             *     Color(0,0), Color(1,0), Color(2,0), Color(0,1), Color(1,1), Color(2,1), Color(0,2), Color(1,2), Color(2,2)
             *
             * \param[out] pixels
             * \param[in]  startX
             * \param[in]  startY
             * \param[in]  width  If set to -1, sets pixels from startX to end of texture.
             * \param[in]  height If set to -1, sets pixels from startY to end of texture.
             * \note apply must be called after any pixel setting in order for the texture on GPU to be updated.
             */
            bool setPixels(std::vector<Color> const& pixels, int startX = 0, int startY = 0, int width = -1, int height = -1);

            /**
             * \return Width of the texture
             */
            unsigned getWidth() const;

            /**
             * \param[in] width
             * \note apply must be called after any dimension changes in order for the texture on GPU to be updated.
             */
            void setWidth(unsigned const& width);

            /**
             * \return Height of the texture
             */
            unsigned getHeight() const;
            
            /**
             * \param[in] height
             * \note apply must be called after any dimension changes in order for the texture on GPU to be updated.
             */
            void setHeight(unsigned const& height);

        protected:

            void getTrueDimensions(int startX, int startY, int& trueWidth, int& trueHeight);

            //----------------------------------------

            std::vector<Color> m_Pixels;

            unsigned m_Width;
            unsigned m_Height;

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