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

#include "OcularEngine.hpp"

#include "Logger/ConsoleLoggerListener.hpp"
#include "Logger/VSConsoleLoggerListener.hpp"
#include "Priority.hpp"
#include "SystemInfo.hpp"

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
        m_Logger          = std::make_shared<Core::Logger>();
        m_Clock           = std::make_shared<Core::Clock>();
        m_HashGenerator   = std::make_shared<Utils::HashGenerator>();
        m_EventManager    = std::make_shared<Core::EventManager>();
        m_InputHandler    = std::make_shared<Core::InputHandler>();
        m_ResourceManager = std::make_shared<Core::ResourceManager>();
        m_SceneManager    = std::make_shared<Core::SceneManager>();
        m_WindowManager   = std::make_shared<Core::WindowManager>();
        m_Profiler        = std::make_shared<Core::Profiler>();

        m_IsRunning = false;
    }

    Engine::~Engine()
    {
        m_IsRunning = false;

        m_InputHandler    = nullptr;
        m_Logger          = nullptr;
        m_Clock           = nullptr;
        m_HashGenerator   = nullptr;
        m_EventManager    = nullptr;
        m_ResourceManager = nullptr;
        m_SceneManager    = nullptr;
        m_WindowManager   = nullptr;
        m_Profiler        = nullptr;
    }

    //--------------------------------------------------------------------------------------
    // PUBLIC METHODS
    //--------------------------------------------------------------------------------------

    bool Engine::initialize()
    {
        setupClock();
        setupLogger();
        setupEvents();
        setupWindowManager();
        setupResourceManager();
        setupSceneManager();
        
        Core::SystemInfo::initialize();

        m_IsRunning = true;

        return true;
    }

    bool Engine::shutdown()
    {
        shutdownWindowManager();

        return true;
    }

    bool Engine::run()
    {
        if(m_IsRunning)
        {
            update();
            render();
        }

        return m_IsRunning;
    }

    std::shared_ptr<Core::Logger> Engine::Logger() const
    {
        return m_Logger;
    }

    std::shared_ptr<Core::Clock> Engine::Clock() const
    {
        return m_Clock;
    }

    std::shared_ptr<Core::EventManager> Engine::EventManager() const
    {
        return m_EventManager;
    }

    std::shared_ptr<Core::InputHandler> Engine::Input() const
    {
        return m_InputHandler;
    }

    std::shared_ptr<Core::WindowManager> Engine::WindowManager() const
    {
        return m_WindowManager;
    }

    std::shared_ptr<Utils::HashGenerator> Engine::HashGenerator() const
    {
        return m_HashGenerator;
    }

    std::shared_ptr<Core::ResourceManager> Engine::ResourceManager() const
    {
        return m_ResourceManager;
    }

    std::shared_ptr<Core::SceneManager> Engine::SceneManager() const
    {
        return m_SceneManager;
    }

    std::shared_ptr<Core::Profiler> Engine::Profiler() const
    {
        return m_Profiler;
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
        m_Clock->tick();
        Core::SystemInfo::refresh();

        m_WindowManager->updateWindows(OCULAR_SYS_MESSAGE_PROCESS_TIMEOUT);
        m_InputHandler->update();
        m_EventManager->processEvents(1000);
        m_SceneManager->update();
    }

    void Engine::render()
    {
        if(m_SceneManager)
        {
            m_SceneManager->render();
        }
    }

    void Engine::setupLogger()
    {
        m_Logger->registerListener(new Core::ConsoleLoggerListener());
        m_Logger->registerListener(new Core::VSConsoleLoggerListener());
    }

    void Engine::setupClock()
    {
        
    }

    void Engine::setupEvents()
    {
        m_EventManager->registerListener(this, Core::Priority::Medium);
    }

    void Engine::setupResourceManager()
    {
        
    }

    void Engine::setupSceneManager()
    {

    }

    void Engine::setupWindowManager()
    {
        
    }

    void Engine::shutdownWindowManager()
    {
        m_WindowManager->closeAllWindows();
    }
}