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
#ifndef __H__OCULAR_RENDERER_WINDOW_MANAGER__H__
#define __H__OCULAR_RENDERER_WINDOW_MANAGER__H__

#include "WindowDisplay.hpp"
#include "WindowDescriptor.hpp"

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
            std::shared_ptr<AWindow> openWindow(WindowDescriptor descriptor);

            /**
             * Destroys the Window with the specified UID.
             * \param uid
             */
            void closeWindow(unsigned long long uid);

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
            unsigned getNumWindows() const;
        
            /**
             * Returns a pointer to the Window with the specified UID.<br/><br/>
             *
             * The returned pointer should not be destroyed as object management
             * is performed by the WindowManager to which the Window belongs.
             *
             * \param uid
             * \return A pointer to the window. If nullptr, then no window matches the specified UID.
             */
            std::shared_ptr<AWindow> getWindow(unsigned long long uid);

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
            void setMainWindow(unsigned long long uid);

            /**
             * Calls the update method for all tracked windows.<br/>
             * This ensures that all system messages get properly dispatched and handled.
             *
             * \param[in] time The amount of time (in MS) to allow a window to digest and dispatch system messages.
             */
            void updateWindows(long long time);

        protected:

        private:

            std::shared_ptr<AWindow> openWindowWin32(WindowDescriptor descriptor);
            std::shared_ptr<AWindow> openWindowOSX(WindowDescriptor descriptor);
            std::shared_ptr<AWindow> openWindowLinux(WindowDescriptor descriptor);

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