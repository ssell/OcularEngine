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

#include "OcularEngine.hpp"
#include "SystemInfo.hpp"
#include "Events/EventSnooper.hpp"
//#include "gtest/gtest.h"

#include "Math/Vector3.hpp"
#include "Tests/Performance/BVHSceneTreeTest.hpp"
#include <boost/current_function.hpp>

Ocular::Core::EventSnooper g_Snooper;

using namespace Ocular::Core;
using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

class SomeClass
{
public:

    SomeClass() { }
    ~SomeClass() { }

    int speak(std::string butts) { OcularLogger->info(BOOST_CURRENT_FUNCTION); return 0; };
};

int runTests(int argc, char** argv)
{
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    return 0;
}

void openWindow()
{
    Ocular::Core::WindowDescriptor descriptor;

    descriptor.displayName   = "Demo Application";
    descriptor.width         = 800;
    descriptor.height        = 600;
    descriptor.colorBits     = 8;
    descriptor.depthBits     = 8;
    descriptor.stencilBits   = 8;
    descriptor.displayMode   = Ocular::Core::WindowDisplayMode::WindowedBordered;
    descriptor.exclusiveMode = false;

    OcularEngine.WindowManager()->openWindow(descriptor);
}

void thisIsAFunction()
{
    OcularLogger->info("Function Name: ", BOOST_CURRENT_FUNCTION);
    SomeClass foo;
    foo.speak("");
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();
    Ocular::Core::SystemInfo::logSystemInfo();

    OcularLogger->info("Function Name: ", BOOST_CURRENT_FUNCTION);
    thisIsAFunction();

    //runTests(argc, argv);

    OcularEngine.shutdown();
}