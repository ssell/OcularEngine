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

#include "Math/Vector4.hpp"

#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Math
    {
        class Matrix3x3;
        class Matrix4x4;
    }

    /**
     * \addtogroup Utils
     * @{
     */
    namespace Utils
    {
        /**
         * \addtogroup StringUtils
         * @{
         */
        namespace StringUtils
        {
            /**
             * Converts a mixed-case string to all lower-case
             *
             * \param[in] str String to convert
             * \return Converted string
             */
            std::string toLower(std::string const& str);

            /**
             * Converts a mixed-case string to all upper-case
             *
             * \param[in] str String to convert
             * \return Converted string
             */
            std::string toUpper(std::string const& str);

            /**
             * \param[in] strA
             * \param[in] strB
             * \param[in] ignoreCase If true, performs a case-insensitive comparision on the strings.
             * 
             * \return TRUE if the strings are equal.
             */
            bool isEqual(std::string const& strA, std::string const& strB, bool ignoreCase = false);

            /**
             * Converts a Win32 specific system error DWORD into a human readable string.
             *
             * \param[in] error The DWORD error message
             * \return String representation of the error
             */
            std::string windowsErrorToString(unsigned long error);

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
            std::string bytesToString(uint64_t bytes);

            /**
             * Converts a string to a single float. 
             * Input is expected as one of the following forms:
             *
             *     "1"
             *     "1.0"
             *     "1.0f"
             *     "1.0F"
             *
             * \param[in]  string Source string to be converted
             * \param[out] value  Float retrieved from the string
             *
             * \return TRUE if successfully converted the string.
             */
            bool stringToFloat(std::string const& string, float& value);

            /**
             * Converts a string to a Vector4f.
             * Input is expected as whitespace-separated floats.
             *
             *     # # # #
             *
             * Where '#' is a properly formatted float (see stringToFloat).
             *
             * \param[in]  string Source string to be converted
             * \param[out] value  Vector4f retrieved from the string
             *
             * \return TRUE if successfully converted the string.
             */
            bool stringToVector(std::string const& string, Math::Vector4f& value);

            /**
             * Converts a string to a Matrix3x3.
             * Input is expected as whitespace-separated floats.
             *
             * Examples:
             *
             *     # # #
             *     # # #
             *     # # #
             *
             *     # # #   # # #   # # #
             *
             * Where '#' is a properly formatted float (see stringToFloat).
             * Spaces are optional.
             *
             * \param[in]  string Source string to be converted
             * \param[out] value  Matrix3x3 retrieved from the string
             *
             * \return TRUE if successfully converted the string.
             */
            bool stringToMatrix(std::string const& string, Math::Matrix3x3& value);

            /**
             * Converts a string to a Matrix4x4.
             * Input is expected as whitespace-separated floats.
             *
             * Examples:
             *
             *     # # # #
             *     # # # # 
             *     # # # # 
             *     # # # # 
             *
             *     # # # #   # # # #   # # # #   # # # # 
             *
             * Where '#' is a properly formatted float (see stringToFloat).
             *
             * \param[in]  string Source string to be converted
             * \param[out] value  Matix4x4f retrieved from the string
             *
             * \return TRUE if successfully converted the string.
             */
            bool stringToMatrix(std::string const& string, Math::Matrix4x4& value);

            /**
             * Converts an integer type to a hex string. <br/>
             * Source: http://stackoverflow.com/a/5100745/735425
             */
            template<typename T>
            std::string toHex(T const x)
            {
                std::stringstream sstream;
                sstream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << x;

                return sstream.str();
            }

        }
        /**
         * @} End of Doxygen Groups
         */
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