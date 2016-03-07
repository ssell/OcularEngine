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

// StringUtils is essentially just a wrapper around the Boost string algorithms.
// This is because Boost may in the future be removed as a dependency, and so
// implementing custom string operations will be seamless.

#include "Utilities/StringUtils.hpp"
#include "Utilities/StringComposer.hpp"
#include "Utilities/StringRegistrar.hpp"

#include "OcularEngine.hpp"

#include <boost/algorithm/string.hpp>

#ifdef OCULAR_WINDOWS
#include <Windows.h>
#endif

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        String::String()
        {

        }

        String::~String()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        std::string String::ToLower(std::string const& str)
        {
            std::string result = str;

            boost::to_lower(result);

            return result;
        }

        std::string String::ToUpper(std::string const& str)
        {
            std::string result = str;

            boost::to_upper(result);

            return result;
        }

        bool String::IsEqual(std::string const& strA, std::string const& strB, bool const ignoreCase)
        {
            bool result = false;

            if(strA.length() == strB.length())
            {
                if(!ignoreCase)
                {
                    result = boost::equals(strA, strB);
                }
                else 
                {
                    result = boost::iequals(strA, strB);
                }
            }

            return result;
        }

        std::string String::FormatWindowsError(unsigned long error)
        {
            std::string errorMessage = "UNKNOWN ERROR";

#ifdef OCULAR_WINDOWS
            LPVOID lpMsgBuf;
            
            ::FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                (DWORD)error,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf,
                0,
                NULL);
            
            if(lpMsgBuf)
            {
                errorMessage = (LPTSTR)lpMsgBuf;
                ::LocalFree(lpMsgBuf);
            }

            //----------------------------------------
            // FormatMessage places a newline at the end of the string. Remove it.

            size_t pos = errorMessage.find('\n');

            if(pos != std::string::npos)
            {
                errorMessage.erase(pos - 1, std::string::npos);
            }
#endif

            return errorMessage;
        }

        std::string String::FormatBytes(uint64_t const bytes)
        {
            std::string result = "";

            double fpBytes = static_cast<double>(bytes);

            if(bytes >= BYTES_PER_TiB)
            {
                fpBytes /= static_cast<double>(BYTES_PER_TiB);
                result = StringComposer().compose(fpBytes, " TiB (", bytes, " B)");
            }
            else if(bytes >= BYTES_PER_GiB)
            {
                fpBytes /= static_cast<double>(BYTES_PER_GiB);
                result = StringComposer().compose(fpBytes, " GiB (", bytes, " B)");
            }
            else if(bytes >= BYTES_PER_MiB)
            {
                fpBytes /= static_cast<double>(BYTES_PER_MiB);
                result = StringComposer().compose(fpBytes, " MiB (", bytes, " B)");
            }
            else if(bytes >= BYTES_PER_KiB)
            {
                fpBytes /= static_cast<double>(BYTES_PER_KiB);
                result = StringComposer().compose(fpBytes, " MiB (", bytes, " B)");
            }
            else
            {
                result = StringComposer().compose(fpBytes, " B");
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

//------------------------------------------------------------------------------------------
// Primitive To/From String Methods
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// Float
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<float> OCULAR_INTERNAL_FloatToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    return std::to_string(void_cast<float>(raw));
});

const Ocular::Utils::FromStringRegistrar<float> OCULAR_INTERNAL_FloatFromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static float result;
    result = 0.0f;

    try
    {
        result = std::stof(str);
    }
    catch(std::invalid_argument const& e)
    {
        OcularLogger->error("Failed to convert string '", str, "' to float with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "FloatFromString"));
    }

    return void_cast<float>(result);
});

//------------------------------------------------------------------------------------------
// Double
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<double> OCULAR_INTERNAL_DoubleToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    return std::to_string(void_cast<double>(raw));
});

const Ocular::Utils::FromStringRegistrar<double> OCULAR_INTERNAL_DoubleFromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static double result;
    result = 0.0;

    try
    {
        result = std::stod(str);
    }
    catch(std::invalid_argument const& e)
    {
        OcularLogger->error("Failed to convert string '", str, "' to double with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "DoubleFromString"));
    }

    return void_cast<double>(result);
});

//------------------------------------------------------------------------------------------
// Int 8
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<int8_t> OCULAR_INTERNAL_Int8ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    std::stringstream sstream;
    sstream << void_cast<int8_t>(raw);

    return sstream.str();
});

const Ocular::Utils::FromStringRegistrar<int8_t> OCULAR_INTERNAL_Int8FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static int8_t result;
    result = 0;

    std::stringstream sstream;
    sstream << str;
    sstream >> result;

    return void_cast<int8_t>(result);
});

//------------------------------------------------------------------------------------------
// UInt 8
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<uint8_t> OCULAR_INTERNAL_UInt8ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    std::stringstream sstream;
    sstream << void_cast<uint8_t>(raw);

    return sstream.str();
});

const Ocular::Utils::FromStringRegistrar<uint8_t> OCULAR_INTERNAL_UInt8FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static uint8_t result;
    result = 0;

    std::stringstream sstream;
    sstream << str;
    sstream >> result;

    return void_cast<uint8_t>(result);
});

//------------------------------------------------------------------------------------------
// Int 16
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<int16_t> OCULAR_INTERNAL_Int16ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    std::stringstream sstream;
    sstream << void_cast<int16_t>(raw);

    return sstream.str();
});

const Ocular::Utils::FromStringRegistrar<int16_t> OCULAR_INTERNAL_Int16FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static int16_t result;
    result = 0;

    std::stringstream sstream;
    sstream << str;
    sstream >> result;

    return void_cast<int16_t>(result);
});

//------------------------------------------------------------------------------------------
// UInt 16
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<uint16_t> OCULAR_INTERNAL_UInt16ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    std::stringstream sstream;
    sstream << void_cast<uint16_t>(raw);

    return sstream.str();
});

const Ocular::Utils::FromStringRegistrar<uint16_t> OCULAR_INTERNAL_UInt16FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static uint16_t result;
    result = 0;

    std::stringstream sstream;
    sstream << str;
    sstream >> result;

    return void_cast<uint16_t>(result);
});

//------------------------------------------------------------------------------------------
// Int32
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<int32_t> OCULAR_INTERNAL_Int32ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    return std::to_string(void_cast<int32_t>(raw));
});

const Ocular::Utils::FromStringRegistrar<int32_t> OCULAR_INTERNAL_Int32FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static int32_t result;
    result = 0;

    try
    {
        result = static_cast<int32_t>(std::stol(str));
    }
    catch(std::invalid_argument const& e)
    {
        OcularLogger->error("Failed to convert string '", str, "' to int32_t with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "Int32FromString"));
    }

    return void_cast<int32_t>(result);
});

//------------------------------------------------------------------------------------------
// UInt32
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<uint32_t> OCULAR_INTERNAL_UInt32ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    return std::to_string(void_cast<uint32_t>(raw));
});

const Ocular::Utils::FromStringRegistrar<uint32_t> OCULAR_INTERNAL_UInt32FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static uint32_t result;
    result = 0;

    try
    {
        result = static_cast<uint32_t>(std::stoul(str));
    }
    catch(std::invalid_argument const& e)
    {
        OcularLogger->error("Failed to convert string '", str, "' to uint32_t with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "UInt32FromString"));
    }

    return void_cast<uint32_t>(result);
});

//------------------------------------------------------------------------------------------
// Int64
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<int64_t> OCULAR_INTERNAL_Int64ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    return std::to_string(void_cast<int64_t>(raw));
});

const Ocular::Utils::FromStringRegistrar<int64_t> OCULAR_INTERNAL_Int64FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static int64_t result;
    result = 0;

    try
    {
        result = static_cast<int64_t>(std::stoll(str));
    }
    catch(std::invalid_argument const& e)
    {
        OcularLogger->error("Failed to convert string '", str, "' to int64_t with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "Int64FromString"));
    }

    return void_cast<int64_t>(result);
});

//------------------------------------------------------------------------------------------
// UInt64
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<uint64_t> OCULAR_INTERNAL_UInt64ToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    return std::to_string(void_cast<uint64_t>(raw));
});

const Ocular::Utils::FromStringRegistrar<uint64_t> OCULAR_INTERNAL_UInt64FromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static uint64_t result;
    result = 0;

    try
    {
        result = static_cast<uint64_t>(std::stoull(str));
    }
    catch(std::invalid_argument const& e)
    {
        OcularLogger->error("Failed to convert string '", str, "' to uint64_t with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "UInt64FromString"));
    }

    return void_cast<uint64_t>(result);
});

//------------------------------------------------------------------------------------------
// Bool
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<bool> OCULAR_INTERNAL_BoolToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    bool cast = *static_cast<bool*>(raw);
    return (cast ? "true" : "false");
});

const Ocular::Utils::FromStringRegistrar<bool> OCULAR_INTERNAL_BoolFromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static bool result;
    result = false;

    if(Ocular::Utils::String::IsEqual(str, "true", true))
    {
        result = true;
    }

    return void_cast<bool>(result);
});

//------------------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------------------

const Ocular::Utils::ToStringRegistrar<std::string> OCULAR_INTERNAL_StringToStringRegister(OCULAR_TO_STRING_LAMBDA
{
    return void_cast<std::string>(raw);
});

const Ocular::Utils::FromStringRegistrar<std::string> OCULAR_INTERNAL_StringFromStringRegistrar(OCULAR_FROM_STRING_LAMBDA
{
    static std::string result;
    result = str;

    return void_cast<std::string>(result);
});