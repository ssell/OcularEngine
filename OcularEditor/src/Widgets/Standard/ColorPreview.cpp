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

#include "stdafx.h"
#include "Widgets/Standard/ColorPreview.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        ColorPreview::ColorPreview(QWidget* parent)
            : QFrame(parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setColor(Core::Color::White());
        }

        ColorPreview::~ColorPreview()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ColorPreview::sizeHint() const
        {
            return QSize(0, 0);
        }

        void ColorPreview::setColor(Core::Color const& color)
        {
            m_Color = color;

            const uint32_t r = static_cast<uint32_t>(color.r * 255.0f);
            const uint32_t g = static_cast<uint32_t>(color.g * 255.0f);
            const uint32_t b = static_cast<uint32_t>(color.b * 255.0f);
            const uint32_t a = static_cast<uint32_t>(color.a * 255.0f);

            const std::string colorStr =
                OcularString->toString<uint32_t>(r) + ", " +
                OcularString->toString<uint32_t>(g) + ", " +
                OcularString->toString<uint32_t>(b) + ", " +
                OcularString->toString<uint32_t>(a);

            const std::string stylesheet = "background-color: rgba(" + colorStr + "); border: 0px solid rgb(27, 27, 28);";

            setStyleSheet(stylesheet.c_str());
        }

        Core::Color const& ColorPreview::getColor() const
        {
            return m_Color;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}