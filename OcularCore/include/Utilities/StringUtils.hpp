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

            /**
             * Attempts to convert the provided object to a string.
             *
             * In order to perform the conversion, an appropriate 'ToString' method must have been
             * registered (via registerToString). If no matching function has been registered, then
             * an empty string is returned.
             *
             * See also the bool return variant of this method.
             *
             * \param[in] data Object to convert to a string
             * \return String representation of the object, or an empty string if no conversion was available.
             */
            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, std::string>::type toString(T const& data) const
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

            /**
             * Attempts to convert the provided object to a string.
             *
             * In order to perform the conversion, an appropriate 'ToString' method must have been
             * registered (via registerToString). If no matching function has been registered, then
             * FALSE is returned.
             *
             * \param[in]  data Object to convert to a string
             * \param[out] str
             *
             * \return Returns TRUE if a matching 'ToString' function was found, else FALSE.
             */
            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, bool>::type toString(T const& data, std::string& str) const
            {
                bool result = false;

                const std::string tStr = TypeName<T>::name;
                auto find = m_ToFunctions.find(tStr);

                if(find != m_ToFunctions.end())
                {
                    str = find->second(void_cast<T>(data));
                    result = true;
                }

                return result;
            }

            /**
             * Attempts to convert the provided raw data to a string.
             *
             * In order to perform the conversion, an appropriate 'ToString' method must have been
             * registered (via registerToString) for the provided type. If no matching function has
             * been registered, then an empty string is returned.
             *
             * \param[in] type String representation of the data type. See OCULAR_TYPE macro and/or Utils::TypeName template. Case-sensitive.
             * \param[in] data Data to be converted to string
             * 
             * \return String representation of the object, or an empty string if no conversion was available.
             */
            std::string toString(std::string const& type, void* data) const
            {
                std::string result;

                if(data)
                {
                    auto find = m_ToFunctions.find(type);

                    if(find != m_ToFunctions.end())
                    {
                        result = find->second(data);
                    }
                }

                return result;
            }

            /**
             * Attempts to convert the provided object to a string.
             *
             * In order to perform the conversion, an appropriate 'ToString' method must have been
             * registered (via registerToString). If no matching function has been registered, then
             * FALSE is returned.
             *
             * \param[in]  type String representation of the data type. See OCULAR_TYPE macro and/or Utils::TypeName template. Case-sensitive.
             * \param[in]  data Data to be converted to string
             * \param[out] str
             *
             * \return Returns TRUE if a matching 'ToString' function was found, else returns FALSE.
             */
            bool toString(std::string const& type, void* data, std::string& str) const
            {
                bool result = false;

                if(data)
                {
                    auto find = m_ToFunctions.find(type);

                    if(find != m_ToFunctions.end())
                    {
                        str = find->second(data);
                        result = true;
                    }
                }

                return result;
            }

            /**
             * Attempts to create an object of the specified type from the provided string.
             *
             * In order to perform the conversion, an appropriate 'FromString' method must have been
             * registered (via registerFromString). If no matching function has been registered, then
             * a default object of the type is returned.
             *
             * See also the bool return variant of this method.
             *
             * \param[in] value  String representation of the value. Must be castable to the specified type.
             * \return Object resulting form the string. Returns a default constructed object of the type if no function was found.
             */
            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, T>::type fromString(std::string const& value) const
            {
                T result;

                const std::string tStr = TypeName<T>::name;
                auto find = m_FromFunctions.find(tStr);

                if(find != m_FromFunctions.end())
                {
                    result = void_cast<T>(find->second(value));
                }

                return result;
            }

            /**
             * Attempts to create an object of the specified type from the provided string.
             *
             * In order to perform the conversion, an appropriate 'FromString' method must have been
             * registered (via registerFromString). If no matching function has been registered, then
             * FALSE is returned.
             *
             * \param[in]  value  String representation of the value. Must be castable to the specified type.
             * \param[out] object Object to be set based on the input string
             *
             * \return Returns TRUE if a matching 'FromString' function was found, else returns FALSE.
             */
            template<typename T>
            typename std::enable_if<!std::is_pointer<T>::value, bool>::type fromString(std::string const& value, T& object) const
            {
                bool result = false;
                auto find = m_FromFunctions.find(value);

                if(find != m_FromFunctions.end())
                {
                    object = void_cast<T>(find->second(value));
                    result = true;
                }

                return result;
            }

            /**
             * Attempts to modify the data pointed to by the object parameter so that it matches the 
             * conversion performed on the specified string for the given type.
             *
             * Note that this method is potentially dangerous if improper parameters are supplied. 
             * As such, it is recommended to use a different variation of the fromString method if
             * it is at all possible.
             *
             * If this method is the only option, then the following conditions must be met:
             *
             *     - object points to the address of an object of the specified type
             *     - size is the proper size for given type
             *
             * Example:
             *
             *     //-----------------------------------------------------
             *     // Good
             *     //-----------------------------------------------------
             *
             *     float x = 5.0f;
             *     void* xvp = void_cast<float*>(&x);
             *
             *     OcularString->fromString(TypeName<float>::name, "8.0", xvp, sizeof(float)); 
             *     // x == 8.0
             *
             *     //-----------------------------------------------------
             *     // Bad (crash)
             *     //-----------------------------------------------------
             *
             *     float y = 5.0f;
             *     void* yvp = void_cast<float>(y);
             *
             *     OcularString->fromString(TypeName<float>::name, "8.0", yvp, sizeof(float));
             *     // crash
             *
             *     //-----------------------------------------------------
             *     // Bad (crash)
             *     //-----------------------------------------------------
             *
             *     float z = 5.0f;
             *     float zvp = void_cast<float*>(&z);
             *
             *     OcularString->fromString(TypeName<float>::name, "8.0", zvp, sizeof(double));
             *     // crash
             *
             *     //-----------------------------------------------------
             *     // Bad (best case no action taken)
             *     //-----------------------------------------------------
             *
             *     float w = 5.0f;
             *     float wvp = void_cast<float*>(&z);
             *
             *     OcularString->fromString("floatt", "8.0", wvp, sizeof(float));
             *     // crash or no action depending on if there is a mapping for 'floatt' type conversion
             *
             *     //-----------------------------------------------------
             *     // Bad (best case default value)
             *     //-----------------------------------------------------
             *
             *     float v = 5.0f;
             *     float vvp = void_cast<float*>(&z);
             *
             *     OcularString->fromString(TypeName<float>::name, "abcdef", vvp, sizeof(float));
             *     // crash or default value set depending on implementation of the registered 'float' conversion function
             *
             * \param[in]  type    String representation of the type. See Utils::TypeName and OCULAR_TYPE macro
             * \param[in]  value   String representation of the value. Must be castable to the specified type.
             * \param[out] object  Raw object data pointer where the converted value will be placed
             * \param[in]  size    Size of the data type 
             * \param[in]  trivial Is it a trivial data type? See std::is_trivial
             *
             * \return Returns TRUE if a matching 'FromString' function was found, else returns FALSE.
             */
            bool fromString(std::string const& type, std::string const& value, void* object, uint32_t const& size, bool isTrivial = true)
            {
                bool result = false;

                if(object)
                {
                    auto find = m_FromFunctions.find(type);

                    if(find != m_FromFunctions.end())
                    {
                        void* cast = find->second(value);

                        if(isTrivial)
                        {
                            memcpy(object, &cast, size);
                        }
                        else
                        {
                            memcpy(object, cast, size);
                        }

                        result = true;
                    }
                }

                return result;
            }

            /**
             * Registers a function to be called when the specified type is requested to be converted.
             *
             * For more information, see the OCULAR_REGISTER_TO_STRING helper macro defined in 'Utilities/StringRegistrar.hpp'
             */
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

            /**
             * Registers a function to be called when the specified type is requested to be converted.
             *
             * For more information, see the OCULAR_REGISTER_FROM_STRING helper macro defined in 'Utilities/StringRegistrar.hpp'
             */
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