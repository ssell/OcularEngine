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

#include "Time\Timer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Timer::Timer()
        {
            m_Stopped = false;
            m_ElapsedMS = 0;
        }

        Timer::~Timer()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Timer::start()
        {
            m_Stopped = false;
            m_LastUpdate = OcularEngine.Clock()->getElapsedMS();
        }

        void Timer::stop()
        {
            m_Stopped = true;
        }

        void Timer::reset()
        {
            m_ElapsedMS = 0;
            m_LastUpdate = OcularEngine.Clock()->getElapsedMS();
        }

        long long Timer::getElapsedMS()
        {
            if(!m_Stopped)
            {
                long long time = OcularEngine.Clock()->getElapsedMS();
                m_ElapsedMS += time - m_LastUpdate;
                m_LastUpdate = time;
            }

            return m_ElapsedMS;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}