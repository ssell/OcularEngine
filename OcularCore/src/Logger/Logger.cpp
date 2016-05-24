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

#include "Logger\Logger.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Logger::Logger()
        {
        }

        Logger::~Logger()
        {
            m_Listeners.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Logger::registerListener(ILoggerListener* listener)
        {
            if(listener != nullptr)
            {
                m_Listeners.push_back(std::unique_ptr<ILoggerListener>(listener));
            }
        }

        void Logger::error(Exception& e)
        {
            m_IncompleteMessage.str("");
            m_IncompleteMessage << "[" << e.getFile() << "@" << e.getLine() << "] " << e.getMessage();
            
            log();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void Logger::log()
        {
            m_CurrentMessage.message = m_IncompleteMessage.str();
        
            // Send the message out to the listeners
            for(auto iter = m_Listeners.begin(); iter != m_Listeners.end(); ++iter)
            {
                (*iter)->onLogMessage(m_CurrentMessage);
            }
        }
    }
}