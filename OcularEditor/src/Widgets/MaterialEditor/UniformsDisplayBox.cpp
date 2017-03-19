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
                        auto size = uniform->getSize();

                        if(size)
                        {
                            // Not an empty uniform
                            m_Properties[i] = OcularEditor.createPropertyWidget(uniform->getName(), uniform->getType());

                            if(size == 1)
                            {
                                m_Properties[i]->setValue(void_cast<float>(uniform->getData()[0]), sizeof(float));
                            }
                            else
                            {
                                m_Properties[i]->setValue(void_cast<const float*>(uniform->getData()), uniform->getSize() * sizeof(float));
                            }
                        }
                        else
                        {
                            // Empty uniform
                            m_Properties[i] = OcularEditor.createPropertyWidget("Empty", OCULAR_TYPE_NAME(float));
                        }

                        m_UniformLayout->addWidget(m_Properties[i]);
                    }
                }
            }
        }

        void UniformsDisplayBox::updateProperties()
        {

        }

        void UniformsDisplayBox::onApply()
        {
            if(m_Material)
            {
                uint32_t currRegister = 0;    // Keep track of current register incase we need to add new uniform
                auto uniformBuffer = m_Material->getUniformBuffer();

                if(uniformBuffer)
                {
                    for(auto prop : m_Properties)
                    {
                        if(prop)
                        {
                            const std::string name  = prop->getDisplayName();
                            const std::string value = prop->getValue();
                            const std::string type  = prop->getType();
                            
                            setUniform(name, currRegister, value, type);
                        }
                    }
                }
            }
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

        void UniformsDisplayBox::setUniform(std::string const& name, uint32_t& currRegister, std::string const& value, std::string const& type)
        {
            // Could do this purely abstractly, but I will allow myself this one ugly if/else chain...
            // (Plus the types supported as uniforms are much less volatile than general object properties)

            if(OcularString->IsEqual(type, OCULAR_TYPE_NAME(float)))
            {
                m_Material->setUniform(name, currRegister, OcularString->fromString<float>(value));
                currRegister += 1;
            }
            else if(OcularString->IsEqual(type, OCULAR_TYPE_NAME(Math::Vector4f)))
            {
                m_Material->setUniform(name, currRegister, OcularString->fromString<Math::Vector4f>(value));
                currRegister += 1;
            }
            else if(OcularString->IsEqual(type, OCULAR_TYPE_NAME(Core::Color)))
            {
                m_Material->setUniform(name, currRegister, OcularString->fromString<Core::Color>(value));
                currRegister += 1;
            }
            else if(OcularString->IsEqual(type, OCULAR_TYPE_NAME(Math::Matrix3x3)))
            {
                m_Material->setUniform(name, currRegister, OcularString->fromString<Math::Matrix3x3>(value));
                currRegister += 4;
            }
            else if(OcularString->IsEqual(type, OCULAR_TYPE_NAME(Math::Matrix4x4)))
            {
                m_Material->setUniform(name, currRegister, OcularString->fromString<Math::Matrix4x4>(value));
                currRegister += 4;
            }
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