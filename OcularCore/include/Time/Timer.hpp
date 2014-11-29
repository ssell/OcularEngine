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
#ifndef __H__OCULAR_TIME_TIMER__H__
#define __H__OCULAR_TIME_TIMER__H__

#include "OcularEngine.hpp"

#include <functional>
#include <list>
#include <utility>
#include <thread>

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
        * \class Timer
        */
        class Timer
        {
        public:

            Timer();
            ~Timer();

            /**
             * Starts the timer.
             */
            void start();
            
            /**
             * Stops the timer.
             */
            void stop();
            
            /**
             * Resets the timer.
             */
            void reset();

            /**
             * Returns the amount of time elapsed since start was called. <br/>
             * If the timer is stopped, then the elapsed time does not increment.
             *
             * \return Amount of time elapsed in milliseconds
             */
            long long getElapsedMS();

        protected:

        private:
            
            void updateInternalTime();

            bool m_Stopped;

            long long m_ElapsedMS;
            long long m_LastUpdate;
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