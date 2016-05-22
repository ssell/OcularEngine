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
#ifndef __H__OCULAR_EDITOR_MESH_RENDERABLE_DISPLAY_MATERIAL__H__
#define __H__OCULAR_EDITOR_MESH_RENDERABLE_DISPLAY_MATERIAL__H__

#include <QtWidgets/qframe.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class Material;
    }

    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        class LineEdit;
        class ButtonResourceBrowse;

        class MeshRenderableDisplayMaterial : public QFrame
        {
        public:

            MeshRenderableDisplayMaterial(uint32_t index, QWidget* parent = nullptr);
            virtual ~MeshRenderableDisplayMaterial();

            virtual QSize sizeHint() const override;

            //------------------------------------------------------------

            void setMaterial(Graphics::Material* material);

        protected:

        private:

            void createLeftSide();
            void createRightSide();
            void createLayout();

            //------------------------------------------------------------

            QFrame* m_FrameLeftSide;             ///< Frame for the name label. Fixed width of 75.
            QFrame* m_FrameRightSide;            ///< Frame for the implementation-specific widgets

            QHBoxLayout* m_Layout;               ///< Layout for the overall widget
            QHBoxLayout* m_LayoutLeft;           ///< Layout for the left-side frame
            QHBoxLayout* m_LayoutRight;          ///< Layout for the right-side frame

            QLabel* m_LabelName;

            LineEdit* m_LineValue;
            ButtonResourceBrowse* m_ButtonBrowse;

            Graphics::Material* m_Material;
            uint32_t m_MaterialIndex;
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