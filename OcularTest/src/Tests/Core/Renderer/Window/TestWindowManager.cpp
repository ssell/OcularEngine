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
#include "Renderer/Window/Window.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

unsigned long long g_WindowUID0 = 0;
unsigned long long g_WindowUID1 = 0;
unsigned long long g_WindowUID2 = 0;

void TestOpenWindows()
{
    Ocular::Core::WindowDescriptor descriptor0;
    Ocular::Core::WindowDescriptor descriptor1;
    Ocular::Core::WindowDescriptor descriptor2;

    descriptor0.displayName = "Test Window 0";
    descriptor1.displayName = "Test Window 1";
    descriptor2.displayName = "Test Window 2";
    
    std::shared_ptr<Ocular::Core::AWindow> window0 = OcularEngine.WindowManager()->openWindow(descriptor0);
    std::shared_ptr<Ocular::Core::AWindow> window1 = OcularEngine.WindowManager()->openWindow(descriptor1);
    std::shared_ptr<Ocular::Core::AWindow> window2 = OcularEngine.WindowManager()->openWindow(descriptor2);
    
    EXPECT_TRUE((window0.get() != nullptr));
    EXPECT_TRUE((window1.get() != nullptr));
    EXPECT_TRUE((window2.get() != nullptr));

    g_WindowUID0 = window0->getUID();
    g_WindowUID1 = window1->getUID();
    g_WindowUID2 = window2->getUID();

    EXPECT_FALSE(g_WindowUID0 == 0);
    EXPECT_FALSE(g_WindowUID1 == 0);
    EXPECT_FALSE(g_WindowUID2 == 0);
}

void TestRetrieveWindows()
{
    std::shared_ptr<Ocular::Core::AWindow> window0 = OcularEngine.WindowManager()->getWindow(g_WindowUID0);
    std::shared_ptr<Ocular::Core::AWindow> window1 = OcularEngine.WindowManager()->getWindow(g_WindowUID1);
    std::shared_ptr<Ocular::Core::AWindow> window2 = OcularEngine.WindowManager()->getWindow(g_WindowUID2);
    
    EXPECT_TRUE((window0.get() != nullptr));
    EXPECT_TRUE((window1.get() != nullptr));
    EXPECT_TRUE((window2.get() != nullptr));
}

void TestCloseWindows()
{
    unsigned numWindows = OcularEngine.WindowManager()->getNumWindows();
    EXPECT_EQ(numWindows, (unsigned)3);

    //------------------------------------------------
    // Test MainWindow switch

    unsigned long long mainWindowUID = OcularEngine.WindowManager()->getMainWindow()->getUID();
    EXPECT_EQ(mainWindowUID, g_WindowUID0);

    OcularEngine.WindowManager()->closeWindow(g_WindowUID0);

    mainWindowUID = OcularEngine.WindowManager()->getMainWindow()->getUID();
    EXPECT_EQ(mainWindowUID, g_WindowUID2);    // This will fail if any Windows were created, and not destroy, prior to this test being run.
                                               // Also remember new windows are added to front of window list, so next is line for MainWindow 
                                               // will actually be the most recently created window.
    OcularEngine.WindowManager()->closeWindow(g_WindowUID1);
    OcularEngine.WindowManager()->closeWindow(g_WindowUID2);

    //------------------------------------------------

    numWindows = OcularEngine.WindowManager()->getNumWindows();
    EXPECT_EQ(numWindows, (unsigned)0);
}

TEST(WindowManager, General)
{
    TestOpenWindows();
    TestRetrieveWindows();
    TestCloseWindows();
}