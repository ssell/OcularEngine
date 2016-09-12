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

#include "Widgets/MainWindow.hpp"
#include "Widgets/MainMenuBar.hpp"
#include "Widgets/MainStatusBar.hpp"
#include "Widgets/ToolbarCommon.hpp"
#include "Widgets/ContentFrame.hpp"
#include "Widgets/PropertiesPanel.hpp"

#include "Utilities/StringComposer.hpp"

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
            setupToolbars();
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

        void MainWindow::update()
        {
            static float elapsedTime = 0.0f;
            elapsedTime += OcularClock->getDelta();

            if(elapsedTime > 0.1f)
            {
                m_ContentFrame->update();
                setFrameStatsMessage();

                elapsedTime = 0.0f;
            }
        }

        //----------------------------------------------------------------------------------
        // Getters
        //----------------------------------------------------------------------------------

        MainMenuBar* MainWindow::getMainMenu() const
        {
            return m_MenuBar;
        }

        MainStatusBar* MainWindow::getMainStatusBar() const
        {
            return m_StatusBar;
        }

        ToolbarCommon* MainWindow::getCommonToolbar() const
        {
            return m_ToolbarCommon;
        }

        ContentFrame* MainWindow::getContentFrame() const
        {
            return m_ContentFrame;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void MainWindow::setupLayouts()
        {
            m_LayoutMain = new QVBoxLayout();
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

        void MainWindow::setupToolbars()
        {
            m_ToolbarCommon = new ToolbarCommon();
            m_LayoutMain->addWidget(m_ToolbarCommon, 0, (Qt::AlignLeft | Qt::AlignTop));
        }

        void MainWindow::setupContent()
        {
            m_ContentFrame = new ContentFrame();
            m_LayoutMain->addWidget(m_ContentFrame, 1, (Qt::AlignHCenter | Qt::AlignTop));
        }
        
        std::string formatNumberStringui(uint32_t const value, uint32_t const totalSize)
        {
            std::string result = OcularEngine.StringUtils()->toString<uint32_t>(value);
            result.resize(totalSize, ' ');  // Artificial display limit of 9,999,999,999 for this temp solution

            return result;
        }

        std::string formatNumberStringf(float const value, uint32_t const totalSize)
        {
            std::string result = OcularEngine.StringUtils()->toString<float>(value);
            result.resize(totalSize, ' '); 

            return result;
        }

        void MainWindow::setFrameStatsMessage()
        {
            /**
             * Frame statistics message in the formats of:
             *
             *    FPS (#) MS (#) Draws (#) Tris (#)
             */

            const Graphics::FrameStats stats = OcularGraphics->getLastFrameStats();

            const float frameTime = OcularEngine.Clock()->getDelta();
            const uint32_t fps = static_cast<uint32_t>(1.0f / frameTime);   // Really lazy, inaccurate FPS...

            const std::string message = OCULAR_STRING_COMPOSER(
                "FPS: ", formatNumberStringui(fps, 10), 
                " RT: ", formatNumberStringf(frameTime, 10), 
                " #D: ", formatNumberStringui(stats.drawCalls, 10),
                " #T: ", formatNumberStringui(stats.triangleCount, 10),
                " #L: ", formatNumberStringui(stats.lineCount, 10),
                " #P: ", formatNumberStringui(stats.pointCount, 10), "");

            OcularEditor.setStatusPermanent(message.c_str());
        }
    }
}