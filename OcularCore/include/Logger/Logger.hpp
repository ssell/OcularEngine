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

#include "ILoggerListener.hpp"

#include <list>
#include <sstream>
#include <memory>

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
        /**
         * \class Logger
         * \warning Currently NOT threadsafe
         */
        class Logger
        {
        public:

            Logger();
            ~Logger();

            void registerListener(ILoggerListener* listener);

            template<typename T, typename... U>
            void debug(T first, U... args);

            template<typename T, typename... U>
            void info(T first, U... args);

            template<typename T, typename... U>
            void warning(T first, U... args);

            template<typename T, typename... U>
            void error(T first, U... args);
        
        protected:

        private:

            template<typename T, typename... U>
            void log(T first, U... last);
            void log();

            //--------------------------------------------

            std::stringstream m_IncompleteMessage;
            LoggerMessage m_CurrentMessage;

            std::list<std::unique_ptr<ILoggerListener>> m_Listeners;
        };

#include "..\..\src\Logger\Logger.tpp"
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif