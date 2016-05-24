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

#include "Common.hpp"
#include "Logger\VSConsoleLoggerListener.hpp"

#include <sstream>

#ifdef OCULAR_WINDOWS
#include <Windows.h>
#endif

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        VSConsoleLoggerListener::VSConsoleLoggerListener()
        {
        }

        VSConsoleLoggerListener::~VSConsoleLoggerListener()
        {
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void VSConsoleLoggerListener::onLogMessage(LoggerMessage const& message)
        {
    #ifdef OCULAR_WINDOWS
            std::stringstream sstream;
            switch (message.channel)
            {
            case LoggerChannels::Debug:
                sstream << "OcularEngine DEBUG: ";
                break;

            case LoggerChannels::Info:
                sstream << "OcularEngine INFO:  ";
                break;

            case LoggerChannels::Warning:
                sstream << "OcularEngine WARN:  ";
                break;

            case LoggerChannels::Error:
                sstream << "OcularEngine ERROR: ";
                break;

            default:
                return;
            }

            sstream << message.message << std::endl;
            OutputDebugString(sstream.str().c_str());
    #endif
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}