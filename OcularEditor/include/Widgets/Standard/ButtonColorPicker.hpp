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
#ifndef __H__OCULAR_EDITOR_BUTTON_COLOR_PICKER__H__
#define __H__OCULAR_EDITOR_BUTTON_COLOR_PICKER__H__

#include <QtWidgets/qpushbutton.h>
#include "Math/Color.hpp"

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
         * \class ButtonColorPicker
         *
         * Helper class implementation of QPushButton for picking colors.
         */
        class ButtonColorPicker : public QPushButton
        {
            Q_OBJECT

        public:

            ButtonColorPicker(QWidget* parent = nullptr);
            ~ButtonColorPicker();

            virtual QSize sizeHint() const override;

            /**
             * \param[in] reset If TRUE, then the edited flag is reset back to FALSE.
             * \return TRUE if the user has modifed this edit. 
             */
            bool wasEdited(bool reset = true);

            /**
             *
             */
            Core::Color const& getSelectedColor() const;

        protected:
            
        private slots:

            void onButtonClick();

        private:

            bool m_WasEdited;

            Core::Color m_SelectedColor;
            QColor m_QColor;
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