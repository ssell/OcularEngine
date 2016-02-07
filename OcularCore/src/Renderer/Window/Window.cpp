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

#include "Renderer/Window/Window.hpp"
#include "Graphics/Texture/RenderTexture.hpp"
#include "Graphics/Texture/DepthTexture.hpp"
#include "Events/Events/WindowResizeEvent.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        AWindow::AWindow(WindowDescriptor const& descriptor)
            : Object(descriptor.displayName, "AWindow"),
              m_Descriptor(descriptor),
              m_RenderTexture(nullptr),
              m_DepthTexture(nullptr),
              m_OSPointer(nullptr)
        {
            OcularEvents->registerListener(this, Priority::Low);
        }

        AWindow::~AWindow()
        {
            if(m_RenderTexture)
            {
                delete m_RenderTexture;
                m_RenderTexture = nullptr;
            }

            if(m_DepthTexture)
            {
                delete m_DepthTexture;
                m_DepthTexture = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool AWindow::onEvent(std::shared_ptr<AEvent> event)
        {
            bool result = true;

            if(event)
            {
                if(event->isType<WindowResizeEvent>())
                {
                    WindowResizeEvent* resizeEvent = dynamic_cast<WindowResizeEvent*>(event.get());

                    if(resizeEvent->window == this)
                    {
                        resize(resizeEvent->width, resizeEvent->height);
                    }
                }
            }

            return result;
        }

        void AWindow::resize(uint32_t const width, uint32_t const height)
        {
            bool rebuild = false;

            if(width != m_Descriptor.width)
            {
                m_RenderTexture->setWidth(width);
                m_DepthTexture->setWidth(width);

                m_Descriptor.width = width;
                rebuild = true;
            }

            if(height != m_Descriptor.height)
            {
                m_RenderTexture->setHeight(height);
                m_DepthTexture->setHeight(height);

                m_Descriptor.height = height;
                rebuild = true;
            }

            if(rebuild)
            {
                m_RenderTexture->apply();
                m_DepthTexture->apply();
            }
        }

        WindowDescriptor AWindow::getDescriptor() const
        {
            return m_Descriptor;
        }

        void AWindow::setDescriptor(WindowDescriptor const& descriptor)
        {
            m_Descriptor = descriptor;
        }

        Graphics::RenderTexture* AWindow::getRenderTexture()
        {
            return m_RenderTexture;
        }

        void AWindow::setRenderTexture(Graphics::RenderTexture* renderTexture)
        {
            if(m_RenderTexture)
            {
                delete m_RenderTexture;
                m_RenderTexture = nullptr;
            }

            m_RenderTexture = renderTexture;
        }

        Graphics::DepthTexture* AWindow::getDepthTexture()
        {
            return m_DepthTexture;
        }

        void AWindow::setDepthTexture(Graphics::DepthTexture* renderTexture)
        {
            if(m_DepthTexture)
            {
                delete m_DepthTexture;
                m_DepthTexture = nullptr;
            }

            m_DepthTexture = renderTexture;
        }

        void AWindow::showCursor(bool show)
        {

        }

        void* AWindow::getOSPointer() const
        {
            return m_OSPointer;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}