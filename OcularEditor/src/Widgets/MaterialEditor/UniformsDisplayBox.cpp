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
#include "Widgets/MaterialEditor/UniformsDisplayBox.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        UniformsDisplayBox::UniformsDisplayBox(QWidget* parent)
            : MaterialPropertiesDisplayBox("Uniforms", parent)
        {
            buildWidgets();
        }

        UniformsDisplayBox::~UniformsDisplayBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void UniformsDisplayBox::setMaterial(Graphics::Material* material)
        {
            MaterialPropertiesDisplayBox::setMaterial(material);

            if(material)
            {
                auto uniformBuffer = material->getUniformBuffer();

                if(uniformBuffer)
                {
                    m_Properties.resize(uniformBuffer->getNumUniforms(), nullptr);

                    for(uint32_t i = 0; i < m_Properties.size(); ++i)
                    {
                        auto uniform = uniformBuffer->getUniform(i);

                        if(uniform->getSize())
                        {
                            // Not an empty uniform
                            m_Properties[i] = OcularEditor.createPropertyWidget(uniform->getName(), uniform->getType());
                            m_Properties[i]->setValue(void_cast<const float*>(uniform->getData()), uniform->getSize() * sizeof(float));
                        }
                        else
                        {
                            // Empty uniform
                            m_Properties[i] = OcularEditor.createPropertyWidget("Empty", Utils::TypeName<float>::name);
                        }

                        m_UniformLayout->addWidget(m_Properties[i]);
                    }
                }
            }
        }

        void UniformsDisplayBox::updateProperties()
        {

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void UniformsDisplayBox::buildWidgets()
        {
            m_UniformLayout = new QVBoxLayout();
            m_Layout->addLayout(m_UniformLayout);

            buildNewUniformWidget();
        }

        void UniformsDisplayBox::buildNewUniformWidget()
        {
            //------------------------------------------------------------
            // Build layouts and frames

            m_NewUniformLayout      = new QHBoxLayout();
            m_NewUniformLeftLayout  = new QHBoxLayout();
            m_NewUniformRightLayout = new QHBoxLayout();

            m_NewUniformLayout->setContentsMargins(5, 0, 5, 0);

            m_NewUniformLeftFrame  = new QFrame();
            m_NewUniformRightFrame = new QFrame();

            //------------------------------------------------------------
            // Build left side

            m_NewUniformNameEdit = new QLineEdit("New Uniform");

            m_NewUniformLeftLayout->addWidget(m_NewUniformNameEdit);
            m_NewUniformLeftFrame->setLayout(m_NewUniformLeftLayout);
            m_NewUniformLeftFrame->setFixedWidth(115);

            m_NewUniformLayout->addWidget(m_NewUniformLeftFrame);

            //------------------------------------------------------------
            // Build right side

            m_NewUniformTypeCombo = new QComboBox();
            m_NewUniformTypeCombo->addItem("float");
            m_NewUniformTypeCombo->addItem("Color");
            m_NewUniformTypeCombo->addItem("Vector4f");
            m_NewUniformTypeCombo->addItem("Matrix3x3");
            m_NewUniformTypeCombo->addItem("Matrix4x4");
            m_NewUniformRightLayout->addWidget(m_NewUniformTypeCombo);

            m_NewUniformAddButton = new QPushButton("Add");
            m_NewUniformAddButton->setFixedWidth(50);
            m_NewUniformAddButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
            m_NewUniformRightLayout->addWidget(m_NewUniformAddButton);

            connect(m_NewUniformAddButton, SIGNAL(clicked()), this, SLOT(onUniformAdded()));

            m_NewUniformRightFrame->setLayout(m_NewUniformRightLayout);
            m_NewUniformLayout->addWidget(m_NewUniformRightFrame);

            //------------------------------------------------------------
            
            m_Layout->addLayout(m_NewUniformLayout);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void UniformsDisplayBox::onUniformAdded()
        {
            PropertyWidget* newProperty = OcularEditor.createPropertyWidget(m_NewUniformNameEdit->text().toStdString(), m_NewUniformTypeCombo->currentText().toStdString());

            if(newProperty)
            {
                m_Properties.push_back(newProperty);
                m_UniformLayout->addWidget(newProperty);
            }
        }
    }
}