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

#include "Logger.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    //--------------------------------------------------------------------------------------
    // CONSTRUCTORS
    //--------------------------------------------------------------------------------------

    Logger::Logger()
    {
    }

    Logger::~Logger()
    {
    
    }

    //--------------------------------------------------------------------------------------
    // PUBLIC METHODS
    //--------------------------------------------------------------------------------------

    template<typename T, typename... U>
    void Logger::debug(T first, U... last) 
    {
        m_CurrentMessage.channel = LOGGER_CHANNEL::DEBUG;
        m_IncompleteMessage.str(std::string());
        m_IncompleteMessage << first;
        log(last...);
    }

    template<typename T, typename... U>
    void Logger::info(T first, U... last) 
    {
        m_CurrentMessage.channel = LOGGER_CHANNEL::INFO;
        m_IncompleteMessage.str(std::string());
        m_IncompleteMessage << first;
        log(last...);
    }

    template<typename T, typename... U>
    void Logger::warning(T first, U... last) 
    {
        m_CurrentMessage.channel = LOGGER_CHANNEL::WARNING;
        m_IncompleteMessage.str(std::string());
        m_IncompleteMessage << first;
        log(last...);
    }

    template<typename T, typename... U>
    void Logger::error(T first, U... last) 
    {
        m_CurrentMessage.channel = LOGGER_CHANNEL::ERROR;
        m_IncompleteMessage.str(std::string());
        m_IncompleteMessage << first;
        log(last...);
    }

    //--------------------------------------------------------------------------------------
    // PROTECTED METHODS
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // PRIVATE METHODS
    //--------------------------------------------------------------------------------------

    template<typename T, typename... U>
    void Logger::log(T first, U... last)
    {
        m_IncompleteMessage << first;
        log(last...);
    }

    void Logger::log()
    {
        m_CurrentMessage.message = m_IncompleteMessage.str();
        // Distribute message...
    }
}