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
#include "Widgets/Properties/CommonDisplay.hpp"

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
              m_PropertyScale(nullptr)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            buildName();
            buildTransform();
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
                // Name
                //--------------------------------------------------------

                Core::ExposedVariable variable;

                object->getVariable("m_Name", variable);
                m_LineName->setText(void_cast<std::string>(variable.data).c_str());

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

                if(m_PropertyPosition)
                {
                    if(m_PropertyPosition->updateProperties())
                    {
                        refresh = true;
                    }
                }

                if(m_PropertyRotation)
                {
                    if(m_PropertyRotation->updateProperties())
                    {
                        refresh = true;
                    }
                }

                if(m_PropertyScale)
                {
                    if(m_PropertyScale->updateProperties())
                    {
                        refresh = true;
                    }
                }

                if(refresh)
                {
                    m_Object->getTransform().refresh();
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void CommonDisplay::buildName()
        {
            m_LineName = new QLineEdit();
            m_Layout->addWidget(m_LineName);
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