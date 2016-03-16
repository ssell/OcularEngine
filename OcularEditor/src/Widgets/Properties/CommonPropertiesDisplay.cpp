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
#include "Widgets/Properties/CommonPropertiesDisplay.hpp"
#include "Widgets/Properties/Types/Vector3Property.hpp"
#include "Widgets/Properties/Types/QuatAsEulerProperty.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CommonPropertiesDisplay::CommonPropertiesDisplay(QWidget* parent)
            : PropertiesDisplayBox("", parent),
              m_LabelTransform(nullptr),
              m_LineName(nullptr),
              m_PropertyPosition(nullptr),
              m_PropertyRotation(nullptr),
              m_PropertyScale(nullptr)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            buildName();
            buildTransform();
        }

        CommonPropertiesDisplay::~CommonPropertiesDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void CommonPropertiesDisplay::setObject(Core::SceneObject* object)
        {
            if(object)
            {
                //--------------------------------------------------------
                // Name
                //--------------------------------------------------------

                Core::ExposedVariable variable;

                object->getVariable("m_Name", variable);
                m_LineName->setText(void_cast<std::string>(variable.data).c_str());

                //--------------------------------------------------------
                // Transform
                //--------------------------------------------------------

                Math::Transform* transform = &(object->getTransform());
                
                transform->getVariable("m_Position", variable);
                m_PropertyPosition->setVariable(variable);
                
                transform->getVariable("m_Rotation", variable);
                m_PropertyRotation->setVariable(variable);
                
                transform->getVariable("m_Scale", variable);
                m_PropertyScale->setVariable(variable);

                m_Object = object;
            }
        }

        void CommonPropertiesDisplay::updateProperties()
        {
            if(m_Object)
            {
                if(m_PropertyPosition->updateProperties() ||
                   m_PropertyRotation->updateProperties() ||
                   m_PropertyScale->updateProperties())
                {
                    m_Object->getTransform().refresh();
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void CommonPropertiesDisplay::buildName()
        {
            m_LineName = new QLineEdit();
            m_Layout->addWidget(m_LineName);
        }

        void CommonPropertiesDisplay::buildTransform()
        {
            m_LabelTransform   = new QLabel("Transform");
            m_PropertyPosition = new Vector3Property("Position");
            m_PropertyRotation = new QuatAsEulerProperty("Rotation");
            m_PropertyScale    = new Vector3Property("Scale");
            
            m_Layout->addWidget(m_LabelTransform);
            m_Layout->addWidget(m_PropertyPosition);
            m_Layout->addWidget(m_PropertyRotation);
            m_Layout->addWidget(m_PropertyScale);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}