/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#include "WindowManager.hpp"
#include "WindowDisplay.hpp"

#include <string>

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
        class AWindow 
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
            AWindow(std::string name, unsigned width, unsigned height, unsigned colorBits,
               unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display, bool alwaysOnTop);

            virtual ~AWindow();

            //--------------------------------------------

            /** 
             * \return The name of the Window
             */
            std::string getName() const;

            /**
             * \param[in] name Name of the Window
             */
            void setName(std::string name);
            
            /** 
             * \return The width of the window / x-resolution in fullscreen display
             */
            unsigned getResolutionX() const;
            void setResolutionX(unsigned width);
            
            /** 
             * \return The height of the window / y-resolution in fullscreen display
             */
            unsigned getResolutionY() const;
            void setResolutionY(unsigned height);

            unsigned getColorBits() const;
            void setColorBits(unsigned bits);

            unsigned getDepthBits() const;
            void setDepthBits(unsigned bits);

            unsigned getStencilBits() const;
            void setStencilBits(unsigned bits);

            WINDOW_DISPLAY_MODE getDisplayMode() const;
            void setDisplayMode(WINDOW_DISPLAY_MODE display);

            /**
             * \return TRUE if the Window is always rendered on top of other Windows.
             */
            bool getIsAlwaysOnTop() const;

            /**
             * \param[in] onTop TRUE if the Window should always be rendered on top of other Windows.
             */
            void setIsAlwaysOnTop(bool onTop);

        protected:

            /**
             * Opens and initializes the Window.
             */
            virtual void open() = 0;

            /**
             * Updates and recreates the Window.
             */
            virtual void update(long long time) = 0;

            /**
             * Closes the Window.
             */
            virtual void close() = 0;

            std::shared_ptr<RenderContext> m_pRenderContext;

            std::string m_Name;

            unsigned m_Width;
            unsigned m_Height;
            unsigned m_ColorBits;
            unsigned m_DepthBits;
            unsigned m_StencilBits;

            WINDOW_DISPLAY_MODE m_DisplayMode;

            bool m_RenderExclusive;

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