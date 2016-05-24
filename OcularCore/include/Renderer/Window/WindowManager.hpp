/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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
#include "WindowDescriptor.hpp"
#include "Window.hpp"

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
             * \param descriptor 
             * \return A pointer to the new window. If nullptr, then an error occurred during creation.
             */
            std::shared_ptr<AWindow> openWindow(WindowDescriptor const& descriptor);

            /**
             * Connects to a pre-existing window.
             *
             * \param[in] windowID The system specific window identifier (HWND in Windows, etc.)
             * \return A pointer to the new Ocular window context. If nullptr, then an error occurred during connection.
             */
            std::shared_ptr<AWindow> connectWindow(WindowDescriptor const& descriptor, void* windowID);

            /**
             * Destroys the Window with the specified UID.
             * \param uid
             */
            void closeWindow(UUID const& uuid);

            /**
             * Destroys all windows.
             */
            void closeAllWindows();

            /**
             * \return A list of all windows tracked by this manager instance.
             */
            std::list<std::shared_ptr<AWindow>> listWindows() const;

            /**
             * \return Number of windows tracked by this manager instance.
             */
            uint32_t getNumWindows() const;
        
            /**
             * Returns a pointer to the Window with the specified UID.<br/><br/>
             *
             * The returned pointer should not be destroyed as object management
             * is performed by the WindowManager to which the Window belongs.
             *
             * \param uid
             * \return A pointer to the window. If nullptr, then no window matches the specified UID.
             */
            std::shared_ptr<AWindow> getWindow(UUID const& uuid);

            /**
             * Returns a pointer to the Winodw matching the specified OS window pointer.<br/><br/>
             *
             * The returned pointer should not be destroyed as object management
             * is performed by the WindowManager to which the Window belongs.
             *
             * \param osPointer
             * \return A pointer to the window. If nullptr, then no window matches the specified OS pointer.
             */
            std::shared_ptr<AWindow> getWindow(void* osPointer);

            /**
             * Returns a pointer to the main/primary window.
             * \return A pointer to the main window. If nullptr, then no windows are being managed.
             */
            std::shared_ptr<AWindow> getMainWindow();

            /**
             * Sets the main window.
             *
             * \param uid
             */
            void setMainWindow(UUID const& uuid);

            /**
             * Calls the update method for all tracked windows.<br/>
             * This ensures that all system messages get properly dispatched and handled.
             *
             * \param[in] time The amount of time (in MS) to allow a window to digest and dispatch system messages.
             */
            void updateWindows(int64_t time);

        protected:

        private:

            std::shared_ptr<AWindow> openWindowWin32(WindowDescriptor const& descriptor);
            std::shared_ptr<AWindow> openWindowOSX(WindowDescriptor const& descriptor);
            std::shared_ptr<AWindow> openWindowLinux(WindowDescriptor const& descriptor);
            
            std::shared_ptr<AWindow> connectWindowWin32(WindowDescriptor const& descriptor, void* windowID);
            std::shared_ptr<AWindow> connectWindowOSX(WindowDescriptor const& descriptor, void* windowID);
            std::shared_ptr<AWindow> connectWindowLinux(WindowDescriptor const& descriptor, void* windowID);

            std::list<std::shared_ptr<AWindow>> m_Windows;
            std::shared_ptr<AWindow> m_MainWindow;
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