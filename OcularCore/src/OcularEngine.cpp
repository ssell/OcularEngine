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

#include "OcularEngine.hpp"
#include "Logger/ConsoleLoggerListener.hpp"
#include "Logger/VSConsoleLoggerListener.hpp"
#include "Events/EventPriority.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    //--------------------------------------------------------------------------------------
    // CONSTRUCTORS
    //--------------------------------------------------------------------------------------

    Engine& Engine::get()
    {
        static Engine instance;
        return instance;
    }

    Engine::Engine()
    {
        m_IsRunning = false;
    }

    Engine::~Engine()
    {
        m_IsRunning = false;
    }

    //--------------------------------------------------------------------------------------
    // PUBLIC METHODS
    //--------------------------------------------------------------------------------------

    bool Engine::initialize()
    {
        setupClock();
        setupLogger();
        setupUID();
        setupEvents();
        setupWindowManager();

        m_IsRunning = true;

        return true;
    }

    bool Engine::shutdown()
    {
        shutdownWindowManager();

        return true;
    }

    void Engine::run()
    {
        update();
        render();
    }

    std::shared_ptr<Core::Logger> Engine::Logger()
    {
        return m_Logger;
    }

    std::shared_ptr<Core::Clock> Engine::Clock()
    {
        return m_Clock;
    }

    std::shared_ptr<Core::EventManager> Engine::EventManager()
    {
        return m_EventManager;
    }

    std::shared_ptr<Core::WindowManager> Engine::WindowManager()
    {
        return m_WindowManager;
    }

    std::shared_ptr<Utils::UIDGenerator> Engine::UIDGenerator()
    {
        return m_UIDGenerator;
    }

    bool Engine::isRunning() const
    {
        return m_IsRunning;
    }

    //--------------------------------------------------------------------------------------
    // PROTECTED METHODS
    //--------------------------------------------------------------------------------------

    bool Engine::onEvent(std::shared_ptr<Core::AEvent> event)
    {
        if(event->getName().compare("ShutdownEvent") == 0)
        {
            m_IsRunning = false;
        }

        return true;
    }

    //--------------------------------------------------------------------------------------
    // PRIVATE METHODS
    //--------------------------------------------------------------------------------------

    void Engine::update()
    {
        m_WindowManager->updateWindows(OCULAR_SYS_MESSAGE_PROCESS_TIMEOUT);
        m_EventManager->processEvents(1000);
    }

    void Engine::render()
    {

    }

    void Engine::setupLogger()
    {
        m_Logger = std::make_shared<Core::Logger>();
        m_Logger->registerListener(new Core::ConsoleLoggerListener());
        m_Logger->registerListener(new Core::VSConsoleLoggerListener());
    }

    void Engine::setupClock()
    {
        m_Clock = std::make_shared<Core::Clock>();
    }

    void Engine::setupUID()
    {
        m_UIDGenerator = std::make_shared<Utils::UIDGenerator>();
    }

    void Engine::setupEvents()
    {
        m_EventManager = std::make_shared<Core::EventManager>();
        m_EventManager->registerListener(this, Core::EVENT_PRIORITY::MEDIUM);
    }

    void Engine::setupWindowManager()
    {
        m_WindowManager = std::make_shared<Core::WindowManager>();
    }

    void Engine::shutdownWindowManager()
    {
        m_WindowManager->destroyAllWindows();
    }
}