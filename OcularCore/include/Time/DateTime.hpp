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

#pragma once
#ifndef __H__OCULAR_TIME_DATE_TIME__H__
#define __H__OCULAR_TIME_DATE_TIME__H__

#include <ctime>

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
         * \class DateTime
         */
        class DateTime
        {
        public:

            /**
             * \note Only basic sanity-checking is performed (minutes in range [0,59], etc.)
             *
             * \param year
             * \param month       Month of year [1,12]
             * \param day         Day of month [1,31]
             * \param hour        Hour of day [0,23]
             * \param minute      Minute of hour [0,59]
             * \param second      Second of minute [0,59]
             * \param millisecond Millisecond of minute [0, 999]
             * \param dst         Daylight Saving Time
             */
            DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, bool dst = false);
        
            /**
             * \param time 
             * \param ms
             */
            DateTime(std::tm* time, int ms = 0);

            ~DateTime();

            /**
             * Returns the year
             */
            int getYear();

            /**
             * Returns the month of the year [1,12]
             */
            int getMonth();

            /**
             * Returns day of the month [1,31]
             */
            int getDayOfMonth();

            /**
             * Returns day of the year [1, 366]
             */
            int getDayOfYear();

            /**
             * Returns hours since midnight [0, 23]
             */
            int getHour();

            /**
             * Returns minutes after the hour [0, 59]
             */
            int getMinute();

            /**
             * Returns seconds after the minute [0, 59]
             */
            int getSecond();

            /**
             * Returns milliseconds after the second [0, 999]
             */
            int getMillisecond();

            /**
             * Returns true if Daylight Saving Time is in effect.
             */
            bool getIsDST();

        protected:

        private:

            int m_Year;
            int m_Month;
            int m_Day;
            int m_DayJulian;
            int m_Hour;
            int m_Minute;
            int m_Second;
            int m_Millisecond;
       
            bool m_DST;
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