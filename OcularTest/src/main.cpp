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

#include "Shader/D3D11VertexShader.hpp"
#include "Shader/D3D11FragmentShader.hpp"

#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

Ocular::Core::EventSnooper g_Snooper;

using namespace Ocular::Core;
using namespace Ocular::Utils;
using namespace Ocular::Math;
using namespace Ocular::Graphics;
using namespace DirectX;

static D3D11GraphicsDriver* driver = nullptr;
static ID3D11Device* d3dDevice = nullptr;
static ID3D11DeviceContext* d3dDeviceContext = nullptr;
static IDXGISwapChain* d3dSwapChain = nullptr;

static ID3D11RasterizerState* d3dRasterizerState = nullptr;
static ID3D11DepthStencilState* d3dDepthStencilState = nullptr;

static ID3D11Buffer* d3dVertexBuffer = nullptr;
static ID3D11Buffer* d3dIndexBuffer = nullptr;

static ID3D11Texture2D* d3dRTVTexture = nullptr;
static ID3D11RenderTargetView* d3dRTV = nullptr;

static ID3D11Texture2D* d3dDSVTexture = nullptr;
static ID3D11DepthStencilView* d3dDSV = nullptr;

static ID3D11InputLayout* d3dInputLayout = nullptr;

static ID3D11VertexShader* d3dVS = nullptr;
static ID3D10Blob* d3dBlobVS = nullptr;

static ID3D11PixelShader* d3dPS = nullptr;
static ID3D10Blob* d3dBlobPS = nullptr;

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