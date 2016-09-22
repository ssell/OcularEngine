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
#include "Widgets/MaterialEditorDialog.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MaterialEditorDialog::MaterialEditorDialog(QWidget* parent)
            : QDialog(parent)
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

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void MaterialEditorDialog::buildWidgets()
        {
            m_MainLayout = new QHBoxLayout();

            buildMaterialTree();
            buildPropertyPanel();
            buildActionButtons();

            setLayout(m_MainLayout);
        }

        void MaterialEditorDialog::buildMaterialTree()
        {
            m_MaterialTreeFrame = new QFrame();
            m_MainLayout->addWidget(m_MaterialTreeFrame);
        }

        void MaterialEditorDialog::buildPropertyPanel()
        {
            m_PropertyPanelLayout = new QVBoxLayout();
            
            m_PropertyPanelFrame = new QFrame();
            m_PropertyPanelLayout->addWidget(m_PropertyPanelFrame);

            m_MainLayout->addLayout(m_PropertyPanelLayout);
        }

        void MaterialEditorDialog::buildActionButtons()
        {
            m_ActionButtonLayout = new QHBoxLayout();
            m_ActionButtonFrame = new QFrame();

            m_ButtonOK = new QPushButton("OK");
            connect(m_ButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
            m_ActionButtonLayout->addWidget(m_ButtonOK);

            m_ButtonCancel = new QPushButton("Cancel");
            connect(m_ButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
            m_ActionButtonLayout->addWidget(m_ButtonCancel);
            
            m_ButtonApply = new QPushButton("Apply");
            connect(m_ButtonApply, SIGNAL(clicked()), this, SLOT(onApply()));
            m_ActionButtonLayout->addWidget(m_ButtonApply);

            m_ActionButtonFrame->setLayout(m_ActionButtonLayout);
            m_PropertyPanelLayout->addWidget(m_ActionButtonFrame);
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