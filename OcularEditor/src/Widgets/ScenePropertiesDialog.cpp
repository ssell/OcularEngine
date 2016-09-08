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

//------------------------------------------------------------------------------------------

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
            setStyleSheet(GeneralStyles::windowStyle);

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

            buildActionButtons();

            setLayout(m_MainLayout);
        }

        void ScenePropertiesDialog::buildActionButtons()
        {
            m_ButtonOK = new QPushButton("OK");
            connect(m_ButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
            m_MainLayout->addWidget(m_ButtonOK);

            m_ButtonCancel = new QPushButton("Cancel");
            connect(m_ButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
            m_MainLayout->addWidget(m_ButtonCancel);
            
            m_ButtonApply = new QPushButton("Apply");
            connect(m_ButtonApply, SIGNAL(clicked()), this, SLOT(onApply()));
            m_MainLayout->addWidget(m_ButtonApply);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void ScenePropertiesDialog::onOK()
        {
            accept();
        }

        void ScenePropertiesDialog::onCancel()
        {
            accept();
        }

        void ScenePropertiesDialog::onApply()
        {

        }
    }
}