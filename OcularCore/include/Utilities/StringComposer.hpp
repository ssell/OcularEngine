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

#pragma once
#ifndef __H__OCULAR_UTILS_STRING_COMPOSER__H__
#define __H__OCULAR_UTILS_STRING_COMPOSER__H__

#include <string>
#include <sstream>
#include <mutex>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Utils
     * @{
     */
    namespace Utils
    {
        /**
         * \class StringComposer
         *
         * Builds a string from a collection of parameters. <br/>
         *
         * Example: <br/>
         *
         *     StringComposer("This ", "has ", 4, " parts.");
         *     -> "This has 4 parts."
         *
         * Though in a lot of ways similar to a std::stringstream (which
         * the composer is built on-top of), it has the benefit of being
         * able to be utilized in-line. <br/>
         *
         * Example: <br/>
         *
         *     Foo* foo = new Foo(STRING_COMPOSER(msgA, msgB, msgC));
         *
         */
        class StringComposer
        {
        public:

            StringComposer() 
                : m_IncompleteString(), m_Mutex()
            { 
            
            }

            ~StringComposer() { }

            template<typename T, typename... U>
            std::string compose(T first, U... args)
            {
                std::string result;

                m_Mutex.lock();

                m_IncompleteString.str(std::string());
                m_IncompleteString << first;

                internalCompose(args...);
                result = m_IncompleteString.str();

                m_Mutex.unlock();

                return result;
            }

        protected:

        private:

            template<typename T, typename... U>
            void internalCompose(T first, U... last)
            {
                m_IncompleteString << first;
                internalCompose(last...);
            }

            static void internalCompose()
            {
                // Empty, but required as it is called when
                // there are no more arguments.
            }

            std::stringstream m_IncompleteString;
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

#define OCULAR_STRING_COMPOSER Ocular::Utils::StringComposer().compose

//------------------------------------------------------------------------------------------

#endif