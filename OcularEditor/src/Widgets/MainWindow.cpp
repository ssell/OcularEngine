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

#include "Widgets/MainWindow.hpp"
#include "Widgets/MainMenuBar.hpp"
#include "Widgets/MainStatusBar.hpp"
#include "Widgets/ToolBarCommon.hpp"
#include "Widgets/ContentFrame.hpp"
#include "Widgets/RenderFrame.hpp"
#include "Widgets/SceneFrame.hpp"
#include "Widgets/DetailsFrame.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MainWindow::MainWindow(QWidget *parent)
            : QMainWindow(parent)
        {
            setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
       
            setupLayouts();
            setupMenus();
            setupToolBars();
            setupContent();
            setupMainWidget();

            setStyleSheet(GeneralStyles::windowStyle);
        }

        MainWindow::~MainWindow()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize MainWindow::sizeHint() const
        {
            return QSize(1024, 768);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void MainWindow::setupLayouts()
        {
            m_LayoutMain    = new QVBoxLayout();
            m_LayoutContent = new QHBoxLayout();
        }

        void MainWindow::setupMenus()
        {
            m_MenuBar = new MainMenuBar();
            m_StatusBar = new MainStatusBar();

            m_StatusBar->showMessage(tr("Ready"));

            setMenuBar((QMenuBar*)(m_MenuBar));
            setStatusBar((QStatusBar*)(m_StatusBar));
        }

        void MainWindow::setupMainWidget()
        {
            m_MainWidget = new QWidget();
            m_MainWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            m_MainWidget->setMinimumSize(QSize(1024, 700));
            
            m_MainWidget->setLayout(m_LayoutMain);
            setCentralWidget(m_MainWidget);
        }

        void MainWindow::setupToolBars()
        {
            m_ToolBarCommon = new ToolBarCommon();
            m_LayoutMain->addWidget(m_ToolBarCommon, 0, (Qt::AlignLeft | Qt::AlignTop));
        }

        void MainWindow::setupContent()
        {
            m_ContentFrame = new ContentFrame();
            m_SceneFrame   = new SceneFrame();
            m_RenderFrame  = new RenderFrame();
            m_DetailsFrame = new DetailsFrame();
            
            m_LayoutContent->addWidget(m_SceneFrame);
            m_LayoutContent->addWidget(m_RenderFrame, 1);
            m_LayoutContent->addWidget(m_DetailsFrame);

            m_ContentFrame->setLayout(m_LayoutContent);

            m_LayoutMain->addWidget(m_ContentFrame, 1, (Qt::AlignHCenter | Qt::AlignTop));
        }
    }
}