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

#include "stdafx.h"
#include "Widgets/MainWindow.hpp"

#include "D3D11GraphicsDriver.hpp"
#include "D3D11DynamicRegistration.hpp"
#include "Scene/Renderables/MeshRenderable.hpp"

#include <QtWidgets/QApplication>

using namespace Ocular::Core;
using namespace Ocular::Utils;
using namespace Ocular::Math;
using namespace Ocular::Graphics;

//------------------------------------------------------------------------------------------

void setupCamera()
{
    Camera* camera = OcularScene->createObject<Camera>(Ocular::Editor::Helpers::EditorCameraName, nullptr);

    if(camera)
    {
        camera->setPosition(0.0f, 0.2f, 0.5f);
        camera->addRoutine("EditorCameraController");
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
            renderable->setMesh("Meshes/cube_normals");
            renderable->setMaterial("Materials/Flat");
            renderable->getMaterial()->setUniform("Color", 0, Ocular::Math::Vector4f(0.0f, 1.0f, 0.0f, 1.0f));

            object->setPosition(Ocular::Math::Vector3f(5.0f, 0.0f, 0.0f));
            //object->setScale(5.0f, 5.0f, 5.0f);
        }
    }

    SceneObject* someChild = object->createChild("Some Child");

    if(someChild)
    {
        MeshRenderable* renderable = (MeshRenderable*)someChild->setRenderable("Mesh");

        if(renderable)
        {
            renderable->setMesh("Meshes/cube_normals");
            renderable->setMaterial("Materials/Flat");

            someChild->setPosition(Ocular::Math::Vector3f(-5.0f, -2.0f, 0.0f));
        }
    }
}

void setupScene()
{
    OcularScene->createScene("TestScene");
    
    setupCamera();
    setupVisual();
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    if(OcularEngine.initialize(new Ocular::Graphics::D3D11GraphicsDriver()))
    {
        Ocular::Editor::MainWindow mainWindow;

        mainWindow.show();
        mainWindow.showMaximized();

        if(OcularGraphics->initialize())
        {
            setupScene();

            while(OcularEngine.run())
            {
                application.processEvents();
            }
        }

        OcularEngine.shutdown();
    }

    return 0;
}
