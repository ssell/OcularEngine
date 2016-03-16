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
#include "D3D11GraphicsDriver.hpp"
#include "D3D11DynamicRegistration.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        Editor& Editor::get()
        {
            static Editor instance;
            return instance;
        }

        Editor::Editor()
        {

        }

        Editor::~Editor()
        {
            delete m_MainWindow;
            delete m_QtApp;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool Editor::initialize(int argc, char** argv)
        {
            bool result = false;

            m_QtApp = new QApplication(argc, argv);

            if(OcularEngine.initialize(new Ocular::Graphics::D3D11GraphicsDriver()))
            {
                m_MainWindow = new MainWindow();
                m_MainWindow->show();
                m_MainWindow->showMaximized();

                if(OcularGraphics->initialize())
                {
                    if(setupEditorCamera())
                    {
                        result = true;
                    }
                }
            }

            return result;
        }

        void Editor::shutdown()
        {
            OcularEngine.shutdown();
        }

        bool Editor::run()
        {
            bool result = false;

            if(OcularEngine.run())
            {
                m_MainWindow->update();
                m_QtApp->processEvents();
                
                result = true;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // Getters
        //----------------------------------------------------------------------------------

        MainWindow* Editor::getMainWindow()
        {
            return m_MainWindow;
        }

        Core::Camera* Editor::getEditorCamera()
        {
            return m_EditorCamera;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        bool Editor::setupEditorCamera()
        {
            bool result = false;

            m_EditorCamera = OcularScene->createObject<Core::Camera>("OCULAR_INTERNAL_EDITOR_CAMERA", nullptr);
            
            if(m_EditorCamera)
            {
                m_EditorCamera->setPersistent(true);
                m_EditorCamera->setPosition(0.0f, 0.2f, 0.5f);
                m_EditorCamera->addRoutine("EditorCameraController");

                result = true;
            }

            return result;
        }
    }
}