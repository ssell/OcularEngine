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
             */
            Texture2D(unsigned width, unsigned height, TEXTURE_FILTER_MODE filter = TEXTURE_FILTER_MODE::BILINEAR, TEXTURE_USAGE_MODE usage = TEXTURE_USAGE_MODE::STATIC);

            virtual ~Texture2D();

            //----------------------------------------
            // Inherited

            virtual void unload();
            virtual void apply() = 0;

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
            void  setPixel(int x, int y, Color const& color);

            /**
             * Retrieves the pixels in the specified bounds of the texture.
             *
             * \param[out] pixels
             * \param[in]  startX
             * \param[in]  startY
             * \param[in]  width  If set to -1, retrieves pixels from startX to end of texture.
             * \param[in]  height If set to -1, retrieves pixels from startY to end of texture.
             */
            void getPixels(std::vector<Color>& pixels, int startX = 0, int startY = 0, int width = -1, int height = -1);
            
            /**
             * Sets the pixels in the specified bounds of the texture.
             *
             * \param[out] pixels
             * \param[in]  startX
             * \param[in]  startY
             * \param[in]  width  If set to -1, sets pixels from startX to end of texture.
             * \param[in]  height If set to -1, sets pixels from startY to end of texture.
             */
            void setPixels(std::vector<Color> const& pixels, int startX = 0, int startY = 0, int width = -1, int height = -1);

            /**
             * \return Width of the texture
             */
            unsigned getWidth() const;

            /**
             * \return Height of the texture
             */
            unsigned getHeight() const;

        protected:

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