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
#include "D3D11GraphicsDriver.hpp"
#include "Events/EventSnooper.hpp"
#include "gtest/gtest.h"

#include "Graphics/Shader/ShaderProgram.hpp"
#include "Shader/D3D11UncompiledShaderResourceLoader.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_BMP.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_PNG.hpp"
#include "Graphics/Material/MaterialResourceLoader.hpp"
#include "Graphics/Material/Material.hpp"

#include "Scene/Routines/FreeFlyController.hpp"
#include "Scene/Renderables/RenderablePrimitiveCube.hpp"
#include "Renderer/Window/Window.hpp"

#include <DirectXMath.h>

Ocular::Core::EventSnooper g_Snooper;

using namespace Ocular::Core;
using namespace Ocular::Utils;
using namespace Ocular::Math;
using namespace Ocular::Graphics;

//------------------------------------------------------------------------------------------

int runTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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

    //--------------------------------------------------------------------
    // Setup Camera

    Camera* mainCamera = OcularCameras->getMainCamera();

    if(mainCamera)
    {
        mainCamera->setPosition(0.0f, 0.0f, 3.0f);
        mainCamera->addRoutine<FreeFlyController>();
    }

    //--------------------------------------------------------------------
    // Setup Input Logger

    SceneObject* inputObject = OcularScene->createObject("Test Object");
    inputObject->addRoutine("InputLogger");

    //--------------------------------------------------------------------
    // Setup Cube

    SceneObject* cubeObject = OcularScene->createObject("Cube");
    cubeObject->setPosition(0.0f, -0.5f, 0.0f);
    //cubeObject->addRoutine<FreeFlyController>();

    RenderablePrimitiveCube* renderable = new RenderablePrimitiveCube("CubeRenderable", cubeObject);
    renderable->initialize();
}

int main(int argc, char** argv)
{
    TextureResourceLoader_BMP blergh;
    TextureResourceLoader_PNG urgh;
    MaterialResourceLoader blag;
    D3D11UncompiledShaderResourceLoader blugg;

    OcularEngine.initialize(new D3D11GraphicsDriver());
    SystemInfo::logSystemInfo();

    if(openWindow())
    {
        setupScene();
        while(OcularEngine.run());
    }

    OcularEngine.shutdown();
}