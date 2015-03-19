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
#include "Texture/TextureLoaders/TextureResourceLoader_BMP.hpp"
#include "Texture/Texture2D.hpp"

Ocular::Core::EventSnooper g_Snooper;

//------------------------------------------------------------------------------------------

int runTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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

void testBMPLoad()
{
    Ocular::Graphics::TextureResourceLoader_BMP bmpLoader;

    Ocular::Core::Resource* resource = OcularEngine.ResourceManager()->loadUnmanagedFile("C:\\Users\\admin\\Desktop\\New folder\\in.bmp");

    if(resource != nullptr)
    {
        Ocular::Graphics::Texture2D* texture = (Ocular::Graphics::Texture2D*)resource;

        if(texture != nullptr)
        {
            Ocular::Core::File outFile("C:\\Users\\admin\\Desktop\\New folder\\out.bmp");
            
            if(OcularEngine.ResourceManager()->saveResource(texture, outFile))
            {
                OcularLogger->info("Successfully saved out Texture2D as BMP");
            }
            else
            {
                OcularLogger->error("Failed to save out Texture2D as BMP");
            }
        }
        else
        {
            OcularLogger->error("Failed to cast Resource to Texture2D");
        }

        delete resource;     // When using loadUnmanagedFile, the caller is responsible for cleanup
        resource = nullptr;
        texture = nullptr;
    }
    else
    {
        OcularLogger->error("Failed to load unmanaged Resource");
    }
}

void testBMPSave()
{
    Ocular::Graphics::TextureResourceSaver_BMP bmpSaver;

    Ocular::Core::File file("C:\\Users\\ssell\\Desktop\\OcularTestPlace\\testBMP.bmp");
    Ocular::Graphics::Texture2D* texture = new Ocular::Graphics::Texture2D(2, 2);

    texture->setPixel(0, 0, Ocular::Color(1.0f, 0.0f, 0.0f, 1.0f));
    texture->setPixel(1, 0, Ocular::Color(1.0f, 1.0f, 1.0f, 1.0f));
    texture->setPixel(0, 1, Ocular::Color(0.0f, 0.0f, 1.0f, 1.0f));
    texture->setPixel(1, 1, Ocular::Color(0.0f, 1.0f, 0.0f, 1.0f));

    OcularEngine.ResourceManager()->saveResource(texture, file);
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();
    
    OcularLogger->info("Number of registered Resource Loaders: ", OcularEngine.ResourceManager()->getNumberOfResourceLoaders());
    OcularLogger->info("Number of registered Resource Savers:  ", OcularEngine.ResourceManager()->getNumberOfResourceSavers());

    //runTests(argc, argv);
    //testResources();
    openWindow();

    testBMPLoad();
    //testBMPSave();
    
    while(OcularEngine.isRunning())
    {
        OcularEngine.run();
    }

    OcularLogger->error("bad thing has happened");

    OcularEngine.shutdown();
}