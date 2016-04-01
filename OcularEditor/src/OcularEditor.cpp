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

#include <regex>

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

        PropertyWidget* Editor::createPropertyWidget(std::string const& displayName, std::string const& type)
        {
            PropertyWidget* result = m_PropertyWidgetFactory.createComponent(type);

            if(result)
            {
                result->setDisplayName(displayName);
            }

            return result;
        }

        Core::ComponentFactory<PropertyWidget>& Editor::getPropertyWidgetFactory()
        {
            return m_PropertyWidgetFactory;
        }

        PropertiesDisplayBox* Editor::createCustomDisplay(std::string const& type)
        {
            PropertiesDisplayBox* result = m_CustomDisplayFactory.createComponent(type);

            if(result)
            {
                result->setTitle(type.c_str());
            }

            return result;
        }

        Core::ComponentFactory<PropertiesDisplayBox>& Editor::getCustomDisplayFactory()
        {
            return m_CustomDisplayFactory;
        }

        bool Editor::IsCommonName(std::string const& name)
        {
            bool result = false;

            static std::string CommonNames[7] =
            {
                "m_Name",
                "m_Position",
                "m_Rotation",
                "m_Scale",
                "m_Class",
                "m_IsStatic",
                "m_ForcedVisible"
            };

            for(auto commonName : CommonNames)
            {
                if(Utils::String::IsEqual(name, commonName))
                {
                    result = true;
                    break;
                }
            }

            return result;
        }

        std::string Editor::FormatName(std::string const& name)
        {
            std::string result = name;

            //------------------------------------------------------------
            // Remove any "m_"

            // Do regex instead!

            if((result.size() > 2) && (result[0] == 'm') && (result[1] == '_'))
            {
                result = result.substr(2);
            }
            
            //------------------------------------------------------------
            // Split apart camel case

            const std::regex caseExp("([a-z0-9])([A-Z])");
            result = std::regex_replace(result, caseExp, "$1 $2");

            return result;
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