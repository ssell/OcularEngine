/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_MATH_COLOR_H__
#define __H__OCULAR_MATH_COLOR_H__

#include "Vector4.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class Color
         */
        class Color : public Math::Vector4f
        {
        public:

            Color(Math::Vector4f const& color);
            Color(float r, float g, float b, float a = 1.0f);
            Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
            Color();

            ~Color();

            //----------------------------------------------------------------
            // Pre-Defined Colors
            //----------------------------------------------------------------

            /**
             * RGBA: (0.545f, 0.27f, 0.075f, 1.0f)
             */
            static Color const& Brown();

            /**
             * RGBA: (0.0f, 0.0f, 0.0f, 1.0f)
             */
            static Color const& Black();

            /**
             * RGBA: (0.0f, 0.0f, 1.0f, 1.0f)
             */
            static Color const& Blue();

            /**
             * RGBA: (0.0f, 0.0f, 0.0f, 0.0f)
             */
            static Color const& Clear();

            /**
             * RGBA: (0.0f, 1.0f, 1.0f, 1.0f)
             */
            static Color const& Cyan();

            /**
             * RGBA: (0.2f, 0.2f, 0.2f, 1.0f)
             */
            static Color const& DarkGray();

            /**
             * RGBA: (1.0f, 0.078f, 0.576f, 1.0f)
             */
            static Color const& ErrorPink();

            /**
             * RGBA: (0.153f, 0.863f, 0.973f, 1.0f)
             */
            static Color const& FrigidBlue();

            /**
             * RGBA: (1.0f, 0.843f, 0.0f, 1.0f)
             */
            static Color const& Gold();

            /**
             * RGBA: (0.5f, 0.5f, 0.5f, 1.0f)
             */
            static Color const& Gray();

            /**
             * RGBA: (0.0f, 1.0f, 0.0f, 1.0f)
             */
            static Color const& Green();

            /**
             * RGBA: (1.0f, 0.0f, 1.0f, 1.0f)
             */
            static Color const& Magenta();

            /**
             * RGBA: (0.502f, 0.0f, 0.0f, 1.0f)
             */
            static Color const& Maroon();

            /**
             * RGBA: (1.0f, 0.647f, 0.0f, 1.0f)
             */
            static Color const& Orange();

            /**
             * RGBA: (1.0f, 0.753f, 0.796f, 1.0f)
             */
            static Color const& Pink();

            /**
             * RGBA: (0.294f, 0.0f, 0.51f, 1.0f)
             */
            static Color const& Purple();

            /**
             * RGBA: (1.0f, 0.0f, 0.0f, 1.0f)
             */
            static Color const& Red();

            /**
             * RGBA: (0.753f, 0.753f, 0.753f, 1.0f)
             */
            static Color const& Silver();

            /**
             * RGBA: (1.0f, 1.0f, 1.0f, 1.0f)
             */
            static Color const& White();

            /**
             * RGBA: (1.0f, 1.0f, 0.0f, 1.0f)
             */
            static Color const& Yellow();

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