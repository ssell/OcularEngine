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

#include "stdafx.h"
#include "Widgets/RenderFrame.hpp"
#include "Input/InputTranslator.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        RenderFrame::RenderFrame(QWidget *parent)
            : QFrame(parent),
              m_Input(new InputTranslator(this))
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setFrameStyle(QFrame::Panel | QFrame::Plain);
            setLineWidth(1);

            //------------------------------------------------------------

            Ocular::Core::WindowDescriptor descriptor;
            descriptor.displayName   = "Ocular Editor Render Frame";
            descriptor.colorBits     = 8;
            descriptor.depthBits     = 8;
            descriptor.stencilBits   = 8;
            descriptor.displayMode   = Core::WindowDisplayMode::WindowedBordered;
            descriptor.exclusiveMode = false;
            descriptor.external      = true;

            HWND hwnd = (HWND)winId();
            auto window = OcularWindows->connectWindow(descriptor, hwnd);

            //------------------------------------------------------------

            setStyleSheet(GeneralStyles::frameStyle);
            installEventFilter(m_Input);
        }

        RenderFrame::~RenderFrame()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize RenderFrame::sizeHint() const
        {
            return QSize(700, 700);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}