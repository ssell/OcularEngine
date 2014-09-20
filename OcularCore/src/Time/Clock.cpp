/**
* Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Time\Clock.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Clock::Clock()
        {
            m_CreationTimeMS = 
                std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();

            m_CreationTimeNS =
                std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
        }

        Clock::~Clock()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        long long Clock::getEpochMS()
        {
            std::chrono::milliseconds::rep currentTime = 
                std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();

            return static_cast<long long>(currentTime);
        }

        long long Clock::getEpochNS()
        {
            std::chrono::nanoseconds::rep currentTime =
                std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
    
            return static_cast<long long>(currentTime);
        }

        long long Clock::getElapsedMS()
        {
            return getEpochMS() - static_cast<long long>(m_CreationTimeMS);
        }

        long long Clock::getElapsedNS()
        {
            return getEpochNS() - static_cast<long long>(m_CreationTimeNS);
        }

        DateTime Clock::getDateTime()
        {
            std::chrono::system_clock::time_point nowA = std::chrono::system_clock::now();
            std::time_t nowB = std::chrono::system_clock::to_time_t(nowA - std::chrono::hours(24));
            std::tm localTime; 
            localtime_s(&localTime, &nowB);

            return DateTime(&localTime, (getEpochMS() % 1000));
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}