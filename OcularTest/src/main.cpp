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

#include "Scene/Renderables/RenderablePrimitiveCube.hpp"
#include "Renderer/Window/Window.hpp"

#include <DirectXMath.h>

Ocular::Core::EventSnooper g_Snooper;

using namespace Ocular::Core;
using namespace Ocular::Utils;
using namespace Ocular::Math;
using namespace Ocular::Graphics;
using namespace DirectX;

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
    descriptor.width         = 800;
    descriptor.height        = 600;
    descriptor.colorBits     = 8;
    descriptor.depthBits     = 8;
    descriptor.stencilBits   = 8;
    descriptor.displayMode   = WindowDisplayMode::WindowedBordered;
    descriptor.exclusiveMode = false;

    if(OcularEngine.WindowManager()->openWindow(descriptor))
    {
        if(OcularGraphics->initialize())
        {
            result = true;
        }
    }

    return result;
}

void testLoadMaterial()
{
    Material* material = OcularResources->getResource<Material>("Materials/Flat");

    if(material)
    {
        uint32_t success = 0;
        success++;
    }
    else
    {
        uint32_t failure = 0;
        failure++;
    }
}

void setupScene()
{
    OcularScene->loadScene("TestScene");

    //--------------------------------------------------------------------
    // Setup Camera

    Camera* mainCamera = OcularScene->createObject<Camera>("MainCamera", nullptr);
    mainCamera->setPriority(Priority::Low);
    mainCamera->setViewport(0.0f, 0.0f, 800.0f, 600.0f);
    mainCamera->setProjectionPerspective(60.0f, (800.0f / 600.0f), 0.1f, 1000.0f);
    mainCamera->setRenderTexture(OcularWindows->getMainWindow()->getRenderTexture());
    mainCamera->setDepthTexture(OcularWindows->getMainWindow()->getDepthTexture());

    //--------------------------------------------------------------------
    // Setup Input Logger

    SceneObject* inputObject = OcularScene->createObject("Test Object");
    inputObject->addRoutine("InputLogger");

    //--------------------------------------------------------------------
    // Setup Cube

    SceneObject* cubeObject = OcularScene->createObject("Cube");
    RenderablePrimitiveCube* renderable = new RenderablePrimitiveCube("CubeRenderable", cubeObject);
    renderable->initialize();




    

    
    Matrix4x4f ocularMatrix;
    XMMATRIX d3dMatrix;


    d3dMatrix = XMMatrixPerspectiveFovRH(60.0f, (800.0f / 600.0f), 0.1f, 1000.0f);
    ocularMatrix = Matrix4x4f::CreatePerspectiveMatrix(60.0f, (800.0f / 600.0f), 0.1f, 1000.0f);

    Matrix4x4f converted;

    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            converted[x][y] = d3dMatrix.r[x].m128_f32[y];
        }
    }

    mainCamera->setProjectionMatrix(converted);



    



    /*
     * Verifies the LookAt View Matrix
     *

    XMVECTOR eyePos;
    eyePos.m128_f32[0] = 0.0f;
    eyePos.m128_f32[1] = 0.0f;
    eyePos.m128_f32[2] = -5.0f;

    XMVECTOR lookAt;
    lookAt.m128_f32[0] = 0.0f;
    lookAt.m128_f32[1] = 0.0f;
    lookAt.m128_f32[2] = 0.0f;
    
    XMVECTOR upDir;
    upDir.m128_f32[0] = 0.0f;
    upDir.m128_f32[1] = 1.0f;
    upDir.m128_f32[2] = 0.0f;
    
    d3dMatrix = XMMatrixLookAtRH(eyePos, lookAt, upDir);
    ocularMatrix = Matrix4x4f::CreateLookAtMatrix(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    */



    //--------------------------------------------------------------------
    // Model Matrix

    XMMATRIX model = XMMatrixIdentity();

    //--------------------------------------------------------------------
    // View Matrix

    XMVECTOR eyePos;
    eyePos.m128_f32[0] = 0.0f;
    eyePos.m128_f32[1] = 0.0f;
    eyePos.m128_f32[2] = -5.0f;

    XMVECTOR lookAt;
    lookAt.m128_f32[0] = 0.0f;
    lookAt.m128_f32[1] = 0.0f;
    lookAt.m128_f32[2] = 0.0f;
    
    XMVECTOR upDir;
    upDir.m128_f32[0] = 0.0f;
    upDir.m128_f32[1] = 1.0f;
    upDir.m128_f32[2] = 0.0f;

    XMMATRIX view = XMMatrixLookAtRH(eyePos, lookAt, upDir);
    XMVECTOR determinant = XMMatrixDeterminant(view);

    view = XMMatrixInverse(&determinant, view);

    //--------------------------------------------------------------------
    // Projection Matrix

    XMMATRIX proj = XMMatrixPerspectiveFovRH(60.0f, (800.0f / 600.0f), 0.1f, 1000.0f);

    //---------------------------------------------------------------------
    // Model View Projection 

    XMMATRIX mvp = XMMatrixMultiply(XMMatrixMultiply(model, view), proj);

    int breakOnMe = 0;
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