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
#include "OcularEngine.hpp"
#include "Time\Timer.hpp"

//------------------------------------------------------------------------------------------

void helloWorld()
{
    OcularEngine.Logger()->info("Hello World!");
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();
    
    /*const Ocular::Core::AWindow* window = OcularEngine.WindowManager()->createWindow(
        "Test Window", 1024, 768, 8, 8, 8, Ocular::Core::WINDOW_DISPLAY_MODE::WINDOWED_BORDERED);

    if(window)
    {
        OcularEngine.Logger()->info("Successful window creation after ", OcularEngine.Clock()->getElapsedMS(), " ms");
    }
    else
    {
        OcularEngine.Logger()->error("Failed to create window");
    }*/

    //-----------------------------------------------
    // Run for 4 seconds, pause for 3 seconds, run for 1 second

    Ocular::Core::Timer timer;
    Ocular::Core::Timer timer2;

    timer.start();

    long long elapsed = timer.getElapsedMS();

    while(elapsed < 5000)
    {
        OcularEngine.Logger()->debug(timer.getElapsedMS(), "ms have elpased");

        if(elapsed > 4000 && elapsed < 4020)
        {
            timer.stop();
            timer2.start();
            long long elapsed2 = timer2.getElapsedMS();

            while(elapsed2 < 3000)
            {
                elapsed2 = timer2.getElapsedMS();
            }

            timer2.reset();
            timer.start();

            while(elapsed < 4020)
            {
                elapsed = timer.getElapsedMS();
            }
        }

        elapsed = timer.getElapsedMS();
    }

    OcularEngine.Logger()->info("Shutting down after ", OcularEngine.Clock()->getElapsedMS(), "ms");
    OcularEngine.shutdown();

    return 0;
}