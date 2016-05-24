/**
* Copyright 2014-2015 Steven T Sell (ssell@vertexfragment.com)
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
            : m_Delta(0.0f)
        {
            m_CreationTimeMS = 
                std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();

            m_CreationTimeNS =
                std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();

            m_LastTick = m_CreationTimeMS;
        }

        Clock::~Clock()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Clock::tick()
        {
            std::chrono::milliseconds::rep currentTime = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();

            m_Delta = static_cast<float>(currentTime - m_LastTick) / 1000.0f;
            m_LastTick = currentTime;
        }

        float Clock::getDelta()
        {
            return m_Delta;
        }

        uint64_t Clock::getEpochMS()
        {
            std::chrono::milliseconds::rep currentTime = 
                std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();

            return static_cast<uint64_t>(currentTime);
        }

        uint64_t Clock::getEpochNS()
        {
            std::chrono::nanoseconds::rep currentTime =
                std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
    
            return static_cast<uint64_t>(currentTime);
        }

        uint64_t Clock::getElapsedMS()
        {
            return getEpochMS() - static_cast<uint64_t>(m_CreationTimeMS);
        }

        uint64_t Clock::getElapsedNS()
        {
            return getEpochNS() - static_cast<uint64_t>(m_CreationTimeNS);
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