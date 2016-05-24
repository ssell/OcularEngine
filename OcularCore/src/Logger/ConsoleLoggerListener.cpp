/**
* Copyright 2014-2015 Steven T Sell (ssell@vertexfragment.com)
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

#include "Logger\ConsoleLoggerListener.hpp"
#include <iostream>

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ConsoleLoggerListener::ConsoleLoggerListener()
        {
        }

        ConsoleLoggerListener::~ConsoleLoggerListener()
        {
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ConsoleLoggerListener::onLogMessage(LoggerMessage const& message)
        {
            switch (message.channel)
            {
            case LoggerChannels::Debug:
                std::cout << "OcularEngine DEBUG: ";
                break;

            case LoggerChannels::Info:
                std::cout << "OcularEngine INFO:  ";
                break;

            case LoggerChannels::Warning:
                std::cout << "OcularEngine WARN:  ";
                break;

            case LoggerChannels::Error:
                std::cout << "OcularEngine ERROR: ";
                break;

            default:
                return;
            }

            std::cout << message.message << std::endl;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}