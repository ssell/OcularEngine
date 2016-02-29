/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_CORE_UTILS_STRING_OPERATIONS__H__
#define __H__OCULAR_CORE_UTILS_STRING_OPERATIONS__H__

#include "VoidCast.hpp"

#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <functional>
#include <unordered_map>

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
         * \class String
         * \brief Collection of helper string-related utilities
         */
        class String
        {
        public:

            String();
            ~String();

            //------------------------------------------------------------------------------
            // General String Operations
            //------------------------------------------------------------------------------

            /**
             * Converts a mixed-case string to all lower-case
             *
             * \param[in] str String to convert
             * \return Converted string
             */
            static std::string ToLower(std::string const& str);

            /**
             * Converts a mixed-case string to all upper-case
             *
             * \param[in] str String to convert
             * \return Converted string
             */
            static std::string ToUpper(std::string const& str);

            /**
             * \param[in] strA
             * \param[in] strB
             * \param[in] ignoreCase If true, performs a case-insensitive comparision on the strings.
             * 
             * \return TRUE if the strings are equal.
             */
            static bool IsEqual(std::string const& strA, std::string const& strB, bool ignoreCase = false);

            /**
             * Converts a Win32 specific system error DWORD into a human readable string.
             *
             * \param[in] error The DWORD error message
             * \return String representation of the error
             */
            static std::string FormatWindowsError(unsigned long error);

            /**
             * Supports sizes up to tebibytes in size.
             *
             * Example:
             *
             *     bytes = 4293386240
             *     "3.99853 GiB (4293386240 B)"
             *
             * \param[in] bytes
             * \return Formatted string
             */
            static std::string FormatBytes(uint64_t bytes);

            /**
             * Converts an integer type to a hex string. <br/>
             * Source: http://stackoverflow.com/a/5100745/735425
             */
            template<typename T>
            static typename std::enable_if<std::is_arithmetic<T>::value, std::string>::type FormatHex(T const x)
            {
                std::stringstream sstream;
                sstream << "0x" << std::setfill('0') << std::setw(sizeof(T) * static_cast<T>(2)) << std::hex << x;

                return sstream.str();
            }

            //------------------------------------------------------------------------------
            // To/From Methods and Helpers
            //------------------------------------------------------------------------------

            // The following methods can not be static like the rest. If we make the maps static, then
            // their is a very strong likelihood that some other static initializer will call these methods,
            // particularly the registers, before the String static initializers can act. This leads to
            // a crash when performing a search in the uninitialized map and why this class was added
            // to the main engine class as OcularString.

            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, std::string>::type toString(T const& data)
            {
                std::string result;

                const std::string tStr = TypeName<T>::name;
                auto find = m_ToFunctions.find(tStr);

                if(find != m_ToFunctions.end())
                {
                    result = find->second(void_cast<T>(data));
                }

                return result;
            }

            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, T>::type fromString(std::string const& str)
            {
                T result;

                const std::string tStr = TypeName<T>::name;
                auto find = m_FromFunctions.find(tStr);

                if(find != m_FromFunctions.end())
                {
                    result = void_cast<T>(find->second(str));
                }

                return result;
            }

            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, void>::type registerToString(std::function<std::string(void*)> func)
            {
                const std::string tStr = TypeName<T>::name;
                auto find = m_ToFunctions.find(tStr);

                if(find == m_ToFunctions.end())
                {
                    m_ToFunctions.insert({tStr, func});
                }
            }

            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, void>::type registerFromString(std::function<void*(std::string const&)> func)
            {
                const std::string tStr = TypeName<T>::name;
                auto find = m_FromFunctions.find(tStr);

                if(find == m_FromFunctions.end())
                {
                    m_FromFunctions.insert({tStr, func});
                }
            }

        protected:

        private:

            std::unordered_map<std::string, std::function<std::string(void*)>> m_ToFunctions;
            std::unordered_map<std::string, std::function<void*(std::string const&)>> m_FromFunctions;
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