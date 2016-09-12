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
#ifndef __H__OCULAR_EDITOR_MAIN_WINDOW__H__
#define __H__OCULAR_EDITOR_MAIN_WINDOW__H__

#include <QtWidgets/QMainWindow>

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
        class MainMenuBar;
        class MainStatusBar;
        class ContentFrame;
        class ToolbarCommon;

        /**
         * \class MainWindow
         * \brief Main window for the Ocular Editor application
         */
        class MainWindow : public QMainWindow
        {
            Q_OBJECT

        public:

            MainWindow(QWidget* parent = nullptr);
            ~MainWindow();

            virtual QSize sizeHint() const override;

            void update();

            //------------------------------------------------------------
            // Getters
            //------------------------------------------------------------

            /**
             * Returns a pointer to the primary menu bar.
             */
            MainMenuBar* getMainMenu() const;

            /**
             * Returns a pointer to the primary status bar.
             */
            MainStatusBar* getMainStatusBar() const;

            /**
             * Returns a pointer to the primary toolbar.
             */
            ToolbarCommon* getCommonToolbar() const;

            /**
             * Returns a pointer to the ContentFrame which contains the PropertiesPanel,  ConsoleText, and SceneTree
             */
            ContentFrame* getContentFrame() const;

        protected:

        private:

            void setupLayouts();
            void setupMenus();
            void setupMainWidget();
            void setupToolbars();
            void setupContent();

            void setFrameStatsMessage();

            //------------------------------------------------------------

            QWidget* m_MainWidget;
            
            QVBoxLayout* m_LayoutMain;          ///< Layout for the entire window

            MainMenuBar*   m_MenuBar;
            MainStatusBar* m_StatusBar;
            ContentFrame*  m_ContentFrame;

            ToolbarCommon* m_ToolbarCommon;
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
