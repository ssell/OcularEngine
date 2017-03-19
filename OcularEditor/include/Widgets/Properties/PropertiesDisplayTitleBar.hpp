/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_EDITOR_PROPERTIES_DISPLAY_TITLE_BAR__H__
#define __H__OCULAR_EDITOR_PROPERTIES_DISPLAY_TITLE_BAR__H__


#include <QtWidgets/qframe.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>

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
         * \class PropertiesDisplayTitleBar
         */
        class PropertiesDisplayTitleBar : public QFrame
        {
        public:

            PropertiesDisplayTitleBar(std::string const& displayName, bool canMinimize = true, bool canClose = false, QWidget* parent = nullptr);
            ~PropertiesDisplayTitleBar();

            virtual QSize sizeHint() const override;

            //------------------------------------------------------------

            void setTitle(std::string const& title);
            void setCanMinimize(bool canMinimize);
            void setCanClose(bool canClose);

        protected:

            void buildLayout();
            void buildTitleBar();

            //------------------------------------------------------------

            QHBoxLayout* m_Layout;

            QLabel* m_LabelTitle;

            QPushButton* m_ButtonMinimize;
            QPushButton* m_ButtonClose;
            
            bool m_CanMinimize;
            bool m_CanClose;

        private:
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