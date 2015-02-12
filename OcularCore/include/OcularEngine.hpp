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

#ifndef __H__OCULAR_ENGINE__H__
#define __H__OCULAR_ENGINE__H__

#include "Common.hpp"

#include "Logger/Logger.hpp"
#include "Time/Clock.hpp"
#include "Events/EventManager.hpp"
#include "Renderer/Window/WindowManager.hpp"
#include "Utilities/UIDGenerator.hpp"
#include "Resources/ResourceManager.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    //--------------------------------------------------------------------------------------
    // Forward Declarations

    namespace Core
    {
        class Clock;
        class EventManager;
        class Logger;
        class ResourceManager;
        class WindowManager;
    }

    namespace Utils
    {
        class UIDGenerator;
    }

    //--------------------------------------------------------------------------------------

    /**
     * \class Engine
     */
    class Engine : public Core::AEventListener
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
         * \note Engine must be initialized before any other action is taken
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
         * \return TRUE if the engine is running.
         */
        bool isRunning() const;

        /**
         *
         */
        void run();

        //----------------------------------------------------------------------------------
        // Core Subsystem Retrieval

        /**
         * \return Reference to the primary Logger
         */
        std::shared_ptr<Core::Logger> Logger();

        /**
         * \return Reference to the primary Clock
         */
        std::shared_ptr<Core::Clock> Clock();

        /**
         * \return Reference to the primary EventManager
         */
        std::shared_ptr<Core::EventManager> EventManager();

        /**
         * \return Reference to the primary WindowManager
         */
        std::shared_ptr<Core::WindowManager> WindowManager();

        /**
         * \return Reference to the primary UID Generator
         */
        std::shared_ptr<Utils::UIDGenerator> UIDGenerator();

        /**
         * \return Reference to the primary ResourceManager
         */
        std::shared_ptr<Core::ResourceManager> ResourceManager();

        //----------------------------------------------------------------------------------
        
    protected:

        virtual bool onEvent(std::shared_ptr<Core::AEvent> event);

    private:

        Engine();
        Engine(Engine const&);
        void operator=(Engine const&);

        // Running

        void update();
        void render();

        // Setup

        void setupLogger();
        void setupClock();
        void setupUID();
        void setupEvents();
        void setupWindowManager();
        void setupResourceManager();

        void shutdownWindowManager();
        
        //--------------------------------------------

        std::shared_ptr<Core::Clock>           m_Clock;
        std::shared_ptr<Core::EventManager>    m_EventManager;
        std::shared_ptr<Core::Logger>          m_Logger;
        std::shared_ptr<Core::ResourceManager> m_ResourceManager;
        std::shared_ptr<Core::WindowManager>   m_WindowManager;
        std::shared_ptr<Utils::UIDGenerator>   m_UIDGenerator;

        bool m_IsRunning;
    };
}
/**
 * @} End of Doxygen Groups
 */

#define OcularEngine Ocular::Engine::get()

#endif