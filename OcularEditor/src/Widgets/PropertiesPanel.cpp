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
#include "Widgets/PropertiesPanel.hpp"
#include "Widgets/Properties/CommonDisplay.hpp"
#include "Widgets/Properties/CustomObjectDisplay.hpp"
#include "Widgets/Properties/RenderableDisplay.hpp"
#include "Widgets/Properties/RoutineDisplay.hpp"
#include "Events/Events/SceneObjectRemovedEvent.hpp"
#include "Events/SceneObjectSelectedEvent.hpp"
#include "Scene/ARoutine.hpp"

#define SAFE_REMOVE(X) if(X){ m_Layout->removeWidget(X); delete X; X = nullptr; }

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PropertiesPanel::PropertiesPanel(QWidget *parent)
            : QFrame(parent),
              m_CurrentObject(nullptr),
              m_CommonProperties(nullptr),
              m_CustomProperties(nullptr),
              m_RenderableProperties(nullptr)
        {
            OcularEvents->registerListener(this, Core::Priority::Low);
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setStyleSheet("QFrame { background-color: rgb(56, 56, 60); }");

            m_Layout = new QVBoxLayout();
            m_Layout->setAlignment(Qt::AlignTop);
            m_Layout->setContentsMargins(0, 20, 0, 10);

            setLayout(m_Layout);
        }

        PropertiesPanel::~PropertiesPanel()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize PropertiesPanel::sizeHint() const
        {
            return QSize(275, 500);
        }

        void PropertiesPanel::selectObject(Core::SceneObject* object)
        {
            if(object != m_CurrentObject)
            {
                m_CurrentObject = object;
                
                if(m_CurrentObject)
                {
                    m_CurrentObjectUUID = object->getUUID();
                }

                initializeCommon();
                initializeCustom();
                initializeRenderable();
                initializeRoutines();
            }
        }

        void PropertiesPanel::update()
        {
            if(m_CurrentObject)
            {
                if(m_CommonProperties)
                {
                    m_CommonProperties->updateProperties();
                }

                if(m_CustomProperties)
                {
                    m_CustomProperties->updateProperties();
                }

                if(m_RenderableProperties)
                {
                    m_RenderableProperties->updateProperties();
                }

                for(auto routine : m_RoutineProperties)
                {
                    if(routine)
                    {
                        routine->updateProperties();
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool PropertiesPanel::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            if(event->isType<SceneObjectSelectedEvent>())
            {
                SceneObjectSelectedEvent* objectEvent = dynamic_cast<SceneObjectSelectedEvent*>(event.get());

                if(objectEvent)
                {
                    selectObject(objectEvent->object);
                }
            }
            else if(event->isType<Core::SceneObjectRemovedEvent>())
            {
                Core::SceneObjectRemovedEvent* objectEvent = dynamic_cast<Core::SceneObjectRemovedEvent*>(event.get());

                if(objectEvent)
                {
                    if(objectEvent->uuid == m_CurrentObjectUUID)
                    {
                        m_CurrentObject = nullptr;
                        objectDeselected();
                    }
                }
            }
            
            return true;    // Do not consume this event
        }

        void PropertiesPanel::objectDeselected()
        {
            SAFE_REMOVE(m_CommonProperties);
            SAFE_REMOVE(m_CustomProperties);
            SAFE_REMOVE(m_RenderableProperties);
            
            for(auto routine : m_RoutineProperties)
            {
                SAFE_REMOVE(routine);
            }

            m_RoutineProperties.clear();
        }

        void PropertiesPanel::initializeCommon()
        {
            SAFE_REMOVE(m_CommonProperties);

            if(m_CurrentObject)
            {
                m_CommonProperties = new CommonDisplay();
                m_CommonProperties->setObject(m_CurrentObject);

                m_Layout->addWidget(m_CommonProperties);
            }
        }

        void PropertiesPanel::initializeCustom()
        {
            SAFE_REMOVE(m_CustomProperties);

            if(m_CurrentObject)
            {
                const std::string type = m_CurrentObject->getClass();

                if(!Utils::String::IsEqual(type, "SceneObject"))
                {
                    // If not a generic SceneObject implementation
                    m_CustomProperties = OcularEditor.createCustomDisplay(type);

                    if(m_CustomProperties == nullptr)
                    {
                        // If no registered custom display for the object type then use a generic CustomObjectDisplay
                        m_CustomProperties = new CustomObjectDisplay();
                        m_CustomProperties->setTitle(type.c_str());
                    }
                    
                    m_CustomProperties->setObject(m_CurrentObject);
                    m_Layout->addWidget(m_CustomProperties);
                }
            }
        }

        void PropertiesPanel::initializeRenderable()
        {
            SAFE_REMOVE(m_RenderableProperties);

            if(m_CurrentObject)
            {
                auto renderable = m_CurrentObject->getRenderable();

                if(renderable)
                {
                    m_RenderableProperties = new RenderableDisplay();
                    m_RenderableProperties->setObject(m_CurrentObject);

                    m_Layout->addWidget(m_RenderableProperties);
                }
            }
        }

        void PropertiesPanel::initializeRoutines()
        {
            for(auto routine : m_RoutineProperties)
            {
                SAFE_REMOVE(routine);
            }

            m_RoutineProperties.clear();

            if(m_CurrentObject)
            {
                auto routines = m_CurrentObject->getAllRoutines();

                for(auto routine : routines)
                {
                    if(routine)
                    {
                        RoutineDisplay* routineDisplay = new RoutineDisplay(routine->getName());
                        routineDisplay->setObject(m_CurrentObject);
                        routineDisplay->setTitle(routine->getName().c_str());
                        
                        m_Layout->addWidget(routineDisplay);
                        m_RoutineProperties.push_back(routineDisplay);
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}