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
#include "Widgets/MainFrame.hpp"
#include "Widgets/MainStatusBar.hpp"
#include "Widgets/ContentTab.hpp"
#include "Widgets/ToolBarCommon.hpp"

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
       
            QWidget* mainWidget = new QWidget(this);
            mainWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            mainWidget->setMinimumSize(QSize(1024, 768));

            QToolBar* toolBar = new QToolBar();
            toolBar->addAction("Test");

            QFrame* frame = new QFrame();
            frame->setMinimumSize(QSize(500, 500));
            frame->setLineWidth(2);
            frame->setFrameStyle(QFrame::Panel | QFrame::Raised);

            QFrame* renderFrame = new QFrame();
            renderFrame->setMinimumSize(QSize(250, 250));
            renderFrame->setLineWidth(1);
            renderFrame->setFrameStyle(QFrame::Panel | QFrame::Raised);

            QTabWidget* tabs = new QTabWidget();
            QWidget* tabA = new QWidget();
            QWidget* tabB = new QWidget();

            tabs->addTab(tabA, "Properties");
            tabs->addTab(tabB, "Scene Tree");


            QVBoxLayout* mainLayout = new QVBoxLayout();
            QHBoxLayout* frameLayout = new QHBoxLayout();

            frameLayout->addWidget(tabs);
            frameLayout->addWidget(renderFrame);

            frame->setLayout(frameLayout);

            mainLayout->addWidget(toolBar);
            mainLayout->addWidget(frame);

            mainWidget->setLayout(mainLayout);
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
            m_LayoutMain     = new QVBoxLayout();
            m_LayoutToolBars = new QVBoxLayout();
            m_LayoutContent  = new QHBoxLayout();
        }

        void MainWindow::setupMenus()
        {
            m_MenuBar = new MainMenuBar();
            setMenuBar((QMenuBar*)(m_MenuBar));

            m_StatusBar = new MainStatusBar();
            setStatusBar((QStatusBar*)(m_StatusBar));

            m_ToolBarCommon = new ToolBarCommon();
            m_LayoutToolBars->addWidget(m_ToolBarCommon);
        }

        void MainWindow::setupContentTab()
        {
            m_ContentTab = new ContentTab();
            m_LayoutContent->addWidget(m_ContentTab);
        }
    }
}