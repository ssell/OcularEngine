/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Gizmos/Axis/AxisGizmo.hpp"
#include "Gizmos/Axis/AxisComponentGizmo.hpp"
#include "Graphics/Texture/NoiseTexture2D.hpp"
#include "Graphics/Texture/TextureSavers/TextureResourceSaver_PNG.hpp"
#include "Math/Noise/PerlinNoise.hpp"
#include "Math/Noise/SimplexNoise.hpp"
#include "Math/Noise/WaveletNoise.hpp"
#include "OcularEngine.hpp"
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

                OcularResources->initialize();

                if(OcularGraphics->initialize())
                {
                    OcularResources->initializeDefaultResources();   // \todo really bad work around. trying to create default resources before driver is ready otherwise

                    if(setupEditorCamera())
                    {
                        setupAxis();
                        setupGizmos();

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

                if(cast->button == Core::MouseButtons::Left)
                {
                    // Check if alt key is down (we assume a rotation around target if it is down)
                    if(!OcularInput->isKeyboardKeyDown(Core::KeyboardKeys::AltLeft))
                    {
                        performMousePick(cast->state);
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

        void Editor::setSelectedObject(Core::SceneObject* object, bool ignoreNormalObject, bool ignoreGizmoObject)
        {
            std::shared_ptr<Core::AEvent> event = nullptr;

            m_GizmoTranslate->setSelected(false);

            if(object)
            {
                m_GizmoTranslate->setActive(true);

                Gizmo* gizmo = dynamic_cast<Gizmo*>(object);

                if(gizmo)
                {
                    // If the selected object was a gizmo (or part of a gizmo), we can not 
                    // set it as the selected object for obvious reasons.

                    // Instead we notify the gizmo that it has been selected (so that it can
                    // handle dragging, etc.) and maintain the current selected object.

                    if(!ignoreGizmoObject)
                    {
                        gizmo->setSelected(true);
                    }
                }
                else
                {
                    if(!ignoreNormalObject)
                    {
                        m_SelectedObject = object;

                        m_MainWindow->getContentFrame()->getSceneFrame()->getSceneTree()->selectObject(m_SelectedObject);
                        m_SelectedObject->addChild(m_GizmoTranslate, false);

                        event = std::make_shared<SceneObjectSelectedEvent>(m_SelectedObject);
                    }
                }
            }
            else
            {
                // Deselect

                m_GizmoTranslate->setActive(false);
                m_GizmoTranslate->setParent(nullptr, false);

                m_MainWindow->getContentFrame()->getSceneFrame()->getSceneTree()->selectObject(nullptr);

                event = std::make_shared<SceneObjectSelectedEvent>(nullptr);
            }

            if(event)
            {
                OcularEvents->queueEvent(event);
            }
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
                statusBar->setPermanentMessage(message.c_str());
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

            static std::string CommonNames[8] =
            {
                "m_IsActive",
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
                Core::PerspectiveProjection projection = m_EditorCamera->getPerspectiveProjection();
                projection.farClip = 10000.0f;

                m_EditorCamera->setProjectionPerspective(projection);
                m_EditorCamera->setPersistent(true);
                m_EditorCamera->setPosition(0.0f, 0.2f, 0.5f);
                m_EditorCamera->addRoutine("EditorCameraController");

                result = true;
            }

            return result;
        }

        void Editor::setupAxis()
        {
            const float length = 10000.0f;
            
            OcularGraphics->drawDebugLine(Math::Vector3f(0.0f, 0.0f, 0.0f), Math::Vector3f(length, 0.0f, 0.0f), Core::Color::Red(), 0);
            OcularGraphics->drawDebugLine(Math::Vector3f(0.0f, 0.0f, 0.0f), Math::Vector3f(0.0f, length, 0.0f), Core::Color::Green(), 0);
            OcularGraphics->drawDebugLine(Math::Vector3f(0.0f, 0.0f, 0.0f), Math::Vector3f(0.0f, 0.0f, length), Core::Color::Blue(), 0);
        }

        void Editor::setupGizmos()
        {
            m_GizmoTranslate = new AxisGizmo();
            m_GizmoTranslate->setName("OCULAR_INTERNAL_EDITOR_GIZMO_TRANSLATE");
            m_GizmoTranslate->setActive(false);
        }

        void Editor::performMousePick(Core::KeyState const state)
        {
            auto mousePos = OcularInput->getMousePosition();
            auto editorCamera = OcularEditor.getEditorCamera();

            if(editorCamera)
            {
                auto ray = editorCamera->getPickRay(mousePos);
                //OcularGraphics->drawDebugLine(ray.getOrigin(), ray.getPointAlong(100.0f), Core::Color::Yellow(), 15000);
                            
                std::vector<std::pair<Core::SceneObject*, float>> intersections;

                OcularScene->getIntersections(ray, intersections);

                if(intersections.size())
                {
                    if(state == Core::KeyState::Released)
                    {
                        // On mouse up, we only care about picking normal (non-gizmo) objects
                        setSelectedObject(intersections[0].first, false, true);
                    }
                    else
                    {
                        // On mouse down, we only care about picking gizmo objects
                        auto gizmo = pickedGizmo(intersections);

                        if(gizmo)
                        {
                            setSelectedObject(gizmo, true, false);
                        }
                    }
                }
                else
                {
                    // If the currently selected object is a gizmo, we simply de-select the gizmo but keep the parent object selected
                    if(m_GizmoTranslate->isSelected())
                    {
                        m_GizmoTranslate->setSelected(false);
                    }
                    else
                    {
                        // No object selected. Treat it as a de-select.
                        setSelectedObject(nullptr, false, true);
                    }
                }
            }
        }

        Core::SceneObject* Editor::pickedGizmo(std::vector<std::pair<Core::SceneObject*, float>> const& intersections) const
        {
            // Check if among the picked items is a gizmo object. If so, we will assume that was the intended pick target.
            Core::SceneObject* result = nullptr;

            for(auto pair : intersections)
            {
                auto object = pair.first;

                if(object)
                {
                    if(OcularString->IsEqual(object->getClass(), OCULAR_TYPE_NAME(AxisComponentGizmo)))
                    {
                        result = object;
                        break;
                    }
                }
            }

            return result;
        }
    }
}