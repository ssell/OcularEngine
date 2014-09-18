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

#include <iostream>
#include "Renderer\Window\Window.hpp"

#include "Logger\Logger.hpp"
#include "Logger\ConsoleLoggerListener.hpp"
#include "Logger\VSConsoleLoggerListener.hpp"
#include "Time\Clock.hpp"

//------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Ocular::Clock clock;

    Ocular::Logger logger;
    logger.registerListener(new Ocular::ConsoleLoggerListener());
    logger.registerListener(new Ocular::VSConsoleLoggerListener());

    //------------------------------------------------

    Ocular::WindowManager manager;
    
    if(manager.createWindow("Test", 800, 600, 8, 8, 8, Ocular::WINDOW_DISPLAY_MODE::WINDOWED_BORDERED))
    {
        logger.info("Window creation successful");
        manager.destroyWindow("Test");
    }
    else 
    {
       logger.error("Failed to create window");
    }

    //------------------------------------------------

    Ocular::DateTime date = clock.getDateTime();
    long long elapsed = clock.getElapsedMS();

    logger.info("Program exit on ", date.getYear(), "-", date.getMonth(), "-", date.getDayOfMonth(),
        "@", (date.getHour() < 10 ? "0" : ""), date.getHour(),
        ":", (date.getMinute() < 10 ? "0" : ""), date.getMinute(),
        ":", (date.getSecond() < 10 ? "0" : ""), date.getSecond(),
        " after ", elapsed, " MS of execution.");

    return 0;
}