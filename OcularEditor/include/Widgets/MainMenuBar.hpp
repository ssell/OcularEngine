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

            void createFileMenu();
            void createSceneMenu();
            void createHelpMenu();

        private slots:

            void onFileNewProject();
            void onFileOpenProject();
            void onFileCloseProject();
            void onFileNewScene();
            void onFileOpenScene();
            void onFileSaveScene();
            void onFileSaveSceneAs();
            void onFileCloseScene();
            void onFileExit();

            void onSceneAddObject();
            void onSceneAddMesh();
            void onSceneAddLight();
            void onSceneImportObject();

            void onHelpAbout();



        private:

            QMenu* m_MenuFile;
            QMenu* m_MenuScene;
            QMenu* m_MenuSceneMesh;
            QMenu* m_MenuSceneLight;
            QMenu* m_MenuHelp;

            std::vector<QAction*> m_MenuActions;   ///< Container of all menu actions. Kept for end-of-life cleanup.

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
