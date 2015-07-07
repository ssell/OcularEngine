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
     * \addtogroup Core
     * @{
     */
    namespace Core
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
             * Calculates and updates the delta time.
             * \note This method should only be called once per frame (at the start) and only by it's explicit owner.
             */
            void tick();

            /**
             * Returns the time, in seconds, it took to complete the last frame.
             */
            float getDelta();

            /**
             * Returns the number of milliseconds since epoch (January 1, 1970).
             */
            uint64_t getEpochMS();

            /**
             * Returns the number of nanoseconds since epoch (January 1, 1970).
             */
            uint64_t getEpochNS();

            /**
             * Returns the number of milliseconds since Clock creation.
             */
            uint64_t getElapsedMS();
        
            /**
             * Returns the number of nanoseconds since Clock creation.
             */
            uint64_t getElapsedNS();

            /**
             * Returns current system date and time.
             */
            DateTime getDateTime();

        protected:

        private:

            std::chrono::milliseconds::rep m_CreationTimeMS;
            std::chrono::nanoseconds::rep  m_CreationTimeNS;

            std::chrono::milliseconds::rep m_LastTick;
            float m_Delta;
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