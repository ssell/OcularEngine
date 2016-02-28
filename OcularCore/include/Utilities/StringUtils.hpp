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

            template<typename T>
            static typename std::enable_if<!std::is_pointer<T>::value, std::string>::type ToString(T const& data)
            {
                std::string result;
                auto find = m_ToFunctions.find(TypeName<T>::name);

                if(find != m_ToFunctions.end())
                {
                    result = find->second(void_cast<T>(data));
                }

                return result;
            }

            template<typename T>
            static typename std::enable_if<!std::is_pointer<T>::value, T>::type FromString(std::string const& str)
            {
                T result;
                auto find = m_FromFunctions.find(TypeName<T>::name);

                if(find != m_FromFunctions.end())
                {
                    result = void_cast<T>(find->second(str));
                }

                return result;
            }

            template<typename T>
            static typename std::enable_if<!std::is_pointer<T>::value, void>::type RegisterToString(std::function<std::string(void*)> func)
            {
                auto find = m_ToFunctions.find(TypeName<T>::name);

                if(find == m_ToFunctions.end())
                {
                    m_ToFunctions.insert({TypeName<T>::name, func});
                }
            }

            template<typename T>
            static typename std::enable_if<!std::is_pointer<T>::value, void>::type RegisterFromString(std::function<void*(std::string const&)> func)
            {
                auto find = m_FromFunctions.find(TypeName<T>::name);

                if(find == m_FromFunctions.end())
                {
                    m_FromFunctions.insert({TypeName<T>::name, func});
                }
            }

        protected:

        private:

            static std::unordered_map<std::string, std::function<std::string(void*)>> m_ToFunctions;
            static std::unordered_map<std::string, std::function<void*(std::string const&)>> m_FromFunctions;
        };

        template<typename T>
        class ToStringRegistrar
        {
        public:

            ToStringRegistrar(std::function<std::string(void*)> func)
            {
                String::RegisterToString<T>(func);
            }
        };

        template<typename T>
        class FromStringRegistrar
        {
        public:

            FromStringRegistrar(std::function<void*(std::string const&)> func)
            {
                String::RegisterFromString<T>(func);
            }
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

/**
 * Helper macro to assist in registering ToString functions with the Ocular::Utils::String class.
 * Can be envoked anywhere, including globally (outside of a function).
 *
 * Example:
 *
 *     OCULAR_REGISTER_TO_STRING(float, OCULAR_TO_STRING_LAMBDA { return std::to_string(void_cast<float>(raw)); });
 *
 * This registers the above lambda function (which makes use of the void_cast helper to transform the raw void*
 * into a float) to be used whenever Ocular::Utils::String::ToString<float>() is called.
 */
#define OCULAR_REGISTER_TO_STRING(X,Y) Ocular::Utils::ToStringRegistrar<X> OCULAR_INTERNAL_ToStringRegister(Y)

/**
 * Helper macro to assist in registering FromString functions with the Ocular::Utils::String class.
 * Can be envoked anywhere, including globally (outside of a function).
 *
 * Example:
 *
 *     OCULAR_REGISTER_FROM_STRING(float, OCULAR_FROM_STRING_LAMBDA { return void_cast<float>(std::stof(string, nullptr)); });
 *
 * This registers the above lambda function (which makes use of the void_cast helper to transform the raw float
 * into a raw void*) to be used whenever Ocular::Utils::String::FromString<float>() is called.
 */
#define OCULAR_REGISTER_FROM_STRING(X,Y) Ocular::Utils::FromStringRegistrar<X> OCULAR_INTERNAL_FromStringRegister(Y)

/**
 * Helper macro to make registering ToString lambda functions easier.
 *
 *     OCULAR_REGISTER_TO_STRING(float, [](void* raw)->std::string { ... });
 *
 * to
 *
 *     OCULAR_REGISTER_TO_STRING(float, OCULAR_TO_STRING_LAMBDA { ... });
 */
#define OCULAR_TO_STRING_LAMBDA [](void* raw)->std::string

/**
 * Helper macro to make registering FromString lambda functions easier.
 *
 *     OCULAR_REGISTER_FROM_STRING(float, [](std::string const& str)->void* { ... });
 *
 * to
 *
 *     OCULAR_REGISTER_FROM_STRING(float, OCULAR_FROM_STRING_LAMBDA { ... });
 */
#define OCULAR_FROM_STRING_LAMBDA [](std::string const& str)->void*

//------------------------------------------------------------------------------------------

#endif