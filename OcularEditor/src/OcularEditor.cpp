/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Events/SceneObjectSelectedEvent.hpp"
#include "Events/SceneObjectFocusedEvent.hpp"
#include "Events/Events/MouseButtonInputEvent.hpp"

#include "Utilities/ColorPicker.hpp"

#include "Widgets/MainStatusBar.hpp"
#include "Widgets/MainWindow.hpp"
#include "Widgets/ContentFrame.hpp"
#include "Widgets/SceneFrame.hpp"
#include "Widgets/SceneTree.hpp"
#include "Widgets/Properties/Renderables/RenderableDisplay.hpp"

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
            : AEventListener(),
              m_MainWindow(nullptr),
              m_EditorCamera(nullptr),
              m_SelectedObject(nullptr),
              m_FocusedObject(nullptr)
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
        
        //----------------------------------------------------------------------------------
        // Core Lifetime Methods
        //----------------------------------------------------------------------------------

        bool Editor::initialize(int argc, char** argv)
        {
            bool result = false;

            m_QtApp = new QApplication(argc, argv);

            if(OcularEngine.initialize(new Ocular::Graphics::D3D11GraphicsDriver()))
            {
                OcularEvents->registerListener(this, Core::Priority::Low);

                m_MainWindow = new MainWindow();
                m_MainWindow->show();
                m_MainWindow->showMaximized();

                if(OcularGraphics->initialize())
                {
                    OcularResources->initialize();   // \todo really bad work around. trying to create default resources before driver is ready otherwise

                    if(setupEditorCamera())
                    {
                        result = true;
                        OcularLogger->info("Successfully initialized ", OCULAR_VERSION);
                    }
                    else
                    {
                        OcularLogger->error("Failed to initialize Ocular Editor: failed to setup Editor cameras");
                    }
                }
                else
                {
                    OcularLogger->error("Failed to initialize Ocular Editor: failed to initialize Ocular Graphics system");
                }
            }
            else
            {
                OcularLogger->error("Failed to initialize Ocular Editor: failed to initialize Ocular Engine");
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

        bool Editor::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            if(event->isType<SceneObjectSelectedEvent>())
            {
                SceneObjectSelectedEvent* cast = dynamic_cast<SceneObjectSelectedEvent*>(event.get());
                m_SelectedObject = cast->object;
            }
            else if(event->isType<SceneObjectFocusedEvent>())
            {
                SceneObjectFocusedEvent* cast = dynamic_cast<SceneObjectFocusedEvent*>(event.get());
                m_FocusedObject = cast->object;
            }
            else if(event->isType<Core::MouseButtonInputEvent>())
            {
                Core::MouseButtonInputEvent* cast = dynamic_cast<Core::MouseButtonInputEvent*>(event.get());

                if((cast->button == Core::MouseButtons::Left) &&
                   (cast->state == Core::KeyState::Released))
                {
                    auto viewport = m_EditorCamera->getViewport();
                    auto mousePos = OcularInput->getMousePosition();

                    const uint32_t mouseX = static_cast<uint32_t>(mousePos.x);
                    const uint32_t mouseY = static_cast<uint32_t>(mousePos.y);

                    auto pickedObject = Utils::ColorPicker::Pick(m_EditorCamera, mouseX, mouseY);
                    
                    if(pickedObject)
                    {
                        m_MainWindow->getContentFrame()->getSceneFrame()->getSceneTree()->selectObject(pickedObject->getUUID());
                    }
                }
            }

            return true;
        }

        //----------------------------------------------------------------------------------
        // Primary Getters
        //----------------------------------------------------------------------------------

        MainWindow* Editor::getMainWindow() const
        {
            return m_MainWindow;
        }

        Core::Camera* Editor::getEditorCamera() const
        {
            return m_EditorCamera;
        }

        Core::SceneObject* Editor::getSelectedObject() const
        {
            return m_SelectedObject;
        }

        Core::SceneObject* Editor::getFocusedObject() const
        {
            return m_FocusedObject;
        }
        
        //----------------------------------------------------------------------------------
        // Misc Methods
        //----------------------------------------------------------------------------------

        void Editor::setStatusNormal(std::string const& message)
        {
            auto statusBar = m_MainWindow->getMainStatusBar();

            if(statusBar)
            {
                statusBar->addWidget(new QLabel(message.c_str()));
            }
        }

        void Editor::setStatusPermanent(std::string const& message)
        {
            auto statusBar = m_MainWindow->getMainStatusBar();

            if(statusBar)
            {
                statusBar->addPermanentWidget(new QLabel(message.c_str()));
            }
        }

        void Editor::setStatusTemporary(std::string const& message, uint32_t const lifetime)
        {
            auto statusBar = m_MainWindow->getMainStatusBar();

            if(statusBar)
            {
                statusBar->showMessage(message.c_str(), lifetime);
            }
        }

        void Editor::setStatusNormalProgress(std::string const& message, uint32_t const progress)
        {
            throw std::exception("implement me");
        }
        
        //----------------------------------------------------------------------------------
        // Widget Factories
        //----------------------------------------------------------------------------------

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

        RenderableDisplay* Editor::createRenderableDisplay(std::string const& type)
        {
            RenderableDisplay* result = m_RenderableDisplayFactory.createComponent(type);

            if(result)
            {
                result->setTitle(type.c_str());
            }

            return result;
        }

        Core::ComponentFactory<RenderableDisplay>& Editor::getRenderableDisplayFactory()
        {
            return m_RenderableDisplayFactory;
        }
        
        //----------------------------------------------------------------------------------
        // Static Methods
        //----------------------------------------------------------------------------------

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