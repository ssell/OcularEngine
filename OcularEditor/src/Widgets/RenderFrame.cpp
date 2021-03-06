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
#include "Widgets/RenderFrame.hpp"
#include "Input/InputTranslator.hpp"
#include "Events/Events/WindowResizeEvent.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        RenderFrame::RenderFrame(QWidget *parent)
            : QFrame(parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setFrameStyle(QFrame::Panel | QFrame::Plain);
            setFocusPolicy(Qt::StrongFocus);                         // Critical! Without it, the QFrame will never receive keyboard input events
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

        void RenderFrame::keyPressEvent(QKeyEvent* event)
        {
            InputTranslator::TranslateKeyPress(event);
        }

        void RenderFrame::keyReleaseEvent(QKeyEvent* event)
        {
            InputTranslator::TranslateKeyRelease(event);
        }

        void RenderFrame::mouseMoveEvent(QMouseEvent* event)
        {
            InputTranslator::TranslateMouseMove(event);
        }

        void RenderFrame::mousePressEvent(QMouseEvent* event)
        {
            InputTranslator::TranslateMousePress(event);
        }

        void RenderFrame::mouseReleaseEvent(QMouseEvent* event)
        {
            InputTranslator::TranslateMouseRelease(event);
        }

        void RenderFrame::wheelEvent(QWheelEvent* event)
        {
            if(event)
            {
                OcularInput->triggerMouseScrollDelta(static_cast<int8_t>(event->delta()));
            }
        }

        void RenderFrame::resizeEvent(QResizeEvent* event)
        {
            if(event)
            {
                void* osPointer = (void*)(winId());
                auto window = OcularWindows->getWindow(osPointer);

                if(window)
                {
                    const uint32_t width  = static_cast<uint32_t>(event->size().width());
                    const uint32_t height = static_cast<uint32_t>(event->size().height());

                    OcularEvents->queueEvent(std::make_shared<Core::WindowResizeEvent>(window.get(), width, height));
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}