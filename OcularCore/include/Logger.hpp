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

#pragma once
#ifndef __H__OCULAR_LOGGER__H__
#define __H__OCULAR_LOGGER__H__

#include <sstream>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular 
{
    enum class LOGGER_CHANNEL
    {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    /**
     * \class Logger
     * \warning Currently NOT threadsafe
     */
    struct LoggerMessage
    {
        std::string message;
        LOGGER_CHANNEL channel;
    };

    /**
     * \class Logger
     */
    class Logger
    {
    public:

        Logger();
        ~Logger();

        template<typename T, typename... U>
        void debug(T first, U... last);

        template<typename T, typename... U>
        void info(T first, U... last);

        template<typename T, typename... U>
        void warning(T first, U... last);

        template<typename T, typename... U>
        void error(T first, U... last);
        
    protected:

    private:

        template<typename T, typename... U>
        void log(T first, U... last);
        void log();

        //--------------------------------------------

        std::stringstream m_IncompleteMessage;
        LoggerMessage m_CurrentMessage;
    };
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif