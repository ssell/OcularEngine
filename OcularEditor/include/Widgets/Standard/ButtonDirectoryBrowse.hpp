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
#ifndef __H__OCULAR_BUTTON_DIRECTORY_BROWSE__H__
#define __H__OCULAR_BUTTON_DIRECTORY_BROWSE__H__

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
         * \class ButtonDirectoryBrowse
         *
         * Helper class implementation of QPushButton for selecting directories.
         */
        class ButtonDirectoryBrowse : public QPushButton
        {
            Q_OBJECT

        public:

            ButtonDirectoryBrowse(QWidget* parent = nullptr);
            virtual ~ButtonDirectoryBrowse();

            virtual QSize sizeHint() const override;
            
            /**
             * \param[in] reset If TRUE, then the edited flag is reset back to FALSE.
             * \return TRUE if the user has modifed this edit. 
             */
            bool wasEdited(bool reset = true);

            /**
             *
             */
            std::string const& getSelectedDirectory() const;

        protected:
            
        private slots :

            void onButtonClick();

        private:

            bool m_WasEdited;

            std::string m_SelectedDirectory;
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