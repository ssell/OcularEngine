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

Ocular::Core::EventSnooper g_Snooper;

using namespace Ocular::Core;
using namespace Ocular::Utils;

//------------------------------------------------------------------------------------------

int runTests(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

bool openWindow()
{
    bool result = false;

    Ocular::Core::WindowDescriptor descriptor;

    descriptor.displayName   = "Ocular Engine";
    descriptor.width         = 800;
    descriptor.height        = 600;
    descriptor.colorBits     = 8;
    descriptor.depthBits     = 8;
    descriptor.stencilBits   = 8;
    descriptor.displayMode   = Ocular::Core::WindowDisplayMode::WindowedBordered;
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

int main(int argc, char** argv)
{
    Ocular::Graphics::TextureResourceLoader_BMP blergh;
    Ocular::Graphics::D3D11UncompiledShaderResourceLoader force;

    OcularEngine.initialize(new Ocular::Graphics::D3D11GraphicsDriver());
    Ocular::Core::SystemInfo::logSystemInfo();

    if(openWindow())
    {
        Ocular::Graphics::ShaderProgram* shader = OcularResources->getResource<Ocular::Graphics::ShaderProgram>("Shaders\\TestShader");

        if(shader)
        {
            int success = 0;
            success++;
        }

        SceneObject* object = OcularScene->createObject("Test Object");
        object->addRoutine("InputLogger");

        while(OcularEngine.run());
    }

    OcularEngine.shutdown();
}