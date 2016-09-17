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
#include "Widgets/Properties/CommonDisplay.hpp"
#include "Widgets/Properties/PropertiesDisplayTitleBar.hpp"
#include "Widgets/Standard/LineEdit.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CommonDisplay::CommonDisplay(QWidget* parent)
            : PropertiesDisplayBox("", parent),
              m_LabelTransform(nullptr),
              m_LineName(nullptr),
              m_PropertyPosition(nullptr),
              m_PropertyRotation(nullptr),
              m_PropertyScale(nullptr),
              m_ActiveCheckBox(nullptr)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            buildName();
            buildTransform();

            m_TitleBar->hide();
        }

        CommonDisplay::~CommonDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void CommonDisplay::setObject(Core::SceneObject* object)
        {
            if(object)
            {
                //--------------------------------------------------------
                // Active
                //--------------------------------------------------------

                m_ActiveCheckBox->setChecked(object->isActive());
                m_ActiveCheckBox->wasEdited();

                //--------------------------------------------------------
                // Name
                //--------------------------------------------------------

                Core::ExposedVariable variable;

                object->getVariable("m_Name", variable);

                m_LineName->setText(void_cast<std::string>(variable.data).c_str());
                m_LineName->wasEdited();  // Reset edited flag

                //--------------------------------------------------------
                // Transform
                //--------------------------------------------------------

                Math::Transform* transform = &(object->getTransform());
                
                if(m_PropertyPosition)
                {
                    transform->getVariable("m_Position", variable);
                    m_PropertyPosition->setVariable(variable);
                }
                
                if(m_PropertyRotation)
                {
                    transform->getVariable("m_Rotation", variable);
                    m_PropertyRotation->setVariable(variable);
                }
                
                if(m_PropertyScale)
                {
                    transform->getVariable("m_Scale", variable);
                    m_PropertyScale->setVariable(variable);
                }

                m_Object = object;
            }
        }

        void CommonDisplay::updateProperties()
        {
            if(m_Object)
            {
                bool refresh = false;

                if(m_ActiveCheckBox)
                {
                    if(m_ActiveCheckBox->wasEdited())
                    {
                        m_Object->setActive(m_ActiveCheckBox->isChecked());
                    }
                    else
                    {
                        m_ActiveCheckBox->setChecked(m_Object->isActive());
                    }
                }

                if(m_LineName)
                {
                    if(m_LineName->wasEdited())
                    {
                        m_Object->setName(m_LineName->text().toStdString());
                    }
                }

                if(m_PropertyPosition)
                {
                    if(m_PropertyPosition->updateProperties())
                    {
                        m_Object->getTransform().onVariableModified("m_Position");
                        refresh = true;
                    }
                }

                if(m_PropertyRotation)
                {
                    if(m_PropertyRotation->updateProperties())
                    {
                        m_Object->getTransform().onVariableModified("m_Rotation");
                        refresh = true;
                    }
                }

                if(m_PropertyScale)
                {
                    if(m_PropertyScale->updateProperties())
                    {
                        m_Object->getTransform().onVariableModified("m_Scale");
                        refresh = true;
                    }
                }

                if(refresh)
                {
                    m_Object->getTransform().refresh();
                    m_Object->onVariableModified("m_Transform");
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void CommonDisplay::buildName()
        {
            m_NameActiveLayout = new QHBoxLayout();

            m_ActiveCheckBox = new CheckBox();
            m_ActiveCheckBox->resize(QSize(20, 20));
            m_ActiveCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            m_ActiveCheckBox->setStyleSheet("QCheckBox { margin-left: 5px; margin-right: -5px;}");

            m_LineName = new LineEdit(LineType::String);
            m_LineName->setStyleSheet("QLineEdit { margin-left: 0px; margin-right: 5px; }");

            m_NameActiveLayout->addWidget(m_ActiveCheckBox);
            m_NameActiveLayout->addWidget(m_LineName);

            m_Layout->addLayout(m_NameActiveLayout);
        }

        void CommonDisplay::buildTransform()
        {
            //m_LabelTransform   = new QLabel("Transform");
            m_PropertyPosition = OcularEditor.createPropertyWidget("Position", Utils::TypeName<Math::Vector3f>::name);
            m_PropertyRotation = OcularEditor.createPropertyWidget("Rotation", "QuatAsEuler");
            m_PropertyScale    = OcularEditor.createPropertyWidget("Scale", Utils::TypeName<Math::Vector3f>::name);
            
            //m_Layout->addWidget(m_LabelTransform);
            m_Layout->addWidget(m_PropertyPosition);
            m_Layout->addWidget(m_PropertyRotation);
            m_Layout->addWidget(m_PropertyScale);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}