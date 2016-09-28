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

#include "Widgets/MaterialEditor/MaterialEditorDialog.hpp"
#include "Widgets/MaterialEditor/MaterialTree.hpp"
#include "Widgets/MaterialEditor/MaterialPropertiesPanel.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MaterialEditorDialog::MaterialEditorDialog(QWidget* parent)
            : QDialog(parent),
              m_MaterialTree(nullptr),
              m_MaterialProperties(nullptr)
        {
            setWindowTitle("Material Editor");
            setStyleSheet(GeneralStyles::windowStyle);
            setMinimumSize(QSize(800, 600));
            resize(QSize(400, 400));

            buildWidgets();
        }

        MaterialEditorDialog::~MaterialEditorDialog()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void MaterialEditorDialog::showEvent(QShowEvent* event)
        {
            if(m_MaterialTree)
            {
                m_MaterialTree->refresh();
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void MaterialEditorDialog::buildWidgets()
        {
            m_MainLayout = new QHBoxLayout();

            buildLeftSide();
            buildRightSide();

            setLayout(m_MainLayout);
        }

        void MaterialEditorDialog::buildLeftSide()
        {
            // Takes up left third of the dialog.
            // Consists of a frame, frame layout, and tree widget added to frame layout.
            
            //------------------------------------------------------------
            // Left-Side Frame
            //------------------------------------------------------------
            
            m_MaterialTreeLayout = new QVBoxLayout();

            m_LeftFrame = new QFrame();
            m_LeftFrame->setLayout(m_MaterialTreeLayout);

            QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            sizePolicy.setHorizontalStretch(1);
            m_LeftFrame->setSizePolicy(sizePolicy);

            m_MainLayout->addWidget(m_LeftFrame);

            //------------------------------------------------------------
            // "Materials" GroupBox
            //------------------------------------------------------------

            m_MaterialGroupLayout = new QVBoxLayout();
            m_MaterialGroupLayout->setContentsMargins(1, 25, 1, 5);

            m_MaterialGroupBox = new QGroupBox("Materials");
            m_MaterialGroupBox->setLayout(m_MaterialGroupLayout);

            m_MaterialTreeLayout->addWidget(m_MaterialGroupBox);

            //------------------------------------------------------------
            // Material Tree Widget
            //------------------------------------------------------------

            m_MaterialTree = new MaterialTree();
            m_MaterialGroupLayout->addWidget(m_MaterialTree);
        }

        void MaterialEditorDialog::buildRightSide()
        {
            m_RightLayout = new QVBoxLayout();
            
            m_RightFrame = new QFrame();
            m_RightFrame->setLayout(m_RightLayout);

            QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            sizePolicy.setHorizontalStretch(2);
            m_RightFrame->setSizePolicy(sizePolicy);

            m_MainLayout->addWidget(m_RightFrame);

            buildPropertyPanel();
            buildActionButtons();
        }

        void MaterialEditorDialog::buildPropertyPanel()
        {
            m_PropertyGroupLayout = new QVBoxLayout();
            m_PropertyGroupLayout->setAlignment(Qt::AlignTop);
            m_PropertyGroupLayout->setContentsMargins(0, 16, 0, 5);

            m_PropertyGroupBox = new QGroupBox("Properties");
            m_PropertyGroupBox->setLayout(m_PropertyGroupLayout);

            m_MaterialProperties = new MaterialPropertiesPanel();

            QScrollArea* scroll = new QScrollArea();
            scroll->setStyleSheet("QScrollArea{ background-color: rgba(0,0,0,0); border: 0px solid black; }");
            scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
            scroll->setWidget(m_MaterialProperties);
            scroll->setWidgetResizable(true);
            scroll->setLayout(new QVBoxLayout());

            m_PropertyGroupLayout->addWidget(scroll);

            m_RightLayout->addWidget(m_PropertyGroupBox);
        }

        void MaterialEditorDialog::buildActionButtons()
        {
            m_ActionButtonLayout = new QHBoxLayout();
            m_ActionButtonFrame = new QFrame();

            m_ButtonOK = new QPushButton("OK");
            m_ButtonOK->setFixedSize(QSize(50, 30));
            connect(m_ButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
            m_ActionButtonLayout->addWidget(m_ButtonOK);

            m_ButtonCancel = new QPushButton("Cancel");
            m_ButtonCancel->setFixedSize(QSize(50, 30));
            connect(m_ButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
            m_ActionButtonLayout->addWidget(m_ButtonCancel);
            
            m_ButtonApply = new QPushButton("Apply");
            m_ButtonApply->setFixedSize(QSize(50, 30));
            connect(m_ButtonApply, SIGNAL(clicked()), this, SLOT(onApply()));
            m_ActionButtonLayout->addWidget(m_ButtonApply);

            m_ActionButtonFrame->setFixedHeight(50);
            m_ActionButtonFrame->setLayout(m_ActionButtonLayout);
            m_RightLayout->addWidget(m_ActionButtonFrame);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void MaterialEditorDialog::onOK()
        {
            onApply();
            hide();
        }

        void MaterialEditorDialog::onCancel()
        {
            hide();
        }

        void MaterialEditorDialog::onApply()
        {

        }
    }
}