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

#ifndef __H__OCULAR_ENGINE__H__
#define __H__OCULAR_ENGINE__H__

#include "Common.hpp"
#include "Logger\Logger.hpp"
#include "Time\Clock.hpp"
#include "Renderer\Window\WindowManager.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
        * \class Engine
        */
    class Engine
    {
    public:

        static Engine& get();
        ~Engine();

        /**
         * Initializes all of the core objects and subsystems of the Ocular Engine.
         * These include:<br/><br/>
         *
         * <ul>
         *     <li>Clock</li>
         *     <li>Logger</li>
         *     <li>WindowManager</li>
         * </ul>
         *
         * \return TRUE if intiailized without any issues.
         */
        bool initialize();

        /**
         * Safely destroys and removes all subsystems used by the Ocular Engine.
         *
         * \return TRUE is shutdown without any issues.
         */
        bool shutdown();

        /**
         * \return Reference to the primary Logger
         */
        std::shared_ptr<Core::Logger> Logger();

        /**
         * \return Reference to the primary Clock
         */
        std::shared_ptr<Core::Clock> Clock();

        /**
         * \return Reference to the primary WindowManager
         */
        std::shared_ptr<Core::WindowManager> WindowManager();
        
    protected:

    private:

        Engine();
        Engine(Engine const&);
        void operator=(Engine const&);

        void setupLogger();
        void setupClock();
        void setupWindowManager();

        void shutdownWindowManager();
        
        //--------------------------------------------

        std::shared_ptr<Core::Logger> m_Logger;
        std::shared_ptr<Core::Clock> m_Clock;
        std::shared_ptr<Core::WindowManager> m_WindowManager;
    };
}
/**
 * @} End of Doxygen Groups
 */

#define OcularEngine Ocular::Engine::get()

#endif