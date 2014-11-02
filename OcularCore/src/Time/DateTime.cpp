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

#include "Time/DateTime.hpp"
#include "Math/MathCommon.hpp"

//------------------------------------------------------------------------------------------

static const int DAYS_ELAPSED[12] =
{
     0,     // Jan 1 :   0 days elapsed
    31,     // Feb 1 :  31 days elapsed (31 days in Jan)
    59,     // Mar 1 :  59 days elapsed (28 days in Feb)
    90,     // Apr 1 :  90 days elapsed (31 days in Mar)
    120,    // May 1 : 120 days elapsed (30 days in Apr)
    151,    // Jun 1 : 151 days elapsed (31 days in May)
    181,    // Jul 1 : 181 days elapsed (30 days in Jun)
    212,    // Aug 1 : 212 days elapsed (31 days in Jul)
    243,    // Sep 1 : 243 days elapsed (31 days in Aug)
    273,    // Oct 1 : 273 days elapsed (30 days in Sep)
    304,    // Nov 1 : 304 days elapsed (31 days in Oct)
    334     // Dec 1 : 334 days elapsed (30 days in Dec)
};

static const int DAYS_ELAPSED_LEAP[12] =
{
     0,
    31,
    60,
    91,
    121,
    152,
    182,
    213,
    244,
    274,
    305,
    335
};

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, bool dst)
        {
            m_Year        = year;
            m_Month       = Math::Clamp(month, 1, 12);
            m_Day         = Math::Clamp(day, 1, 31);
            m_Hour        = Math::Clamp(hour, 0, 23);
            m_Minute      = Math::Clamp(minute, 0, 59);
            m_Second      = Math::Clamp(second, 0, 59);
            m_Millisecond = Math::Clamp(millisecond, 0, 999);
            m_DST         = dst;

            if((m_Year % 4) == 0)
            {
                m_DayJulian = DAYS_ELAPSED_LEAP[m_Month - 1] + m_Day;
            }
            else
            {
                m_DayJulian = DAYS_ELAPSED[m_Month - 1] + m_Day;
            }
        }

        DateTime::DateTime(std::tm* time, int ms)
        {
            if(time != nullptr)
            {
                m_Year        = time->tm_year + 1900;
                m_Month       = time->tm_mon + 1;
                m_Day         = time->tm_mday + 1;
                m_DayJulian   = time->tm_yday + 1;
                m_Hour        = time->tm_hour;
                m_Minute      = time->tm_min;
                m_Second      = time->tm_sec;
                m_Millisecond = ms;
                m_DST         = (time->tm_isdst > 0) ? true : false;
            }
        }

        DateTime::~DateTime()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        int DateTime::getYear()
        {
            return m_Year;
        }

        int DateTime::getMonth()
        {
            return m_Month;
        }

        int DateTime::getDayOfMonth()
        {
            return m_Day;
        }

        int DateTime::getDayOfYear()
        {
            return m_DayJulian;
        }

        int DateTime::getHour()
        {
            return m_Hour;
        }

        int DateTime::getMinute()
        {
            return m_Minute;
        }

        int DateTime::getSecond()
        {
            return m_Second;
        }
    
        int DateTime::getMillisecond()
        {
            return m_Millisecond;
        }

        bool DateTime::getIsDST()
        {
            return m_DST;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}