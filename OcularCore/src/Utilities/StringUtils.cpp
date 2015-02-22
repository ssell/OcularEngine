/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
#include <boost/algorithm/string.hpp>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        std::string StringUtils::toLower(std::string const& str)
        {
            std::string result = str;

            boost::to_lower(result);

            return result;
        }

        std::string StringUtils::toUpper(std::string const& str)
        {
            std::string result = str;

            boost::to_upper(result);

            return result;
        }

        bool StringUtils::isEqual(std::string const& strA, std::string const& strB, bool const ignoreCase)
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

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}