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

#include "OcularEngine.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

int runTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();
    OcularEngine.WindowManager()->createWindow("Window", 800, 600, 8, 8, 8, Ocular::Core::WINDOW_DISPLAY_MODE::WINDOWED_BORDERED, true);

    while(OcularEngine.isRunning())
    {
        OcularEngine.run();
    }

    //runTests(argc, argv);
    
    OcularEngine.shutdown();
}