/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Scene/Renderables/MeshRenderable.hpp"

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
    Camera* camera = OcularCameras->getMainCamera();

    if(camera)
    {
        camera->setPosition(0.5f, 0.5f, 5.0f);
        camera->addRoutine("FreeFlyController");
        camera->addRoutine("InputLogger");
    }
}

void setupVisual()
{
    SceneObject* object = OcularScene->createObject("Test Object");

    if(object)
    {
        MeshRenderable* renderable = (MeshRenderable*)object->setRenderable("Mesh");

        if(renderable)
        {
            const uint64_t start = OcularClock->getEpochMS();
            renderable->setMesh("Meshes/hand_normals");
            const uint64_t end = OcularClock->getEpochMS();

            renderable->setMaterial("Materials/Flat");

            OcularLogger->info("Mesh loaded in ", (end - start), "ms");
        }
    }

    object->setScale(Vector3f(1.0f, 1.0f, 1.0f));
}

void setupScene()
{
    OcularScene->loadScene("TestScene");
    
    setupCamera();
    setupVisual();
}

int main(int argc, char** argv)
{
    OcularEngine.initialize(new D3D11GraphicsDriver());
   
    Ocular::Math::Matrix4x4 matrix;
    OcularLogger->info("Type: ", OCULAR_TYPE(matrix));

    if(openWindow())
    {
        setupScene();
        while(OcularEngine.run());
    }

    OcularEngine.shutdown();
}