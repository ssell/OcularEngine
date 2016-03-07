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

#pragma once
#ifndef __H__OCULAR_EDITOR_MENU_BAR__H__
#define __H__OCULAR_EDITOR_MENU_BAR__H__

#include <QtWidgets/qmenubar.h>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        class MainWindow;
        
        /**
         * \class MainMenuBar
         * \brief The primary menu bar in the MainWindow widget
         */
        class MainMenuBar : QMenuBar
        {
            Q_OBJECT

        public:

            /**
             * \param[in] parent Parent widget of this menu bar, which may only be a MainWindow
             */
            MainMenuBar(MainWindow* parent = nullptr);
            ~MainMenuBar();

            virtual QSize sizeHint() const override;

        protected:

            void createActions();
            void createMenus();

        private slots:

            void fileNewProject();
            void fileOpenProject();
            void fileCloseProject();
            void fileNewScene();
            void fileOpenScene();
            void fileSaveScene();
            void fileSaveSceneAs();
            void fileCloseScene();
            void fileExit();
            void helpAbout();

        private:

            QMenu* m_MenuFile;
            QAction* m_MenuActionFileNewProject;
            QAction* m_MenuActionFileOpenProject;
            QAction* m_MenuActionFileCloseProject;
            QAction* m_MenuActionFileNewScene;
            QAction* m_MenuActionFileOpenScene;
            QAction* m_MenuActionFileSaveScene;
            QAction* m_MenuActionFileSaveSceneAs;
            QAction* m_MenuActionFileCloseScene;
            QAction* m_MenuActionFileExit;

            QMenu* m_MenuEdit;

            QMenu* m_MenuHelp;
            QAction* m_MenuActionHelpAbout;

            std::string m_LastScenePath;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif
