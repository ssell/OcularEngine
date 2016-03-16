/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#ifndef __H__OCULAR_EDITOR__H__
#define __H__OCULAR_EDITOR__H__

#include "Widgets/MainWindow.hpp"

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
        class Editor
        {
        public:

            static Editor& get();
            ~Editor();

            bool initialize(int argc, char** argv);
            void shutdown();
            bool run();

            //------------------------------------------------------------------------------

            MainWindow* getMainWindow();
            Core::Camera* getEditorCamera();

        protected:

        private:

            Editor();
            Editor(Editor const&) = delete;
            void operator=(Editor const&) = delete;

            bool setupEditorCamera();

            //------------------------------------------------------------------------------

            QApplication* m_QtApp;

            MainWindow* m_MainWindow;
            Core::Camera* m_EditorCamera;

        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

#define OcularEditor Ocular::Editor::Editor::get()

//------------------------------------------------------------------------------------------

#endif