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
#include "Widgets/ScenePropertiesDialog.hpp"

#include "Widgets/Properties/Types/ColorProperty.hpp"
#include "Widgets/Properties/Types/Arithmetic/FloatProperty.hpp"

//------------------------------------------------------------------------------------------

namespace
{
    const char* BoldStyle = "font-weight: 600;";
}

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ScenePropertiesDialog::ScenePropertiesDialog(QWidget* parent)
            : QDialog(parent)
        {
            setWindowTitle("Scene Properties");
            setStyleSheet(GeneralStyles::windowStyle);
            setMinimumSize(QSize(400, 400));
            resize(QSize(400, 400));

            buildWidgets();
        }

        ScenePropertiesDialog::~ScenePropertiesDialog()
        {

        }
        
        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void ScenePropertiesDialog::buildWidgets()
        {
            m_MainLayout = new QVBoxLayout();
            
            buildScrollArea();
            buildActionButtons();
            buildProperties();

            setLayout(m_MainLayout);
        }

        void ScenePropertiesDialog::buildScrollArea()
        {
            m_ScrollLayout = new QVBoxLayout();
            m_ScrollLayout->setAlignment(Qt::AlignTop);
            
            m_ScrollArea = new QScrollArea();
            m_ScrollArea->setLayout(m_ScrollLayout);
            m_ScrollArea->setStyleSheet("QScrollArea{ border: 0px solid black; background-color: rgb(56, 56, 60); }");
            
            m_MainLayout->addWidget(m_ScrollArea);
        }

        void ScenePropertiesDialog::buildActionButtons()
        {
            m_ActionButtonLayout = new QHBoxLayout();

            m_ButtonOK = new QPushButton("OK");
            connect(m_ButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
            m_ActionButtonLayout->addWidget(m_ButtonOK);

            m_ButtonCancel = new QPushButton("Cancel");
            connect(m_ButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
            m_ActionButtonLayout->addWidget(m_ButtonCancel);
            
            m_ButtonApply = new QPushButton("Apply");
            connect(m_ButtonApply, SIGNAL(clicked()), this, SLOT(onApply()));
            m_ActionButtonLayout->addWidget(m_ButtonApply);

            m_MainLayout->addLayout(m_ActionButtonLayout);
        }

        void ScenePropertiesDialog::buildProperties()
        {
            buildLightProperties();
            buildSceneTreeProperties();
            buildRendererProperties();
        }

        void ScenePropertiesDialog::buildLightProperties()
        {
            m_LightPropertiesLabel = new QLabel("Lighting Properties");
            m_LightPropertiesLabel->setStyleSheet(BoldStyle);

            m_AmbientIntensityProperty = OcularEditor.createPropertyWidget("Ambient Intensity", Utils::TypeName<float>::name);
            m_AmbientIntensityProperty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            Core::ExposedVariable intensityVar("Intensity", Utils::TypeName<float>::name, &m_AmbientIntensity, false, false);
            m_AmbientIntensity = OcularLights->getAmbientLightIntensity();
            m_AmbientIntensityProperty->setVariable(intensityVar);
            m_AmbientIntensityProperty->updateProperties();

            m_AmbientColorProperty = OcularEditor.createPropertyWidget("Ambient Color", Utils::TypeName<Core::Color>::name);
            m_AmbientColorProperty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            Core::ExposedVariable colorVar("Color", Utils::TypeName<Core::Color>::name, &m_AmbientColor, false, false);
            m_AmbientColor = OcularLights->getAmbientLightColor();
            m_AmbientColorProperty->setVariable(colorVar);
            m_AmbientColorProperty->updateProperties();

            m_ScrollLayout->addWidget(m_LightPropertiesLabel);
            m_ScrollLayout->addWidget(m_AmbientIntensityProperty);
            m_ScrollLayout->addWidget(m_AmbientColorProperty);
            m_ScrollLayout->addSpacerItem(new QSpacerItem(1, 25));
        }

        void ScenePropertiesDialog::buildSceneTreeProperties()
        {
            m_SceneTreePropertiesLabel = new QLabel("SceneTree Properties");
            m_SceneTreePropertiesLabel->setStyleSheet(BoldStyle);

            m_SceneTreeStaticProperty = OcularEditor.createPropertyWidget("Static Tree", Utils::TypeName<std::string>::name);
            m_SceneTreeStaticProperty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            m_SceneTreeDynamicProperty = OcularEditor.createPropertyWidget("Dynamic Tree", Utils::TypeName<std::string>::name);
            m_SceneTreeDynamicProperty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            m_ScrollLayout->addWidget(m_SceneTreePropertiesLabel);
            m_ScrollLayout->addWidget(m_SceneTreeStaticProperty);
            m_ScrollLayout->addWidget(m_SceneTreeDynamicProperty);
            m_ScrollLayout->addSpacerItem(new QSpacerItem(1, 25));
        }

        void ScenePropertiesDialog::buildRendererProperties()
        {
            m_RendererPropertiesLabel = new QLabel("Renderer Properties");
            m_RendererPropertiesLabel->setStyleSheet(BoldStyle);

            m_RendererTypeProperty = OcularEditor.createPropertyWidget("Renderer Type", Utils::TypeName<std::string>::name);
            m_RendererTypeProperty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            
            m_ScrollLayout->addWidget(m_RendererPropertiesLabel);
            m_ScrollLayout->addWidget(m_RendererTypeProperty);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void ScenePropertiesDialog::onOK()
        {
            onApply();
            accept();
        }

        void ScenePropertiesDialog::onCancel()
        {
            accept();
        }

        void ScenePropertiesDialog::onApply()
        {
            // Apply lighting changes

            m_AmbientColorProperty->updateProperties();
            m_AmbientIntensityProperty->updateProperties();

            OcularLights->setAmbientLightColor(m_AmbientColor);
            OcularLights->setAmbientLightIntensity(m_AmbientIntensity);
        }
    }
}