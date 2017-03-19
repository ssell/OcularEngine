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
#ifndef __H__OCULAR_BUTTON_FILE_BROWSE__H__
#define __H__OCULAR_BUTTON_FILE_BROWSE__H__

#include <QtWidgets/qpushbutton.h>

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
         * \class ButtonFileBrowse
         *
         * Helper class implementation of QPushButton for selecting files.
         */
        class ButtonFileBrowse : public QPushButton
        {
            Q_OBJECT

        public:

            ButtonFileBrowse(QWidget* parent = nullptr);
            virtual ~ButtonFileBrowse();

            virtual QSize sizeHint() const override;
            
            /**
             * \param[in] reset If TRUE, then the edited flag is reset back to FALSE.
             * \return TRUE if the user has modifed this edit. 
             */
            bool wasEdited(bool reset = true);

            /**
             * See QFileDialog::setNameFilter
             */
            void setNameFilter(std::string const& filter);

            /**
             *
             */
            std::string const& getSelectedFile() const;

        protected:
            
        private slots :

            void onButtonClick();

        private:

            bool m_WasEdited;

            std::string m_FilterString;
            std::string m_SelectedFile;
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