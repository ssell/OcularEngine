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
#ifndef __H__OCULAR_EDITOR_MATERIAL_EDITOR_DIALOG__H__
#define __H__OCULAR_EDITOR_MATERIAL_EDITOR_DIALOG__H__

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
        class MaterialTree;
        class MaterialPropertiesPanel;

        /**
         * \class MaterialEditorDialog
         * \brief Dialog to view and editor Material resource objects.
         */
        class MaterialEditorDialog : public QDialog
        {
            Q_OBJECT

        public:

            MaterialEditorDialog(QWidget* parent = nullptr);
            virtual ~MaterialEditorDialog();

            virtual void showEvent(QShowEvent* event) override;

        protected:

            void buildWidgets();
            void buildLeftSide();
            void buildRightSide();
            void buildPropertyPanel();
            void buildActionButtons();

        private slots:

            void onOK();
            void onCancel();
            void onApply();

        private:

            QHBoxLayout* m_MainLayout;              ///< Layout for the entire dialog 
            QVBoxLayout* m_RightLayout;             ///< Layout for the right-side of the dialog (property panel/action buttons)
            QHBoxLayout* m_ActionButtonLayout;      ///< Layout for the action buttons on lower-right side
            QVBoxLayout* m_MaterialTreeLayout;
            QVBoxLayout* m_MaterialGroupLayout;
            QVBoxLayout* m_PropertyGroupLayout;

            QPushButton* m_ButtonOK;
            QPushButton* m_ButtonCancel;
            QPushButton* m_ButtonApply;

            QFrame* m_LeftFrame;
            QFrame* m_RightFrame;
            QFrame* m_ActionButtonFrame;
            
            QGroupBox* m_MaterialGroupBox;
            QGroupBox* m_PropertyGroupBox;

            MaterialTree* m_MaterialTree;
            MaterialPropertiesPanel* m_MaterialProperties;
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