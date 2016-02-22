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

#include "Math/Vector4.hpp"
#include "Math/Matrix4x4.hpp"
#include "Math/Matrix3x3.hpp"

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
        namespace StringUtils
        {
            std::string ToLower(std::string const& str)
            {
                std::string result = str;

                boost::to_lower(result);

                return result;
            }

            std::string ToUpper(std::string const& str)
            {
                std::string result = str;

                boost::to_upper(result);

                return result;
            }

            bool IsEqual(std::string const& strA, std::string const& strB, bool const ignoreCase)
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

            std::string WindowsErrorToString(unsigned long error)
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

            std::string BytesToString(uint64_t bytes)
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

            bool StringToFloat(std::string const& string, float& value)
            {
                bool result = true;

                try
                {
                    value = std::stof(string, nullptr);
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", string, "' to float value with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "StringToFloat"));
                }

                return true;
            }

            bool StringToVector(std::string const& string, Math::Vector2f& value)
            {
                bool result = true;

                uint32_t index = 0;

                size_t cumulativePos = 0;
                size_t nextPos = 0;

                try
                {
                    while((cumulativePos < string.size()) && (index < 2))
                    {
                        value[index] = std::stof(string.substr(cumulativePos), &nextPos);

                        cumulativePos += nextPos;
                        index += 1;
                    }
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", string, "' to Vector2f value with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "StringToVector"));
                }

                return result;
            }

            bool StringToVector(std::string const& string, Math::Vector3f& value)
            {
                bool result = true;

                uint32_t index = 0;

                size_t cumulativePos = 0;
                size_t nextPos = 0;

                try
                {
                    while((cumulativePos < string.size()) && (index < 3))
                    {
                        value[index] = std::stof(string.substr(cumulativePos), &nextPos);

                        cumulativePos += nextPos;
                        index += 1;
                    }
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", string, "' to Vector3f value with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "StringToVector"));
                }

                return result;
            }

            bool StringToVector(std::string const& string, Math::Vector4f& value)
            {
                bool result = true;

                uint32_t index = 0;

                size_t cumulativePos = 0;
                size_t nextPos = 0;

                try
                {
                    while((cumulativePos < string.size()) && (index < 4))
                    {
                        value[index] = std::stof(string.substr(cumulativePos), &nextPos);

                        cumulativePos += nextPos;
                        index += 1;
                    }
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", string, "' to Vector4f value with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "StringToVector"));
                }

                return result;
            }

            bool StringToQuaternion(std::string const& string, Math::Quaternion& value)
            {
                bool result = true;

                float values[4] { 0.0f, 0.0f, 0.0f, 1.0f };

                uint32_t index = 0;

                size_t cumulativePos = 0;
                size_t nextPos = 0;

                try
                {
                    while((cumulativePos < string.size()) && (index < 4))
                    {
                        values[index] = std::stof(string.substr(cumulativePos), &nextPos);

                        cumulativePos += nextPos;
                        index += 1;
                    }

                    value = Math::Quaternion(values[0], values[1], values[2], values[3]);
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", string, "' to Quaternion value with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "StringToQuaternion"));
                }

                return result;
            }

            bool StringToMatrix(std::string const& string, Math::Matrix3x3& value)
            {
                bool result = true;

                uint32_t index = 0;

                size_t cumulativePos = 0;
                size_t nextPos = 0;

                try
                {
                    while((cumulativePos < string.size()) && (index < 9))
                    {
                        value.setElement(index, std::stof(string.substr(cumulativePos), &nextPos));

                        cumulativePos += nextPos;
                        index += 1;
                    }
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", string, "' to Matrix3x3 value with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "StringToMatrix"));
                }

                return result;
            }

            bool StringToMatrix(std::string const& string, Math::Matrix4x4& value)
            {
                bool result = true;

                uint32_t index = 0;

                size_t cumulativePos = 0;
                size_t nextPos = 0;

                try
                {
                    while((cumulativePos < string.size()) && (index < 16))
                    {
                        value.setElement(index, std::stof(string.substr(cumulativePos), &nextPos));

                        cumulativePos += nextPos;
                        index += 1;
                    }
                }
                catch(std::invalid_argument const& e)
                {
                    result = false;
                    OcularLogger->error("Failed to convert string '", string, "' to Matrix4x4 value with error: ", e.what(), OCULAR_INTERNAL_LOG("StringUtils", "StringToMatrix"));
                }
                
                return result;
            }
        }
    }
}