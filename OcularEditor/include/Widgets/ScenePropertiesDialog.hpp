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
#ifndef __H__OCULAR_EDITOR_SCENE_PROPERTIES_DIALOG__H__
#define __H__OCULAR_EDITOR_SCENE_PROPERTIES_DIALOG__H__

#include <QtWidgets/qdialog.h>

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
        /**
         * \class ScenePropertiesDialog
         * \brief Dialog that displays various scene-based properties (Main Menu -> Scene -> Scene Properties)
         */
        class ScenePropertiesDialog : public QDialog
        {
            Q_OBJECT

        public:

            ScenePropertiesDialog(QWidget* parent = nullptr);
            virtual ~ScenePropertiesDialog();

        protected:

            void buildWidgets();
            void buildActionButtons();

        private slots:

            void onOK();
            void onCancel();
            void onApply();
            
        private:

            QVBoxLayout* m_MainLayout;

            QPushButton* m_ButtonOK;
            QPushButton* m_ButtonCancel;
            QPushButton* m_ButtonApply;
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