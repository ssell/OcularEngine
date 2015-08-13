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

#include "Tests/Performance/BVHSceneTreeTest.hpp"

Ocular::Core::EventSnooper g_Snooper;

using namespace Ocular::Core;
using namespace Ocular::Utils;

//------------------------------------------------------------------------------------------

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

double testHashSpeed()
{
    static const std::string comparison = "e89R0th9C2";
    static const std::string strings[10] =
    {
        "XKAsTEZzaP",
        "fVnPq79rDM",
        "iORia59XbF",
        "8OnoBgEaFj",
        "e89R0th9C2",
        "bAFCiKxIlg",
        "S7HzKuufMk",
        "qNQ4Y5lXSf",
        "EdQsw1hRXi",
        "HtxoxdcDIa"
    };

    auto hashGenerator = OcularEngine.HashGenerator();
    int matches = 0;
    
    const uint64_t startTime = OcularEngine.Clock()->getEpochNS();

    for(uint32_t i = 0; i < 10000; i++)
    {
        uint32_t hashA = hashGenerator->getHash32(comparison, 0); 
        uint32_t hashB = hashGenerator->getHash32(strings[(i % 10)], 0);

        if(hashA == hashB)
        {
            matches++;
        }
    }

    const uint64_t stopTime = OcularEngine.Clock()->getEpochNS();
    const double elapsed = static_cast<double>(stopTime - startTime) * 1e-6;

    return elapsed;
}

double testPrecomputedHashSpeed()
{
    static const std::string strings[10] =
    {
        "XKAsTEZzaP",
        "fVnPq79rDM",
        "iORia59XbF",
        "8OnoBgEaFj",
        "e89R0th9C2",
        "bAFCiKxIlg",
        "S7HzKuufMk",
        "qNQ4Y5lXSf",
        "EdQsw1hRXi",
        "HtxoxdcDIa"
    };

    auto hashGenerator = OcularEngine.HashGenerator();
    int matches = 0;

    const uint32_t hashes[10] =
    {
        hashGenerator->getHash32(strings[0]),
        hashGenerator->getHash32(strings[1]),
        hashGenerator->getHash32(strings[2]),
        hashGenerator->getHash32(strings[3]),
        hashGenerator->getHash32(strings[4]),
        hashGenerator->getHash32(strings[5]),
        hashGenerator->getHash32(strings[6]),
        hashGenerator->getHash32(strings[7]),
        hashGenerator->getHash32(strings[8]),
        hashGenerator->getHash32(strings[9])
    };
    
    const uint64_t startTime = OcularEngine.Clock()->getEpochNS();

    for(uint32_t i = 0; i < 10000; i++)
    {
        if(hashes[4] == hashes[(i % 10)])
        {
            matches++;
        }
    }

    const uint64_t stopTime = OcularEngine.Clock()->getEpochNS();
    const double elapsed = static_cast<double>(stopTime - startTime) * 1e-6;

    return elapsed;
}

double testStringCompareSpeed()
{
    static const std::string comparison = "e89R0th9C2";
    static const std::string strings[10] =
    {
        "XKAsTEZzaP",
        "fVnPq79rDM",
        "iORia59XbF",
        "8OnoBgEaFj",
        "e89R0th9C2",
        "bAFCiKxIlg",
        "S7HzKuufMk",
        "qNQ4Y5lXSf",
        "EdQsw1hRXi",
        "HtxoxdcDIa"
    };

    auto hashGenerator = OcularEngine.HashGenerator();
    int matches = 0;
    
    const uint64_t startTime = OcularEngine.Clock()->getEpochNS();

    for(uint32_t i = 0; i < 10000; i++)
    {
        if(comparison.compare(strings[(i % 10)]))
        {
            matches++;
        }
    }

    const uint64_t stopTime = OcularEngine.Clock()->getEpochNS();
    const double elapsed = static_cast<double>(stopTime - startTime) * 1e-6;

    return elapsed;
}

double testTimeSpeeds()
{
    const uint64_t startTime = OcularEngine.Clock()->getEpochNS();

    for(uint32_t i = 0; i < 10000; i++)
    {
        uint64_t time = OcularEngine.Clock()->getEpochNS();
    }

    const uint64_t stopTime = OcularEngine.Clock()->getEpochNS();
    const double elapsed = static_cast<double>(stopTime - startTime) * 1e-6;

    return elapsed;
}

void compareComparisonSpeeds()
{
    double hashTotal   = 0.0;
    double pcHashTotal = 0.0;
    double stringTotal = 0.0;
    double timeTotal   = 0.0;

    const uint32_t runs = 10;

    for(uint32_t i = 0; i < runs; i++)
    {
        hashTotal   += testHashSpeed();
        pcHashTotal += testPrecomputedHashSpeed();
        stringTotal += testStringCompareSpeed();
        timeTotal   += testTimeSpeeds();
    }
    
    const double hashAverage   = hashTotal / static_cast<double>(runs);
    const double pcHashAverage = pcHashTotal / static_cast<double>(runs);
    const double stringAverage = stringTotal / static_cast<double>(runs);
    const double timeAverage   = timeTotal / static_cast<double>(runs);
    
    OcularLogger->info("  Average elapsed for hash speed: ", hashAverage, "ms");
    OcularLogger->info("Average elapsed for pcHash speed: ", pcHashAverage, "ms");
    OcularLogger->info("Average elapsed for string speed: ", stringAverage, "ms");
    OcularLogger->info("  Average elapsed for time speed: ", timeAverage, "ms");
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();
    Ocular::Core::SystemInfo::logSystemInfo();

    //compareComparisonSpeeds();

    OCULAR_PROFILE_START("main");

    //Ocular::Tests::BVHSceneTreeTest test;
    //test.run();

    //runTests(argc, argv);

    OCULAR_PROFILE_STOP();
    OcularEngine.Profiler()->printToConsole();

    OcularEngine.shutdown();
}