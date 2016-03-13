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
#include "Widgets/Properties/Vector3Property.hpp"
#include "Widgets/Properties/QuatAsEulerProperty.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CommonPropertiesDisplay::CommonPropertiesDisplay(QWidget* parent)
            : QGroupBox("", parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            buildLayout();
            buildName();
            buildTransform();
        }

        CommonPropertiesDisplay::~CommonPropertiesDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize CommonPropertiesDisplay::sizeHint() const
        {
            return QSize(275, 150);
        }

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
            }
        }

        void CommonPropertiesDisplay::updateProperties()
        {
            m_PropertyPosition->updateProperties();
            m_PropertyRotation->updateProperties();
            m_PropertyScale->updateProperties();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void CommonPropertiesDisplay::buildLayout()
        {
            m_Layout = new QVBoxLayout();
            m_Layout->setAlignment(Qt::AlignTop);
            m_Layout->setContentsMargins(5, 5, 5, 5);

            setLayout(m_Layout);
        }

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