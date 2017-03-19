/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#include "Exceptions/Exception.hpp"

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
             * Registers a new logger listener with the Logger. <br/>
             * The listener will receive all messages sent to this Logger instance.
             *
             * \param[in] listener
             */
            void registerListener(ILoggerListener* listener);

            /**
             * Sends a message through the debug logger channel.
             */
            template<typename T, typename... U>
            void debug(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LoggerChannels::Debug;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
             * Sends a message through the info logger channel.
             *
             * This should be used for generally useful information, such as
             * services stops and starts, that you want to always be available
             * but don't typically care about under normal circumstances.
             */
            template<typename T, typename... U>
            void info(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LoggerChannels::Info;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
             * Sends a message through the warning logger channel.
             *
             * This should be used for anything that can potentially cause
             * application oddities, but for which there is a system in place
             * for automatic recovery. For example, this could be missing
             * input to a method but the operation can still continue.
             */
            template<typename T, typename... U>
            void warning(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LoggerChannels::Warning;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
             * Sends a message through the error logger channel.
             *
             * This should be used for any error that is fatal to the operation
             * but not the service or application as a whole. An example of this
             * would be if a file, that is necessary for a function, is not found.
             */
            template<typename T, typename... U>
            void error(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LoggerChannels::Error;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }

            /**
             * Sends an exception error through the error logger channel.
             */
            void error(Exception& e);

            /**
             * Sends a message through the fatal logger channel.
             *
             * This should be used for any error that is fatal to the application
             * or service as a whole. A fatal error will cause the program to terminate.
             *
             * Typically, there should be no message following a fatal message as 
             * the program will have ceased.
             */
            template<typename T, typename... U>
            void fatal(T first, U... args)
            {
                m_Mutex.lock();

                m_CurrentMessage.channel = LoggerChannels::Fatal;
                m_IncompleteMessage.str(std::string());
                m_IncompleteMessage << first;
                log(args...);

                m_Mutex.unlock();
            }
        
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