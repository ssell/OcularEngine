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
#include <queue>

#include "OcularEngine.hpp"
#include "Foo.hpp"

#include "Tests/PriorityListTest.hpp"

#include "FileIO/Directory.hpp"

//------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    OcularEngine.initialize();

    std::string path = "C:\\Users\\ssell\\Desktop";
    Ocular::Core::Directory directory(path);
    directory.delve();

    std::vector<Ocular::Core::Directory> directories = directory.getChildDirectories();
    std::vector<Ocular::Core::File> files = directory.getChildFiles();

    OcularEngine.Logger()->debug("Contents of '", path, "'");

    for(unsigned i = 0; i < directories.size(); i++)
    {
        OcularEngine.Logger()->debug("\t", directories[i].getFullPath());
    }

    for(unsigned i = 0; i < files.size(); i++)
    {
        OcularEngine.Logger()->debug("\t", files[i].getFullPath());
    }

    /*OcularEngine.WindowManager()->createWindow("Main Window", 1024, 768, 8, 8, 8, Ocular::Core::WINDOW_DISPLAY_MODE::WINDOWED_BORDERED);

    while(OcularEngine.isRunning())
    {
        OcularEngine.run();
    }*/

    OcularEngine.shutdown();
}