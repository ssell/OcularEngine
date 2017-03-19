/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#include "D3D11GraphicsDriver.hpp"
#include "D3D11DynamicRegistration.hpp"

using namespace Ocular::Core;
using namespace Ocular::Utils;
using namespace Ocular::Math;
using namespace Ocular::Graphics;

//------------------------------------------------------------------------------------------

bool openWindow()
{
    bool result = false;

    WindowDescriptor descriptor;

    descriptor.displayName   = "Ocular Engine";
    descriptor.width         = 1300;
    descriptor.height        = 900;
    descriptor.colorBits     = 8;
    descriptor.depthBits     = 8;
    descriptor.stencilBits   = 8;
    descriptor.displayMode   = WindowDisplayMode::WindowedBordered;
    descriptor.exclusiveMode = false;

    if(OcularEngine.WindowManager()->openWindow(descriptor))
    {
        OcularWindows->getMainWindow()->showCursor(false);

        if(OcularGraphics->initialize())
        {
            result = true;
        }
    }

    return result;
}

void setupCamera()
{
    // Check if a Camera already exists (potentially loaded in with a Scene)
    Camera* camera = OcularCameras->getMainCamera();

    if(camera == nullptr)
    {
        // Calling `new Camera` will create the camera, register it with the global 
        // Camera Manager (OcularCameras), and set it as the Main camera if it is the first.

        camera = new Camera();

        camera->setPosition(0.0f, 0.0f, 2.0f);
        camera->addRoutine("FreeFlyController");
    }
}

int main(int argc, char** argv)
{
    /**
     * Basic steps to start running:
     *
     * 1. Initialize the Engine
     * 2. Open a Window
     * 3. Set Resource Directory (optional)
     * 4. Create / Load a Scene
     * 5. Setup Camera
     * 6. Run
     */

    if(OcularEngine.initialize(new D3D11GraphicsDriver()))
    {
        if(openWindow())
        {
            OcularResources->setSourceDirectory("C:\\Projects\\OcularEngine\\Resources");
            OcularResources->forceSourceRefresh();

            OcularScene->loadScene(File("C:\\Projects\\OcularEngine\\Resources\\test.oscene"));

            setupCamera();

            while(OcularEngine.run());
        }

        OcularEngine.shutdown();
    }
}