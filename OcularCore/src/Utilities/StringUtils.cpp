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
        std::unordered_map<std::string, std::function<std::string(void*)>> String::m_ToFunctions = std::unordered_map<std::string, std::function<std::string(void*)>>();
        std::unordered_map<std::string, std::function<void*(std::string const&)>> String::m_FromFunctions = std::unordered_map<std::string, std::function<void*(std::string const&)>>();

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

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