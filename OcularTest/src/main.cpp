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
#include "Events/EventSnooper.hpp"
#include "gtest/gtest.h"

#include "Resources/ResourceExplorer.hpp"
#include "Exceptions/FileReadWriteException.hpp"

Ocular::Core::EventSnooper g_Snooper;

//------------------------------------------------------------------------------------------

int runTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void testDirectory()
{
    Ocular::Core::Directory directory("C:\\Users\\ssell\\Desktop\\DirTest");
    directory.explore(true);
    
    auto childDirs  = directory.getChildDirectories();
    auto childFiles = directory.getChildFiles();

    std::cout << "Directories: \n" << std::endl;
    for(auto dirIter = childDirs.begin(); dirIter != childDirs.end(); dirIter++)
    {
        std::cout << (*dirIter).getFullPath() << std::endl;
    }

    std::cout << "\nFiles: \n" << std::endl;
    for(auto fileIter = childFiles.begin(); fileIter != childFiles.end(); fileIter++)
    {
        std::cout << (*fileIter).getFullPath() << std::endl;
    }
}

void testResources()
{
    /*Ocular::Core::ResourceExplorer explorer;
    std::unordered_map<std::string, Ocular::Core::File> resources;

    explorer.populateResourceMap(resources);

    //--------------------------------------------------------------------------------------

    auto resource = resources.find("Shaders\\TestVS");

    if(resource != resources.end())
    {
        OcularEngine.Logger()->debug("Found resource: ", (*resource).second.getFullPath());
    }
    else 
    {
        OcularEngine.Logger()->debug("Did not find resource :(");
    }*/
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
    descriptor.displayMode   = Ocular::Core::WINDOW_DISPLAY_MODE::WINDOWED_BORDERED;
    descriptor.exclusiveMode = false;

    OcularEngine.WindowManager()->openWindow(descriptor);
}

void setupEventSnooper()
{
    g_Snooper.setIgnoreDuplicates(true);
    OcularEngine.EventManager()->registerListener(&g_Snooper, Ocular::Core::EVENT_PRIORITY::MONITOR);
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();

    //runTests(argc, argv);
    //testResources();
    openWindow();
    
    while(OcularEngine.isRunning())
    {
        OcularEngine.run();
    }

    OcularEngine.shutdown();
}