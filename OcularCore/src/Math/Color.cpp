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

#include "Math/Color.hpp"
#include "Math/MathCommon.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Color::Color(Math::Vector4f const& color)
        {
            r = Math::Clamp<float>(color.r);
            g = Math::Clamp<float>(color.g);
            b = Math::Clamp<float>(color.b);
            a = Math::Clamp<float>(color.a);
        }

        Color::Color(float r, float g, float b, float a)
        {
            this->r = Math::Clamp<float>(r);
            this->g = Math::Clamp<float>(g);
            this->b = Math::Clamp<float>(b);
            this->a = Math::Clamp<float>(a);
        }

        Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            this->r = static_cast<float>(r) / 255.0f;
            this->g = static_cast<float>(g) / 255.0f;
            this->b = static_cast<float>(b) / 255.0f;
            this->a = static_cast<float>(a) / 255.0f;
        }

        Color::Color()
        {
            // Default set to the ErrorPink color
            r = 1.0f;
            g = 0.078f; 
            b = 0.576f;
            a = 1.0f;
        }

        Color::~Color()
        {
        
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