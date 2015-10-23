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
        
            static Color Brown()     { return Color(0.545f, 0.27f, 0.075f); }
            static Color Black()     { return Color(0.0f, 0.0f, 0.0f); }
            static Color Blue()      { return Color(0.0f, 0.0f, 1.0f); }
            static Color Clear()     { return Color(0.0f, 0.0f, 0.0f, 0.0f); }
            static Color Cyan()      { return Color(0.0f, 1.0f, 1.0f); }
            static Color ErrorPink() { return Color(1.0f, 0.078f, 0.576f); }
            static Color Gold()      { return Color(1.0f, 0.843f, 0.0f); }
            static Color Gray()      { return Color(0.5f, 0.5f, 0.5f); }
            static Color Green()     { return Color(0.0f, 1.0f, 0.0f); }
            static Color Magenta()   { return Color(1.0f, 0.0f, 1.0f); }
            static Color Maroon()    { return Color(0.502f, 0.0f, 0.0f); }
            static Color Orange()    { return Color(1.0f, 0.647f, 0.0f); }
            static Color Pink()      { return Color(1.0f, 0.753f, 0.796f); }
            static Color Purple()    { return Color(0.294f, 0.0f, 0.51f); }
            static Color Red()       { return Color(1.0f, 0.0f, 0.0f); }
            static Color Silver()    { return Color(0.753f, 0.753f, 0.753f); }
            static Color White()     { return Color(1.0f, 1.0f, 1.0f); }
            static Color Yellow()    { return Color(1.0f, 1.0f, 0.0f); }

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