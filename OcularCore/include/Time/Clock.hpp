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

#pragma once
#ifndef __H__OCULAR_TIME_CLOCK__H__
#define __H__OCULAR_TIME_CLOCK__H__

#include "Time\DateTime.hpp"
#include <chrono>

//------------------------------------------------------------------------------------------

/**
* \addtogroup Ocular
* @{
*/
namespace Ocular
{
    /**
     * \class Clock
     */
    class Clock
    {
    public:

        Clock();
        ~Clock();

        /**
         * Returns the number of milliseconds since epoch (January 1, 1970).
         */
        long long getEpochMS();

        /**
         * Returns the number of nanoseconds since epoch (January 1, 1970).
         */
        long long getEpochNS();

        /**
         * Returns the number of milliseconds since Clock creation.
         */
        long long getElapsedMS();
        
        /**
         * Returns the number of nanoseconds since Clock creation.
         */
        long long getElapsedNS();

        /**
         * Returns current system date and time.
         */
        DateTime getDateTime();

    protected:

    private:

        std::chrono::milliseconds::rep m_CreationTimeMS;
        std::chrono::nanoseconds::rep  m_CreationTimeNS;
    };
}
/**
* @} End of Doxygen Groups
*/

//------------------------------------------------------------------------------------------

#endif