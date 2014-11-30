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
#ifndef __H__OCULAR_RENDERER_WINDOW_MANAGER__H__
#define __H__OCULAR_RENDERER_WINDOW_MANAGER__H__

#include "WindowDisplay.hpp"

#include <memory>
#include <list>

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
        class AWindow;

        /**
         * \class WindowManager
         *
         * The WindowManager is responsible for creating and destroying Window instances.<br/>
         * All windows should be requested through the WindowManager and not directly instantiated.
         */
        class WindowManager
        {
        public:

            WindowManager();
            ~WindowManager();

            /**
             * Creates and returns a reference to a new window.<br/><br/>
             *
             * The returned pointer should not be destroyed as object management
             * is performed by the WindowManager to which the Window belongs.
             *
             * \param name        Display name of the window
             * \param width       Width of the window 
             * \param height      Height of the window
             * \param colorBits   Number of color bits
             * \param depthBits   Number of depth bits
             * \param stencilBits Number of stencil bits
             * \param display     Display mode
             * \param alwaysOnTop Should this Window be rendered on top of other Windows? (Exclusive mode rendering)
             * \return A pointer to the new window. If nullptr, then an error occurred during creation.
             */
            std::shared_ptr<AWindow> createWindow(std::string name, unsigned width, unsigned height, unsigned colorBits, 
               unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display, bool alwaysOnTop = false);

            /**
             * Destroys the Window with the specified name.
             * \param name
             */
            void destroyWindow(std::string name);

            /**
             * Destroys all windows.
             */
            void destroyAllWindows();

            /**
             * Lists all windows managed by this instance.
             */
            std::list<std::string> listWindows();
        
            /**
             * Returns a pointer to the Window with the specified name.<br/><br/>
             *
             * The returned pointer should not be destroyed as object management
             * is performed by the WindowManager to which the Window belongs.
             *
             * \param name
             * \return A pointer to the window. If nullptr, then no window matches the specified name.
             */
            std::shared_ptr<AWindow> getWindow(std::string name);

            /**
             * Returns a pointer to the main/primary window.
             * \return A pointer to the main window. If nullptr, then no windows are being managed.
             */
            std::shared_ptr<AWindow> getMainWindow();

            /**
             * Sets the main window.
             */
            void setMainWindow(std::string name);

            /**
             * Calls the update method for all tracked windows.<br/>
             * This ensures that all system messages get properly dispatched and handled.
             *
             * \param[in] time The amount of time (in MS) to allow a window to digest and dispatch system messages.
             */
            void updateWindows(long long time);

        protected:

        private:

            std::shared_ptr<AWindow> createWindowWin32(std::string name, unsigned width, unsigned height,
               unsigned colorBits, unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display, bool alwaysOnTop);

            std::shared_ptr<AWindow> createWindowOSX(std::string name, unsigned width, unsigned height,
               unsigned colorBits, unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display, bool alwaysOnTop);

            std::shared_ptr<AWindow> createWindowLinux(std::string name, unsigned width, unsigned height,
               unsigned colorBits, unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display, bool alwaysOnTop);

            std::string m_MainWindow;
            std::list<std::shared_ptr<AWindow>> m_Windows;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/** 
 * }@ End of Doxygen Groups 
 */

//------------------------------------------------------------------------------------------

#endif