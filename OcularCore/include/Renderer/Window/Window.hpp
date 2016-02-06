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
#ifndef __H__OCULAR_RENDERER_WINDOW__H__
#define __H__OCULAR_RENDERER_WINDOW__H__

#include "Object.hpp"
#include "WindowManager.hpp"
#include "WindowDisplay.hpp"
#include "WindowDescriptor.hpp"
#include "Events/AEventListener.hpp"

#include <string>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class RenderTexture;
        class DepthTexture;
    }

    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        class RenderContext;

        /**
         * \class Window
         * 
         * Abstract parent class of all Window implementations.<br/><br/>
         *
         * See ::WindowWin32 <br/>
         * See ::WindowLinux <br/>
         * See ::WindowOSX
         */
        class AWindow : public Object, public AEventListener
        {
            friend class WindowManager;
        public:

            /**
             * \param name        Display name of the window
             * \param width       Width of the window 
             * \param height      Height of the window
             * \param colorBits   Number of color bits
             * \param depthBits   Number of depth bits
             * \param stencilBits Number of stencil bits
             * \param display     Display mode
             * \param alwaysOnTop Should this Window be rendered on top of other Windows? (Exclusive mode rendering)
             */
            AWindow(WindowDescriptor const& descriptor);

            virtual ~AWindow();
            
            virtual bool onEvent(std::shared_ptr<AEvent> event) override;

            //--------------------------------------------

            /**
             * If the window dimensions do not already match the specified width/height, then the
             * window will be resized. In addition to this, the descriptor, render target, and depth
             * stencil textures will be updated and recreated to match the new dimensions.
             *
             * \param[in] width
             * \param[in] height
             */
            void resize(uint32_t width, uint32_t height);

            /**
             * \return The WindowDescriptor for this window instance.
             */
            WindowDescriptor getDescriptor() const;

            /**
             * Sets the WindowDescriptor for this window instance.
             * \param[in] descriptor
             */
            void setDescriptor(WindowDescriptor const& descriptor);

            /**
             * \return TRUE if this window currently has input focus.
             */
            bool hasFocus() const;

            /**
             * \return The current backbuffer render texture.
             */
            Graphics::RenderTexture* getRenderTexture();

            /**
             * Sets the RenderTexture to use as the backbuffer.
             * 
             * This method is typically called automatically during window creation
             * and/or GraphicsDriver initialization. Except for special circumstances
             * it should not be called externally.
             *
             * \note When set, the window assumes ownership of the texture and will 
             *       destroy it when it is no longer in use.
             *
             * \param[in] renderTexture
             */
            void setRenderTexture(Graphics::RenderTexture* renderTexture);

            /**
             * \return The current depth texture.
             */
            Graphics::DepthTexture* getDepthTexture();

            /**
             * Sets the DepthTexture to use for depth values.
             *
             * This method is typically called automatically during window creation
             * and/or GraphicsDriver initialization. Except for special circumstances
             * it should not be called externally.
             *
             * \note When set, the window assumes owndership of the texture and will
             *       destroy it when it is no longer in use.
             *
             * \param[in] depthTexture
             */
            void setDepthTexture(Graphics::DepthTexture* depthTexture);

            /**
             * Turns the cursor on and off.
             * \param[in] show If TRUE, the cursor is displayed while the window has focus.
             */
            virtual void showCursor(bool show);

            /** 
             * Returns the raw Operating System specific pointer for this window.
             * This can be cast to HWND on Windows, etc.
             */
            void* getOSPointer() const;

        protected:

            /**
             * Opens and initializes the Window.
             */
            virtual void open() = 0;

            /**
             * Updates and recreates the Window.
             */
            virtual void update(uint64_t time) = 0;

            /**
             * Closes the Window.
             */
            virtual void close() = 0;

            //----------------------------------------------------------

            WindowDescriptor m_Descriptor;

            Graphics::RenderTexture* m_RenderTexture;
            Graphics::DepthTexture*  m_DepthTexture;

            void* m_OSPointer;

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