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
#include "Exception.hpp"

#include <list>
#include <sstream>
#include <memory>
#include <mutex>

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

            /**
            *
            */
            Logger();

            /**
            *
            */
            ~Logger();

            /**
            *
            */
            void registerListener(ILoggerListener* listener);

            /**
            *
            */
            template<typename T, typename... U>
            void debug(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LOGGER_CHANNELS::DEBUG_CHANNEL;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
            *
            */
            template<typename T, typename... U>
            void info(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LOGGER_CHANNELS::INFO_CHANNEL;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
            *
            */
            template<typename T, typename... U>
            void warning(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LOGGER_CHANNELS::WARNING_CHANNEL;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
            *
            */
            template<typename T, typename... U>
            void error(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LOGGER_CHANNELS::ERROR_CHANNEL;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
            *
            */
            void error(Exception& e);
        
        protected:

        private:

            /**
            *
            */
            template<typename T, typename... U>
            void log(T first, U... last)
            {
                m_IncompleteMessage << first;
                log(last...);
            }

            /**
            *
            */
            void log();

            //--------------------------------------------

            std::stringstream m_IncompleteMessage;
            LoggerMessage m_CurrentMessage;

            std::list<std::unique_ptr<ILoggerListener>> m_Listeners;

            std::mutex m_Mutex;

        };
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