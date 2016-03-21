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
#include "Widgets/Properties/CommonPropertiesDisplay.hpp"
#include "Widgets/Properties/RenderablePropertiesDisplay.hpp"
#include "Events/SceneObjectSelectedEvent.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PropertiesPanel::PropertiesPanel(QWidget *parent)
            : QFrame(parent)
        {
            OcularEvents->registerListener(this, Core::Priority::Low);
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            m_CommonProperties = new CommonPropertiesDisplay();
            m_RenderableProperties = new RenderablePropertiesDisplay();

            m_Layout = new QVBoxLayout();
            m_Layout->setAlignment(Qt::AlignTop);
            m_Layout->addWidget(m_CommonProperties);
            m_Layout->addWidget(m_RenderableProperties);
            m_Layout->setContentsMargins(2, 2, 2, 2);

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
            if(object)
            {
                m_CommonProperties->setObject(object);
                m_RenderableProperties->setObject(object);
            }
        }

        void PropertiesPanel::update()
        {
            m_CommonProperties->updateProperties();
            m_RenderableProperties->updateProperties();
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

            return true;    // Do not consume this event
        }

        void PropertiesPanel::displayCommon(Core::SceneObject* object)
        {

        }

        void PropertiesPanel::displayCustom(Core::SceneObject* object)
        {

        }

        void PropertiesPanel::displayRenderable(Core::SceneObject* object)
        {

        }

        void PropertiesPanel::displayRoutines(Core::SceneObject* object)
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}