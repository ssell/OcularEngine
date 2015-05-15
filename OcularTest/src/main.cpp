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
#include "gtest/gtest.h"
#include "Utilities/HashGenerator.hpp"

Ocular::Core::EventSnooper g_Snooper;

//------------------------------------------------------------------------------------------

int runTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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

int main(int argc, char** argv)
{
    OcularEngine.initialize();
    Ocular::Core::SystemInfo::logSystemInfo();

    runTests(argc, argv);

    // Hash testing

    Ocular::Utils::HashGenerator hashGen0;
    Ocular::Utils::HashGenerator hashGen1;
    
    uint32_t hash0 = hashGen0.getHash32("Hello World!");
    uint32_t hash1 = hashGen0.getHash32("Hello World!");
    
    uint32_t hash2 = hashGen1.getHash32("Hello World!", 0);
    uint32_t hash3 = hashGen1.getHash32("Hello World!", 0);
    
    OcularLogger->info("Hash0: ", hash0);
    OcularLogger->info("Hash1: ", hash1);
    OcularLogger->info("Hash2: ", hash2);
    OcularLogger->info("Hash3: ", hash3);

    OcularEngine.shutdown();
}