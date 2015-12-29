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
#include "D3D11GraphicsDriver.hpp"

#include "CoreDynamicRegistration.hpp"
#include "D3D11DynamicRegistration.hpp"

#include "Scene/Routines/FreeFlyController.hpp"
#include "Scene/Renderables/MeshRenderable.hpp"

#include "Tests/Routines/InputLoggerRoutine.hpp"

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
    descriptor.width         = 1920;
    descriptor.height        = 1080;
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

void setupScene()
{
    OcularScene->loadScene("TestScene");

    //RenderState* renderState = OcularGraphics->getRenderState();
    //RasterState rasterState = renderState->getRasterState();
    //rasterState.cullDirection = CullDirection::Clockwise;
    //renderState->setRasterState(rasterState);
    //renderState->bind();

    Camera* camera = OcularCameras->getMainCamera();
    camera->setPosition(0.0f, 0.0f, 5.0f);
    camera->addRoutine<FreeFlyController>();
    camera->addRoutine<InputLoggerRoutine>();

    SceneObject* object = OcularScene->createObject("PLY Test Object");
    object->setScale(5.0f, 5.0f, 5.0f);

    MeshRenderable* renderable = new MeshRenderable("PLY Renderable", object);

    uint64_t start = OcularClock->getEpochMS();
    renderable->setMesh("Meshes/dragon_normals");
    uint64_t end = OcularClock->getEpochMS();

    OcularLogger->info("Loaded PLY in ", (end - start), "ms");
    
    
    renderable->setMaterial("Materials/Flat");
}

int main(int argc, char** argv)
{
    OcularEngine.initialize(new D3D11GraphicsDriver());

    if(openWindow())
    {
        setupScene();
        while(OcularEngine.run());
    }

    OcularEngine.shutdown();
}