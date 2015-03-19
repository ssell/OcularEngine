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

#include "Texture/TextureSavers/TextureResourceSaver_BMP.hpp"
#include "Texture/TextureLoaders/TextureResourceLoader_PNG.hpp"
#include "Texture/Texture2D.hpp"

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
    descriptor.displayMode   = Ocular::Core::WINDOW_DISPLAY_MODE::WINDOWED_BORDERED;
    descriptor.exclusiveMode = false;

    OcularEngine.WindowManager()->openWindow(descriptor);
}

void setupEventSnooper()
{
    g_Snooper.setIgnoreDuplicates(true);
    OcularEngine.EventManager()->registerListener(&g_Snooper, Ocular::Core::EVENT_PRIORITY::MONITOR);
}

bool convertPNGtoBMP(Ocular::Core::File const& pngIn, Ocular::Core::File const& bmpOut)
{
    bool result = false;

    Ocular::Core::Resource* resource = OcularEngine.ResourceManager()->loadUnmanagedFile(pngIn);

    if(resource)
    {
        result = OcularEngine.ResourceManager()->saveResource(resource, bmpOut);

        delete resource;
        resource = nullptr;
    }

    return result;
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();
    
    OcularLogger->info("Number of registered Resource Loaders: ", OcularEngine.ResourceManager()->getNumberOfResourceLoaders());
    OcularLogger->info("Number of registered Resource Savers:  ", OcularEngine.ResourceManager()->getNumberOfResourceSavers());

    //runTests(argc, argv);
    //testResources();

    Ocular::Graphics::TextureResourceLoader_PNG blergh;
    Ocular::Graphics::TextureResourceSaver_BMP blerghh;

    Ocular::Core::File png("C:\\Users\\admin\\Desktop\\New folder\\in.png");
    Ocular::Core::File bmp("C:\\Users\\admin\\Desktop\\New folder\\out.bmp");
    
    convertPNGtoBMP(png, bmp);

    OcularEngine.shutdown();
}