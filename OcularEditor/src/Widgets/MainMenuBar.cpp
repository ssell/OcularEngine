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
#include "Widgets/MainMenuBar.hpp"
#include "Widgets/MainWindow.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MainMenuBar::MainMenuBar(MainWindow* parent)
            : QMenuBar(parent),
              m_MenuFile(nullptr),
              m_MenuEdit(nullptr),
              m_MenuHelp(nullptr)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            createActions();
            createMenus();
        }

        MainMenuBar::~MainMenuBar()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize MainMenuBar::sizeHint() const
        {
            // Some arbitrarily large size so that the frame always exapnds to fill all available space
            return QSize(99999, 99999);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void MainMenuBar::createActions()
        {
            // Must be called before createMenus
            
            //------------------------------------------------------------
            // File Menu Actions

            m_MenuActionFileNewProject = new QAction(tr("New Project"), this);
            connect(m_MenuActionFileNewProject, SIGNAL(triggered()), this, SLOT(fileNewProject()));

            m_MenuActionFileOpenProject = new QAction(tr("Open Project"), this);
            connect(m_MenuActionFileOpenProject, SIGNAL(triggered()), this, SLOT(fileOpenProject()));

            m_MenuActionFileCloseProject = new QAction(tr("Close Project"), this);
            connect(m_MenuActionFileCloseProject, SIGNAL(triggered()), this, SLOT(fileCloseProject()));

            m_MenuActionFileNewScene = new QAction(tr("New Scene"), this);
            connect(m_MenuActionFileNewScene, SIGNAL(triggered()), this, SLOT(fileNewScene()));

            m_MenuActionFileOpenScene = new QAction(tr("Open Scene"), this);
            connect(m_MenuActionFileOpenScene, SIGNAL(triggered()), this, SLOT(fileOpenScene()));

            m_MenuActionFileSaveScene = new QAction(tr("Save Scene"), this);
            connect(m_MenuActionFileSaveScene, SIGNAL(triggered()), this, SLOT(fileSaveScene()));

            m_MenuActionFileSaveSceneAs = new QAction(tr("Save Scene As..."), this);
            connect(m_MenuActionFileSaveSceneAs, SIGNAL(triggered()), this, SLOT(fileSaveSceneAs()));

            m_MenuActionFileCloseScene = new QAction(tr("Close Scene"), this);
            connect(m_MenuActionFileCloseScene, SIGNAL(triggered()), this, SLOT(fileCloseScene()));

            m_MenuActionFileExit = new QAction(tr("Exit"), this);
            connect(m_MenuActionFileExit, SIGNAL(triggered()), this, SLOT(fileExit()));

            //------------------------------------------------------------
            // Edit Menu Actions

            //------------------------------------------------------------
            // Help Menu Actions

            m_MenuActionHelpAbout = new QAction(tr("About Ocular Editor"), this);
            connect(m_MenuActionHelpAbout, SIGNAL(triggered()), this, SLOT(helpAbout()));

        }

        void MainMenuBar::createMenus()
        {
            // Must be called after createActions
            
            //------------------------------------------------------------
            // File Menu

            m_MenuFile = addMenu(tr("&FILE"));
            m_MenuFile->addAction(m_MenuActionFileNewProject);
            m_MenuFile->addAction(m_MenuActionFileOpenProject);
            m_MenuFile->addAction(m_MenuActionFileCloseProject);
            m_MenuFile->addSeparator();
            m_MenuFile->addAction(m_MenuActionFileNewScene);
            m_MenuFile->addAction(m_MenuActionFileOpenScene);
            m_MenuFile->addAction(m_MenuActionFileSaveScene);
            m_MenuFile->addAction(m_MenuActionFileSaveSceneAs);
            m_MenuFile->addAction(m_MenuActionFileCloseScene);
            m_MenuFile->addSeparator();
            m_MenuFile->addAction(m_MenuActionFileExit);
            
            //------------------------------------------------------------
            // Edit Menu

            m_MenuEdit = addMenu(tr("&EDIT"));
            
            //------------------------------------------------------------
            // Help Menu

            m_MenuHelp = addMenu(tr("&HELP"));
            m_MenuHelp->addAction(m_MenuActionHelpAbout);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void MainMenuBar::fileNewProject()
        {

        }

        void MainMenuBar::fileOpenProject()
        {

        }

        void MainMenuBar::fileCloseProject()
        {

        }

        void MainMenuBar::fileNewScene()
        {
            OcularScene->createScene("New Scene");
        }

        void MainMenuBar::fileOpenScene()
        {
            const std::string searchPath = (m_LastScenePath.size() ? m_LastScenePath : OcularResources->getSourceDirectory());
            const std::string path = QFileDialog::getOpenFileName(this, tr("Open Scene"), searchPath.c_str(), tr("Ocular Scene Files (*.oscene)")).toStdString();

            Core::File openFile(path);

            if(openFile.exists() && openFile.canRead() && Utils::String::IsEqual(openFile.getExtension(), ".oscene"))
            {
                if(OcularScene->loadScene(openFile))
                {
                    m_LastScenePath = path;
                }
            }
        }

        void MainMenuBar::fileSaveScene()
        {
            if(m_LastScenePath.size())
            {
                OcularScene->saveScene(Core::File(m_LastScenePath));
            }
            else
            {
                fileSaveSceneAs();
            }
        }

        void MainMenuBar::fileSaveSceneAs()
        {
            const std::string searchPath = (m_LastScenePath.size() ? m_LastScenePath : OcularResources->getSourceDirectory());
            const std::string path = QFileDialog::getSaveFileName(this, tr("Save Scene"), searchPath.c_str(), tr("Ocular Scene Files (*.oscene)")).toStdString();

            Core::File saveFile(path);

            if(OcularScene->saveScene(saveFile))
            {
                m_LastScenePath = path;
            }
        }

        void MainMenuBar::fileCloseScene()
        {

        }

        void MainMenuBar::fileExit()
        {

        }

        void MainMenuBar::helpAbout()
        {

        }
    }
}